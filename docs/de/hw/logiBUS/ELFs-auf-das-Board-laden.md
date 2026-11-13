# Fehlende ELFs auf das Trainer-Board laden

Diese Anleitung zeigt am Beispiel von Übung 256 (PWM-Frequenz, `test_AX/Uebungen/Uebung_256_AX.SUB`), wie ein Programm per Online-Deploy aus der 4diac IDE auf das Trainer-Board gelangt und was zu tun ist, wenn die IDE `UNSUPPORTED_TYPE` meldet. Hintergrund zu den Skripten steht auf der Seite [Deploy-Skripte und Launches](Deploy-Skripte-und-Launches.md).

## Worum es geht

FORTE auf dem Board kennt nur die Grundbausteine. Die Bibliotheken der Übungen (Adapter, logiBUS-IO, Speicher, OPC UA und weitere) liegen als ELF-Dateien in `/data/elf-libs/` auf dem Board und werden beim Start geladen. Fehlt eine ELF, meldet die IDE beim Deploy `UNSUPPORTED_TYPE` für den betroffenen Baustein.

Die ELFs gehören zum Trainingsprojekt. Sie liegen unter `Ventilsteuerung/4diacIDE-workspace/.lib/<Lib>-<Version>/elf/riscv32/`. Das Skript `RunSkript_PreloadELF_AX` lädt die **ELF-Grundausstattung** (die häufig gebrauchten Bibliotheken samt Abhängigkeiten) in einem Rutsch auf das Board. Welche Bibliotheken dazugehören, steht in `PRELOAD_LIBS` in `scripts_central/deploy_common.py`.

Übung 256 braucht nur Bibliotheken aus der Grundausstattung:

- `logiBUS_io`
- `adapter`, `adapter_types`, `adapter_conversion`, `adapter_events`, `adapter_iec61131-3`
- `net_adapter`
- `logiBUS_storage`
- `iec61131-3`, `iec61131-3-bool`, `events`

Ein Durchlauf von `RunSkript_PreloadELF_AX` genügt also. Dasselbe gilt für die Übungen 265 und 266.

## Voraussetzungen

- Das Trainingsprojekt ist auf dem aktuellen Stand (`git pull` oder neuestes Release). Nur dann passen die ELFs zu den Bausteinen in der IDE.
- Python 3 ist installiert und `python` steht im Pfad. Weitere Pakete braucht es nicht.
- Das Trainer-Board hängt per Netzwerkkabel am PC. **Nur ein Board gleichzeitig anschließen**: Alle Boards melden sich unter demselben Namen `logibus.local`, und es ist Zufall, welches antwortet (siehe [Hostname und mDNS](Deploy-Skripte-und-Launches.md#hostname-und-mdns)).
- Im Browser öffnet sich `http://logibus.local/` mit der Weboberfläche des Boards. Wenn nicht, ist das Board nicht erreichbar: Kabel und Netzwerkadapter prüfen.

## Schritt 1: Grundausstattung aufspielen

In der 4diac IDE: **Run → External Tools → `RunSkript_PreloadELF_AX.bat`**. Alternativ `test_AX/scripts/RunSkript_PreloadELF_AX.bat` per Doppelklick starten.

Die Ausgabe zeigt jede ELF mit dem Status `OK` oder `unveraendert (Hash stimmt), uebersprungen`. Am Ende muss stehen:

    ZUSAMMENFASSUNG (1/1 Knoten erfolgreich):
      - logibus.local: OK

!!! warning "Das Skript löscht Boot-Dateien und Manifeste"
    Alle Boot-Dateien (`*.fboot`) und Bibliotheks-Manifeste (`*.libs.json`) auf dem Board werden gelöscht. FORTE startet danach leer und wartet auf das Deploy aus der IDE. Mehr dazu unter [Knoten vorbereiten (Preload)](Deploy-Skripte-und-Launches.md#knoten-vorbereiten-preload).

Bricht das Skript mit einer Warnung ab, einfach noch einmal starten. ELFs, die schon auf dem Board liegen, überspringt es.

## Schritt 2: Board neu starten

Auf `http://logibus.local/` den **Reboot**-Button drücken. Erst nach dem Neustart lädt FORTE die neuen ELFs.

## Schritt 3: Übung 256 deployen

1. In `test_AX/sys/Training_AX/test_AX.sys` die SubApp **`Control`** auswählen.
2. Mit Rechtsklick → **Change Type** den Typ `Uebungen::Uebung_256_AX` wählen und speichern.
3. **Run As → `Deploy_App_AX`** starten. Alternativ im System-Explorer per Rechtsklick auf `FORTE_PC_AX` → Deploy.

Das Gerät `FORTE_PC_AX` spricht das Board über `logibus.local:61499` an. Die Adresse muss nicht angepasst werden.

## Wenn `UNSUPPORTED_TYPE` kommt

Die Meldung nennt den Bausteintyp. Dann der Reihe nach prüfen:

1. **Board neu gestartet?** Ohne Neustart nach Schritt 1 liegen die ELFs zwar auf dem Board, sind aber nicht geladen.
2. **Trainingsprojekt aktuell?** Ein neuer Baustein in der IDE braucht die passende, ebenfalls neue ELF. Projekt aktualisieren und die Schritte 1 und 2 wiederholen.
3. **Bibliothek nicht in der Grundausstattung?** Der Namensraum des Typs zeigt die Bibliothek, zum Beispiel `adapter::events::…` gehört zu `adapter_events`. Fehlt sie in `PRELOAD_LIBS` in `scripts_central/deploy_common.py`, gehört sie nicht zur Grundausstattung. Dann liefert der Online-Deploy `UNSUPPORTED_TYPE`. Beispiel: `SPLIT_WORD_INTO_BOOLS` und `ASSEMBLE_BYTE_FROM_BOOLS` stammen aus der Bibliothek `utils`. Sie gehört nicht zur Grundausstattung, deshalb meldet der Online-Deploy dafür `UNSUPPORTED_TYPE`.
4. **Baustein noch nicht in der ELF?** Ein neuer Baustein kann in der IDE schon als Typ vorhanden sein, bevor seine ELF neu gebaut ist. Dann hilft kein Hochladen: Die ELF muss neu gebaut werden.

!!! info "`NO_SUCH_OBJECT` ist nur eine Folge"
    Meldet die Konsole `NO_SUCH_OBJECT` bei allen Verbindungen eines Bausteins, wurde der Baustein selbst nicht angelegt, weil seine ELF fehlt oder veraltet ist. Die eigentliche Ursache steht weiter oben in der Konsole bei `CREATE`. Dort zuerst nachsehen.

## Gut zu wissen

- **Speicherplatz:** `http://logibus.local/space/` zeigt die Belegung. Ein fast volles Dateisystem kann bei weiteren Uploads beschädigt werden und wird beim nächsten Start neu formatiert. Dabei sind alle Dateien auf dem Board weg. Dann die Schritte 1 und 2 wiederholen.
- **Nächste Übung:** Die ELFs bleiben auf dem Board. Für weitere Übungen nur Schritt 3 mit dem anderen Typ wiederholen.

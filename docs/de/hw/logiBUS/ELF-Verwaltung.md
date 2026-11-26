# ELF-Verwaltung (grafische Oberfläche)

Die ELF-Verwaltung (`scripts_central/elf_manager_gui.py`) ist eine kleine grafische Oberfläche, mit der einzelne ELF-Bibliotheken auf einen logiBUS-Knoten nachinstalliert werden, ohne das komplette Preload zu wiederholen. Sie benutzt nur die Python-Standardbibliothek (tkinter). Hintergrund zu den ELFs steht auf der Seite [Fehlende ELFs auf das Trainer-Board laden](ELFs-auf-das-Board-laden.md), zu den Skripten auf [Deploy-Skripte und Launches](Deploy-Skripte-und-Launches.md).

> **Hinweis:** Die Seite beschreibt das Programm nach seinem Quelltext. Es ist nicht auf Hardware getestet.

## Starten

- Aus der 4diac IDE über External Tools beziehungsweise den Launch `RunSkript_ElfManager_AX` (als Favorit eingetragen).
- Oder in `scripts_central` mit `python elf_manager_gui.py [host]`. Ohne Angabe ist der Host `logibus.local`.
- Laut Auskunft der Entwicklung legt der TrainingsInstaller ab dem ersten Release nach dem Merge eine Verknüpfung „logiBUS ELF-Verwaltung“ an (nicht geprüft).

## Ablauf

1. **Verbinden:** Host eintragen, „Verbinden / Aktualisieren“ drücken. Das Programm löst den Host auf, prüft, dass er im internen Netz liegt und erreichbar ist, und ermittelt Architektur und `FORTE_ABI` des Knotens. Passt die Architektur nicht (Firmware zu alt oder zu neu), bricht es mit einer Meldung ab. Laut Entwicklung gilt `FORTE_ABI` 7, also Firmware ab b-199. `isobus_fs` und ELFs auf dem ESP32-S31 gibt es erst ab b-214 (Auskunft der Entwicklung, nicht geprüft).
2. **Liste:** Alle ELF-Bibliotheken des Repos erscheinen mit Version, Stand auf dem Knoten und der Spalte „Wird geladen“. Dort steht „ja“, wenn die Bibliothek im aktiven Manifest steht. Aktiv ist das alphabetisch erste `*.libs.json`, denn das nimmt der Loader.
3. **Auswählen:** Ein Klick (oder Leertaste) hakt eine Bibliothek an (☑) oder ab (☐).
   - „Nur Grundausstattung“ hakt `PRELOAD_LIBS` samt Abhängigkeiten an.
   - „Aktuelles Manifest“ hakt an, was gerade geladen wird.
4. **Installieren:** „Angehakte installieren“. Nach einer Sicherheitsabfrage werden die angehakten Bibliotheken samt ihrer `requires` (aus `MANIFEST.MF`) aufgelöst, höchstens 64 Stück. Danach läuft derselbe Ablauf wie beim Preload: ELFs hochladen, andere Manifeste und alle `*.fboot` auf dem Knoten löschen, `elf_grundausstattung.libs.json` schreiben.
5. **Neustart:** Wirksam wird die Änderung erst nach dem Neustart des Knotens. Der Button „Weboberfläche“ öffnet die Seite des Knotens im Browser. Im Protokollfenster unten stehen alle Ausgaben.

## Status in der Spalte „Auf dem Knoten“

| Status | Bedeutung |
|---|---|
| aktuell | SHA256 der ELF am Knoten gleicht der im Repo |
| anderer Stand | gleicher Dateiname, anderer Hash |
| alte Version | eine andere Versionsnummer der Bibliothek liegt am Knoten |
| fehlt | nichts davon am Knoten |
| keine ELF im Repo | für diese Architektur gibt es keine ELF |

Rot markiert sind „fehlt“, „alte Version“ und „anderer Stand“. Bibliotheken für CAN2 tragen den Zusatz „(CAN2, nicht am Trainer)“.

## Typischer Fall

Die Dateisystem-Übungen (156/156b) brauchen `isobus_fs`, das nicht zur Grundausstattung gehört: `isobus_fs` anhaken, installieren, Knoten neu starten.

## Wichtig

- Der Loader lädt nur Bibliotheken, die im Manifest stehen. Eine ELF, die nur in `elf-libs/` liegt, ist für FORTE nicht vorhanden.
- Die Installation löscht andere Manifeste und alle Bootfiles auf dem Knoten.

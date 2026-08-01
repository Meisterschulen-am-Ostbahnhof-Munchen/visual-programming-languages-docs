# Schreibgeschützte Einstellungen (`settingsReadOnly.ini`)

## Einleitung

In logiBUS®-Systemen werden Konfigurationswerte und Parameter in INI-Dateien auf dem Dateisystem des Steuergeräts verwaltet. Neben der frei beschreibbaren Standard-Konfigurationsdatei (`settings.ini`) unterstützt das System eine schreibgeschützte Einstellungsdatei: **`settingsReadOnly.ini`**.

Dieses Feature dient dazu, Werkseinstellungen, herstellerseitige Systemparameter, feste Kommunikationsadressen oder kritische Hardware- und Sicherheitsoptionen dauerhaft einzufrieren. So wird verhindert, dass wichtige Parameter durch Bediener oder durch die Steuerungsausführung versehentlich geändert werden.

---

## Konzept der zwei Konfigurationsdateien

Das Steuergerät unterscheidet zwei Ebenen der Konfigurationsspeicherung:

| Datei | Zweck | Schreibbar? | Typische Inhalte |
|---|---|---|---|
| **`settingsReadOnly.ini`** | Werkseinstellungen & Systemvorgaben | ❌ Nein (Schreibschutz) | ISOBUS-Quelladressen (Node-SAs), Hardware-Pinbelegungen, fest vorgegebene Boot-Zeiten |
| **`settings.ini`** | Benutzer- & Laufzeiteinstellungen | ✅ Ja (Lesen & Schreiben) | Benutzerpräferenzen, dynamische Betriebsparameter, wählbare Grenzwert-Skalierungen |

### Funktionsweise & Priorität beim Start

1. **Vorrang von Werkseinstellungen**: Beim Booten liest das Steuergerät zuerst die Datei `settingsReadOnly.ini`. Alle darin definierten Abschnitte (`[Section]`) und Schlüssel (`KEY`) werden schreibgeschützt geladen.
2. **Automatische Bereinigung (*Purge*)**: Befindet sich ein Schlüssel sowohl in `settingsReadOnly.ini` als auch in der beschreibbaren `settings.ini`, wird der doppelte Schlüssel beim Systemstart automatisch aus `settings.ini` **entfernt**. Dadurch ist gewährleistet, dass keine widersprüchlichen Werte existieren und die Benutzerdatei übersichtlich bleibt.
3. **Ergänzendes Laden**: Alle Parameter, die *nicht* in `settingsReadOnly.ini` stehen, werden aus `settings.ini` geladen und verhalten sich normal schreibbar.

---

## Verhalten im Betrieb (Lesen & Schreiben)

### Lesezugriffe (`GET`)
Das Auslesen von Parametern erfolgt transparent. Wenn ein Schlüssel in `settingsReadOnly.ini` hinterlegt ist, wird stets dessen unveränderlicher Wert zurückgegeben.

### Schreibzugriffe (`SET`)
Wird versucht, einen schreibgeschützten Schlüssel zu ändern (egal ob durch Steuerungsfunktionen oder über 4diac IEC 61499 Funktionsblöcke), passiert Folgendes:
* Der **Schreibversuch wird abgelehnt**.
* Der in `settingsReadOnly.ini` festgelegte Wert **bleibt unverändert**.
* Die Ablehnung des Schreibvorgangs wird protokolliert und an die aufrufende Baustein-Logik zurückgemeldet.

---

## Verhalten in 4diac FORTE (IEC 61499 INI-Bausteine)

Für Anwender von 4diac FORTE Steuerungsprogrammen verhalten sich die INI-Funktionsblöcke (`INI`, `INI_AX`, `INI_AUI`, `INI_AR` usw.) bei schreibgeschützten Parametern wie folgt:

* **Lese-Ereignis (`GET`)**: Signalisiert wie gewohnt das Bestätigungsereignis `GETO`. Am Ausgang `VALUEO` liegt der geschützte Wert an, `STATUS` meldet `"OK"`.
* **Schreib-Ereignis (`SET`)**:
  * Es wird **nicht** das normale Erfolgsereignis (`SETO`) ausgelöst, sondern das Fehler-Ereignis **`SETOE`** (*Set Output Error*).
  * Der Datenausgang **`STATUS`** liefert die verständliche Meldung: **`"Key is read-only"`**.
  * Der Ausgang **`QO`** zeigt den Fehlerzustand an.

!!! note "Hinweis für Applikationsentwickler"
    Durch Auswerten des Ausgangsereignisses `SETOE` oder des Statusstrings `"Key is read-only"` kann in der 4diac-Applikation gezielt auf schreibgeschützte Parameter reagiert werden (z. B. Anzeige eines Hinweises auf der Visualisierung).

---

## Einspielen und Verwalten der Werkseinstellungen

Die Datei `settingsReadOnly.ini` liegt auf dem Speicher des Steuergeräts unter:
`/data/settingsReadOnly.ini`

### Übertragung auf das Steuergerät
Das Einspielen oder Aktualisieren der Werkseinstellungen erfolgt einfach über das integrierte **Web-Interface** (File Server) des Steuergeräts:

1. Verbinden Sie sich über einen Webbrowser mit dem Web-Interface des Steuergeräts.
2. Navigieren Sie zur Dateiverwaltung (`/data`).
3. Laden Sie Ihre vorbereitete `settingsReadOnly.ini` hoch.
4. Nach einem Neustart des Steuergeräts werden die schreibgeschützten Parameter wirksam.

### Verhalten bei fehlender Datei
Falls keine `settingsReadOnly.ini` auf dem Steuergerät vorhanden ist, startet das System gewohnt ohne Einschränkungen. Alle Schlüssel in `settings.ini` verhalten sich wie bisher voll beschreibbar.

---

## Praktisches Beispiel

### Beispieldatei `settingsReadOnly.ini` (Werkseinstellungen):
```ini
[CF-A]
NODE1_SA = 128
bootTimeVT = 90

[System]
DeviceName = LOGIBUS-NODE-01
```

### Beispieldatei `settings.ini` (Benutzereinstellungen):
```ini
[CF-A]
UserLanguage = DE

[User]
OperatorID = 42
```

**Ergebnis im Betrieb:**
* `NODE1_SA` (`128`), `bootTimeVT` (`90`) und `DeviceName` (`"LOGIBUS-NODE-01"`) sind geschützt und können nicht verändert werden.
* `UserLanguage` (`"DE"`) und `OperatorID` (`42`) können durch die Steuerung frei geändert und dauerhaft gespeichert werden.
* Sollte in `settings.ini` versehentlich ein alter Wert `NODE1_SA = 130` vorhanden gewesen sein, löscht das Steuergerät diesen beim Booten automatisch, sodass stets die Vorgabe `128` gilt.

---

## Zusammenfassung & Best Practices

| Ziel | Empfohlene Vorgehensweise |
|---|---|
| **Werkseinstellungen sichern** | Legen Sie alle unveränderlichen Parameter (z. B. Bus-Adressen, Sicherheitsgrenzen) in `settingsReadOnly.ini` an und spielen Sie diese auf das Steuergerät auf. |
| **Benutzereinstellungen erlauben** | Halten Sie Parameter, die vom Bediener angepasst werden dürfen (z. B. Sprache, Betriebsmodi, Zählerstände), ausschließlich in `settings.ini`. |
| **Parameter freigeben** | Um einen Parameter wieder beschreibbar zu machen, entfernen Sie den betreffenden Schlüssel aus `settingsReadOnly.ini` und starten Sie das Steuergerät neu. |

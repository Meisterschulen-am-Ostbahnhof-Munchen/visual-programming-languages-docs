# CSV_WRITER_2

![CSV_WRITER_2](https://github.com/user-attachments/assets/3c2f2095-ba2e-4a3a-9484-9f5c310500e9)

* * * * * * * * * *
## Einleitung
Der CSV_WRITER_2 ist ein Funktionsblock, der dazu dient, Daten in eine CSV-Datei zu schreiben. Er bietet eine einfache Schnittstelle für die Initialisierung und den Schreibvorgang, wobei zwei verschiedene Datenfelder unterstützt werden. Der Funktionsblock ist besonders nützlich für Anwendungen, bei denen Daten persistent gespeichert oder für weitere Analysen exportiert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Funktionsblock und konfiguriert den Dateinamen für die CSV-Datei.
  - Eingangsdaten: `QI` (BOOL), `FILE_NAME` (STRING)
- **REQ**: Startet den Schreibvorgang der Daten in die CSV-Datei.
  - Eingangsdaten: `QI` (BOOL), `SD_1` (ANY), `SD_2` (ANY)

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung des Funktionsblocks.
  - Ausgangsdaten: `QO` (BOOL), `STATUS` (STRING)
- **CNF**: Bestätigt den erfolgreichen Abschluss des Schreibvorgangs.
  - Ausgangsdaten: `QO` (BOOL), `STATUS` (STRING)

### **Daten-Eingänge**
- **QI**: Qualifiziert das Ereignis (TRUE für gültig, FALSE für ungültig).
- **FILE_NAME**: Der Name der CSV-Datei, in die geschrieben werden soll.
- **SD_1**: Das erste Datenfeld, das in die CSV-Datei geschrieben wird (beliebiger Datentyp).
- **SD_2**: Das zweite Datenfeld, das in die CSV-Datei geschrieben wird (beliebiger Datentyp).

### **Daten-Ausgänge**
- **QO**: Qualifiziert das Ausgangsereignis (TRUE für erfolgreich, FALSE für fehlgeschlagen).
- **STATUS**: Gibt den Status des Dateizugriffs zurück (z.B. Erfolgsmeldung oder Fehlerbeschreibung).

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
1. **Initialisierung**: Durch das Senden eines `INIT`-Ereignisses mit dem gewünschten Dateinamen (`FILE_NAME`) wird der Funktionsblock initialisiert. Der Status der Initialisierung wird über `INITO` zurückgemeldet.
2. **Daten schreiben**: Das `REQ`-Ereignis löst den Schreibvorgang aus. Die Daten `SD_1` und `SD_2` werden in die CSV-Datei geschrieben. Der Erfolg oder Misserfolg des Schreibvorgangs wird über `CNF` gemeldet.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen für die zu schreibenden Daten (`SD_1` und `SD_2`).
- Der Status (`STATUS`) gibt detaillierte Informationen über den Erfolg oder Fehler des Dateizugriffs.
- Der Funktionsblock ist Teil des `eclipse4diac::utils`-Pakets.

## Zustandsübersicht
1. **Inaktiv**: Der Funktionsblock wartet auf Initialisierung.
2. **Initialisiert**: Der Funktionsblock ist bereit, Daten zu schreiben.
3. **Schreibvorgang**: Der Funktionsblock schreibt Daten in die CSV-Datei.

## Anwendungsszenarien
- Protokollierung von Prozessdaten in einer CSV-Datei für spätere Analysen.
- Export von Messdaten für externe Auswertungen.
- Speicherung von Konfigurationsdaten in einem lesbaren Format.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren Schreibfunktionsblöcken unterstützt `CSV_WRITER_2` zwei Datenfelder und bietet eine detaillierte Statusrückmeldung.
- Andere CSV-Schreibfunktionsblöcke könnten weniger flexibel in der Datentypunterstützung sein oder keine Statusrückmeldung bieten.

## Fazit
Der `CSV_WRITER_2` ist ein flexibler und zuverlässiger Funktionsblock für das Schreiben von Daten in CSV-Dateien. Seine Unterstützung für beliebige Datentypen und detaillierte Statusrückmeldungen machen ihn ideal für Anwendungen, bei denen Daten persistent gespeichert werden müssen.

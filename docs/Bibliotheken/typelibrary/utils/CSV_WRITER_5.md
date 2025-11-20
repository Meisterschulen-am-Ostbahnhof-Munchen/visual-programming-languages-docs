# CSV_WRITER_5

![CSV_WRITER_5](https://github.com/user-attachments/assets/f24a7a1e-0d03-409e-8ce7-c7d9a9719c2c)

* * * * * * * * * *
## Einleitung
Der CSV_WRITER_5 ist ein Funktionsblock zur Ausgabe von Daten in eine CSV-Datei. Er ermöglicht das Schreiben von bis zu fünf verschiedenen Datenpunkten in eine benutzerdefinierte Datei. Der Funktionsblock ist besonders nützlich für Datenerfassungs- und Protokollierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Funktionsblock und öffnet die angegebene CSV-Datei.
  - Verknüpfte Daten: QI (BOOL), FILE_NAME (STRING)
- **REQ**: Löst den Schreibvorgang aus.
  - Verknüpfte Daten: QI (BOOL), SD_1 bis SD_5 (ANY)

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung.
  - Verknüpfte Daten: QO (BOOL), STATUS (STRING)
- **CNF**: Bestätigt den erfolgreichen Schreibvorgang.
  - Verknüpfte Daten: QO (BOOL), STATUS (STRING)

### **Daten-Eingänge**
- **QI**: Qualifiziert das Ereignis (TRUE für aktiv, FALSE für inaktiv).
- **FILE_NAME**: Name der CSV-Datei, in die geschrieben werden soll.
- **SD_1 bis SD_5**: Die zu schreibenden Daten (beliebiger Typ).

### **Daten-Ausgänge**
- **QO**: Gibt den Status des Funktionsblocks zurück (TRUE für erfolgreich, FALSE für Fehler).
- **STATUS**: Enthält eine Statusmeldung über den letzten Vorgang.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. **Initialisierung**: Durch das INIT-Ereignis wird die CSV-Datei mit dem angegebenen Namen geöffnet. Falls die Datei nicht existiert, wird sie erstellt.
2. **Daten schreiben**: Das REQ-Ereignis löst den Schreibvorgang aus. Die Daten SD_1 bis SD_5 werden als eine Zeile in die CSV-Datei geschrieben.
3. **Bestätigung**: Nach jedem Schreibvorgang wird das CNF-Ereignis ausgelöst, das den Status des Vorgangs zurückgibt.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen für die Ausgabedaten (ANY).
- Der Statusausgang (STATUS) gibt detaillierte Fehlermeldungen zurück.
- Die Initialisierung kann bei Bedarf wiederholt werden, um eine neue Datei zu öffnen.

## Zustandsübersicht
- **Inaktiv**: Wartet auf Initialisierung.
- **Bereit**: Datei ist geöffnet und bereit für Schreibvorgänge.
- **Fehler**: Ein Fehler ist aufgetreten (z.B. Dateizugriff verweigert).

## Anwendungsszenarien
- Protokollierung von Sensordaten.
- Speicherung von Prozessdaten für spätere Analysen.
- Export von Daten in ein tabellenbasiertes Format.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren CSV-Writer-Blöcken bietet CSV_WRITER_5 mehr Flexibilität durch die Unterstützung von fünf Datenpunkten und beliebigen Datentypen.
- Andere Blöcke könnten auf bestimmte Datentypen beschränkt sein oder weniger Datenpunkte unterstützen.

## Fazit
Der CSV_WRITER_5 ist ein leistungsfähiger und flexibler Funktionsblock für die Datenerfassung und -protokollierung. Seine Unterstützung für beliebige Datentypen und mehrere Datenpunkte macht ihn ideal für komplexe Anwendungen.

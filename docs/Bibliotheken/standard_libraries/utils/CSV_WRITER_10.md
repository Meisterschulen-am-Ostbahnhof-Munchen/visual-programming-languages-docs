# CSV_WRITER_10

![CSV_WRITER_10](https://github.com/user-attachments/assets/e227277e-11fe-4910-be49-977cea7553d2)

* * * * * * * * * *
## Einleitung
Der CSV_WRITER_10 Funktionsblock dient zum Schreiben von Daten in eine CSV-Datei. Er ermöglicht das Speichern von bis zu 10 verschiedenen Datenwerten in einer strukturierten Textdatei. Der Block ist besonders nützlich für Datenerfassung, Protokollierung und den Austausch von Daten mit anderen Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Funktionsblock und gibt den Dateinamen an (mit QI und FILE_NAME)
- **REQ**: Löst den Schreibvorgang aus (mit QI und SD_1 bis SD_10)

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung (mit QO und STATUS)
- **CNF**: Bestätigt den Schreibvorgang (mit QO und STATUS)

### **Daten-Eingänge**
- **QI**: BOOL - Qualifiziert die Ereigniseingänge
- **FILE_NAME**: STRING - Name der CSV-Datei
- **SD_1 bis SD_10**: ANY - Zu schreibende Datenwerte (beliebiger Typ)

### **Daten-Ausgänge**
- **QO**: BOOL - Qualifiziert die Ereignisausgänge
- **STATUS**: STRING - Statusmeldung des Dateizugriffs

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. **Initialisierung**: Durch INIT mit gültigem FILE_NAME wird die CSV-Datei vorbereitet
2. **Daten schreiben**: Bei REQ werden die aktuellen Werte von SD_1 bis SD_10 als neue Zeile in die Datei geschrieben
3. **Statusrückmeldung**: Jede Aktion generiert eine Statusmeldung (erfolgreich/fehlgeschlagen)

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (ANY) für die zu schreibenden Werte
- Automatische Konvertierung der Daten in Textformat
- Thread-sichere Dateizugriffe
- Maximale Kapazität von 10 Datenwerten pro Zeile

## Zustandsübersicht
1. **Nicht initialisiert**: Vor INIT
2. **Bereit**: Nach erfolgreicher Initialisierung
3. **Fehler**: Bei Dateizugriffsproblemen

## Anwendungsszenarien
- Datenerfassung von Prozesswerten
- Erstellung von Logdateien
- Export von Messdaten für externe Analyse
- Schnittstelle zu Tabellenkalkulationsprogrammen

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren CSV-Writern bietet dieser Block mehr Flexibilität durch 10 Datenkanäle
- Unterstützt im Gegensatz zu fest typisierten Writern beliebige Datentypen
- Bietet detailliertere Statusrückmeldungen als Basisversionen

## Fazit
Der CSV_WRITER_10 ist ein leistungsfähiger Funktionsblock für strukturierte Datenspeicherung, der sich besonders für Anwendungen mit mehreren gleichzeitig zu protokollierenden Werten eignet. Die flexible Typunterstützung und detaillierte Statusrückmeldung machen ihn zu einer robusten Lösung für industrielle Datenerfassungsaufgaben.

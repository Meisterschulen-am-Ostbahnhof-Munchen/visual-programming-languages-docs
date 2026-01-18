# CSV_WRITER_6

```{index} single: CSV_WRITER_6
```

![CSV_WRITER_6](https://github.com/user-attachments/assets/f5ac4221-a93b-49d5-b7b3-280d171a347a)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `CSV_WRITER_6` dient zum Schreiben von Daten in eine CSV-Datei. Er ermöglicht die Speicherung von bis zu sechs verschiedenen Datenwerten in einem komma-separierten Format. Der Block ist besonders nützlich für Datenerfassung und -protokollierung in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisiert den Funktionsblock. Wird mit den Variablen `QI` und `FILE_NAME` ausgelöst.
- `REQ`: Startet den Schreibvorgang. Wird mit den Variablen `QI`, `SD_1` bis `SD_6` ausgelöst.

### **Ereignis-Ausgänge**
- `INITO`: Bestätigt die Initialisierung. Gibt `QO` und `STATUS` zurück.
- `CNF`: Bestätigt den erfolgreichen Schreibvorgang. Gibt `QO` und `STATUS` zurück.

### **Daten-Eingänge**
- `QI` (BOOL): Qualifiziert das Ereignis (z.B., ob der Schreibvorgang aktiviert werden soll).
- `FILE_NAME` (STRING): Name der CSV-Datei, in die geschrieben werden soll.
- `SD_1` bis `SD_6` (ANY): Die zu schreibenden Datenwerte.

### **Daten-Ausgänge**
- `QO` (BOOL): Qualifiziert das Ausgangsereignis (z.B., ob der Vorgang erfolgreich war).
- `STATUS` (STRING): Statusmeldung des Dateizugriffs.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. **Initialisierung**: Durch das `INIT`-Ereignis wird der Funktionsblock mit dem Dateinamen (`FILE_NAME`) initialisiert. Der Status wird über `INITO` zurückgemeldet.
2. **Schreibvorgang**: Das `REQ`-Ereignis löst den Schreibvorgang aus. Die Daten `SD_1` bis `SD_6` werden in die CSV-Datei geschrieben. Der Erfolg wird über `CNF` bestätigt.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (`ANY`) für die zu schreibenden Daten.
- Der Status (`STATUS`) gibt detaillierte Informationen über Fehler oder Erfolg des Dateizugriffs.

## Zustandsübersicht
1. **Initialisierungszustand**: Wartet auf `INIT`-Ereignis.
2. **Bereit-Zustand**: Nach erfolgreicher Initialisierung wartet auf `REQ`-Ereignis.
3. **Schreibzustand**: Verarbeitet die Daten und schreibt sie in die Datei.

## Anwendungsszenarien
- Protokollierung von Sensordaten in Echtzeit.
- Speicherung von Prozessdaten für spätere Analysen.
- Datenerfassung in Test- und Validierungsumgebungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren CSV-Writer-Blöcken bietet `CSV_WRITER_6` die Möglichkeit, bis zu sechs verschiedene Datenwerte gleichzeitig zu speichern.
- Andere Blöcke könnten auf bestimmte Datentypen beschränkt sein, während dieser Block `ANY`-Typen unterstützt.

## Fazit
Der `CSV_WRITER_6` ist ein flexibler und leistungsfähiger Funktionsblock für die Datenspeicherung in CSV-Dateien. Seine Unterstützung für verschiedene Datentypen und die Möglichkeit, mehrere Werte gleichzeitig zu speichern, machen ihn ideal für komplexe Datenerfassungsaufgaben.

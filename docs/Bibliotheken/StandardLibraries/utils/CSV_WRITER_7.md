# CSV_WRITER_7

```{index} single: CSV_WRITER_7
```

![CSV_WRITER_7](https://github.com/user-attachments/assets/7ae443fb-c96d-4894-a2ac-9103f6e76007)

* * * * * * * * * *
## Einleitung
Der CSV_WRITER_7 ist ein Funktionsblock, der Daten in eine CSV-Datei schreibt. Er unterstützt das Schreiben von bis zu sieben verschiedenen Datenfeldern in eine angegebene Datei. Der Funktionsblock ist besonders nützlich für die Protokollierung und Datenspeicherung in Automatisierungsanwendungen.

![CSV_WRITER_7](CSV_WRITER_7.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Funktionsblock. Wird mit den Variablen `QI` (Qualifier Input) und `FILE_NAME` (Name der CSV-Datei) verwendet.
- **REQ**: Startet den Schreibvorgang. Wird mit den Variablen `QI` und den sieben Datenfeldern `SD_1` bis `SD_7` verwendet.

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung. Gibt `QO` (Qualifier Output) und `STATUS` (Status der Initialisierung) zurück.
- **CNF**: Bestätigt den abgeschlossenen Schreibvorgang. Gibt `QO` und `STATUS` zurück.

### **Daten-Eingänge**
- **QI**: Boolescher Qualifier, der angibt, ob der Vorgang ausgeführt werden soll.
- **FILE_NAME**: Name der CSV-Datei, in die geschrieben werden soll.
- **SD_1** bis **SD_7**: Datenfelder, die in die CSV-Datei geschrieben werden. Jedes Feld kann einen beliebigen Datentyp (`ANY`) haben.

### **Daten-Ausgänge**
- **QO**: Boolescher Qualifier, der den Erfolg oder Misserfolg des Vorgangs anzeigt.
- **STATUS**: Zeichenkette, die den Status des Dateizugriffs beschreibt.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
1. **Initialisierung**: Der Funktionsblock wird durch das `INIT`-Ereignis initialisiert. Dabei wird der Dateiname (`FILE_NAME`) übergeben.
2. **Schreibvorgang**: Das `REQ`-Ereignis löst den Schreibvorgang aus. Die Daten `SD_1` bis `SD_7` werden in die angegebene CSV-Datei geschrieben.
3. **Bestätigung**: Nach Abschluss des Vorgangs wird das `CNF`-Ereignis ausgelöst, das den Status des Vorgangs zurückgibt.

## Technische Besonderheiten
- Unterstützt das Schreiben von bis zu sieben verschiedenen Datenfeldern.
- Die Datenfelder können beliebige Datentypen (`ANY`) haben.
- Der Status des Dateizugriffs wird detailliert zurückgegeben.

## Zustandsübersicht
1. **Initialisierungszustand**: Wartet auf das `INIT`-Ereignis.
2. **Bereit**: Nach erfolgreicher Initialisierung wartet der Funktionsblock auf das `REQ`-Ereignis.
3. **Schreibvorgang**: Während des Schreibvorgangs ist der Funktionsblock aktiv.
4. **Abgeschlossen**: Nach Abschluss des Schreibvorgangs wird das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Protokollierung von Prozessdaten in der Industrieautomation.
- Speicherung von Messdaten für spätere Analysen.
- Datenerfassung in Echtzeitsystemen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **CSV_WRITER_5**: Unterstützt nur fünf Datenfelder.
- **FILE_WRITER**: Allgemeinerer Baustein, der nicht speziell für CSV-Dateien optimiert ist.

## Fazit
Der CSV_WRITER_7 ist ein leistungsfähiger Funktionsblock für die Datenspeicherung in CSV-Dateien. Seine Flexibilität bei der Unterstützung verschiedener Datentypen und die detaillierte Statusrückmeldung machen ihn zu einer idealen Wahl für viele Automatisierungsanwendungen.
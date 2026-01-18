# CSV_WRITER_1

```{index} single: CSV_WRITER_1
```

![CSV_WRITER_1](https://github.com/user-attachments/assets/4f7fdcfb-c9cf-4e0a-8347-ccdc85acd150)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `CSV_WRITER_1` dient als Service-Interface zum Schreiben von Daten in eine CSV-Datei. Er ermöglicht die Initialisierung des Schreibvorgangs sowie das kontrollierte Schreiben von Daten in eine Datei mit Statusrückmeldungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Schreibservice. Wird mit den Variablen `QI` (Qualifier) und `FILE_NAME` (Dateiname) ausgelöst.
- **REQ**: Fordert das Schreiben von Daten an. Wird mit den Variablen `QI` und `SD_1` (zu schreibende Daten) ausgelöst.

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung. Liefert `QO` (Qualifier) und `STATUS` (Zustand der Initialisierung).
- **CNF**: Bestätigt den Abschluss des Schreibvorgangs. Liefert `QO` und `STATUS` (Zustand des Schreibvorgangs).

### **Daten-Eingänge**
- **QI**: Boolescher Qualifier für Ereignisse.
- **FILE_NAME**: String, der den Namen der zu schreibenden Datei angibt.
- **SD_1**: Daten vom Typ `ANY`, die in die CSV-Datei geschrieben werden sollen.

### **Daten-Ausgänge**
- **QO**: Boolescher Qualifier für Ausgangsereignisse.
- **STATUS**: String, der den Status des Dateizugriffs zurückgibt.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. **Initialisierung**: Durch das `INIT`-Ereignis wird der Schreibservice mit dem angegebenen Dateinamen (`FILE_NAME`) initialisiert. Der Status wird über `INITO` zurückgemeldet.
2. **Daten schreiben**: Das `REQ`-Ereignis löst den Schreibvorgang der Daten (`SD_1`) aus. Der Erfolg oder Fehler wird über `CNF` und den `STATUS` gemeldet.

## Technische Besonderheiten
- Unterstützt generische Datentypen (`ANY`) für die zu schreibenden Daten.
- Rückmeldung des Status als String für detaillierte Fehleranalyse.

## Zustandsübersicht
- **Initialisierungszustand**: Wird durch `INIT` gesetzt und durch `INITO` bestätigt.
- **Schreibzustand**: Wird durch `REQ` aktiviert und durch `CNF` abgeschlossen.

## Anwendungsszenarien
- Protokollierung von Prozessdaten in CSV-Dateien.
- Export von Messdaten für weitere Analysen.
- Automatisierte Datenspeicherung in industriellen Steuerungssystemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Dateischreib-Blöcken bietet `CSV_WRITER_1` eine detaillierte Statusrückmeldung und Unterstützung für generische Datentypen.
- Andere Blöcke könnten auf bestimmte Datentypen beschränkt sein oder weniger Feedback bieten.

## Fazit
Der `CSV_WRITER_1` ist ein flexibler und zuverlässiger Funktionsblock für das Schreiben von Daten in CSV-Dateien, ideal für Anwendungen, die eine robuste Protokollierung und Datenexportfunktionalität erfordern.

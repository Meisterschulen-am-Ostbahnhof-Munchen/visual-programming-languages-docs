# CSV_WRITER_9

```{index} single: CSV_WRITER_9
```

![CSV_WRITER_9](https://github.com/user-attachments/assets/472722ac-0bc8-40af-9d9b-a31346a5e041)

* * * * * * * * * *
## Einleitung
Der CSV_WRITER_9 ist ein Funktionsblock zur Erstellung von CSV-Dateien. Er ermöglicht das Schreiben von bis zu neun verschiedenen Datenpunkten in eine CSV-Datei. Der Funktionsblock ist Teil des eclipse4diac::utils-Pakets und eignet sich für Anwendungen, bei denen Daten in einem standardisierten Format gespeichert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Funktionsblock und legt den Dateinamen fest. Wird mit `QI` und `FILE_NAME` verwendet.
- **REQ**: Startet den Schreibvorgang in die CSV-Datei. Wird mit `QI` und den Datenpunkten `SD_1` bis `SD_9` verwendet.

### **Ereignis-Ausgänge**
- **INITO**: Bestätigt die Initialisierung und gibt den Status zurück. Wird mit `QO` und `STATUS` verwendet.
- **CNF**: Bestätigt den erfolgreichen oder fehlgeschlagenen Schreibvorgang. Wird mit `QO` und `STATUS` verwendet.

### **Daten-Eingänge**
- **QI**: Boolescher Qualifier für Ereigniseingänge.
- **FILE_NAME**: String, der den Namen der CSV-Datei angibt.
- **SD_1** bis **SD_9**: Datenpunkte vom Typ `ANY`, die in die CSV-Datei geschrieben werden.

### **Daten-Ausgänge**
- **QO**: Boolescher Qualifier für Ereignisausgänge.
- **STATUS**: String, der den Status des Dateizugriffs angibt.

### **Adapter**
Es sind keine Adapter definiert.

## Funktionsweise
1. **Initialisierung**: Der Funktionsblock wird durch das `INIT`-Ereignis initialisiert. Dabei wird der Dateiname über `FILE_NAME` festgelegt.
2. **Schreibvorgang**: Das `REQ`-Ereignis löst den Schreibvorgang aus. Die Datenpunkte `SD_1` bis `SD_9` werden in die CSV-Datei geschrieben.
3. **Bestätigung**: Der Status des Vorgangs wird über `INITO` oder `CNF` zurückgemeldet.

## Technische Besonderheiten
- Unterstützt bis zu neun Datenpunkte (`SD_1` bis `SD_9`) vom Typ `ANY`.
- Der Status des Dateizugriffs wird über den `STATUS`-Ausgang zurückgegeben.
- Der Funktionsblock ist Teil des eclipse4diac::utils-Pakets und unterliegt der Eclipse Public License 2.0.

## Zustandsübersicht
- **Initialisierung**: Erfolgreich (`INITO+`) oder fehlgeschlagen (`INITO-`).
- **Schreibvorgang**: Erfolgreich (`CNF+`) oder fehlgeschlagen (`CNF-`).

## Anwendungsszenarien
- Datenerfassung und -speicherung in industriellen Steuerungssystemen.
- Protokollierung von Prozessdaten in einer standardisierten CSV-Datei.
- Integration in größere Automatisierungslösungen zur Datenverarbeitung.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfacheren CSV-Writer-Funktionsblöcken bietet der CSV_WRITER_9 die Möglichkeit, bis zu neun Datenpunkte gleichzeitig zu schreiben.
- Andere Funktionsblöcke könnten weniger Flexibilität bei den Datentypen bieten, da `ANY` verwendet wird.

## Fazit
Der CSV_WRITER_9 ist ein leistungsfähiger Funktionsblock für die Erstellung von CSV-Dateien in 4diac-IDE. Seine Flexibilität bei der Datenaufnahme und die klare Statusrückmeldung machen ihn zu einer guten Wahl für Anwendungen, die eine strukturierte Datenspeicherung erfordern.

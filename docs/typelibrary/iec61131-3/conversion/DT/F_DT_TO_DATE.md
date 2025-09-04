# F_DT_TO_DATE

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DT_TO_DATE` dient der Konvertierung eines Datums-Zeit-Werts (DT) in ein reines Datum (DATE). Diese Funktionalität ist besonders nützlich, wenn in Steuerungsanwendungen nur das Datum ohne Zeitinformation benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung der Konvertierung. Verbunden mit dem Daten-Eingang `IN`.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Verbunden mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- `IN` (DT): Der Eingang für den zu konvertierenden Datums-Zeit-Wert.

### **Daten-Ausgänge**
- `OUT` (DATE): Der Ausgang für das konvertierte Datum.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang eines `REQ`-Ereignisses wird der DT-Wert am Eingang `IN` in ein DATE konvertiert und am Ausgang `OUT` ausgegeben. Gleichzeitig wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock implementiert die Konvertierung mittels der Funktion `DT_TO_DATE`.
- Die Konvertierung ist atomar und erfolgt in einem einzigen Ausführungsschritt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Jede `REQ`-Anfrage wird unabhängig verarbeitet.

## Anwendungsszenarien
- Extraktion des Datums aus Zeitstempeln in Logging-Systemen
- Vorverarbeitung von Datumsinformationen für Berichte oder Visualisierungen
- Schnittstellen zu Systemen, die nur DATE-Datentypen verarbeiten können

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_DT_TO_TIME` konvertiert dieser Baustein nur den Datumsteil
- Ähnlich zu `F_DT_TO_TOD`, aber mit Fokus auf das Datum statt der Tageszeit

## Fazit
Der `F_DT_TO_DATE` Funktionsblock bietet eine einfache und effiziente Möglichkeit, DT-Werte in reine Datumsangaben umzuwandeln. Seine schlanke Implementierung macht ihn besonders geeignet für Echtzeitanwendungen, wo Performance kritisch ist.
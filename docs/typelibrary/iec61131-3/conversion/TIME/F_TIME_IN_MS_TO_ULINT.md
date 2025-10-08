# F_TIME_IN_MS_TO_ULINT

<img width="1534" height="212" alt="F_TIME_IN_MS_TO_ULINT" src="https://github.com/user-attachments/assets/1e823341-98ae-4b40-bc4f-74b28764bb74" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_MS_TO_ULINT` dient der Konvertierung eines Zeitwerts in Millisekunden (`TIME`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`ULINT`). Dieser Baustein ist besonders nützlich, wenn Zeitwerte für weitere Berechnungen oder Vergleiche in numerischer Form benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert vom Typ `TIME`, der in Millisekunden angegeben ist.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Wert als vorzeichenlosen 64-Bit-Integer (`ULINT`) zurück.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `TIME`-Wert in Millisekunden in einen `ULINT`-Wert umwandelt. Die Konvertierung erfolgt synchron bei Auftreten des `REQ`-Ereignisses. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Baustein nutzt die Funktion `TIME_IN_MS_TO_ULINT` zur Konvertierung.
- Die Implementierung erfolgt in Structured Text (ST).
- Der Baustein ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umrechnung von Zeitwerten für mathematische Operationen.
- Verwendung in Steuerungsalgorithmen, die numerische Zeitwerte benötigen.
- Integration in Systeme, die Zeitstempel als numerische Werte speichern oder verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist dieser Funktionsblock spezialisiert auf die Umwandlung von `TIME` in `ULINT`.
- Andere Bausteine könnten zusätzliche Optionen wie die Konvertierung in andere Datentypen bieten, sind jedoch weniger spezifisch.

## Fazit
Der `F_TIME_IN_MS_TO_ULINT`-Funktionsblock bietet eine effiziente und spezialisierte Lösung für die Konvertierung von Zeitwerten in Millisekunden in vorzeichenlose 64-Bit-Integer. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die numerische Zeitwerte benötigen.

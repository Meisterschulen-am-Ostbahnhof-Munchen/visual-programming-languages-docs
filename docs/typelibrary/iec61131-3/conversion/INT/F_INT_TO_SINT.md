# F_INT_TO_SINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_SINT` dient der Konvertierung eines ganzzahligen Wertes vom Typ `INT` in einen vorzeichenbehafteten 8-Bit-Integer-Wert vom Typ `SINT`. Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `INT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `SINT`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `INT` zu `SINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus innerhalb des Blocks nutzt die Funktion `INT_TO_SINT`, um die Konvertierung durchzuführen. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Es gibt keine zusätzliche Fehlerbehandlung für Überlauf- oder Unterlaufbedingungen. Der Nutzer muss sicherstellen, dass der Eingabewert innerhalb des gültigen Bereichs für `SINT` liegt (-128 bis 127).

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach Auslösen des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Kommunikation zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Reduzierung der Speicherbelegung, wenn ein kleinerer Datentyp ausreichend ist.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_USINT**: Konvertiert `INT` zu `USINT` (vorzeichenloser 8-Bit-Integer).
- **F_INT_TO_DINT**: Konvertiert `INT` zu `DINT` (32-Bit-Integer), was keine Datenreduktion bedeutet.
- **F_INT_TO_REAL**: Konvertiert `INT` zu `REAL` (Gleitkommazahl).

## Fazit
Der `F_INT_TO_SINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `INT`- zu `SINT`-Werten. Er eignet sich besonders für Anwendungen, bei denen Speicherplatz optimiert oder Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen. Nutzer sollten jedoch darauf achten, dass die Eingabewerte innerhalb des gültigen Bereichs für `SINT` liegen, um unerwartete Ergebnisse zu vermeiden.
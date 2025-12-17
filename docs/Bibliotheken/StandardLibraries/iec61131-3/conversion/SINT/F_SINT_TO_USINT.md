# F_SINT_TO_USINT

<img width="1450" height="213" alt="F_SINT_TO_USINT" src="https://github.com/user-attachments/assets/e1008d5b-c1c4-4a42-8bfd-7d328b59eced" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_USINT` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (SINT) in einen vorzeichenlosen 8-Bit-Integer-Wert (USINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Darstellungen für numerische Werte verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (SINT): Der vorzeichenbehaftete 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (USINT): Der resultierende vorzeichenlose 8-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` von SINT zu USINT konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock führt eine direkte Typumwandlung durch, wobei der vorzeichenbehaftete Wert in einen vorzeichenlosen Wert umgewandelt wird.
- Es gibt keine zusätzliche Logik zur Behandlung von Überlaufbedingungen oder ungültigen Eingaben.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch und löst `CNF` aus.
3. Keine weiteren Zustände, da es sich um einen einfachen, nicht-zustandsbehafteten Block handelt.

## Anwendungsszenarien
- Konvertierung von Sensorwerten, die als vorzeichenbehaftete Werte geliefert werden, aber als vorzeichenlose Werte weiterverarbeitet werden sollen.
- Datenaufbereitung für Kommunikationsprotokolle, die vorzeichenlose Werte erfordern.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_UINT**: Konvertiert vorzeichenbehaftete 16-Bit-Integer-Werte in vorzeichenlose 16-Bit-Integer-Werte.
- **F_DINT_TO_UDINT**: Konvertiert vorzeichenbehaftete 32-Bit-Integer-Werte in vorzeichenlose 32-Bit-Integer-Werte.
- **F_SINT_TO_USINT** ist spezifisch für 8-Bit-Werte und daher effizienter für diese Datengröße.

## Fazit
Der `F_SINT_TO_USINT`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung von vorzeichenbehafteten zu vorzeichenlosen 8-Bit-Integer-Werten. Seine Einfachheit und Effizienz machen ihn ideal für Anwendungen, bei denen solche Konvertierungen regelmäßig durchgeführt werden müssen.

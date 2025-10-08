# F_SINT_TO_UINT

<img width="1441" height="213" alt="F_SINT_TO_UINT" src="https://github.com/user-attachments/assets/76c8c3fe-c626-4192-8647-9b5e552de116" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_UINT` dient der Konvertierung eines vorzeichenbehafteten 8-Bit-Integer-Werts (`SINT`) in einen vorzeichenlosen 16-Bit-Integer-Wert (`UINT`). Diese Konvertierung ist insbesondere dann notwendig, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Wert vom Typ `SINT` (vorzeichenbehafteter 8-Bit-Integer).

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten Wert als `UINT` (vorzeichenloser 16-Bit-Integer).

### **Adapter**
- Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Dabei wird der Wert am Eingang `IN` vom Typ `SINT` in einen `UINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die erfolgreiche Konvertierung wird durch das Ereignis `CNF` signalisiert.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `SINT_TO_UINT`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Funktionsblock ist einfach und benötigt keine zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustände. Der Block reagiert direkt auf das `REQ`-Ereignis mit der Ausführung der Konvertierung und der Ausgabe des Ergebnisses.

## Anwendungsszenarien
- Konvertierung von Sensorwerten, die als `SINT` vorliegen, für Systeme, die `UINT` erwarten.
- Datenaufbereitung für Kommunikationsprotokolle, die vorzeichenlose Werte benötigen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_SINT_TO_UINT` spezialisiert und optimiert für die Konvertierung von `SINT` zu `UINT`.
- Andere Blöcke wie `F_INT_TO_UINT` oder `F_DINT_TO_UDINT` bieten ähnliche Funktionalität, jedoch für andere Datentypen.

## Fazit
Der `F_SINT_TO_UINT` Funktionsblock ist ein effizientes Werkzeug für die spezifische Konvertierung von vorzeichenbehafteten zu vorzeichenlosen Integer-Werten. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung in Steuerungs- und Automatisierungssystemen.

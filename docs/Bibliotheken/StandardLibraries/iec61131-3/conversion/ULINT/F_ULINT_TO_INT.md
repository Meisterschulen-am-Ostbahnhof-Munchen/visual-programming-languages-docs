# F_ULINT_TO_INT

```{index} single: F_ULINT_TO_INT
```

<img width="1442" height="214" alt="F_ULINT_TO_INT" src="https://github.com/user-attachments/assets/ef9d1612-2e7c-4316-b959-f3ed32453d61" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_INT` dient der Konvertierung eines 64-Bit vorzeichenlosen Integer-Werts (ULINT) in einen 16-Bit vorzeichenbehafteten Integer-Wert (INT). Diese Konvertierung ist insbesondere dann notwendig, wenn Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen.

![F_ULINT_TO_INT](F_ULINT_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Konvertierung aus. Beim Eintreffen dieses Ereignisses wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Dieses Ereignis signalisiert den Abschluss der Konvertierung. Es wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (ULINT): Hier wird der 64-Bit vorzeichenlose Integer-Wert bereitgestellt, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (INT): Dieser Ausgang liefert den konvertierten 16-Bit vorzeichenbehafteten Integer-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von ULINT zu INT durch, sobald das Ereignis `REQ` eintrifft. Die Konvertierung erfolgt mittels der Funktion `ULINT_TO_INT(IN)`, die den Wert von `IN` in den Zieltyp `INT` umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert wird an `OUT` ausgegeben.

## Technische Besonderheiten
- **Datentyp-Konvertierung**: Die Konvertierung von ULINT (64-Bit) zu INT (16-Bit) kann zu Datenverlust führen, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs von INT liegt (d.h., größer als 32767 oder kleiner als -32768 ist).
- **Einfache Implementierung**: Der Funktionsblock ist als SimpleFB implementiert und verwendet einen einfachen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Bei Eintreffen von `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach der Konvertierung wird `CNF` ausgelöst, und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenkompatibilität**: Wird verwendet, wenn Systeme mit unterschiedlichen Datentypen kommunizieren müssen.
- **Datenreduktion**: Kann eingesetzt werden, um Speicherplatz zu sparen, wenn die höhere Präzision von ULINT nicht benötigt wird.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_ULINT_TO_DINT**: Konvertiert ULINT zu DINT (32-Bit), bietet einen größeren Wertebereich als INT.
- **F_ULINT_TO_LINT**: Konvertiert ULINT zu LINT (64-Bit), behält die volle Präzision bei.

## Fazit
Der Funktionsblock `F_ULINT_TO_INT` ist ein einfaches, aber effektives Werkzeug zur Konvertierung von 64-Bit vorzeichenlosen Integer-Werten in 16-Bit vorzeichenbehaftete Integer-Werte. Er ist besonders nützlich in Szenarien, wo Speichereffizienz oder Kompatibilität mit älteren Systemen erforderlich ist. Beachten Sie jedoch die möglichen Datenverluste bei der Konvertierung großer Werte.
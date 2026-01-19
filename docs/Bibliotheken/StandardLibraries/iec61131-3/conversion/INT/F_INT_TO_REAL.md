# F_INT_TO_REAL

```{index} single: F_INT_TO_REAL
```

<img width="1423" height="216" alt="F_INT_TO_REAL" src="https://github.com/user-attachments/assets/6294145e-fd3f-497a-ada1-e0cf83c00ba8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_REAL` dient der Konvertierung eines ganzzahligen Wertes (`INT`) in eine Fließkommazahl (`REAL`). Diese Funktionalität ist besonders nützlich, wenn in Steuerungsanwendungen Daten zwischen verschiedenen numerischen Darstellungen umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Ausführung der Konvertierung aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert den Abschluss der Konvertierung. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`INT`): Der ganzzahlige Wert, der in eine Fließkommazahl umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (`REAL`): Der resultierende Fließkommawert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Wert des Daten-Eingangs `IN` gelesen und in den Typ `REAL` konvertiert. Das Ergebnis wird am Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Operation.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder Einstellungen.
- Der Funktionsblock ist einfach und effizient implementiert, was eine schnelle Ausführung gewährleistet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Sensorwerten (z.B. als `INT` erfasst) in Fließkommazahlen für weitere Berechnungen.
- Integration in Steuerungslogiken, die gemischte Datentypen verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_INT_TO_REAL` spezialisiert und daher effizienter für diesen spezifischen Anwendungsfall.
- Andere Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht erforderlich ist.

## Fazit
Der `F_INT_TO_REAL` Funktionsblock ist ein einfaches und effektives Werkzeug zur Konvertierung von ganzzahligen Werten in Fließkommazahlen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und zuverlässige Typumwandlung benötigt wird.
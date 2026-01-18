# F_DINT_TO_INT

```{index} single: F_DINT_TO_INT
```

<img width="1425" height="212" alt="F_DINT_TO_INT" src="https://github.com/user-attachments/assets/5147e94b-3493-443d-9b11-48a63ecf9d50" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_INT` dient der Konvertierung eines 32-Bit-DINT-Wertes in einen 16-Bit-INT-Wert. Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (DINT): Der 32-Bit-DINT-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (INT): Der resultierende 16-Bit-INT-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von einem 32-Bit-DINT-Wert (`IN`) in einen 16-Bit-INT-Wert (`OUT`) durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt durch die Funktion `DINT_TO_INT`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche DINT-Wert außerhalb des darstellbaren Bereichs eines INT-Wertes liegt (-32768 bis 32767).
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen mit unterschiedlicher Wortbreite.
- Integration von Systemen, die unterschiedliche Datentypen verwenden.
- Reduzierung der Speicherbelegung, wenn die höhere Präzision eines DINT nicht benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_DINT_TO_INT` spezialisiert auf die Konvertierung von DINT zu INT und bietet daher eine einfache und direkte Lösung für diesen spezifischen Anwendungsfall.
- Andere Konvertierungsbausteine, wie `F_INT_TO_DINT`, führen entgegengesetzte Konvertierungen durch.

## Fazit
Der Funktionsblock `F_DINT_TO_INT` ist ein effizientes Werkzeug für die Konvertierung von 32-Bit-DINT-Werten in 16-Bit-INT-Werte. Seine einfache und spezialisierte Funktionsweise macht ihn ideal für Anwendungen, in denen solche Konvertierungen regelmäßig erforderlich sind. Bei der Verwendung ist jedoch auf den möglichen Datenverlust bei großen Werten zu achten.

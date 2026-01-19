# F_BOOL_TO_SINT

```{index} single: F_BOOL_TO_SINT
```

<img width="1231" height="184" alt="F_BOOL_TO_SINT" src="https://github.com/user-attachments/assets/f88ef12a-b389-4669-b68c-8527d08d1d6e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_SINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen vorzeichenbehafteten 8-Bit-Integer (`SINT`). Diese Konvertierung ist nützlich, wenn boolesche Werte in Berechnungen oder Steuerungen verwendet werden sollen, die ganzzahlige Werte erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, wird der boolesche Wert am Daten-Eingang `IN` in einen `SINT`-Wert konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der boolesche Wert (`BOOL`), der in einen `SINT`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Wert (`SINT`). Der Ausgangswert ist `1`, wenn der Eingang `IN` `TRUE` ist, andernfalls `0`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock konvertiert den booleschen Eingangswert `IN` in einen `SINT`-Wert. Die Konvertierung erfolgt nach folgender Regel:
- `TRUE` wird zu `1` konvertiert.
- `FALSE` wird zu `0` konvertiert.

Die Konvertierung wird durch das Ereignis `REQ` ausgelöst. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst und der konvertierte Wert am Ausgang `OUT` ausgegeben.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus (`SimpleFB`), der direkt die Konvertierung durchführt.
- Die Konvertierung erfolgt ohne Verzögerung, sobald das Ereignis `REQ` eintrifft.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von booleschen Signalen in numerische Werte für mathematische Operationen.
- Integration von booleschen Steuerungssignalen in Systeme, die ganzzahlige Werte erwarten.

## Vergleich mit ähnlichen Bausteinen
- **F_BOOL_TO_INT**: Konvertiert `BOOL` in einen 16-Bit-Integer (`INT`). Dieser Baustein ist ähnlich, aber der Ausgangswert hat eine größere Bitbreite.
- **F_BOOL_TO_USINT**: Konvertiert `BOOL` in einen vorzeichenlosen 8-Bit-Integer (`USINT`). Der Unterschied liegt in der Interpretation des Ausgangswertes (vorzeichenbehaftet vs. vorzeichenlos).

## Fazit
Der Funktionsblock `F_BOOL_TO_SINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von booleschen Werten in vorzeichenbehaftete 8-Bit-Integer. Er ist besonders nützlich in Steuerungssystemen, wo boolesche Signale in numerische Werte umgewandelt werden müssen.
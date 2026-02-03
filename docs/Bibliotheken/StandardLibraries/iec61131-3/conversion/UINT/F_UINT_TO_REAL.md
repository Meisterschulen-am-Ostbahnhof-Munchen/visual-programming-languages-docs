# F_UINT_TO_REAL

```{index} single: F_UINT_TO_REAL
```

<img width="1441" height="216" alt="F_UINT_TO_REAL" src="https://github.com/user-attachments/assets/4cb48960-25c6-479d-9c4c-636b5a546a0c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_REAL` dient der Konvertierung eines vorzeichenlosen Integer-Werts (`UINT`) in eine Fließkommazahl (`REAL`). Diese Funktionalität ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

![F_UINT_TO_REAL](F_UINT_TO_REAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `UINT`, der in einen `REAL`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `REAL`, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus innerhalb des Blocks weist den Wert von `IN` direkt `OUT` zu, wobei eine implizite Typumwandlung von `UINT` zu `REAL` stattfindet. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Einstellungen.
- Der Block ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Umwandlung von Sensorwerten, die als `UINT` vorliegen, in `REAL` für weitere Berechnungen.
- Kompatibilität zwischen Systemen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu komplexeren Konvertierungsblöcken bietet `F_UINT_TO_REAL` eine einfache, direkte Umwandlung ohne zusätzliche Funktionalität.
- Ähnliche Blöcke könnten zusätzliche Features wie Skalierung oder Bereichsprüfungen bieten, was hier nicht der Fall ist.



## Zugehörige Übungen

* [Uebung_072c](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_072c.md)

## Fazit
Der `F_UINT_TO_REAL`-Funktionsblock ist ein einfaches und effizientes Werkzeug für die Typumwandlung von `UINT` zu `REAL`. Seine Stärke liegt in der Einfachheit und direkten Anwendbarkeit, ohne Overhead durch zusätzliche Funktionen.
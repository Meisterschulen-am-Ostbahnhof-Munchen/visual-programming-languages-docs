# F_UINT_TO_BYTE

```{index} single: F_UINT_TO_BYTE
```

<img width="1438" height="216" alt="F_UINT_TO_BYTE" src="https://github.com/user-attachments/assets/a8cfd8ac-c7a0-4336-80db-1efc0682ced0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_BYTE` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in einen 8-Bit-Byte-Wert (BYTE). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_UINT_TO_BYTE](F_UINT_TO_BYTE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang für den UINT-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten BYTE-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald ein Ereignis am Eingang `REQ` eintrifft. Dabei wird der Wert am Eingang `IN` vom Typ UINT in einen BYTE-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung erfolgt mittels der Funktion `UINT_TO_BYTE`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Kommunikationsprotokollen, wo BYTE-Daten erwartet werden.
- Datenreduktion, wenn nur die unteren 8 Bit eines UINT-Werts relevant sind.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UINT_TO_BYTE` spezialisiert auf die Umwandlung von UINT zu BYTE.
- Andere Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht der Fall ist.




## 🛠️ Zugehörige Übungen

* [Uebung_12x_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_12x_sub.md)

## Fazit
Der `F_UINT_TO_BYTE` Funktionsblock ist ein einfacher und effizienter Baustein für die spezifische Konvertierung von UINT zu BYTE. Er eignet sich besonders für Anwendungen, wo eine schnelle und direkte Typumwandlung benötigt wird.
# F_DWORD_TO_UDINT

```{index} single: F_DWORD_TO_UDINT
```

<img width="1253" height="181" alt="F_DWORD_TO_UDINT" src="https://github.com/user-attachments/assets/0b023d3e-49d2-41d3-a6b3-db4d5f1970f8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_UDINT` dient der Konvertierung eines `DWORD`-Werts in einen `UDINT`-Wert. Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und ermöglicht eine einfache und effiziente Typumwandlung.

![F_DWORD_TO_UDINT](F_DWORD_TO_UDINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `DWORD`, der den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UDINT`, der das Ergebnis der Konvertierung liefert.

### **Adapter**
- Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DWORD` zu `UDINT` durch, sobald das `REQ`-Ereignis ausgelöst wird. Die Umwandlung erfolgt mithilfe der integrierten Funktion `DWORD_TO_UDINT`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus (`REQ`), der die Konvertierung durchführt.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, bei denen `DWORD`-Werte in `UDINT`-Werte umgewandelt werden müssen.
- Integration in größere Steuerungssysteme, die eine Typkompatibilität zwischen verschiedenen Datenformaten erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_UINT` oder `F_BYTE_TO_USINT` führen ähnliche Typumwandlungen durch, jedoch für andere Datentypen.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_DWORD_TO_UDINT` spezialisiert und optimiert für die Umwandlung von `DWORD` zu `UDINT`.




## 🛠️ Zugehörige Übungen

* [Uebung_011](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_011.md)
* [Uebung_011a2](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_011a2.md)
* [Uebung_012](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_012.md)
* [Uebung_012a_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_012a_sub.md)
* [Uebung_012b](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_012b.md)
* [Uebung_012c](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_012c.md)
* [Uebung_020c2_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020c2_sub.md)
* [Uebung_028](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_028.md)
* [Uebung_034](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034.md)
* [Uebung_034a1_Q1](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034a1_Q1.md)
* [Uebung_034a1_Q2](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034a1_Q2.md)
* [Uebung_034a1_Q4](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034a1_Q4.md)
* [Uebung_103](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_151](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_151.md)
* [Uebung_151_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_151_AX.md)
* [Uebung_152](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_153.md)

## Fazit
Der `F_DWORD_TO_UDINT`-Funktionsblock bietet eine einfache und effiziente Lösung für die Konvertierung von `DWORD`-Werten in `UDINT`-Werte. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem zuverlässigen Baustein in Steuerungsanwendungen.
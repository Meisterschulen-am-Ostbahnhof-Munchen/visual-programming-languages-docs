# SPLIT_BYTE_INTO_BOOLS

```{index} single: SPLIT_BYTE_INTO_BOOLS
```

![SPLIT_BYTE_INTO_BOOLS](https://github.com/user-attachments/assets/666a1be8-3ac9-4da7-b5ab-b11513e98c9c)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_BYTE_INTO_BOOLS` dient dazu, ein Byte in seine einzelnen Bits zu zerlegen und diese als separate BOOL-Werte auszugeben. Dies ist besonders nützlich, wenn mit Hardware gearbeitet wird, die einzelne Bits eines Bytes auswertet oder setzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird dieser Event ausgelöst, werden die Bits des aktuellen Byte-Wertes an `IN` ausgewertet.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung des Funktionsblocks. Dieser Event wird ausgelöst, nachdem alle Bits ausgewertet und an die entsprechenden Ausgänge weitergeleitet wurden.

### **Daten-Eingänge**
- **IN**: Das Byte, das in seine einzelnen Bits zerlegt werden soll. Der Datentyp ist `BYTE`.

### **Daten-Ausgänge**
- **BIT_00** bis **BIT_07**: Die einzelnen Bits des Bytes, wobei `BIT_00` das niederwertigste Bit (LSB) und `BIT_07` das höchstwertige Bit (MSB) repräsentiert. Der Datentyp aller Ausgänge ist `BOOL`.

### **Adapter**
Der Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock zerlegt das eingehende Byte `IN` in seine 8 Bits und weist diese den entsprechenden BOOL-Ausgängen zu. Jedes Bit wird direkt aus dem Byte extrahiert und als separater BOOL-Wert ausgegeben. Die Auswertung erfolgt bei jedem `REQ`-Event.

## Technische Besonderheiten
- Die Bit-Extraktion erfolgt direkt über die Zugriffsnotation `IN.%X0` bis `IN.%X7`, was eine effiziente und schnelle Verarbeitung ermöglicht.
- Der Funktionsblock ist in der Programmiersprache ST (Structured Text) implementiert.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt direkt bei Empfang des `REQ`-Events, und die Ergebnisse werden sofort über den `CNF`-Event und die Datenausgänge bereitgestellt.

## Anwendungsszenarien
- **Hardware-Steuerung**: Bei der Ansteuerung von digitalen Ein- und Ausgängen, die als Byte organisiert sind, können einzelne Bits einfach ausgewertet werden.
- **Datenverarbeitung**: Bei der Verarbeitung von Byte-Daten, bei denen einzelne Bits eine spezifische Bedeutung haben (z.B. Statusflags).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulationsfunktionen bietet dieser Baustein eine spezialisierte und einfache Lösung für die Zerlegung eines Bytes in Bits.
- Andere Bausteine könnten komplexere Operationen wie Bit-Shifts oder Masken erfordern, während dieser Baustein die direkte Extraktion der Bits ermöglicht.






## 🛠️ Zugehörige Übungen

* [Uebung_053](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_053.md)

## Fazit
Der `SPLIT_BYTE_INTO_BOOLS`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Zerlegung eines Bytes in seine einzelnen Bits. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und direkte Bit-Extraktion benötigt wird. Durch seine klare Schnittstelle und einfache Funktionsweise ist er leicht in bestehende Systeme integrierbar.
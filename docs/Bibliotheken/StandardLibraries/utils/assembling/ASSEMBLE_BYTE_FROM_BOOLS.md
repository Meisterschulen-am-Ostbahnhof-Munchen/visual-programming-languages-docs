# ASSEMBLE_BYTE_FROM_BOOLS

```{index} single: ASSEMBLE_BYTE_FROM_BOOLS
```

![ASSEMBLE_BYTE_FROM_BOOLS](https://github.com/user-attachments/assets/4a70532a-aa28-4489-a8b6-5cf357a41460)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_BYTE_FROM_BOOLS` kombiniert 8 boolesche Eingangswerte zu einem Byte. Jeder boolesche Eingang repräsentiert dabei ein Bit des resultierenden Bytes. Dieser Baustein ist besonders nützlich, wenn einzelne boolesche Signale zu einem kompakten Byte-Wert zusammengefasst werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung der booleschen Eingänge und erzeugt das resultierende Byte.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Zusammenfassung der booleschen Werte zu einem Byte.

### **Daten-Eingänge**
- `BIT_00` bis `BIT_07`: Acht boolesche Eingänge, die jeweils einem Bit des resultierenden Bytes entsprechen.

### **Daten-Ausgänge**
- `BYTE`: Das zusammengesetzte Byte, das aus den 8 booleschen Eingängen generiert wird.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock setzt die 8 booleschen Eingänge (`BIT_00` bis `BIT_07`) zu einem Byte zusammen. Jeder boolesche Wert wird auf das entsprechende Bit des Bytes abgebildet:
- `BIT_00` entspricht Bit 0 (LSB)
- `BIT_01` entspricht Bit 1
- ...
- `BIT_07` entspricht Bit 7 (MSB)

Bei Auslösung des Ereignisses `REQ` werden die aktuellen Werte der booleschen Eingänge gelesen und zu einem Byte kombiniert. Das Ergebnis wird am Datenausgang ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Verarbeitung.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Die Bit-Zuordnung erfolgt direkt über die Zuweisung der booleschen Werte zu den entsprechenden Bits des Bytes.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Verarbeitungszustand**: Liest die booleschen Eingänge und setzt das Byte zusammen.
3. **Bestätigungszustand**: Gibt das resultierende Byte aus und signalisiert `CNF`.

## Anwendungsszenarien
- Zusammenfassen von 8 einzelnen Schalterstellungen zu einem Byte für die Kommunikation mit anderen Systemen.
- Komprimierung von booleschen Statusinformationen für effizientere Datenübertragung.
- Verwendung in Steuerungssystemen, wo mehrere boolesche Signale als ein Byte verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu manuellen Bit-Operationen in ST oder anderen Sprachen bietet dieser Baustein eine vordefinierte und wartungsfreundliche Lösung.
- Ähnliche Bausteine könnten weniger Eingänge haben oder zusätzliche Features wie invertierte Logik bieten, was hier nicht der Fall ist.





## Zugehörige Übungen

* [Uebung_035a1b_AX](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_035a1b_AX.md)
* [Uebung_053](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_053.md)

## Fazit
Der `ASSEMBLE_BYTE_FROM_BOOLS`-Funktionsblock ist eine einfache und effiziente Lösung, um 8 boolesche Werte zu einem Byte zu kombinieren. Durch seine klare Schnittstelle und direkte Implementierung eignet er sich ideal für Anwendungen, bei denen boolesche Signale kompakt verarbeitet werden müssen.
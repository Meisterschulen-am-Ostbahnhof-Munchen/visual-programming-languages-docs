# ASSEMBLE_LWORD_FROM_QUARTERS

![ASSEMBLE_LWORD_FROM_QUARTERS](https://github.com/user-attachments/assets/c6bc85a7-e9e1-4464-b725-6d168027e7af)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_LWORD_FROM_QUARTERS` kombiniert 32 Byte-Werte (QUARTER_BYTE_00 bis QUARTER_BYTE_31) zu einem 64-Bit LWORD-Wert. Dies ist besonders nützlich, wenn Daten in kleineren Einheiten vorliegen und zu einem größeren Datenwort zusammengesetzt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung und kombiniert die 32 Byte-Eingänge zu einem LWORD.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Zusammenführung der Bytes zu einem LWORD.

### **Daten-Eingänge**
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_31` (32 Eingänge vom Typ `BYTE`): Die einzelnen Byte-Werte, die zu einem LWORD kombiniert werden.

### **Daten-Ausgänge**
- (Unbenannt, Typ `LWORD`): Der kombinierte 64-Bit-Wert, der aus den 32 Byte-Eingängen zusammengesetzt wird.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nimmt die 32 Byte-Eingänge entgegen und kombiniert sie zu einem 64-Bit LWORD. Dabei wird jeder Byte-Wert an eine bestimmte Position im LWORD verschoben (mittels `SHL`-Operation) und dann mit dem aktuellen LWORD-Wert logisch verknüpft (`OR`-Operation). Die Verschiebung erfolgt gemäß vordefinierter Konstanten (`quarterconst::SHIFT_QUARTER_XX`), die die genaue Position jedes Bytes im LWORD festlegen.

## Technische Besonderheiten
- Verwendet bitweise Operationen (`SHL`, `OR`) für die effiziente Kombination der Bytes.
- Die Reihenfolge der Kombination ist von `QUARTER_BYTE_31` (höchstwertiges Byte) bis `QUARTER_BYTE_00` (niederwertigstes Byte).
- Der Funktionsblock ist in ST (Structured Text) implementiert und nutzt eine Bibliothek (`quarterconst`) für die Verschiebungskonstanten.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Verarbeitung erfolgt direkt bei Empfang des `REQ`-Ereignisses, und das Ergebnis wird sofort über `CNF` ausgegeben.

## Anwendungsszenarien
- Zusammensetzen von Daten, die in kleineren Einheiten (Bytes) übertragen oder gespeichert wurden.
- Verarbeitung von Protokollen oder Datenformaten, die große Werte in segmentierter Form übermitteln.
- Einsatz in Systemen, die mit 64-Bit-Daten arbeiten, aber nur 8-Bit-Schnittstellen zur Verfügung haben.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten z. B. `ASSEMBLE_DWORD_FROM_BYTES` sein, die jedoch nur 32-Bit-Werte kombinieren.
- Im Gegensatz zu manuellen Implementierungen bietet dieser Baustein eine standardisierte und optimierte Lösung für die Kombination von 32 Bytes zu einem LWORD.

## Fazit
Der `ASSEMBLE_LWORD_FROM_QUARTERS`-Funktionsblock bietet eine effiziente und zuverlässige Methode, um 32 Byte-Werte zu einem 64-Bit LWORD zu kombinieren. Durch die Verwendung von bitweisen Operationen und vordefinierten Verschiebungskonstanten ist die Lösung performant und leicht in bestehende Systeme integrierbar. Ideal für Anwendungen, die mit großen Datenwerten in segmentierter Form arbeiten.

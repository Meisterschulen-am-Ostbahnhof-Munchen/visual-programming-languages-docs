# SPLIT_WORD_INTO_BOOLS

```{index} single: SPLIT_WORD_INTO_BOOLS
```

![SPLIT_WORD_INTO_BOOLS](https://github.com/user-attachments/assets/dc1abe89-3f91-409f-815b-858dcd48d035)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_WORD_INTO_BOOLS` dient dazu, ein 16-Bit-Wort in seine einzelnen Bits zu zerlegen. Jedes Bit des Eingangswortes wird auf einen separaten BOOL-Ausgang abgebildet. Dies ist besonders nützlich, wenn einzelne Bits eines Wortes weiterverarbeitet oder überwacht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Zerlegung des Eingangswortes. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Bestätigt die erfolgreiche Zerlegung des Wortes. Wird mit allen 16 BOOL-Ausgängen verknüpft.

### **Daten-Eingänge**
- `IN` (WORD): Das 16-Bit-Wort, das in einzelne Bits zerlegt werden soll.

### **Daten-Ausgänge**
- `BIT_00` bis `BIT_15` (BOOL): Die einzelnen Bits des Eingangswortes, wobei `BIT_00` das niederwertigste Bit (LSB) und `BIT_15` das höchstwertige Bit (MSB) darstellt.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock zerlegt das Eingangswort `IN` in seine 16 einzelnen Bits und weist diese den entsprechenden BOOL-Ausgängen zu. Die Zuweisung erfolgt direkt über die Bit-Adressierung des WORD-Datentyps (z.B. `IN.%X0` für das erste Bit). Bei Auslösung des `REQ`-Ereignisses werden alle Bits extrahiert und das `CNF`-Ereignis bestätigt die erfolgreiche Ausführung.

## Technische Besonderheiten
- Die Bit-Extraktion erfolgt direkt über die Hardware-nahe Bit-Adressierung, was eine effiziente Verarbeitung ermöglicht.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
- **Idle**: Wartet auf das `REQ`-Ereignis.
- **Processing**: Zerlegt das Wort und aktualisiert die Ausgänge.
- **Complete`: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Verarbeitung von digitalen Eingangssignalen, die als WORD übertragen werden.
- Dekodierung von Status- oder Steuerworten in Steuerungssystemen.
- Schnittstelle zwischen Wort-basierten und Bit-basierten Systemkomponenten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulationsfunktionen bietet dieser Baustein eine spezialisierte und einfache Schnittstelle für die Zerlegung von Wörtern.
- Ähnliche Bausteine könnten eine flexible Anzahl von Bits unterstützen, was hier nicht der Fall ist.

## Fazit
Der `SPLIT_WORD_INTO_BOOLS`-Funktionsblock ist ein einfacher und effizienter Baustein für die Zerlegung von 16-Bit-Wörtern in einzelne Bits. Er eignet sich besonders für Anwendungen, bei denen eine klare und direkte Bit-Extraktion benötigt wird.
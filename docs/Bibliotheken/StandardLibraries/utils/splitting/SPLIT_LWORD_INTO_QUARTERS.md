# SPLIT_LWORD_INTO_QUARTERS

```{index} single: SPLIT_LWORD_INTO_QUARTERS
```

![SPLIT_LWORD_INTO_QUARTERS](https://github.com/user-attachments/assets/673b8e11-a630-41ed-ab74-5c16e3fe349b)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_LWORD_INTO_QUARTERS` dient zur Extraktion der 32 Quarter Bytes (je 8 Bit) aus einem LWORD (64 Bit). Dies ermöglicht die gezielte Verarbeitung einzelner Byte-Segmente innerhalb eines langen Wortes.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung des Eingangswertes `IN`.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die erfolgreiche Verarbeitung und liefert alle 32 Quarter Bytes.

### **Daten-Eingänge**
- `IN` (LWORD): Das 64-Bit-Eingangswort, das in Quarter Bytes aufgeteilt werden soll.

### **Daten-Ausgänge**
32 Ausgänge vom Typ BYTE:
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_31`: Die extrahierten 8-Bit-Segmente des Eingangswortes.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt Bitoperationen (AND und Rechts-Shift) in Kombination mit Konstanten (`quarterconst::LWORD_QUARTER_xx` und `quarterconst::SHIFT_QUARTER_xx`), um jedes der 32 Quarter Bytes aus dem Eingangs-LWORD zu isolieren. Jedes Quarter Byte wird anschließend in einen separaten BYTE-Ausgang geschrieben.

## Technische Besonderheiten
- Verwendet spezielle Bitmasken und Verschiebungskonstanten für präzise Extraktion
- Arbeitet mit dem größten IEC-Datentyp LWORD (64 Bit)
- Liefert alle 32 Quarter Bytes parallel in einem Durchlauf

## Zustandsübersicht
1. **Idle**: Wartet auf REQ-Ereignis
2. **Processing**: Extrahiert alle Quarter Bytes
3. **Output**: Trigger CNF-Ereignis mit allen Ausgangswerten

## Anwendungsszenarien
- Verarbeitung von langen Datenwörtern in Kommunikationsprotokollen
- Extraktion einzelner Parameter aus gepackten Datenstrukturen
- Bitweise Analyse von Sensor- oder Steuerdaten

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen BYTE-Extraktionsblöcken kann dieser FB alle 32 Segmente gleichzeitig verarbeiten
- Effizienter als mehrere hintereinandergeschaltete Extraktionsblöcke
- Spezialisiert auf die Verarbeitung von LWORD-Datentypen

## Fazit
Der `SPLIT_LWORD_INTO_QUARTERS`-Funktionsblock bietet eine hochoptimierte Lösung für die Aufteilung von 64-Bit-Wörtern in ihre einzelnen Byte-Komponenten. Durch die parallele Verarbeitung aller Segmente eignet er sich besonders für Anwendungen, die eine effiziente Verarbeitung großer Datenwörter erfordern.

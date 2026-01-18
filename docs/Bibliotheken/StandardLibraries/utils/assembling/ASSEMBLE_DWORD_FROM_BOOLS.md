# ASSEMBLE_DWORD_FROM_BOOLS

```{index} single: ASSEMBLE_DWORD_FROM_BOOLS
```

![ASSEMBLE_DWORD_FROM_BOOLS](https://github.com/user-attachments/assets/2c59a6bc-c069-4740-8371-474846a393ee)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_DWORD_FROM_BOOLS` kombiniert 32 einzelne BOOL-Werte zu einem einzigen DWORD-Wert. Dies ist besonders nützlich, wenn mehrere binäre Zustände in einer kompakten Form verarbeitet oder übertragen werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Auslöseereignis, das die Verarbeitung der Eingangsdaten startet. Wird mit allen 32 BIT-Eingängen verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigungsereignis, das nach erfolgreicher Kombination der BOOL-Werte zu einem DWORD ausgegeben wird.

### **Daten-Eingänge**
32 BOOL-Eingänge (`BIT_00` bis `BIT_31`), die jeweils ein Bit im resultierenden DWORD repräsentieren:
- `BIT_00`: Bit 0 (niederwertigstes Bit)
- `BIT_01`: Bit 1
- ...
- `BIT_31`: Bit 31 (höchstwertigstes Bit)

### **Daten-Ausgänge**
- `OUT`: DWORD, das aus den 32 Eingangs-BOOLs zusammengesetzt wird.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock setzt bei Auslösung des `REQ`-Ereignisses die 32 BOOL-Eingänge zu einem DWORD zusammen. Jeder BOOL-Eingang entspricht einem Bit im DWORD:
- `BIT_00` wird zu Bit 0 (LSB)
- `BIT_31` wird zu Bit 31 (MSB)

Nach der erfolgreichen Kombination wird das `CNF`-Ereignis ausgegeben.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Die Bit-Zuordnung erfolgt direkt über die Zuweisung der BOOL-Werte zu den entsprechenden Bit-Positionen des DWORD.
- Keine Pufferung oder Zustandsspeicherung: Die Verarbeitung erfolgt bei jedem `REQ`-Ereignis neu.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Verarbeitung erfolgt rein ereignisgesteuert:
1. `REQ` empfangen → Verarbeitung starten.
2. BOOL-Werte lesen und zu DWORD kombinieren.
3. `CNF` ausgeben.

## Anwendungsszenarien
- Komprimierung mehrerer binärer Signale für die Übertragung über Kommunikationsprotokolle.
- Speicherung mehrerer Schaltzustände in einem einzigen Register.
- Effiziente Verarbeitung von Bitmasken in Steuerungsalgorithmen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu manuellen Bit-Operationen in ST oder anderen FB-Typen bietet dieser Baustein eine vordefinierte, fehlerfreie Lösung für die Kombination von BOOLs zu einem DWORD.
- Ähnliche Bausteine könnten weniger Bits verarbeiten oder zusätzliche Funktionen wie Bit-Verschiebungen bieten.

## Fazit
Der `ASSEMBLE_DWORD_FROM_BOOLS`-Funktionsblock ist eine effiziente und zuverlässige Lösung, um 32 binäre Eingänge in einem einzigen DWORD zu kombinieren. Durch seine einfache und klare Schnittstelle eignet er sich ideal für Anwendungen, die kompakte Darstellungen mehrerer binärer Zustände erfordern.

# SPLIT_DWORD_INTO_QUARTERS

```{index} single: SPLIT_DWORD_INTO_QUARTERS
```

![SPLIT_DWORD_INTO_QUARTERS](https://github.com/user-attachments/assets/140e8baa-2ae9-4977-91b3-1a7b608f9f12)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_DWORD_INTO_QUARTERS` dient dazu, ein 32-Bit-Wort (DWORD) in seine 16 einzelnen 4-Bit-Blöcke (QUARTER_BYTE) aufzuteilen. Jeder dieser 4-Bit-Blöcke wird als separate BYTE-Variable ausgegeben. Der Block ist besonders nützlich, wenn einzelne Teile eines DWORDs separat verarbeitet oder analysiert werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung des Eingangs-DWORD.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Verarbeitung und die Bereitstellung aller 16 QUARTER_BYTE-Ausgänge.

### **Daten-Eingänge**
- `IN`: Das Eingangs-DWORD, das in 16 QUARTER_BYTE aufgeteilt wird.

### **Daten-Ausgänge**
- `QUARTER_BYTE_00` bis `QUARTER_BYTE_15`: Die 16 einzelnen 4-Bit-Blöcke des Eingangs-DWORDs, jeweils als BYTE ausgegeben.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die 16 QUARTER_BYTE aus dem Eingangs-DWORD durch bitweise Operationen. Jeder QUARTER_BYTE wird durch eine Kombination aus bitweiser UND-Verknüpfung und Rechtsverschiebung isoliert und anschließend in einen BYTE-Wert konvertiert. Die verwendeten Konstanten (`DWORD_QUARTER_XX` und `SHIFT_QUARTER_XX`) sind in einer separaten Konstante-Datei (`quarterconst`) definiert.

## Technische Besonderheiten
- Der Block verwendet bitweise Operationen, um die einzelnen 4-Bit-Blöcke zu isolieren.
- Die Ausgabewerte sind als BYTE definiert, obwohl sie nur 4 Bit enthalten. Die oberen 4 Bit jedes BYTE sind daher immer 0.
- Die Verwendung von vordefinierten Konstanten (`quarterconst`) ermöglicht eine flexible Anpassung der Bitpositionen.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Verarbeitung erfolgt bei jedem `REQ`-Ereignis neu.

## Anwendungsszenarien
- Verarbeitung von Datenpaketen, bei denen einzelne 4-Bit-Blöcke eines DWORDs ausgewertet werden müssen.
- Dekodierung von Status- oder Steuerinformationen, die in einem DWORD kodiert sind.
- Aufteilung von Daten für die weitere Verarbeitung in nachgelagerten Systemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bitmanipulations-Blöcken bietet `SPLIT_DWORD_INTO_QUARTERS` eine spezialisierte Funktionalität für die Aufteilung eines DWORDs in 4-Bit-Blöcke.
- Andere Blöcke wie `SPLIT_DWORD_INTO_BYTES` teilen ein DWORD in 8-Bit-Blöcke auf, während dieser Block eine feinere Granularität bietet.

## Fazit
Der `SPLIT_DWORD_INTO_QUARTERS`-Funktionsblock ist ein spezialisiertes Werkzeug für die Aufteilung eines 32-Bit-Wortes in 16 einzelne 4-Bit-Blöcke. Durch seine einfache und effiziente Implementierung eignet er sich ideal für Anwendungen, bei denen eine detaillierte Analyse oder Verarbeitung von DWORD-Daten erforderlich ist.

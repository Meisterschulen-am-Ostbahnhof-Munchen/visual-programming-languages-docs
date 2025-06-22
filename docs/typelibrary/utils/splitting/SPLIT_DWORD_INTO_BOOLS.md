# SPLIT_DWORD_INTO_BOOLS

![SPLIT_DWORD_INTO_BOOLS](https://github.com/user-attachments/assets/6450d832-86ef-4de3-96ad-82a9b4c7bb3e)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SPLIT_DWORD_INTO_BOOLS` dient dazu, ein 32-Bit-DWORD in seine einzelnen Bits aufzuteilen und diese als separate BOOL-Werte auszugeben. Dies ist besonders nützlich, wenn komprimierte Daten in einer Steuerung verarbeitet werden müssen und die einzelnen Bits separat angesprochen werden sollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird dieser Eingang aktiviert, werden die Bits des Eingangs-DWORD ausgewertet und an den Ausgängen bereitgestellt.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Dieses Ereignis wird zusammen mit den aktualisierten BOOL-Ausgängen ausgelöst.

### **Daten-Eingänge**
- **IN**: Das Eingangs-DWORD, das in 32 einzelne Bits aufgeteilt werden soll.

### **Daten-Ausgänge**
- **BIT_00** bis **BIT_31**: Die 32 einzelnen Bits des Eingangs-DWORD, jeweils als BOOL-Wert ausgegeben. Jeder Ausgang repräsentiert ein Bit des DWORD, wobei `BIT_00` dem niederwertigsten Bit (LSB) und `BIT_31` dem höchstwertigen Bit (MSB) entspricht.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock extrahiert jedes Bit des Eingangs-DWORD `IN` und weist es den entsprechenden BOOL-Ausgängen zu. Die Zuordnung erfolgt direkt: 
- `BIT_00` = Bit 0 (LSB)
- `BIT_01` = Bit 1
- ...
- `BIT_31` = Bit 31 (MSB)

Bei Aktivierung des `REQ`-Ereignisses werden alle Bits ausgewertet, und das `CNF`-Ereignis wird ausgelöst, sobald die Ausgänge aktualisiert sind.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert und verwendet direkte Bit-Zugriffe auf das DWORD (`IN.%X0` bis `IN.%X31`).
- Die Ausgänge werden synchron mit dem `CNF`-Ereignis aktualisiert, was eine deterministische Verarbeitung ermöglicht.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Bei jedem `REQ`-Ereignis werden die Ausgänge neu berechnet.

## Anwendungsszenarien
- Verarbeitung von komprimierten Statusinformationen, z. B. aus einem Feldbus oder einer Schnittstelle.
- Dekodierung von Bitmasken in Steuerungsanwendungen.
- Aufteilung von DWORD-Werten für individuelle Bit-Manipulationen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulations-Funktionen bietet dieser Baustein eine direkte und effiziente Methode zur Extraktion aller Bits eines DWORD.
- Ähnliche Bausteine könnten nur Teile eines DWORD verarbeiten oder zusätzliche Logik enthalten, was hier nicht der Fall ist.

## Fazit
Der `SPLIT_DWORD_INTO_BOOLS`-Funktionsblock ist ein spezialisiertes Werkzeug zur effizienten Aufteilung eines DWORD in seine einzelnen Bits. Durch seine einfache und deterministische Funktionsweise eignet er sich ideal für Anwendungen, in denen Bit-Manipulationen erforderlich sind.

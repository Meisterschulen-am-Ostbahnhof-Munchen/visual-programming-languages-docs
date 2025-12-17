# ST08B_TO_BOOLS

![ST08B_TO_BOOLS](https://github.com/user-attachments/assets/5ab5b2e2-dd67-448f-8306-12ec64fd03c5)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ST08B_TO_BOOLS` dient zur Konvertierung eines `ST08B`-Datentyps in acht einzelne `BOOL`-Werte. Dies ermöglicht die einfache Extraktion einzelner Bits aus einem Byte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Wird mit allen acht Daten-Ausgängen (`OUT_00` bis `OUT_07`) verknüpft.

### **Daten-Eingänge**
- **IN**: Eingang vom Typ `ST08B`, der das zu konvertierende Byte enthält.

### **Daten-Ausgänge**
- **OUT_00** bis **OUT_07**: Acht einzelne `BOOL`-Ausgänge, die den Bits 0 bis 7 des Eingangsbytes entsprechen.

### **Adapter**
Es werden keine Adapter verwendet.

## Funktionsweise
Der Funktionsblock extrahiert die einzelnen Bits aus dem `ST08B`-Eingang und weist sie den entsprechenden `BOOL`-Ausgängen zu. Die Extraktion erfolgt direkt durch Zugriff auf die einzelnen Bitfelder des `ST08B`-Typs (`B_00` bis `B_07`).

## Technische Besonderheiten
- Der Funktionsblock ist für die Verarbeitung eines einzelnen Bytes optimiert.
- Die Extraktion der Bits erfolgt ohne zusätzliche Berechnungen oder Verzögerungen.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Extraktion von Steuerbits aus einem Byte, z.B. von Sensordaten oder Steuerbefehlen.
- Aufteilung von Byte-Daten für die individuelle Verarbeitung einzelner Bits in nachfolgenden Funktionsblöcken.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Extraktionsfunktionen ist `ST08B_TO_BOOLS` spezifisch für den `ST08B`-Datentyp optimiert.
- Ähnliche Funktionsblöcke könnten eine flexible Bit-Positionierung ermöglichen, was hier nicht erforderlich ist.

## Fazit
Der `ST08B_TO_BOOLS`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, die Bits eines `ST08B`-Bytes in einzelne `BOOL`-Werte zu extrahieren. Er ist besonders nützlich in Anwendungen, wo einzelne Bits eines Bytes separat verarbeitet werden müssen.

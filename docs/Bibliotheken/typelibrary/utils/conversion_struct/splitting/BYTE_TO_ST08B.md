# BYTE_TO_ST08B

![BYTE_TO_ST08B](https://github.com/user-attachments/assets/1bbabd58-531d-476d-9130-75f93e1a1429)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BYTE_TO_ST08B` dient zur Konvertierung eines BYTE-Wertes in eine Struktur von 8 einzelnen BOOL-Werten (ST08B). Diese Funktionalität ist besonders nützlich, wenn einzelne Bits eines Bytes separat verarbeitet oder überwacht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Event): Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Event): Signalisiert den Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (BYTE): Der Eingangswert, der in 8 einzelne BOOL-Werte zerlegt werden soll.

### **Daten-Ausgänge**
- `OUT` (ST08B): Die Ausgangsstruktur, die die 8 BOOL-Werte enthält. Die Struktur besteht aus den folgenden Elementen:
  - `B_00` bis `B_07`: Entsprechen den Bits 0 bis 7 des Eingangs-BYTE.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die einzelnen Bits des Eingangs-BYTE und weist sie den entsprechenden BOOL-Elementen der Ausgangsstruktur `ST08B` zu. Die Zuordnung erfolgt wie folgt:
- Bit 0 des BYTE → `OUT.B_00`
- Bit 1 des BYTE → `OUT.B_01`
- ...
- Bit 7 des BYTE → `OUT.B_07`

Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Verzögerung.
- Der Funktionsblock ist für die Verarbeitung eines einzelnen BYTE-Wertes optimiert.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Extrahiert die Bits aus dem BYTE und füllt die `ST08B`-Struktur.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Extraktion von Statusbits aus einem Steuerbyte.
- Verarbeitung von digitalen Eingangssignalen, die als Byte übertragen werden.
- Debugging und Monitoring von einzelnen Bits in einem Byte.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulations-Funktionsblöcken ist `BYTE_TO_ST08B` spezialisiert auf die Konvertierung eines BYTE in eine feste Struktur von 8 BOOL-Werten.
- Ähnliche Funktionsblöcke könnten eine flexible Anzahl von Bits unterstützen, was jedoch oft mit zusätzlicher Komplexität verbunden ist.

## Fazit
Der `BYTE_TO_ST08B`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, ein Byte in seine einzelnen Bits zu zerlegen. Durch seine spezialisierte Funktionalität ist er besonders in Szenarien nützlich, in denen eine klare und direkte Zuordnung von Bits zu BOOL-Werten erforderlich ist.

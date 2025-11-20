# ASSEMBLE_WORD_FROM_BOOLS

![ASSEMBLE_WORD_FROM_BOOLS](https://github.com/user-attachments/assets/0f9e88ae-3645-4364-a8e7-183caf4f1bb0)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_WORD_FROM_BOOLS` kombiniert 16 boolesche Eingangswerte zu einem einzigen WORD-Ausgangswert. Jeder boolesche Eingang repräsentiert dabei ein einzelnes Bit im resultierenden WORD.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Verarbeitung und übernimmt alle aktuellen Werte der booleschen Eingänge.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Zusammenführung der booleschen Werte zu einem WORD.

### **Daten-Eingänge**
16 boolesche Eingänge (BIT_00 bis BIT_15), die jeweils einem Bit im resultierenden WORD entsprechen:
- `BIT_00` bis `BIT_15` (BOOL): Einzelne Bits für das zusammenzusetzende WORD

### **Daten-Ausgänge**
- `(Unbenannt)` (WORD): Das resultierende WORD, das aus den 16 booleschen Eingängen zusammengesetzt wurde.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses werden alle 16 booleschen Eingangswerte gelesen und zu einem 16-Bit-WORD kombiniert. Dabei entspricht:
- `BIT_00` dem Bit 0 (LSB)
- `BIT_15` dem Bit 15 (MSB)

Die Zuweisung erfolgt direkt über Bitoperationen, wobei jeder boolesche Eingangswert auf das entsprechende Bit im WORD abgebildet wird.

## Technische Besonderheiten
- Die Bitreihenfolge ist fest vorgegeben (BIT_00 = LSB, BIT_15 = MSB)
- Der Block führt keine zusätzlichen Berechnungen oder Transformationen durch
- Die Operation ist atomar und erfolgt in einem Schritt

## Zustandsübersicht
1. **Idle**: Wartet auf `REQ`-Ereignis
2. **Processing**: Verarbeitet die Eingänge und setzt das WORD zusammen
3. **Output**: Sendet `CNF` mit dem resultierenden WORD

## Anwendungsszenarien
- Zusammenführen von einzelnen Schaltzuständen zu einem kompakten Datenwort
- Vorbereitung von Daten für die Kommunikation mit Geräten, die WORD-Daten erwarten
- Bitweise Steuerung von Hardware-Registern

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu allgemeinen Kombinationsblöcken ist dieser FB speziell auf die Konvertierung von BOOL zu WORD optimiert
- Bietet eine direktere und effizientere Lösung als die Verwendung mehrerer Einzelblöcke
- Ähnlich zu BIT_TO_* Blöcken, aber mit fester 16-Bit-WORD-Ausgabe

## Fazit
Der `ASSEMBLE_WORD_FROM_BOOLS` Funktionsblock bietet eine effiziente und direkte Methode, um 16 boolesche Signale in ein einzelnes WORD zu konvertieren. Seine einfache und deterministische Funktionsweise macht ihn besonders geeignet für Anwendungen, bei denen einzelne Bits zu kompakten Datenwörtern zusammengefasst werden müssen.

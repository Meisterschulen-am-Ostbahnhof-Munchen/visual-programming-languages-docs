# ASSEMBLE_WORD_FROM_BYTES

```{index} single: ASSEMBLE_WORD_FROM_BYTES
```

![ASSEMBLE_WORD_FROM_BYTES](https://github.com/user-attachments/assets/7ddc020d-4826-42e2-8447-7ba0fcfd215a)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ASSEMBLE_WORD_FROM_BYTES` kombiniert zwei Byte-Werte zu einem Wort (WORD). Dies ist besonders nützlich, wenn Daten aus zwei separaten Byte-Quellen zu einem zusammenhängenden 16-Bit-Wert verknüpft werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Verarbeitung. Die Eingabedaten `BYTE_00` und `BYTE_01` werden mit diesem Ereignis übergeben.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Zusammenführung der Bytes zu einem WORD.

### **Daten-Eingänge**
- **BYTE_00**: Das niederwertige Byte (LSB) des resultierenden WORD.
- **BYTE_01**: Das höherwertige Byte (MSB) des resultierenden WORD.

### **Daten-Ausgänge**
- **(kein Name)**: Das resultierende WORD, zusammengesetzt aus `BYTE_00` (LSB) und `BYTE_01` (MSB).

### **Adapter**
Es werden keine Adapter verwendet.

## Funktionsweise
Der Funktionsblock setzt die beiden Eingabe-Bytes `BYTE_00` und `BYTE_01` zu einem 16-Bit-WORD zusammen. Dabei wird `BYTE_00` als niederwertiges Byte (LSB) und `BYTE_01` als höherwertiges Byte (MSB) verwendet. Die Operation erfolgt unmittelbar nach dem Eintreffen des `REQ`-Ereignisses, und das Ergebnis wird mit dem `CNF`-Ereignis ausgegeben.

## Technische Besonderheiten
- Die Zusammenführung erfolgt direkt durch Zuweisung der Bytes zu den entsprechenden Positionen im WORD.
- Der Block ist für die Verwendung in Echtzeit-Systemen optimiert und hat eine deterministische Laufzeit.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Eingabedaten und erzeugt das WORD.
3. **Output**: Sendet das `CNF`-Ereignis mit dem resultierenden WORD.

## Anwendungsszenarien
- Kombination von Sensorwerten, die als separate Bytes vorliegen.
- Verarbeitung von Kommunikationsprotokollen, bei denen Daten in Byte-Paaren übertragen werden.
- Allgemeine Datenmanipulation in Steuerungssystemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Rechenbausteinen ist `ASSEMBLE_WORD_FROM_BYTES` spezialisiert und effizienter für diese spezielle Aufgabe.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Byte-Swapping oder Fehlerbehandlung bieten, sind aber komplexer.

## Fazit
Der `ASSEMBLE_WORD_FROM_BYTES`-Funktionsblock ist ein einfacher und effizienter Baustein zur Kombination von zwei Bytes zu einem WORD. Er eignet sich besonders für Anwendungen, bei denen Performance und Einfachheit im Vordergrund stehen.
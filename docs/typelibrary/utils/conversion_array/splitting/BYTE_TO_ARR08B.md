# BYTE_TO_ARR08B

![BYTE_TO_ARR08B](https://github.com/user-attachments/assets/99f955b1-afef-4745-b87c-78e83c9287c5)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BYTE_TO_ARR08B` dient zur Konvertierung eines Byte-Wertes in ein Array von 8 Booleschen Werten. Jedes Bit des Eingabe-Byte wird dabei auf ein entsprechendes Element im Ausgabe-Array abgebildet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (BYTE): Der Byte-Wert, der in ein Array von Booleschen Werten umgewandelt werden soll.

### **Daten-Ausgänge**
- `OUT` (ARRAY[0..7] OF BOOL): Das Ausgabe-Array, das die einzelnen Bits des Eingabe-Byte als Boolesche Werte enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die 8 Bits des Eingabe-Byte und weist jedes Bit einem entsprechenden Element im Ausgabe-Array zu. Die Zuordnung erfolgt direkt, wobei das niederwertigste Bit (Bit 0) des Byte dem ersten Element des Arrays (`OUT[0]`) entspricht und das höchstwertige Bit (Bit 7) dem letzten Element (`OUT[7]`).

## Technische Besonderheiten
- Die Konvertierung erfolgt bitweise und ist deterministisch.
- Der Funktionsblock ist für die Verarbeitung eines einzelnen Byte-Wertes optimiert.

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Verarbeitung**: Bei Empfang von `REQ` wird der Byte-Wert `IN` verarbeitet und in das Array `OUT` umgewandelt.
3. **Bestätigung**: Nach erfolgreicher Verarbeitung wird das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Umwandlung von Byte-Daten in einzelne Boolesche Signale für die Steuerung von digitalen Ausgängen.
- Verarbeitung von seriellen Daten, bei denen einzelne Bits als separate Signale benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Bit-Manipulations-Funktionsblöcken ist `BYTE_TO_ARR08B` spezialisiert auf die direkte Umwandlung eines Byte in ein Boolesches Array und bietet daher eine einfachere und effizientere Lösung für diesen spezifischen Anwendungsfall.

## Fazit
Der `BYTE_TO_ARR08B`-Funktionsblock ist ein nützliches Werkzeug für die direkte Konvertierung von Byte-Daten in ein Array von Booleschen Werten. Seine Einfachheit und Effizienz machen ihn ideal für Anwendungen, bei denen eine schnelle und zuverlässige Bit-Extraktion erforderlich ist.

# F_SINT_TO_WORD

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SINT_TO_WORD` dient der Konvertierung eines SINT-Wertes (8-Bit Ganzahl mit Vorzeichen) in einen WORD-Wert (16-Bit Ganzahl ohne Vorzeichen). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlichen Integer-Formaten erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung der Konvertierung. Wird mit dem Eingabewert `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Liefert den konvertierten Wert über `OUT`.

### **Daten-Eingänge**
- `IN` (SINT): Der Eingabewert, der von SINT zu WORD konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (WORD): Der konvertierte WORD-Wert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert von SINT zu WORD konvertiert. Das Ergebnis wird über `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch die Funktion `SINT_TO_WORD(IN)`.
- Keine zusätzliche Fehlerbehandlung für Überlauf oder Unterlauf, da SINT (8-Bit) in WORD (16-Bit) konvertiert wird und somit keine Werte verloren gehen.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo unterschiedliche Integer-Formate verarbeitet werden müssen.
- Datenvorverarbeitung für Kommunikationsprotokolle oder Sensordaten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_WORD` oder `F_DINT_TO_WORD` bieten Konvertierungen von anderen Integer-Typen zu WORD.
- `F_SINT_TO_WORD` ist spezifisch für die Konvertierung von 8-Bit vorzeichenbehafteten zu 16-Bit vorzeichenlosen Integern optimiert.

## Fazit
Der `F_SINT_TO_WORD` Funktionsblock ist ein einfacher und effizienter Baustein für die Typumwandlung von SINT zu WORD. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Konvertierung benötigen.
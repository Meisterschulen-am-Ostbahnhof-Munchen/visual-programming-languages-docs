# ARR08B_TO_BYTE

![ARR08B_TO_BYTE](https://github.com/user-attachments/assets/94aae622-5ea6-4d2d-a227-5bca8fafe259)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARR08B_TO_BYTE` dient zur Konvertierung eines 8-elementigen BOOL-Arrays in einen BYTE-Wert. Jedes Bit des BYTE-Ausgangs entspricht einem Element des Eingangsarrays.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (ARR08B Input): Ein 8-elementiges BOOL-Array (Indizes 0 bis 7), das die einzelnen Bits für die Konvertierung bereitstellt.

### **Daten-Ausgänge**
- `OUT` (BYTE Output): Der resultierende BYTE-Wert, dessen Bits den Werten des Eingangsarrays entsprechen.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die 8 Bits aus dem Eingangsarray und weist sie den entsprechenden Bits des BYTE-Ausgangs zu:
- `OUT.0` = `IN[0]`
- `OUT.1` = `IN[1]`
- ...
- `OUT.7` = `IN[7]`

Die Konvertierung erfolgt bei jedem `REQ`-Ereignis, und das Ergebnis wird mit dem `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Die Indizierung des Eingangsarrays muss von 0 bis 7 erfolgen.

## Zustandsübersicht
1. **Wartezustand**: Der Funktionsblock wartet auf ein `REQ`-Ereignis.
2. **Ausführungszustand**: Bei `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst.

## Anwendungsszenarien
- Umwandlung von digitalen Eingangssignalen (z.B. von Schaltern oder Sensoren) in einen kompakten BYTE-Wert für die weitere Verarbeitung.
- Datenkomprimierung für die Übertragung oder Speicherung.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu allgemeinen Konvertierungsbausteinen ist `ARR08B_TO_BYTE` speziell auf die Umwandlung von 8 BOOL-Werten in einen BYTE optimiert.
- Ähnliche Bausteine könnten andere Datentypen oder Array-Größen unterstützen.

## Fazit
`ARR08B_TO_BYTE` ist ein effizienter und spezialisierter Funktionsblock für die Konvertierung von 8 BOOL-Werten in einen BYTE. Seine einfache und direkte Implementierung macht ihn zuverlässig und leicht verständlich.

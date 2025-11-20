# ST08B_TO_ARR08B

![ST08B_TO_ARR08B](https://github.com/user-attachments/assets/3bd08caa-dbcf-4c94-87d6-4b2e75f167bd)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ST08B_TO_ARR08B` dient zur Konvertierung einer `ST08B`-Struktur in ein `BOOL`-Array der Größe 8. Er extrahiert die einzelnen Bits aus der Byte-Struktur und ordnet sie einem Array zu.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (ST08B Input): Die Eingangsdaten im `ST08B`-Format, die in ein `BOOL`-Array umgewandelt werden sollen.

### **Daten-Ausgänge**
- `OUT` (ARR08B Output): Das Ergebnis der Konvertierung als `BOOL`-Array mit 8 Elementen (Indizes 0 bis 7).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die einzelnen Bits (`B_00` bis `B_07`) aus der `ST08B`-Struktur und weist sie den entsprechenden Positionen im `BOOL`-Array `OUT` zu. Die Zuordnung erfolgt wie folgt:
- `OUT[0]` = `IN.B_00`
- `OUT[1]` = `IN.B_01`
- `OUT[2]` = `IN.B_02`
- `OUT[3]` = `IN.B_03`
- `OUT[4]` = `IN.B_04`
- `OUT[5]` = `IN.B_05`
- `OUT[6]` = `IN.B_06`
- `OUT[7]` = `IN.B_07`

## Technische Besonderheiten
- Der Funktionsblock ist für die Verarbeitung von Byte-Daten optimiert und eignet sich besonders für die Umwandlung von strukturierten Daten in Arrays.
- Die Konvertierung erfolgt direkt und ohne Verzögerung bei Auslösung des `REQ`-Ereignisses.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Ausführungszustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Umwandlung von Byte-Daten in einzelne Bits für die Steuerung von digitalen Ausgängen.
- Verarbeitung von Daten aus Sensoren oder Steuerungen, die als Byte-Struktur vorliegen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist `ST08B_TO_ARR08B` speziell für die `ST08B`-Struktur optimiert und bietet eine direkte und effiziente Umwandlung.
- Andere Bausteine könnten eine allgemeinere Lösung bieten, sind aber möglicherweise weniger effizient oder erfordern zusätzliche Konfiguration.

## Fazit
Der `ST08B_TO_ARR08B`-Funktionsblock ist ein spezialisiertes und effizientes Werkzeug zur Konvertierung von `ST08B`-Daten in ein `BOOL`-Array. Er eignet sich ideal für Anwendungen, bei denen eine schnelle und direkte Umwandlung erforderlich ist.

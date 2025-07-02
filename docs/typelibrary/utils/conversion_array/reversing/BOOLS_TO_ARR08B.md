# BOOLS_TO_ARR08B

![BOOLS_TO_ARR08B](https://github.com/user-attachments/assets/465fd42e-745b-4b1f-a06d-0957abc3621b)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOLS_TO_ARR08B` dient zur Konvertierung von acht einzelnen BOOL-Werten in ein BOOL-Array der Größe 8. Dieser Baustein ist besonders nützlich, wenn mehrere binäre Signale zusammengefasst und als Array weiterverarbeitet werden sollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit allen Daten-Eingängen verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN_00` (BIT 00): Erster BOOL-Eingang.
- `IN_01` (BIT 01): Zweiter BOOL-Eingang.
- `IN_02` (BIT 02): Dritter BOOL-Eingang.
- `IN_03` (BIT 03): Vierter BOOL-Eingang.
- `IN_04` (BIT 04): Fünfter BOOL-Eingang.
- `IN_05` (BIT 05): Sechster BOOL-Eingang.
- `IN_06` (BIT 06): Siebter BOOL-Eingang.
- `IN_07` (BIT 07): Achter BOOL-Eingang.

### **Daten-Ausgänge**
- `OUT` (ARR08B Output): Ausgangsarray vom Typ BOOL mit den Indizes 0 bis 7, das die Eingangswerte enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `BOOLS_TO_ARR08B` weist die acht Eingangs-BOOL-Werte den entsprechenden Positionen im Ausgangsarray zu:
- `OUT[0]` erhält den Wert von `IN_00`.
- `OUT[1]` erhält den Wert von `IN_01`.
- ...
- `OUT[7]` erhält den Wert von `IN_07`.

Die Ausführung wird durch das Ereignis `REQ` gestartet und mit `CNF` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Das Ausgangsarray ist fest auf eine Größe von 8 Elementen (0..7) definiert.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt direkt bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Zusammenfassen von binären Sensordaten für die Weiterverarbeitung.
- Vorbereitung von Daten für die Kommunikation mit anderen Systemen, die Array-Daten erwarten.
- Vereinfachung der Logik bei der Handhabung mehrerer BOOL-Signale.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu manuell erstellten Array-Zuweisungen bietet dieser Funktionsblock eine vordefinierte und wiederverwendbare Lösung. Ähnliche Bausteine könnten eine flexible Array-Größe unterstützen, was hier nicht der Fall ist.

## Fazit
Der `BOOLS_TO_ARR08B`-Funktionsblock ist eine einfache und effiziente Lösung, um acht einzelne BOOL-Werte in ein Array zu konvertieren. Er eignet sich besonders für Anwendungen, bei denen mehrere binäre Signale gebündelt werden müssen. Die feste Array-Größe von 8 Elementen macht ihn spezifisch, aber auch leicht verständlich und wartbar.

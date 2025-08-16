# F_BOOL_AS_STRING

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_AS_STRING` dient zur Konvertierung eines booleschen Wertes (`BOOL`) in eine Zeichenkette (`STRING`). Diese Funktionalität ist besonders nützlich, wenn boolesche Werte für die Ausgabe oder Weiterverarbeitung in einem Textformat benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der boolesche Wert (`BOOL`), der in eine Zeichenkette konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Die resultierende Zeichenkette (`STRING`), die den konvertierten booleschen Wert repräsentiert.

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock nutzt einen einfachen Algorithmus, um den booleschen Wert `IN` in eine Zeichenkette `OUT` umzuwandeln. Die Konvertierung erfolgt durch die Funktion `BOOL_AS_STRING(IN)`, die intern den Wert von `IN` in eine entsprechende Zeichenkette umsetzt (z.B. `TRUE` oder `FALSE`).

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient implementiert, ohne zusätzliche Zustände oder komplexe Logik.
- Die Konvertierung erfolgt synchron mit dem Auslösen des `REQ`-Ereignisses.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine expliziten Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Protokollierung**: Konvertierung von booleschen Werten für Logging-Zwecke.
- **Benutzeroberflächen**: Darstellung von booleschen Werten in menschenlesbarer Form.
- **Datenkommunikation**: Vorbereitung von booleschen Werten für die Übertragung als Text.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_TO_BOOL**: Führt die umgekehrte Konvertierung von `STRING` zu `BOOL` durch.
- **F_BOOL_TO_***: Andere Konvertierungsbausteine, die boolesche Werte in verschiedene Datentypen umwandeln.

## Fazit
Der `F_BOOL_AS_STRING` Funktionsblock bietet eine einfache und effektive Möglichkeit, boolesche Werte in Zeichenketten umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem nützlichen Werkzeug in vielen Anwendungsfällen.
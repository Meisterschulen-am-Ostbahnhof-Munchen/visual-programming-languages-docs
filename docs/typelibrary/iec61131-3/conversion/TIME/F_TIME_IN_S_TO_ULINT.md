# F_TIME_IN_S_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_ULINT` dient der Konvertierung eines TIME-Werts in Sekunden in einen ULINT-Wert. Dies ist besonders nützlich, wenn Zeitwerte in numerische Formate umgewandelt werden müssen, um sie in Berechnungen oder für weitere Verarbeitungsschritte zu verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungs-Event. Dieser Event löst die Konvertierung aus und ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgreicher Ausführung. Dieser Event wird zusammen mit dem Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Eingang vom Typ `TIME`, der den zu konvertierenden Zeitwert in Sekunden enthält.

### **Daten-Ausgänge**
- **OUT**: Ausgang vom Typ `ULINT`, der den konvertierten numerischen Wert enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den TIME-Wert (in Sekunden) in einen ULINT-Wert umwandelt. Die Konvertierung erfolgt bei Auftreten des `REQ`-Events, und das Ergebnis wird über den `OUT`-Ausgang ausgegeben, begleitet vom `CNF`-Event.

## Technische Besonderheiten
- Der Funktionsblock verwendet den Standardalgorithmus `TIME_IN_S_TO_ULINT` für die Konvertierung.
- Der FB ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auftreten des `REQ`-Events.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungssysteme, die Zeitwerte in numerischer Form verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser FB spezialisiert auf die Umwandlung von TIME in ULINT.
- Andere Blöcke könnten unterschiedliche Ausgabetypen oder zusätzliche Funktionen bieten, wie z.B. die Umwandlung in andere numerische Formate.

## Fazit
Der `F_TIME_IN_S_TO_ULINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in numerische ULINT-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die solche Konvertierungen erfordern.
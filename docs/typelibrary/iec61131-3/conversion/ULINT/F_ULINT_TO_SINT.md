# F_ULINT_TO_SINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_SINT` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsigned integer) in einen `SINT`-Wert (8-Bit signed integer). Dieser Baustein ist besonders nützlich in Anwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `ULINT`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `SINT`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den `ULINT`-Wert an `IN` in einen `SINT`-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt durch die Funktion `ULINT_TO_SINT`.
- Es ist zu beachten, dass bei der Konvertierung von einem größeren zu einem kleineren Datentyp Datenverlust auftreten kann, wenn der `ULINT`-Wert außerhalb des darstellbaren Bereichs von `SINT` liegt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis durchgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen
- Datenverarbeitung, bei der unterschiedliche Datentypen verarbeitet werden müssen
- Kommunikation zwischen Systemen mit unterschiedlichen Datentypen

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_SINT` oder `F_LINT_TO_SINT` führen ähnliche Konvertierungen durch, jedoch mit anderen Ausgangsdatentypen.
- `F_ULINT_TO_SINT` ist spezifisch für die Konvertierung von `ULINT` zu `SINT`.

## Fazit
Der `F_ULINT_TO_SINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, `ULINT`-Werte in `SINT`-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, bei denen eine Typumwandlung erforderlich ist, jedoch sollte auf mögliche Datenverluste bei der Konvertierung geachtet werden.
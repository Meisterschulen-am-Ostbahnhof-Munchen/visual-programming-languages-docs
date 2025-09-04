# F_LINT_TO_BYTE

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_BYTE` dient der Konvertierung eines LINT-Datentyps (64-Bit Ganzzahl) in einen BYTE-Datentyp (8-Bit Ganzzahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Löst die Ausführung des Funktionsblocks aus. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingang für den LINT-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten BYTE-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von LINT zu BYTE durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `LINT_TO_BYTE(IN)`, wobei der Wert von `IN` in den BYTE-Typ umgewandelt und an `OUT` ausgegeben wird. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus (SimpleFB) und führt keine komplexen Zustandsübergänge durch.
- Die Konvertierung kann zu Datenverlust führen, wenn der LINT-Wert außerhalb des darstellbaren Bereichs eines BYTE (0 bis 255) liegt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge. Die Ausführung erfolgt direkt bei Auslösung von `REQ`.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo LINT-Daten in BYTE-Daten umgewandelt werden müssen.
- Verwendung in Datenverarbeitungsketten, wo unterschiedliche Datentypen kompatibel gemacht werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_INT_TO_BYTE` oder `F_DINT_TO_BYTE` führen ähnliche Konvertierungen durch, jedoch mit anderen Ausgangsdatentypen.
- `F_LINT_TO_BYTE` ist spezifisch für die Konvertierung von 64-Bit zu 8-Bit Ganzzahlen.

## Fazit
Der `F_LINT_TO_BYTE` Funktionsblock bietet eine einfache und effiziente Möglichkeit, LINT-Daten in BYTE-Daten umzuwandeln. Seine Verwendung ist in Szenarien mit Typkonvertierungen unerlässlich, jedoch ist auf mögliche Datenverluste bei großen Werten zu achten.
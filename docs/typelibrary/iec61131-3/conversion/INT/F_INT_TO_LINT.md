# F_INT_TO_LINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_LINT` dient der Konvertierung eines 16-Bit Integer-Werts (`INT`) in einen 64-Bit Long Integer-Wert (`LINT`). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Erweiterung des Wertebereichs oder eine Typanpassung für nachfolgende Verarbeitungsschritte erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`INT`): Der 16-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`LINT`): Der resultierende 64-Bit Long Integer-Wert nach der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingabewerts `IN` vom Typ `INT` zum Ausgabewert `OUT` vom Typ `LINT` durch. Die Konvertierung erfolgt implizit durch die Typumwandlung, wobei der numerische Wert erhalten bleibt.

## Technische Besonderheiten
- **Einfache Implementierung**: Der Algorithmus besteht aus einer einzigen Zuweisung.
- **Keine Datenverluste**: Da `LINT` einen größeren Wertebereich als `INT` besitzt, gibt es keine Überlaufprobleme.
- **Deterministisches Verhalten**: Die Ausführung ist vorhersehbar und schnell.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand. Jeder Aufruf über `REQ` führt zur sofortigen Ausführung und Ausgabe über `CNF`.

## Anwendungsszenarien
- **Datenverarbeitung**: Erweiterung von Integer-Werten für nachfolgende Berechnungen mit größerem Wertebereich.
- **Schnittstellenanpassung**: Anpassung von Daten für Komponenten, die `LINT` erwarten.
- **Protokollierung**: Speicherung von `INT`-Werten in Systemen, die `LINT` verwenden.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_DINT**: Konvertiert `INT` zu `DINT` (32-Bit), bietet weniger Wertebereich als `LINT`.
- **F_DINT_TO_LINT**: Konvertiert `DINT` zu `LINT`, ähnlich aber mit anderem Eingangstyp.
- **F_LINT_TO_INT**: Umgekehrte Konvertierung, potenziell mit Datenverlust.

## Fazit
Der `F_INT_TO_LINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Typkonvertierung in 4diac-IDE. Seine Stärke liegt in der direkten und verlustfreien Umwandlung, was ihn ideal für Anwendungen mit erweitertem Wertebedarf macht.
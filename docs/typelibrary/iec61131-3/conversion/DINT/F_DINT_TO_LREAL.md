# F_DINT_TO_LREAL

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_LREAL` dient der Konvertierung eines 32-Bit-Ganzzahlwertes (DINT) in einen 64-Bit-Gleitkommawert (LREAL). Diese Konvertierung ist insbesondere in Steuerungssystemen notwendig, wo unterschiedliche Datentypen in verschiedenen Teilen der Anwendung verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DINT`, der in einen `LREAL`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `LREAL`, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Bei Auslösung des Ereignisses `REQ` wird der Wert von `IN` gelesen und in den Datentyp `LREAL` umgewandelt. Das Ergebnis wird an `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Skalierung oder Offset-Anpassung.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Ganzzahlen in Gleitkommazahlen für mathematische Berechnungen.
- Integration in Steuerungssysteme, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Verwendung in Regelungstechnik, wo präzise Gleitkommaberechnungen erforderlich sind.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_DINT_TO_LREAL` spezialisiert auf die Umwandlung von `DINT` zu `LREAL` und bietet daher eine höhere Effizienz und Lesbarkeit im Code.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Begrenzung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_DINT_TO_LREAL` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von Ganzzahlen in Gleitkommazahlen. Seine klare Schnittstelle und deterministische Funktionsweise machen ihn ideal für den Einsatz in Steuerungs- und Regelungssystemen.
# F_LINT_TO_LREAL

<img width="1448" height="214" alt="F_LINT_TO_LREAL" src="https://github.com/user-attachments/assets/411d5efa-708f-43f3-8da5-db0f863bcd2c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_LREAL` dient der Konvertierung eines ganzzahligen Wertes des Typs `LINT` (64-Bit Ganzzahl) in einen Fließkommawert des Typs `LREAL` (64-Bit Fließkomma). Diese Konvertierung ist insbesondere dann notwendig, wenn ganzzahlige Werte in Berechnungen mit Fließkommazahlen verwendet werden sollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `LINT`, der in einen `LREAL`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `LREAL`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` vom Typ `LINT` in den Typ `LREAL` konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen geeignet, da er deterministisch arbeitet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Umwandlung von großen Ganzzahlen in Fließkommazahlen für mathematische Berechnungen.
- Integration in Steuerungssysteme, die gemischte Datentypen verarbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_REAL` oder `F_DINT_TO_REAL` handelt `F_LINT_TO_LREAL` mit größeren Zahlenbereichen (64-Bit).

## Fazit
Der `F_LINT_TO_LREAL`-Funktionsblock bietet eine effiziente und zuverlässige Methode zur Konvertierung von 64-Bit Ganzzahlen in 64-Bit Fließkommazahlen. Seine einfache Schnittstelle und deterministische Funktionsweise machen ihn ideal für den Einsatz in industriellen Steuerungssystemen.

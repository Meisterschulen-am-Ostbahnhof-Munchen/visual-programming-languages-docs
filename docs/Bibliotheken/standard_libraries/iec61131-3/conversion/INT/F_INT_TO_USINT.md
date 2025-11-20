# F_INT_TO_USINT

<img width="1232" height="183" alt="F_INT_TO_USINT" src="https://github.com/user-attachments/assets/936ae83a-1805-4eae-89d4-6a1f41f0e727" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_USINT` dient der Konvertierung eines ganzzahligen Wertes vom Datentyp `INT` (16-Bit Ganzzahl mit Vorzeichen) in den Datentyp `USINT` (8-Bit Ganzzahl ohne Vorzeichen). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlich großen numerischen Werten erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Typ: `Event`): Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF** (Typ: `Event`): Signalisiert den erfolgreichen Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (Typ: `INT`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (Typ: `USINT`): Das Ergebnis der Konvertierung von `INT` zu `USINT`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus des Funktionsblocks ausgeführt. Dieser wandelt den Wert am Daten-Eingang `IN` vom Typ `INT` in den Typ `USINT` um und speichert das Ergebnis im Daten-Ausgang `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die Funktion `INT_TO_USINT`, die den `INT`-Wert in einen `USINT`-Wert umwandelt. Dabei kann es zu einem Datenverlust kommen, wenn der ursprüngliche `INT`-Wert außerhalb des darstellbaren Bereichs von `USINT` (0 bis 255) liegt.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`, das verschiedene Typkonvertierungen bereitstellt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typkonvertierung in Steuerungsanwendungen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Reduzierung der Speicherbelegung durch Konvertierung in kleinere Datentypen, wo möglich.
- Vorbereitung von Daten für die Kommunikation mit Systemen, die nur `USINT`-Werte verarbeiten können.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_USINT` oder `F_SINT_TO_USINT` bieten Konvertierungen von anderen Ganzzahltypen zu `USINT`. `F_INT_TO_USINT` ist spezifisch für die Umwandlung von `INT` zu `USINT` optimiert.
- Im Gegensatz zu generischen Konvertierungsblöcken bietet dieser Baustein eine direkte und effiziente Lösung für die spezifische Typumwandlung.

## Fazit
Der `F_INT_TO_USINT` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von `INT`- zu `USINT`-Werten. Er eignet sich ideal für Anwendungen, die eine präzise und spezifische Typumwandlung erfordern, insbesondere in Umgebungen mit begrenzten Ressourcen oder spezifischen Datentypanforderungen.

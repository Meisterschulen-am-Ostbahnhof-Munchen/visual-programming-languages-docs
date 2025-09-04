# F_UDINT_TO_UINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UDINT_TO_UINT` dient der Konvertierung eines 32-Bit unsigned integer-Werts (UDINT) in einen 16-Bit unsigned integer-Wert (UINT). Der Block ist Teil des `iec61131::conversion` Pakets.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Eingabewerts. Der Eingabewert `IN` wird mit diesem Event übergeben.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Konvertierung und gibt den konvertierten Wert `OUT` aus.

### **Daten-Eingänge**
- **IN** (UDINT): Der 32-Bit unsigned integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (UINT): Der konvertierte 16-Bit unsigned integer-Wert.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Empfang des Events `REQ` wird der Eingabewert `IN` vom Typ UDINT in den Typ UINT konvertiert und über den Ausgang `OUT` ausgegeben. Gleichzeitig wird das Event `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch eine direkte Typumwandlung, wobei die höherwertigen Bits des UDINT-Werts abgeschnitten werden, falls der Wert außerhalb des darstellbaren Bereichs von UINT liegt.
- Der Block ist für die Verwendung in Echtzeit-Systemen geeignet.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Events.

## Anwendungsszenarien
- Konvertierung von 32-Bit-Werten in 16-Bit-Werten in Steuerungsanwendungen.
- Verwendung in Systemen, die mit unterschiedlichen Integer-Größen arbeiten müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_UDINT_TO_UINT` spezialisiert auf die Konvertierung von UDINT zu UINT und daher effizienter in der Ausführung.
- Ähnliche Blöcke wie `F_DINT_TO_INT` konvertieren zwischen anderen Integer-Typen.

## Fazit
Der Funktionsblock `F_UDINT_TO_UINT` ist ein spezialisierter und effizienter Baustein zur Konvertierung von 32-Bit- zu 16-Bit-unsigned integer-Werten. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und direkte Typumwandlung erforderlich ist.
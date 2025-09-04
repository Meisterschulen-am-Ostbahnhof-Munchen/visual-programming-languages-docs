# F_ULINT_TO_LREAL

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_LREAL` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsigned integer) in einen `LREAL`-Wert (64-Bit floating point). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Ganzzahlwerte in Gleitkommazahlen umgewandelt werden müssen, um weitere Berechnungen durchzuführen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- `IN` (`ULINT`): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (`LREAL`): Der konvertierte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `ULINT` nach `LREAL` durch, wenn das `REQ`-Ereignis ausgelöst wird. Die Konvertierung erfolgt mittels der eingebauten Funktion `ULINT_TO_LREAL`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst und der konvertierte Wert am Ausgang `OUT` bereitgestellt.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus (`REQ`), der die Konvertierung durchführt.
- Die Konvertierung ist verlustfrei, da `LREAL` einen größeren Wertebereich als `ULINT` abdeckt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Ganzzahlwerten in Gleitkommazahlen für weitere Berechnungen.
- Verwendung in Steuerungs- und Regelungssystemen, wo Gleitkommaoperationen erforderlich sind.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen (z.B. `F_INT_TO_REAL`) ist dieser speziell für die Konvertierung von 64-Bit unsigned integers zu 64-Bit floating points optimiert.
- Ähnliche Bausteine könnten eine geringere Genauigkeit oder einen kleineren Wertebereich aufweisen.

## Fazit
Der `F_ULINT_TO_LREAL`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `ULINT`-Werte in `LREAL`-Werte umzuwandeln. Seine klare Schnittstelle und verlustfreie Konvertierung machen ihn zu einem nützlichen Baustein in verschiedenen Anwendungen.
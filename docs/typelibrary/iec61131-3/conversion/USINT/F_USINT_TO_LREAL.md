# F_USINT_TO_LREAL

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_LREAL` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen 64-Bit-Gleitkommawert (LREAL). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (USINT): Der Eingangswert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (LREAL): Der konvertierte Ausgangswert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Typumwandlung durch. Bei Eintreffen eines `REQ`-Ereignisses wird der Wert von `IN` in den Datentyp LREAL umgewandelt und an `OUT` ausgegeben. Anschließend wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Skalierung oder Anpassung.
- Der Block ist für einfache Typumwandlungen optimiert und verfügt über keine komplexe Logik oder Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Konvertierung von Sensordaten, die als USINT vorliegen, für Berechnungen, die LREAL erfordern.
- Schnittstellen zwischen Systemen mit unterschiedlichen Datentypanforderungen.
- Einfache Typumwandlungen in Automatisierungsanwendungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_USINT_TO_LREAL` spezialisiert und daher effizienter für diese spezifische Konvertierung.
- Andere Blöcke könnten zusätzliche Funktionen wie Skalierung oder Bereichsprüfungen bieten, was hier nicht erforderlich ist.

## Fazit
Der `F_USINT_TO_LREAL`-Funktionsblock ist ein einfacher und effizienter Baustein für die direkte Konvertierung von USINT zu LREAL. Seine Stärke liegt in der Einfachheit und Spezialisierung, was ihn ideal für spezifische Anwendungsfälle macht, bei denen keine zusätzliche Logik benötigt wird.
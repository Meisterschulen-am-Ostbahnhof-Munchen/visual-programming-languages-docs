# F_LINT_TO_DINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_DINT` dient der Konvertierung eines 64-Bit Integer-Werts (LINT) in einen 32-Bit Integer-Wert (DINT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht werden müssen oder wenn Speicherplatz optimiert werden soll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (LINT): Der 64-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DINT): Der resultierende 32-Bit Integer-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der Algorithmus `REQ` aufgerufen wird, sobald das Ereignis `REQ` eintrifft. Der Algorithmus nutzt die Funktion `LINT_TO_DINT`, um den Wert von `IN` nach `OUT` zu konvertieren. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.
- Es handelt sich um einen einfachen Funktionsblock ohne interne Zustände oder komplexe Logik.
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche LINT-Wert außerhalb des darstellbaren Bereichs eines DINT liegt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Logik wird direkt bei Eintreffen des `REQ`-Ereignisses ausgeführt.

## Anwendungsszenarien
- Datenkompatibilität zwischen Systemen mit unterschiedlicher Wortbreite.
- Speicheroptimierung, wenn 64-Bit Werte nicht benötigt werden.
- Integration in größere Steuerungssysteme, die DINT-Werte erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_LINT_TO_DINT` spezialisiert auf die Konvertierung von LINT zu DINT.
- Andere Blöcke könnten zusätzliche Funktionen wie Bereichsprüfungen oder Fehlerbehandlung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_LINT_TO_DINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit Integer-Werte in 32-Bit Integer-Werte umzuwandeln. Seine Einfachheit macht ihn zuverlässig und leicht integrierbar, jedoch sollten Anwender potenzielle Datenverluste bei der Konvertierung großer Werte berücksichtigen.
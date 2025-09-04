# F_TIME_IN_S_TO_LINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_LINT` dient zur Konvertierung eines Zeitwertes in Sekunden (`TIME`) in einen 64-Bit Ganzzahlwert (`LINT`). Diese Konvertierung ist besonders nützlich, wenn Zeitwerte für Berechnungen oder Vergleiche in einer numerischen Form benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Zeitwertes. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang für den Zeitwert in Sekunden (`TIME`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten 64-Bit Ganzzahlwert (`LINT`).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den Zeitwert in Sekunden (`TIME`) in einen 64-Bit Ganzzahlwert (`LINT`) umwandelt. Die Konvertierung erfolgt bei Auslösung des `REQ`-Ereignisses und das Ergebnis wird über den `OUT`-Datenausgang ausgegeben, gefolgt von einem `CNF`-Ereignis.

## Technische Besonderheiten
- Der Funktionsblock verwendet den Standard `61499-1`.
- Die Konvertierung erfolgt mittels der Funktion `TIME_IN_S_TO_LINT`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine komplexen Zustände. Er reagiert auf das `REQ`-Ereignis, führt die Konvertierung durch und signalisiert den Abschluss mit dem `CNF`-Ereignis.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungssysteme, die Zeitwerte in einer numerischen Form benötigen.
- Verwendung in Systemen, die eine hohe Präzision bei der Zeitmessung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen, die möglicherweise andere Datentypen unterstützen, ist dieser Funktionsblock speziell auf die Konvertierung von `TIME` zu `LINT` ausgelegt.
- Andere Bausteine könnten eine Konvertierung in andere Ganzzahltypen (z.B. `INT` oder `DINT`) anbieten, aber dieser Baustein bietet eine höhere Präzision durch die Verwendung von `LINT`.

## Fazit
Der Funktionsblock `F_TIME_IN_S_TO_LINT` ist ein effizientes Werkzeug zur Konvertierung von Zeitwerten in Sekunden in 64-Bit Ganzzahlen. Seine einfache und direkte Funktionsweise macht ihn zu einer zuverlässigen Komponente in Steuerungssystemen, die präzise Zeitmessungen und -berechnungen erfordern.
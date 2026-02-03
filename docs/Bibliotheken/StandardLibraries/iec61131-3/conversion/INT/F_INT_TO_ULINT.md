# F_INT_TO_ULINT

```{index} single: F_INT_TO_ULINT
```

<img width="1232" height="183" alt="F_INT_TO_ULINT" src="https://github.com/user-attachments/assets/55a69d83-7b80-4166-9e24-3160c0e9d1b1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_ULINT` dient der Konvertierung eines ganzzahligen Wertes vom Datentyp `INT` in einen vorzeichenlosen 64-Bit-Ganzzahlwert vom Datentyp `ULINT`. Diese Konvertierung ist besonders nützlich, wenn Werte zwischen unterschiedlichen Systemen oder Komponenten ausgetauscht werden müssen, die unterschiedliche Datentypen verwenden.

![F_INT_TO_ULINT](F_INT_TO_ULINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Eingabewertes. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung und gibt den konvertierten Wert über den Daten-Ausgang `OUT` aus.

### **Daten-Eingänge**
- **IN**: Der Eingabewert vom Datentyp `INT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgabewert vom Datentyp `ULINT`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Der Algorithmus innerhalb des Funktionsblocks wandelt den `INT`-Wert am Eingang `IN` in einen `ULINT`-Wert um und stellt das Ergebnis am Ausgang `OUT` bereit. Die erfolgreiche Konvertierung wird durch das Auslösen des Ereignisses `CNF` signalisiert.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Funktionsblock ist für die Verwendung in Echtzeitsystemen geeignet.
- Die Implementierung erfolgt gemäß dem IEC 61131-3 Standard.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem Empfang des `REQ`-Ereignisses durchgeführt.

## Anwendungsszenarien
- Konvertierung von Sensorwerten für die Verarbeitung in Systemen, die `ULINT`-Werte erfordern.
- Integration von Komponenten, die unterschiedliche Datentypen verwenden.
- Verwendung in Steuerungssystemen, die eine Typumwandlung benötigen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_DINT_TO_ULINT` oder `F_SINT_TO_ULINT` ist dieser Funktionsblock speziell für die Konvertierung von `INT` zu `ULINT` optimiert.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Fehlerbehandlung bieten, was dieser Funktionsblock nicht tut.

## Fazit
Der Funktionsblock `F_INT_TO_ULINT` ist ein einfacher und effizienter Baustein zur Konvertierung von `INT`-Werten in `ULINT`-Werte. Er ist besonders in Szenarien nützlich, wo eine direkte und schnelle Typumwandlung benötigt wird. Die klare Schnittstellenstruktur und die einfache Funktionsweise machen ihn zu einem zuverlässigen Werkzeug in der Automatisierungstechnik.
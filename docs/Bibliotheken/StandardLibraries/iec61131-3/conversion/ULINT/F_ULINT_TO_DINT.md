# F_ULINT_TO_DINT

```{index} single: F_ULINT_TO_DINT
```

<img width="1453" height="214" alt="F_ULINT_TO_DINT" src="https://github.com/user-attachments/assets/0a9c4fad-0e7e-45ea-a121-a14bf7015759" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_DINT` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsignierte Ganzzahl) in einen `DINT`-Wert (32-Bit signierte Ganzzahl). Diese Konvertierung ist besonders in Szenarien relevant, in denen Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen.

![F_ULINT_TO_DINT](F_ULINT_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`ULINT`): Der unsignierte 64-Bit Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`DINT`): Das Ergebnis der Konvertierung als signierter 32-Bit Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Bei Aktivierung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `ULINT`-Wert am Eingang `IN` in einen `DINT`-Wert konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche `ULINT`-Wert außerhalb des darstellbaren Bereichs von `DINT` liegt (d.h. größer als 2³¹-1 ist).
- Der Funktionsblock ist Teil des `iec61131::conversion`-Pakets.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Eingang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Datentypen verwenden.
- Integration von Systemen, die unterschiedliche Bitbreiten für Ganzzahlen verwenden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_ULINT_TO_DINT` spezialisiert auf die Konvertierung von `ULINT` zu `DINT`.
- Andere Konvertierungsblöcke könnten andere Datentypen oder Konvertierungsrichtungen unterstützen.

## Fazit
Der `F_ULINT_TO_DINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, unsignierte 64-Bit Werte in signierte 32-Bit Werte zu konvertieren. Seine Verwendung ist in Szenarien mit unterschiedlichen Datentypanforderungen sinnvoll, jedoch sollte auf mögliche Datenverluste bei der Konvertierung geachtet werden.
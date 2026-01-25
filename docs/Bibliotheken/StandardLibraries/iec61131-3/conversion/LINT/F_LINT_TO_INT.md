# F_LINT_TO_INT

```{index} single: F_LINT_TO_INT
```

<img width="1421" height="214" alt="F_LINT_TO_INT" src="https://github.com/user-attachments/assets/59a9a468-b60b-4e33-9018-cc20619801a8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_INT` dient zur Konvertierung eines 64-Bit Integer-Werts (LINT) in einen 16-Bit Integer-Wert (INT). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht oder verarbeitet werden müssen.

![F_LINT_TO_INT](F_LINT_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (LINT): Der 64-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (INT): Der resultierende 16-Bit Integer-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von einem LINT- zu einem INT-Wert durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt durch die Funktion `LINT_TO_INT(IN)`, die den Wert von `IN` in einen INT-Wert umwandelt und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um die erfolgreiche Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche LINT-Wert außerhalb des darstellbaren Bereichs eines INT-Werts (-32.768 bis 32.767) liegt.
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Führt die Konvertierung durch und gibt das Ergebnis aus.
3. **Bestätigungszustand**: Sendet das Ereignis `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenkommunikation zwischen Systemen mit unterschiedlicher Wortbreite.
- Reduzierung der Speicherbelegung, wenn die volle 64-Bit-Präzision nicht benötigt wird.
- Integration in Steuerungssysteme, die nur 16-Bit-Integer verarbeiten können.

## Vergleich mit ähnlichen Bausteinen
- **F_LINT_TO_DINT**: Konvertiert LINT zu DINT (32-Bit Integer).
- **F_LINT_TO_UDINT**: Konvertiert LINT zu UDINT (32-Bit vorzeichenloser Integer).
- **F_LINT_TO_ULINT**: Konvertiert LINT zu ULINT (64-Bit vorzeichenloser Integer).

## Fazit
Der `F_LINT_TO_INT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit Integer-Werte in 16-Bit Integer-Werte umzuwandeln. Er ist besonders nützlich in Szenarien, wo die Reduzierung der Datenbreite notwendig ist, jedoch sollte die Möglichkeit eines Datenverlusts bei der Konvertierung beachtet werden.
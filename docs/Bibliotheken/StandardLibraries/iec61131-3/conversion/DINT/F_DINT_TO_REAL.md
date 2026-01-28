# F_DINT_TO_REAL

```{index} single: F_DINT_TO_REAL
```

<img width="1437" height="217" alt="F_DINT_TO_REAL" src="https://github.com/user-attachments/assets/9a171061-0724-4ae7-ae31-84f0ef970859" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_REAL` dient der Konvertierung eines ganzzahligen Wertes vom Typ `DINT` in einen Fließkommawert vom Typ `REAL`. Diese Konvertierung ist in vielen Steuerungs- und Automatisierungsanwendungen notwendig, wenn Daten zwischen verschiedenen Systemen oder Komponenten ausgetauscht werden müssen.

![F_DINT_TO_REAL](F_DINT_TO_REAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DINT`, der in einen `REAL`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `REAL`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus `REQ` wandelt den Eingangswert `IN` vom Typ `DINT` in einen `REAL`-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient implementiert, ohne zusätzliche Zustände oder komplexe Logik.
- Die Konvertierung erfolgt direkt durch die Funktion `DINT_TO_REAL`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt sofort bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von ganzzahligen Sensorwerten in Fließkommawerte für weitere Berechnungen.
- Datenkonvertierung zwischen Systemen, die unterschiedliche Datentypen verwenden.
- Integration in Steuerungsalgorithmen, die Fließkommawerte erfordern.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_REAL**: Konvertiert `INT` zu `REAL`, hat aber einen kleineren Eingangsbereich im Vergleich zu `DINT`.
- **F_LINT_TO_REAL**: Konvertiert `LINT` zu `REAL`, hat einen größeren Eingangsbereich, ist aber in den meisten Fällen nicht notwendig, wenn `DINT` ausreicht.

## Fazit
Der Funktionsblock `F_DINT_TO_REAL` ist ein einfaches und effizientes Werkzeug zur Konvertierung von `DINT`-Werten in `REAL`-Werte. Er ist besonders nützlich in Anwendungen, bei denen Daten zwischen verschiedenen Systemen oder Komponenten mit unterschiedlichen Datentypen ausgetauscht werden müssen. Die direkte und zustandslose Implementierung macht ihn zuverlässig und leicht integrierbar.
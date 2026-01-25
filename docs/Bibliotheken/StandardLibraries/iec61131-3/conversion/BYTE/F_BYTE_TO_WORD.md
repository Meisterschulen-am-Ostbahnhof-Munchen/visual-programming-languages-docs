# F_BYTE_TO_WORD

```{index} single: F_BYTE_TO_WORD
```

<img width="1232" height="182" alt="F_BYTE_TO_WORD" src="https://github.com/user-attachments/assets/895b5f0c-a270-44f1-9dab-26aed65b0089" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_WORD` dient der Konvertierung eines `BYTE`-Datentyps in einen `WORD`-Datentyp. Diese Konvertierung ist nützlich, wenn Daten in verschiedenen Größen verarbeitet oder weitergegeben werden müssen.

![F_BYTE_TO_WORD](F_BYTE_TO_WORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `BYTE`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `WORD`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BYTE` zu `WORD` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `BYTE_TO_WORD(IN)`, die den Eingangswert `IN` in den entsprechenden `WORD`-Wert umwandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert den Abschluss der Operation.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis durchgeführt und das Ergebnis sofort ausgegeben.

## Anwendungsszenarien
- **Datenkonvertierung**: Wenn ein `BYTE`-Wert in einem System verarbeitet werden muss, das `WORD`-Werte erwartet.
- **Schnittstellenanpassung**: Bei der Kommunikation zwischen Systemen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_BYTE**: Führt die umgekehrte Konvertierung durch, von `WORD` zu `BYTE`.
- **F_BYTE_TO_INT**: Konvertiert `BYTE` zu `INT`, was eine andere Art der Datentypumwandlung darstellt.

## Fazit
Der `F_BYTE_TO_WORD`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `BYTE`- zu `WORD`-Werten. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen schnelle und unkomplizierte Datentypkonvertierungen erforderlich sind.
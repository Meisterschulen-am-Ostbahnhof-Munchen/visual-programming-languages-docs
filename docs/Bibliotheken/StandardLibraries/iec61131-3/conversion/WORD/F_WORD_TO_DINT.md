# F_WORD_TO_DINT

```{index} single: F_WORD_TO_DINT
```

<img width="1439" height="214" alt="F_WORD_TO_DINT" src="https://github.com/user-attachments/assets/b1305cee-de08-4bea-9af0-84521b8ee895" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WORD_TO_DINT` dient der Konvertierung eines `WORD`-Datentyps in einen `DINT`-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist, z.B. bei der Verarbeitung von Daten aus verschiedenen Quellen oder bei der Anpassung von Daten für unterschiedliche Systemkomponenten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Eingang löst die Konvertierung aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieser Ausgang signalisiert den Abschluss der Konvertierung. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingangsvariable vom Typ `WORD`, die den zu konvertierenden Wert enthält.

### **Daten-Ausgänge**
- **OUT**: Ausgangsvariable vom Typ `DINT`, die das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock `F_WORD_TO_DINT` führt die Konvertierung von einem `WORD`- zu einem `DINT`-Datentyp durch. Bei Auslösung des `REQ`-Ereignisses wird der Wert am Eingang `IN` gelesen und mit der Funktion `WORD_TO_DINT` konvertiert. Das Ergebnis wird an den Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den Abschluss der Operation.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung, sobald das `REQ`-Ereignis eintrifft.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Typumwandlung in Steuerungssystemen, bei denen Daten unterschiedlicher Typen verarbeitet werden müssen.
- Integration von Komponenten, die unterschiedliche Datentypen verwenden.
- Datenaufbereitung für weitere Verarbeitungsschritte.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_TO_REAL` oder `F_BOOL_TO_BYTE` ist `F_WORD_TO_DINT` spezifisch auf die Umwandlung von `WORD` zu `DINT` ausgelegt.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht der Fall ist.

## Fazit
Der Funktionsblock `F_WORD_TO_DINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von `WORD`- zu `DINT`-Werten. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen, bei denen solche Typumwandlungen erforderlich sind.
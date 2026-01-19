# F_TIME_AS_WSTRING

```{index} single: F_TIME_AS_WSTRING
```

<img width="1479" height="212" alt="F_TIME_AS_WSTRING" src="https://github.com/user-attachments/assets/ed6f36e7-4f40-4837-a19d-4f35b3fbce62" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_AS_WSTRING` dient der Konvertierung eines TIME-Wertes in einen WSTRING-Wert. Dies ist besonders nützlich, wenn Zeitwerte für die Anzeige oder Protokollierung in einer menschenlesbaren Form benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsaufruf. Wird dieser Eingang ausgelöst, führt der Funktionsblock die Konvertierung durch.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der Ausführung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingang für den TIME-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten WSTRING-Wert.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock konvertiert den eingehenden TIME-Wert (`IN`) in einen WSTRING-Wert (`OUT`), sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `TIME_AS_WSTRING`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.

## Zustandsübersicht
Der Funktionsblock hat keine komplexen Zustände. Er reagiert auf das `REQ`-Ereignis mit der Ausführung des Algorithmus und bestätigt die Ausführung mit dem `CNF`-Ereignis.

## Anwendungsszenarien
- Anzeige von Zeitwerten in Benutzeroberflächen.
- Protokollierung von Zeitstempeln in lesbarer Form.
- Integration in Systeme, die Zeitwerte als Zeichenketten benötigen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_TIME_AS_WSTRING` spezialisiert auf die Umwandlung von TIME zu WSTRING.
- Andere Bausteine könnten zusätzliche Formatierungsoptionen bieten, dieser Baustein ist jedoch einfach und effizient.

## Fazit
Der `F_TIME_AS_WSTRING` Funktionsblock ist ein einfaches und effektives Werkzeug zur Konvertierung von TIME-Werten in WSTRING. Er eignet sich besonders für Anwendungen, bei denen Zeitwerte in einer lesbaren Form dargestellt oder weiterverarbeitet werden müssen.
# F_BYTE_TO_ULINT

<img width="1451" height="212" alt="F_BYTE_TO_ULINT" src="https://github.com/user-attachments/assets/d4e7fc4c-195c-4c12-b30d-9326c5eea4de" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_TO_ULINT` dient der Konvertierung eines `BYTE`-Wertes in einen `ULINT`-Wert. Diese Konvertierung ist insbesondere in Szenarien nützlich, in denen Daten unterschiedlicher Größe verarbeitet oder weitergegeben werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Ausführung des Funktionsblocks aus. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `BYTE`-Wert, der in einen `ULINT`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `ULINT`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BYTE` nach `ULINT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mithilfe der Funktion `BYTE_TO_ULINT`, die den Eingabewert `IN` in den entsprechenden `ULINT`-Wert umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar nach Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungsanwendungen, wo `BYTE`-Werte in größere Datentypen wie `ULINT` umgewandelt werden müssen.
- Integration in größere Systeme, die eine einheitliche Datenverarbeitung in `ULINT` erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_WORD_TO_ULINT` oder `F_DWORD_TO_ULINT` führen Konvertierungen von anderen Datentypen nach `ULINT` durch. Der `F_BYTE_TO_ULINT` ist spezifisch für die Konvertierung von `BYTE`.

## Fazit
Der `F_BYTE_TO_ULINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, `BYTE`-Werte in `ULINT`-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem nützlichen Baustein in der Automatisierungstechnik.

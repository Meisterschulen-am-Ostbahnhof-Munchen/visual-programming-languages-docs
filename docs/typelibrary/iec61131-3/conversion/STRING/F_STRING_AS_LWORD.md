# F_STRING_AS_LWORD

<img width="1478" height="213" alt="F_STRING_AS_LWORD" src="https://github.com/user-attachments/assets/e11ef5e8-2080-4d17-b504-b066c795a15d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_LWORD` dient der Konvertierung eines `STRING`-Werts in einen `LWORD`-Wert. Er ist Teil des `iec61131::conversion`-Pakets und ermöglicht die einfache Umwandlung zwischen diesen beiden Datentypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`STRING`): Der Eingangsstring, der in einen `LWORD`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`LWORD`): Der konvertierte `LWORD`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung aus, wenn das Ereignis `REQ` empfangen wird. Dabei wird der Eingangsstring `IN` mit der Funktion `STRING_AS_LWORD` in einen `LWORD`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Block ist als einfacher Funktionsblock (`SimpleFB`) implementiert, der nur einen Algorithmus enthält.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Umwandlung von String-Daten in `LWORD`-Werte für die weitere Verarbeitung in Steuerungssystemen.
- Integration in Systeme, die `LWORD`-Werte erfordern, aber String-Eingaben erhalten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_STRING_AS_LWORD` spezialisiert auf die Umwandlung von `STRING` zu `LWORD`.
- Andere Bausteine wie `F_STRING_TO_*` könnten ähnliche Funktionen für andere Datentypen bieten.

## Fazit
Der `F_STRING_AS_LWORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, String-Daten in `LWORD`-Werte umzuwandeln. Er ist besonders nützlich in Szenarien, wo solche Konvertierungen regelmäßig benötigt werden.

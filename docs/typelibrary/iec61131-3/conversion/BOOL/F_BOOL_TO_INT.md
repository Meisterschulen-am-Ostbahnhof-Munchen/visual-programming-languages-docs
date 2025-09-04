# F_BOOL_TO_INT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_INT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen ganzzahligen Wert (`INT`). Dabei wird `TRUE` in `1` und `FALSE` in `0` umgewandelt. Der Block ist besonders nützlich in Szenarien, wo boolesche Logik in numerische Berechnungen integriert werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der boolesche Wert (`BOOL`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte ganzzahlige Wert (`INT`). `TRUE` wird zu `1` und `FALSE` zu `0`.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der boolesche Wert am Eingang `IN` gelesen und in einen ganzzahligen Wert umgewandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Block ist ein einfacher Funktionsblock (`SimpleFB`) ohne interne Zustände.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Integration von boolescher Logik in numerische Steuerungen.
- Umwandlung von Schaltzuständen (`TRUE`/`FALSE`) in numerische Werte für weitere Berechnungen.
- Verwendung in Regelungstechnik, wo boolesche Signale in numerische Steuersignale umgewandelt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **F_BOOL_TO_REAL**: Konvertiert `BOOL` in `REAL` (Gleitkommazahl), ähnlich wie `F_BOOL_TO_INT`, aber mit Gleitkomma-Ausgabe.
- **F_INT_TO_BOOL**: Führt die umgekehrte Konvertierung durch (`INT` zu `BOOL`).

## Fazit
Der `F_BOOL_TO_INT`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung von booleschen Werten in ganzzahlige Werte. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und unkomplizierte Umwandlung erfordern.
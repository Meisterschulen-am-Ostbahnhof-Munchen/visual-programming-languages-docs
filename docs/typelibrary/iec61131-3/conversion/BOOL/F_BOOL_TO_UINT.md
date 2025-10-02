# F_BOOL_TO_UINT

<img width="1230" height="183" alt="F_BOOL_TO_UINT" src="https://github.com/user-attachments/assets/0ed51abc-df99-4646-bb36-6243ba00a996" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_UINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen vorzeichenlosen Integerwert (`UINT`). Diese Konvertierung ist besonders nützlich, wenn boolesche Signale in numerische Werte umgewandelt werden müssen, z.B. für weitere Berechnungen oder Steuerungszwecke.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der boolesche Eingangswert (`BOOL`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte vorzeichenlose Integerwert (`UINT`).

### **Adapter**
- Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den booleschen Wert `IN` in einen vorzeichenlosen Integerwert `OUT` umwandelt. Die Konvertierung erfolgt gemäß der folgenden Regel:
- `FALSE` wird zu `0`
- `TRUE` wird zu `1`

Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und führt die Konvertierung in einem einzigen Algorithmus durch.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- Umwandlung von booleschen Sensordaten in numerische Werte für weitere Verarbeitung.
- Integration in Steuerungssysteme, die numerische Werte anstelle von booleschen Werten erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_BOOL_TO_INT` oder `F_BOOL_TO_REAL` bieten Konvertierungen in andere Datentypen, aber `F_BOOL_TO_UINT` ist speziell für vorzeichenlose Integerwerte optimiert.

## Fazit
Der `F_BOOL_TO_UINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von booleschen Werten in vorzeichenlose Integerwerte. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungs- und Automatisierungssystemen.

# F_DINT_TO_UINT

<img width="1442" height="217" alt="F_DINT_TO_UINT" src="https://github.com/user-attachments/assets/19436375-bd4c-4e93-ad90-b387e008a9c2" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_UINT` dient der Konvertierung eines 32-Bit Integer-Wertes (DINT) in einen vorzeichenlosen 32-Bit Integer-Wert (UINT). Dieser Block ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `UINT`, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DINT` zu `UINT` durch, wenn das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der eingebauten Funktion `DINT_TO_UINT`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst und der konvertierte Wert über den Ausgang `OUT` ausgegeben.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Block unterstützt keine Fehlerbehandlung für ungültige Eingabewerte.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Konvertierung**: Führt die Konvertierung durch und gibt das Ergebnis über `OUT` aus, gefolgt von einem `CNF`-Ereignis.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo vorzeichenbehaftete Werte in vorzeichenlose Werte umgewandelt werden müssen.
- Datenverarbeitung in industriellen Automatisierungssystemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_DINT_TO_UINT` spezialisiert auf die Umwandlung zwischen `DINT` und `UINT` und bietet daher eine einfachere und direktere Lösung für diesen spezifischen Anwendungsfall.

## Fazit
Der `F_DINT_TO_UINT` Funktionsblock ist ein effizientes Werkzeug für die spezifische Konvertierung zwischen `DINT` und `UINT` Datentypen. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Typumwandlung erfordern.

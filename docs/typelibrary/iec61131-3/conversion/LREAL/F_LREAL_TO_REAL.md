# F_LREAL_TO_REAL

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_REAL` dient der Konvertierung eines LREAL-Wertes (64-Bit Fließkommazahl) in einen REAL-Wert (32-Bit Fließkommazahl). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden numerischen Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ LREAL, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ REAL, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` vom Typ LREAL in einen REAL-Wert konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock führt eine direkte Typumwandlung durch, wobei mögliche Genauigkeitsverluste aufgrund der unterschiedlichen Bitbreiten der Datentypen zu beachten sind.
- Die Konvertierung erfolgt mittels der eingebauten Funktion `LREAL_TO_REAL`.

## Zustandsübersicht
Der Funktionsblock ist zustandslos und führt bei jedem `REQ`-Ereignis die Konvertierung durch.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo LREAL-Werte aus hochpräzisen Berechnungen in REAL-Werte für weitere Verarbeitungsschritte umgewandelt werden müssen.
- Kompatibilität mit Systemen oder Bausteinen, die nur REAL-Datentypen verarbeiten können.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_LREAL_TO_REAL` spezialisiert auf die Umwandlung zwischen LREAL und REAL und bietet daher eine klar definierte und effiziente Lösung für diesen spezifischen Anwendungsfall.

## Fazit
Der `F_LREAL_TO_REAL` Funktionsblock ist ein einfacher, aber effektiver Baustein für die Konvertierung zwischen LREAL- und REAL-Datentypen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen, wo solche Typumwandlungen erforderlich sind.
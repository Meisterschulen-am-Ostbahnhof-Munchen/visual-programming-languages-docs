# F_LINT_TO_ULINT

```{index} single: F_LINT_TO_ULINT
```

<img width="1448" height="214" alt="F_LINT_TO_ULINT" src="https://github.com/user-attachments/assets/ad56b68e-ba86-4df1-ada2-b318dda134f6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_ULINT` dient der Konvertierung eines vorzeichenbehafteten 64-Bit-Integer-Werts (`LINT`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`ULINT`). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Konvertierung aus. Er ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Dieser Ausgang signalisiert den Abschluss der Konvertierung. Er ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`LINT`): Der vorzeichenbehaftete 64-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`ULINT`): Der vorzeichenlose 64-Bit-Integer-Wert, der als Ergebnis der Konvertierung ausgegeben wird.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `LINT` zu `ULINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `LINT_TO_ULINT(IN)`, die den Wert von `IN` in den entsprechenden vorzeichenlosen Typ umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Baustein ohne interne Zustandsverwaltung.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo vorzeichenbehaftete und vorzeichenlose Werte verarbeitet werden müssen.
- Datenverarbeitung in industriellen Automatisierungssystemen, wo unterschiedliche Datentypen kompatibel gemacht werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine könnten `F_INT_TO_UINT` oder `F_DINT_TO_UDINT` sein, die jedoch für kleinere Integer-Typen konzipiert sind.
- Im Gegensatz zu generischen Konvertierungsbausteinen ist `F_LINT_TO_ULINT` spezialisiert auf die 64-Bit-Varianten der Datentypen.

## Fazit
Der `F_LINT_TO_ULINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenbehaftete 64-Bit-Integer-Werte in vorzeichenlose umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einem zuverlässigen Werkzeug in der industriellen Automatisierung.
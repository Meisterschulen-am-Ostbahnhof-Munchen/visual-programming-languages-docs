# F_TIME_IN_US_TO_UDINT

```{index} single: F_TIME_IN_US_TO_UDINT
```

<img width="1536" height="212" alt="F_TIME_IN_US_TO_UDINT" src="https://github.com/user-attachments/assets/4ae404ca-902a-488d-8a1e-3385150b6d56" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_US_TO_UDINT` dient der Konvertierung eines TIME-Werts in Mikrosekunden (µs) in einen UDINT-Wert. Diese Konvertierung ist insbesondere in Anwendungen nützlich, bei denen Zeitwerte in numerischer Form weiterverarbeitet werden müssen.

![F_TIME_IN_US_TO_UDINT](F_TIME_IN_US_TO_UDINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang vom Typ `TIME`, der den zu konvertierenden Zeitwert in Mikrosekunden enthält.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang vom Typ `UDINT`, der das Ergebnis der Konvertierung enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock konvertiert den an `IN` übergebenen TIME-Wert (in µs) in einen UDINT-Wert. Die Konvertierung erfolgt durch den Aufruf der Funktion `TIME_IN_US_TO_UDINT(IN)`. Nach erfolgreicher Konvertierung wird das Ergebnis an `OUT` ausgegeben und das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus (`REQ`), der die Konvertierung durchführt.
- Es gibt keine Zustandsmaschine oder komplexe Logik, da der Block ausschließlich für die Konvertierung zuständig ist.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -maschinen. Der Block führt die Konvertierung bei jedem `REQ`-Ereignis durch und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Zeitmessung und -verarbeitung in Steuerungssystemen.
- Umwandlung von Zeitwerten für die Speicherung oder Übertragung in numerischer Form.
- Integration in Systeme, die Zeitwerte in µs als UDINT verarbeiten müssen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_TIME_IN_US_TO_UDINT` spezialisiert auf die Umwandlung von TIME in UDINT.
- Ähnliche Blöcke könnten andere Zeitformate oder andere Ziel-Datentypen unterstützen, z.B. TIME in REAL oder TIME in STRING.

## Fazit
Der Funktionsblock `F_TIME_IN_US_TO_UDINT` bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Mikrosekunden in UDINT-Werte umzuwandeln. Durch seinen schlanken Aufbau ist er besonders für Anwendungen geeignet, bei denen Performance und Einfachheit im Vordergrund stehen.
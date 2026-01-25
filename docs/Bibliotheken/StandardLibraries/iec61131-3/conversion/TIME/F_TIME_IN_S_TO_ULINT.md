# F_TIME_IN_S_TO_ULINT

```{index} single: F_TIME_IN_S_TO_ULINT
```

<img width="1520" height="212" alt="F_TIME_IN_S_TO_ULINT" src="https://github.com/user-attachments/assets/60c0a628-bf00-4bf4-b81c-1397cad4dd61" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_ULINT` dient der Konvertierung eines TIME-Werts in Sekunden in einen ULINT-Wert. Dies ist besonders nützlich, wenn Zeitwerte in numerische Formate umgewandelt werden müssen, um sie in Berechnungen oder für weitere Verarbeitungsschritte zu verwenden.

![F_TIME_IN_S_TO_ULINT](F_TIME_IN_S_TO_ULINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungs-Event. Dieser Event löst die Konvertierung aus und ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgreicher Ausführung. Dieser Event wird zusammen mit dem Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Eingang vom Typ `TIME`, der den zu konvertierenden Zeitwert in Sekunden enthält.

### **Daten-Ausgänge**
- **OUT**: Ausgang vom Typ `ULINT`, der den konvertierten numerischen Wert enthält.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den TIME-Wert (in Sekunden) in einen ULINT-Wert umwandelt. Die Konvertierung erfolgt bei Auftreten des `REQ`-Events, und das Ergebnis wird über den `OUT`-Ausgang ausgegeben, begleitet vom `CNF`-Event.

## Technische Besonderheiten
- Der Funktionsblock verwendet den Standardalgorithmus `TIME_IN_S_TO_ULINT` für die Konvertierung.
- Der FB ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auftreten des `REQ`-Events.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungssysteme, die Zeitwerte in numerischer Form verarbeiten müssen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser FB spezialisiert auf die Umwandlung von TIME in ULINT.
- Andere Blöcke könnten unterschiedliche Ausgabetypen oder zusätzliche Funktionen bieten, wie z.B. die Umwandlung in andere numerische Formate.

## Fazit
Der `F_TIME_IN_S_TO_ULINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in numerische ULINT-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die solche Konvertierungen erfordern.
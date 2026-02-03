# F_TIME_IN_NS_TO_ULINT

```{index} single: F_TIME_IN_NS_TO_ULINT
```

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_ULINT" src="https://github.com/user-attachments/assets/8f77a80e-b99a-4045-87db-8e4bb1e7fc74" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_ULINT` dient der Konvertierung eines `TIME`-Werts in Nanosekunden in einen `ULINT`-Wert. Diese Konvertierung ist besonders nützlich, wenn Zeitwerte in numerischen Berechnungen oder für weitere Verarbeitungsschritte benötigt werden.

![F_TIME_IN_NS_TO_ULINT](F_TIME_IN_NS_TO_ULINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `TIME`-Wert in Nanosekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten `ULINT`-Wert aus.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des `TIME`-Werts in Nanosekunden (`IN`) in einen `ULINT`-Wert (`OUT`) durch, sobald das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mithilfe der Funktion `TIME_IN_NS_TO_ULINT`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung ist direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungssysteme, wo Zeitwerte als numerische Werte weiterverarbeitet werden müssen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell auf die Umwandlung von `TIME` in `ULINT` ausgelegt.
- Ähnliche Bausteine könnten andere Datentypen oder Einheiten verwenden, dieser ist jedoch auf Nanosekunden optimiert.

## Fazit
Der `F_TIME_IN_NS_TO_ULINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Nanosekunden in `ULINT`-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem nützlichen Baustein in der Automatisierungstechnik.
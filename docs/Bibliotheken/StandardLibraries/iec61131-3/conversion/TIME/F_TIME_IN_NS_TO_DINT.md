# F_TIME_IN_NS_TO_DINT

```{index} single: F_TIME_IN_NS_TO_DINT
```

<img width="1528" height="212" alt="F_TIME_IN_NS_TO_DINT" src="https://github.com/user-attachments/assets/1bf1ef7f-a9cc-4407-a8c7-72c2401edce4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_DINT` dient zur Konvertierung eines TIME-Werts in Nanosekunden in einen DINT-Wert. Diese Konvertierung ist nützlich, wenn Zeitwerte in numerischen Berechnungen oder für weitere Verarbeitungsschritte benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (TIME): Der Eingang für den Zeitwert in Nanosekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DINT): Der Ausgang für den konvertierten numerischen Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt bei einem eingehenden `REQ`-Ereignis die Konvertierung des TIME-Werts `IN` in einen DINT-Wert `OUT` durch. Die Konvertierung erfolgt mittels der Funktion `TIME_IN_NS_TO_DINT`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
1. **Warten auf REQ**: Der Funktionsblock wartet auf ein eingehendes `REQ`-Ereignis.
2. **Konvertierung**: Bei `REQ` wird der TIME-Wert `IN` in DINT konvertiert.
3. **Ausgabe**: Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungssysteme, wo Zeitwerte als numerische Werte benötigt werden.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist `F_TIME_IN_NS_TO_DINT` spezialisiert auf die Umwandlung von TIME in DINT.
- Ähnliche Bausteine könnten andere Datentypen oder zusätzliche Funktionen bieten, wie z.B. Skalierung oder Filterung.

## Fazit
Der Funktionsblock `F_TIME_IN_NS_TO_DINT` bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Nanosekunden in numerische DINT-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, wo Zeitwerte in Berechnungen oder Steuerungslogiken integriert werden müssen.

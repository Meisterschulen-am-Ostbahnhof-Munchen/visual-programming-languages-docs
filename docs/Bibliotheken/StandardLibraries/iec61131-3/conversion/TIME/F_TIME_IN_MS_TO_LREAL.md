# F_TIME_IN_MS_TO_LREAL

```{index} single: F_TIME_IN_MS_TO_LREAL
```

<img width="1520" height="212" alt="F_TIME_IN_MS_TO_LREAL" src="https://github.com/user-attachments/assets/fd32035d-3e73-424b-9bef-32b3ce7a10d8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_MS_TO_LREAL` dient zur Konvertierung eines TIME-Werts in Millisekunden in einen LREAL-Wert. Dies ist besonders nützlich, wenn Zeitwerte für weitere Berechnungen oder Analysen in einer höheren Präzision benötigt werden.

![F_TIME_IN_MS_TO_LREAL](F_TIME_IN_MS_TO_LREAL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingangsvariable vom Typ `TIME`. Der zu konvertierende Zeitwert in Millisekunden.

### **Daten-Ausgänge**
- **OUT**: Ausgangsvariable vom Typ `LREAL`. Der konvertierte Wert als Gleitkommazahl.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der eingehende TIME-Wert in Millisekunden in einen LREAL-Wert umgewandelt wird. Die Konvertierung erfolgt über den Algorithmus `REQ`, der die Funktion `TIME_IN_MS_TO_LREAL` verwendet.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für präzise Berechnungen.
- Integration in Steuerungssysteme, die Gleitkommawerte für Zeitmessungen benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell auf die Umwandlung von TIME in LREAL ausgelegt und bietet daher eine einfache und direkte Lösung für diesen Anwendungsfall.

## Fazit
Der `F_TIME_IN_MS_TO_LREAL` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von Zeitwerten in Millisekunden in Gleitkommazahlen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungssystemen.
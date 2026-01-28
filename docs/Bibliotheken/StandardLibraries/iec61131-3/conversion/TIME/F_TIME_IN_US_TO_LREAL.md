# F_TIME_IN_US_TO_LREAL

```{index} single: F_TIME_IN_US_TO_LREAL
```

<img width="1536" height="212" alt="F_TIME_IN_US_TO_LREAL" src="https://github.com/user-attachments/assets/ece70afa-d5af-4a67-a95e-e1c2a79fc167" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_US_TO_LREAL` dient zur Konvertierung eines Zeitwertes in Mikrosekunden (`TIME`) in eine Fließkommazahl mit doppelter Genauigkeit (`LREAL`). Diese Umwandlung ist insbesondere in Steuerungsanwendungen nützlich, wo Zeitwerte für weitere Berechnungen benötigt werden.

![F_TIME_IN_US_TO_LREAL](F_TIME_IN_US_TO_LREAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Auslöser für die Konvertierung. Bei diesem Ereignis wird der Eingangswert `IN` verarbeitet und das Ergebnis an `OUT` ausgegeben.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (`TIME`): Der Eingangswert in Mikrosekunden, der in einen `LREAL`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT** (`LREAL`): Der konvertierte Wert als Fließkommazahl mit doppelter Genauigkeit.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `TIME`-Eingangswert `IN` mittels der Funktion `TIME_IN_US_TO_LREAL` in einen `LREAL`-Wert umwandelt. Das Ergebnis wird an den Ausgang `OUT` übergeben und durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Funktionsblock ist für Echtzeitanwendungen optimiert und unterstützt präzise Zeitmessungen.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem Auftreten des `REQ`-Ereignisses durchgeführt.

## Anwendungsszenarien
- Umwandlung von Zeitdauern für mathematische Berechnungen.
- Integration in Steuerungssysteme, die Fließkommawerte für Regelungsalgorithmen benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser Funktionsblock spezialisiert auf die Umwandlung von `TIME` in `LREAL` und bietet daher eine optimierte Leistung.
- Andere Blöcke könnten zusätzliche Parameter oder Zustände besitzen, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_US_TO_LREAL`-Funktionsblock ist ein effizientes Werkzeug zur präzisen Konvertierung von Zeitwerten in Fließkommazahlen. Seine einfache und direkte Funktionsweise macht ihn ideal für Anwendungen, die schnelle und genaue Umrechnungen erfordern.
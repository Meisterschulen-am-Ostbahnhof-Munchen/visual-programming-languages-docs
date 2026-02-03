# F_TIME_IN_US_TO_DINT

```{index} single: F_TIME_IN_US_TO_DINT
```

<img width="1520" height="212" alt="F_TIME_IN_US_TO_DINT" src="https://github.com/user-attachments/assets/f69e17a7-e3ae-4ca9-ac0d-e8c66d9c31ce" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_US_TO_DINT` dient zur Konvertierung eines TIME-Wertes in Mikrosekunden (µs) in einen DINT-Wert. Diese Konvertierung ist insbesondere dann nützlich, wenn Zeitwerte in numerischen Berechnungen oder für Steuerungszwecke verwendet werden sollen.

![F_TIME_IN_US_TO_DINT](F_TIME_IN_US_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei diesem Ereignis wird der Eingangswert `IN` verarbeitet und das Ergebnis am Ausgang `OUT` ausgegeben.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `TIME`, der in Mikrosekunden angegeben ist und in einen DINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Wert vom Typ `DINT`, der das Ergebnis der Umwandlung des TIME-Wertes in Mikrosekunden darstellt.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der TIME-Wert in Mikrosekunden in einen DINT-Wert umgewandelt wird. Die Konvertierung erfolgt synchron mit dem Eintreffen des `REQ`-Ereignisses. Das Ergebnis wird sofort am Ausgang `OUT` ausgegeben und durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne Verzögerung.
- Der Funktionsblock ist für die Verwendung in Echtzeitanwendungen geeignet.
- Es werden keine zusätzlichen Parameter oder Konfigurationen benötigt.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Aktiv-Zustand**: Bei Eintreffen von `REQ` wird die Konvertierung durchgeführt und das Ergebnis ausgegeben.
3. **Bestätigungs-Zustand**: Das `CNF`-Ereignis wird ausgelöst, um die erfolgreiche Konvertierung zu signalisieren.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungsalgorithmen, die Zeitwerte in einer anderen Form benötigen.
- Verwendung in Systemen, die Zeitstempel oder Zeitdauern in Mikrosekunden verarbeiten.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist dieser Funktionsblock spezialisiert auf die Umwandlung von TIME in DINT.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Filterung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_US_TO_DINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von Zeitwerten in Mikrosekunden in einen DINT-Wert. Seine einfache Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und zuverlässige Umwandlung benötigen.
# F_TIME_IN_US_TO_LINT

<img width="1522" height="212" alt="F_TIME_IN_US_TO_LINT" src="https://github.com/user-attachments/assets/ec011268-cf2a-49c0-8b92-65bb95c903f0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_US_TO_LINT` dient der Konvertierung eines TIME-Wertes in Mikrosekunden (µs) in einen LINT-Wert (64-Bit Ganzzahl). Diese Konvertierung ist nützlich, wenn Zeitwerte in numerischen Berechnungen oder für weitere Verarbeitungsschritte benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung des Funktionsblocks. Wird mit dem Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den Abschluss der Konvertierung. Wird mit dem Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (TIME): Der Eingangswert in Mikrosekunden (µs), der in einen LINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- `OUT` (LINT): Der konvertierte 64-Bit Ganzzahlwert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den TIME-Eingangswert (`IN`) in Mikrosekunden in einen LINT-Wert (`OUT`) umwandelt. Die Konvertierung erfolgt bei Auslösung des `REQ`-Ereignisses und wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Algorithmus verwendet die Funktion `TIME_IN_US_TO_LINT`, um die Konvertierung durchzuführen.
- Der Funktionsblock ist für die Verwendung in Echtzeitanwendungen geeignet.

## Zustandsübersicht
Der Funktionsblock hat einen einfachen Zustandsautomaten:
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Ausführungszustand**: Führt die Konvertierung durch und löst das `CNF`-Ereignis aus.

## Anwendungsszenarien
- Zeitmessung und -verarbeitung in Steuerungssystemen.
- Integration von Zeitwerten in numerische Berechnungen.
- Protokollierung und Analyse von Zeitdauern.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell auf die Umwandlung von TIME in LINT optimiert.
- Ähnliche Bausteine könnten andere Datentypen oder Einheiten verwenden, z.B. Millisekunden statt Mikrosekunden.

## Fazit
Der `F_TIME_IN_US_TO_LINT` Funktionsblock bietet eine effiziente und zuverlässige Möglichkeit, Zeitwerte in Mikrosekunden in 64-Bit Ganzahlen umzuwandeln. Seine einfache Schnittstelle und klare Funktionsweise machen ihn ideal für eine Vielzahl von Anwendungen in der Automatisierungstechnik.

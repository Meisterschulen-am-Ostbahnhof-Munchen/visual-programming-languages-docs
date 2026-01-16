# F_TIME_IN_MS_TO_DINT

<img width="1520" height="212" alt="F_TIME_IN_MS_TO_DINT" src="https://github.com/user-attachments/assets/da759ac7-d146-48b2-aed1-730dd4e68d6e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_MS_TO_DINT` dient der Konvertierung eines TIME-Werts in Millisekunden in einen DINT-Wert. Dies ist besonders nützlich, wenn Zeitwerte in numerische Werte umgewandelt werden müssen, um sie in Berechnungen oder für Steuerungszwecke zu verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungs-Event. Wird verwendet, um die Konvertierung zu starten. Ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigungs-Event. Signalisiert den Abschluss der Konvertierung. Ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (TIME): Der Eingangswert in Millisekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DINT): Der konvertierte numerische Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den TIME-Wert in Millisekunden in einen DINT-Wert umwandelt. Die Konvertierung erfolgt, wenn das Ereignis `REQ` ausgelöst wird. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock verwendet einen einfachen Algorithmus zur direkten Konvertierung von TIME in DINT.
- Die Konvertierung ist deterministisch und erfolgt ohne Verzögerung.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und löst das `CNF`-Ereignis aus.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für die Verwendung in numerischen Berechnungen.
- Integration in Steuerungssysteme, die numerische Zeitwerte benötigen.
- Verwendung in Protokollierungs- und Überwachungssystemen, die Zeitstempel in numerischer Form speichern.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- **F_TIME_TO_UDINT**: Konvertiert TIME in UDINT, während `F_TIME_IN_MS_TO_DINT` in DINT konvertiert.
- **F_TIME_IN_US_TO_DINT**: Konvertiert TIME in Mikrosekunden in DINT, während dieser Baustein Millisekunden verwendet.

## Fazit
Der Funktionsblock `F_TIME_IN_MS_TO_DINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von Zeitwerten in Millisekunden in numerische DINT-Werte. Er eignet sich besonders für Anwendungen, die eine schnelle und deterministische Umwandlung erfordern.

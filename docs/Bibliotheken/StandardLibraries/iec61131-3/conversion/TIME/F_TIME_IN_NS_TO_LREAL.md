# F_TIME_IN_NS_TO_LREAL

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_LREAL" src="https://github.com/user-attachments/assets/c94f3148-26d5-44a8-88fc-e5eeb5938a75" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_LREAL` dient zur Konvertierung eines Zeitwertes in Nanosekunden (`TIME`) in einen Fließkommawert (`LREAL`). Diese Umwandlung ist insbesondere in Steuerungsanwendungen nützlich, wo Zeitwerte in mathematischen Berechnungen verwendet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert in Nanosekunden (`TIME`).

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Fließkommawert (`LREAL`) zurück.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung des Zeitwertes `IN` von Nanosekunden (`TIME`) in einen Fließkommawert (`LREAL`) durch. Die Umwandlung erfolgt bei jedem Auftreten des Ereignisses `REQ`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der Ergebniswert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist als einfacher FB (`SimpleFB`) implementiert.
- Die Konvertierung erfolgt mithilfe der eingebauten Funktion `TIME_IN_NS_TO_LREAL`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Zeitmessungen in Steuerungssystemen, die eine weitere Verarbeitung in mathematischen Ausdrücken erfordern.
- Integration in Regelkreise, wo Zeitwerte als Fließkommazahlen benötigt werden.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_TIME_IN_NS_TO_LREAL` speziell auf die Umwandlung von Zeitwerten in Nanosekunden zu Fließkommazahlen optimiert.
- Andere Blöcke wie `F_TIME_TO_LREAL` könnten eine ähnliche Funktionalität bieten, jedoch ohne die explizite Angabe der Nanosekunden-Einheit.

## Fazit
Der Funktionsblock `F_TIME_IN_NS_TO_LREAL` bietet eine effiziente und spezialisierte Lösung für die Konvertierung von Zeitwerten in Fließkommazahlen. Seine einfache Handhabung und direkte Integration machen ihn ideal für Anwendungen, die präzise Zeitverarbeitung erfordern.

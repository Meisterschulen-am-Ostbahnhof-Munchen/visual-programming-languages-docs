# F_TIME_IN_NS_TO_LINT

<img width="1521" height="212" alt="F_TIME_IN_NS_TO_LINT" src="https://github.com/user-attachments/assets/2aa3f00a-29f1-4cb9-944b-381d672567a3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_NS_TO_LINT` dient zur Konvertierung eines Zeitwerts in Nanosekunden (`TIME`) in einen 64-Bit-Ganzzahlwert (`LINT`). Diese Konvertierung ist nützlich, wenn Zeitwerte für Berechnungen oder Vergleiche in einer numerischen Form benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert vom Typ `TIME`, der in Nanosekunden angegeben ist.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten Wert als 64-Bit-Ganzzahl (`LINT`).

### **Adapter**
- Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den Zeitwert `IN` in Nanosekunden in einen `LINT`-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist als *SimpleFB* implementiert, was bedeutet, dass er keinen internen Zustand hat und bei jedem Aufruf von `REQ` neu ausgeführt wird.
- Die Konvertierung erfolgt direkt über die Funktion `TIME_IN_NS_TO_LINT`, die den `TIME`-Wert in einen `LINT`-Wert umwandelt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -maschinen.

## Anwendungsszenarien
- Zeitmessung und -verarbeitung in Steuerungssystemen, wo numerische Operationen auf Zeitwerten erforderlich sind.
- Integration in Systeme, die Zeitstempel in einer numerischen Form speichern oder übertragen müssen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsblöcken ist dieser Funktionsblock spezialisiert auf die Umwandlung von `TIME` in `LINT`.
- Andere Blöcke könnten zusätzliche Funktionen wie Skalierung oder Formatierung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_NS_TO_LINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Nanosekunden in 64-Bit-Ganzzahlen umzuwandeln. Er ist besonders nützlich in Anwendungen, die präzise Zeitmessungen und -berechnungen erfordern.

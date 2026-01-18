# F_TIME_IN_S_TO_DINT

```{index} single: F_TIME_IN_S_TO_DINT
```

<img width="1506" height="212" alt="F_TIME_IN_S_TO_DINT" src="https://github.com/user-attachments/assets/3154c79d-5b35-46bb-8057-39d2ce513a57" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_DINT` dient der Konvertierung eines Zeitwerts in Sekunden (`TIME`) in einen vorzeichenbehafteten Ganzzahlwert (`DINT`). Diese Konvertierung ist nützlich, wenn Zeitwerte in numerischen Berechnungen oder für Steuerungszwecke verwendet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert vom Typ `TIME` in Sekunden.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten Wert als vorzeichenbehaftete Ganzzahl (`DINT`).

### **Adapter**
Es werden keine Adapter verwendet.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den Zeitwert `IN` in Sekunden in einen `DINT`-Wert um und speichert das Ergebnis in `OUT`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock nutzt die Funktion `TIME_IN_S_TO_DINT` für die Konvertierung.
- Der Block ist einfach und effizient, da er direkt auf dem ST-Algorithmus basiert.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach dem Auslösen von `REQ`.

## Anwendungsszenarien
- Umrechnung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungslogiken, die numerische Zeitwerte benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken ist dieser speziell auf die Umwandlung von `TIME` in `DINT` ausgelegt.
- Einfacher und direkter als allgemeine Konvertierungsblöcke, die möglicherweise zusätzliche Parameter benötigen.

## Fazit
Der `F_TIME_IN_S_TO_DINT` Funktionsblock bietet eine effiziente und einfache Lösung für die Konvertierung von Zeitwerten in Sekunden in vorzeichenbehaftete Ganzzahlen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Steuerungsanwendungen.
# F_TIME_IN_MS_TO_LINT

```{index} single: F_TIME_IN_MS_TO_LINT
```

<img width="1520" height="212" alt="F_TIME_IN_MS_TO_LINT" src="https://github.com/user-attachments/assets/461a5741-0611-455b-92b2-5ce407357498" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock `F_TIME_IN_MS_TO_LINT` dient der Konvertierung eines Zeitwertes (`TIME`) in Millisekunden in einen 64-Bit-Ganzzahlwert (`LINT`). Diese Funktionalität ist besonders nützlich, wenn Zeitwerte für Berechnungen oder Vergleiche in einer numerischen Form benötigt werden.

![F_TIME_IN_MS_TO_LINT](F_TIME_IN_MS_TO_LINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des Zeitwertes. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert (`TIME`), der in Millisekunden umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Zeitwert als 64-Bit-Ganzzahl (`LINT`) aus.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Zeitwert `IN` in Millisekunden umrechnet und das Ergebnis als `LINT` über den Ausgang `OUT` ausgibt. Das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock nutzt die Funktion `TIME_IN_MS_TO_LINT` zur Umrechnung des Zeitwertes.
- Die Konvertierung erfolgt mit einer hohen Genauigkeit, da der `LINT`-Datentyp 64 Bit breit ist.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Zeitmessungen, bei denen die Ergebnisse in numerischer Form weiterverarbeitet werden müssen.
- Steuerungsanwendungen, die präzise Zeitintervalle in Millisekunden benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen, die möglicherweise nur in kleinere Ganzzahltypen konvertieren, bietet dieser Baustein eine höhere Genauigkeit durch die Verwendung des `LINT`-Datentyps.
- Ähnliche Bausteine könnten die Zeit in anderen Einheiten (z.B. Sekunden oder Mikrosekunden) konvertieren, während dieser Baustein speziell auf Millisekunden ausgelegt ist.

## Fazit
Der `F_TIME_IN_MS_TO_LINT` Funktionsblock ist ein effizientes Werkzeug zur präzisen Konvertierung von Zeitwerten in Millisekunden in einen 64-Bit-Ganzzahlwert. Seine einfache und direkte Funktionsweise macht ihn besonders geeignet für Anwendungen, die genaue Zeitmessungen und -berechnungen erfordern.
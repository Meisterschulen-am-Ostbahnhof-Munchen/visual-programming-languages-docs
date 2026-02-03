# F_TIME_IN_US_TO_ULINT

```{index} single: F_TIME_IN_US_TO_ULINT
```

<img width="1536" height="212" alt="F_TIME_IN_US_TO_ULINT" src="https://github.com/user-attachments/assets/30c49e6f-e058-49c6-84cf-c4478d9a7c69" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_IN_US_TO_ULINT` dient der Konvertierung eines Zeitwerts in Mikrosekunden (`TIME`) in einen vorzeichenlosen 64-Bit-Integer-Wert (`ULINT`). Dies ist besonders nützlich, wenn Zeitwerte in numerische Berechnungen oder für weitere Verarbeitungsschritte umgewandelt werden müssen.

![F_TIME_IN_US_TO_ULINT](F_TIME_IN_US_TO_ULINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Zeitwert vom Typ `TIME` (in Mikrosekunden), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Wert als vorzeichenlosen 64-Bit-Integer (`ULINT`) zurück.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt den Algorithmus `REQ`, um den eingehenden `TIME`-Wert in Mikrosekunden in einen `ULINT`-Wert umzuwandeln. Die Konvertierung erfolgt durch die Funktion `TIME_IN_US_TO_ULINT(IN)`. Sobal die Konvertierung abgeschlossen ist, wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus.
- Die Konvertierung ist direkt und ohne zusätzliche Parameter oder Zustandsverwaltung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine komplexen Zustandsübergänge. Der Block reagiert auf das `REQ`-Ereignis, führt die Konvertierung durch und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Zeitmessung und -verarbeitung in Steuerungssystemen.
- Umwandlung von Zeitwerten für die Verwendung in Berechnungen oder Logging-Systemen.
- Integration in größere Steuerungsalgorithmen, die numerische Zeitwerte benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_TIME_IN_US_TO_ULINT` spezialisiert auf die Umwandlung von `TIME` zu `ULINT`.
- Andere Blöcke könnten zusätzliche Funktionen wie Skalierung oder Filterung anbieten, was hier nicht der Fall ist.

## Fazit
Der Funktionsblock `F_TIME_IN_US_TO_ULINT` ist ein einfaches, aber effektives Werkzeug zur Konvertierung von Zeitwerten in Mikrosekunden in numerische Werte. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen, die präzise Zeitverarbeitung erfordern.
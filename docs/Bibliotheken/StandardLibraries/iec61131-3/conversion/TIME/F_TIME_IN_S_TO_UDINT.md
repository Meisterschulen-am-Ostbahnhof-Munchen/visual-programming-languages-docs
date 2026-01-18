# F_TIME_IN_S_TO_UDINT

```{index} single: F_TIME_IN_S_TO_UDINT
```

<img width="1520" height="212" alt="F_TIME_IN_S_TO_UDINT" src="https://github.com/user-attachments/assets/9fd11a62-281e-43ec-9520-98d7cc20671c" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_TIME_IN_S_TO_UDINT` dient der Konvertierung eines TIME-Werts in Sekunden in einen UDINT-Wert. Diese Konvertierung ist nützlich, wenn Zeitwerte in numerischen Operationen oder für weitere Verarbeitungsschritte benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: TIME-Wert in Sekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Konvertierter UDINT-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock konvertiert den eingehenden TIME-Wert (IN) in Sekunden in einen UDINT-Wert (OUT). Die Konvertierung erfolgt durch den Aufruf der Funktion `TIME_IN_S_TO_UDINT(IN)` im Algorithmus. Bei Auslösung des REQ-Ereignisses wird die Konvertierung durchgeführt und das CNF-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und effizient, da er direkt die eingebaute Funktion `TIME_IN_S_TO_UDINT` nutzt.
- Keine zusätzlichen Zustände oder komplexe Logik erforderlich.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt sofort bei Auslösung des REQ-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungssysteme, wo Zeitwerte als numerische Werte benötigt werden.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell für die Umwandlung von TIME in UDINT optimiert.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Grenzwertprüfung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_S_TO_UDINT` Funktionsblock ist ein einfacher und effizienter Baustein zur Konvertierung von TIME-Werten in UDINT. Er eignet sich ideal für Anwendungen, bei denen Zeitwerte in numerischer Form benötigt werden.
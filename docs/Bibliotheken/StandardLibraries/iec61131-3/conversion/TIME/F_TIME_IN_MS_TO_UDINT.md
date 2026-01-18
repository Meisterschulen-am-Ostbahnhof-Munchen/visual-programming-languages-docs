# F_TIME_IN_MS_TO_UDINT

```{index} single: F_TIME_IN_MS_TO_UDINT
```

<img width="1531" height="212" alt="F_TIME_IN_MS_TO_UDINT" src="https://github.com/user-attachments/assets/142405a6-cd3f-4140-b2ae-e38e692d620f" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_TIME_IN_MS_TO_UDINT` dient der Konvertierung eines `TIME`-Werts in Millisekunden in einen `UDINT`-Wert. Dies ist besonders nützlich, wenn Zeitwerte in numerischen Berechnungen oder für Steuerungszwecke verwendet werden sollen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingang vom Typ `TIME`. Der Zeitwert in Millisekunden, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang vom Typ `UDINT`. Der konvertierte numerische Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `TIME`-Wert in Millisekunden in einen `UDINT`-Wert umwandelt. Die Konvertierung erfolgt synchron mit dem Auslösen des `REQ`-Ereignisses. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach und hat keine internen Zustände.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik.

## Anwendungsszenarien
- Umwandlung von Zeitwerten für numerische Berechnungen.
- Integration in Steuerungslogiken, die numerische Zeitwerte benötigen.

## Umgekehrte Konvertierung (Numerisch zu TIME)
Oft wird nach einer Funktion wie `DINT_TO_TIME` gesucht, um einen numerischen Wert (z.B. 500) wieder in einen Zeitwert (z.B. 500ms) zurückzuwandeln. Einen solchen expliziten Konvertierungsbaustein gibt es in der Regel nicht, da dies elegant über eine Multiplikation gelöst wird.

Verwenden Sie hierfür den Baustein **`F_MULTIME`** (aus der Kategorie `arithmetic`):
*   Multiplizieren Sie Ihren numerischen Wert mit der gewünschten Zeitbasis.
*   **Beispiel:** `500 * T#1ms = T#500ms`
*   Dies ermöglicht eine flexible Skalierung (z.B. * T#1s für Sekunden, * T#100ms für Zehntelsekunden).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen ist dieser speziell auf die Umwandlung von `TIME` in `UDINT` ausgelegt.
- Andere Bausteine könnten zusätzliche Funktionen wie Skalierung oder Filterung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_TIME_IN_MS_TO_UDINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von Zeitwerten in Millisekunden in numerische Werte. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und direkte Umwandlung benötigt wird.
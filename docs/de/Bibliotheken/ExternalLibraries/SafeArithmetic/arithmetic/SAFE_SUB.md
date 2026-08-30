# SAFE_SUB

![SAFE_SUB](SAFE_SUB.svg)

* * * * * * * * * *
## Einleitung

**SAFE_SUB** ist Teil der **SafeArithmetic**-Bibliothek (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). Es ist ein fester Subtraktions-Funktionsbaustein mit 2 Eingängen, der sich
wie das Standard-`F_SUB` verhält, aber einen Unter-/Überlauf nie unbemerkt durchlässt: bei einer
Grenzwertverletzung wird das Ergebnis auf den gültigen Bereich des Ergebnistyps **geklemmt**
(saturiert), und `LIMIT_HIT` zeigt an, dass geklemmt wurde.

Das ist der Baustein, der die ganze Bibliothek ausgelöst hat: `Uebung_011b3` zeigt auf echter
ESP32-P4-Hardware, dass das normale `F_SUB` `UDINT#1 - UDINT#12 = UDINT#4294967285` berechnet —
genau der in IEC 61131-3 spezifizierte Zweierkomplement-Wraparound für unsigned-Typen, aber
gefährlich für reale Messwerte (Sollwertdifferenzen, Restweg-Berechnungen). `SAFE_SUB` berechnet
dieselbe Subtraktion stattdessen als `UDINT#0` mit `LIMIT_HIT = TRUE`.

Anders als `SAFE_ADD_2/3/4`/`SAFE_MUL_2/3/4` ist `SAFE_SUB` **nicht** generisch in der Arität:
Subtraktion ist weder assoziativ noch kommutativ, sodass ein N-stelliges, "erweiterbares"
`SAFE_SUB_n` keine wohldefinierte Bedeutung hätte, wie es bei erweiterbarem ADD/MUL der Fall ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Normale Ausführungsanforderung

### **Ereignis-Ausgänge**

- `CNF`: Ausführungsbestätigung

### **Daten-Eingänge**

- `IN1` (ANY_MAGNITUDE): Minuend
- `IN2` (ANY_MAGNITUDE): Subtrahend

### **Daten-Ausgänge**

- `OUT` (ANY_MAGNITUDE): IN2 von IN1 subtrahiert, geklemmt auf den gültigen Bereich des Ergebnistyps
- `LIMIT_HIT` (BOOL): TRUE, wenn das Ergebnis wegen Unter-/Überlauf geklemmt wurde

## Funktionsweise

1. **Berechnungsanforderung**: `REQ`-Ereignis mit Werten für IN1 und IN2.
2. **Subtraktion**: berechnet `IN1 - IN2`.
3. **Ergebnisausgabe**: `CNF`-Ereignis mit berechnetem `OUT` und `LIMIT_HIT`.

## Über-/Unterlaufverhalten

- **Signed Integer**-Typen: bei Über-/Unterlauf Klemmen auf `numeric_limits::min()` bzw.
  `::max()`, Richtung abhängig vom Vorzeichen von IN2.
- **Unsigned Integer**-Typen: Subtraktion kann nur unterlaufen (unter 0 gehen), daher wird immer
  auf `0` geklemmt — genau der `Uebung_011b3`-Fall: `UDINT#1 - UDINT#12` klemmt auf `UDINT#0` mit
  `LIMIT_HIT = TRUE`, statt auf `UDINT#4294967285` überzulaufen.
- **REAL/LREAL**: ein nicht-endliches Zwischen- oder Endergebnis wird immer erkannt, unabhängig
  davon, ob die *Eingänge* bereits nicht-endlich waren — `+INF`/`-INF` werden auf
  `numeric_limits::max()`/`::lowest()` geklemmt, `NaN` (z.B. `INF - INF`) wird zu einer
  deterministischen `0`. `LIMIT_HIT` wird in jedem Fall gesetzt.
- **Inkompatible Typen** (z.B. Mischen eines Magnitude-Typs mit einem nicht verwandten Typ, für
  den keine Subtraktion definiert ist): das Ergebnis dieser Operation ist undefiniert (als Fehler
  geloggt), `OUT` bleibt unverändert, und `LIMIT_HIT` wird für diesen Fall **nicht** gesetzt — es
  ist ein Typfehler, kein numerisches Grenzwert-Ereignis.

## Verwandte Funktionsbausteine

- [F_SUB](../../../StandardLibraries/iec61131-3/arithmetic/F_SUB.md) — das normale,
  nicht-saturierende Standard-Pendant (stiller Wraparound/`INF` bei Overflow statt Klemmen und
  Melden).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — der Hardware-Befund,
  der diese Bibliothek motiviert hat.
- [Uebung_011b5](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b5.md) — dasselbe
  `1 - 12`-Szenario, erneut ausgeführt mit `SAFE_SUB`, mit `LIMIT_HIT` auf einem zweiten Ausgang
  verdrahtet, damit das Klemmen auf der Hardware sichtbar wird.

## Fazit

SAFE_SUB bietet dieselbe Subtraktion wie `F_SUB`, aber mit einem expliziten, bereichsbewussten
Grenzwert-Signal statt eines stillen Wraparounds (Integer) bzw. eines still verfälschten
Ergebnisses (Fließkomma) — und schließt damit direkt die Lücke, die `Uebung_011b3` in der
Standardbibliothek gefunden hat.

# SAFE_MUL_4

![SAFE_MUL_4](SAFE_MUL_4.svg)

* * * * * * * * * *
## Einleitung

**SAFE_MUL_4** ist Teil der **SafeArithmetic**-Bibliothek (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). Es ist ein generischer Funktionsbaustein für Multiplikation mit 4 Eingängen,
der das feste 2-Eingänge-`F_MUL` der Standardbibliothek auf 4 Eingänge erweitert (die
Standardbibliothek hat noch kein generisches, mehrstelliges `MUL_n`, anders als `ADD_2/3/4`),
und einen Overflow nie unbemerkt durchlässt: bei Overflow wird das Ergebnis auf den gültigen
Bereich des Ergebnistyps **geklemmt** (saturiert), und `LIMIT_HIT` zeigt an, dass geklemmt wurde.

Diese Bibliothek existiert, weil normale IEC-61131-3-Arithmetik-Funktionsbausteine (wie
`F_MUL` selbst, bei Integer-Typen) bei Overflow den in IEC 61131-3 spezifizierten
Zweierkomplement-Wraparound berechnen — laut Norm korrekt, aber gefährlich für reale Messwerte.
`Uebung_011b3` zeigt das auf echter Hardware: das normale `F_SUB` berechnet
`UDINT#1 - UDINT#12 = UDINT#4294967285`, ein stiller Unterlauf-Wraparound.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Normale Ausführungsanforderung

### **Ereignis-Ausgänge**

- `CNF`: Ausführungsbestätigung

### **Daten-Eingänge**

- `IN1` (ANY_NUM): erster Faktor
- `IN2` (ANY_NUM): zweiter Faktor
- `IN3` (ANY_NUM): dritter Faktor
- `IN4` (ANY_NUM): vierter Faktor

### **Daten-Ausgänge**

- `OUT` (ANY_NUM): MUL-Ergebnis, geklemmt auf den gültigen Bereich des Ergebnistyps
- `LIMIT_HIT` (BOOL): TRUE, wenn das Ergebnis wegen Overflow geklemmt wurde

## Funktionsweise

1. **Berechnungsanforderung**: `REQ`-Ereignis mit Werten für IN1, IN2, IN3, IN4.
2. **Berechnung**: berechnet `IN1 * IN2 * IN3 * IN4` von links nach rechts, Schritt für Schritt paarweise.
   Jeder Schritt wird auf Overflow geprüft; überläuft ein Schritt, wird sein Ergebnis auf den
   gültigen Bereich des Ergebnistyps geklemmt und `LIMIT_HIT` gesetzt (bleibt gesetzt — einmal
   von irgendeinem Schritt gesetzt, bleibt es für den Rest der Faltung gesetzt).
3. **Ergebnisausgabe**: `CNF`-Ereignis mit berechnetem `OUT` und `LIMIT_HIT`.

## Overflow-/Sättigungsverhalten

- **Signed Integer**-Typen: bei Overflow Klemmen auf `numeric_limits::max()` bzw. `::min()`,
  Richtung abhängig von den Vorzeichen der Operanden des überlaufenden Schritts.
- **Unsigned Integer**-Typen: bei Overflow Klemmen auf `numeric_limits::max()`.
- **REAL/LREAL**: ein nicht-endliches Zwischen- oder Endergebnis wird immer erkannt, unabhängig
  davon, ob die *Eingänge* dieses Schritts bereits nicht-endlich waren — `+INF`/`-INF` werden auf
  `numeric_limits::max()`/`::lowest()` geklemmt, `NaN` (z.B. wenn ein vorheriger Schritt bereits
  nicht-endlich wurde und die Kombination `NaN` ergibt) wird zu einer deterministischen `0`.
  `LIMIT_HIT` wird in jedem Fall gesetzt.
- **Inkompatible Typen** (z.B. Mischen eines Magnitude-Typs mit einem nicht verwandten Typ, für
  den kein `MUL` definiert ist): der betroffene Schritt wird übersprungen (als Fehler geloggt),
  `OUT` behält den bis dahin akkumulierten Wert der Faltung, und `LIMIT_HIT` wird für diesen Fall
  **nicht** gesetzt — es ist ein Typfehler, kein numerisches Grenzwert-Ereignis.

## Bekannte Einschränkung bei verketteter (Arität ≥ 3) Multiplikation mit SIGNED-Typen

`SAFE_MUL_4` wird als strikte, von links nach rechts gefaltete Kette einzelner Zweier-Operationen
ausgewertet: `((IN1 * IN2) * IN3) * ...`, wobei nach jedem Schritt geklemmt wird. Bei
**signed** Integer-Typen (und REAL/LREAL, die kein unsigned kennen) bedeutet das: Ein vorübergehender
Zwischen-Overflow, den ein späterer Eingang eigentlich wieder in den gültigen Bereich zurückholen
würde, wird dauerhaft in `OUT` festgeschrieben — inklusive eines `LIMIT_HIT`, das die wahre
Gesamtsumme nicht mehr widerspiegelt.

Beispiel (INT, IN1=40000, IN2=40000, IN3=0, IN4=1): das wahre Ergebnis wäre `0`, locker innerhalb des
INT-Bereichs, aber die Faltung klemmt bereits nach dem zweiten Schritt und erholt sich nicht mehr.

Das ist **kein** Bug, der still gefixt wird — es ist dokumentiertes, beabsichtigtes Verhalten: die
Faltung wertet als reale Kette von Operationen mit fester Breite aus, genau wie das normale
(nicht-sichere) `F_MUL` es auch tut, und meldet eine echte Zwischen-Grenzwertverletzung statt
die Berechnung heimlich umzusortieren.

**Unsigned**-Ketten jeder Arität sind davon nicht betroffen und melden immer einen echten Overflow:
ein späterer Faktor ist entweder 0 (das Ergebnis kollabiert dann sauber auf 0, unabhängig von vorherigem Klemmen) oder ≥ 1 (das Produkt bleibt monoton nicht-fallend) — bei unsigned kann sich das Zwischenklemmen daher nie von der wahren Gesamtsumme unterscheiden.

`SAFE_MUL_2` (nur eine einzelne Operation, keine Verkettung) meldet unabhängig vom
Vorzeichen immer einen echten, korrekten Overflow — die Mehrdeutigkeit existiert nur ab Arität 3.

## Verwandte Funktionsbausteine

- [F_MUL](../../../StandardLibraries/iec61131-3/arithmetic/F_MUL.md) — der feste 2-Eingänge-
  Standardbaustein, den dieses Muster erweitert (stiller Wraparound/`INF` bei Overflow statt
  Klemmen und Melden; ein 4-Eingänge-Standardpendant existiert nicht).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — der Hardware-Befund,
  der diese Bibliothek motiviert hat.

## Fazit

SAFE_MUL_4 erweitert die Multiplikation von `F_MUL` auf 4 Eingänge, mit einem
expliziten, bereichsbewussten Grenzwert-Signal statt eines stillen Wraparounds (Integer) bzw.
eines still verfälschten Ergebnisses (Fließkomma) — auf Kosten der oben dokumentierten
Arität-≥-3/signed-Verkettungs-Einschränkung, die eine bewusste Design-Entscheidung ist, kein
Versehen.

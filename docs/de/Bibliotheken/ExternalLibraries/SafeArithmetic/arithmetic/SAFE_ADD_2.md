# SAFE_ADD_2

![SAFE_ADD_2](SAFE_ADD_2.svg)

* * * * * * * * * *
## Einleitung

**SAFE_ADD_2** ist Teil der **SafeArithmetic**-Bibliothek (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). Es ist ein generischer Funktionsbaustein für Addition mit 2 Eingängen,
der sich wie das Standard-`ADD_2` verhält, aber einen Overflow nie unbemerkt
durchlässt: bei Overflow wird das Ergebnis auf den gültigen Bereich des Ergebnistyps
**geklemmt** (saturiert), und `LIMIT_HIT` zeigt an, dass geklemmt wurde.

Diese Bibliothek existiert, weil normale IEC-61131-3-Arithmetik-Funktionsbausteine (wie
`ADD_2` selbst, bei Integer-Typen) bei Overflow den in IEC 61131-3 spezifizierten
Zweierkomplement-Wraparound berechnen — laut Norm korrekt, aber gefährlich für reale Messwerte.
`Uebung_011b3` zeigt das auf echter Hardware: das normale `F_SUB` berechnet
`UDINT#1 - UDINT#12 = UDINT#4294967285`, ein stiller Unterlauf-Wraparound.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Normale Ausführungsanforderung

### **Ereignis-Ausgänge**

- `CNF`: Ausführungsbestätigung

### **Daten-Eingänge**

- `IN1` (ANY_MAGNITUDE): erster Summand
- `IN2` (ANY_MAGNITUDE): zweiter Summand

### **Daten-Ausgänge**

- `OUT` (ANY_MAGNITUDE): ADD-Ergebnis, geklemmt auf den gültigen Bereich des Ergebnistyps
- `LIMIT_HIT` (BOOL): TRUE, wenn das Ergebnis wegen Overflow geklemmt wurde

## Funktionsweise

1. **Berechnungsanforderung**: `REQ`-Ereignis mit Werten für IN1, IN2.
2. **Berechnung**: berechnet `IN1 + IN2` von links nach rechts, Schritt für Schritt paarweise.
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
  den kein `ADD` definiert ist): der betroffene Schritt wird übersprungen (als Fehler geloggt),
  `OUT` behält den bis dahin akkumulierten Wert der Faltung, und `LIMIT_HIT` wird für diesen Fall
  **nicht** gesetzt — es ist ein Typfehler, kein numerisches Grenzwert-Ereignis.

## Verwandte Funktionsbausteine

- [ADD_2](../../../StandardLibraries/iec61131-3/arithmetic/ADD_2.md) — das
  normale, nicht-saturierende Standard-Pendant (stiller Wraparound/`INF` bei Overflow statt
  Klemmen und Melden).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — der Hardware-Befund,
  der diese Bibliothek motiviert hat.

## Fazit

SAFE_ADD_2 bietet dieselbe Addition mit 2 Eingängen wie `ADD_2`, aber mit einem
expliziten, bereichsbewussten Grenzwert-Signal statt eines stillen Wraparounds (Integer) bzw.
eines still verfälschten Ergebnisses (Fließkomma) — auf Kosten der oben dokumentierten
Arität-≥-3/signed-Verkettungs-Einschränkung, die eine bewusste Design-Entscheidung ist, kein
Versehen.

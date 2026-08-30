# SAFE_DIV

![SAFE_DIV](SAFE_DIV.svg)

* * * * * * * * * *
## Einleitung

**SAFE_DIV** ist Teil der **SafeArithmetic**-Bibliothek (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). Es ist ein fester Divisions-Funktionsbaustein mit 2 Eingängen, der sich
wie das Standard-`F_DIV` verhält, aber niemals abstürzt, `INF`/`NaN` erzeugt oder einen Overflow
unbemerkt durchlässt: Division durch Null und Overflow werden als **Klemm**-Bedingung behandelt,
und `LIMIT_HIT` zeigt an, dass geklemmt wurde.

Wie `SAFE_SUB` ist auch `SAFE_DIV` **nicht** generisch in der Arität: Division ist weder
assoziativ noch kommutativ, sodass eine "verkettete" Division keine wohldefinierte Bedeutung
hätte, wie es bei erweiterbarem ADD/MUL der Fall ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `REQ`: Normale Ausführungsanforderung

### **Ereignis-Ausgänge**

- `CNF`: Ausführungsbestätigung

### **Daten-Eingänge**

- `IN1` (ANY_NUM): Dividend
- `IN2` (ANY_NUM): Divisor

### **Daten-Ausgänge**

- `OUT` (ANY_NUM): IN1 dividiert durch IN2; 0, wenn IN2 gleich 0 ist
- `LIMIT_HIT` (BOOL): TRUE, wenn das Ergebnis wegen Overflow oder Division durch Null geklemmt wurde

## Funktionsweise

1. **Berechnungsanforderung**: `REQ`-Ereignis mit Werten für IN1 und IN2.
2. **Division**: berechnet `IN1 / IN2`.
3. **Ergebnisausgabe**: `CNF`-Ereignis mit berechnetem `OUT` und `LIMIT_HIT`.

## Overflow-/Division-durch-Null-Verhalten

- **Beliebiger Integer**-Typ, `IN2 == 0`: klemmt auf `0` mit `LIMIT_HIT = TRUE`, statt
  abzustürzen (Integer-Division durch Null ist in reinem C++ undefiniertes Verhalten und würde
  `F_DIV` zum Absturz bringen).
- **Signed Integer**-Typen: der eine verbleibende Fall, der überlaufen kann, `INT_MIN / -1`,
  klemmt auf `numeric_limits::max()`.
- **REAL/LREAL**, `IN2 == 0.0`: klemmt auf `0` mit `LIMIT_HIT = TRUE`, statt IEEE-754
  `+INF`/`-INF`/`NaN` zu erzeugen (`0.0 / 0.0`).
- **REAL/LREAL**, `IN2 != 0.0`: ein nicht-endliches Zwischen- oder Endergebnis wird immer
  erkannt, unabhängig davon, ob die *Eingänge* bereits nicht-endlich waren — `+INF`/`-INF` werden
  auf `numeric_limits::max()`/`::lowest()` geklemmt, `NaN` wird zu einer deterministischen `0`.
  `LIMIT_HIT` wird in jedem Fall gesetzt.
- **Inkompatible Typen** (z.B. Mischen eines numerischen Typs mit einem nicht verwandten Typ, für
  den keine Division definiert ist): das Ergebnis dieser Operation ist undefiniert (als Fehler
  geloggt), `OUT` bleibt unverändert, und `LIMIT_HIT` wird für diesen Fall **nicht** gesetzt — es
  ist ein Typfehler, kein numerisches Grenzwert-Ereignis.

## Verwandte Funktionsbausteine

- [F_DIV](../../../StandardLibraries/iec61131-3/arithmetic/F_DIV.md) — das normale,
  nicht-saturierende Standard-Pendant (undefiniertes Verhalten bei Integer-Division durch Null,
  `INF`/`NaN` bei Fließkomma-Division durch/von Null, statt Klemmen und Melden).
- [Uebung_011b7](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b7.md) — eine
  Division-durch-Null-Demo mit `SAFE_DIV`, `LIMIT_HIT` auf einem zweiten Ausgang verdrahtet,
  damit das Klemmen auf der Hardware sichtbar wird.

## Fazit

SAFE_DIV bietet dieselbe Division wie `F_DIV`, aber mit einem expliziten, bereichsbewussten
Grenzwert-Signal statt undefiniertem Verhalten (Integer-Division durch Null) oder einem still
verfälschten Ergebnis (Fließkomma-Overflow/`NaN`).

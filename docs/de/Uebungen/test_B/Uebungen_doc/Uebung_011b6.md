# Übung_011b6: Numeric Value Input SAFE_SUB

![Uebung_011b6_network](./Uebung_011b6_network.svg)

* * * * * * * * * *
## Einleitung

Übung **Uebung_011b6** ist die direkte Behebung von [Übung_011b3](Uebung_011b3.md): dieselbe
Subtraktion zweier über das ISOBUS-Netzwerk eingelesener numerischer Werte, aber mit
[SAFE_SUB](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/SafeArithmetic/arithmetic/SAFE_SUB/) statt
normalem `F_SUB`. `SAFE_SUB.LIMIT_HIT` wird nach `UDINT` konvertiert und auf `OutputNumber_N2`
geschrieben, sodass der Unterlauf, den `Uebung_011b3` still erzeugt hat, jetzt direkt auf dem
ISOBUS-Netzwerk sichtbar ist.

## Verwendete Funktionsbausteine (FBs)

- **InputNumber_I1** / **InputNumber_I2** (Typ: `isobus::UT::io::NumericValue::NumericValue_ID`)
  - Lesen die aktuellen numerischen Werte der ISOBUS-Objekte "InputNumber_I1"/"InputNumber_I2".
- **F_DWORD_TO_UDINT** / **F_DWORD_TO_UDINT_1** (Typ: `iec61131::conversion::F_DWORD_TO_UDINT`)
  - Konvertieren die eingehenden DWORD-Werte nach UDINT.
- **SAFE_SUB** (Typ: `SafeArithmetic::arithmetic::SAFE_SUB`)
  - Daten-Eingänge: `IN1` (Minuend), `IN2` (Subtrahend), beide UDINT. Daten-Ausgänge: `OUT`
    (UDINT, geklemmte Differenz), `LIMIT_HIT` (BOOL, TRUE wenn die Subtraktion unter-/übergelaufen ist).
- **Q_NumericValue** (Typ: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N1`)
  - Schreibt `SAFE_SUB.OUT` zurück auf das ISOBUS-Netzwerk.
- **F_BOOL_TO_UDINT** (Typ: `iec61131::conversion::F_BOOL_TO_UDINT`)
  - Konvertiert `SAFE_SUB.LIMIT_HIT` (BOOL) nach `UDINT` (`1`/`0`).
- **Q_NumericValue_1** (Typ: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N2`)
  - Schreibt das konvertierte `LIMIT_HIT` zurück auf das ISOBUS-Netzwerk.

## Programmablauf und Verbindungen

1. **Ereignissteuerung**: `InputNumber_I1.IND`/`InputNumber_I2.IND` lösen das `REQ` ihrer
   Konverter aus. Beide `CNF`-Ausgänge lösen `SAFE_SUB.REQ` aus. `SAFE_SUB.CNF` löst sowohl
   `Q_NumericValue.REQ` (die Differenz) als auch `F_BOOL_TO_UDINT.REQ` (das Grenzwert-Flag) aus,
   und `F_BOOL_TO_UDINT.CNF` löst `Q_NumericValue_1.REQ` aus.
2. **Datenfluss**: die konvertierten `IN1`/`IN2` (UDINT) gehen an `SAFE_SUB.IN1`/`IN2`.
   `SAFE_SUB.OUT` geht an `Q_NumericValue.u32NewValue`. `SAFE_SUB.LIMIT_HIT` geht an
   `F_BOOL_TO_UDINT.IN`, dessen `OUT` an `Q_NumericValue_1.u32NewValue` geht.

## Hardware-Ergebnis (gleiche Eingänge wie Übung_011b3)

`InputNumber_I1 = UDINT#1`, `InputNumber_I2 = UDINT#12`:

```
SAFE_SUB.OUT = 0           (geklemmt: unsigned-Subtraktion kann nur unterlaufen)
SAFE_SUB.LIMIT_HIT = TRUE  ->  OutputNumber_N1 = 0, OutputNumber_N2 = 1
```

Bestätigt direkt die Behebung: statt des stillen `UDINT#4294967285` aus
[Übung_011b3](Uebung_011b3.md) wird das wahrhaft-negative und nicht darstellbare Ergebnis jetzt
auf `0` geklemmt, mit einem expliziten, beobachtbaren `LIMIT_HIT = TRUE`.

## Zusammenfassung

Führen Sie [Übung_011b3](Uebung_011b3.md) und diese Übung mit denselben Eingängen nebeneinander
aus, um das exakte Vorher/Nachher der `SafeArithmetic`-Fix für den ursprünglichen Hardware-Befund
zu sehen.

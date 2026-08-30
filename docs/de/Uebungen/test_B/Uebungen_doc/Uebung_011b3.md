# Übung_011b3: Numeric Value Input SUB

![Uebung_011b3_network](./Uebung_011b3_network.svg)

* * * * * * * * * *
## Einleitung

Übung **Uebung_011b3** führt eine einfache Subtraktion zweier über das ISOBUS-Netzwerk
eingelesener numerischer Werte durch. Anders als die vorherigen Übungen dieser Reihe dient sie
dazu, einen echten Befund auf ESP32-P4-Hardware zu zeigen: `F_SUB` berechnet bei Unterlauf den in
IEC 61131-3 spezifizierten Zweierkomplement-Wraparound, und für den hier verwendeten unsigned-Typ
`UDINT` ist das gefährlich für reale Messwerte (Sollwertdifferenzen, Restweg-Berechnungen). Mit
`InputNumber_I1 = 1` und `InputNumber_I2 = 12` gibt die Übung `UDINT#4294967285` aus statt des
mathematisch erwarteten `-11` — weil `UDINT` keine negative Zahl darstellen kann und die normale
Subtraktion überläuft, statt den Unterlauf zu melden. Dieser Befund hat direkt die
[SafeArithmetic](../../../Bibliotheken/ExternalLibraries/SafeArithmetic/index.md)-Bibliothek und
ihren [SAFE_SUB](../../../Bibliotheken/ExternalLibraries/SafeArithmetic/arithmetic/SAFE_SUB.md)-Baustein
motiviert — siehe [Übung_011b6](Uebung_011b6.md) für dasselbe Szenario, erneut ausgeführt mit
`SAFE_SUB`.

## Verwendete Funktionsbausteine (FBs)

- **InputNumber_I1** (Typ: `isobus::UT::io::NumericValue::NumericValue_ID`)
  - Parameter: `QI` = `TRUE`, `u16ObjId` = `InputNumber_I1`
  - Ereignis-Ausgang: `IND`, Daten-Ausgang: `IN` (DWORD)
  - Liest den aktuellen numerischen Wert des ISOBUS-Objekts "InputNumber_I1".
- **InputNumber_I2** (Typ: `isobus::UT::io::NumericValue::NumericValue_ID`)
  - Wie oben, für das ISOBUS-Objekt "InputNumber_I2".
- **F_DWORD_TO_UDINT** / **F_DWORD_TO_UDINT_1** (Typ: `iec61131::conversion::F_DWORD_TO_UDINT`)
  - Konvertieren die eingehenden DWORD-Werte nach UDINT.
- **F_SUB** (Typ: `iec61131::arithmetic::F_SUB`)
  - Daten-Eingänge: `IN1` (Minuend), `IN2` (Subtrahend), beide UDINT. Daten-Ausgang: `OUT` (UDINT).
  - Berechnet `IN1 - IN2` mit normaler IEC-61131-3-Semantik (Wraparound).
- **Q_NumericValue** (Typ: `isobus::UT::Q::Q_NumericValue`)
  - Parameter: `u16ObjId` = `OutputNumber_N1`. Schreibt `F_SUB.OUT` zurück auf das ISOBUS-Netzwerk.

## Programmablauf und Verbindungen

1. **Ereignissteuerung**: `InputNumber_I1.IND`/`InputNumber_I2.IND` lösen jeweils das `REQ` ihres
   `F_DWORD_TO_UDINT`-Konverters aus. Beide `CNF`-Ausgänge der Konverter sind mit `F_SUB.REQ`
   verbunden (implizit ODER-verknüpft — jeder neue Eingang löst eine Neuberechnung aus).
   `F_SUB.CNF` löst `Q_NumericValue.REQ` aus.
2. **Datenfluss**: `InputNumber_I1.IN`/`InputNumber_I2.IN` (DWORD) gehen an die `IN`-Eingänge der
   Konverter. Die `OUT`-Werte (UDINT) der Konverter gehen an `F_SUB.IN1` (von I1) und `F_SUB.IN2`
   (von I2). `F_SUB.OUT` geht an `Q_NumericValue.u32NewValue`.

## Hardware-Befund

`InputNumber_I1 = UDINT#1`, `InputNumber_I2 = UDINT#12`:

```
F_SUB.OUT = UDINT#1 - UDINT#12 = UDINT#4294967285   (F_SUB hat kein LIMIT_HIT)
```

Das ist der korrekte, in IEC 61131-3 spezifizierte Zweierkomplement-Wraparound für `UDINT` — kein
FORTE-Bug — aber es erzeugt still ein unsinniges Ergebnis für eine reale Subtraktion, deren wahre
Antwort negativ und in einem unsigned-Typ nicht darstellbar ist. Siehe
[Übung_011b6](Uebung_011b6.md) für die Behebung.

## Zusammenfassung

Diese Übung ist der Ausgangspunkt einer kleinen Reihe: sie reproduziert auf echter Hardware genau
das Problem des stillen Wraparounds, das die SafeArithmetic-Bibliothek lösen soll. Vergleichen Sie
ihre Ausgabe direkt mit [Übung_011b6](Uebung_011b6.md) (gleiche Eingänge, `SAFE_SUB` statt
`F_SUB`).

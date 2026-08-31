# E_SR_SYM

![E_SR_SYM_ecc](./E_SR_SYM_ecc.svg)

* * * * * * * * * *

## Einleitung

Der `E_SR_SYM` (Event-driven SR Flip-Flop, symmetrisches Start-Up-Verhalten) ist funktional identisch zu [E_RS_SYM](E_RS_SYM.md) — beide Bausteine existieren, analog zu [E_RS](E_RS.md)/[E_SR](E_SR.md), lediglich zur Wahrung der Namenskonvention aus der IEC 61131-3 (`SR` = Set-dominant benannt, `RS` = Reset-dominant benannt), ohne dass in der IEC 61499 eine echte Dominanz zwischen Ereignissen existiert.

![E_SR_SYM](E_SR_SYM.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **S (Set)**: Setzt den Ausgang `Q` auf `TRUE`.
- **R (Reset)**: Setzt den Ausgang `Q` auf `FALSE`.

### **Ereignis-Ausgänge**

- **EO (Event Output)**: Wird nach jedem `S`- oder `R`-Ereignis ausgelöst.
    - **Verbundene Daten**: `Q`

### **Daten-Ausgänge**

- **Q**: Der aktuelle Zustand des Flip-Flops (Datentyp: `BOOL`).

## Funktionsweise

Identisch zu [E_RS_SYM](E_RS_SYM.md): Die ECC besitzt die Zustände `START`, `SET` und `RESET`. Bereits im Zustand `START` führen sowohl `S` als auch `R` zu einem definierten Folgezustand. Aus `SET`/`RESET` heraus schaltet `R` nach `RESET`, `S` nach `SET`. Jeder Übergang setzt `Q` entsprechend und löst `EO` aus.

## Technische Besonderheiten

- **Funktional identisch zu `E_RS_SYM`**: Die grafische Darstellung und Benennung (`S` vor `R` in der Schnittstelle) orientiert sich an der Konvention der IEC 61131-3, hat aber auf das tatsächliche Verhalten keinen Einfluss.
- **Symmetrisches Start-Up-Verhalten**: Wie bei `E_RS_SYM` reagiert bereits der Startzustand definiert auf beide Ereignisse.

## Zustandsübersicht

| Zustand | Bedeutung |
| --- | --- |
| START | Anfangszustand, wartet symmetrisch auf `S` oder `R` |
| SET | `Q = TRUE` |
| RESET | `Q = FALSE` |

## Anwendungsszenarien

Siehe [E_RS_SYM](E_RS_SYM.md) — identische Anwendungsfälle, `E_SR_SYM` wird bevorzugt dort eingesetzt, wo im Projekt konsequent die `SR`-Namenskonvention (Set zuerst) verwendet wird.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[E_RS_SYM](E_RS_SYM.md)**: funktional identisch, lediglich vertauschte Reihenfolge von `S`/`R` im Symbol.
- **[E_SR_SYM_INIT](E_SR_SYM_INIT.md)**: dieselbe Grundfunktion, erweitert um eine `INIT`/`INITO`-Schnittstelle.
- **[E_SR](E_SR.md)**: ohne symmetrisches Start-Up-Verhalten.

## Fazit

`E_SR_SYM` ist die zu `E_RS_SYM` namenskonventionsgleiche, funktional identische Variante des symmetrischen Set-Reset-Flipflops.

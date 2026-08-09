# Hysteresis_AR_AX

![Hysteresis_AR_AX](./Hysteresis_AR_AX.svg)

* * * * * * * * * *
## Introduction

The function block `Hysteresis_AR_AX` implements an analog-to-digital threshold circuit with hysteresis. It converts an analog input value (via an AR adapter) into a Boolean output (via an AX adapter), applying a defined hysteresis band around a mean value (threshold). The switching behavior is defined as follows:

- **Switch-on**: occurs when the input value reaches or exceeds the value `THRESHOLD + (HYSTERESIS / 2.0)` (inclusive).
- **Switch-off**: occurs when the input value falls below the value `THRESHOLD - (HYSTERESIS / 2.0)` (strict, i.e., only when <).

Durch die Hysterese wird ein stabiles Schaltverhalten erreicht, das Oszillationen um den Schwellwert vermeidet.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**

| Ereignis | Typ   | Beschreibung                     | Mit Var |
|----------|-------|----------------------------------|---------|
| `INIT`   | EInit | Initialisierungsanforderung      | `QI`    |

### **Ereignis‑Ausgänge**

| Ereignis | Typ   | Beschreibung                     | Mit Var |
|----------|-------|----------------------------------|---------|
| `INITO`  | EInit | Bestätigung der Initialisierung  | `QO`    |

### **Daten‑Eingänge**

| Name | Typ  | Beschreibung                                       |
|------|------|----------------------------------------------------|
| `QI` | BOOL | Eingangsqualifizierer – steuert die INIT‑Verarbeitung |

### **Daten‑Ausgänge**

| Name | Typ  | Beschreibung                                        |
|------|------|-----------------------------------------------------|
| `QO` | BOOL | Ausgangsqualifizierer – spiegelt den Zustand des FB |

### **Adapter**

| Adapter   | Typ              | Beschreibung                                                  |
|-----------|------------------|--------------------------------------------------------------|
| `INPUT`   | AR (unidirektional) | Analoger Eingangswert                                        |
| `THRESHOLD` | AR (unidirektional) | Mitte des Hysterese‑Bandes                                  |
| `HYSTERESIS` | AR (unidirektional) | Breite des Hysterese‑Bandes (wird als Absolutwert verwendet) |
| `OUTPUT`  | AX (unidirektional) | Digitaler Ausgang (BOOL) der Hysterese‑Entscheidung         |

## Funktionsweise

Der FB arbeitet als endlicher Automat (ECC) mit folgenden Zuständen und Übergängen:

1. **START** → **Init**
Auslöser: Eintreffen von `INIT` bei `QI = TRUE`.
Aktion: Das Initialisierungs‑Algorithmus wird ausgeführt: `QO := QI; OUTPUT.D1 := FALSE`.

2. **Init** → **sOFF**
Auslöser: Ein Ereignis am Eingangs‑Adapter `INPUT.E1`.
Der FB beginnt im ausgeschalteten Zustand.

3. **sOFF**
Aktion: Ausführen von `alOff` – setzt `OUTPUT.D1 := FALSE; QO := QI`.
Übergänge:

- Bei erneutem `INIT` mit `QI = FALSE` → **DeInit** (Deinitialisierung).
- Bei wiederholtem Ereignis `INPUT.E1` **und** der Bedingung
INPUT.D1 > = THRESHOLD.D1 + (ABS(HYSTERESIS.D1) / 2.0)) → **sON** (switch on).

4. **sON**

Action: Executing `alOn` – sets `OUTPUT.D1 := TRUE` if `QI = TRUE`; `QO` is set to `QI`.

Transitions:

- On subsequent `INIT` with `QI = FALSE` → **DeInit**
- On repeated event `INPUT.E1` **and** the condition

INPUT.D1 < THRESHOLD.D1 - (ABS(HYSTERESIS.D1) / 2.0)` → **sOFF** (Shutdown).

5. **DeInit**

Action: Execute `deInitialize` – sets `QO := FALSE; OUTPUT.D1 := FALSE`.

Transition: always (`1`) back to **START**.

Hysteresis is always calculated using the absolute value of the hysteresis, so negative inputs are also processed correctly.

## Technical Features

- **Strict Shutdown**: The shutdown condition uses a strict inequality (`<`), not `<=`. This decision (version 1.2) prevents oscillations. Exactly at the switch-off threshold.
- **Hysteresis Value**: The hysteresis value is converted to its absolute value before being halved using `ABS`. This allows the hysteresis to be passed as a negative value without changing the behavior.
- **Initialization Behavior**: After `INIT` with `QI=TRUE`, the output `OUTPUT.D1` is set to `FALSE`. It only becomes active when the switch-on threshold is exceeded.
- **Deinitialization**: Sets both `QO` and `OUTPUT.D1` to `FALSE` and returns to the START state.

## State Overview

| State | Description |
|---------|------------------------------------------------------------------------------|
| `START` | Idle state after reset; waits for first INIT. |
| `Init` | Initialization; sets output to FALSE and confirms with INITO. |
| `sOFF` | Off state; output is FALSE. |
| `sON` | On state; output is TRUE (if QI is active). |
| `DeInit` | Deinitialization; resets outputs and returns to START. |

## Application Scenarios

- **Threshold switch for sensors**: E.g., temperature, pressure, or fill level – the digital output activates a display or actuator as soon as a measured value exceeds a threshold. Hysteresis exceeded.
- **Analog signal debouncing**: Prevents rapid switching changes with noisy signals.
- **Two-point controller (on/off control)**: Directly applicable in simple control loops, e.g., heating on/off.
- **Signal conditioning in automation systems**: Conversion of analog measured values into binary control signals with defined switching behavior.

## Comparison with similar components

Common hysteresis components in IEC 61499 often differ in the definition of the switching conditions:

- **Symmetrical hysteresis** (as shown here): Threshold ± hysteresis/2 – the midpoint is the set threshold.
- **Fixed band hysteresis**: The turn-on threshold and turn-off threshold can be parameterized separately (e.g., `SWITCH_ON`, `SWITCH_OFF`).
- **Hysteresis without magnitude calculation**: The sign of the hysteresis determines the direction of the band (e.g., only positive hysteresis).

This module uses `ABS`, which makes parameterization more robust.

Compared to simple threshold switches (e.g., `GT`, `LT`), `Hysteresis_AR_AX`, thanks to its hysteresis, prevents output flutter with slowly changing or noisy signals.

## Conclusion

Hysteresis_AR_AX` is a reliable and clearly structured functional block for implementing an analog hysteresis circuit in the digital realm. The use of adapters (AR/AX) allows for easy integration into existing signal processing chains. The consistent magnitude calculation and strict turn-off ensure stable operation. Oscillation-free operation. This makes the module ideal for demanding automation tasks where precise switching points are required.

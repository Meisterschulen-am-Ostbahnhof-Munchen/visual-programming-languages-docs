# AUI_ADD_4_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUI_ADD_4`](AUI_ADD_4.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

  +--------------+          Trigger (Event an IN1..IN4)          +-------------------+
|              | --------------------------------------------> |                   |
|    IDLE      |                                               |   BERECHNUNG &    |
|  (Wartend)   | <-------------------------------------------- |   AKTUALISIERUNG  |
  +--------------+             Berechnung abgeschlossen          +-------------------+

1. **IDLE (Default State):** The function block passively waits for incoming data changes at the sockets.
2. **CALCULATION:** An event at one of the inputs triggers the summation. The result is calculated, passed to `OUT`, and an output event is generated. The function block then immediately returns to the state `IDLE`.

- **Sensor Data Fusion:** Summing up to four analog measured values (e.g., determining the total volume flow from four individual partial flows).
- **Power Calculation:** Adding the active power of four separate loads to determine the total power in an energy monitoring system.
- **Setpoint Generation:** Combining a base setpoint with up to three correction or offset values in control systems.
- **Comparison with Standard `ADD` (IEC 61131-3):** Classic `ADD` function blocks use explicit data and event pins. `AUI_ADD_4_UNGATED` bundles these signals in adapters, simplifying and standardizing wiring.
- **Comparison with `AUI_ADD_2`:** Adding three or four values with a dual adder would require cascading multiple function blocks. `AUI_ADD_4_UNGATED` saves system resources, reduces latency, and results in a cleaner application layout.

The `AUI_ADD_4_UNGATED` is a practical utility function block for advanced control projects in the 4diac IDE. It combines the basic mathematical function of addition with the structural advantages of modern adapter connections and is ideally suited for clean, clear signal processing chains.

## Introduction

## Interface Structure

### Event Inputs

### Event Outputs

### Data Inputs

### Data Outputs

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

#### **Plugs (Ausgangs-Schnittstellen)**

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

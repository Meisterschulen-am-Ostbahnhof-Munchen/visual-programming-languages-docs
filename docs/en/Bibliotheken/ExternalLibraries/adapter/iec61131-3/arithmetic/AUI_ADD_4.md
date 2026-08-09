# AUI_ADD_4

  +--------------+          Trigger (Event an IN1..IN4)          +-------------------+
|              | --------------------------------------------> |                   |
|    IDLE      |                                               |   BERECHNUNG &    |
|  (Wartend)   | <-------------------------------------------- |   AKTUALISIERUNG  |
  +--------------+             Berechnung abgeschlossen          +-------------------+

1. **IDLE (Default State):** The function block passively waits for incoming data changes at the sockets.
2. **CALCULATION:** An event at one of the inputs triggers the summation. The result is calculated, passed to `OUT`, and an output event is generated. The function block then immediately returns to the state `IDLE`.
* **Sensor Data Fusion:** Summing up to four analog measured values (e.g., determining the total volume flow from four individual partial flows).
* **Power Calculation:** Adding the active power of four separate loads to determine the total power in an energy monitoring system.
* **Setpoint Generation:** Combining a base setpoint with up to three correction or offset values in control systems.
* **Comparison with Standard `ADD` (IEC 61131-3):** Classic `ADD` function blocks use explicit data and event pins. `AUI_ADD_4` bundles these signals in adapters, simplifying and standardizing wiring.
* **Comparison with `AUI_ADD_2`:** Adding three or four values with a dual adder would require cascading multiple function blocks. `AUI_ADD_4` saves system resources, reduces latency, and results in a cleaner application layout.

The `AUI_ADD_4` is a practical utility function block for advanced control projects in the 4diac IDE. It combines the basic mathematical function of addition with the structural advantages of modern adapter connections and is ideally suited for clean, clear signal processing chains.
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

## Conclusion
# A2X_XOR_2

![A2X_XOR_2](A2X_XOR_2.svg)

* * * * * * * * * *

## Introduction

The A2X_XOR_2 function block computes the logical exclusive-OR of two [A2X](../types/unidirectional/BOOL/A2X.md) adapters — separately for the UP and DOWN channels. Like [A2X_AND_2](A2X_AND_2.md) and [A2X_OR_2](A2X_OR_2.md), it is a hand-built composite function block that internally wires two standard `XOR_BOOL_2` blocks, one per channel.

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs — events flow through the `IN1`/`IN2` adapters.

### **Event Outputs**

The function block has no direct event outputs — events flow through the `OUT` adapter.

### **Data Inputs**

The function block has no direct data inputs.

### **Data Outputs**

The function block has no direct data outputs.

### **Adapters**

**Input Adapters:**

- **IN1**: XOR input 1 (type: `adapter::types::unidirectional::A2X`)
- **IN2**: XOR input 2 (type: `adapter::types::unidirectional::A2X`)

**Output Adapter:**

- **OUT**: XOR result (type: `adapter::types::unidirectional::A2X`)

## Functionality

The block contains two internal instances of `iec61131::booleanOperators::XOR_BOOL_2`: `XOR_UP` combines the UP channels of `IN1` and `IN2`, `XOR_DOWN` the DOWN channels. When a UP event (`E_UP`) arrives on `IN1` or `IN2`, `XOR_UP.REQ` is triggered, the result of `IN1.UP XOR IN2.UP` is computed, and it is output via `OUT.E_UP`/`OUT.UP`. The DOWN channel runs the same logic independently through `XOR_DOWN`.

## Technical Details

- A genuine composite block (not the `GenericClassName` mechanism), built from two standard `XOR_BOOL_2` instances
- Two independent channels (UP/DOWN), each with its own event pair — no shared state between channels
- Since IEC 61499 allows multiple sources on an event destination but not on a data destination, one logic block is inserted per channel instead of wiring the two input values directly onto a shared variable

## State Overview

The block is a combinational logic block with no internal state; every incoming event recomputes the result directly:

- IN1.E_UP, IN2.E_UP → XOR_UP.REQ; IN1.UP, IN2.UP → XOR_UP.IN1/IN2; XOR_UP.CNF → OUT.E_UP; XOR_UP.OUT → OUT.UP
- IN1.E_DOWN, IN2.E_DOWN → XOR_DOWN.REQ; IN1.DOWN, IN2.DOWN → XOR_DOWN.IN1/IN2; XOR_DOWN.CNF → OUT.E_DOWN; XOR_DOWN.OUT → OUT.DOWN

## Application Scenarios

- Detecting contradictions between two UP/DOWN signal sources that should normally run in sync
- Toggle or exclusive-select logic where exactly one signal is allowed to be active
- Combinational logic in controllers built on A2X adapters instead of plain BOOL signals

## ⚖️ Comparison with Similar Blocks

[A2X_AND_2](A2X_AND_2.md) and [A2X_OR_2](A2X_OR_2.md) are structurally identical but use `AND_BOOL_2` and `OR_BOOL_2` instead of `XOR_BOOL_2`. The single-channel predecessor [AX_XOR_2](AX_XOR_2.md) combines only a single Boolean signal. Unlike bitwise blocks such as [AB_AND_2](../bitwiseOperators/AB_AND_2.md), A2X_XOR_2 processes individual Boolean truth values per channel.

## Conclusion

A2X_XOR_2 brings the logical exclusive-OR operation to the two-channel A2X world: two independent, event-driven XOR combinations for UP and DOWN, cleanly separated and without multiple writers on a shared variable.

# A2X_AND_2

![A2X_AND_2](A2X_AND_2.svg)

* * * * * * * * * *

## Introduction

The A2X_AND_2 function block computes the logical AND of two [A2X](../../../types/unidirectional/BOOL/A2X.md) adapters — separately for the UP and DOWN channels. Unlike the single-channel, generic `AX_AND` blocks, A2X_AND_2 is a hand-built composite function block that internally wires two standard `AND_BOOL_2` blocks, one per channel.

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

- **IN1**: AND input 1 (type: `adapter::types::unidirectional::A2X`)
- **IN2**: AND input 2 (type: `adapter::types::unidirectional::A2X`)

**Output Adapter:**

- **OUT**: AND result (type: `adapter::types::unidirectional::A2X`)

## Functionality

The block contains two internal instances of `iec61131::booleanOperators::AND_BOOL_2`: `AND_UP` combines the UP channels of `IN1` and `IN2`, `AND_DOWN` the DOWN channels. When a UP event (`E_UP`) arrives on `IN1` or `IN2`, `AND_UP.REQ` is triggered, the result of `IN1.UP AND IN2.UP` is computed, and it is output via `OUT.E_UP`/`OUT.UP`. The DOWN channel runs the same logic independently through `AND_DOWN`. Because an event destination — unlike a data destination — may have multiple sources, both `IN1.E_UP` and `IN2.E_UP` are allowed to feed into `AND_UP.REQ`; the result is recomputed on either triggering event.

## Technical Details

- A genuine composite block (not the `GenericClassName` mechanism used by `AX_AND_2`), built from two standard `AND_BOOL_2` instances
- Two independent channels (UP/DOWN), each with its own event pair — no shared state between channels
- Since IEC 61499 allows multiple sources on an event destination but not on a data destination, one logic block is inserted per channel instead of wiring the two input values directly onto a shared variable

## State Overview

The block is a combinational logic block with no internal state; every incoming event recomputes the result directly:

- IN1.E_UP, IN2.E_UP → AND_UP.REQ; IN1.UP, IN2.UP → AND_UP.IN1/IN2; AND_UP.CNF → OUT.E_UP; AND_UP.OUT → OUT.UP
- IN1.E_DOWN, IN2.E_DOWN → AND_DOWN.REQ; IN1.DOWN, IN2.DOWN → AND_DOWN.IN1/IN2; AND_DOWN.CNF → OUT.E_DOWN; AND_DOWN.OUT → OUT.DOWN

## Application Scenarios

- Safety logic where two UP/DOWN signal sources must be active simultaneously before an actuator is enabled
- Interlocks between two redundant A2X signal sources
- Combinational logic in controllers built on A2X adapters instead of plain BOOL signals

## ⚖️ Comparison with Similar Blocks

[A2X_OR_2](A2X_OR_2.md) and [A2X_XOR_2](A2X_XOR_2.md) are structurally identical but use `OR_BOOL_2` and `XOR_BOOL_2` instead of `AND_BOOL_2`. The single-channel predecessor [AX_AND_2](AX_AND_2.md) combines only a single Boolean signal and, unlike A2X_AND_2, is implemented as a generic block (`GEN_AX_AND`). Unlike [AB_AND_2](../bitwiseOperators/AB_AND_2.md), which combines a complete `BYTE` bit pattern, A2X_AND_2 processes individual Boolean truth values per channel.

## Conclusion

A2X_AND_2 brings the logical AND operation to the two-channel A2X world: two independent, event-driven AND combinations for UP and DOWN, cleanly separated and without multiple writers on a shared variable.

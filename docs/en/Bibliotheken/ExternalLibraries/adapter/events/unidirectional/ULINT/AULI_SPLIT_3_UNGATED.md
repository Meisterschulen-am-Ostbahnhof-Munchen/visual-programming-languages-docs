# AULI_SPLIT_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AULI_SPLIT_3`](AULI_SPLIT_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AULI_SPLIT_3_UNGATED](./AULI_SPLIT_3_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **AULI_SPLIT_3_UNGATED** is used to distribute a single AULI adapter signal to three identical outputs. It acts as a simple splitter for unidirectional AULI connections and enables the broadcast of a signal to multiple downstream components. The block is designed generically and can be instantiated for various AULI types.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Name | Type | Description |
| ------ | ----- | --------------- |
| IN | AULI (unidirectional) | Input adapter – receives the signal to be distributed. |
| OUT1 | AULI (unidirectional) | First output adapter. |
| OUT2 | AULI (unidirectional) | Second output adapter. |
| OUT3 | AULI (unidirectional) | Third output adapter. |

## Functionality

The function block forwards all AULI information (both events and associated data) arriving at the input adapter **IN** directly and without delay to all three output adapters **OUT1**, **OUT2**, and **OUT3**. No filtering, transformation, or buffering takes place. The outputs are identical and operate in parallel, so the input signal is sent to three independent receivers simultaneously.

## Technical Features

- **Generic Type:** The function block is declared as a generic function block (GenericClassName `'GEN_AULI_SPLIT'`). It can be used with various specific AULI adapter types, provided they conform to the unidirectional AULI interface.
- **Latency:** Due to the pure forwarding without internal logic, latency is minimal and limited to the runtime of the runtime system.
- **Copyright:** This function block is subject to the Eclipse Public License 2.0 (SPDX License Identifier: EPL-2.0).

## State Overview

The function block does not have an internal state machine. Its functionality is purely combinational and continuously active – as soon as a signal is present at the input, it is passed on to all outputs.

## Application Scenarios

- **Signal Distribution:** An AULI signal (e.g., control commands, measured values) is to be sent to several independent actuators or subsystems.
- **Test and Simulation Setups:** A test signal is recorded or sent from a source and distributed in parallel to several monitoring or analysis blocks.
- **Redundant Processing:** The same input value is required simultaneously by several parallel logic circuits.

## Comparison with Similar Function Blocks

Unlike an **AULI_MERGE** (which combines multiple inputs into one output) or an **AULI_SELECT** (which selectively passes through one of several inputs), **AULI_SPLIT_3_UNGATED** offers a pure fan-out function. There is no decision mechanism, no prioritization, and no data modification. Similar splitters with a different number of outputs (e.g., SPLIT_2) differ only in the number of outputs.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

**AULI_SPLIT_3_UNGATED** is a simple yet essential function block for multiplying unidirectional AULI signals. Its generic design and delay-free transmission make it particularly suitable for broadcast scenarios in automation technology, where a signal must be transmitted to multiple devices simultaneously.

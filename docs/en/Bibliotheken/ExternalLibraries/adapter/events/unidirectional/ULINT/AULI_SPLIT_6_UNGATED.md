# AULI_SPLIT_6_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AULI_SPLIT_6`](AULI_SPLIT_6.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AULI_SPLIT_6_UNGATED](./AULI_SPLIT_6_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **AULI_SPLIT_6_UNGATED** is used to distribute a single AULI adapter input (unidirectional) to six identical AULI outputs. It provides a generic solution for forwarding an AULI signal to multiple subsequent blocks without compromising signal integrity.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| IN | Socket (Input) | adapter::types::unidirectional::AULI | Receives the AULI signal to be distributed. |
| OUT1 | Plug (Output) | adapter::types::unidirectional::AULI | First identical output of the distributed signal. |
| OUT2 | Plug (Output) | adapter::types::unidirectional::AULI | Second identical output. |
| OUT3 | Plug (Output) | adapter::types::unidirectional::AULI | Third identical output. |
| OUT4 | Plug (Output) | adapter::types::unidirectional::AULI | Fourth identical output. |
| OUT5 | Plug (Output) | adapter::types::unidirectional::AULI | Fifth identical output. |
| OUT6 | Plug (Output) | adapter::types::unidirectional::AULI | Sixth identical output. |

## Functionality

This component functions as a pure signal distributor (splitter). An AULI signal applied to **IN** is duplicated to all six output adapters (**OUT1** to **OUT6**) without delay or data loss. No active processing or filtering takes place – data transmission occurs exclusively via the unidirectional AULI adapters.

Since there are no events or data inputs/outputs, communication is based entirely on the adapter interface. The component is event-free and is activated solely by connecting the adapters.

## Technical Features

- **Generic Type:** The function block is implemented as a generic function block (`GEN_AULI_SPLIT`), allowing it to be reused for various AULI variants.
- **Unidirectional Adapters:** The adapters used are declared as unidirectional interfaces – they only support one direction of data flow (from the socket to the plugs).
- **No Data or Event Processing:** The function block contains no internal algorithms or states; it functions solely as a passive splitter.
- **Simple Scaling:** With a fixed number of six outputs, the function block is optimized for typical applications in agricultural technology (e.g., HR agricultural technology).

## State Overview

Since the function block has no event control and manages no internal states, there is no state machine. The function block is purely combinational and passes the input signals unchanged to all outputs.

## Application Scenarios

- **Distributing a Sensor Signal:** In agricultural control systems, a single AULI sensor (e.g., for crop flow) can be connected to multiple downstream evaluation modules.
- **Parallel Actuator Controls:** A control command (e.g., for hydraulic valves) is to be simultaneously forwarded to six identical actuators.
- **Redundancy Setup:** In safety-critical applications, the same signal can be routed multiple times to redundant control units.

## Comparison with Similar Modules

| Module | Number of Outputs | Special Feature |
| ---------- | ------------------ | -------------- |
| AULI_SPLIT_6_UNGATED | 6 | Fixed splitter for AULI adapter |
| AULI_SPLIT_2 | 2 | Smaller version for two outputs |
| AULI_SPLIT_4 | 4 | Medium-sized version for four outputs |

Compared to smaller splitters, the **AULI_SPLIT_6_UNGATED** offers a higher number of outputs, reducing wiring complexity in complex systems while maintaining a clean signal structure.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **AULI_SPLIT_6_UNGATED** is a simple yet effective function block for distributing an AULI adapter signal to six parallel outputs. Thanks to its generic implementation and pure adapter interface, it can be easily integrated into IEC 61499 applications in agricultural and automation technology. It is particularly suitable for scenarios where a signal is required multiple times without additional logic or state management.

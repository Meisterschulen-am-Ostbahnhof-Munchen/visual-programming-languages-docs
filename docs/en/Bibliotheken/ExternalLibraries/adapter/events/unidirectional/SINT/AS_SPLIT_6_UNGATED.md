# AS_SPLIT_6_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AS_SPLIT_6`](AS_SPLIT_6.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AS_SPLIT_6_UNGATED](./AS_SPLIT_6_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **AS_SPLIT_6_UNGATED** is used to split a single incoming AS adapter signal into six separate AS adapter outputs. It is implemented as a generic block and can be used with various unidirectional AS adapter types (e.g., sensor or actuator adapters).

## Interface Structure

### **Event Inputs**

– None –

### **Event Outputs**

– None –

### **Data Inputs**

– None –

### **Data Outputs**

– None –

### **Adapter**

| Direction | Name | Type |
| ---------- | ------ | ----- |
| SOCKET | IN | unidirectional::AS (generic) |
| PLUG | OUT1 | unidirectional::AS (generic) |
| PLUG | OUT2 | unidirectional::AS (generic) |
| PLUG | OUT3 | unidirectional::AS (generic) |
| PLUG | OUT4 | unidirectional::AS (generic) |
| PLUG | OUT5 | unidirectional::AS (generic) |
| PLUG | OUT6 | unidirectional::AS (generic) |

## Functionality

This component forwards all adapter signals present at the SOCKET **IN** unchanged to all six PLUGs (**OUT1** to **OUT6**). No data processing or conversion takes place – the distribution is purely structural. Therefore, all outputs behave identically to the inputs.

## Technical Features

- **Generic Block:** The specific AS adapter type is only defined during instantiation (e.g., by specifying a GenericClassName such as `'GEN_AS_SPLIT'`). This allows the block to be used with various protocols or data structures.
- **No State Logic:** The block has no state machine, no algorithms, and no events – it operates purely passively and immediately.
- **Unidirectional:** The adapters are of type `unidirectional::AS`, meaning data flows only from the input to the outputs.

## State Overview

The block does not have an End-Centre Conditioning (ECC) function, as no sequential processes or processing steps are defined. Signal distribution is static and continuous.

## Application Scenarios

- **Signal Multiplication:** A single sensor adapter (e.g., temperature measurement) is provided to multiple processing units.
- **Data Bus Coupling:** A common signal is passed on to six parallel control modules or displays.
- **Prototyping and Testing:** Simplified generation of multiple identical interfaces from a single source.

## Comparison with Similar Function Blocks

- **AS_SPLIT_2 / AS_SPLIT_4** – Identical functionality, but with only two or four outputs, respectively. This function block is suitable for applications with exactly six destinations.
- **AS_MERGE_...** – Combines multiple adapter inputs into one output – the opposite task.
- **Manual Wiring** – Could be implemented using multiple adapter couplings, but increases the configuration effort.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **AS_SPLIT_6_UNGATED** is a simple yet effective generic function block for splitting a unidirectional AS signal into six separate outputs. Its generic nature allows for flexible use in various automation environments where fast and clear signal duplication is required.

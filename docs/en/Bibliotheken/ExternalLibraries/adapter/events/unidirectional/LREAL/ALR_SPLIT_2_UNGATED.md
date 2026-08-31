# ALR_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALR_SPLIT_2`](ALR_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALR_SPLIT_2_UNGATED](./ALR_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The ALR_SPLIT_2_UNGATED function block splits an incoming ALR adapter signal into two identical output signals. It is designed generically (`GEN_ALR_SPLIT`) and is suitable for distributing alarm or lifecycle signals.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

#### **Data Outputs**

None

#### **Adapter**

- **IN** (Socket): Type `adapter::types::unidirectional::ALR` – Input adapter for the ALR signal.
- **OUT1** (Plug): Type `adapter::types::unidirectional::ALR` – first output adapter.
- **OUT2** (Plug): Type `adapter::types::unidirectional::ALR` – second output adapter.

## Functionality

The function block forwards the ALR signal received via socket `IN` unchanged to both plugs `OUT1` and `OUT2`. No transformation or delay occurs. The signal is passively split.

## Technical Features

- The function block is implemented as a generic function block (attribute `GenericClassName` = `'GEN_ALR_SPLIT'`).
- Unidirectional adapters of type `ALR` are used, which only support one direction of data flow.
- No internal timers, states, or events – pure signal distribution.

## State Overview

This function block has no state machines. Its behavior is determined solely by the adapter definition.

## Application Scenarios

- Distribution of an ALR signal (e.g., alarm, temperature limit) to two different receivers.
- As part of a logic circuit that needs to evaluate an alarm signal multiple times.
- Use in control systems that forward a signal in parallel to two function blocks.

## Comparison with Similar Function Blocks

- **ALR_SPLIT_2_UNGATED** splits an ALR signal to two outputs; comparable to event splitters like `E_SWITCH` or `E_SPLIT`, but for ALR adapters.
- Unlike data-based splitters (`MUX`, `F_SPLIT`), no data manipulation takes place here.
- Variants with more outputs may exist (e.g., `ALR_SPLIT_4`), allowing for a higher number of distributions.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

ALR_SPLIT_2_UNGATED` is a simple and effective component for splitting an incoming ALR adapter signal to two outputs. Due to its generic nature and lack of logic, it is ideally suited for clean signal distribution in IEC 61499 systems.

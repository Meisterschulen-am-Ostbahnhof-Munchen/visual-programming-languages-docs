# AX_OR_9_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AX_OR_9`](AX_OR_9.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

<img width="960" height="503" alt="image" src="https://github.com/user-attachments/assets/8e2166fd-c540-4651-a06b-83a9435a923c" />
* * * * * * * * * *
## Introduction

The AX_OR_9_UNGATED is a generic function block for calculating the Boolean OR operation with nine inputs. This block is used for the logical processing of signals in automation systems and outputs the result of the OR operation on all input signals.
![AX_OR_9_UNGATED](AX_OR_9_UNGATED.svg)

## Interface Structure

### **Event Inputs**

*No event inputs available*

### **Event Outputs**

*No event outputs available*

### **Data Inputs**

*No direct data inputs available*

### **Data Outputs**

*No direct data outputs available*

### **Adapters**

**Sockets (Inputs):**

- **IN1** - OR Input 1
- **IN2** - OR Input 2
- **IN3** - OR Input 3
- **IN4** - OR Input 4
- **IN5** - OR Input 5
- **IN6** - OR Input 6
- **IN7** - OR Input 7
- **IN8** - OR Input 8
- **IN9** - OR Input 9

**Plugs (Outputs):**

- **OUT** - OR Result

## Functionality

The function block continuously calculates the Boolean OR operation of all nine input signals. The output signal is TRUE (1) if at least one of the nine inputs is TRUE (1). Only if all inputs are FALSE (0) will the output also be FALSE (0).

## Technical Features

- Generic function block with a fixed number of 9 inputs
- Uses unidirectional AX adapters for inputs and outputs
- No event-driven control - operates continuously
- Implemented as a generic function block with a specific class name

## State Overview

The function block has no internal state and operates stateless. The output is calculated solely based on the current input values.

## Application Scenarios

- Safety circuits with multiple emergency stop buttons
- Monitoring systems with multiple sensors
- Control logic with redundant input signals
- Alarm systems with multiple triggers

## ⚖️ Comparison with similar function blocks

Compared to standard OR function blocks with fewer inputs, AX_OR_9_UNGATED offers the ability to process up to nine signals simultaneously, simplifying the wiring of more complex logic. Unlike configurable OR function blocks, this block has a fixed number of inputs, simplifying configuration for known requirements.

Comparison with [OR_9](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_9.md)

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The AX_OR_9_UNGATED is a specialized OR function block for applications that need to logically combine exactly nine input signals. Its fixed number of inputs and simple operation make it particularly suitable for clearly defined control tasks with redundant input signals.

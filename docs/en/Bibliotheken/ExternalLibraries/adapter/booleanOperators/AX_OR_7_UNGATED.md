# AX_OR_7_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AX_OR_7`](AX_OR_7.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

<img width="960" height="436" alt="image" src="https://github.com/user-attachments/assets/239ec61a-ac42-409e-9a51-94394f41ef93" />
* * * * * * * * * *
## Introduction

The AX_OR_7_UNGATED function block is a generic function block for calculating Boolean OR operations. It has seven inputs and calculates the logical OR of all input signals.
![AX_OR_7_UNGATED](AX_OR_7_UNGATED.svg)

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No direct data inputs available.

### **Data Outputs**

No direct data outputs available.

### **Adapters**

**Input Adapter:**

- **IN1** - OR Input 1
- **IN2** - OR Input 2
- **IN3** - OR Input 3
- **IN4** - OR Input 4
- **IN5** - OR Input 5
- **IN6** - OR Input 6
- **IN7** - OR Input 7

**Output Adapter:**

- **OUT** - OR Result

All adapters use the type `adapter::types::unidirectional::AX`.

## Functionality

The function block continuously calculates the Boolean OR operation of all seven input signals. The result is output via the output adapter OUT. The output signal is TRUE if at least one of the seven inputs is TRUE.

## Technical Features

- Generic function block with the class 'GEN_AX_OR'
- Uses unidirectional AX adapters for all interfaces
- No event control - operates continuously
- Seven independent inputs for maximum flexibility

## State Overview

Since it is a purely combinational function block without event control, the AX_OR_7_UNGATED does not have a state machine. The output is calculated directly from the current input values.

## Application Scenarios

- Safety circuits with multiple emergency stop buttons
- Multiple operator stations in machine controls
- Monitoring systems with multiple sensors
- Linking multiple enable signals

## ⚖️ Comparison with Similar Function Blocks

Compared to standard OR blocks, the AX_OR_7_UNGATED offers the unique feature of seven inputs, which simplifies wiring because fewer blocks need to be connected in series. The use of adapters instead of direct data connections allows for more flexible integration into various system architectures.

Comparison with [OR_7](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_7.md)

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The AX_OR_7_UNGATED is a specialized OR gate for applications with many input signals. With its seven inputs and adapter-based interface, it is particularly suitable for complex control tasks where multiple signals need to be logically combined.

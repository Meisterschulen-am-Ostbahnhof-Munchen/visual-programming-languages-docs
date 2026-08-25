# SET_REAL

![SET_REAL](./SET_REAL.svg)

* * * * * * * * * *
## Introduction

The function block **SET_REAL** is used to write a REAL value from a data input to an InOut variable. It is a simple, event-driven function block that, upon receiving a request (REQ), passes the current input value IN to the referenced variable OUT and acknowledges the operation with a confirmation event (CNF).
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| REQ | Event | Normal execution request (connected to IN and OUT) |

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| CNF | Event | Execution Confirmation (connected to OUT) |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|-----|--------------|--------------|
| IN | REAL | 0.0 | Value to be written |
| OUT | REAL (InOut) | 0.0 | Target variable (InOut – read and write) |

### **Data Outputs**

No separate data outputs are available. The InOut parameter OUT also functions as an output and is updated after assignment.

### **Adapters**

None.

## Functionality

The FB has a single execution state **REQ**. As soon as an event arrives at the **REQ** input, the defined algorithm is executed:

OUT := IN;
The current value of IN is assigned to the InOut variable OUT. The **CNF** event is then triggered to signal the completion of the operation. The process is atomic and requires no further state transitions.

## Technical Features

- **InOut Parameter OUT**: The variable OUT is both readable and writable. It is directly referenced by the calling environment, so the assignment immediately changes the value at the original address.
- **Initial Values**: Both IN and OUT are initialized to 0.0. This prevents undefined states before the first execution.
- **Simplicity**: The function block consists of only one state and one algorithm, guaranteeing very low runtime complexity.

## State Overview

| State | Description | Action | Output |
|---------|--------------|---------|---------|
| REQ | Wait for execution request | Execute algorithm REQ → OUT := IN | CNF |

No further state exists; the function block immediately returns to the waiting REQ state after execution.

## Application Scenarios

- **Parameter setting**: Passing a REAL value to a global configuration variable, e.g., for scaling or setpoints.
- **Initialization**: Setting an InOut variable to a defined start value during commissioning.
- **Value copy within an application**: Easily overwriting an existing REAL variable with a different value, triggered by an event.

## Comparison with similar function blocks

| FB | Type | Difference |
|----|-----|-------------|
| **SET_BOOL** | BOOL | Writes Boolean values, analogous functionality |
| **SET_INT** | INT | Writes integers, identical event control |
| **MOVE** (generic) | ANY | Can copy any data type, but requires type matching and often has multiple states |
| **SET_REAL** | REAL | Specifically optimized for REAL, minimal states and clear semantics |

Compared to a generic MOVE block, SET_REAL offers a leaner implementation and is tailored to the frequently used REAL type.

## Conclusion

The **SET_REAL** function block is a simple yet effective block for setting a REAL variable. Thanks to its minimal state machine and direct use of InOut parameters, it is ideally suited for event-driven assignments in IEC 61499 applications. It reduces complexity and increases the readability of the control code.

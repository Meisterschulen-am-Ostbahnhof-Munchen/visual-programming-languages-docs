# AX_NOOP

![AX_NOOP](./AX_NOOP.svg)

* * * * * * * * * *

## Introduction

The function block **AX_NOOP** (No Operation) serves as a pure pass-through function. It connects an incoming adapter (`IN`) directly to an outgoing adapter (`OUT`) without modifying data or processing events. This function block is designed as a basic block for testing, debugging, and placeholder purposes.

## Interface Structure

### **Event Inputs**

No direct event inputs are available.

Events are received via the adapter `IN`.

## **Event Outputs**

No direct event outputs are available.

Events are passed on via the adapter `OUT`.

### **Data Inputs**

No direct data inputs available.

Data is received via the `IN` adapter.

### **Data Outputs**

No direct data outputs available.

Data is passed on via the `OUT` adapter.

### **Adapters**

| Type | Name | Direction | Comment |
| ----- | ------ | ---------- | ----------- |
| `adapter::types::unidirectional::AX` | IN | Socket (Input) | Receives events and data |
| `adapter::types::unidirectional::AX` | OUT | Plug (Output) | Passes on events and data unchanged |

## Functionality

This module establishes a point-to-point connection between the input adapter `IN` and the output adapter `OUT`. Internally, the following connections are implemented:

- **Event Connection**: `IN.E1` → `OUT.E1`
- **Data Connection**: `IN.D1` → `OUT.D1`

Every incoming event at `IN.E1` is immediately forwarded to `OUT.E1`. Every data value at `IN.D1` is passed on unchanged to `OUT.D1`. No logic, delay, or state change occurs.

## Technical Features

- Pure passthrough without processing.
- Uses the adapter type `AX` for communication.
- No modifiable parameters or configurations.
- Ideally suited as a placeholder or for debugging adapter connections in the 4diac IDE.

## State Overview

The function block does not have its own state machine. Its behavior is static and corresponds to direct wiring.

## Application Scenarios

- **Test Environments**: Replacing a complex function block during the test phase to check the wiring.
- **Debugging**: Injecting a measurement or trace point into an adapter path.
- **Placeholder**: Temporarily inserting during the step-by-step implementation of a larger system.
- **Adapter Transparency**: Checking whether an adapter type is correctly connected without functional logic.

## Comparison with Similar Function Blocks

| Function Block | Description | Difference |
| ---------- | -------------- | ------------- |
| `E_NOP` | Event NOP with direct event/data inputs/outputs | Uses standard I/O instead of adapters |
| `MUX` | Selection between multiple data sources | Provides selection, not pure passthrough |
| `BYE` | Explicit end-of-service marker | Has special semantics, not passthrough |
| **AX_NOOP** | Pure adapter passthrough | Specifically designed for the adapter type `AX` |

## Conclusion

The **AX_NOOP** is a minimalist yet useful component for working with adapter interfaces. Thanks to its simple pass-through functionality, it is ideally suited for testing, debugging, and as a placeholder in the 4diac IDE. Despite lacking its own logic, it plays a crucial role in the step-by-step development and verification of connection-intensive applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

# OFF_TO_ALR

![AUS_TO_ALR](./AUS_TO_ALR.svg)

* * * * * * * * * *
## Introduction

The **OFF_TO_ALR** function block is a composite function block that converts an **OFF adapter** (with USINT data) into an **ALR adapter** (with LREAL data). It serves purely as a forwarding interface and does not perform any complex logic or conversion calculations.
## Interface Structure

### **Event Inputs**

No separate event inputs are available. Event forwarding is handled via the **OFF_IN** adapter.

### **Event Outputs**

No separate event outputs are available. Event forwarding is handled via the **ALR_OUT** adapter.

### **Data Inputs**

No separate data inputs are available. Data is forwarded via the **AUS_IN** adapter.

### **Data Outputs**

No separate data outputs are available. Data is forwarded via the **ALR_OUT** adapter.

### **Adapters**

| Role | Name | Type | Comment |
|-------|------|-----|-----------|
| **Socket (Input)** | AUS_IN | `adapter::types::unidirectional::AUS` | USINT Adapter Input |
| **Plug (Output)** | ALR_OUT | `adapter::types::unidirectional::ALR` | LREAL Adapter Output |

- The **AUS_IN** adapter provides the interface for incoming USINT data, including an associated event.
- The **ALR_OUT** adapter provides the interface for outgoing LREAL data, including an associated event.
- Inside the function block, the events (`E1`) and data (`D1`) are directly routed from the *AUS_IN* interface to the *ALR_OUT* interface.

## Functionality

1. **Event Forwarding**: The event (`E1`) received by the **AUS_IN** adapter is passed unchanged to the **ALR_OUT** adapter (`E1`).
2. **Data Forwarding**: The data value (`D1`) from the **OFF_IN** adapter is passed directly to the **ALR_OUT** adapter (`D1`).
3. **Data Type Conversion**: The actual conversion from `USINT` (8-bit integer value) to `LREAL` (64-bit floating-point number) does **not take place within the function block** – the **OFF_TO_ALR** block merely provides a structural framework for this. The conversion must be implemented either by the connected adapters or by upstream function blocks.

The function block itself contains no computation logic or state machine; it consists solely of connections between the adapters.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Function Block**: The function block is implemented as a composite function block (CFB) whose internal network contains only two connections.
- **No Internal Logic**: All functionality is provided by external function blocks or the adapter implementation.
- **Type Compliance**: The connection between `AUS.D1` (USINT) and `ALR.D1` (LREAL) requires that the underlying adapter implementation allows implicit type conversion. For caution, explicit conversion outside the function block is necessary.

## State Overview

The function block has **no internal state machine**. It operates transparently: As soon as an event arrives at the input adapter, it is immediately forwarded to the output adapter. There are no delays, storage, or internal states.

## Application Scenarios

- **Connecting Heterogeneous Control Systems**: A sensor delivers values as USINT via an AUS adapter, while the subsequent control module expects LREAL via an ALR adapter.
- **Structural Adaptation**: The function block (FB) serves as a pure conversion adapter when protocol/interface adapter types use different data formats.
- **Test and Simulation Environments**: Simple pass-through of data and events for testing adapter communication.

## Comparison with Similar Function Blocks

| Feature | AUS_TO_ALR | Typical Conversion FBs (e.g., USINT_TO_LREAL) |
|---------|------------|-----------------------------------------------------|
| Input / Output | Adapter Interfaces | Individual Data Inputs/Outputs |
| Event Processing | Pass-Through via Adapter | Custom Event I/C Pairs |
| Implementation | Composite (Connections Only) | Executable Algorithms |
| Type Conversion | Not Included in the Function Block | Explicit Conversion via Algorithm |

While a classic *USINT_TO_LREAL* function block performs the value conversion itself, **AUS_TO_ALR** only provides adapter adaptation. A separate function block must be interposed for the actual data conversion.

## Conclusion

The **AUS_TO_ALR** function block is a simple yet useful composite block for structural adaptation between an AUS and an ALR adapter. It does not perform data conversion but enables the seamless forwarding of events and values between different adapter interfaces. Due to its minimalist design, it is particularly suitable for integration and testing tasks where the actual type conversion is performed externally.

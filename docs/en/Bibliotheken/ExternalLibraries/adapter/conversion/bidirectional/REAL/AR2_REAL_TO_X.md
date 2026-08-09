# AR2_REAL_TO_X

![AR2_REAL_TO_X](./AR2_REAL_TO_X.svg)

* * * * * * * * * *
## Introduction

The function block `AR2_REAL_TO_X` is a composite function block (FB) for converting a REAL value into an AR2 format. It encapsulates a bidirectional adapter of type `adapter::types::bidirectional::AR2` and acts as a transparent interface between a simple REAL variable and the more complex AR2 data type. The conversion logic resides entirely within the adapter, while the FB only handles signal and data transmission.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| `REQ` | Request for processing via the adapter (triggers adapter output) |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| `CNF` | Confirmation after adapter processing is complete |

### **Data Inputs**

| Variable | Type | Comment |
|----------|------|-----------|
| `OUT` | REAL | Output data sent to the adapter (actually: input value for conversion) |

### **Data Outputs**

| Variable | Type | Comment |
|----------|------|----------------------------------------------|
| `IN` | REAL | Input data returned by the adapter (actually: converted value) |

### **Adapter**

| Adapter | Type | Comment |
|---------|-----------------------------------------|-----------------------|
| `AR2_OUT` | `adapter::types::bidirectional::AR2` | Bidirectional interface adapter for AR2 conversion |

## Functionality

The function block operates as a simple forwarding block:

1. An incoming event at the **event input `REQ`** is forwarded directly to the event output `EO1` of the adapter `AR2_OUT`.
2. The current value of the **data input `OUT`** is simultaneously sent to the data output `DO1` of the adapter.
3. The adapter internally performs the conversion from REAL to AR2 format (and back if necessary) and sends an acknowledgment event back via its event input `EI1`.
4. This event is passed on to the **event output `CNF`** of the function block.
5. The value provided by the adapter at its data input `DI1` is transferred to the **data output `IN`** of the function block.

The actual conversion (REAL ↔ AR2) takes place exclusively within the adapter – the function block itself does not perform any arithmetic operations.

## Technical Features

- **Composite Block**: The functionality is implemented through the internal wiring of an external adapter type. The function block is therefore dependent on the implementation of the adapter `adapter::types::bidirectional::AR2`.
- **Bidirectional Data Flow**: The variable names (`OUT` as input, `IN` as output) can be confusing. In reality, the data flows as follows:
- REAL value → Adapter → AR2 object (forward)
- AR2 object → Adapter → REAL value (reverse)

The function block provides both directions via the event handlers `REQ` / `CNF`.

- **No State Logic**: The function block (FB) does not have its own state machine – all processes are event-driven and direct.

## State Overview

Since the FB does not have an internal state machine, there is no classic state overview. The process is purely sequential per event:

1. Wait for `REQ`
2. Send to adapter
3. Wait for adapter response
4. Output of `CNF` and updated `IN`

## Application Scenarios

- **Interface to External Systems**: When an external device or another function block expects data in AR2 format, but the user code works with REAL values.
- **Data Preprocessing**: Integration into a chain of conversion blocks to convert REAL data into a specific binary or structured format (AR2).
- **Testing and Simulation**: Used in test environments to verify adapter functionality without requiring in-depth knowledge of the adapter itself.

## Comparison with Similar Function Blocks

- **AR2_REAL_TO_X vs. Simple Type Conversion (REAL_TO_INT etc.)**:

Simple converters work directly with elementary data types. `AR2_REAL_TO_X`, on the other hand, uses an adapter that encapsulates a complex conversion (e.g., to an array or structure).

- **AR2_REAL_TO_X vs. Direct Adapter Use**:

The function block simplifies handling by performing the signal wiring (event and data connections). The user only needs to instantiate the function block and connect it to their code.

- **AR2_REAL_TO_X vs. CONVERT Adapter Blocks**:

Similar blocks (e.g., from the IEC 61499 library) usually offer generic conversion. This function block is specifically for coupling REAL and AR2.

## Conclusion

The function block `AR2_REAL_TO_X` provides a simple, event-driven interface for using a bidirectional AR2 adapter. It is ideal for all applications that require conversion between the standard REAL data type and a project-specific AR2 format. Its design keeps the complexity hidden within the adapter, and the block can be integrated into applications like a normal function block.

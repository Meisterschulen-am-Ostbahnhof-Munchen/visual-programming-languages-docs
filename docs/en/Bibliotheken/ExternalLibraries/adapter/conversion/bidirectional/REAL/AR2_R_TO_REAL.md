# AR2_R_TO_REAL

![AR2_R_TO_REAL](./AR2_R_TO_REAL.svg)

* * * * * * * * * *

## Introduction

The **AR2_R_TO_REAL** function block is a composite module that acts as a bridge between an AR2 adapter interface and REAL values. It enables bidirectional data transfer and conversion, with the actual conversion being performed by an external adapter of type `adapter::types::bidirectional::AR2`.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|---------------|
| `REQ` | Starts data transfer to the adapter. The data value `OUT` is sent. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Acknowledges the adapter's response. The converted value is stored as `IN`. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `OUT` | REAL | Data value passed to the adapter. |

### **Data Outputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `IN` | REAL | Converted value returned by the adapter. |

### **Adapter**

| Name | Type | Direction | Description |
|-----------|------------------------------------------|----------|-------------|
| `AR2_IN` | `adapter::types::bidirectional::AR2` | Socket | Bidirectional adapter for AR2 communication and conversion. |

## Functionality

The module functions purely as a mediation layer:

1. An incoming event `REQ` triggers the transfer of the value `OUT` (REAL) to the connected adapter (via `AR2_IN.DI1`).
2. The adapter performs the necessary conversion (e.g., AR2 ↔ REAL) and sends an acknowledgment event to its output `EO1`.
3. This event is forwarded externally as `CNF`, and the converted value is made available via `AR2_IN.DO1` as `IN` (REAL).

The actual conversion direction is determined by the implementation of the connected adapter. The name of the function block suggests a primary conversion from AR2 to REAL, but the bidirectional adapter interface also allows for the reverse direction.

## Technical Features

- **Composite Function Block**: Contains no internal logic; it simply combines an adapter socket with event and data connections.
- **Bidirectional Adapter**: The interface `AR2_IN` must provide an adapter of type `adapter::types::bidirectional::AR2`, which implements the actual conversion.
- **Simple Coupling**: The function block separates the REAL world from the AR2 world, thus enabling modular integration.

## State Overview

The function block has no internal states of its own. Its behavior is entirely controlled by the external events `REQ` and the adapter's feedback.

## Application Scenarios

- **Connecting AR2-based sensors/actuators** to a control system that uses REAL values.
- **Bidirectional data bridge** in mixed automation environments where AR2 and REAL protocols interact.
- **Test and simulation setups** where AR2 data needs to be replaced with easily manageable REAL values.

## Comparison with Similar Components

While direct conversion components (e.g., AR2_TO_REAL) hardwire the conversion, this composite component allows for the flexible connection of an external adapter. This decouples the conversion logic, allowing it to be replaced depending on the application without changing the rest of the configuration.

## Conclusion

The **AR2_R_TO_REAL** is a useful bridging component for systems that need to process both AR2 and REAL data. By using a bidirectional adapter, a clear separation between the interface and the conversion logic is achieved, which improves reusability and maintainability.

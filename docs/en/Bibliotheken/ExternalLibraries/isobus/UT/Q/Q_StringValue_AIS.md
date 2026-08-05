# Q_StringValue_AIS
![Q_StringValue_AIS](./Q_StringValue_AIS.svg)
* * * * * * * * * *
## Introduction
The function block **Q_StringValue_AIS** implements the "Command Change String Value" service according to ISO 11783-6 (Part 6, Section F.24). It is used to send a new string value to a connected device via an ISOBUS network. The block encapsulates all the logic for initialization, sending the command, and returning the result. The new string value is input via a unidirectional adapter (AIS), which provides the actual data.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|-------|-------------------------------------------------|

| INIT | EInit | Service initialization, sets the object ID |

### **Event Outputs**

| Event | Type | Comment |

|----------|-------|---------------------------------------------------|

| INITO | EInit | Confirmation of successful initialization |

| CNF | Event | Confirmation of the requested service (result) |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|----------|------|--------------|-----------------------------|

| u16ObjId | UINT | ID_NULL | Object ID of the value to be changed |

### **Data Outputs**

| Name | Type | Comment |

|-----------|-------|----------------------------------------------------|

| STATUS | STRING | Service status (e.g., "IDLE", "BUSY", "ERROR") |

| s16result | INT | Return value (see service description) |

### **Adapter**

| Name | Type | Comment |

|------------|------------------------------------|----------------------------------|

| pau8String | adapter::types::unidirectional::AIS | Returns the new string value |

## Functionality

The function block internally contains an instance of the function block `Q_StringValue` (from the library `isobus::UT::Q`), which performs the actual ISOBUS communication. The wiring is as follows:

1. **Initialization**: An INIT event at the input activates the internal `Q_StringValue` function block. The provided `u16ObjId` is forwarded to this device.

2. **Triggering the Service**: As soon as the adapter `pau8String` receives an event (E1), the REQ event of the internal block is triggered. Simultaneously, the string value is passed to `Q_StringValue.pau8String` via the adapter's data output D1.

3. **Feedback**: After processing is complete, the internal block outputs the events `INITO` and `CNF`, whose output data (`STATUS`, `s16result`) are directly passed to the corresponding outputs of the overall block.

All the logic is implemented in the included `Q_StringValue` block; the `Q_StringValue_AIS` serves as a specialized package with an adapter input.

## Technical Features
- The block complies with the **ISO 11783-6** (ISOBUS) specification, Part 6, "Command Change String Value" service.
- The implementation uses a **unidirectional adapter** (`adapter::types::unidirectional::AIS`) that only transmits data from the host to the block. This simplifies integration into control systems where the new string value is provided asynchronously.
- The initial value of `u16ObjId` is `ID_NULL` – this must be set to a valid object ID before first use.
- The outputs `STATUS` and `s16result` provide the status and return value of the service as soon as the `CNF` event is triggered. The exact values are defined in the underlying service description.

## State Overview

The function block itself does not have an explicit internal state machine, as the state logic is entirely contained within `Q_StringValue`. Essentially, the following phases can be distinguished:

- **Idle**: After starting or after a successful/failed execution – the function block waits for an INIT or an event on the adapter.
- **Initialization**: Active through INIT until the INITO event is sent.
- **Service Active**: After being triggered by the adapter, until the CNF event arrives.
- **Errors**: In case of invalid parameters or communication errors, a corresponding status/return value is provided.

## Application Scenarios
- **ISOBUS Command:** Changing a string parameter on an agricultural device (e.g., machine name, task, variable name) via the ISOBUS network.
- **Control Systems:** Connection to a PLC or HMI that provides the new string value via an adapter (e.g., from a text box, a database field, or a communication channel).
- **Test Environments:** Simulating the service for development and testing purposes.

## Comparison with Similar Function Blocks

The `Q_StringValue_AIS` function block is a specialized variant of the `Q_StringValue` function block, which already includes all ISOBUS communication. The difference lies in the input interface: While `Q_StringValue` receives the string value via a standard data input `pau8String` (of type `STRING` array), `Q_StringValue_AIS` uses an adapter (AIS) that can supply data asynchronously. The adapter enables loose coupling and facilitates reuse in different contexts, for example, when the string value is provided by another, independent function block.

Other similar function blocks from the ISO 11783-6 family handle different data types (e.g., `Q_NumberValue_AIS` for numeric values).

## Conclusion

The `Q_StringValue_AIS` is a practical, standards-compliant function block for modifying string values in an ISOBUS context. Using an adapter makes integration flexible and modular. It is particularly suitable for applications where the new value is provided asynchronously or from external sources. The clear separation of initialization and service execution, as well as the standardized outputs, facilitate debugging and reuse.
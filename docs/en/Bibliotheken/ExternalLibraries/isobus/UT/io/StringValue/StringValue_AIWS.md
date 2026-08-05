# StringValue_AIWS
![StringValue_AIWS](./StringValue_AIWS.svg)
* * * * * * * * * *
## Introduction
The function block **StringValue_AIWS** is an input-service interface block for processing wide-string data (UTF-16) in an ISOBUS context. It provides an adapter-based interface through which external resources can input strings. The block acts as a wrapper for the internal block *StringValue_IWS* and offers a standardized initialization and request interface.
## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Comment |

|---|---|---|---|

| `INIT` | EInit | `QI`, `PARAMS`, `u16ObjId` | Service Initialization |

| `REQ` | Event | `QI` | Service Request (Query) |

### **Event Outputs**

| Event | Type | With Variables | Comment |

|---|---|---|---|

| `INITO` | Initialization | `QO`, `STATUS` | Initialization Acknowledgement |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|---|---|---|---|

| `QI` | BOOL | – | Event Qualifier (Share) |

| `PARAMS` | STRING | – | Service Parameter (e.g., Configuration String) |

| `u16ObjId` | UINT | `ID_NULL` | Object ID (e.g., ISOBUS Object Identifier) |

### **Data Outputs**

| Name | Type | Comment |

|---|---|---|

| `QO` | BOOL | Output Qualifier (Status of Last Operation) |

| `STATUS` | STRING | Status message (e.g., error message or success message) |

### **Adapter**

| Name | Type | Comment |

|---|---|---|

| `IN` | `adapter::types::unidirectional::AIWS` | Input of wide-string data from the resource (unidirectional) |

The adapter `IN` receives the actual strings and makes them available to the function block. The connection is established via the event line `E1` and the data channel `D1`.

## Functionality

The function block initializes the internal *StringValue_IWS* function block via the event `INIT`. The parameters `QI`, `PARAMS`, and `u16ObjId` are passed to this event. After successful initialization, the event `INITO` is triggered, and the output variables `QO` and `STATUS` are set.

The event `REQ` initiates a request to provide a new wide-string value. The actual string is delivered asynchronously via the adapter `IN`: As soon as the internal module receives a new string, it sends an event (`IND` or `CNF`) to the adapter output `E1`, and the data is then passed to the connected resource via the data channel `D1`.

The module encapsulates all the logic for initialization and communication with the underlying wide-string service and provides a uniform adapter interface to the outside.

## Technical Features
- **Wide-String Support**: The module is designed for UTF-16 (Wide Strings) and is therefore particularly suitable for international character sets (Unicode).
- **Adapter-based communication**: The use of a unidirectional adapter (`AIWS`) allows for a clean separation between service logic and the resource interface.
- **ISOBUS compliance**: The object ID (`u16ObjId`) is assigned the initial value `ID_NULL`, indicating ISOBUS-specific assignment.
- **Event-driven processing**: Both initialization and data requests are triggered by explicit events, making the function block suitable for use in time-critical environments.

## State overview

The function block does not have an explicit state machine; its behavior is controlled by events:

1. **Idle state** – The function block waits for `INIT` or `REQ`.

2. **Initialization** – After `INIT`, the parameters are passed to the internal function block; outputs `QO` and `STATUS` are updated, and `INITO` is sent.

3. **Request State** – After `REQ`, a data request is initiated. The response is asynchronous via the adapter `IN` (event `E1`).

4. **Error Handling** – If an error occurs during initialization, `QO` is set to `FALSE`, and a corresponding message `STATUS` is output.

## Application Scenarios
- **Input of Unicode text** into agricultural operator terminals (ISOBUS-UT) – e.g., for vehicle names, field names, or product designations.
- **Configuration interface** for ISOBUS devices that require wide-string parameters.
- **Connection of external input devices** (keyboards, touchscreens) to an ISOBUS control unit via a standardized adapter interface.

## Comparison with Similar Modules

| Module | Interface | Special Feature |

|---|---|---|

| `StringValue_AIWS` | Adapter (Input) | Receives wide-strings via the adapter `AIWS` |

| `StringValue_IWS` | Direct Events/Data | Internal logic, no adapter interface |

| `StringValue` (Standard) | Events/Data | Simple Wide-String Input (without adapter) |

The `StringValue_AIWS` stands out due to its adapter-based interface, which enables loose coupling between resource and service. It is particularly suitable for modular systems where the data source can change dynamically.

## Conclusion

The **StringValue_AIWS** is a robust input-service interface block for wide-string data in ISOBUS systems. By combining event-driven initialization, adapter communication, and a clear interface structure, it provides a reliable foundation for processing Unicode text in industrial applications. The separation of service logic and resource interface simplifies the maintainability and reusability of the block.
# Q_NumericValueAux_AUDI
![Q_NumericValueAux_AUDI](./Q_NumericValueAux_AUDI.svg)

* * * * * * * * * *
## Introduction
This function block implements the **Change Numeric Value** command according to ISO 11783-6 (Part 6, F.22). It is used to change the numeric value of an object and is only suitable for objects that have a numeric value attribute.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment | Carried Variable |

|----------|-------|-------------------------------------|----------------------|

| `INIT` | EInit | Service Initialization | `u16ObjId` |

### **Event Outputs**

| Event | Type | Comment | Carried Variable |

|----------|--------|-----------------------------------|-----------------------|

| `INITO` | EInit | Initialization Acknowledgement | – |

| `CNF` | Event | Acknowledgement of Requested Service | `STATUS`, `s16result` |

### **Data Inputs**

| Variable | Type | Comment | Initial Value |

|-------------|-------|------------|-------------|

| `u16ObjId` | UINT | Object ID | `ID_NULL` |

### **Data Outputs**

| Variable | Type | Comment |

|-------------|--------|----------------------------|

| `STATUS` | STRING | Service Status |

| `s16result` | INT | Return Value (see description) |

### **Adapters**

| Adapter | Direction | Type | Comment |

|-----------------|----------|--------------------------------------|-----------------------------|

| `u32OldValue` | Plug | `adapter::types::unidirectional::AUDI` | Old Value of ID |

| `u32NewValue` | Socket | `adapter::types::unidirectional::AUDI` | New ID Value |

## Functionality

The function block (FB) expects a valid object ID (`u16ObjId`) via the INIT input. After successful initialization, a new value can be passed via the socket adapter (`u32NewValue`). The socket adapter event (E1) triggers internal processing, in which the old value is returned via the plug adapter (`u32OldValue`). The result is signaled via the CNF output with status and return code (`s16result`).

`` Possible return codes are:

- `VT_E_NO_ERR (0)` – Success
- `VT_E_OVERFLOW (-6)` – Buffer overflow
- `VT_E_NOACT (-8)` – Command not possible in the current state
- `VT_E_NO_INSTANCE (-21)` – No VT client available
- `VT_E_ISO_INSTANCE_INVALID (-129)` – Connection instance invalid
- `VT_E_HANDLE_INVALID (-128)` – Invalid handle
- `VT_E_NOT_ALIVE (-130)` – VT unreachable

## Technical Features
- Use of unidirectional adapters for transmitting old and new values, enabling flexible, loose coupling in the application.
- Initialization with an object ID (`u16ObjId`) is mandatory.
- Returns ISO-11783-specific error codes, allowing for detailed error diagnosis.
- The function block internally contains a sub-FB (`Q_NumericValueAux`) that encapsulates the actual logic.

## State Overview

The FB does not have any explicit state machines in its XML description. Its operation is event-driven:

1. **INIT** – Sets the object ID and initializes the internal logic.

2. **Waiting for Value** – After INIT, the function waits for an event from the socket adapter (`u32NewValue.E1`).

3. **Processing** – Upon arrival, the value is processed, the previous value is returned via the plug adapter, and the result is reported via `CNF`.

## Application Scenarios
- Changing numerical attributes of objects in a Virtual Terminal (VT) according to the ISOBUS standard.
- Controlling agricultural machinery – e.g., setting target values for speeds, pressures, or positions within an ISOBUS network.

## Comparison with Similar Modules

The basic module `Q_NumericValueAux` (without the suffix `_AUDI`) offers the same core functionality, but without the two unidirectional adapters. The `_AUDI` variant allows for separate and reusable connections of legacy and new values, which facilitates the development of modular and testable applications.

## Conclusion

The `Q_NumericValueAux_AUDI` is a specialized function block for ISO 11783 communication. It encapsulates the "Change Numeric Value" command and provides a clean, decoupled interface for value transfer via adapters. With its detailed error feedback, it is particularly suitable for safety-critical applications in agricultural engineering.

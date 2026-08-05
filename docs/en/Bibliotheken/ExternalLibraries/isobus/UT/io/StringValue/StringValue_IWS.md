# StringValue_IWS

![StringValue_IWS](./StringValue_IWS.svg)

* * * * * * * * * *

## Introduction

The function block **StringValue_IWS** is a service interface function block (SIFB) responsible for receiving wide strings (*Wide String*, `WSTRING`) as input data from a resource-side source (e.g., hardware interface, bus system). It provides a standardized interface for managing initialization, cyclic/demand-driven data retrieval, and asynchronous indications. This function block is typically found in ISOBUS-based control environments or other fieldbus systems that process Unicode-encoded text data.

## Interface Structure

### **Event Inputs**

| Event | Comment | Accompanying Data |

|----------|-----------|-------------------|

| `INIT` | Service Initialization | `QI`, `PARAMS`, `u16ObjId` |

| `REQ` | Service Request | `QI` |

### **Event Outputs**

| Event | Comment | Accompanying Data |

|----------|-----------|-------------------|

| `INITO` | Initialization Confirmation | `QO`, `STATUS` |

| `CNF` | Confirmation of requested action | `QO`, `STATUS`, `IN` |

| `IND` | Asynchronous indication from the resource | `QO`, `STATUS`, `IN` |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|-----------|----------|-------------|------------|

| `QI` | `BOOL` | – | Event input qualifier |

| `PARAMS` | `STRING` | – | Service parameter (e.g., port/device configuration) |

| `u16ObjId`| `UINT` | `ID_NULL` | Object ID for identifying the data source |

### **Data Outputs**

| Name | Type | Comment |

|----------|-----------|-----------|

| `QO` | `BOOL` | Event Output Qualifier |

| `STATUS` | `STRING` | Status or Error Message |

| `IN` | `WSTRING` | Received Input Data (Wide String) |

### **Adapter**

None.


## Functionality

The `StringValue_IWS` follows the typical behavior of a service interface function block:

1. **Initialization (`INIT` → `INITO`)**

The service is started by triggering the `INIT` event. The qualifier `QI` determines whether the initialization is active (`TRUE`) or disabling (`FALSE`). Necessary configuration parameters (e.g., bus address, protocol options) are passed using `PARAMS`. The object ID `u16ObjId` specifies which data source (e.g., a particular ISOBUS object) is to be addressed. After successful initialization, `INITO` is output; `QO` and `STATUS` indicate the initial state.

2. **Request (`REQ` → `CNF`)**

The `REQ` event triggers an explicit data query. The function block retrieves a new value from the connected device (e.g., via a driver). The response is provided via the output `IN` (as `WSTRING`) and the status `STATUS`. Simultaneously, the `CNF` event is sent.

3. **Asynchronous Indication (`IND`)**

If the resource provides new data without being prompted (e.g., when an input is changed), the `IND` event is triggered. `IN` then contains the current data, and `STATUS` the corresponding status. This output can be used in parallel with the `CNF` event.


The event outputs `QO` always return the current qualifier value (usually `QI` upon successful operation, otherwise `FALSE`). The status `STATUS` contains human-readable error or success messages.

## Technical Features

- **Wide Strings (`WSTRING`)**

This function block uses `WSTRING` (UTF-16 encoded) to correctly transmit international character sets, special characters, and emojis. This is particularly important in ISOBUS agricultural technology, for example, when operator terminals display Unicode text.


- **Object ID `u16ObjId`**

The initial value `ID_NULL` is inherited from the imported constant `isobus::UT::Q::const::IDs::ID_NULL`. A valid object ID must be set before the `INIT` action to address the correct data source.

- **Service Interface Character**

The function block is implemented as a SIFB and expects a resource-side implementation (driver). The actual communication with the hardware or bus system takes place outside the function block and is abstracted via the event/data interfaces.

- **Use of `eclipse4diac::core::TypeHash`**

This attribute serves for runtime identification of the type and is used for dynamic function block instances.


## State Overview

An explicit state engine is not defined in the XML; however, the following implicit process emerges from the SIFB semantics:

1. **IDLE** – Waiting for `INIT` or the first `REQ`.

2. **INIT** – Initialization phase; after successful execution, transition to **READY**.

3. **READY** – Ready for `REQ` or `IND`. Briefly enters **BUSY** upon `REQ`, then returns to **READY**.

4. **INDICATION** – Asynchronous data indexing; returns to **READY** after processing.

5. **ERROR** – In case of errors (e.g., communication interruption), `STATUS` is set and the block remains in place until `INIT` is sent again (with `QI=FALSE` as a possible reset).

## Application Scenarios

- **ISOBUS Terminal (UT) – Unicode Text Input**

Receiving user input such as machine names, addresses, or diagnostic texts from an operator terminal via ISOBUS.

- **Universal Interface for Character Input**

Connecting external sensors or input devices that deliver character strings in UTF-16 format (e.g., barcode scanners, RFID readers with text output).


- **Diagnostics and Logging Interface**

Captures status messages, warnings, or error texts from a control unit for forwarding to an HMI or cloud connection.

## Comparison with similar function blocks

| Function block | Type | Difference |

|----------------|-------|-------------|

| `StringValue_IWS` (present) | `WSTRING` | Receives UTF-16 encoded strings. |

| `StringValue_IWS` (standard version) | `STRING` | Receives ASCII/UTF-8 strings, lower character coverage. |

| `AnalogInput_IWS` | `REAL` | Receives analog measured values, not strings. |

| `EventInput_IWS` | – | Event interface only, no data. |

The `StringValue_IWS`is specifically designed for processing Unicode text and is therefore suitable for international or character set-heavy applications.

## Conclusion

The `StringValue_IWS` is an essential component for integrating text input into IEC 61499-based control systems, especially in ISOBUS environments. Its support for `WSTRING`, the clean separation of initialization, request, and asynchronous indication, and the flexible object ID addressing make it a robust solution for receiving long strings from distributed resources.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
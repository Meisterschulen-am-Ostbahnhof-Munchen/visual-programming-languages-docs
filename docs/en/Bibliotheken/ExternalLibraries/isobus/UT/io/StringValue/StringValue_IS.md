# StringValue_IS

![StringValue_IS](./StringValue_IS.svg)

* * * * * * * * * *

## Introduction

The **StringValue_IS** function block is an input service interface function block (Input SIFB) for receiving string data from a resource. It serves as a standardized interface for integrating external string information into the 4diac environment. Typical applications include connecting to ISOBUS systems, where strings such as names, status messages, or identifiers are received.

## Interface Structure

### **Event Inputs**

| Event | Type | Description | Data Carried |

|---------|------|--------------|-------------------|

| `INIT` | EInit | Service Interface Component Initialization | `QI`, `PARAMS`, `u16ObjId` |

| `REQ` | Event | Request for data query or update | `QI` |

### **Event Outputs**

| Event | Type | Description | Data Carried |

|---------|------|-------------|-------------------|

| `INITO` | EInit | Confirmation of successful initialization | `QO`, `STATUS` |

| `CNF` | Event | Confirmation of executed request | `QO`, `STATUS`, `IN` |

| `IND` | Event | Asynchronous indication – new input data from the resource | `QO`, `STATUS`, `IN` |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|-------------|

| `QI` | BOOL | – | Event Qualifier: Controls the execution of the associated events |

| `PARAMS` | STRING | – | Service parameter (e.g., configuration of access to the resource) |

| `u16ObjId` | UINT | `ID_NULL` | Object ID that identifies the string to be read from the resource |

### **Data Outputs**

| Name | Type | Description |

|------|-----|-------------|

| `QO` | BOOL | Event Qualifier: Indicates whether the output provides valid data |

| `STATUS` | STRING | Service status message (e.g., error codes or success message) |

| `IN` | STRING | Received string from the resource |

### **Adapter**

This function block does not have any adapter interfaces.

## Functionality

The **StringValue_IS** function block operates according to the standard scheme of a service interface function block for data input:

1. **Initialization (`INIT`)**

The function block is configured by creating a `INIT` event. The parameters `QI` (qualifier), `PARAMS` (service parameter), and `u16ObjId` (object ID) are passed. After successful initialization, the function block confirms with the event `INITO` and returns the status via `QO` and `STATUS`.

2. **Request (`REQ`)**

A `REQ` event triggers an active data query from the resource. The qualifier `QI` is evaluated. The response is returned with the event `CNF`. The received string is then available at the output `IN`.

3. **Asynchronous Indication (`IND`)**

The resource can send new data at any time. The function block signals this via the event `IND`. Simultaneously, the current data is provided at output `IN`, and the status is provided via `QO` and `STATUS`.

The outputs `IN`, `QO`, and `STATUS` are updated with each of the events `CNF` and `IND` and can be used immediately by subsequent function blocks.

## Technical Features

- **Object ID:**

The input `u16ObjId` is predefined with the initial value `ID_NULL`. Before first use, a valid object ID must be set. The actual meaning of the ID depends on the underlying resource protocol (e.g., ISOBUS object number).

- **Service Parameter (`PARAMS`):**

This string input is used to pass configuration-specific parameters (e.g., bus address, communication path). The exact syntax depends on the implemented driver.

- **Typical Event Sequence:**

`INIT` → `INITO` → (possibly repeated `REQ` ↔ `CNF` or asynchronous `IND`).


- **Error Handling:**

Errors are signaled via the `STATUS` output and can be used for error diagnosis.

## State Overview

The function block goes through the following basic states (not explicitly modeled in the XML, but typical for SIFBs):

- **Not Initialized:** After the system starts. Only `INIT` is processed.

- **Initialized:** After successful `INITO`. The function block is ready for `REQ` and can receive asynchronous `IND`.

- **Request in Progress:** After a `REQ` until the arrival of `CNF`. No further requests are processed during this time.

- **Error State:** In case of communication errors. Can be reset by re-running `INIT`.

## Application Scenarios

- **ISOBUS Control Units:**

Receiving strings such as device names, variable names, or status messages from an ISOBUS server.

- **User Interfaces:**

Reading text data sent from an external HMI or operator panel.

- **Configuration Data:**

Retrieving string parameters from a central configuration service.

## Comparison with Similar Function Blocks

| Function Block | Data Type | Special Feature |

|----------|----------|--------------|

| `BOOL_IS` | BOOL | Simple Boolean inputs (e.g., switches) |

| `INT_IS` | INT | Integer inputs (e.g., counter readings) |

`REAL_IS` | REAL | Floating-point inputs (e.g., measured values) |

`StringValue_IS` | STRING | Strings – for names, descriptions, irregularly formatted data |

`StringValue_IS` expands the family of input SIFBs with the flexible data type `STRING`, which is characterized by variable length and content.

## Conclusion

The **StringValue_IS** is an essential component for integrating string-based data into 4diac. It offers a standardized interface to the resource, enables both active queries and asynchronous indications, and can be flexibly configured using the parameters `PARAMS` and `u16ObjId`. Its use simplifies integration with protocols such as ISOBUS and increases the reusability of application logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
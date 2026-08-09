# GetVtcStatus

![GetVtcStatus](./GetVtcStatus.svg)

* * * * * * * * * *
## Introduction

The function block **GetVtcStatus** is a Service Interface Block (SIFB) that encapsulates the function `IsoVtcGetStatusInfo()` from the ISOBUS driver. It enables the reading of various status information from a VT client and the connected Virtual Terminal (VT). The block was developed according to the ISO 11783-6 standard and is suitable for integration into ISOBUS applications.
## Interface Structure

### **Event Inputs**

| Event | Type | Description | Data Carried |
|----------|-----|---------------|-------------------|
| `INIT` | EInit | Initializes the function block. | `QI`, `u8Instance` |
| `REQ` | Event | Requests the reading of a status value. | `QI`, `u8Instance`, `eVTInfo` |

### **Event Outputs**

| Event | Type | Description | Data Carried |
|----------|-----|--------------|-------------------|
| `INITO` | EInit | Confirmation of initialization. | `QO`, `STATUS` |
| `CNF` | Event | Confirmation of the read request with result. | `QO`, `STATUS`, `wValue` |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|-----|--------------|--------------|
| `QI` | BOOL | – | Quality input: TRUE activates the service. |
| `u8Instance` | USINT | – | VT client instance identifier (0–255). |
| `eVTInfo` | UINT | 0 | Type of status information to query (values from the enumeration `ISOVT_STATUS_e`). |

### **Data Outputs**

| Name | Type | Description |
|------|-----|---------------|
| `QO` | BOOL | Quality output: TRUE upon successful execution. |
| `STATUS` | STRING | Service status – contains a textual response. |
| `wValue` | UINT | The value returned by `IsoVtcGetStatusInfo()` (dependent on `eVTInfo`). |

### **Adapters**

No adapters available.

## Functionality

1. **Initialization**

The module is activated by the event `INIT`. The parameter `QI` must be set to TRUE for the service to start. The VT client instance to be used is specified via `u8Instance`. After successful initialization, the event `INITO` is sent with the output data `QO` and `STATUS`.

2. **Reading Status Information**

The event `REQ` initiates a specific query. The desired status value must be selected from the enumeration `ISOVT_STATUS_e` using `eVTInfo` (see the list in the technical specifications). Internally, the function block calls the function `IsoVtcGetStatusInfo()` and sends the event `CNF` upon completion. The outputs contain:

- `QO` = TRUE if the read operation was successful,
- `STATUS` = description of the result,
- `wValue` = the retrieved numerical value.

If `QI` is FALSE during the REQ call, the service is not executed and a corresponding error status is returned.

## Technical Features

- The function block is implemented as a **Service Interface Block** (SIFB) and accesses the system-level ISOBUS driver library.
- The possible values for `eVTInfo` (ISOVT_STATUS_e) are:

| Value | Label | Description |
|------|-------------|--------------|
| 0 | VT_SOURCE_ADDRESS | Source address of the VT |
| 2 | VT_HND | CF handle of the VT |
| 3 | CF_SOURCE_ADDRESS | Source address of the VT client |
| 4 | CF_HND | CF handle of the VT client |
6 | ID_VISIBLE_DATA_MASK | Data mask open on the VT |
7 | ID_VISIBLE_SOFTKEY_MASK | Softkey mask open on the VT |
8 | VT_BUSY_CODE | Busy code of the VT status message |
9 | AUXUNITS_TYPE1_ONBUS | TRUE if a Type 1 auxiliary device is on the bus |
11 | VT_ALIVE | VT unreachable for more than 3 seconds |
12 | VT_DOWNLOAD_FINISHED | Full announcement completed |
13 | VT_POOL_ACTIVE_onVT | Pool (selected) active on the VT |
14 | VT_STATEOFANNOUNCING | Announcing status |
| 15 | WS_VERSION_NR | Working Set version number |
| 16 | VT_NUMBOFVERSIONSTRINGS | Number of VT version strings sent |
| 17 | VT_NAVSOFTKEYS | Navigation softkeys (version 4) |
| 18 | VT_SOFTKEYXDOT | Softkey identifier – pixel X |
| 19 | VT_SOFTKEYYDOT | Softkey identifier – pixel Y |
| 20 | VT_VIRTUALSOFTKEYS | Number of virtual softkeys |
| 21 | VT_PHYSICALSOFTKEYS | Number of physical softkeys |
| 25 | VT_BOOTTIME | VT boot time |
| 26 | VT_GRAPHICTYPE | VT hardware graphics type |
| 29 | VT_VERSIONNR | Version of Working Set VT |

- The function block supports both initialization and repeated calls to read operations, allowing different status values to be queried within a loop.

## State Overview

The function block implements simple state-driven logic:

1. **Start State** – The function block waits for the event `INIT`.
2. **Initialization** – Upon receiving `INIT` (with a valid QI), the service is initialized. If successful, `INITO` is sent with QO=TRUE. If an error occurs, QO=FALSE and a corresponding STATUS are sent.
3. **Ready** – After successful initialization, any number of `REQ` events can be processed. Each `REQ` call triggers a call to `IsoVtcGetStatusInfo()` and the subsequent sending of `CNF`.
4. **Error Handling** – If an internal error occurs during a REQ, `CNF` is output with QO=FALSE and an error description in `STATUS`.

## Application Scenarios

- **Diagnostics and Monitoring** of an ISOBUS system: Reading the current VT address, graphics type, or boot time.
- **Detection of VT Availability** by querying `VT_ALIVE` and `VT_DOWNLOAD_FINISHED`.
- **Control of the softkey configuration** by querying the number of physical and virtual softkeys (`VT_PHYSICALSOFTKEYS`, `VT_VIRTUALSOFTKEYS`).
- **Comparison of the working set version** between different components using `VT_VERSIONNR` and `WS_VERSION_NR`.

## Comparison with similar modules

Similar modules such as `GetVtPool` or `GetVtObject` focus on reading pool or object data. The `GetVtcStatus` module, on the other hand, is specifically designed for accessing the general VT client status. It provides a direct interface to the system status properties of the ISOBUS specification and complements function blocks that access mask or softkey information.

## Conclusion

The function block `GetVtcStatus`It provides a compact and standards-compliant way to access the system-level status data of an ISOBUS virtual terminal. Its clear interface and diverse query options make it a valuable tool for implementing diagnostic, monitoring, and configuration functions in agricultural control systems.

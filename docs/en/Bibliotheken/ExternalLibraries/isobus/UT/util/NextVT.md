# NextVT
![NextVT](./NextVT.svg)

* * * * * * * * * *
## Introduction
The **NextVT** function block is a service interface block that enables switching to the next available Virtual Terminal (VT) in an ISOBUS network (ISO 11783-6). It encapsulates the functionality of `VTC_NextVTButtonPressed()` from the ISOBUS driver examples and allows seamless switching between multiple VT devices.
## Interface Structure
### **Event Inputs**

| Event | Data Type | With Variables | Description |
|----------|-----------|----------------|---------------|
| INIT | EInit | QI | Service Initialization. Triggered to configure the block. |
| REQ | Event | QI | Service request. Starts the process to switch to the next available VT. |

### **Event Outputs**

| Event | Data Type | With Variables | Description |
|----------|-----------|---------------|---------------|
| INITO | EInit | QO, STATUS | Initialization confirmation. Signals whether the initialization was successful. |
| CNF | Event | QO, STATUS, s16Result | Switchover confirmation. Outputs as soon as the switch to the next VT has been initiated. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|---------------|
| QI | BOOL | Quality input. TRUE activates the service. FALSE means no action is taken. |

### **Data Outputs**

| Variable | Type | Description |
|-----------|--------|---------------|
| QO | BOOL | Quality output. TRUE if the service was successful. |
| STATUS | STRING | Status message regarding the result of the last operation. |
| s16Result | INT | Return value: 0 = E_NO_ERR (successful), negative value = error code. |

### **Adapters**
No adapters available.

## Functionality

When a **REQ** event is received, the block performs the following steps:

1. **Determine list of all VTs** – All virtual terminals available on the ISOBUS network are identified using `IsoClientsReadListofExtHandles()`.

2. **Find currently connected VT** – The currently used VT is identified using `IsoVtcGetStatusInfo(VT_HND)`.

3. **Determine next VT** – The next entry after the current VT is selected from the list (cyclic sequence).

4. **Execute switchover** – The switchover to the next VT is initiated using `IsoVtcMultipleNextVT()`.

- **Error case:** If only one VT is present on the bus or the switchover fails, a negative return value (`s16Result`) and a corresponding status message are output.
- **Important Note:** The application must enter a safe state after calling this block, as the connection to the current VT is lost during the transition.

## Technical Features
- **Standard Compliance:** The block is based on ISO 11783-6 (ISOBUS) and implements the VT switching function according to the standard.
- **Service Interface Block:** Execution is asynchronous; the **CNF** event signals the completion of the switching process.
- **Initialization:** Before first use, the block must be initialized via the **INIT** event to allocate internal resources.

## State Overview
The block does not have explicit states in its XML definition. Its behavior is determined by event-driven processing:

- **Initialization Phase:** After **INIT** with `QI=TRUE`, initialization is performed and acknowledged by **INITO**.
- **Operational Phase:** After **REQ** with `QI=TRUE`, the switching process is initiated. Upon completion, the **CNF** event occurs.
- **Error Handling:** In case of errors, `QO=FALSE` and a corresponding error code are set in `s16Result`.

## Application Scenarios
- **ISOBUS Machine Operation:** Switching between multiple Virtual Terminals in agricultural vehicles, e.g., to switch between the display and the on-board computer.
- **Multi-Monitor Systems:** Switching the active display to a different VT device on the network.
- **Diagnostics and Testing:** Simulating the pressing of the "Next VT" button during the development of ISOBUS-compliant applications.

## Comparison with Similar Blocks
- **VTSelection** (hypothetical): A block that selects a specific VT object instead of simply jumping to the next one. NextVT is simpler and follows standard key logic.
- **VTConnect** (hypothetical): Establishes a direct connection to a named VT. NextVT, on the other hand, works automatically and does not require a target address.

## Conclusion
The **NextVT** function block is a specialized service interface block for ISOBUS applications that enables standards-compliant switching to the next available virtual terminal. Its simple interface (INIT, REQ) and clear error feedback make it ideally suited for integration into control software that requires flexible VT selection. However, the application must account for the brief connection interruption.

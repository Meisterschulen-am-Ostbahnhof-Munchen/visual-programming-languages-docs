# PoolReload
![PoolReload](./PoolReload.svg)

* * * * * * * * * *
## Introduction
The function block `PoolReload` is a service interface block according to ISO 11783-6 (ISOBUS). It enables the reloading or updating of the object pool of a Virtual Terminal (VT) during application runtime. This block is typically used, for example, to switch between different language variants or to dynamically load modified pool files without requiring a system restart.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |
|----------|-----|-----------|
| `INIT` | `EInit` | Service initialization (with parameters `QI` and `poolFileName`) |
| `REQ` | `Event` | Service request – performs pool reloading (with `QI`) |

### **Event Outputs**

| Event | Type | Comment |
|----------|-----|-----------|
| `INITO` | `EInit` | Initialization confirmation (outputs `QO` and `STATUS`) |
| `CNF` | `Event` | Confirmation – Pool reload complete (outputs `QO`, `STATUS`, and `s16Result`) |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `QI` | `BOOL` | Quality Input: `TRUE` activates the service |
| `poolFileName` | `STRING` | Path to the pool file (e.g., `pools/pool_de.iop`) |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `QO` | `BOOL` | Quality Output: `TRUE`, if the reload was successful |
| `STATUS` | `STRING` | Service status (e.g., error message or success message) |
| `s16Result` | `INT` | Return value: `0` = `E_NO_ERR` (success), negative values correspond to error codes |

### **Adapter**
No adapters available.

## Functionality
This function block encapsulates the ISOBUS function `VTC_PoolReload()`. The process is divided into the following steps:

1. **Initialization (`INIT`)**

- The pool data is loaded from the file specified in `poolFileName`.
- The pool is opened for the configured color depth.
- After successful loading, the function block returns a confirmation message via `INITO`.

2. **Service Execution (`REQ`)**

- This function block calls `IsoVtcPoolUpdate()` to update the pool on the VT.
- Optionally, ID range modes can be applied for pool manipulation.
- Upon completion of the operation, a `CNF` event is triggered, reporting success or failure (via `s16Result`).

## Technical Features
- **Standard Compliance**: This function block complies with the ISOBUS standard ISO 11783-6 (Agricultural vehicles – Virtual Terminal).
- **File Path**: By default, the pool file is expected to be located at `pools/pool_de.iop`. However, the path can be configured via the input `poolFileName`.
- **File Path**: By default, the pool file is expected to be located at `pools/pool_de.iop`. However, the path can be configured via the input `poolFileName`. - **Runtime Update**: Unlike a static pool import, this function block allows a dynamic update without requiring an application restart.
- **Error Handling**: The output `s16Result` returns the detailed ISOBUS error code (0 = success, negative values = error).

## State Overview
The function block can go through the following basic states:

| State | Description |
|---------|--------------|
| **IDLE** | Waiting for an INIT event. |
| **INIT_PENDING** | Initialization is being performed; upon completion, `INITO` is sent. |
| **READY** | Ready for `REQ` after successful initialization. |
| **REQ_PENDING** | Pool reloading is in progress; Upon completion, `CNF` is sent. |
**ERROR** | If initialization or reloading fails, an error status is reported, and the function block remains in the error state until it is re-initialized. |

## Application Scenarios
- **Language Switching**: During runtime, it is possible to switch between different language variants (e.g., German, English) by replacing the pool file.
- **Dynamic Pool Updates**: New screens or symbols can be loaded without restarting the entire VT – useful for firmware updates or field modifications.
- **Last-Minute Changes**: Modified pool files can be quickly loaded during commissioning.

## Comparison with Similar Function Blocks

| Function Block | Description |
|----------|--------------|
PoolLoader` | Loads the pool only at system startup; no reloading at runtime. |
PoolActivate` | Switches between already loaded pools, but requires prior loading. |
PoolReload` | Combines loading and updating in one step and enables dynamic reloading during runtime. |

## Conclusion
The `PoolReload` function block is a specialized service interface module for ISOBUS virtual terminals that enables flexible reloading and updating of object pools at runtime. It simplifies language switching, dynamic updates, and facilitates the maintenance of VT applications. Its clear event interface and detailed error feedback make it well-suited for use in agricultural control systems.

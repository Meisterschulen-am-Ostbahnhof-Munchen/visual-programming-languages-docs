# PoolDeleteVersion

![PoolDeleteVersion](./PoolDeleteVersion.svg)

* * * * * * * * * *

## Introduction

The service interface block `PoolDeleteVersion` deletes a stored object pool version from the non-volatile memory of a Virtual Terminal (VT). It encapsulates the function `VTC_PoolDeleteVersion()` from the ISOBUS driver. The block calls `IsoVtcCmd_DeleteVersion()` to remove the specified pool version.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| INIT | EInit | Service Initialization |

| REQ | Event | Service Request – Delete Pool Version |


### **Event Outputs**

| Name | Type | Comment |

|-------|------|-----------|

| INITO | EInit | Initialization Confirmation |

| CNF | Event | Confirmation – Deletion complete |

### **Data Inputs**

| Name | Type | Comment | Initial Value |

-----------------|--------|---------------------------------------------------|----------------------|

| QI | BOOL | Quality Input – TRUE activates the service | |

| versionString | STRING | Version label to be deleted (space for last saved version) | `'       '` |

### **Data Outputs**

| Name | Type | Comment |

|-----------|--------|-------------------------------------------------------|

| QO | BOOL | Quality output – TRUE on successful deletion |

| STATUS | STRING | Service status |

| s16Result | INT | Return value: 0 = E_NO_ERR (success), negative = error code |

### **Adapter**

None.

## Functionality

The block is initialized via the event input `INIT`, passing the version number to be deleted (`versionString`). After successful initialization, an event `REQ` triggers the deletion process. The block calls the system-level function ``IsoVtcCmd_DeleteVersion()``, which removes the specified pool version from the VT's flash memory. The result is signaled via the outputs ``QO``, ``STATUS``, and ``s16Result``, triggering a corresponding confirmation event (``CNF`` or ``INITO``).

## Technical Specifications

- ``versionString`` must be null-terminated or exactly 32 bytes long (ISO V11+).

- If a string consisting of spaces (``'       '``) is passed, the function deletes the last stored pool version.


``` - Maximum version entry length: 32 bytes.

- The block is designed as a Service Interface Block (SIB) for ISOBUS communication (ISO 11783-6).

## State Overview

The block does not have any explicitly defined states in the XML. Control is event-driven via `INIT` and `REQ`:

1. **Initialization** (INIT) → Acknowledge (INITO)

2. **Request** (REQ) → Acknowledge (CNF) with result

Failed initialization or deletion is signaled by `QO=FALSE` and the corresponding `STATUS` message.


## Application Scenarios

- Deleting old pool versions before uploading a new version

- Freeing up flash memory space on the VT

- Removing corrupted or no longer needed pool versions

- Resetting to the factory-stored version by deleting all user-defined versions

## Comparison with Similar Blocks

There is no direct comparison to other function blocks. This block is specifically for managing ISOBUS object pools in VT flash memory.

## Conclusion

`PoolDeleteVersion` provides a standardized and reliable way to delete stored object pool versions from the flash memory of a virtual terminal. Its simple event-driven interface makes it easy to integrate into automation and control applications. Adherence to ISO specifications (version string length, spaces for the last version) makes the block particularly robust for use in agricultural machinery according to ISO 11783.
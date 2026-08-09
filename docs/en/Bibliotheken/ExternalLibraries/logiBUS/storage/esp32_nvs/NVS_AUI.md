# NVS_AUI

![NVS_AUI](./NVS_AUI.svg)

* * * * * * * * * *
## Introduction

The function block **NVS_AUI** is used to load and store UINT data in non-volatile memory (NVS) using a key. It encapsulates access to the NVS and provides a standardized AUI adapter interface for outputting read values and receiving values to be stored. Typical applications include embedded systems that need to persistently store configuration or status data.
## Interface Structure

### **Event Inputs**

| Event | Comment | Accompanying Data |
|----------|-----------|-------------------|
| `INIT` | Service Initialization | `QI` (BOOL), `KEY` (STRING), `DEFAULT_VALUE` (UDINT) |

### **Event Outputs**

| Event | Comment | Carrying Data |
|----------|-----------|-------------------|
| `INITO` | Initialization Acknowledgement | `QO` (BOOL), `STATUS` (STRING) |

### **Data Inputs**

| Name | Type | Comment |
|-----------------|--------|-----------|
| `QI` | BOOL | Qualifier for the input event |
| `KEY` | STRING | Key name for NVS access |
| `DEFAULT_VALUE` | UDINT | Value to be read if no entry exists in the NVS |

### **Data Outputs**

| Name | Type | Comment |
|----------|--------|-----------|
| `QO` | BOOL | Qualifier for the output event |
| `STATUS` | STRING | Service status message |

### **Adapters**

| Adapter | Type / Direction | Comment |
|------------|----------------------------------------|-----------|
| `AUI_IN` | **Socket** (Input) – Type: `adapter::types::unidirectional::AUI` | Returns the value to be stored (SET) |
| `AUI_OUT` | **Plug** (Output) – Type: `adapter::types::unidirectional::AUI` | Returns the retrieved value (GETO) |

## Functionality

1. **Initialization**

A `INIT` event triggers the connection to the non-volatile memory. The key (`KEY`) and the default value (`DEFAULT_VALUE`) are passed. After successful initialization, `INITO` is acknowledged with the result (`QO` / `STATUS`).

2. **Reading Data**

After initialization, the stored value for the specified key is automatically read internally and provided as an event (E1) and data (D1) via the output adapter `AUI_OUT`. If no entry exists, `DEFAULT_VALUE` is output.

3. **Storing Data**

A new value can be received via the input adapter `AUI_IN`. An incoming event (E1) with the associated data (D1) is forwarded to the internal NVS function block, which persistently stores the value under the initialized key.

The entire data and event flow is implemented by the embedded function block `NVS` (from the library `logiBUS::storage::esp32_nvs`).

## Technical Features

- **AUI Adapter Interface**

The unidirectional adapters `AUI_IN` and `AUI_OUT` enable loose coupling between the NVS module and other components that use standardized AUI interfaces.

- **Automatic Read Operation After Initialization**

Immediately after initialization, the value is read and made available via `AUI_OUT` – without a separate "Get" event.

- **Error Handling**

Errors during initialization or memory accesses are signaled via `STATUS`.

## Status Overview

The FB is in **idle state** after startup.

- **Initialization** (upon arrival of `INIT`): Establishing the NVS connection, reading the existing value.
- **Ready** (after successful `INITO`): Waiting for incoming data via `AUI_IN` to save or for external requests via `AUI_OUT`.
- **Save operation** (upon event at `AUI_IN`): Value is persisted; then returns to the ready state.
- **Error state** (in case of unsuccessful initialization): `QO` = FALSE, `STATUS` contains error text.

## Application Scenarios

- **Configuration Memory** in IoT devices: Storing network settings, calibration data, or user settings.
- **Status Monitoring**: Saving the last operating state (e.g., counter readings) before a power failure.
- **Parameter Transfer** between different automation components that communicate via AUI adapters.

## Comparison with Similar Function Blocks

Compared to the direct **NVS** function block, `NVS_AUI` offers a higher level of abstraction through its adapter interface. While the basic function block requires separate events for reading (`GET`) and writing (`SET`), `NVS_AUI` simplifies data flow through unidirectional adapters and automatic read operation after INIT. Other memory modules (e.g., `F_MMAP`, `F_FILE`) typically use file-based or memory-mapping methods; `NVS_AUI` is specifically optimized for non-volatile memory with key-value pairs.

## Conclusion

NVS_AUI` is a practical functional block for persistent data storage in automation systems. The combination of NVS memory and an AUI adapter allows for easy integration into existing IEC 61499 applications, reduces wiring effort, and ensures a clear separation between memory logic and communication.

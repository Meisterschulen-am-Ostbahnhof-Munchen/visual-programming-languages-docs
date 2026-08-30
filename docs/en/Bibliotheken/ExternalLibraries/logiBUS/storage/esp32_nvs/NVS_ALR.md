# NVS_ALR

![NVS_ALR](./NVS_ALR.svg)

* * * * * * * * * *

## Introduction

The function block **NVS_ALR** is used to load and store values of type `LREAL` in non-volatile storage (NVS) using a key. It is specifically designed for connection via the unidirectional **ALR adapter**. The block combines an initialization phase, in which the memory contents are read, with a subsequent read and write operation via the adapter.

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Variables |
|----------|---------------|-----------------------|
| **INIT** | Initializes the function block and performs an initial read operation from the NVS. | QI, KEY, DEFAULT_VALUE |

### **Event Outputs**

| Event | Description | Included Variables |
|----------|---------------|-----------------------|
| **INITO** | Confirmation of initialization and feedback of the result. | QO, STATUS |

### **Data Inputs**

| Variable | Type | Description |
| ---------- | ------- | -------------- |
| QI | BOOL | Control for initialization (TRUE = active). |
| KEY | STRING | Key name for NVS access. |
| DEFAULT_VALUE | LREAL | Value to be read if no entry exists in the NVS under the specified key. |

### **Data Outputs**

| Variable | Type | Description |
| ---------- | ------- | -------------- |
| QO | BOOL | Initialization confirmation (TRUE = successful). |
| STATUS | STRING | Status message (e.g., error message for failed access). |

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| **ALR_IN** | Socket | `adapter::types::unidirectional::ALR` | Receives write commands (stores value). |
| **ALR_OUT** | Plug | `adapter::types::unidirectional::ALR` | Sends read values after a read operation. |

## Functionality

1. **Initialization**

After an event at the **INIT** input, the internal function block `NVS` is called with the specified key (`KEY`), the default value (`DEFAULT_VALUE`), and the activation (`QI`). The initialization process opens the NVS area and immediately reads the existing value. This value is output via the **ALR_OUT** adapter as an event with the corresponding data value (`D1`). Simultaneously, the **INITO** event output is triggered with the acknowledgments (`QO`, `STATUS`).

1. **Write via ALR_IN**

An event at the **ALR_IN.E1** input (connected to the socket) triggers a **SET** operation. The supplied data value (`ALR_IN.D1`) is written to the NVS under the previously stored key. After successful writing, the event is passed to **ALR_OUT.E1**, and the written value is output there.

1. **Read via ALR_IN?**

In this network, a **GET** command is automatically triggered after initialization. An explicit read call via the adapter is not included in the design; the function block always outputs the current value via **ALR_OUT** after each NVS operation (INIT, SET).

## Technical Features

- **Adapter Interface**

Communication with the outside world occurs exclusively via the unidirectional ALR adapter. This makes the module particularly suitable for modular architectures where data flows are handled via standardized interfaces.

- **Internal NVS Module**

The FB `NVS` (from the library `logiBUS::storage::esp32_nvs`) is used in the network. This encapsulates the actual read and write logic on the ESP32-NVS.

- **Automatic Read Operation**

After initialization, a GET request is executed immediately, so the user receives the current value (default value or stored value) right away.

- **Error Handling**

The outputs `QO` and `STATUS` allow for easy verification of initialization success. Errors are reported as a string.

## State Overview

The function block does not cycle through explicitly modeled states, but is event-driven. The following behavior occurs:

- **Idle State** – No INIT is performed. No actions are executed.
- **Initializing** – INIT is received; NVS operations are started; upon completion, INITO is triggered and a GET request is initiated.
- **Ready** – After successful initialization, the function block waits for events via **ALR_IN.E1** (write) or internal GET requests (only triggered automatically initially).
- **Write** – At ALR_IN.E1, the value is saved and the result is sent to ALR_OUT.

## Application Scenarios

- **ESP32 Configuration Parameters**

Storage of LREAL values such as calibration factors, thresholds, or PID parameters that should be retained after a restart. The ALR adapter enables easy integration with other function blocks that use the same adapter type.

- **Encapsulated Data Access**

If a function block needs to read and write LREAL values from the NVS, but directly using the NVS function block seems too complex, NVS_ALR offers an abstracted interface.

- **Modular Automation**

Use in Industry 4.0 applications where devices communicate via standardized adapter services (e.g., via an ALR configuration layer).

## Comparison with Similar Function Blocks

- **NVS (Direct)**

The `NVS` function block offers more flexibility (e.g., random access, different data types), but requires more complex wiring and explicit GET/SET calls. NVS_ALR reduces the complexity to an adapter interface.

- **BOOL_NVS, INT_NVS (Hypothetical)**

Analogous function blocks for other data types. NVS_ALR is specifically designed for LREAL and utilizes the ALR adapter, which is typically intended for LREAL data.

- **Retentive Variables**

In some systems, retentive variables can be used directly in the function block model. However, NVS_ALR is explicitly designed for use with an external flash memory (NVS) and is therefore more portable.

## Conclusion

The **NVS_ALR** function block offers a compact and user-friendly way to persistently store LREAL values in an NVS and exchange them via a unidirectional adapter. By combining initialization, automatic reading, and adapter-based writing, it is particularly well-suited for modular and reusable ESP32-based control applications. Its design adheres to the IEC 61499 standard and enables a clean separation of memory logic and application.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

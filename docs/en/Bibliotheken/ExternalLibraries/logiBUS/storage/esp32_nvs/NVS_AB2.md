# NVS_AB2
![NVS_AB2](./NVS_AB2.svg)

* * * * * * * * * *
## Introduction
The function block **NVS_AB2** enables the loading and saving of `REAL` data in non-volatile storage (NVS) using a string key. It encapsulates NVS access in a convenient, asynchronous interface and communicates with the environment via a bidirectional **AB2** adapter. This makes the block particularly suitable for scenarios where configuration values or status data need to be permanently stored on an ESP32.
## Interface Structure
### **Event Inputs**

| Event | Type | Description |

|----------|-----|--------------|

| `INIT` | EInit | Initializes the function block. The input data (`QI`, `KEY`, `DEFAULT_VALUE`) are transferred when this event occurs. |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|--------------|

| `INITO` | EInit | Confirmation of successful initialization and the first read operation. |

### **Data Inputs**

| Name | Type | Description |

|----------------|--------|--------------|

| `QI` | BOOL | Qualifier for the initialization event (e.g., enabling processing). |

KEY` | STRING | Name of the key under which the value is stored in the NVS. |

DEFAULT_VALUE` | REAL | Value returned if no value exists in the NVS for the specified key. |

### **Data Outputs**

| Name | Type | Description |

|----------|--------|--------------|

QO` | BOOL | Qualifier for the output event – signals success (`TRUE`) or failure (`FALSE`). |

| `STATUS` | STRING | Detailed status message (e.g., error text or confirmation). |

### **Adapter**

| Name | Type (AB2 adapter) | Description |

|-------|-------------------|--------------|

| `VAL` | `adapter::types::bidirectional::AB2` | Bidirectional interface for the data value. Reading and writing are performed via the adapter channels (events: `EI1`, `EO1`; data: `DI1`, `DO1`).

## Functionality
Upon arrival of the **INIT** event, the internal NVS module is initialized. Immediately after successful initialization, a **read operation** (`GET`) is automatically initiated, which reads the value corresponding to the key `KEY` from the NVS. If no value is found, `DEFAULT_VALUE` is used. The read value is output via the adapter (`VAL.DI1`), and the event `INITO` signals completion.

After initialization, the function block can process asynchronous read and write requests via the adapter:

- **Read**: An event received at the adapter port `VAL.EO1` triggers another read operation (`GET`) in the NVS. The read value is again made available via `VAL.DI1`, and the acknowledgment (`VAL.EI1`) is sent.
- **Write**: The value to be saved is made available via the adapter on `VAL.DO1`. An event at `VAL.EO1` triggers the **write operation** (`SET`) in the NVS. Acknowledgement is sent via `VAL.EI1` after successful saving.

The outputs `QO` and `STATUS` are set to the current status of the NVS module upon each of the output events (`INITO`, as well as the internal adapter acknowledgments).

## Technical Features
- **NVS Access on the ESP32**: The module utilizes the function block defined at `logiBUS::storage::esp32_nvs::NVS`, which encapsulates the ESP32's flash memory management.
- **Bidirectional Adapter Interface**: The AB2 adapter allows the function block to process both read and write requests from the environment without requiring separate trigger events on the function block itself.
- **Automatic First Read Access**: After initialization, the stored value is read immediately, so that the current data value is available via the adapter after `INITO`.
- **Error Handling**: The status (`STATUS`) and the qualifier (`QO`) indicate the success or failure of each NVS operation.

## State Overview
The function block does not have explicit state machines, as it uses the behavior of the internal NVS function block as a composite function block. The following phases can be distinguished:

1. **Initialization** – triggered by `INIT`

2. **Ready** – after successful initialization, the module waits for adapter events

3. **Read/Write Operation** – brief access to the NVS during the processing of an adapter event

## Application Scenarios
- **Configuration storage** for device parameters (e.g., setpoints, calibration data) on ESP32-based controllers.
- **Persistent state maintenance**, e.g., last operating mode or counter readings across a restart.
- **Data exchange via AB2 protocol** with other modules that support the AB2 adapter interface – easy integration into existing automation solutions.

## Comparison with Similar Function Blocks
Compared to simpler read/write function blocks (e.g., direct NVS FBs without an adapter), **NVS_AB2** offers:

- **Asynchronous, event-driven communication** via the AB2 adapter – decouples data access from the main control flow.
- **Automatic initialization and first read** reduces programming effort.
- **Uniform error signaling** via `QO` and `STATUS`.

In contrast, function blocks without an adapter require separate event inputs for reading and writing and do not offer a standardized bidirectional interface.

## Conclusion

**NVS_AB2** is a practical function block for reliable, asynchronous access to the non-volatile memory of an ESP32. By encapsulating the NVS logic in a composite module and providing an AB2 adapter interface, it can be flexibly integrated into automation projects requiring persistent data storage. The combination of automatic initialization, read/write support, and clear status feedback makes it an efficient solution for embedded controllers.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

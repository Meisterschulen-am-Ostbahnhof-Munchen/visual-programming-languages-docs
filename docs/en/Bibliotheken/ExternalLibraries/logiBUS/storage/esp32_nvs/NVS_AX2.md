# NVS_AX2

![NVS_AX2](./NVS_AX2.svg)

* * * * * * * * * *
## Introduction
The function block **NVS_AX2** is used to load and save REAL data to the non-volatile memory (NVS) of an ESP32 via an adapter. It encapsulates the initialization and access to a single NVS entry, which is identified by a key. The function block provides an initializing event interface and a bidirectional adapter interface through which the stored value can be accessed externally. The block is modeled according to IEC 61499 and optimized for use in distributed automation systems.

## Interface Structure
### **Event Inputs**

| Event | Type | Comment | Carried Variables |

|----------|--------|----------------------------------|---------------------------|

| `INIT` | EInit | Service Initialization | QI, KEY, DEFAULT_VALUE |

### **Event Outputs**

| Event | Type | Comment | Carried Variables |

|----------|--------|----------------------------------|---------------------------|

| `INITO` | EInit | Initialization Confirm | QO, STATUS |

### **Data Inputs**

| Name | Type | Comment |

|----------------|--------|---------------------------------------------------------|

| `QI` | BOOL | Event Input Qualifier (Initialization Enabled) |

| `KEY` | STRING | Key name for the NVS entry |

| `DEFAULT_VALUE`| BOOL | Default value if the key does not exist in the NVS (default: FALSE) |

### **Data Outputs**

| Name | Type | Comment |

|----------|--------|----------------------------------|

| `QO` | BOOL | Event Output Qualifier |

| `STATUS` | STRING | Service status |

### **Adapters**

| Adapter | Type | Comment |

|---------|-------------------------------------------|----------------|

| `VAL` | `adapter::types::bidirectional::AX2` (Socket) | Value (REAL) |

The **VAL** adapter establishes a bidirectional connection to an external component. The stored REAL value can be read and written via this adapter. The AX2 adapter type defines an event and data protocol for data transfer.

## Functionality

1. **Initialization**: An event at input `INIT` triggers the initialization of the internal NVS component. The values `QI`, `KEY`, and `DEFAULT_VALUE` are passed. After successful initialization, the event `INITO` is sent at the output. Simultaneously, a read operation (GET) for the specified key is automatically initiated.


``` 2. **Read Value**: The read value is output via the adapter `VAL` as `DI1` (data output of the adapter), and an event `EI1` is triggered on the adapter. The outputs `QO` and `STATUS` reflect the result of the read operation.

3. **Save Value**: An external function block can send an event `EO1` via the adapter `VAL` to write a new value (provided as `DO1`) to the NVS. The internal NVS function block then performs a SET operation and confirms it via `SETO`. The event `EI1` is then triggered on the adapter to signal completion to the sender.

4. **Status Signaling**: The outputs `QO` and `STATUS` are updated after each read or write operation and output with the event `INITO`.

## Technical Features
- **Persistence on ESP32**: The function block uses the ESP32 microcontroller's NVS (Non-Volatile Storage) to permanently store data. The data is retained even after a restart.

- **Adapter-Based Communication**: The interface to the user is via a bidirectional adapter (AX2), which enables flexible and standardized connectivity to other components. The data type is set to REAL.

- **Error Handling**: Error messages (e.g., NVS error, insufficient memory) can be queried via the output `STATUS`. The output `QO` indicates the success of the operation.

- **Standard Compliance**: The function block (FB) is implemented according to IEC 61499 and uses the block class `logiBUS::storage::esp32_nvs::NVS`.

## State Overview
The FB does not have an explicit state machine, but the following logical sequence occurs:

1. **Idle**: No `INIT` event is received.

2. **Initializing**: After `INIT` – the internal NVS block is started and a GET request is executed.

3. **Ready**: After `INITO` – the module waits for read/write requests via the adapter.

4. **Write Operation**: A `EO1` event on the adapter triggers a SET operation.

5. **Read**: A subsequent read operation can only be performed by another `INIT` event or internal logic (the module reads once at startup and subsequently only during write operations).

## Application Scenarios

- **Configuration Storage**: Saving user settings (e.g., setpoints, operating modes) to an ESP32 device.

- **Calibration Data**: Permanent storage of calibration values for sensors.

- **State Storage**: Saving the last operating state (e.g., counter readings, switch positions) in the event of a power failure.

- **Data Logging**: Targeted saving of individual measured values via the adapter.

## Comparison with Similar Function Blocks
Unlike simple memory function blocks (e.g., `CTUO` or generic `R_TRIG` blocks), `NVS_AX2` is specifically designed for persistent storage on ESP32 hardware. While other function blocks only process volatile data, this block ensures permanent data retention. Using an adapter offers more flexibility than a fixed input/output because the data type and communication direction are clearly defined. Compared to direct NVS API calls in IEC 61499, this function block simplifies integration through its fully declarative description.


``` ## Conclusion

The function block `NVS_AX2` is an efficient and standards-compliant solution for persistently storing a REAL value in the NVS of an ESP32. Its clear interface structure with event control and bidirectional adapter facilitates integration into complex automation projects. Thanks to integrated initialization and error logging, the block is robust and suitable for industrial applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de ](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

* [🌐 MCU vs. MPU Comparison Guide on ms-muc-docs.de ](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]
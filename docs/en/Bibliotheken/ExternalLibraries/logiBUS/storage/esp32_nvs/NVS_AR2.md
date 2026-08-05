# NVS_AR2
![NVS_AR2](./NVS_AR2.svg)
* * * * * * * * * *
## Introduction
The NVS_AR2 function block is used to store and load real values (floating-point numbers) into non-volatile storage (NVS) using a key. It encapsulates the logic of the underlying NVS block and provides a bidirectional AR2 adapter interface for asynchronous communication. This allows the block to be integrated into an event-driven environment where read and write operations are triggered asynchronously.
## Interface Structure
### **Event Inputs**
- **INIT**: Initializes the block. This event passes the parameters QI (Qualifier), KEY (Key), and DEFAULT_VALUE (Default Value). After successful initialization, the INITO output is triggered.

### **Event Outputs**
- **INITO**: Initialization confirmation. This event signals that the function block is ready. It is also triggered after a read or write operation via the adapter (since the events are chained).

### **Data Inputs**
- **QI** (BOOL): Input qualifier for controlling execution. Typically, this is set to TRUE to activate initialization.
- **KEY** (STRING): The key name under which the value is to be stored or read in the NVS.
- **DEFAULT_VALUE** (REAL): The value returned if no entry exists in the NVS under the specified key.

### **Data Outputs**
- **QO** (BOOL): Output qualifier. Displays the status of the executed operation.
- **STATUS** (STRING): Status message of the operation (e.g., success, error code).

### **Adapter**
- **VAL** (of type `adapter::types::bidirectional::AR2`): Bidirectional adapter for asynchronous reading and writing of values. The adapter has two events (EO1 – from the module to the adapter; EI1 – from the adapter to the module) and two data ports (DO1 – data from the module to the adapter; DI1 – data from the adapter to the module). External components can send read and write requests to the NVS_AR2 and receive results via this adapter.

## Functionality
The NVS_AR2 acts as an intermediary between the actual NVS memory module (`logiBUS::storage::esp32_nvs::NVS`) and a higher-level controller via the bidirectional adapter. Upon receipt of the INIT event, the parameters are forwarded to the internal NVS module. The NVS module performs initialization and acknowledges with INITO.

After initialization, a read operation (GET) is automatically triggered: The NVS block reads the value under the specified key. If no entry exists, DEFAULT_VALUE is used. The read result is sent to the connected component via the adapter output (VAL.DI1) and the event VAL.EI1.

A write operation occurs when the external component sends a write command via the adapter (VAL.EO1). The desired value is then passed to NVS_AR2 via VAL.DO1, which forwards it to the NVS block (SET). After a successful write, the NVS block acknowledges with SETO, which in turn triggers the event VAL.EI1 to send the confirmation back to the external component.

## Technical Features
- **Asynchronous Communication**: The block supports asynchronous read and write operations via the AR2 adapter, allowing it to be integrated into concurrent systems without blocking calls.
- **Default Value**: Specifying a DEFAULT_VALUE ensures that a defined value is returned even when a key is used for the first time.
- **Error Handling**: STATUS and QO indicate the success or failure of the operation.
- **Reusability**: The function block encapsulates the general NVS function block and adds a standardized adapter interface, facilitating reuse in various control logics.

## State Overview
The function block does not have an explicitly defined state machine in the XML, as it is controlled via the internal NVS function block and event chaining. The state is determined by the sequence of events:

1. Waiting for INIT → Initialization runs → INITO and GET are triggered.

2. After GET: Waiting for read result → Value sent to adapter.

3. Waiting for write request via adapter → SET executed → Confirmation returned.

4. After each step, the function block is ready for new requests.

```
## Application Scenarios

- **Persistent Configuration Memory**: Saving and retrieving settings (e.g., setpoints, parameters) in an embedded system with NVS (such as ESP32 NVS).
- **Data Logging**: Asynchronously storing measured values in NVS.
- **Load Initial Default Values**: Loading a saved value at system startup or using a default value if it has never been saved.

## Comparison with Similar Devices
- **NVS**: The basic NVS device without an adapter has direct event interfaces (INIT, REQ, etc.) and requires a direct connection. NVS_AR2 adds a bidirectional adapter interface, enabling a more flexible, protocol-independent connection.
- **Other Memory Devices (e.g., EEPROM, file system)**: These devices often have different data types and access methods. NVS_AR2 is specifically optimized for REAL values and NVS access.

## Conclusion
The NVS_AR2 function block offers a clean, adapter-based interface for asynchronously reading and writing real data to non-volatile memory. Thanks to the encapsulation of the NVS block and the integration of the AR2 adapter, it is ideally suited for modular, event-driven control systems that require persistent data management.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

# NVS_AIS

![NVS_AIS](./NVS_AIS.svg)

* * * * * * * * * *
## Introduction

The function block `NVS_AIS` is used to store and load strings (STRING) in the non-volatile storage (NVS) of an ESP32 microcontroller. The data is addressed via a key (KEY) and exchanged via AIS (Acyclic Information Service) adapters. The block encapsulates the NVS initialization as well as the basic read and write operations and provides a standardized interface for integration into industrial control applications.
## Interface Structure

### **Event Inputs**

| Event | Type | Description | Data Carried |
|----------|-------|----------------------------------------------------------|-------------------|
| INIT | EInit | **Service Initialization** – Starts the function block and communication with the NVS. | QI, KEY, DEFAULT_VALUE |

### **Event Outputs**

| Event | Type | Description | Carrying Data |
|----------|-------|---------------------------------------------------------|-------------------|
| INITO | EInit | **Initialization Confirm** – Confirms successful initialization or signals an error. | QO, STATUS |

### **Data Inputs**

| Name | Data Type | Description |
|---------------|----------|--------------------------------------------------------------------------------------------------|
| QI | BOOL | **Event Input Qualifier** – Controls the behavior during the INIT phase (e.g., activation). |
| KEY | STRING | **Key name** – The key under which the value is stored/retrieved in the NVS. |
| DEFAULT_VALUE | STRING | **Default value** – Value that is read if no entry exists in the NVS for the specified KEY. |

### **Data Outputs**

| Name | Data type | Description |
|--------|----------|------------------------------------------------------------------------------|
| QO | BOOL | **Event Output Qualifier** – Indicates the success of the last operation. |
| STATUS | STRING | **Service Status** – Feedback on the NVS driver status (e.g., error messages). |

### **Adapters**

| Adapter | Type | Description |
|----------|-----------------------------------------------|------------------------------------------------------------------------------------------------------|
| AIS_IN | `adapter::types::unidirectional::AIS` (Socket) | **Value to store (SET)** – Receives a STRING value to be stored via the AIS protocol. |
| AIS_OUT | `adapter::types::unidirectional::AIS` (Plug) | **Stored value output (GETO)** – Sends the read STRING value from the NVS via the AIS protocol. |

## Functionality

1. **Initialization**

An event at the `INIT` input starts the internal logic. The function block calls the embedded `NVS` function block, which prepares the non-volatile memory. The supplied data (`QI`, `KEY`, `DEFAULT_VALUE`) are forwarded to the internal function block.

2. **Read Operation**

After a successful INIT phase (event `INITO` of the internal NVS), the `GET` event input of the internal NVS is automatically activated. The read value (or the `DEFAULT_VALUE` entry if no entry exists) is output via the `AIS_OUT` adapter as the `E1` event and `D1` data.

3. **Write Operation**

A new value can be received via the `AIS_IN` adapter. The associated `SET` event (E1) is routed to the internal NVS module, which stores the received value (D1) under the previously set `KEY`. The acknowledgment (`SETO`) is then sent via the `AIS_OUT` adapter.

4. **Feedback**

After both reading and writing, the module outputs the status (`QO`, `STATUS`) as well as the `INITO` event. The status can be used for error diagnosis.

## Technical Features

- **NVS for ESP32** – The module is specifically designed for the ESP32's non-volatile memory and uses the corresponding driver API.
- **Adapter Interface** – Communication with the outside world is exclusively via AIS adapters (unidirectional). This decouples the module from specific bus or application protocols.
- **Automatic Read Operation After INIT** – After initialization, a read operation is started immediately, so the stored value is instantly available at the output.
- **Unified Status** – All relevant status information is reported back via the outputs `QO` and `STATUS`.

## State Overview

The function block `NVS_AIS` itself does not have an explicit state machine. Its behavior is entirely controlled by the embedded function block `NVS`, which cycles through the typical states of an NVS driver (e.g., initialization, ready, error). The events `INIT` and `INITO` represent the start-stop cycle. The adapter events `E1` initiate the read/write requests.

## Application Scenarios

- **Configuration Memory** – Persistent storage of device settings (e.g., network parameters, operating modes) as strings.
- **Data Exchange with Other Devices** – Using the AIS adapters for easy integration into an IEC 61499 application without having to program direct bus or memory accesses.
- **Recovery After Restart** – The combination of INIT, automatic reading, and default values ensures that a defined initialized state is reached.

## Comparison with Similar Devices

- **`NVS` (direct)**: The direct NVS device offers more detailed control options (dedicated events for GET/SET) but requires manual connection of the interfaces. `NVS_AIS` simplifies the application by embedding the read/write logic and using standardized adapters.
- **Additional memory modules (e.g., for SD cards)**: These usually operate with different protocols (SPI, I²C) and offer different memory schemes. `NVS_AIS` is optimized for the specific characteristics of the ESP32-NVS (key-value pairs, low latency).

## Conclusion

NVS_AIS`is a practical function block that encapsulates the saving and loading of strings in the ESP32's non-volatile memory and provides it via a clean adapter interface. With its automated initialization and integrated read and write operations, it is particularly well-suited for applications requiring simple, reliable persistence of configuration data. The adapter interface enables loose coupling with other components and increases reusability across various IEC 61499 projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)
- [🌐 MCU vs. MPU comparison guide on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]

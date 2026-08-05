# NVS_AUDI
![NVS_AUDI](./NVS_AUDI.svg)

* * * * * * * * * *
## Introduction
The **NVS_AUDI** function block enables the storage and loading of **UDINT** data in the **Non-Volatile Storage (NVS)** of an ESP32 microcontroller. The data is addressed using a unique **key (KEY)**. The block uses a **unidirectional AUDI adapter interface** to communicate with the NVS: The value to be stored is received via an input adapter (socket), and the read value is provided via an output adapter (plug).
## Interface Structure
### **Event Inputs**

| Name | Type | Data Carried | Comment |
|-------|-------|---------------------------|-------------------------------|
| INIT | EInit | QI, KEY, DEFAULT_VALUE | Initializes the service |

### **Event Outputs**

| Name | Type | Carried Data | Comment |
|-------|-------|-------------------|----------------------------------|
| INITO | EInit | QO, STATUS | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Comment |
|---------------|--------|---------------------------------------------------|
| QI | BOOL | Event Input Qualifier |
| KEY | STRING | Key Name for NVS Access |
| DEFAULT_VALUE | UDINT | Default value if no value exists in NVS |

### **Data Outputs**

| Name | Type | Comment |
|--------|--------|------------------------------|
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Service Status (Error/OK) |

### **Adapter**

| Name | Type | Comment |
|----------|--------------------------------------|------------------------------------|
| AUDI_IN | adapter::types::unidirectional::AUDI | Value to be stored (SET) |
| AUDI_OUT | adapter::types::unidirectional::AUDI | Stored/loaded value (GETO)|

## Functionality
Upon arrival of the **INIT** event, the internal NVS module is initialized (QI, KEY, and DEFAULT_VALUE are passed). After successful initialization, **INITO** fires, and simultaneously a **GET** request is sent to the NVS to load the stored value. The result of the GET operation is provided via **AUDI_OUT** (data on D1, event on E1).

If an event (E1) with a value (D1) is received via the **AUDI_IN** adapter, a **SET** request is sent to the NVS to store the value under the current KEY. After saving, **SETO** fires, and the result is also acknowledged via **AUDI_OUT**.

The status (QO, STATUS) is updated via the outputs after both loading and saving.

## Technical Features
- The function block uses the **unidirectional AUDI adapter**, which allows for simple, stream-based data transfer: A value is sent (SET), and a value is received (GETO).
- Internally, the function block `logiBUS::storage::esp32_nvs::NVS` is used, which executes the actual NVS operation on the ESP32.
- The default data type is **UDINT** (unsigned 32-bit).
- No additional states or timers are required; the function block operates purely event-driven.
- The **TypeHash** attribute is set to an empty string – it can be used for integrity checks.

## State Overview
Since no explicit state machine is defined in the XML, the process is derived from the events:

1. **Initialization Phase** – INIT received → NVS-INIT → NVS-GET triggered.

Afterwards: Ready (waiting for SET or another GET by re-INIT).

2. **Storage Phase** – Event via AUDI_IN (E1) → NVS-SET → Value is written.

3. **Read Operation** – Automatically after INIT or by re-INIT.

Output via AUDI_OUT occurs after each read or write operation.

## Application Scenarios
- Storing **configuration parameters** (e.g., limits, operating modes) in the NVS, which are retained even after a power failure.
- **Meter readings** or **calibration data** in ESP32-based industrial controllers.
- **Persistent states** of automation processes, uniquely identified by a key.
- Exchanging data between different FBs via the AUDI adapter without directly accessing the NVS.

## Comparison with Similar Function Blocks
- **NVS (without adapter)**: Provides direct access to the NVS via individual events and data ports, but requires more wiring.
- **NVS_AUDI** encapsulates the NVS operations behind a standardized adapter interface. This makes the module easier to replace and standardizes data transfer (e.g., with other memory modules that also use AUDI adapters).

Other memory modules (e.g., Retain, SD card) differ in their hardware interface and latency; NVS is specifically optimized for the ESP32.

## Conclusion
The NVS_AUDI function block provides an elegant solution for persistent storage of UDINT data on the ESP32. The integration of the AUDI adapter interface simplifies connectivity to other modules and results in clearer code structure. It is particularly suitable for applications requiring standardized data exchange between storage and processing components.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)
* [🌐 MCU vs. MPU comparison guide on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]

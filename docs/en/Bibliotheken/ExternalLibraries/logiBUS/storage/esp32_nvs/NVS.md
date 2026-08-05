# NVS

<img width="1739" height="315" alt="image" src="https://github.com/user-attachments/assets/58cbe71a-173a-41eb-848d-c641fafb502f" />

* * * * * * * * * *
## Introduction
The NVS (Non-Volatile Storage) function block enables persistent storage and loading of data on an ESP32 microcontroller. It utilizes the ESP32's non-volatile storage (NVS) to store values under a defined key and retrieve them as needed. This block is particularly suitable for applications where configuration data, calibration values, or status information must be retained across device restarts.

![NVS](NVS.svg)

## Interface Structure

### **Event Inputs**

* **INIT**: Initializes the function block. Triggers the read operation of the value specified by `KEY`. If no value is stored, `DEFAULT_VALUE` is returned.

* **SET**: Saves the value passed to `VALUE` under the previously configured key (`KEY`) in the NVS.

* **GET**: Reads the value stored under the configured key (`KEY`) in the NVS.

### **Event Outputs**

* **INITO**: Confirms the execution of the initialization (INIT) and returns the result.

* **SETO**: Confirms the execution of the write operation (SET) and returns the status.

* **GETO**: Confirms the execution of the read operation (GET) and returns the read value.

### **Data Inputs**

* **QI** (BOOL): Qualifies the INIT event input. The service is activated by `TRUE` and deactivated by `FALSE`.

* **KEY** (STRING): The unique key name under which the value is stored in the NVS or from which it is read. This value must be set during the INIT phase.

* **VALUE** (ANY_ELEMENTARY): The data record to be stored. It can be any elementary data type (e.g., BOOL, INT, REAL, STRING).

* **DEFAULT_VALUE** (ANY_ELEMENTARY): The default value returned during a read operation (INIT or GET) if no value is yet stored in the NVS under the specified key.


* ### **Data Outputs**

* **QO** (BOOL): Reflects the current operating state of the function block (`TRUE` = ready/successful, `FALSE` = not ready/error).

* **STATUS** (STRING): Contains a status message describing the success or type of error of the last operation (e.g., "OK", "Key not found", "Storage full").

* **VALUEO** (ANY_ELEMENTARY): The value actually read from the NVS or, if no value was present, the value from `DEFAULT_VALUE`.

### **Adapters**
This function block does not use adapters.

## Operation
The NVS block operates based on its state. During initialization (INIT with `QI=TRUE`), the specified `KEY` is set. The system then automatically attempts to read the corresponding value from the NVS (Network Value System). The result (stored value or `DEFAULT_VALUE`) is output along with the status via `INITO`.

Afterward, the block can perform two main operations:

1. **Write (SET)**: The value assigned to `VALUE` is stored in the NVS under the specified key (`KEY`). Confirmation is provided via `SETO`.


``` 2. **Read (GET)**: The value currently stored under the key is read from the NVS and made available via `VALUEO` at output `GETO`.

The data types of the inputs and outputs `VALUE`, `DEFAULT_VALUE`, and `VALUEO` must be consistent. The block is designed for repeated access to the same key.

## Technical Features
* **ESP32-Specific**: This block directly uses the NVS API of the ESP32-IDF and is therefore only compatible with ESP32-based target platforms.

* **Type Flexibility**: The use of the generic data type `ANY_ELEMENTARY` allows for the storage of various elementary data types. The specific type is set during initial use (INIT) and must be retained for all subsequent operations.

**Persistence**: Data in the NVS survives a microcontroller restart and is also retained after a power failure (depending on the NVS memory configuration).

## State Overview

1. **Not Initialized**: The block is inactive after startup. The key (`KEY`) is not set.

2. **Initialized/Ready**: After a successful `INIT` event, the block is ready for operation. The key is configured, and an initial value (from NVS or default) has been loaded. The block is waiting for `SET` or `GET` events.

3. **Write Operation**: During the processing of a `SET` event.

4. **Read Operation**: During the processing of a `GET` event or the implicit read operation during `INIT`.

## Application Scenarios
* **Device Configuration**: Saving network credentials (SSID, password), IP addresses, or other parameters to be retained after a reset.

* **Operational Data Acquisition**: Persistently counting operating hours, cycle counts, or units produced.

* **Calibration Data**: Storing sensor- or actuator-specific calibration values.

* **Last Known State**: Saving the system state before an unexpected shutdown to restore it upon the next startup.


## ⚖️ Comparison with similar building blocks

* **E_R_TRIG / F_TRIG**: These are purely event triggers and do not offer persistent data storage.

* **BLINK / DELAY**: Time-based blocks without memory functionality.

* **E_EEPROM**: A generic EEPROM block. The NVS block is specific to the ESP32 platform and utilizes its optimized, wear-leveling file system (NVS), while a generic E_EEPROM block would be hardware-dependent and often operate on simpler memory.


## 🛠️ Related Exercises

* [Exercise_012](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012.md)]

* [Exercise_012a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012a_sub.md)]

* [Exercise_020c2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2_sub.md)]

## Conclusion
The NVS function block provides a simple and robust interface to the ESP32's non-volatile memory. Its clear separation of read and write operations, along with its type-flexible data processing, makes it ideal for a wide range of applications requiring persistent data on embedded ESP32 systems. Its integration into the 4diac IDE enables platform-specific functionality within the portable IEC 61499 model.



``` ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

* [🌐 MCU vs. MPU Comparison Guide on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]
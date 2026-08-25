# INI

## 🎧 Podcast

* [The E_CTU in IEC 61499: Event-driven counting and why the minimalist approach is convincing in mechanical engineering](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_CTU-in-der-IEC-61499-Ereignisgesteuertes-Zhlen-und-warum-der-Minimalist-im-Maschinenbau-berzeugt-e3a9qnq)
* [From "Mass Errors" to Masterpiece: Streamlining Industrial Software by Eliminating Mapping](https://podcasters.spotify.com/pod/show/logibus/episodes/From-Mass-Errors-to-Masterpiece-Streamlining-Industrial-Software-by-Eliminating-Mapping-e3759t4)
* [The tracked monster awakens: Lanz Bulldog Caterpillar – The fascinating revival of the 10-liter hot-bulb workhorse after 25 years of inactivity](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Das-Kettenmonster-erwacht-Lanz-Bulldog-Raupe--Die-faszinierende-Wiederbelebung-des-10-Liter-Glhkopf-Arbeitstiers-nach-25-Jahren-Stillstand-e39arpd)
* [Masters of change: How the curriculum for agricultural and construction machinery mechatronics technicians redefines lifelong learning](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Meister-des-Wandels-Wie-der-Lehrplan-fr-Land--und-Baumaschinenmechatroniker-lebenslanges-Lernen-neu-definiert-e38di5u)
* [Miniware TS101: The mobile soldering all-rounder – Strengths, weaknesses, and the USB-C Revolution](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Miniware-TS101-Das-mobile-Lt-Multitalent--Strken--Schwchen-und-die-USB-C-Revolution-e368lka)

## Introduction

The INI function block enables the loading and saving of data to a `settings.ini` file. It provides a simple interface for persistently managing values using a section name (SECTION) and a key (KEY). The block is particularly useful for configuration management in 4diac FORTE applications, for example, for setting and retrieving parameters such as IP addresses, thresholds, or operating modes.

## Interface Structure

### **Event Inputs**

* **INIT**: Service initialization. Used during startup or reconfiguration. Triggers the initialization of the block and, optionally, the first read/write of a value.
* **SET**: Sets the value for the configured key in the INI file.
* **GET**: Reads the value for the configured key from the INI file.

### **Event Outputs**

* **INITO**: Initialization confirmation. Triggered after processing the INIT event.
* **SETO**: Write confirmation. Triggered after processing the SET event.
* **GETO**: Read confirmation. Triggered after processing the GET event.

### **Data Inputs**

* **QI (BOOL)**: Event input qualifier. Controls whether the operation is enabled (`TRUE`) or disabled (`FALSE`) upon INIT.
* **SECTION (STRING)**: The name of the section within the `settings.ini` file.
* **KEY (STRING)**: The name of the key within the specified section.
* **VALUE (ANY_ELEMENTARY)**: The value to be written. This data type can be any elementary type (e.g., BOOL, INT, REAL, STRING).
* **DEFAULT_VALUE (ANY_ELEMENTARY)**: The default value returned if the requested key does not exist in the INI file.

### **Data Outputs**

* **QO (BOOL)**: Event output qualifier. Returns the status of the operation (`TRUE` for success, `FALSE` for error or deactivation).
* **STATUS (STRING)**: Detailed status of the executed operation (e.g., "OK", "ERROR").
* **VALUEO (ANY_ELEMENTARY)**: The value read or written. For GET requests, this is either the value read from the file or the DEFAULT_VALUE.

### **Adapters**

This function block does not use adapters.

## Functionality

The INI block acts as an interface between the IEC 61499 application and a persistent `settings.ini` file on the file system. Upon a `INIT` event with `QI=TRUE`, the block is configured for the specified `SECTION` and `KEY`. Optionally, a value (`VALUE`) can be written immediately, or a default (`DEFAULT_VALUE`) can be set.

A `SET` event writes the current value of the `VALUE` input under the configured key to the file. A `GET` event reads the value from the file. If the key does not exist, `DEFAULT_VALUE` is returned instead. Each operation (`INIT`, `SET`, `GET`) is acknowledged by a corresponding output event (`INITO`, `SETO`, `GETO`), with `QO`, `STATUS`, and `VALUEO` indicating the result status.

...
## Technical Features

* **Type Flexibility**: The data inputs/outputs `VALUE`, `DEFAULT_VALUE`, and `VALUEO` use the generic data type `ANY_ELEMENTARY`. This allows the storage of various elementary data types (e.g., numbers, Boolean values, strings) using the same function block.
* **Persistence**: The data is stored in text-based INI files (`settings.ini` for writable values, `settingsReadOnly.ini` for read-only factory settings).
* **Write Protection & Factory Defaults**: Keys in `settingsReadOnly.ini` override values in `settings.ini` and reject write attempts (`SET`) (`STATUS = "Key is read-only"`). For details, see [Read-Only Settings (settingsReadOnly.ini) ](./settingsReadOnly.md).
* **Error Handling**: The output of `STATUS` provides textual feedback on the success or failure of the operation, facilitating debugging.
* **Package**: The block is included in the package `eclipse4diac::storage`.

## State Overview

The block does not have an explicit, complex state machine in the user-accessible sense. Its behavior is event-driven: After initialization (`INIT`), it waits for requests (`SET` or `GET`), processes them, and then returns to a waiting state. The internal state (configured section/key) is retained after `INIT`.

## Application Scenarios

* **Configuration Management**: Loading device IP addresses, communication ports, or network settings when an application starts.
* **Parameterization**: Saving plant- or product-specific parameters (e.g., setpoints, times) that should be retained between restarts.
* **Operational Data Acquisition**: Persistently saving simple operating states or counter readings.
* **User Settings**: Managing language settings or other user preferences.
*
## ⚖️ Comparison with similar building blocks

* **`E_SR` (SR flip-flop) / `E_RS` (RS flip-flop)**: These blocks store a binary state (`BOOL`) in memory only during runtime. The INI block stores arbitrary data types permanently in non-volatile memory.
* **`E_DEMUX` / `E_MUX`**: These are used for event and data distribution, not persistent storage.
* **`FB_RETAIN` (from `eclipse4diac::core`)**: Stores data persistently, but typically uses device-specific, non-directly accessible retain memory. The INI block uses a standardized, readable text file.
* **Database or File I/O Blocks**: More general blocks for file access offer greater flexibility but are also more complex to use. The INI block is a specialized, simple solution for the common use case of key-value storage.

## Conclusion

The INI function block is a practical and straightforward tool for persistently storing configuration and parameter data in 4diac FORTE applications. Its strengths lie in its ease of use via sections and keys, the flexibility provided by the `ANY_ELEMENTARY` type, and the human-readability of the stored INI file. It is an excellent choice for applications that require a simple, persistent key-value database.

# Conclusion

The INI function block is a practical and straightforward tool for persistently storing configuration and parameter data in 4diac FORTE applications. ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

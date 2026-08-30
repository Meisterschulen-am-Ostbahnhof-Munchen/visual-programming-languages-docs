# INI_AR

![INI_AR](./INI_AR.svg)

* * * * * * * * * *
## Introduction

The INI_AR function block is used to load and save real data from a settings.ini file. It accesses the configuration file via a section and key name and provides the read or saved values via a unidirectional adapter. This allows for flexible integration into modular storage and control architectures.
## Interface Structure

### **Event Inputs**

- `INIT` (EInit): Service initialization. Triggers the loading of the current value and processes the associated data inputs.

### **Event Outputs**

- `INITO` (EInit): Initialization confirmation. Sent after a successful read or write operation.

### **Data Inputs**

- `QI` (BOOL): Qualifier for the event input.
- `SECTION` (STRING): Name of the section in the INI file.
- `KEY` (STRING): Name of the key within the section.
- `DEFAULT_VALUE` (REAL): Value to be used if no entry is found in the settings.ini file.

### **Data Outputs**

- `QO` (BOOL): Qualifier for the event output.
- `STATUS` (STRING): Status message of the service (e.g., success, error).

### **Adapter**

- **AR_OUT** (Plug, type `adapter::types::unidirectional::AR`): Adapter output through which the read value (GETO) is sent to other function blocks.
- **AR_IN** (Socket, type `adapter::types::unidirectional::AR`): Adapter input through which a value to be stored (SET) can be received.

## Functionality

After an INIT pulse, the internal function block `INI` (of type `eclipse4diac::storage::INI`) is triggered. This reads the current value from the specified section and the key from the settings.ini file. If no entry exists, `DEFAULT_VALUE` is used. After the read operation is complete, the GET event is triggered, and the read value is passed on via the adapter output `AR_OUT` (event GETO, data VALUEO).

Simultaneously, a new value (event E1, data D1) can be received via the adapter input `AR_IN`. This triggers the SET event in the INI block, which writes the value to the INI file. After writing, an acknowledgment is sent via `SETO`, which is also forwarded to the adapter output. The GETO and SET events are combined into the same output event `AR_OUT.E1`. The qualified outputs `QO` and `STATUS` are taken directly from the internal INI block.

## Technical Features

- The function block uses the internal INI function block from the library `eclipse4diac::storage`.
- The adapters `AR_IN` and `AR_OUT` must be of type `adapter::types::unidirectional::AR`.
- The function block is licensed under the Eclipse Public License 2.0 (EPL-2.0).
- Author: Franz Höpfinger, Version 1.0, Date: April 24, 2026.

## State Overview

The function block does not have an explicit state machine. The logic is controlled entirely via the event chaining of the internal INI function block:

- The value is read (GET) after `INIT`.
- Each `SET` pulse via `AR_IN` writes a new value to the INI file.

## Application Scenarios

- Persistent storage of configuration parameters (REAL) in an INI file for automation projects.
- Exchange of runtime parameters between different function blocks via the adapter interface.
- Initializing plant parameters from a central configuration file.

## Comparison with Similar Blocks

- **Standard INI Block** (`INI`): Provides direct read/write access to INI files via data inputs and outputs without an adapter.
- **INI_AR** extends this with the adapter interface, allowing values to be passed modularly to other blocks via events and data without having to encapsulate all the logic in a single block.
- Analogous building blocks exist for other data formats (JSON, XML), but these use different libraries.

## Conclusion

The INI_AR function block encapsulates access to an INI file for real values and simultaneously provides a standardized adapter interface for integration into distributed control networks. It simplifies saving and loading configuration data and allows for a clear separation between memory logic and data flows.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

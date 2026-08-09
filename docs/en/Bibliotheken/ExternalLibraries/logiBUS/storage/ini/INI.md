# INI

![INI](./INI.svg)

* * * * * * * * * *
## Introduction

The **INI** function block is used for the secure reading and writing of configuration data in a `settings.ini` file. It allows access to values via a section and key name and provides both initialization and read/write operations as separate events. Its use of generic data types (`ANY`) makes it flexible.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|--------|---------|----------------------------------------------|
| INIT | EInit | Initializes the function block and opens the INI file |
| SET | Event | Writes the value of `VALUE` for the current key |
GET | Event | Reads the value of the current key |

### **Event Outputs**

| Name | Type | Comment |
|--------|---------|----------------------------------------------|
| INITO | EInit | Initialization Confirmation |
| SETO | Event | Write Confirmation |
| GETO | Event | Read Confirmation |

### **Data Inputs**

| Name | Type | Comment |
|---------------|--------|------------------------------------------------|
| QI | BOOL | Event Input Qualifier (controls execution) |
| SECTION | STRING | Section Name in the INI File |
| KEY | STRING | Key name within the section |
| VALUE | ANY | Value to be set (for SET) |
| DEFAULT_VALUE | ANY | Default value if key does not exist (for GET) |

### **Data Outputs**

| Name | Type | Comment |
|---------|--------|------------------------------------------------|
| QO | BOOL | Event output qualifier (indicates success/failure) |
| STATUS | STRING | Status information (e.g., error message) |
| VALUEO | ANY | Value retrieved (for GET) or confirmed set value |

### **Adapters**

No adapters defined.

## Functionality

The function block operates on a file `settings.ini`, which contains a simple key-value structure in sections (`[Section]`). Its use involves three steps:

1. **INIT** – The INIT event passes the parameters `SECTION` and `KEY`. The function block opens or loads the INI file and prepares the read/write operations. Successful initialization is signaled by the INITO event.
2. **SET** – After initialization, a new value can be written to the previously defined key using SET. The passed value `VALUE` is stored in `settings.ini`, provided the key is not write-protected. If the parameter is read-only and located in `settingsReadOnly.ini`, the write attempt is rejected, triggering the error event **`SETOE`**, and `STATUS` reports `"Key is read-only"`.
3. **GET** – The GET function reads the current value of the key. For read-only parameters, the value from `settingsReadOnly.ini` is always returned. If a normal key does not exist in `settings.ini`, the default value specified via `DEFAULT_VALUE` is returned. The read value appears at output `VALUEO`.

The execution of each event is acknowledged by the respective output (INITO, SETO/SETOE, GETO). The function block `QO` indicates whether the operation was successful, and `STATUS` provides textual feedback.

## Technical Features

- **Generic Data Types** – `VALUE` and `DEFAULT_VALUE` are declared as `ANY`. The function block can therefore work with various data types (e.g., BOOL, INT, REAL, STRING), provided the runtime environment supports them.
- **Write Protection (Factory Default)** – In addition to `settings.ini`, the system also supports the write-protected default file `settingsReadOnly.ini`. Parameters from this file override modifiable values and reject write attempts using `STATUS = "Key is read-only"`. See also [Read-only settings (`settingsReadOnly.ini`)](./settingsReadOnly.md)].
- **Event-based control** – All actions are triggered by events. The function block can therefore be fully integrated into an event-driven system (e.g., IEC 61499).
- **Error handling** – The output qualifier `QO` and the `STATUS` string enable easy error diagnosis (e.g., for read-only keys, missing file, or invalid section).

## State overview

The function block goes through the following main states:

- **Idle** – Waiting for INIT.
- **Initialized** – After successful INIT; ready for SET or GET.
- **Error** – In case of failed initialization or operation; only a new INIT can exit this state.

State transitions are controlled by the INIT, SET, and GET events and their corresponding acknowledgment outputs.

## Application Scenarios

- **Machine Configuration** – Saving and retrieving parameters such as speed, temperature limits, or operating modes in a central INI file.
- **Plant Initialization** – Loading settings once when the controller starts via the INIT event.
- **Online Parameterization** – Dynamically changing values during operation using SET and immediately retrieving them with GET.

## Comparison with Similar Function Blocks

| Function Block | Data Source | Type Support | Event Interface |
|------------|------------------|-----------------------|-----------------------|
| INI | settings.ini | ANY (generic) | INIT, SET, GET |
| FILE_READ | Text File | STRING | REQ, CNF |
| PARAM_DB | Database | Type-specific | Complex |

The INI function block stands out due to its simplicity and direct connection to INI files, without the need for additional drivers or databases. Other function blocks either offer more flexibility (database) or are limited to simple text input/output.

## Conclusion

The INI function block provides a compact and reliable solution for the persistent storage of configuration data in IEC 61499 systems. Its generic data type definition and clear event handling make it versatile. Thanks to its integrated error handling, it is suitable for both development and production environments.

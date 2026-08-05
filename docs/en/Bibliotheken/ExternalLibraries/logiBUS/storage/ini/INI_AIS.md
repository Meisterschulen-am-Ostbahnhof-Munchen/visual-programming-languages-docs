# INI_AIS
![INI_AIS](./INI_AIS.svg)

* * * * * * * * * *
## Introduction
The function block **INI_AIS** is used to load and save strings (STRING) from a `settings.ini` file. The desired value is accessed via a section name and a key. The interface is implemented using unidirectional AIS adapters, allowing the block to both read and write values.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|-------|--------|--------------------------------------|
| INIT | EInit | Service Initialization |

### **Event Outputs**

| Name | Type | Description |
|-------|--------|--------------------------------------|
| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Name | Type | Description |
|---------------|--------|----------------------------------------------------------|
| QI | BOOL | Qualifier for the event input |
| SECTION | STRING | Name of the section in the configuration file |
| KEY | STRING | Name of the key in the specified section |
| DEFAULT_VALUE | STRING | Default value if the entry does not exist |

### **Data Outputs**

| Name | Type | Description |
|--------|--------|--------------------------------------|
| QO | BOOL | Qualifier for the event output |
| STATUS | STRING | Status message (e.g., error text) |

### **Adapter**

| Name | Type | Direction | Description |
|---------|------------------------------|------------|----------------------------------------------------------|
| AIS_OUT | adapter::types::unidirectional::AIS | Plug | Output for the read value (GETO) |
| AIS_IN | adapter::types::unidirectional::AIS | Socket | Input for the value to be stored (SET) |

## Functionality

The function block internally contains an instance of the function block `INI` (from the library `eclipse4diac::storage`). The process is as follows:

1. **Initialization (INIT)**

- The data `QI`, `SECTION`, `KEY`, and `DEFAULT_VALUE` are forwarded to the internal INI block.
- The INIT event pulse starts the INI block.
- Upon completion, INI returns the event `INITO`, which is output externally as `INITO` of the INI_AIS. Simultaneously, the outputs `QO` and `STATUS` are also received.

`` - Immediately after initialization, the `GET` service is automatically triggered in the INI block to read the value from `settings.ini`.

2. **Reading a Value (via AIS_OUT)**

- The read value appears at the data output `VALUEO` of the INI block and is assigned to the data output `D1` of the adapter plug `AIS_OUT`.
- The event `GETO` of the INI block is transferred to the event input `E1` of `AIS_OUT`, allowing the receiving block to retrieve the value.

3. **Writing a Value (via AIS_IN)**

- An external function block can send a value (event `E1` with data `D1`) to the INI_AIS via the adapter socket `AIS_IN`.
- This event triggers the `SET` service of the internal INI function block. The incoming value is passed to the data input `VALUE` of INI.
- After successful writing, INI sends the event `SETO`, which is forwarded to the event output `E1` of `AIS_OUT`. The written value is simultaneously returned via `VALUEO`, so the writing block receives confirmation of the value.

## Technical Features
- **Internal Networking:** This block utilizes the existing `INI` block and encapsulates its complex interface in a simpler, adapter-based form.
- **Unidirectional AIS Adapters:** Data exchange occurs via AIS interfaces, which enable loose coupling between the blocks. The `AIS_IN` socket is responsible for receiving write commands, and the `AIS_OUT` plug is responsible for sending read results.
- **Automatic Read Access:** After initialization, the stored value is immediately read and made available via the output – without a separate GET request.
- **Automatic Read Access:** - **Error Handling:** Status messages are communicated via the `STATUS` output (e.g., file not found, section/key missing).

## State Overview

The function block has no explicitly programmed states. The internal INI block handles state management. From the user's perspective, the following operating phases occur:

- **Initialized (after INIT – INITO):** The function block is ready to read and write values. The value of the specified key has already been read once and is available at the `AIS_OUT` output.
- **Write Operation (via AIS_IN):** An external command triggers a write access. After completion, the new value can be retrieved via `AIS_OUT`.
- **Read Access:** Occurs implicitly after each INIT and is not explicitly controlled.

## Application Scenarios
- **Persistent Configuration Data:** Saving parameters such as device addresses, limits, or operating modes in an INI file.
- **Plug-and-Play Modules:** Modules that read their configuration via the AIS adapter and overwrite it as needed – without hardwiring the data paths.
- **Initialization Values:** Reading default values at system startup, which can be customized via the `settings.ini` file.

## Comparison with Similar Modules

| Module | Description |
|---------------|--------------------------------------------------------------------------------|
| INI | Direct access to INI files with separate GET and SET events. |
| **INI_AIS** | INI extends the INI function block with an adapter-based interface that simplifies the coupling of other function blocks and integrates the handling of read and write operations. |

- Unlike the basic `INI` function block, INI_AIS provides a unified, event-driven interface for read and write components.
- The use of adapters enables flexible connectivity in larger automation networks without the need for individual data wiring.

## Conclusion

The **INI_AIS** function block is a practical extension of the basic `INI` function block.A module that significantly simplifies the use of configuration files in automation projects. By integrating read and write operations into a single adapter interface, system design becomes more modular and streamlined. This module is particularly suitable for scenarios where multiple components need to access the same data storage.

---

### 🌐 Related topic subpages on ms-muc-docs.de

``* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

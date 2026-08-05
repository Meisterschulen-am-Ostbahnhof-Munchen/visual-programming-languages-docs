# Exercise_012m: String Input and Saving to NVS with a Subapp
* * * * * * * * * *
## Introduction
This exercise demonstrates processing a string input from an ISOBUS source and saving and retrieving the value to/from the non-volatile memory (NVS) of an ESP32. All the logic is organized in a self-contained subapp, promoting reusability and modularity. The goal is to implement robust storage of configuration data or user input that persists even after a reboot.
## Function Blocks (FBs) Used

### Sub-Block: Uebung_012m_sub
- **Type**: `SubAppType` (custom SubApp)
- **Internal FBs Used**:
- **StringValue_IS**: `isobus::UT::io::StringValue::StringValue_IS`
- **Parameters**: `QI` = `TRUE`
- **Event Output/Input**:
- Input: (no explicit event input in the XML, controlled by higher-level logic via `IND` – not directly visible here)
- Output: `IND` – signals that the value has been read from the ISOBUS source
- **Data Output/Input**:
- Input: `u16ObjId` (connected via SubApp parameter) – Identification of the isobus object
- Output: `IN` – the read string value
- **NVS**: `logiBUS::storage::esp32_nvs::NVS`
- **Parameters**: `QI` = `TRUE`, `DEFAULT_VALUE` = `STRING#''`
- **Event Inputs/Outputs**:
- Inputs: `SET` (write), `GET` (read), `INIT` (initialization)
- Outputs: `SETO` (Write confirmed), `GETO` (Read confirmed), `INITO` (Initialization complete)
- **Data Inputs/Outputs**:
- Inputs: `KEY` (Key for NVS entry), `VALUE` (Value to be stored)
- Outputs: `VALUEO` (Value read)
- **Q_StringValue**: `isobus::UT::Q::Q_StringValue`
- **Parameters**: None visible in the XML
- **Event Input/Output**:
- Input: `REQ` – Request to output the value to the ISOBUS bus
- Output: (Not listed in the XML, used for bus communication)
- **Data Inputs/Outputs**:
- Input: `u16ObjId` (object ID for isobus), `pau8String` (pointer to string data)
- Output: none visible (sends via isobus)
- **Functionality**:

The subapp `Uebung_012m_sub` encapsulates the entire process: reading a string via `StringValue_IS`, saving it in the NVS via the function block `NVS`, and optionally sending the saved value via the isobus bus with `Q_StringValue`. The parameters `KEY` and `u16ObjId` are passed externally and determine the NVS storage location and the isobus object ID, respectively.

**Process**:

1. After initialization (`NVS.INITO`), a read operation (`NVS.GET`) is automatically triggered. The read value is then stored at `NVS.VALUEO`.

2. Upon an external event (not shown, but logical), `StringValue_IS` is activated. Its output, `IND`, triggers `NVS.SET`, which then saves the current string in the NVS.

3. After a successful write (`NVS.SETO`) or read (`NVS.GETO`), an event is sent to the output `IND` of the subapp.

4. Simultaneously, with each read operation (`NVS.GETO`), the retrieved value is sent to the ISOBUS bus via `Q_StringValue.REQ`, allowing other devices to query the current value.

4. Simultaneously, with each read operation (`NVS.GETO`), the retrieved value is sent to the ISOBUS bus via `Q_StringValue.REQ`, enabling other devices to query the current value.

4. Simultaneously, with each read operation (`NVS.GETO`), the retrieved value is sent to the ISOBUS bus, allowing other devices to query the current value.
## Program Flow and Connections

The main subapp `Uebung_012m` instantiates `Uebung_012m_sub` and provides it with two parameters:

- `KEY` = `KEY_I1_STORE` (a constant key for the NVS entry)
- `u16ObjId` = `InputString_S1` (the ISOBUS object ID from which the input string is read)

The connections within `Uebung_012m_sub` are as follows (from the XML file):

- **Event Flows**:
- `StringValue_IS.IND` → `NVS.SET` (after reading a new string, it is immediately saved)
- `NVS.SETO` → SubApp event output `IND` (signal after successful write)
- `NVS.GETO` → `Q_StringValue.REQ` and → SubApp event output `IND` (after reading, the value is sent to the bus and a signal is output)
- `NVS.INITO` → `NVS.GET` (the stored value is read immediately after initialization)
- **Data flows**:
- `StringValue_IS.IN` → `NVS.VALUE` (the read string is passed to the NVS for storage)
- `NVS.VALUEO` → `Q_StringValue.pau8String` (The extracted string is prepared for transmission)
- `NVS.VALUEO` → SubApp data output `VALUEO` (for forwarding to higher layers)
- `KEY` (external) → `NVS.KEY`
- `u16ObjId` (external) → `StringValue_IS.u16ObjId` and `Q_StringValue.u16ObjId`

**Notes**:

- This exercise requires that the isobus library and the NVS driver for the ESP32 are present in the runtime environment.
- The parameter `DEFAULT_VALUE = STRING#''` defines an empty string as the default if no value has yet been stored in NVS.
- The connections are marked as visible (except for some marked `Visible = false` – these are for internal wiring only and are hidden by default in the IDE's graphical display).

## Summary

This exercise provides training in working with string input, non-volatile memory (NVS), and isobus communication in an encapsulated subapp. Learning objectives include:

- Understanding the initialization and use of the NVS function block.
- Event-driven chaining of read, write, and communication operations.
- Parameterizing subapps for reuse.
- Integrating isobus objects for data transmission.

**Difficulty Level**: Medium
**Required Prior Knowledge**: Basic knowledge of the 4diac IDE, event and data connections, simple function blocks.

**Start of the exercise**: Load the main subapp `Uebung_012m` into a project and connect the inputs `KEY` and `u16ObjId` to corresponding constants or variables. The output `VALUEO` can be connected to a display, for example.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)


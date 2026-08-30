# Exercise_012k: String Input and Saving to INI with Subapp

* * * * * * * * * *

## Introduction

This exercise demonstrates reading a string value from an input source (e.g., a touch input field) and permanently saving this value to an INI file. All functionality is encapsulated in a subapp, which is available as a reusable building block. The saved value is available as an output after each read or save operation and is simultaneously transmitted to an output component (e.g., a display).

## Function Blocks (FBs) Used

### Sub-Block: `Uebung_012k_sub`

- **Type**: SubAppType
- **Internal FBs Used**:
- **`StringValue_IS`**: `isobus::UT::io::StringValue::StringValue_IS`
- Parameters: `QI` = `TRUE`
- Description: This FB reads the current string value from an input source specified via `u16ObjId`. When a new value is detected, it generates an event at output `IND`.
- **`INI`**: `eclipse4diac::storage::INI`
- Parameters: `QI` = `TRUE`, `DEFAULT_VALUE` = `STRING#''`
- Description: This function block stores a string value under a specific key (`KEY`) and range (`SECTION`) in an INI file. It supports the events `SET` (save), `GET` (load), and `INIT` (initialization).

- **`Q_StringValue`**: `isobus::UT::Q::Q_StringValue`

- Parameters: none (parameters are set via data connections)
- Description: This function block converts the binary string provided by `INI` into an output format and sends it to the output location identified by `u16ObjId` (e.g., display).
- **Functionality**:

1. **Initialization**: Upon startup, the `INIT` event of the `INI` function block is triggered. This internally triggers a `GET` event, which loads the last saved value from the INI file.
2. **Saving a New Value**: When the `StringValue_IS` function block detects a new input value, it sends an event to the `SET` input of `INI`. `INI` then saves the current value under the specified `KEY` and `SECTION` and outputs the event `SETO`.

3. **Reading and Output**: As soon as `INI` completes a `GET` operation (both after INIT and after each SET – however, this is only implemented after INIT here), the event is forwarded via `GETO` to the `REQ` input of `Q_StringValue` and simultaneously to the output `IND` of the subapp. The loaded string is then directly output via `VALUEO` and sent to the output location by `Q_StringValue`.

## Program Flow and Connections

The top-level block `Uebung_012k` does not have its own interface (empty `SubAppInterfaceList`). It instantiates the sub-block `Uebung_012k_sub` and passes it three constant parameters:

- `KEY` = `KEY_I1_STORE`
- `SECTION` = `SECTION_I1_STORE`
- `u16ObjId` = `InputString_S1`

These constants are defined in the referenced libraries and determine the key and range under which the string is stored in the INI file, as well as which input/output component is used.

- `KEY` = `KEY_I1_STORE`

These constants are defined in the referenced libraries and specify the key and range under which the string is stored in the INI file, as well as which input/output component is used. **Connections in the Sub-Module**:

- Event Flow:
- `StringValue_IS.IND` → `INI.SET`
- `INI.SETO` → `IND` (Output of the SubApp)
- `INI.GETO` → `Q_StringValue.REQ` and `IND`
- `INI.INITO` → `INI.GET`
- Data Flow:
- `StringValue_IS.IN` → `INI.VALUE`
- `u16ObjId` → `StringValue_IS.u16ObjId` and `Q_StringValue.u16ObjId`
- `KEY` → `INI.KEY`
- `SECTION` → `INI.SECTION`
- `INI.VALUEO` → `Q_StringValue.pau8String` and `VALUEO` (output of the subapp)

**Note**: After a save operation (`SET`), a new `GET` is currently not triggered. Therefore, the newly saved value is only read and passed to the output during the next initialization or a manual `GET`. In this configuration, this serves to store a one-time initial value, which is restored upon restart.

## Summary

This exercise demonstrates how to handle string input, persistent storage in INI files, and the encapsulated reuse of functionality through a subapp. The `INI` function block handles saving and loading, while `StringValue_IS` and `Q_StringValue` manage communication with the hardware (input/output). The subapp `Uebung_012k_sub` can be easily adapted to different object IDs and storage locations in higher-level projects via parameter configuration.

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

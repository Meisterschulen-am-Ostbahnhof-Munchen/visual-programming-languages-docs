# Exercise_012f_AR: Numeric Value Input PHYS and Storage in Non-Volatile Memory (NVS) with Subapp (AR Adapter)
* * * * * * * * * *
## Introduction
This exercise deals with reading a numeric value (physical quantity) and storing it in non-volatile memory (NVS) using an AR adapter. The subapp serves as a building block for applications that need to read a value once and store it permanently.
## Function Blocks (FBs) Used

### Sub-Block: `Uebung_012f_sub_AR`
- **Type**: `MyLib::sys::NVS_IN_AND_STORE_AR`
- **Parameters**:
- `KEY` = `KEY_I1_STORE`
- `stObj` = `InputNumber_I3`
- **Functionality**:

The block receives a numeric value via the built-in AR adapter. The data type and structure of the value are defined by the predefined constant `InputNumber_I3` from the library `DefaultPool_Numeric`. The read value is stored in non-volatile memory under the memory key `KEY_I1_STORE` from the constant library `NVS_Keys`.

## Program Flow and Connections

The sub-app `Uebung_012f_AR` itself has no input or output interfaces. It instantiates the pre-built sub-module `Uebung_012f_sub_AR` and provides it with the two parameters `KEY` and `stObj`. These parameters are assigned the corresponding constants from the imported libraries. The module then executes all the logic for receiving the value via the AR adapter and storing it in the NVS.

**Learning Objectives of this Exercise:**

- Understand how an AR adapter is used for value input.
- Storing values in non-volatile memory using predefined keys.
- Managing constants from external libraries.

**Difficulty Level:** Medium
**Prerequisites:** Basic understanding of 4diac function block networks, SubApps, and the use of adapters.

## Summary

The exercise `Uebung_012f_AR` demonstrates the persistent storage of a numeric value using an AR adapter. The pre-built block `NVS_IN_AND_STORE_AR` is parameterized and encapsulated in a SubApp, resulting in a clear and reusable solution for reading and saving data.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

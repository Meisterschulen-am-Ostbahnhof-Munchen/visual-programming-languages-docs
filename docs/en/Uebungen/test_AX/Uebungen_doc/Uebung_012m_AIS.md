# Exercise_012m_AIS: String Input and Storage in Non-Volatile Memory (NVS) with Subapp (AIS Adapter)

* * * * * * * * * *
## Introduction

This exercise demonstrates the use of an **AIS adapter** (Application Interface Service) to read and store a string in **non-volatile memory (NVS)**. The function block `NVS_IN_AND_STORE_AIS` is used as a subapp to parameterize a predefined key (`KEY`) and an object ID (`u16ObjId`) and thus persistently store any string value.
The exercise shows how external constants from the project import can be used to keep the configuration clean.
## Function Blocks Used

The exercise contains a single subapp block that encapsulates all the functionality.

### Sub-modules: `Uebung_012m_sub_AIS`

- **Type**: `MyLib::sys::NVS_IN_AND_STORE_AIS`
- **Internal Function Blocks Used**: None (the function block is included as a predefined type from a library)
- **Parameters**:
- `KEY` = `KEY_I1_STORE` (Import from `Uebungen::const::NVS::NVS_Keys::KEY_I1_STORE`)
- `u16ObjId` = `InputString_S1` (Import from `Uebungen::const::UT::DefaultPool::InputString_S1`)
- **Functionality**:

The function block `NVS_IN_AND_STORE_AIS` waits for an incoming string via the AIS adapter. As soon as a valid value arrives, it is permanently stored under the specified NVS key (`KEY`). The object ID (`u16ObjId`) identifies the data source or storage location in the DefaultPool. The interaction between AIS and NVS enables low-level, asynchronous data transfer without the need for cyclical queries.

## Program Flow and Connections

The subapp has no input/output interfaces of its own (InterfaceList is empty). It is embedded as an independent component in a higher-level application. The connection to the outside world is exclusively via the AIS adapter provided by the runtime environment.

- The constants `KEY_I1_STORE` and `InputString_S1` must be defined as constants in the project and are transferred to the subapp during import.

`` - Execution starts as soon as the AIS adapter provides a new string. The function block then stores this value persistently.

**Learning Objectives**:

- Understanding the AIS adapter concept for asynchronous data acquisition
- Persistent storage of string data in NVS
- Using imported constants to parameterize function blocks

**Difficulty Level**: Advanced
**Prerequisites**: Basic knowledge of the 4diac IDE, NVS concept, working with constants and imports

## Summary

The exercise `Uebung_012m_AIS` demonstrates how a string is read via an AIS adapter and securely stored in non-volatile memory using a predefined function block. The strict separation of constants and logic ensures that the configuration remains flexible and reusable.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

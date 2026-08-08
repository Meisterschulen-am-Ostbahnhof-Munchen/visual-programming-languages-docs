# Exercise_012e_AR: Numeric Value Input PHYS and Saving INI with Subapp (AR Adapter)
* * * * * * * * * *
This exercise demonstrates the input of a numeric value (PHYS) and its storage using a subapp that utilizes an AR adapter. The entered value is stored under a predefined key in non-volatile memory (NVS). The exercise shows how constants from a central pool (`DefaultPool_Numeric`) and NVS keys are imported and used in a subapp parameter.
## Function Blocks Used (FBs)
## Introduction
### Sub-Block: Exercise_012e_sub_AR
- **Type**: `MyLib::sys::INI_IN_AND_STORE_AR`
- **Internal FBs Used**: No other FBs in the network – the subapp encapsulates all the logic for initialization and storage.

- `KEY` = `KEY_I1_STORE` (constant from `Uebungen::const::NVS::NVS_Keys`)
- `SECTION` = `SECTION_I1_STORE` (constant from `Uebungen::const::NVS::NVS_Keys`)
- `stObj` = `InputNumber_I1` (constant from `Uebungen::const::UT::DefaultPool_Numeric`)
- **Functionality**:

The subapp `INI_IN_AND_STORE_AR` expects a numeric input value (e.g., via the AR adapter) and stores it in non-volatile memory under the specified section and key. The constants ``KEY_I1_STORE`` and ``SECTION_I1_STORE`` define the exact storage location. The constant ``InputNumber_I1`` provides the initial value or structure of the object to be stored.

- **Learning Objectives**:
- Using AR adapters in SubApps
- Working with NVS constants and constant pools
- Parameterizing SubApps to configure storage locations
- **Difficulty Level**: Medium
- **Prerequisites**: Basic knowledge of the 4diac IDE, creating SubApps, understanding of AR interfaces and non-volatile memory.

The exercise consists of a single SubApp that is integrated into a higher-level system. The SubApp is configured using the three parameters. The connection of the AR adapter and the provision of the numeric value are handled outside this subapp definition (e.g., in the parent application). The stored data can then be retrieved using the same keys.


Exercise `Uebung_012e_AR` demonstrates a compact solution for persistently storing a numeric value using a subapp with an AR adapter. By outsourcing the storage logic to the reusable subapp `INI_IN_AND_STORE_AR` and centrally defining keys and objects, a clear separation of configuration and functional logic is achieved.

---

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Program Flow and Connections
## Summary
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
# Exercise_012c_AUDI: Numeric Value Input and Storage INI with Subapp (Adapter Version)

* * * * * * * * * *

## Introduction

This exercise demonstrates the implementation of numeric value input followed by storage in non-volatile memory (NVS) using a SubApp. The unique aspect is the use of a SubApp in the **Adapter Version**, which allows the inputs and outputs to be encapsulated via an adapter mechanism. The SubApp **Exercise_012c_AUDI** contains a pre-built sub-module that handles the entire input and storage process.


``` ## Function Blocks (FBs) Used

### Sub-Blocks: Exercise_012c_sub_AUDI

- **Type**: `MyLib::sys::INI_IN_AND_STORE_AUDI`

- **Internal FBs Used**: The internal FBs of this block are not visible in detail, as it is a predefined block from the library `MyLib::sys`. It likely consists of a chain of blocks for value acquisition, conversion, and NVS storage.

- **Functionality**: The block reads a numeric value from `DefaultPool` under object ID `InputNumber_I1` (imported from `Uebungen::const::UT::DefaultPool`). This value is stored in non-volatile memory (NVS) under the key `KEY_I1_STORE` in the section `SECTION_I1_STORE` (both imported from `Uebungen::const::NVS::NVS_Keys`). The parameters `KEY`, `SECTION`, and `u16ObjId` are passed to the subapp during insertion.

#### Sub-module parameters:

| Parameter | Value | Source / Meaning |

|--------------|-----------------------|----------------------------------------------------------|

| `KEY` | `KEY_I1_STORE` | Constant: Key for the NVS entry |
| `SECTION` | `SECTION_I1_STORE` | Constant: Section in the NVS structure |

| `u16ObjId` | `InputNumber_I1` | Object ID from the DefaultPool that provides the input value |

## Program Flow and Connections

The main subapp `Uebung_012c_AUDI` has **no input/output interfaces** (`SubAppInterfaceList` is empty). The entire functionality is covered by the embedded sub-module `Uebung_012c_sub_AUDI`.

- **Flow**: As soon as the subapp is activated (e.g., by a parent module), the sub-module `INI_IN_AND_STORE_AUDI` starts its internal flow. It retrieves the current value of the span `InputNumber_I1` from `DefaultPool` and stores it persistently in the NVS under the specified key and section constants.

- **Connections**: No explicit data or event connections are visible within the SubApp, as the sub-block completely encapsulates its functionality internally. The SubApp serves as a wrapper to enable configuration (via parameters) and simplify reuse.

- **Learning Objectives**: Understanding the use of SubApps in 4diac, especially as an adapter. Learning about NVS storage and linking input values from a DefaultPool to persistent storage locations.

- **Difficulty Level**: Medium – Basic knowledge of 4diac and function block modeling is required.


## Summary

Exercise *Exercise_012c_AUDI* demonstrates how to read a numeric value via a predefined SubApp (adapter version) and store it in non-volatile memory. Constants for key and section, as well as an object ID from the DefaultPool, are used. The learner gains insight into encapsulating function logic using SubApps and into working with the NVS library in 4diac.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
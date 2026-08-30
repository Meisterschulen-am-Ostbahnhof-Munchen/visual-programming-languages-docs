# Exercise_012a_AX: Numeric Value Input and Storage (Adapter Version)

* * * * * * * * * *

## Introduction

This exercise teaches how to use adapters for numeric value input and persistent storage in non-volatile memory (NVS). The function block `Uebung_012a_AX` encapsulates all the logic in a sub-app that receives a numeric value via an adapter and stores it under a defined key. The adapter version allows for flexible connection to various input sources.
The function block itself has no visible input/output interfaces – communication takes place entirely via the adapter and the configured constants.

## Function Blocks (FBs) Used

### Sub-Blocks: Uebung_012a_sub_AUDI

- **Type**: `MyLib::sys::NVS_IN_AND_STORE_AUDI`
- **Internal FBs Used**:

Not specified in detail – the block contains an encapsulated implementation for adapter-based input and NVS storage.

- **Parameters**:
- `KEY` = `KEY_I1_STORE`

(Key under which the value is stored in the NVS; defined in `Uebungen::const::NVS::NVS_Keys`)

- `u16ObjId` = `InputNumber_I1`

(Identification of the input value; defined in `Uebungen::const::UT::DefaultPool`)

- **Functionality**:

When activated, the FB reads the current numeric value from an adapter and stores it persistently in the NVS under the specified `KEY`. The object ID `InputNumber_I1` references the provision of the value by the higher-level environment (e.g., an HMI input or a higher-level controller).

## Program Flow and Connections

The subapp `Uebung_012a_AX` consists of a single network containing the function block `Uebung_012a_sub_AUDI`. No further connections or event chains are visible, as all interactions are controlled via the adapter and the parameterized constants.

**Process**:

1. The parent application activates the subapp (e.g., via an event).
2. The function block `Uebung_012a_sub_AUDI` reads the current value from the adapter.
3. The read value is stored in the network under the key `KEY_I1_STORE`.

**Learning Objectives**:

- Understanding the adapter interface for input values.
- Familiarity with persistent storage using the network.
- Working with constant keys and object IDs from separate constant sources.

**Difficulty Level**: Medium
**Prerequisites**: Basic knowledge of the 4diac IDE, working with SubApps and constants, adapter concept.

**Integration Notes**:

- The constants `KEY_I1_STORE` and `InputNumber_I1` must be defined in the corresponding `const` resources of the project.
- The adapter must be provided by the calling environment (e.g., via an HMI component).

## Summary

The exercise `Uebung_012a_AX` demonstrates the efficient use of adapters for numeric value input and their persistent storage in the NVS. Encapsulation within a SubApp and the use of constants achieve high reusability and configurability. This component is particularly suitable for scenarios where flexible input sources (e.g., keyboard, bus subsystems) need to be connected to a unified memory logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

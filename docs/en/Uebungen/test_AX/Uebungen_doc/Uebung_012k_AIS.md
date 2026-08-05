# Exercise_012k_AIS: String Input and Storage INI with Subapp (AIS Adapter)

* * * * * * * * * *
## Introduction
The exercise *Exercise_012k_AIS* demonstrates how to store an entered string (e.g., user input or sensor value) in non-volatile memory (NVS). Access is via an AIS adapter (Application Interface Subapp), which simplifies communication with the memory logic. The goal is to learn how to work with persistent data and adapter-based subapplications in the 4diac IDE.

## Function Blocks (FBs) Used

The exercise consists of a single subapplication that encapsulates all the necessary functions.


### Sub-module: Exercise_012k_sub_AIS
- **Type**: `MyLib::sys::INI_IN_AND_STORE_AIS`
- **Internal Function Blocks Used**: Not visible (defined internally by the type)
- **Parameters**:

- `KEY` = `KEY_I1_STORE` (constant from `Uebungen::const::NVS::NVS_Keys`)

- `SECTION` = `SECTION_I1_STORE` (constant from `Uebungen::const::NVS::NVS_Keys`)

- `u16ObjId` = `InputString_S1` (constant from `Uebungen::const::UT::DefaultPool`)

- **Functionality**:

This sub-module The program receives a string input value via an AIS adapter. Upon arrival of a corresponding event (presumably from the adapter), the value is stored in the NVS under the specified section and key. The object ID (`u16ObjId`) identifies the specific input channel. After successful storage, an acknowledgment signal (e.g., `INIT` or `CNF`) is returned.

## Program Flow and Connections

1. **Initialization**: The sub-app `Uebung_012k_sub_AIS` is parameterized with the predefined constants.

2. **Data Flow**: A string is passed to the sub-module via the AIS adapter.

3. **Storage**: The sub-module persistently stores the string in the INI-like NVS structure under the section `SECTION_I1_STORE` and the key `KEY_I1_STORE`.

4. **Feedback**: After the storage process is complete, an event is triggered (e.g., `CNF`) to signal successful completion.

This exercise contains no further connections or event chains—all logic is encapsulated in the type `INI_IN_AND_STORE_AIS`. This ensures a clear separation between application logic and memory access and increases reusability.

## Summary
*Exercise_012k_AIS* demonstrates how to implement a secure, persistent storage operation for a string using an AIS adapter. The learner gains insights into:

- the use of NVS constants (`KEY`, `SECTION`),
- the integration of an adapter-based sub-component,
- parameter passing via the 4diac IDE.

After completing the exercise, the developer can apply this pattern to their own applications where user input or configuration data needs to be stored permanently.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
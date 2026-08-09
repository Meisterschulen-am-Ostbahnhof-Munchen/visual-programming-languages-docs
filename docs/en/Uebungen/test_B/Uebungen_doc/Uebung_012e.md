# Exercise_012e: Numeric Value Input PHYS and Saving to INI with Subapp

* * * * * * * * * *
## Introduction

This exercise demonstrates reading a numeric value via a physical input block (`NumericValue_PHYS`) and permanently saving the value using an INI file block. All the logic is encapsulated in a subapp, which serves as a reusable component. The goal is to capture a value via an object-based configuration, temporarily store it, and read it back as needed.
## Function Blocks (FBs) Used

### Main Subapp: `Uebung_012e`

- Instantiates the subapp `Uebung_012e_sub` with predefined parameters for key, section, and object.
- The main subapp has no inputs/outputs of its own; its behavior is entirely defined by the subapp.

### Sub-modules: `Uebung_012e_sub`

- **Type**: `SubAppType`
- **Internal Function Blocks Used**:
- **`NumericValue_PHYS`**: `isobus::UT::io::NumericValue::NumericValue_PHYS`
- Parameters: `QI` = `TRUE`
- Event output: `IND` (triggered after successful value acquisition)
- Data input: `stObj` (object configuration of type `NumericObjectPool_S`)
- Data output: `rPhys` (physical value as `REAL`)
- **`INI`**: `eclipse4diac::storage::INI`
- Parameters:
- `QI` = `TRUE`
- `DEFAULT_VALUE` = `REAL#0.0`
- Event inputs: `SET`, `GET`, `INIT`
- Event outputs: `SETO`, `GETO`, `INITO`
- Data inputs: `KEY` (`STRING`) `SECTION` (`STRING`), `VALUE` (`REAL`)
- Data output: `VALUEO` (`REAL`)
- **`Q_NumericValue_PHYS`**: `isobus::UT::Q::Q_NumericValue_PHYS`
- Event input: `REQ`
- Data inputs: `stObj` (object configuration), `rPhys` (value)
- Function: Qualifies the physical value (e.g., for scaling or offsetting)
- **How it works**:
1. The function block `NumericValue_PHYS` reads a value according to the object configuration (`stObj`) and outputs it as `rPhys`. Upon successful acquisition, the event `IND` is sent.
2. The event `IND` triggers the `SET` input of the `INI` block. This block stores the value under the specified `KEY` in the `SECTION` of the INI file.
3. After saving, `SETO` is triggered, which is then passed on to the subapp via the output `IND`. 4. Simultaneously, the initialization chain starts: `INITO` from `INI` is connected to `GET`, so that the stored value is read after the subapp starts.
5. The read value (`VALUEO`) is passed to the function block `Q_NumericValue_PHYS`, which qualifies it with the object configuration and forwards it to the output `VALUEO` of the subapp.

## Program Flow and Connections

The subapp operates in two main phases:

1. **Initialization (Start)**:
- The event `INITO` of the `INI` block is internally connected to the `GET` input.
- This immediately reads the stored value from the INI file.
- The read value is passed via `VALUEO` to `Q_NumericValue_PHYS` and to the output of the subapp.
- The event `GETO` is also sent to the output `IND` of the subapp.
2. **Cyclic Operation (on Value Change)**:
- `NumericValue_PHYS` captures a new physical value upon activation.
- This value is passed to the `VALUE` input of the `INI` block via `rPhys`.
- The `IND` event of `NumericValue_PHYS` triggers the `SET` input of `INI`, thus saving the value.
- After successful saving, `SETO` is triggered, which is then passed to the subapp as `IND`.

**Data Connections**:

- The object configuration (`stObj`) is passed externally to `NumericValue_PHYS` and `Q_NumericValue_PHYS`.
- The key and section names (`KEY`, `SECTION`) are passed externally to the `INI` block.
- The stored value (`VALUEO`) is passed to both `Q_NumericValue_PHYS` and directly to the output `VALUEO` of the subapp.

## Summary

This exercise teaches how to handle physical value inputs and persistent data storage in 4diac. This tutorial demonstrates how to create a reusable component using the subapp technique that:

- reads a numeric value via an object,
- saves this value to an INI file,
- restores the saved value at system startup, and
- processes the value using a qualifier block.

The combination of the blocks `NumericValue_PHYS`, `INI`, and `Q_NumericValue_PHYS` illustrates a typical automation scenario (acquiring, saving, and restoring parameters).

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

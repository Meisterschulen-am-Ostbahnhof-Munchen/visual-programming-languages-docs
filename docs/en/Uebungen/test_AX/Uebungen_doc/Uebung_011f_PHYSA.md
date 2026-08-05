# Exercise_011f_PHYSA: Passing Through Numeric Value Input I1 to N3 with PHYSA (Physical Values)

![Uebung_011f_PHYSA_network](./Uebung_011f_PHYSA_network.svg)

* * * * * * * * * *

## Introduction

This exercise demonstrates the direct pass-through of a physical value (PHYSA) without conversion. An incoming numeric value from interface `InputNumber_I3` is passed unchanged to output interface `OutputNumber_N3`. The exercise illustrates how to handle physical values in an ISOBUS context and the simple connection of input and output modules.


## Function Blocks Used (FBs)

Two predefined function blocks are used in the subapp:

### NumericValue_PHYSA
- **Type**: `isobus::UT::io::NumericValue::NumericValue_PHYSA`
- **Parameters**:

- `QI` = `TRUE` (Block enable)

- `stObj` = `InputNumber_I3` (Input reference)

- **Adapter output**: `rPhys` (Physical value)

This function block reads the physical value from the input address `InputNumber_I3`. It is configured so that the value is provided directly (without conversion) at the adapter output `rPhys`.

### Q_NumericValue_PHYSA

- **Type**: `isobus::UT::Q::Q_NumericValue_PHYSA`

- **Parameters**:

- `stObj` = `OutputNumber_N3` (reference to the output address)

- **Adapter Input**: `rPhys` (physical value)

This function block receives the physical value via its adapter input `rPhys` and writes it unchanged to the output address `OutputNumber_N3`.

Both function blocks are configured from the imported libraries `Uebungen::const::UT::DefaultPool_Numeric::InputNumber_I3` and `Uebungen::const::UT::DefaultPool_Numeric::OutputNumber_N3`.


## Program Flow and Connections

The connection between the two modules is established via a single **adapter connection**:

- Source: `NumericValue_PHYSA.rPhys`

- Destination: `Q_NumericValue_PHYSA.rPhys`

The data flow is linear: As soon as `NumericValue_PHYSA` is active (QI=TRUE), it provides the current physical value of `I3`. This value is then passed directly to `Q_NumericValue_PHYSA`, which outputs it to `N3`. No conversion or processing takes place – it is a simple pass-through.

**Classification:**

This exercise is suitable for beginners who want to learn the basics of using ISO-BUS modules and signal flow in 4diac-IDE. It demonstrates the direct coupling of input and output modules via physical adapters.

## Summary

Exercise **Exercise_011f_PHYSA** implements a simple pass-through of a physical value without conversion. The module `NumericValue_PHYSA` reads the value from `InputNumber_I3`, passes it via the adapter output `rPhys` to `Q_NumericValue_PHYSA`, which outputs the value to `OutputNumber_N3`. This exercise is a basic example of using physical values and adapter connections in 4diac.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
# AL_TO_AULI

![AL_TO_AULI](./AL_TO_AULI.svg)

* * * * * * * * * *
## Introduction

The function block **AL_TO_AULI** is a composite function block (FB) that performs a data type conversion from an **AL adapter** (type `LWORD`) to an **AULI adapter** (type `ULINT`).
It serves as a bridge between components that work with different data types and enables seamless integration into IEC 61499-based systems.

## Interface Structure

### **Event Inputs**

The **E1** event is received via the **AL_IN** socket (adapter `AL`). This event triggers the conversion of the incoming LWORD value.

### **Event Outputs**

The **E1** event is sent via the **AULI_OUT** plug (adapter `AULI`) as soon as the conversion is complete and the ULINT value is available at the output.

### **Data Inputs**

| Name | Adapter Port | Data Type | Description |
|--------|--------------|----------|----------------------------------|
| AL_IN | D1 | LWORD | Input value in LWORD format |

### **Data Outputs**

| Name | Adapter Port | Data Type | Description |
|---------|--------------|----------|-----------------------------------|
| AULI_OUT| D1 | ULINT | Converted Value in ULINT Format |

### **Adapter**

| Type | Direction | Name | Description |
|-------------|----------|-----------|----------|--------------------------------------|
| `AL` | Socket | AL_IN | Input adapter with LWORD data |
| `AULI` | Plug | AULI_OUT | Output adapter with ULINT data |

## Functionality

The function block (FB) performs the conversion using an internal block `F_LWORD_TO_ULINT` from the library `iec61131::conversion`.

- As soon as an event **E1** arrives at the input adapter **AL_IN**, it is forwarded to the input **REQ** of the internal conversion block.
- Simultaneously, the data value **D1** (LWORD) is passed to the **IN** input of the converter.
- After successful conversion, the internal function block signals this via its **CNF** output, which triggers the **E1** event of the **AULI_OUT** output adapter.
- The converted ULINT value is then available at the **D1** data output of the output adapter.

## Technical Specifications

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- **License:** This function block is provided under the **Eclipse Public License 2.0**.
- **Version:** 1.0 (as of 2026-02-17)
- **Dependencies:** It requires the function `F_LWORD_TO_ULINT` from the `iec61132::conversion` library.
- **Portability:** As a composite function block, it is platform-independent and can be used in any 4diac IDE environment.
- **Type Hash:** The function block has an attribute `eclipse4diac::core::TypeHash` for unique identification (value empty).

## State Overview

The function block **AL_TO_AULI** does not have its own state machine – it delegates all conversion logic to the internal function block `F_LWORD_TO_ULINT`. This makes it behave like a transparent conversion layer that only becomes active upon an incoming event and returns to its idle state after the conversion.

## Application Scenarios

- **Data Type Conversion** in PLC or automation systems when an LWORD signal (e.g., from a communication module) needs to be converted into a ULINT value for subsequent processing (e.g., counters or arithmetic).
- **Adapter bridge** between function blocks that work exclusively with the AULI adapter and those that use the AL adapter.
- **Migration** of existing LWORD-based components to ULINT-based systems without changing the signal chain.

## Comparison with similar function blocks

- **F_LWORD_TO_ULINT (direct converter):** This pure function block performs the same conversion, but without adapter interfaces. It is suitable for simple data flow models, while **AL_TO_AULI** is specifically optimized for use in adapter-based architectures.
- **Other adapter converters (e.g., AL_TO_UDINT, AL_TO_DWORD):** Similar function blocks exist for other target types (UDINT, DWORD). They differ only in the output data type but follow the same design pattern.

## Conclusion

The **AL_TO_AULI** function block offers a simple and robust way to convert LWORD data to ULINT data via adapters. By encapsulating the conversion logic in a composite function block, the interface remains clear and reusable. It is particularly suitable for modular IEC 61499 projects where adapters are used as standardized communication interfaces.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

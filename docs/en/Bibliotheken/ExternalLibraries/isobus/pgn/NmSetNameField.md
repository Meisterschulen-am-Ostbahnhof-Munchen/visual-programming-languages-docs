# NmSetNameField

<img width="1070" height="248" alt="image" src="https://github.com/user-attachments/assets/f7752178-ab95-47c7-9972-b0f2c8b49ec3" />
![NmSetNameField](./NmSetNameField.svg)

* * * * * * * * * *
## Introduction

The function block `NmSetNameField` converts an ISO NAME, as defined in ISO 11783-5 (section 5.1.2), into a structured representation. An ISO NAME is an 8-byte identifier used in agricultural and forestry machinery (ISOBUS) for the unique identification of electronic control units (ECUs). This function block extracts the individual fields from the byte array and populates a corresponding data structure (`NAMEFIELD_T`). This facilitates further processing and evaluation of the device information in an IEC 61499 application.

## Interface Structure

### **Event Inputs**

- **REQ**: Starts processing. Upon receiving this event, the value at `au8IsoName` is processed.

### **Event Outputs**

- **CNF**: Triggered as soon as the conversion is complete and the structured data is available at the output.

### **Data Inputs**

- **au8IsoName** (`isobus::pgn::CF_NAME_T`): An 8-byte array containing the raw ISO NAME according to ISO 11783-5.

### **Data Outputs**

- **(no explicit name)** (`isobus::pgn::NAMEFIELD_T`): The output variable contains the structured breakdown of the ISO NAME. The exact structure of the `NAMEFIELD_T` structure is defined by the `isobus::pgn` library used.

### **Adapters**

This function block does not use any adapters.

## Functionality

When the `REQ` event is triggered, the function block processes the incoming byte array `au8IsoName`. The Structured Text (ST) implementation extracts the individual components of the ISO NAME bit- and byte-wise and assigns them to the corresponding fields of the `NAMEFIELD_T` output structure. The logic follows the bit mapping exactly as defined in ISO 11783-5, section 5.1.2. After the calculations are complete, the `CNF` event is set to signal the successful completion of the operation.

## Technical Features

- **Bit Manipulation:** This block uses logical AND operations (`AND`), shift operations (`SHL`, `SHR`), and type conversions (`BYTE_TO_WORD`, `BYTE_TO_DWORD`) to isolate the relevant bits from the input array.
- **Library Dependency:** This block depends on the data types `CF_NAME_T` and `NAMEFIELD_T` from the `isobus::pgn` library. The exact definition of these types (e.g., the field names in `NAMEFIELD_T`) is outside this block.
- **Library Dependency:** This block depends on the data types `CF_NAME_T` and `NAMEFIELD_T` from the `isobus::pgn` library. The precise definition of these types (e.g., the field names in `NAMEFIELD_T`) is outside this block.
- * **Deterministic:** The operation is purely data-driven and has no internal state. With the same input, it always produces the same output.

## State Overview

The function block has no persistent internal state. It behaves like a pure function:

1. **Wait/Idle State:** The block waits for the `REQ` event.
2. **Processing State:** At `REQ`, the input data is processed and the output structure is calculated. This state is instantaneous (no delay).
3. **Output:** Immediately after the calculation, the `CNF` event is triggered and the calculated `NAMEFIELD_T` structure is output. The block then returns to the wait state.

## Application Scenarios

- **ISOBUS Device Identification:** In an ISOBUS network manager that needs to decode incoming NAME data from connected ECUs to identify device type, manufacturer, and instance.
- **Diagnostics and Logging:** For clear display and logging of device names in a human-readable, structured format instead of the raw 8-byte value.
- **Filtering and Addressing:** As a preprocessing step to make decisions about further communication based on specific fields (such as device class or manufacturer code).
- **ISOBUS Device Identification:**
## ⚖️ Comparison with Similar Components

- **Counterpart `NmGetIsoName`:** A hypothetical complementary component would perform the reverse operation: It would take a `NAMEFIELD_T` structure as input and generate the corresponding 8-byte `CF_NAME_T` array. `NmSetNameField` is the decoder; its counterpart would be the encoder.
- **Generic Byte Parsers:** Unlike generic byte-to-structure converters, this block is specifically tailored to the ISO NAME format and contains the exact bit logic of the standard. Using this specialized block reduces errors and increases maintainability in the ISOBUS context.
*
## 🛠️ Related Exercises

- [Exercise_120](../../../../Uebungen/test_B/Uebungen_doc/Uebung_120.md)
- [Exercise_121](../../../../Uebungen/test_B/Uebungen_doc/Uebung_121.md)
- [Exercise_122](../../../../Uebungen/test_B/Uebungen_doc/Uebung_122.md)
- [Exercise_122b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_122b.md)

## Conclusion

The `NmSetNameField` function block is an essential tool for working with ISOBUS networks in 4diac. It abstracts the complex bit manipulation required to interpret the ISO NAME and provides the information in an easily processed, structured format. Its use promotes correct, standards-compliant applications and significantly improves the readability of the source code.

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

# AULI_TO_AW

![AULI_TO_AW](./AULI_TO_AW.svg)

* * * * * * * * * *
## Introduction

The function block **AULI_TO_AW** is a composite function block (FB) that converts a ULINT adapter interface (AULI) to a WORD adapter interface (AW). It is used where a unidirectional data type conversion from unsigned 64-bit integer to 16-bit word is required.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| E1 (via AULI_IN) | Event | Starts the conversion |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| E1 (via AW_OUT) | Event | Signals completion of conversion |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| D1 (via AULI_IN) | ULINT | ULINT input value |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| D1 (via AW_OUT) | WORD | WORD output value |

### **Adapters**

| Type | Role | Name | Comment |
|-----|-------|------|-----------|
| **adapter::types::unidirectional::AULI** | Socket | AULI_IN | ULINT Adapter Input |
| **adapter::types::unidirectional::AW** | Plug | AW_OUT | WORD Adapter Output |

## Functionality

The function block internally uses the IEC 61131 function **F_ULINT_TO_WORD** to convert the incoming ULINT value (via the AULI_IN adapter) into a WORD value. The process is purely event-driven:

1. An incoming event at the AULI_IN adapter (E1) triggers the conversion.
2. The ULINT value (D1) is passed to the function block **F_ULINT_TO_WORD**.
3. After the conversion is complete, the output event is sent at the AW_OUT adapter (E1), and the WORD value is available at the output data point (D1).

## Technical Features

- **Unidirectional Adapters**: Both AULI_IN and AW_OUT are unidirectional adapters, meaning data flow is only in one direction.
- **Composition**: The function block is built from a single integrated conversion function block, making it easy to understand and maintain.
- **Type Conversion**: The conversion from ULINT (64-bit) to WORD (16-bit) results in an overflow for values greater than 65535 – the user must ensure that the input value is in the range 0…65535.

## State Overview

Since this is a pure composite function block without its own state machine, there are no internal states. All logic is implemented by the embedded function block **F_ULINT_TO_WORD**, which has simple, event-driven function execution.

## Application Scenarios

- **Interface Adaptation**: When an AULI adapter (e.g., from a sensor unit) needs to be integrated into a system that only supports Word adapter (AW) interfaces.
- **Data Reduction**: Reducing the data width from 64 bits to 16 bits for subsequent processing steps.
- **Legacy Integration**: Integrating older components that only work with 16-bit data into a modern environment that provides ULINT.

## Comparison with Similar Function Blocks

Comparable function blocks include **ULINT_TO_INT** and **ULINT_TO_DWORD**, which offer different target formats. **AULI_TO_AW** is specifically tailored to the unidirectional adapter types of the 4diac world. Unlike a simple type conversion, this function block also handles event and adapter linking, significantly simplifying integration into adapter-based architectures.

## Conclusion

**AULI_TO_AW** is a practical, compact conversion function block that bridges the gap between ULINT and WORD adapter interfaces. By encapsulating the IEC function in a composite function block, the user is relieved of adapter details and receives a clean, event-driven transformation solution. This function block is particularly suitable for scenarios where data widths need to be reduced while maintaining the adapter structure.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

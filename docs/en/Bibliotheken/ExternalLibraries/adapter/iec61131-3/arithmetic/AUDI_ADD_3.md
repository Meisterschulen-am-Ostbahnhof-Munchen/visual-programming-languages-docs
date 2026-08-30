# AUDI_ADD_3

![AUDI_ADD_3](./AUDI_ADD_3.svg)

* * * * * * * * * *

## Introduction

The function block `AUDI_ADD_3` performs an arithmetic addition of three input values. It is a generic block that receives the values via adapter interfaces and outputs the result via another adapter. The function block is designed as part of the 4diac IDE for IEC 61499-2.

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No direct data inputs available. The input values are provided via the adapter interfaces.

### **Data Outputs**

No direct data outputs available. The result is provided via the adapter output.

### **Adapter**

| Name | Type | Direction | Comment |
| ------ | ----- | ---------- | ----------- |
| IN1 | `adapter::types::unidirectional::AUDI` | Socket (Input) | ADD input 1 |
| IN2 | `adapter::types::unidirectional::AUDI` | Socket (Input) | ADD input 2 |
| IN3 | `adapter::types::unidirectional::AUDI` | Socket (Input) | ADD input 3 |
| OUT | `adapter::types::unidirectional::AUDI` | Plug (Output) | ADD result |

## Functionality

The function block adds the three values received via the adapters `IN1`, `IN2`, and `IN3`. The result is continuously output via the adapter `OUT`. Since this is a generic function block, the specific data type of the addition is determined at runtime by the attributes `eclipse4diac::core::GenericClassName` and `eclipse4diac::core::TypeHash`.

## Technical Features

- The function block is stateless (purely combinatorial) – no ECC is required.
- It uses the Eclipse 4diac generic type system to enable flexible reusability for various arithmetic data types (e.g., INT, REAL, LREAL).
- The connection is established exclusively via adapters of type `adapter::types::unidirectional::AUDI`, which provide a standardized unidirectional interface for arithmetic operations.

## State Overview

The function block (FB) does not have a state machine (no ECC elements in the XML). Its behavior is purely data-driven: The output is recalculated whenever an input value changes.

## Application Scenarios

- **Summation of Measured Values:** Summing three analog sensor values (e.g., temperatures).
- **Mixing Calculation:** Adding three quantities or volume flows in process engineering.
- **Generic Addition:** Used in libraries where the data type is defined during project planning.

## Comparison with Similar Function Blocks

- **ADD_2:** Performs an addition of two values – `AUDI_ADD_3` extends this to three inputs.
- **ADD_4:** Adds four values – `AUDI_ADD_3` specifies three inputs.
- **MUL_3:** Multiplies three values – unlike addition.

All of the above blocks use the same adapter concept and are generic.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AUDI_ADD_3` is a flexible, generic function block for adding three values. Its pure adapter interface and stateless nature make it easy to use and ideal for modular automation solutions based on IEC 61499.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

# AR_ADD_2

![AR_ADD_2](./AR_ADD_2.svg)

* * * * * * * * * *

## Introduction

The function block **AR_ADD_2** is used to calculate the arithmetic addition of two values. It is designed as a generic function block and implements the basic arithmetic operation via adapter interfaces. The block is platform-independent and complies with the IEC 61499 standard.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapters**

| Name | Direction | Type | Comment |
| ------------- | ---------- | ----- | ----------- |
| `IN1` | Socket | `adapter::types::unidirectional::AR` | ADD input 1 |
| `IN2` | Socket | `adapter::types::unidirectional::AR` | ADD input 2 |
| `OUT` | Plug | `adapter::types::unidirectional::AR` | ADD result |

The adapters are of type `unidirectional::AR` and enable type-safe connections with other function blocks that support the same adapter type.

## Functionality

The function block adds the two values received via adapters `IN1` and `IN2`. The result is provided at adapter `OUT`. The precise data interpretation (data type, value range) is determined by the adapter type used; the function block itself operates generically and delegates the type information to the underlying framework.

The actual calculation takes place in the background via the configured runtime environments – the function block merely defines the interfaces and the semantics of the addition.

## Technical Features

- **Generic Structure** – The function block uses a generic class name (`GEN_AR_ADD`) at runtime, which is defined by the attribute `eclipse4diac::core::GenericClassName`. This allows for later specialization for specific data types (e.g., integers or floating-point numbers).
- **Adapter-Based** – Instead of individual data inputs and outputs, all signals are routed via unidirectional adapters. This simplifies encapsulation and reuse in complex systems.
- **Package Information** – The function block is organized in the package `adapter::iec61131::arithmetic`, indicating its origin from an IEC 61131 adapter library.
- **No State Logic** – The addition is stateless; there is no internal state machine.

## State Overview

The function block does not have a state machine. The calculation is purely data-driven – if the input adapters change, the result is recalculated.

## Application-Specific Scenarios

- **Signal Processing** – Combining two analog or digital measured values into a sum.
- **Control Engineering** – Summing counter readings or time values.
- **Generic Library Function Blocks** – Use as a basis for application-specific, typed addition function blocks (e.g., `AR_ADD_INT`, `AR_ADD_REAL`).

## Comparison with Similar Function Blocks

Compared to classic, data-input-based addition blocks (e.g., `ADD`), `AR_ADD_2` is distinguished by its adapter interfaces. While standard adders often operate with single inputs (`IN1`, `IN2`) and one output (`OUT`), adapters enable direct connection to more complex data structures and greater reusability through type safety. The block is intentionally generic, allowing for dynamic type adjustment at runtime.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

AR_ADD_2` is a compact, generic function block for adding two values using adapter interfaces. It is particularly suitable for cross-system applications where type flexibility and loose coupling via adapters are required. Its simple, stateless architecture makes it robust and easy to integrate into existing automation projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

# AUDI_MUL_3

![AUDI_MUL_3](./AUDI_MUL_3.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_MUL_3** is a generic function block for multiplying three input values. The values are provided via unidirectional adapters of type **AUDI**, and the result is output via a similar adapter. The function block is designed for use in IEC 61499-based control systems.
## Interface Structure

### **Event Inputs**

Not present – all data transmission is adapter-based without explicit event control.

### **Event Outputs**

Not present.

### **Data Inputs**

Not present – the input values are provided via **Sockets IN1, IN2, and IN3** as adapters.

### **Data Outputs**

Not present – the result is output via **Plug OUT** as an adapter.

### **Adapter**

| Name | Direction | Type | Description |
|------|----------|-----|--------------|
| **IN1** | Socket (Input) | `adapter::types::unidirectional::AUDI` | First multiplication factor. |
| **IN2** | Socket (Input) | `adapter::types::unidirectional::AUDI` | Second multiplication factor. |
| **IN3** | Socket (Input) | `adapter::types::unidirectional::AUDI` | Third multiplication factor. |
| **OUT** | Plug (Output) | `adapter::types::unidirectional::AUDI` | Result of multiplication `IN1 * IN2 * IN3`. |

## Functionality

The function block **AUDI_MUL_3** performs an arithmetic multiplication of the three values provided via the adapters **IN1, IN2, and IN3**. The product is calculated continuously and made available via the adapter **OUT**. The underlying data type **AUDI** is defined generically (via the attribute `eclipse4diac::core::GenericClassName`) and can be replaced by a specific numeric type (e.g., INT, REAL) at configuration time. Explicit triggering by events is not required, as the adapters handle the data transfer independently.

## Technical Features

- **Generic Data Type**: The function block is designed as a generic block (`GenericClassName = 'GEN_AUDI_MUL'`). The adapter type used, **AUDI**, can be replaced by any numeric data type, as long as the same type is used on all adapters.
- **Adapter-based interface**: Instead of discrete data and event ports, the function block communicates exclusively via unidirectional adapters. This enables flexible chaining with other function blocks of the same adapter type.
- **No explicit state logic**: The function block does not require an internal state machine – multiplication is purely data flow-driven.

## State overview

The **AUDI_MUL_3** does not have an explicit state machine. The output **OUT** always corresponds to the current product of the three inputs. As soon as valid data is present at all sockets, the result is calculated without delay.

## Application scenarios

- **Multidimensional calculations**: Combining several physical quantities that need to be multiplied (e.g., volume from length, width, and height).
- **Signal scaling**: Multiplying a sensor value by two calibration factors.
- **Nested arithmetic**: Use as part of a larger calculation chain where the product of three inputs is required.

## Comparison with Similar Function Blocks

- **AUDI_MUL_2**: Performs the multiplication of only two inputs. **AUDI_MUL_3** extends this functionality to three factors.
- **AUDI_ADD_3**: Performs the addition of three values, while **AUDI_MUL_3** performs multiplication – both use the same adapter structure.
- **Conventional IEC 61499 Function Blocks**: Typical multifunction blocks often use separate data and event ports. The adapter-based approach simplifies typing and reusability in generic frameworks.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

**AUDI_MUL_3** is a compact, generic function block for multiplying three values. Its adapter-driven interface and generic typing make it ideal for modular, reusable control applications. Its simple, data-flow-oriented approach without state machines makes it intuitive to use and extensible.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

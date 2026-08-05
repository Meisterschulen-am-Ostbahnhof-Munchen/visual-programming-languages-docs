# AUDI_ADD_2
![AUDI_ADD_2](./AUDI_ADD_2.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_ADD_2** performs an arithmetic addition of two input values and outputs the result. The block is generic and uses a standardized adapter interface of type `AUDI`. This allows it to be used for different data types (e.g., integers, floating-point numbers) without requiring modification of the function block itself.
## Interface Structure
### **Event Inputs**
None.

#### **Event Outputs**
None.

#### **Data Inputs**
None.

#### **Data Outputs**
None.

#### **Adapter**

| Type | Direction | Name | Comment |

|-----|----------|------|-----------|

| `adapter::types::unidirectional::AUDI` | Socket (Input) | **IN1** | ADD input 1 |

| `adapter::types::unidirectional::AUDI` | Socket (Input) | **IN2** | ADD input 2 |

| `adapter::types::unidirectional::AUDI` | Plug (Output) | **OUT** | ADD result |

The three adapters are all of the same type, `AUDI`. This adapter type encapsulates the actual data value (e.g., a numerical value) and enables unidirectional data transfer from the socket to the plug. The addition is performed between the values of `IN1` and `IN2`; The result is provided to `OUT`.

## Functionality
The function block **AUDI_ADD_2** does not have traditional data inputs or events. Instead, it communicates exclusively via adapters. As soon as both input adapters (`IN1` and `IN2`) contain valid values, the sum `IN1 + IN2` is calculated internally, and the resulting value is output via the output adapter `OUT`.

The function block is generic: The actual data type used is determined by the adapter configuration and the generic attributes (`GenericClassName`, `TypeHash`). This allows the use of different numeric data types (e.g., `INT`, `REAL`, `LREAL`) without requiring multiple instantiations of the function block itself.

## Technical Features
- **Pure Adapter Interface**: No events or direct data inputs/outputs – all communication occurs via adapters.
- **Generic Execution**: The attributes `eclipse4diac::core::GenericClassName` and `eclipse4diac::core::TypeHash` allow the function block to be specialized for different data types at runtime.
- **Unidirectional Adapters**: The adapters used, of type `AUDI`, are unidirectional, meaning they only transmit values in one direction (socket → plug).
- - **No State Control**: The function block (FB) contains no Execution Control Chart (ECC) and operates without events; the calculation is performed immediately upon receipt of the input values.

## State Overview
The **AUDI_ADD_2** function block has no states (no ECC). The addition is performed without delay when valid input values are present.

## Application Scenarios
- **Arithmetic Processing in Adapter-Based Systems**: If an architecture consistently relies on adapters, this FB offers a clean way to add two numerical values.
- **Generic Calculations**: Thanks to its generic design, the FB can be used in algorithms that work with different data types (e.g., mixed integer and floating-point environments).
- **Data Flow Systems**: In purely data flow-oriented applications where no events are required, the FB integrates seamlessly.

## Comparison with Similar Function Blocks
- **Classic ADD Function Blocks (e.g., `ADD` from IEC 61131-3)**: These typically have concrete data inputs and outputs as well as event control. The `AUDI_ADD_2` replaces this with an adapter interface, enabling a higher level of abstraction and encapsulation.
- **Generic Adders (e.g., `GEN_ADD`)**: Such function blocks are also generic but often use direct data ports. The `AUDI_ADD_2` is specifically optimized for adapter-based interfaces.

## Conclusion
The **AUDI_ADD_2** is a specialized, generic addition function block for adapter-based 4diac IDE environments. By eliminating traditional ports and utilizing the `AUDI` adapter type, it is particularly well-suited for data flow-oriented and highly modularized control applications. Its generic design increases reusability across different data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
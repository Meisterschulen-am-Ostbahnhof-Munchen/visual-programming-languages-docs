# AR_ADD_3
![AR_ADD_3](./AR_ADD_3.svg)
* * * * * * * * * *
## Introduction
The function block `AR_ADD_3` is used to calculate the arithmetic addition of three values. It is a generic function block (FB) according to IEC 61499-2, which operates via adapter interfaces. The block is designed to be used in conjunction with the adapter `adapter::types::unidirectional::AR` from the library `adapter::iec61131::arithmetic`.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

No direct data inputs. Input values are provided via adapter interfaces.

### **Data Outputs**

No direct data outputs. The result is provided via an adapter output.

### **Adapter**

| Direction | Name | Type | Comment |

|-----------|------|--------------------------------------|-----------------|

| Sockets | IN1 | `adapter::types::unidirectional::AR` | ADD input 1 |

| Sockets | IN2 | `adapter::types::unidirectional::AR` | ADD input 2 |

| Sockets | IN3 | `adapter::types::unidirectional::AR` | ADD input 3 |

| Plugs | OUT | `adapter::types::unidirectional::AR` | ADD result |

## Functionality

The function block adds the three values received via the adapter sockets `IN1`, `IN2`, and `IN3` and provides the result via the adapter plug `OUT`. The exact semantics of the addition (e.g., supported data types, overflow behavior) are determined by the implementation of the adapter type used, `AR`. The function block is generic, meaning it can be parameterized for different data types (e.g., by type hash or generic class name).

## Technical Features
- **Generic Block:** The actual data type handling is controlled via the attributes `eclipse4diac::core::GenericClassName` (value: `'GEN_AR_ADD'`) and `eclipse4diac::core::TypeHash`.
- **Adapter-Based Communication:** The block uses adapters (`adapter::types::unidirectional::AR`) exclusively for input and output. This enables loose coupling and reusability in different contexts.
- **License:** Released under the Eclipse Public License 2.0 (EPL-2.0).
- **Compatibility:** Developed for the 4diac IDE and the Eclipse 4diac runtime environment.

## State Overview

The block does not have an explicit state diagram (ECC). It is a purely combinatorial function: The output is always the sum of the three inputs. There are no internal states or time dependencies.

## Application Scenarios
- **Multiple Addition in Control Systems:** When three analog or digital values (e.g., sensor data, setpoints) need to be summed.
- **Generic Library Blocks:** Used in reusable function block libraries where the data types are defined at configuration time.
- **Adapter-Based Architectures:** In systems that rely on standardized adapter interfaces to enable flexible chaining of functions.

## Comparison with Similar Blocks

**AR_ADD_2 / AR_ADD_4 etc.:** These blocks differ only in the number of inputs (two or four). `AR_ADD_3` is specifically optimized for adding exactly three values. The generic approach allows all these variants to be implemented, if needed, by parameterizing a common base type.

## Conclusion

`AR_ADD_3` is a clear, generic function block for adding three values using adapters. Its abstraction via generic attributes and adapters makes it well-suited for IEC 61499 applications that require flexible and reusable signal processing.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

# AB_SPLIT_7
![AB_SPLIT_7](./AB_SPLIT_7.svg)

* * * * * * * * * *
## Introduction
The function block **AB_SPLIT_7** is used to split a single incoming adapter of type `adapter::types::unidirectional::AB` into seven identical output adapters. It is implemented as a generic block (`GEN_AB_SPLIT`) and can therefore be instantiated for various specific adapter types that conform to the unidirectional AB protocol. It was developed under the Eclipse Public License 2.0.
## Interface Structure

### **Event Inputs**

None available.

#### **Event Outputs**

None available.

#### **Data Inputs**

None available.

#### **Data Outputs**

None available.

#### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| IN | `adapter::types::unidirectional::AB` | Socket (Input) | Incoming adapter that is distributed to the outputs. |

| OUT1 | `adapter::types::unidirectional::AB` | Plug (Output) | First outgoing adapter, identical to the input. |

| OUT2 | `adapter::types::unidirectional::AB` | Plug (Output) | Second outgoing adapter. |

| OUT3 | `adapter::types::unidirectional::AB` | Plug (Output) | Third outgoing adapter. |

| OUT4 | `adapter::types::unidirectional::AB` | Plug (Output) | Fourth outgoing adapter. |

| OUT5 | `adapter::types::unidirectional::AB` | Plug (Output) | Fifth outgoing adapter. |

OUT6 | `adapter::types::unidirectional::AB` | Plug (Output) | Sixth outgoing adapter. |

OUT7 | `adapter::types::unidirectional::AB` | Plug (Output) | Seventh outgoing adapter. |

## Functionality

This component functions purely as a signal distributor for adapter connections. Every data or event flow arriving via socket `IN` is forwarded unchanged and in parallel to all seven output plugs (`OUT1` – `OUT7`). No processing, buffering, or state changes take place. Therefore, this component should be understood as a passive "splitter."

Since these are unidirectional adapters, communication only occurs in one direction – from the socket to the plugs. The outputs are logically identical and can be connected independently to subsequent function blocks.

## Technical Features
- **Generic Type**: The function block is declared as a generic FB (GenericClassName `'GEN_AB_SPLIT'`). This allows reuse for different implementations of the unidirectional AB adapter without having to redefine the interface.
- **No Internal Logic**: There are no event triggers, data operations, or state machines. The FB is completely defined by its adapter wiring.
- **Unidirectionality**: The adapter type `unidirectional::AB` supports only one direction of data flow. There are no return channels.

## State Overview

The function block does not have an internal state machine (ECC). It is static and does not execute any sequential logic. There are no distinguishable operating states.

## Application Scenarios
- **Distributing control information** to multiple parallel consumers (e.g., controlling several identical actuators).
- **Splitting a feedback signal** for separate evaluation in different branches of an automation application.
- **Generating multiple identical adapter strings** for redundancy or separate monitoring.

Due to its generic design, the function block can be used in various contexts once the specific adapter type is defined.

## Comparison with Similar Function Blocks
- **AB_MERGE**: Merges multiple incoming adapters into one output – the opposite function to AB_SPLIT_7.
- **AB_SPLIT_N**: Generalization with a configurable number of outputs, if available. AB_SPLIT_7 is a fixed 1:7 split.
- **Direct wiring without a splitter**: If multiple identical copies are needed, the source function block would have to be instantiated multiple times, which increases the design complexity. The splitter reduces redundancy at the adapter connection level.

## Conclusion

The **AB_SPLIT_7** is a simple yet useful function block for multiplying a unidirectional adapter connection. Its generic nature and clear separation of inputs and outputs make it a reusable tool in the 4diac IDE, especially in scenarios requiring parallel signal distribution. It contributes to the modularity and clarity of industrial control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

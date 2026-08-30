# AUDI_MUL_2

![AUDI_MUL_2](./AUDI_MUL_2.svg)
**Image:** No image available.

* * * * * * * * * *
The function block `AUDI_MUL_2` is a generic function block for calculating the arithmetic product of two numeric values. It receives its operands via two input adapters and outputs the result via one output adapter. Its generic design allows the use of different data types (e.g., integers, floating-point numbers), which are defined by the specific adapter type.

None.

No direct data ports. The input values are transmitted via the adapters `IN1` and `IN2`.

No direct data ports. The result is output via the adapter `OUT`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| **Socket** (Input) | `IN1` | `adapter::types::unidirectional::AUDI` | First Multiplication Operand |
| **Socket** (Input) | `IN2` | `adapter::types::unidirectional::AUDI` | Second Multiplication Operand |
| **Plug** (Output) | `OUT` | `adapter::types::unidirectional::AUDI` | Product of the two input values |

*Note:* The adapter type `AUDI` is a unidirectional, typed adapter that encapsulates the actual numerical value.

## Functionality

The function block performs the multiplication `OUT = IN1 * IN2` as soon as both input values are available via the adapters. Since no events are present, the processing is purely data-driven: As soon as the socket adapters `IN1` and `IN2` provide valid values, the product is calculated and output via the plug adapter `OUT`.

The function block is designed generically. The specific data type (e.g., `REAL`, `INT`, `LINT`) is determined by the adapter type used. Multiplication is performed using the operation defined for that type.

- **Adapter-Based Communication:** The function block does not use traditional event/data ports, but exclusively adapters. This enables loose coupling and reuse in different contexts.
- **Generic Design:** The attributes `eclipse4diac::core::GenericClassName` and `eclipse4diac::core::TypeHash` identify the function block as generic. The actual data type is only defined in the specific project, e.g., by typing the adapter.
- **No Execution Control Chart (ECC):** Since no events exist, a state machine is not required. Processing occurs continuously with valid data.

This function block has no states or ECC state diagrams. Execution is determined solely by the data flow.

- Arithmetic calculations in industrial control applications where the multiplication of two values is required (e.g., scaling, unit conversion).
- Use in complex function blocks where operands are obtained from other components via adapters.
- Replacement for classic MUL function blocks when loose coupling via adapters is desired.
- **Classic MUL FB** (with event/data ports): Operates in an event-driven manner and requires explicit data inputs/outputs. `AUDI_MUL_2`, on the other hand, uses adapters, which allows for more flexible interconnection.
- **Other generic arithmetic function blocks** (e.g., `AUDI_ADD_2`): Same structure, but with a different operation. The adapter interface remains identical, ensuring easy interchangeability.

AUDI_MUL_2` is a generic, adapter-based multiplication function block for IEC 61499 applications. By eliminating events and using typed adapters, it is particularly well-suited for dataflow-oriented and loosely coupled systems. Its generic design allows it to be used with various numeric data types without requiring modification of the function block itself.

AUDI_MUL_2` is a generic, adapter-based multiplication function block for IEC 61499 applications. ---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

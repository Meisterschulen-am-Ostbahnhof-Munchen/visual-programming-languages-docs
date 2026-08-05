# AUDI_MUX_2

![AUDI_MUX_2](./AUDI_MUX_2.svg)

* * * * * * * * * *

## Introduction

The **AUDI_MUX_2** is a generic multiplexer function block (FB) according to IEC 61499. It allows the selection of one of two input values via an index (K) and forwards the selected value to the output. The FB is implemented as a generic block, so the specific data type of the values can be flexibly defined using adapters.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |

|------|-----|------------|-----------|

| REQ | Event | Set Index K | K |


The event input `REQ` triggers processing. The index passed via `K` determines which of the two input values is forwarded to the output.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

After successful selection and forwarding of the value, the event `CNF` is output.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0 or 1) |


The index `K` determines which of the two values provided via the adapter interfaces is selected:

- **K = 0** → Value from `IN1`
- **K = 1** → Value from `IN2`

### **Data Outputs**

This function block has no dedicated data outputs. Output is exclusively via the adapter `OUT`.

### **Adapter**

| Type | Direction | Identifier | Comment |

|-----|----------|------------|-----------|

| "adapter::types::unidirectional::AUDI" | Plug | OUT | Output: provides the selected value |

| "adapter::types::unidirectional::AUDI" | Socket | IN1 | Input 1: Value for K=0 |

"adapter::types::unidirectional::AUDI" | Socket | IN2 | Input 2: Value for K=1 |

All adapters are of type `adapter::types::unidirectional::AUDI`. This generic adapter defines a unidirectional data connection and can be assigned any data type in the specific project (e.g., Integer, Real, Structure). This makes the function block reusable for a wide variety of applications.

## Functionality

The function block operates according to the multiplexer principle:

1. An incoming event `REQ` triggers processing.

2. The index `K` is read. It must have the value 0 or 1.

3. Depending on `K`, the corresponding adapter socket `IN1` (K=0) or `IN2` (K=1) is activated, and its data value is transferred to plug `OUT`.

4. After successful transfer, a `CNF` event is sent.

The transfer occurs synchronously during event processing. It must be ensured that valid values are present at sockets `IN1` and `IN2` before sending `REQ`.


## Technical Features

- **Generic Function Block**: The function block is declared as a generic type (`GEN_AUDI_MUX`). This allows it to be used in various contexts with different data types without requiring a separate implementation for each type.

- **Adapter-Based Interface**: The use of adapters instead of fixed data ports enables flexible coupling with other function blocks that implement the same adapter type.

- **Index Range**: The index `K` is declared as `UINT`, but is restricted to the values 0 and 1 in the multiplexer. Values outside this range result in undefined behavior (no error handling in the function block).

- **License**: The function block is available under the Eclipse Public License 2.0 (EPL-2.0).


## State Overview

The FB does not have an explicit state machine (ECC). Its functionality is purely event-driven:

- **Waiting for REQ**: The FB waits for an event at input `REQ`.

- **Processing**: Upon receipt of `REQ`, the index is evaluated and the corresponding value is forwarded.

- **Output of CNF**: Immediately after the forwarding is complete, `CNF` is output. The FB returns to the wait state.

An internal state is not required.

## Application Scenarios

- **Selection between two measured values**: In automation technology, the FB can be used to switch between two sensor values (e.g., temperature, pressure), controlled by an operating mode.

- **Data Source Switching**: In communication systems, the function block selects between two parallel data streams, depending on a control signal.

- **Parameter Selection**: In control applications, the function block can be used to pass different sets of parameters (as structures) to a subsequent algorithm.

## Comparison with Similar Function Blocks

- **IEC 61499 Standard MUX**: The standard MUX usually works with fixed data types and more than two inputs. `AUDI_MUX_2` is specifically limited to two inputs but is implemented generically via adapters.

- **Multi-Adapter Selector**: A generic 2-to-1 multiplexer with adapters offers the same basic functionality, but often with additional states or error handling. `AUDI_MUX_2` is minimalist and suitable for simple switching tasks without side effects.


## Conclusion

The `AUDI_MUX_2` is a compact, generic multiplexer function block for selecting between two values. Its adapter-based interface makes it flexible and unconstrained on specific data types. Simple event control and a clear operating principle enable straightforward integration into IEC 61499 applications. For tasks requiring only binary selection, it represents an efficient and reusable solution.
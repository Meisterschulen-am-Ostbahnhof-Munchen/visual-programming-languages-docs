# ALR_MUL_2

![ALR_MUL_2](./ALR_MUL_2.svg)

* * * * * * * * * *

## Introduction

The function block `ALR_MUL_2` is a generic arithmetic function block designed for multiplying two values. It is based on the IEC 61499 architecture and uses adapter interfaces to encapsulate and transmit data and events. This enables clean structuring and reduces wiring effort in 4diac IDE applications, as data and associated control flows are bundled in common connections (adapters).

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Control flow is managed implicitly via the adapters used.*

### **Event Outputs**

*This function block does not have direct event outputs. Events are forwarded implicitly via the output adapter.*

### **Data Inputs**

*This function block has no direct data inputs. The input data is provided via the adapter interfaces.*

### **Data Outputs**

*This function block has no direct data outputs. The calculation result is provided via the output adapter.*

### **Adapters**

The function block communicates exclusively via adapter connections of type `ALR` (unidirectional):

- **IN1 (Socket)**:
- **Type**: `adapter::types::unidirectional::ALR`
- **Description**: First input (multiplicand 1) for multiplication.
- **IN2 (Socket)**:

**Type**: `adapter::types::unidirectional::ALR`

**Description**: Second input (multiplicand 2) for multiplication.

**OUT (Plug)**:

**Type**: `adapter::types::unidirectional::ALR`

**Description**: Output for the calculated multiplication result.

---

## Functionality

The function block `ALR_MUL_2` performs a mathematical multiplication according to the following principle:

$$ OUT = IN1 × IN2 $$

As soon as a new event is signaled at the input adapters `IN1` and/or `IN2`, indicating a data update, the function block receives the corresponding values, multiplies them, and outputs the result along with a corresponding update event via the output adapter `OUT`.

Since this is a generic function block (`GEN_ALR_MUL`), the underlying calculation adapts to the data type defined in the adapter.

---

## Technical Features

- **Generic Implementation**: The function block is classified as `GEN_ALR_MUL`. This allows for flexible use with various numeric data types defined by the adapter profile `ALR`.
- **Adapter Encapsulation**: By using unidirectional adapters, the control flow (events) is directly linked to the data flow (values). This prevents synchronization errors between data and events.
- **Compiler Package**: The function block is declared in the package `adapter::iec61131::arithmetic` and uses the core library `eclipse4diac::core::GenericClassName`.

--

## State Overview

The function block behaves like a classic, stateless (or purely functional) function block. There are no internal states that are stored beyond a single calculation cycle:

1. **Wait State**: The function block waits for an event at `IN1` or `IN2`.
2. **Calculation**: Upon arrival of an event, the values from the adapters are read and multiplied.
3. **Output**: The result is applied to `OUT`, and the output event is triggered. The function block immediately returns to the wait state.

---

## Application Scenarios

- **Signal Processing in Distributed Systems**: When sensor values are already available as adapter structures and need to be scaled or calculated together (e.g., calculating power from current and voltage).
- **Modular Control Design**: Reduction of line crossings in the function block diagram of 4diac applications by using adapters instead of separate event and data lines. * **Cascaded Calculations**: Simple chaining of multiple mathematical operations without additional overhead for event wiring.

---

## Comparison with Similar Function Blocks

- **Standard `MUL` Function Block (IEC 61131-3)**: The classic `MUL` function block uses separate event inputs (e.g., `REQ`) and data inputs (e.g., `IN1`, `IN2` as REAL/INT). `ALR_MUL_2` simplifies this by combining these channels in adapters.
- **ALR_ADD_2 / ALR_SUB_2**: These function blocks operate on the same adapter principle, but perform additions or subtractions instead of multiplications.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

`ALR_MUL_2` is a specialized, highly efficient function block for modern IEC 61499 architectures. Through its consistent use of adapters, it promotes clean, object-oriented software design in industrial automation and is ideally suited for complex, distributed control tasks.

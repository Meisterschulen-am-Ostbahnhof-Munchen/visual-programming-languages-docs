# AULI_MUL_2

![AULI_MUL_2](./AULI_MUL_2.svg)

*No image available*

* * * * * * * * * *
## Introduction

The function block `AULI_MUL_2` is used to perform an arithmetic multiplication of two values. It is a generic function block (`GEN_AULI_MUL`) whose interfaces are implemented entirely via adapters of type `AULI` (unidirectional). This allows for clean encapsulation of data and events and reduces the wiring effort within the 4diac IDE.

## Interface Structure

### **Event Inputs**

*There are no direct event inputs. Event control is handled implicitly via the adapter interfaces.*

### **Event Outputs**

*There are no direct event outputs. Event control is implicit via the adapter interfaces.*

### **Data Inputs**

*There are no direct data inputs. Data is transferred via the input adapters.*

### **Data Outputs**

*There are no direct data outputs. Data is output via the output adapter.*

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::AULI`):
* First input value (multiplicand) for multiplication.
* **IN2** (Type: `adapter::types::unidirectional::AULI`):
* Second input value (multiplier) for multiplication.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AULI`):
* Result of the multiplication ($OUT = IN1 × IN2$).

---

## Functionality

As soon as new data is signaled at the input adapters `IN1` or `IN2`, the function block performs the multiplication of the two values:

$$OUT = IN1 × IN2$

The result and the corresponding update event are then output via the output adapter `OUT`. Since this is a generic function block, the exact data type depends on the definition of the `AULI` adapter used (e.g., REAL, INT, LREAL).

---

## Technical Features

* **Generic Function Block:** The type is declared as `GEN_AULI_MUL`, which allows for flexible reusability for various numeric data types, provided they are supported by the adapter type.
* **Adapter Encapsulation:** By using unidirectional adapters (`AULI`), data and the associated trigger event are bundled in a single connection. This prevents "spaghetti code" and loose event-data pairs in the function plan.
* **Package Membership:** The function block is organized in the `adapter::iec61131::arithmetic` namespace.
* ---

## State Overview

Since this is a purely computational function block (arithmetic function), it does not have an internal state machine (ECC) in the classical sense.

1. **Waiting:** The function block waits for an update event on the adapters `IN1` or `IN2`.
2. **Calculation:** Upon receiving an event, the values from `IN1` and `IN2` are read and multiplied.
3. **Output:** The result is created on `OUT`, and the output event of the adapter is triggered. The function block immediately returns to the *Waiting* state.

---

## Application Scenarios

* **Signal Processing:** Scaling of sensor values where a measured value needs to be multiplied by a constant or dynamic factor.
* **Control Engineering:** Calculation of manipulated variables in control loops (e.g., the proportional component of a PID controller).
* **Structured Control Architectures:** Use in complex systems where adapters are used uniformly to maintain the readability of the overall system.

--

## Comparison with Similar Function Blocks

Compared to a standard multiplication function block (such as the IEC 61199 `MUL` function block), the `AULI_MUL_2` offers the following advantages and disadvantages:

| Feature | Standard `MUL` function block | `AULI_MUL_2` |
| :--- | :--- | :--- |
| **Interfaces** | Individual event and data pins | Bundled adapters (`AULI`) |
| **Wiring Effort** | High (separate event and data lines) | Minimal (only one adapter line per signal) |
| **Flexibility** | High (direct mapping of variables) | Requires the use of the `AULI` adapter type |
| **Readability** | Can become cluttered with many function blocks | Very clean and modular |

---

## Conclusion

The `AULI_MUL_2` is a specialized and modern variant of a multiplication function block for IEC 61499. Due to the consistent use of adapters, it is ideally suited for demanding, modular applications where clarity and standardization are paramount.
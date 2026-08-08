# AUS_DIV_2

![AUS_DIV_2](./AUS_DIV_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block (FB) **AUS_DIV_2** is a generic block for performing arithmetic division (DIV). It is designed for use in IEC 61499-compliant systems (such as Eclipse 4diac). The block uses unidirectional adapters of type `AUS` to receive the input data, perform the division, and forward the result via a corresponding output adapter. Encapsulating the signals in adapters significantly simplifies the wiring within the development environment.

## Interface Structure

### **Event Inputs**

There are no direct event inputs on the block interface. Event-based control and triggering of the calculation are handled internally via the connected input adapters.

### **Event Outputs**
There are no direct event outputs on the block interface. Calculation and update events are forwarded via the output adapter.

### **Data Inputs**
The block has no direct elementary data inputs. All input data is passed via the adapter interfaces.

### **Data Outputs**
The block has no direct elementary data outputs. The calculation result is provided via the output adapter.

### **Adapters**

| Type | Name | Adapter Type | Description |

| :--- | :--- | :--- | :--- |

| **Socket (Input)** | `IN1` | `adapter::types::unidirectional::AUS` | First input value for division (Dividend). |

| **Socket (Input)** | `IN2` | `adapter::types::unidirectional::AUS` | Second input value for the division (divisor). |

**Plug (Output)** | `OUT` | `adapter::types::unidirectional::AUS` | Output for the result of the division (quotient). |


## Functionality

The function block `AUS_DIV_2` performs a classic division according to the following mathematical principle:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Since it is a generic function block (identified by the attribute `GEN_AUS_DIV`), the block is not fixed to a specific data type (such as `INT` or `REAL`). The actual data type is resolved during instantiation in the 4diac IDE based on the connected adapters.


As soon as a new data event is signaled at the input adapters `IN1` or `IN2`, the function block performs the division and updates the value at the output adapter `OUT`, followed by a corresponding release event via the output plug.

## Technical Features

* **Generic Type (`GEN_AUS_DIV`):** Enables flexible reuse for different numeric data types without the need to create separate function blocks for `INT`, `REAL`, or `LREAL`.

* **Unidirectional Adapters:** Using the `adapter::types::unidirectional::AUS` type ensures clean data and event encapsulation. This reduces visual complexity in system design (less "spaghetti code" due to loosely connected event and data lines).

* **Division by Zero:** When implementing on the target platform (runtime), it is important to consider how the function block reacts to a divisor of `0` (e.g., outputting `NaN`/`INF` for floating-point numbers or a system error for integers).

## State Overview

The function block does not have a complex internal state diagram (ECC). Its execution is purely transactional:

1. **Wait State:** The function block waits for an update event at sockets `IN1` or `IN2`.

2. **Calculation:** Upon receiving an event, the values are read and divided.

3. **Output:** The result is written to the plug `OUT` and the output event is triggered. The function block immediately returns to the wait state.

## Application Scenarios

* **Measurement Scaling:** Division of sensor values by constant factors distributed across the system via adapter structures.

* **Average Calculation:** Use in mathematical computation networks within distributed control systems.

* **Ratio Control:** Calculation of ratios (e.g., air-fuel ratio in burner controls) where the input signals are already available as standardized `AUS` adapters.


## Comparison with Similar Function Blocks

Compared to a standard integer division function block (such as the IEC 61131-3 `DIV` block), `AUS_DIV_2` offers the following advantages:

* **Adapter-Based Coupling:** Standard function blocks require separate pins for data and events (REQ/CNF). `AUS_DIV_2` logically combines these in the `AUS` adapters.

* **Data Type Flexibility:** While classic function blocks are often rigidly defined for, e.g., `REAL` (e.g., `R_DIV`), this generic function block adapts to the adapter type used.


* **Adapter-Based Coupling:** Standard function blocks require separate pins for data and events (REQ/CNF). `AUS_DIV_2` logically combines these in the `AUS` adapters.

* **Data Type Flexibility:** While classic function blocks are often fixed for, e.g., `REAL` (e.g., `R_DIV`), this generic function block adapts to the adapter type used.

* ## Conclusion

The function block `AUS_DIV_2` is a highly efficient, reusable auxiliary block for arithmetic calculations in modern, adapter-based IEC 61499 architectures. It significantly improves the clarity of application diagrams by consolidating the signal and event flows for mathematical divisions in standardized adapters.
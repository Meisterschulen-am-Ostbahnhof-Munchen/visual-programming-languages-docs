# AUS_MUL_4

![AUS_MUL_4](./AUS_MUL_4.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `AUS_MUL_4` is a generic function block (Generic FB) for performing an arithmetic multiplication (`MUL`) with up to four input values. It is based on the IEC 61499 architecture and uses unidirectional adapters to transmit data and the associated control events in a clean, encapsulated manner.

Due to its generic nature (`GEN_AUS_MUL`), the function block is flexible and can be applied to various numeric data types.

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Event control is handled entirely via the connected adapters.*

### **Event Outputs**

*This function block does not have direct event outputs. Event control is handled entirely via the output adapter.*

### **Data Inputs**

*There are no direct data inputs. Data is transferred via the input adapters.*

### **Data Outputs**

*There are no direct data outputs. Data is transferred via the output adapter.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AUS`): First input value (multiplicand 1) for multiplication.
- **IN2** (Type: `adapter::types::unidirectional::AUS`): Second input value (multiplicand 2) for multiplication.
- **IN3** (Type: `adapter::types::unidirectional::AUS`): Third input value (multiplicand 3) for multiplication.
- **IN4** (Type: `adapter::types::unidirectional::AUS`): Fourth input value (multiplicand 4) for multiplication.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AUS`): The calculated product (result of the multiplication).

---

## Functionality

As soon as new data values and the corresponding trigger events are present at the input adapters (`IN1` to `IN4`), the function block performs the multiplication.

The mathematical calculation follows the formula:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3} \times \text{IN4}$$

The calculated result, along with a corresponding output event, is provided via the output adapter `OUT`. Since this is a generic function block, the actual data type (e.g., `INT`, `REAL`, `LREAL`) adapts to the instantiation in the 4diac IDE.

---

## Technical Features

- **Generic Function Block:** By defining it as `GEN_AUS_MUL`, the function block is not tied to a specific data type, which drastically increases its reusability across different projects.
- **Adapter-Based Communication:** The use of unidirectional `AUS` adapters ensures a clear application diagram, as data and event lines are bundled into a single connection. This reduces wiring errors in the development environment.

--

## State Overview

The function block behaves like a classic, stateless mathematical operator (combinatorial logic). It does not store any internal states between calculation cycles. Each update of the input values via the adapters triggers a recalculation and update of the output.

-- ---

## Application Scenarios

- **Scaling and Calibration:** Calculation of more complex physical values where multiple factors (e.g., sensor value × calibration factor × temperature compensation × unit conversion) need to be multiplied.
- **Power Calculation:** Combination of multiple measured variables in process engineering.
- **Multi-Stage Gain Control:** Cascading of gain factors in control algorithms.

--

## Comparison with Similar Components

Compared to standard multiplication components (such as the classic `MUL` of IEC 61131-3), which use separate pins for events and data, the `AUS_MUL_4` offers the following advantages:

- **Fewer Connections:** Four separate inputs and one output would require at least 10 connections (5 events, 5 data lines) in the classic model. The adapter technology reduces this to 5 adapter connections.
- **Compactness:** Cascading multiple 2x multipliers is no longer necessary, as four operands can be processed directly in a single function block.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AUS_MUL_4` is a highly efficient and modern function block for the 4diac IDE. It combines the fundamental mathematical function of multiplication with the modern structuring advantages of IEC 61499 adapters, resulting in cleaner, more maintainable, and more transparent control applications.

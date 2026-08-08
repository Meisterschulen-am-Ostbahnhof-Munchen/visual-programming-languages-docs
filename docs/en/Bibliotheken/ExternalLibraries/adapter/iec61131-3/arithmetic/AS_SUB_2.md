# AS_SUB_2

![AS_SUB_2](./AS_SUB_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `AS_SUB_2` is a generic function block (Generic FB) for the 4diac-ide development environment. It performs an arithmetic subtraction ($OUT = IN1 - IN2$).

Unlike classic arithmetic blocks that work directly with standard data and event interfaces, this block uses unidirectional adapter connections to encapsulate data and control events. This enables structured and clear wiring in complex IEC 61499 applications.

## Interface Structure

### **Event Inputs**
The function block does not have direct, independent event inputs. Event control is handled entirely via the connected adapters.


### **Event Outputs**
The function block does not have direct, independent event outputs. Events are forwarded via the output adapter.

### **Data Inputs**
No direct data inputs are defined on the function block. Input data is provided via the adapter interfaces.

### **Data Outputs**
No direct data outputs are defined on the function block. The result is passed via the output adapter.

### **Adapters**
All communication of the function block is implemented via adapters:

* **Sockets (Input Adapters):**

* `IN1` (Type: `adapter::types::unidirectional::AS`): The first input (minuend) for subtraction.

* `IN2` (Type: `adapter::types::unidirectional::AS`): The second input (subtrahend) for subtraction.

* **Plugs (Output Adapters):**

* `OUT` (Type: `adapter::types::unidirectional::AS`): The result (difference) of the arithmetic subtraction.

## Functionality
As soon as valid values and the corresponding trigger events are present at the input adapters `IN1` and `IN2`, the function block performs the calculation.


The mathematical operation is:

$$\text{Result} = \text{Value of } IN1 - \text{Value of } IN2$$

The result of the calculation and the corresponding output event are then forwarded to subsequent function blocks via the output adapter `OUT`. Since it is a generic function block (`GenericClassName="GEN_AS_SUB"`), it is flexible with respect to the underlying data types, provided these are supported by the adapter type.

## Technical Features
* **Generic Behavior:** By declaring it as a generic function block, it can be used for various numeric data types (e.g., INT, REAL, LREAL), depending on the definition of the adapter used, `adapter::types::unidirectional::AS`.


* **Compact Structure:** The use of adapters significantly reduces visual complexity in the 4diac Application Editor, as event and data lines are bundled into a single adapter connection.

**Unidirectional Data Flow:** The adapters used have a strictly unidirectional signal flow (from the sockets to the plug).

## State Overview
The execution logic is typically triggered by events on the input adapters:

1. **Idle State:** The block waits for an event on `IN1` or `IN2`.

2. **Calculation:** Upon receiving a trigger, the data is read from the adapters, and the difference is calculated.

3. **Dispatch:** The result is written to the output adapter, and the output event on `OUT` is triggered. The module returns to standby mode.

## Application Scenarios

* **Measurement Correction:** Subtraction of zero-point errors or offsets in analog sensor values.

* **Setpoint-Actual Comparison:** Calculation of the control deviation ($e = w - x$) in control loops where setpoint and actual values are transferred via standardized adapter structures.

* **Level and Quantity Calculation:** Determination of differential quantities in process plants.


## Comparison with Similar Function Blocks

Compared to a standard subtraction function block (e.g., `SUB` from the IEC 61131-3 library), which uses explicit inputs like `REQ`, `IN1`, and `IN2`, the `AS_SUB_2` offers significantly higher modularity due to its encapsulation in adapters. It is particularly suitable for advanced software architectures in IEC 61499, where data and signal flows are to be combined as logical units (interfaces).

## Conclusion
The `AS_SUB_2` is a highly efficient, reusable, and clearly structured function block for implementing subtraction tasks. Its strength lies in the consistent use of adapters, which leads to cleaner software designs and improved maintainability within the 4diac-ide.
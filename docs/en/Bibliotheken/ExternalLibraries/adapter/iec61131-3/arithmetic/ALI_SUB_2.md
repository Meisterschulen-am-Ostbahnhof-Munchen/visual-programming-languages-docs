# ALI_SUB_2

![ALI_SUB_2](./ALI_SUB_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block (FB) `ALI_SUB_2` is a generic arithmetic function block for performing a subtraction. It conforms to the IEC 61131-3 standard for standard arithmetic functions. The block uses adapter connections (`ALI` - Arithmetic Logical Interface) to receive input data and output the result of the subtraction.

## Interface Structure

### **Event Inputs**

This function block does not have direct event inputs. Control and event processing are implemented via the connected adapters.

### **Event Outputs**

This function block does not have direct event outputs. Event forwarding occurs via the output adapters.

### **Data Inputs**

There are no direct data inputs. Data transmission is encapsulated via the input adapters.

### **Data Outputs**

There are no direct data outputs. The result is provided via the output adapter.

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::ALI`): The first input (minuend) for subtraction calculation.
* **IN2** (Type: `adapter::types::unidirectional::ALI`): The second input (subtrahend) for subtraction calculation.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::ALI`): The output (difference) of the calculation ($OUT = IN1 - IN2$).

---

## Functionality

The function block `ALI_SUB_2` performs a mathematical subtraction. As soon as values are received or updated via the input adapters, the function block calculates the difference:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

The result is immediately passed to the output adapter `OUT`. Since this is a generic function block based on the internal class `GEN_ALI_SUB`, the function block can flexibly adapt to the data types defined in the adapter.

---

## Technical Features

* **Generic Implementation:** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_ALI_SUB'`. This allows for flexible handling of various data types defined by the adapter interfaces.
* **Encapsulation by Adapters:** By using unidirectional `ALI` adapters, data and the associated control events (such as update events) are bundled in a single connection. This reduces the number of visible connection lines in the 4diac application editor and improves clarity.

--

## State Overview

The function block behaves in a purely stateless and reactive manner. There is no internal state machine (Execution Control Chart - ECC). Processing is triggered directly by incoming data changes or events on the input adapters `IN1` and `IN2`.

---

## Application Scenarios

* **Signal Processing and Scaling:** Calculation of deviations, such as the difference between a setpoint and an actual value (control deviation) in control applications.
* **Offset Compensation:** Subtraction of zero-point errors or offsets from sensor data fed into the system via adapter structures.
* **Modular System Architectures:** Use in complex, distributed control systems where a structured and transparent data flow is required through the use of adapters.
* ---

## Comparison with Similar Function Blocks

Compared to the standard subtraction function block `SUB` from the IEC 61131-3 library, `ALI_SUB_2` does not require explicit wiring of data types (like `INT`, `REAL`) and control events (like `REQ` / `CNF`). While the standard `SUB` function block has discrete inputs and outputs, `ALI_SUB_2` combines these in `ALI` adapters, which significantly improves reusability and clarity in system design.

 ---

## Conclusion

The `ALI_SUB_2` is a versatile and easy-to-maintain function block for arithmetic subtraction in 4diac. Thanks to the consistent use of adapters, it integrates perfectly into service-oriented and modular control architectures and minimizes wiring effort in the development tool.
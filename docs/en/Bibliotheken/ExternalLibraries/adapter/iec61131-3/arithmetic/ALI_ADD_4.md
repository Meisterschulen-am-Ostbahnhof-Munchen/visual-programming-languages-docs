# ALI_ADD_4

![ALI_ADD_4](./ALI_ADD_4.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ALI_ADD_4` is a generic arithmetic function block according to the IEC 61131-3 standard. Its main task is to calculate the sum of four input values. Unlike classic arithmetic blocks that work with elementary data types and standard event inputs/outputs, this block uses unidirectional adapter connections of type `ALI` (Analog Line Interface). This enables encapsulated and clear signal transmission of data and the associated trigger events within the 4diac-ide.

## Interface Structure

### **Event Inputs**

*The block does not have direct event inputs. Event control is handled entirely via the connected adapters.*

### **Event Outputs**

*This function block does not have direct event outputs. Events are forwarded via the output adapter.*

### **Data Inputs**

*This function block does not have direct data inputs. Data is transferred via the input adapters (sockets).*

### **Data Outputs**

*This function block does not have direct data outputs. Data is output via the output adapter (plug).*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::ALI`): First addend for addition.
- **IN2** (Type: `adapter::types::unidirectional::ALI`): Second addend for addition.
- **IN3** (Type: `adapter::types::unidirectional::ALI`): Third addend for the addition.
- **IN4** (Type: `adapter::types::unidirectional::ALI`): Fourth addend for the addition.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::ALI`): Output of the calculated addition result.

---

## Functionality

As soon as a new event with an updated data value is received at one of the input adapters (`IN1` to `IN4`), the function block performs the mathematical addition of the four values:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

The result of the calculation is immediately passed to the output adapter `OUT`, and a corresponding output event is triggered to inform subsequent function blocks in the control flow.

--

## Technical Features

- **Generic Class:** The function block is based on the generic base class `GEN_ALI_ADD` (attribute: `eclipse4diac::core::GenericClassName`).
- **Adapter Coupling:** By using unidirectional adapters (`ALI`), data and events are bundled into a single connection. This drastically reduces the visual complexity (the "cable clutter") in the 4diac-ide Function Block Diagram (FBD) editor.
- **IEC 61131-3 Compliance:** Complies with the guidelines for standard arithmetic functions.

---

## State Overview

The `ALI_ADD_4` function block is a stateless (combinatorial) function block. It does not store any internal states or historical values between calculation cycles. Each calculation is based solely on the values currently present at the input adapters at the time of the trigger event.

---

## Application Scenarios

- **Measurement Consolidation:** Summing four analog measurements (e.g., partial load currents, flow rates, or individual power outputs) into a single total value.
- **Mixing Processes:** Calculating total weights or volumes in recipe systems where four components are combined.
- **Signal Processing:** Structured preprocessing of sensor signals in modular control architectures that consistently rely on adapter connections.

--

## Comparison with Similar Components

- **Standard ADD Component (IEC 61131-3):** A standard ADD component uses elementary data types (e.g., `REAL`, `INT`) and separate event ports (`REQ` / `CNF`). `ALI_ADD_4`, on the other hand, encapsulates these interfaces in adapters, which increases reusability and clarity.
- **ALI_ADD_2 / ALI_ADD_3:** These function blocks operate on the same principle but are designed for adding only two or three input signals, respectively.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `ALI_ADD_4` function block offers an elegant and clean way to add four analog values within an adapter-based 4diac application. By encapsulating data and event channels in `ALI` adapters, it supports the creation of modular, clear, and easily maintainable control software.

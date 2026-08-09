# AUI_ADD_2

![AUI_ADD_2](./AUI_ADD_2.svg)

*No image available*

* * * * * * * * * *
## Introduction

The function block `AUI_ADD_2` is a generic function block (Generic FB) designed to perform arithmetic addition. It uses unidirectional adapters of type `AUI` (Adapter Unidirectional Interface) to add two input values and output the result. Because it is a generic block based on the class `GEN_AUI_ADD`, it can be flexibly used for various data types supported by the corresponding adapters.

## Interface Structure

Since this function block is entirely based on adapters, it has no direct, discrete data or event channels at the top level. All communication and control are handled via the adapter interfaces.

### **Event Inputs**

*No direct event inputs available (control is handled via the connected adapters).*

### **Event Outputs**

*No direct event outputs available (forwarding is handled via the connected adapters).*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

* **Sockets (Input Adapters):**
* **IN1** (Type: `adapter::types::unidirectional::AUI`): First input (addend) for arithmetic addition.
* **IN2** (Type: `adapter::types::unidirectional::AUI`): Second input (addend) for arithmetic addition.
* **Plugs (Output Adapters):**
* **OUT** (Type: `adapter::types::unidirectional::AUI`): Output for the result of the addition (`IN1 + IN2`).

## Functionality

As soon as values are present at the input adapters `IN1` and `IN2`, or a corresponding update event is triggered via the adapters, the function block performs the addition.

The mathematical operation is:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

The result and the associated output event are immediately passed on to the subsequent function blocks via the output adapter `OUT`.

By defining it as a generic building block (`GEN_AUI_ADD`), the internal addition logic dynamically adapts to the data types of the connected adapters (e.g., integer or floating-point types).

## Technical Features

* **Generic Design:** The building block is classified as `GEN_AUI_ADD` via the attribute `eclipse4diac::core::GenericClassName`. This enables high reusability for different numeric data types.
* **Adapter Encapsulation:** The use of the unidirectional adapter `AUI` ensures a very clean design in the 4diac application editor, as event and data flows are bundled in a single connection.
* **Unidirectional Flow:** The interfaces are designed as purely unidirectional connections, which dictates a clear direction of signal and data flow from the sockets (`IN1`, `IN2`) to the plug (`OUT`).

## State Overview

The module does not have a complex internal state machine (ECC). Processing is event-driven and stateless (combinatorial) based on the triggers received via the adapters.

## Application Scenarios

* **Signal Addition:** Combining two sensor values (e.g., to calculate a total volumetric flow rate from two individual flow meters).
* **Setpoint Offset:** Applying a constant or variable correction value (offset) to an existing control parameter.
* **Structured Signal Processing:** For use in more complex control loops within IEC 61499 where a clean, adapter-based wiring style is preferred.

## Comparison with Similar Components

Compared to standard IEC 61131-3 addition components (such as a classic `ADD` component with discrete inputs), the `AUI_ADD_2` eliminates the need for separate wiring of REQ/CNF events and the actual data lines. This reduces the potential for errors when manually creating event-data associations (WITH connections).

## Conclusion

The `AUI_ADD_2` is a highly efficient, modular component for mathematical addition in modern IEC 61499 systems. Through the consistent use of adapters, he promotes a clear, error-resistant and easily maintainable application design in the 4diac IDE.
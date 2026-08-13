# AS_DIV_2

![AS_DIV_2](./AS_DIV_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block (FB) `AS_DIV_2` is a generic block for performing arithmetic division within the context of the IEC 61499 architecture. It utilizes an adapter-based data transmission concept and enables clean and structured signal processing by receiving input data via standardized adapters, calculating the division, and passing the result to an output adapter.

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Control and triggering are implicit via the connected adapters.*

### **Event Outputs**

*This function block does not have direct event outputs.*

### **Data Inputs**

*This function block does not have direct data inputs.*

### **Data Outputs**

*This function block does not have direct data outputs.*

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::AS`):
* Represents the first input value of the division (dividend).
* **IN2** (Type: `adapter::types::unidirectional::AS`):
* Represents the second input value of the division (divisor).

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AS`):
* Outputs the result of the division (quotient).

---

## Functionality

The function block `AS_DIV_2` performs a mathematical division of the passed input values. The basic formula is:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

As soon as the values at the input adapters `IN1` or `IN2` change, or a corresponding event is transmitted via the adapters, the division is performed and the result is provided via the output adapter `OUT`.

---

## Technical Features

* **Generic Block:** The attribute `GenericClassName = 'GEN_AS_DIV'` defines the block as a generic type. This allows for high flexibility when processing different numeric data types.
* **Adapter Encapsulation:** Instead of using loose data and event lines, this block exclusively uses unidirectional adapters of type `AS`. This ensures a clean and clear application diagram in the 4diac IDE.
* **Division by Zero:** During implementation and use, it is important to ensure that the divisor (`IN2`) is not equal to zero to avoid a runtime error (division by zero).
* ---

## State Overview

Since it is a purely mathematical/arithmetic function block, the `AS_DIV_2` does not have a complex internal state machine (ECC). The output values are calculated directly based on the input signals applied to the adapters.

--

## Application Scenarios

* **Measurement Scaling:** Conversion and normalization of analog sensor values (e.g., dividing a raw value to convert it into a physical unit).
* **Percentage Calculations:** Determination of ratios or percentages in industrial processes.
* **Signal Preprocessing:** Mathematical reduction of process data directly at the field level before forwarding to higher-level systems.
* ---

## Comparison with Similar Components

Compared to classic IEC 61131-3 `DIV` components, which use direct data pins, the `AS_DIV_2` offers significantly improved encapsulation through the use of adapters. The number of connection lines in the CFC (Continuous Function Chart) is significantly reduced, which improves maintainability, especially for large and complex control programs.

--

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AS_DIV_2` is a robust and versatile component for arithmetic division in distributed control systems. Its consistent use of the adapter concept supports modern, modular software design according to the IEC 61499 standard.
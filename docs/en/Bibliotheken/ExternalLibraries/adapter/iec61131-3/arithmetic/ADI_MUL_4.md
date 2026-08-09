# ADI_MUL_4

![ADI_MUL_4](./ADI_MUL_4.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `ADI_MUL_4` is a generic, adapter-based block for IEC 61499, used to perform arithmetic multiplications. It calculates the product of four input values provided via unidirectional ADI adapters (`adapter::types::unidirectional::ADI`) and outputs the result via a corresponding output adapter. By encapsulating signals in adapters, this block ensures a clearer application diagram in the 4diac IDE.

## Interface Structure

### **Event Inputs**

*This block does not have direct event inputs. Event control is encapsulated within the adapters used.*

### **Event Outputs**

*This block does not have direct event outputs. Event forwarding is encapsulated within the adapters used.*

### **Data Inputs**

*This block does not have direct data inputs. Data is transferred via the sockets.*

### **Data Outputs**

*This block does not have direct data outputs. Data is output via the plug.*

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::ADI`): First factor for multiplication.
* **IN2** (Type: `adapter::types::unidirectional::ADI`): Second factor for multiplication.
* **IN3** (Type: `adapter::types::unidirectional::ADI`): Third factor for multiplication.
* **IN4** (Type: `adapter::types::unidirectional::ADI`): Fourth factor for multiplication.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::ADI`): Result of the multiplication ($OUT = IN1 × IN2 × IN3 × IN4$).

## Functionality

As soon as new values and their corresponding events arrive at the input adapters (`IN1` to `IN4`), the function block performs the multiplication of the four values:

$$ OUT = \text{IN1} \cdot \text{IN2} \cdot \text{IN3} \cdot \text{IN4}$$

The calculated result, along with the corresponding trigger event, is forwarded via the output adapter `OUT` to the subsequent function blocks. Since this is a generic function block (`GEN_ADI_MUL`), the calculation behavior adapts to the data type defined in the adapter.

## Technical Features

* **Generic Type (`GEN_ADI_MUL`):** The function block is internally declared as a generic function block. This allows for flexible handling of various data types (e.g., `INT`, `REAL`, `LREAL`), depending on the specifications of the connected ADI adapters.
* **Encapsulation by Adapters:** Since both data and events are routed via unidirectional adapters (`ADI`), the number of visible connection lines in the 4diac IDE is drastically reduced. This improves the clarity of complex control applications.

## State Overview

The function block `ADI_MUL_4` is a **stateless** function block. It does not have an internal State Machine (ECC). Each activation by an event at the input adapters directly leads to a recalculation of the output based on the currently applied input values.

## Application Scenarios

* **Physical Calculations:** Calculation of volumes (V = l × b × h) with an additional scaling or correction factor.
* **Measurement Scaling:** Multi-level weighting or scaling of analog sensor values across multiple factors.
* **Power Calculations:** Multiplication of various electrical or mechanical parameters to determine total power or efficiency in process automation.

## Comparison with Similar Function Blocks

* **Standard `MUL` function block (IEC 61131-3):** Classic multipliers use direct data and event pins. `ADI_MUL_4`, on the other hand, uses adapters, which simplifies routing but requires a corresponding adapter infrastructure in the project. * **ADI_MUL_2 / ADI_MUL_3:** Similar function blocks with fewer inputs. The `ADI_MUL_4` is particularly suitable when exactly four factors need to be multiplied together without cascading multiple 2x multipliers.

## Conclusion

The `ADI_MUL_4` is a highly efficient auxiliary function block for mathematical signal processing in IEC 61499 systems. Through the consistent use of unidirectional adapters, it promotes clean, modular software design and reduces the complexity of graphical wiring within the 4diac IDE.
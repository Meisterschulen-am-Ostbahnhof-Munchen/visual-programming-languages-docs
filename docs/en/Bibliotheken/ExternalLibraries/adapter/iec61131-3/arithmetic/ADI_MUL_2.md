# ADI_MUL_2

![ADI_MUL_2](./ADI_MUL_2.svg)

*(No image available)*

* * * * * * * * * *
The function block `ADI_MUL_2` is a generic arithmetic multiplication block for the 4diac IDE, based on the IEC 61499 standard. It is used to multiply two input values. The unique feature of this block is the use of unidirectional adapters (`ADI`) for data transmission instead of traditional data and event connections. This enables modular and loosely coupled signal processing.



*There are no direct event inputs. Control and synchronization are implicit via the adapters used.*

*There are no direct event outputs. Event forwarding is coupled via the output adapter.*

*The function block does not have traditional data inputs. Data acquisition is handled entirely via the adapter interfaces.*

*The function block does not have traditional data outputs. Data output is handled via the output adapter.*

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
The function block uses adapters to encapsulate data and events:

* **Sockets (Input Adapters):**

* **IN1** (Type: `adapter::types::unidirectional::ADI`): First factor for multiplication (multiplicand).

* **IN2** (Type: `adapter::types::unidirectional::ADI`): Second factor for the multiplication (multiplier).

* **Plugs (Output Adapters):**

* **OUT** (Type: `adapter::types::unidirectional::ADI`): The result of the multiplication ($OUT = IN1 × IN2$).

## Functionality
As soon as valid values and the corresponding trigger events are received via the adapters `IN1` and `IN2`, the function block performs the arithmetic multiplication:

$$OUT = IN1 × IN2$

The result is immediately passed to the output adapter `OUT` and is available for subsequent function blocks. Since the function block is declared as a generic type (`GEN_ADI_MUL`), the exact data type width (e.g., INT, REAL, LREAL) is flexible and is determined during instantiation in the 4diac IDE based on the connected adapters.

* **Generic Implementation:** The `GenericClassName = 'GEN_ADI_MUL'` attribute makes the function block data type independent.

* **Adapter Encapsulation:** Using the unidirectional adapter `ADI` reduces the number of visible lines in the function block diagram because data and events are bundled and transferred in a single connection.

* **Compiler Context:** The function block is organized in the package `adapter::iec61131::arithmetic` and imports the class `eclipse4diac::core::GenericClassName`.


* ## State Overview

The function block behaves in a purely stateless (or combinatorial) manner. There is no internal state machine (ECC). Each activation of the input adapters directly leads to the calculation of the output value and the updating of the output adapter `OUT`.


* **Modular Signal Processing:** Perfectly suited for control architectures that consistently rely on adapter connections to maintain the clarity of complex function plans.

* **Scalable Calculations:** Use in mathematical computing networks within IEC 61499 applications where different numerical data types need to be multiplied.



Compared to a standard multiplication block (such as the classic `MUL` block from the IEC 61131-3 library), which uses explicit data pins (`IN1`, `IN2`, `OUT`) and events (`REQ`, `CNF`), the `ADI_MUL_2` eliminates the need for manual wiring of trigger events. This increases reusability and results in cleaner software design.

The `ADI_MUL_2` is a modern, flexible, and easy-to-wire multiplication block. Through the consistent use of unidirectional adapters, it is ideally suited for service-oriented architectures in industrial automation and facilitates the creation of cleanly structured IEC 61499 applications.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion
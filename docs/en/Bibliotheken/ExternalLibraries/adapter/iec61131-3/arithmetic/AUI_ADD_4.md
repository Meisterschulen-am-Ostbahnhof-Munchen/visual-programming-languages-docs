# AUI_ADD_4

```text
        +-----------------------------------+
        |             AUI_ADD_4             |
        +-----------------------------------+
==#==>  | [Socket] IN1          [Plug] OUT  | ==#==>
==#==>  | [Socket] IN2                      |
==#==>  | [Socket] IN3                      |
==#==>  | [Socket] IN4                      |
        +-----------------------------------+



![AUI_ADD_4](./AUI_ADD_4.svg)

* * * * * * * * * *
## Introduction

The function block `AUI_ADD_4` is a generic arithmetic block for the 4diac-IDE development environment. It is used to add up to four numerical input values, which are provided via standardized, unidirectional adapters of type `AUI` (Analog Universal Interface). The calculated sum is output via a corresponding output adapter.

By using adapters, the number of visible connections in the control diagram is minimized, resulting in a clearer and more modular application architecture.

## Interface Structure

### **Event Inputs**
The block does not have direct event inputs. Event control is handled implicitly via the integrated event channels of the input adapters (`IN1` to `IN4`).

### **Event Outputs**
This function block does not have direct event outputs. Update events are forwarded implicitly via the output adapter (`OUT`).

### **Data Inputs**
There are no direct data inputs. Data transfer is fully encapsulated within the input adapters.

### **Data Outputs**
There are no direct data outputs. Data output is encapsulated within the output adapter.


### ### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN1** (Type: `adapter::types::unidirectional::AUI`): 
First addend of the addition operation.

* **IN2** (Type: `adapter::types::unidirectional::AUI`): 
Second addend of the addition operation.

* **IN3** (Type: `adapter::types::unidirectional::AUI`): 
Third addend of the addition operation.

* **IN4** (Type: `adapter::types::unidirectional::AUI`): 
Fourth addend of the addition operation.

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AUI`): 
Output adapter that provides the mathematical result of the addition.


## Functionality

The function block operates according to the principles of IEC 61499 for data- and event-driven execution:

1. **Triggering:** As soon as a new data event is signaled at one of the input adapters (`IN1` to `IN4`), the internal calculation algorithm is called.

2. **Calculation:** The block reads the numerical values from all four connected adapters and adds them according to the following mathematical formula:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

3. **Output:** The calculated sum is written to the output adapter `OUT`, and an update event is triggered via this adapter to inform subsequent blocks of the new value.


## Technical Features

* **Generic Type (`GEN_AUI_ADD`):** Thanks to its generic definition, the function block is highly versatile. The exact data type resolution (e.g., `INT`, `REAL`, `LREAL`) is determined dynamically at runtime or during instantiation in the 4diac IDE, according to the configuration of the `AUI` adapter.

* **Adapter Encapsulation:** Using adapters instead of individual event/data pins drastically reduces visual complexity in the function block diagram ("Clean Design").

* **Unidirectional Data Flow:** The use of unidirectional adapters ensures that data and events flow strictly from inputs to outputs, preventing unintended feedback loops.


* ## State Overview

The component has a simple, event-driven execution logic (Execution Control Chart - ECC):


```text
  +--------------+          Trigger (Event an IN1..IN4)          +-------------------+
  |              | --------------------------------------------> |                   |
  |    IDLE      |                                               |   BERECHNUNG &    |
  |  (Wartend)   | <-------------------------------------------- |   AKTUALISIERUNG  |
  +--------------+             Berechnung abgeschlossen          +-------------------+

1. **IDLE (Default State):** The function block passively waits for incoming data changes at the sockets.

2. **CALCULATION:** An event at one of the inputs triggers the summation. The result is calculated, passed to `OUT`, and an output event is generated. The function block then immediately returns to the state `IDLE`.

## Application Scenarios

* **Sensor Data Fusion:** Summing up to four analog measured values (e.g., determining the total volume flow from four individual partial flows).

* **Power Calculation:** Adding the active power of four separate loads to determine the total power in an energy monitoring system.

* **Setpoint Generation:** Combining a base setpoint with up to three correction or offset values in control systems.


## Comparison with Similar Function Blocks

* **Comparison with Standard `ADD` (IEC 61131-3):** Classic `ADD` function blocks use explicit data and event pins. `AUI_ADD_4` bundles these signals in adapters, simplifying and standardizing wiring.

* **Comparison with `AUI_ADD_2`:** Adding three or four values with a dual adder would require cascading multiple function blocks. `AUI_ADD_4` saves system resources, reduces latency, and results in a cleaner application layout.

## Conclusion

The `AUI_ADD_4` is a practical utility function block for advanced control projects in the 4diac IDE. It combines the basic mathematical function of addition with the structural advantages of modern adapter connections and is ideally suited for clean, clear signal processing chains.
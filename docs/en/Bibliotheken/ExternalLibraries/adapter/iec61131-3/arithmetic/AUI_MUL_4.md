# AUI_MUL_4

![AUI_MUL_4](./AUI_MUL_4.svg)

*No image available*

* * * * * * * * * *
## Introduction
The function block `AUI_MUL_4` is a generic block for performing an arithmetic multiplication of four input values. It uses unidirectional adapters of type `AUI` (Adapter Unit Interface) to transmit data and associated events in a bundled manner. This enables clean and clear modeling in the 4diac-ide.

## Interface Structure

### **Event Inputs**
*There are no direct event inputs. Event control is handled via the adapter interfaces.*

### **Event Outputs**
*There are no direct event outputs. Event control is handled via the adapter interfaces.*

### **Data Inputs**
*There are no direct data inputs.*

### **Data Outputs**
*There are no direct data outputs.*

### **Adapters**

#### **Sockets (Inputs)**
* **IN1** (Type: `adapter::types::unidirectional::AUI`): First multiplicand.

* **IN2** (Type: `adapter::types::unidirectional::AUI`): Second multiplicand.

* **IN3** (Type: `adapter::types::unidirectional::AUI`): Third multiplicand.

* **IN4** (Type: `adapter::types::unidirectional::AUI`): Fourth multiplicand.


#### **Plugs (Outputs)**

* **OUT** (Type: `adapter::types::unidirectional::AUI`): Output for the result of the multiplication ($OUT = IN1 \cdot IN2 \cdot IN3 \cdot IN4$).

## Functionality
As soon as a new event is signaled at one of the input adapters (`IN1` to `IN4`), the function block reads the current values of the four inputs. These values are multiplied together:

$$\text{Result} = \text{Value of IN1} \cdot \text{Value of IN2} \cdot \text{Value of IN3} \cdot \text{Value of IN4}$$

The calculated result is passed to the output adapter `OUT`, and a corresponding update event is output via this plug.

## Technical Features
* **Generic Module:** The module is based on the generic class `GEN_AUI_MUL`. This allows for flexible adaptation to different data types within the adapter type used.

* **Using Adapters:** By encapsulating data and events in unidirectional adapters (`AUI`), the number of connection lines in the 4diac-ide application editor is drastically reduced, significantly improving the clarity of complex applications.

## State Overview

The function block operates purely event-driven and has no internal state that persists beyond the duration of a calculation cycle (stateless/static function block).

* **Wait State:** The function block waits for an update event at one of the sockets (`IN1` to `IN4`).

* **Calculation:** After an event arrives, the multiplication is performed.

* **Output:** The result is created at `OUT`, an event is triggered at the plug, and the function block immediately returns to the wait state.

## Application Scenarios

* **Signal Scaling:** Cascaded scaling of measured values where a raw value must be multiplied by several correction and calibration factors.


* **Signal Scaling:** * **Power Calculation:** Multiplication of various physical quantities to determine a target value (e.g., calculating total power from different factors).

* **Modular Control Concepts:** Applications where structured data transfers are implemented using standardized adapter interfaces.

## Comparison with Similar Function Blocks

* **Standard MUL Function Blocks (IEC 61131-3):** Classic multipliers work with direct elementary data types (such as `REAL` or `INT`) and require separate event inputs (`REQ`) and event outputs (`CNF`). `AUI_MUL_4` simplifies this by encapsulating the data in adapters.

* **AUI_MUL_2 / AUI_MUL_3:** Similar function blocks with fewer inputs. The function block `AUI_MUL_4` is particularly suitable when exactly four factors need to be multiplied without having to chain multiple multiplication blocks together (which saves resources and latency in the execution model).

## Conclusion
The function block `AUI_MUL_4` represents an efficient and clean solution for arithmetic multiplications of four factors within an adapter-based 4diac architecture. It promotes the modular design and clarity of the IEC 61499 application.
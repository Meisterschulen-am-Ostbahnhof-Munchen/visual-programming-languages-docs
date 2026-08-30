# AI_ADD_3

![AI_ADD_3](./AI_ADD_3.svg)

* * * * * * * * * *

## Introduction

The function block `AI_ADD_3` is a generic, arithmetic addition block for the 4diac-ide development environment. It is used to add the values of three analog inputs (AI) and output the result to an analog output. The use of unidirectional adapters ensures clean encapsulation of data and associated events.

## Interface Structure

The block uses an adapter-based interface design. It does not have direct, traditional event or data channels at the main level, but delegates these entirely to the adapters.

## **Event Inputs**

*No direct event inputs are available.* (Event control is handled via the adapter interfaces).

### **Event Outputs**

*No direct event outputs available.* (Event control is handled via the adapter interfaces).

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AI`): First analog input value for the addition operation.
- **IN2** (Type: `adapter::types::unidirectional::AI`): Second analog input value for the addition operation.
- **IN3** (Type: `adapter::types::unidirectional::AI`): Third analog input value for the addition operation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AI`): Output adapter that provides the calculated result of the addition.

---

## Functionality

As soon as an update event arrives at one of the input adapters (`IN1`, `IN2`, or `IN3`), the function block reads the analog values of the three sockets.

The following mathematical operation is performed:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

After successful calculation, the result value is passed to the output plug `OUT`, and a corresponding update event is triggered at the output.

---

## Technical Features

- **Generic Function Block (FB):** The function block is internally typed as `GEN_AI_ADD`. This allows for flexible adaptation to different numeric data types (e.g., `INT`, `REAL`, `LREAL`), depending on the specific type defined by the connected adapters.
- **Adapter Coupling:** By using unidirectional adapters (`unidirectional::AI`), signal routing in the application diagram is greatly simplified. Data and trigger events are bundled in a single connection line.
- **Adapter Coupling:** The use of unidirectional adapters (`unidirectional::AI`) greatly simplifies signal routing in the application diagram. ---

## State Overview

The function block operates purely event-driven:

1. **Standby State (Idle):** The function block waits for incoming events at sockets `IN1`, `IN2`, or `IN3`.
2. **Calculation Phase:** An event triggers the addition of the incoming values.
3. **Update Phase:** The result is applied to `OUT`, and the output event is triggered. The function block immediately returns to standby state.

--

## Application Scenarios

- **Sensor Data Fusion:** Combining and summing three analog measured values (e.g., determining a total volume flow from three individual partial flows).
- **Setpoint Calculation:** Calculation of an overall setpoint consisting of a base setpoint and two correction or offset values.
- **Mixing Processes:** Weighting and combining analog control signals in process automation.

---

## Comparison with Similar Function Blocks

Compared to classic IEC 61131-3 adders (such as `F_ADD`) or standard IEC 61499 function blocks, `AI_ADD_3` eliminates the manual and error-prone wiring of separate `REQ` and `CNF` event lines.

While standard adders typically only support two inputs, the `AI_ADD_3` eliminates the need to cascade two separate modules when adding three values, thus optimizing execution time and improving system clarity.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AI_ADD_3` is a modular and user-friendly auxiliary module for efficient analog signal processing. Its consistent use of adapters significantly reduces the visual "spaghetti wiring" in 4diac applications and contributes to a high-performance, event-driven control architecture.

# ALR_ADD_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALR_ADD_2`](ALR_ADD_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALR_ADD_2_UNGATED](./ALR_ADD_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `ALR_ADD_2_UNGATED` is a generic, arithmetic addition block for the 4diac IDE, compliant with the IEC 61131-3 standard. It is used to mathematically add two input values. The special feature of this block lies in the use of unidirectional adapters (`ALR`), which encapsulate both the data and the associated control logic to enable clean and modular signal processing.

## Interface Structure

### **Event Inputs**

*This function block does not have direct, dedicated event inputs. Event control is handled via the adapters.*

### **Event Outputs**

*This function block does not have direct, dedicated event outputs. Event control is handled via the adapters.*

### **Data Inputs**

*No direct data inputs are defined, as data transfer is handled entirely via the adapters.*

### **Data Outputs**

*No direct data outputs are defined, as the result is provided via the output adapter.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::ALR`): The first addend of the addition operation.
- **IN2** (Type: `adapter::types::unidirectional::ALR`): The second addend of the addition operation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::ALR`): The result of the addition ($OUT = IN1 + IN2$).

---

## Functionality

The `ALR_ADD_2_UNGATED` reads the values via the two input adapters `IN1` and `IN2`. As soon as a corresponding event signals via the adapters that new data is available, the function block performs the addition:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

The calculated result is then forwarded via the output adapter `OUT`, along with the corresponding output event, to subsequent function blocks. Since it is a generic function block (`GEN_ALR_ADD`), it can flexibly work with various numeric data types supported by the ALR adapter interface.

---

## Technical Features

- **Generic Type (`GEN_ALR_ADD`):** The function block is implemented in a data-type-independent manner and adapts to the data types defined in the ALR adapter.
- **Adapter Encapsulation:** By using unidirectional adapters, the number of visible connections in the 4diac IDE's control flow diagram is drastically reduced, thus improving the clarity and maintainability of the overall system.
- **Compliance:** Complies with the mathematical standards according to IEC 61131-3 for standard arithmetic functions.

- ---

## State Overview

Since the logic of this function block operates purely data- and event-driven via the adapters, the block does not have a complex internal state machine (ECC). It reacts immediately to incoming data changes/events at sockets `IN1` and `IN2` and forwards the result to plug `OUT`.

--

## Application Scenarios

- **Signal Combining:** Addition of two analog sensor values (e.g., determining a total volume flow rate from two individual flow meters).
- **Setpoint Offset Calculation:** Applying a correction offset to a base setpoint in process engineering plants.
- **Compact Programming:** Use in complex control loops where clear routing via adapters is preferred.

---

## Comparison with Similar Function Blocks

Compared to a standard `ADD` function block (which has separate event inputs like `REQ`, event outputs like `CNF`, and classic data pins), the `ALR_ADD_2_UNGATED` completely omits these classic pins. It replaces them with standardized `ALR` adapters. This significantly simplifies wiring in the 4diac IDE, as event and data are bundled in a single connection.

--

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALR_ADD_2_UNGATED` is a modern and highly efficient variant of the classic addition function block. It is ideally suited for service-oriented architectures and distributed control systems within the 4diac environment, where clarity and standardized adapter interfaces are paramount.

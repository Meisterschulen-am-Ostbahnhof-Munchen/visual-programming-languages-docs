# AI_SPLIT_5

![AI_SPLIT_5](./AI_SPLIT_5.svg)

* * * * * * * * * *
## Introduction

The function block **AI_SPLIT_5** is used to distribute an incoming analog signal (AI) to five identical outputs. It is a generic function block specifically designed for splitting an analog value into multiple parallel paths. It is implemented using unidirectional adapters of type `AI`.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No direct data inputs available. Signal transmission occurs exclusively via the adapter input.

### **Data Outputs**

No direct data outputs available. Signal transmission occurs exclusively via the adapter outputs.

### **Adapter**

| Direction | Name | Type | Description |
|----------|--------|------------------------------|-----------------------------------------------------|
| Socket | IN | `adapter::types::unidirectional::AI` | Receives the incoming analog signal. |
| Plug | OUT1 | `adapter::types::unidirectional::AI` | First output, provides the same signal as the input. |
| Plug | OUT2 | `adapter::types::unidirectional::AI` | Second output, provides the same signal as the input. |
| Plug | OUT3 | `adapter::types::unidirectional::AI` | Third output, provides the same signal as the input. |
| Plug | OUT4 | `adapter::types::unidirectional::AI` | Fourth output provides the same signal as IN. |
| Plug | OUT5 | `adapter::types::unidirectional::AI` | Fifth output provides the same signal as IN. |

## Functionality

The function block forwards the analog signal present at the adapter input *IN* unchanged to all five adapter outputs *OUT1* to *OUT5*. No signal processing or buffering takes place; the distribution is purely topological at the connection level. This makes the function block ideal for distributing a single analog signal to multiple subsequent functions or devices without requiring any duplication at the application level.

## Technical Features

- **Generic Type**: The function block is implemented as a generic function block (`GEN_AI_SPLIT`) and can be adapted to different analog signal types by assigning appropriate type codes.
- **Unidirectional Adapters**: All adapters are unidirectional, meaning data flows only from the input to the outputs.
- **No Internal State Behavior**: The function block (FB) does not have its own state model (ECC) because it operates purely combinatorially.
- **Scalability**: The function block is designed for five outputs. For other numbers, similar function blocks (e.g., AI_SPLIT_2, AI_SPLIT_3) can be used or created by adapting the generic pattern.

## State Overview

The FB does not have an explicit state diagram. Since no events are processed, the behavior is static: the signal at the input is permanently passed through to the outputs. Initialization or special behavior during commissioning is not required.

## Application Scenarios

- **Distribution of a Measured Value**: An analog sensor (e.g., temperature, pressure) provides a value that must be transmitted in parallel to several control, monitoring, or visualization components.
- **Parallel Processing**: In a control application, the same analog value is processed differently in different branches (e.g., in both a PID controller and a limit value monitor).
- **Redundancy**: The signal is sent to multiple independent evaluation units to ensure fault tolerance.

## Comparison with Similar Function Blocks

- **AI_SPLIT_2, AI_SPLIT_3, AI_SPLIT_N**: These function blocks split an analog signal to a different number of outputs. AI_SPLIT_5 is specifically optimized for five outputs.
- **Analog Splitters in Other Libraries**: Often, such functions are implemented using adapter coupling or data copiers. AI_SPLIT_5 offers a clean, reusable structure within the 4diac framework.
- **Difference to Data-Event-Based Splitters**: Since the function block does not use events, it is purely signal-flow oriented and requires no synchronization or sequence control.

**AI_SPLIT_5 is not a data-event-based splitter.**
## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AI_SPLIT_5 is a simple yet useful function block for duplicating an analog signal. Its generic nature and clear adapter interface make it an ideal building block for modular automation solutions where an analog value is needed multiple times. The lack of event-driven control reduces complexity and enables direct signal transmission without time delays.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

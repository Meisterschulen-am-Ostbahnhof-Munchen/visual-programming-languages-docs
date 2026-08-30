# A2X_SPLIT_8

![A2X_SPLIT_8](./A2X_SPLIT_8.svg)

* * * * * * * * * *
## Introduction

The A2X_SPLIT_8 function block serves as a generic building block to distribute an incoming A2X adapter (socket) to eight identical A2X adapter outputs (plugs). It is used in industrial automation when a signal is required multiple times.
## Interface Structure

### **Event Inputs**

Not present.

### **Event Outputs**

Not present.

### **Data Inputs**

Not present.

### **Data Outputs**

Not present.
### **Adapters**

The FB has the following adapter interfaces:

**Socket (Input):**

- `IN` (Type: `adapter::types::unidirectional::A2X`)

**Plugs (Outputs):**

- `OUT1` to `OUT8` (each type: `adapter::types::unidirectional::A2X`)

## Functionality

The FB forwards the data received via socket `IN` unchanged to all eight plugs `OUT1` to `OUT8`. No processing or conversion of the data takes place. The FB functions purely as a distributor (splitter) for A2X adapters.

## Technical Features

- The function block is implemented as a generic FB (GenericClassName: `GEN_A2X_SPLIT`), enabling flexible reuse in various contexts.
- There are no events or data points; all communication takes place via the A2X adapters.
- The FB is compliant with the IEC 61499-2 standard.
- The outputs are independent of each other and can be individually connected to other FBs.

## State Overview

Since the FB has neither event inputs nor an execution state, there is no state machine. The FB operates continuously without an internal state.

## Application Scenarios

- Distribution of a sensor signal (e.g., temperature, pressure) to multiple consumers or controllers.
- Parallel connection of a control signal to multiple actuators.
- Provision of a reference value for multiple control loops.

## Comparison with Similar Function Blocks

- **A2X_SPLIT_2**, **A2X_SPLIT_4**: Function blocks with fewer outputs that can be used as needed.
- **A2X_MERGE**: Combines multiple A2X inputs into one output – the opposite function.
- **A2X_SELECT**: Selects one of several A2X inputs, while the splitter operates all outputs simultaneously.

## Conclusion

The A2X_SPLIT_8 is a simple yet useful function block for multiplying A2X signals in automation projects. Its generic design and clear separation of inputs and outputs provide a clean and reusable solution.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Total resistance in series & parallel circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)

]

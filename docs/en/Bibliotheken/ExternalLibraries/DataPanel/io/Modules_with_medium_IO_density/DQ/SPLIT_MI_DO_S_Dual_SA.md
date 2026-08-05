# SPLIT_MI_DO_S_Dual_SA
![SPLIT_MI_DO_S_Dual_SA](./SPLIT_MI_DO_S_Dual_SA.svg)

* * * * * * * * * *
## Introduction
The function block **SPLIT_MI_DO_S_Dual_SA** is used to split a single data panel input of type `DataPanel_MI_DO_S_Dual_SA` into two separate outputs of type `DataPanel_MI_DO_S_Single_SA`. The drive information contained in the dual structure for forward/reverse movement (or up/down, right/left, clockwise/counterclockwise) is distributed to two independent outputs.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Service Request: The block processes the current value of the data input IN. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirmation of processing completed. Sent after the algorithm has finished executing. |

### **Data Inputs**

| Name | Type | Description |

|------|-----|--------------|

| IN | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Dual_SA` | Dual input carrying both forward (UP) and backward (DOWN) information. |

### **Data Outputs**

| Name | Type | Description |

|-------|-----|--------------|

| UP | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Single_SA` | Output for forward, upward, clockwise, or counterclockwise rotation. |

DOWN | `DataPanel::io::MI::DQ::DataPanel_MI_DO_S_Single_SA` | Output for reverse, downward, counterclockwise, or counterclockwise rotation. |

### **Adapter**
None.

## Functionality
The function block is activated by the **REQ** event. The associated algorithm performs the following assignments:

- The common control value `u8SAMember` of the dual structure is passed unchanged to both outputs (`UP.u8SAMember` and `DOWN.u8SAMember`).
- The direction information is separated: Output `UP.Port` receives the value of field `IN.Up`, and output `DOWN.Port` receives the value of field `IN.Down`.
- After the algorithm executes, the acknowledgment event **CNF** is sent.

## Technical Features
- The function block is implemented as a simple function block (SimpleFB), meaning the logic is executed within a single algorithm without a state machine.
- The data types used are from the `DataPanel::io::MI::DQ` package. They are declared as implicit imports in the function block.
- The output data is valid at the time of the **CNF** event.

## State Overview
The function block has only a single EC state, **REQ**, in which the algorithm is executed and the output event **CNF** is subsequently set. There are no other states or branches.

## Application Scenarios
- Splitting a combined drive signal for a bidirectional motor into two separate control lines (e.g., for direction control).
- Separating forward and reverse signals in a machine control system when downstream function blocks expect separate inputs for each direction of movement.
- Preparing data for two independent actuators that operate in the same mode (e.g., power level) but control different directions.

## Comparison with Similar Function Blocks
A possible alternative approach would be to use a general-purpose splitter function block that splits arbitrary compound data types. **SPLIT_MI_DO_S_Dual_SA** is specifically tailored to the aforementioned data types and directly handles the correct assignment of the direction fields, reducing the potential for errors and improving the readability of the control code.

## Conclusion

**SPLIT_MI_DO_S_Dual_SA** offers a simple and reliable way to split a dual data panel control command into two separate outputs for opposite directions of movement. Thanks to its clearly defined interface and direct processing from an event call, it is particularly well-suited for use in modular control systems where a clean separation of the direction signals is required.

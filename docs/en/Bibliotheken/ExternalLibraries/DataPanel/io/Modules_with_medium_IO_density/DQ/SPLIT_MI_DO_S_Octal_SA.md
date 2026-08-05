# SPLIT_MI_DO_S_Octal_SA
![SPLIT_MI_DO_S_Octal_SA](./SPLIT_MI_DO_S_Octal_SA.svg)
* * * * * * * * * *
## Introduction
The function block **SPLIT_MI_DO_S_Octal_SA** is used to split a single data value of type `DataPanel_MI_DO_S_Octal_SA` into eight separate outputs of type `DataPanel_MI_DO_S_Single_SA`. The common portion (`u8SAMember`) is retained unchanged, and the respective port information from the octal input is distributed to the individual outputs.
## Interface Structure
### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `REQ` | Service Request; Processing starts as soon as the event occurs. The user must first validate the data input `IN`. |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| `CNF` | Confirmation of completed processing. Indicates that all eight outputs have been updated. |

### **Data Inputs**

| Name | Type | Comment |

|------|----------------------------------|------------------------------------|

| `IN` | `DataPanel_MI_DO_S_Octal_SA` | Octal input value (Port 1…8 and common `u8SAMember`) |

### **Data Outputs**

| Name | Type | Comment |

|------|-----------------------------------|--------------------------|

| `OUT1` | `DataPanel_MI_DO_S_Single_SA` | Single Output 1 |

| `OUT2` | `DataPanel_MI_DO_S_Single_SA` | Single Output 2 |

| `OUT3` | `DataPanel_MI_DO_S_Single_SA` | Single Output 3 |

| `OUT4` | `DataPanel_MI_DO_S_Single_SA` | Single Output 4 |

| `OUT5` | `DataPanel_MI_DO_S_Single_SA` | Single Output 5 |

| `OUT6` | `DataPanel_MI_DO_S_Single_SA` | Single Output 6 |

| `OUT7` | `DataPanel_MI_DO_S_Single_SA` | Single Output 7 |

| `OUT8` | `DataPanel_MI_DO_S_Single_SA` | Single Output 8 |

### **Adapters**
No adapters available.

## Functionality
This function block implements a simple, event-driven process:

1. An incoming `REQ` event triggers the execution of the algorithm `REQ`.

### **Adapters**
No adapters available.

## Functionality

This function block implements a simple, event-driven sequence:

1. An incoming `REQ` event triggers the execution of the algorithm `REQ`.

### **Adapters**

# 2. The algorithm copies the array `u8SAMember` from the input `IN` to each of the eight outputs (`OUT1` … `OUT8`).

3. Each output also receives the corresponding port value from the octal input:

- `OUT1.Port := IN.Port1`
- `OUT2.Port := IN.Port2`
- …
- `OUT8.Port := IN.Port8`
4. Upon completion, the event `CNF` is sent, indicating that all eight outputs are valid.

## Technical Features
- The function block is implemented as a **SimpleFB** (simple function block) and operates without a state machine with multiple states – processing occurs in a single step.
- There is no concurrency or time-critical processes; the partitioning occurs synchronously with the `REQ` event.
- The types `DataPanel_MI_DO_S_Octal_SA` and `DataPanel_MI_DO_S_Single_SA` must be defined in the same data namespace (here, `DataPanel::io::MI::DQ`).

## State Overview
The function block has exactly one state, `REQ`:

- **Entry** via the `REQ` event.
- **Action**: Execution of the algorithm `REQ`.
- **Output**: Sending the `CNF` event (all outputs are carried out simultaneously).

There are no other states that indicate delay or error handling.

## Application Scenarios
- Splitting an octal data bus (e.g., a module with eight identical digital outputs) into individual logical channels.
- Interface between an octal sensor/actuator panel and a controller that processes individual outputs separately.
- Preprocessing in automation technology when a data packet contains multiple ports that need to be forwarded separately.

## Comparison with Similar Components
Comparable components exist for other data structures (e.g., `SPLIT_MI_DO_S_Octal_SA` for specific panel types). The basic mechanism—splitting a composite data type into its components—is universal but differs depending on the data field name and type.

## Conclusion

The `SPLIT_MI_DO_S_Octal_SA` is a compact and clearly structured function block for decomposing an octal data packet into eight individual signals. It facilitates the modularization of automation software by dividing complex data types into manageable units and directly inheriting the port assignment from the source structure.
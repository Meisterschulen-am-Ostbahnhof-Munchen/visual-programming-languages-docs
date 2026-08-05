# ASR_SPLIT_7
![ASR_SPLIT_7](./ASR_SPLIT_7.svg)

* * * * * * * * * *
## Introduction
The function block **ASR_SPLIT_7** is a generic function block that distributes a single ASR adapter input to seven ASR adapter outputs. It acts as a 1:7 splitter for ASR data and enables the parallel transmission of a signal to multiple downstream components.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Input (Socket) | **IN** | `adapter::types::unidirectional::ASR` | Source adapter whose data is distributed to all outputs. |

| Output (Plug) | **OUT1** | `adapter::types::unidirectional::ASR` | First output, receives the duplicated data from `IN`. |

| Output (Plug) | **OUT2** | `adapter::types::unidirectional::ASR` | Second output. |

| Output (Plug) | **OUT3** | `adapter::types::unidirectional::ASR` | Third output. |

| Output (Plug) | **OUT4** | `adapter::types::unidirectional::ASR` | Fourth output. |

Output (Plug) | **OUT5** | `adapter::types::unidirectional::ASR` | Fifth output. |

Output (Plug) | **OUT6** | `adapter::types::unidirectional::ASR` | Sixth output. |

Output (Plug) | **OUT7** | `adapter::types::unidirectional::ASR` | Seventh output. |

## Functionality

The module receives an ASR signal via socket `IN`. This signal is internally duplicated to all seven plugs (`OUT1` … `OUT7`) and forwarded without modification. No data manipulation or filtering takes place – the incoming signal is copied one-to-one to each output.

## Technical Features
- **Generic Type**: The function block is declared as a generic block with the class name `GEN_ASR_SPLIT`. This allows it to be used in various contexts where an ASR splitter is required.
- **Pure Adapter Interface**: Only adapters (no events or data inputs/outputs) are used. Communication takes place via the unidirectional ASR adapter protocol.
- **No Internal State**: The block has no state management; signal distribution is continuous and instantaneous.

## State Overview

The block has no explicit states. Its functionality is limited to the static duplication of the input signal.

## Application Scenarios
- **Signal Distribution**: An ASR signal (e.g., a control command or a configuration message) is to be sent to multiple independent receivers.
- **Parallel Processing**: In an automated control system, information must reach multiple subsystems simultaneously, each designed for the ASR protocol.
- **Test Environments**: A test adapter is connected to `IN`, and the outputs are connected to various monitoring or logging modules.

## Comparison with Similar Modules

Other splitter modules exist, such as `ASR_SPLIT_2`, `ASR_SPLIT_4`, and `ASR_SPLIT_n`, which distribute the input signal to 2, 4, and `n` outputs, respectively. `ASR_SPLIT_7` represents a specific variant with seven outputs. All of them share the common feature of duplicating the incoming ASR signal without modification.

## Conclusion

The `ASR_SPLIT_7` is a simple yet useful component for distributing an ASR signal across seven parallel paths. Its generic definition and the absence of events or states make it flexible and robust in operation.

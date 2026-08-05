# ASR_SPLIT_5

![ASR_SPLIT_5](./ASR_SPLIT_5.svg)

* * * * * * * * * *

## Introduction

The function block **ASR_SPLIT_5** is used to split a single unidirectional ASR adapter (Agricultural Standardized Interface) into five identical ASR outputs. It is designed as a generic module, thus enabling the simple distribution of an ASR signal to multiple downstream components or controllers.

## Interface Structure

The module does not have any traditional event or data inputs/outputs. All communication takes place via adapter interfaces of type `adapter::types::unidirectional::ASR`.

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapter**

| Name | Type | Direction |

|-------------|----------------------------|----------|

| `IN` | `adapter::types::unidirectional::ASR` | Socket (Input) |

| `OUT1` | `adapter::types::unidirectional::ASR` | Plug (Output) |

| `OUT2` | `adapter::types::unidirectional::ASR` | Plug (Output) |

| `OUT3` | `adapter::types::unidirectional::ASR` | Plug (Output) |

| `OUT4` | `adapter::types::unidirectional::ASR` | Plug (Output) |

| `OUT5` | `adapter::types::unidirectional::ASR` | Plug (Output) |

## Functionality

This component is a simple multiplexer at the adapter level. The ASR signal present at socket `IN` is passed through unchanged and without delay to all five output plugs (`OUT1` … `OUT5`). Thus, each connected receiver receives the identical signal from the input adapter. No active signal processing or conditioning takes place.

## Technical Features

- **Generic Type**: The component is implemented as a generic function block (`GEN_ASR_SPLIT`) and can be automatically adapted to the specific data types of the ASR adapter used.

- **Unidirectional Communication**: All adapters are unidirectional (`adapter::types::unidirectional::ASR`), meaning data flows only from the input to the outputs; feedback is not provided.

- **No State Logic**: Since no events or algorithms are present, the module does not have an ECC state diagram and operates exclusively in a data flow-oriented manner.

## State Overview

The functional block has no internal state machine. It behaves like a passive signal distributor and does not require state control.

## Application Scenarios

- **Signal Distribution**: An ASR signal (e.g., sensor data, control commands) must be simultaneously transmitted to multiple consumers (e.g., multiple actuators or higher-level controllers).

- **Test and Simulation Environments**: Parallel injection of a test signal into multiple independent system paths.

- **Redundancy**: Supplying multiple identical control units with the same input information.


## Comparison with Similar Function Blocks

- **ASR_SPLIT_2 / ASR_SPLIT_3 / ASR_SPLIT_4**: These function blocks split an ASR signal into two, three, or four outputs, respectively – the appropriate number can be selected as needed.

- **ASR_MERGE**: Unlike a splitter, a MERGE combines multiple ASR inputs into a single output.

## Conclusion

The **ASR_SPLIT_5** is a simple yet useful routing function block for multiplying a unidirectional ASR adapter. Thanks to its generic implementation and pure adapter interface, it integrates seamlessly into IEC 61499 applications and facilitates structured signal distribution in complex automation systems.
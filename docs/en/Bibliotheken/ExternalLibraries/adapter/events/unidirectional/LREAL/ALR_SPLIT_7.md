# ALR_SPLIT_7
![ALR_SPLIT_7](./ALR_SPLIT_7.svg)
*(No image available)*

* * * * * * * * * *
## Introduction
The function block `ALR_SPLIT_7` is used to split an incoming ALR (Agricultural Logic Resource) signal into seven identical output signals. It is designed as a generic block and enables the parallel distribution of an alarm or control signal to up to seven downstream components or subsystems.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| IN | `adapter::types::unidirectional::ALR` | Socket (Input) | Incoming ALR signal, which is distributed to the outputs. |

| OUT1 | `adapter::types::unidirectional::ALR` | Plug (Output) | First output of the split signal. |

| OUT2 | `adapter::types::unidirectional::ALR` | Plug (Output) | Second output of the split signal. |

| OUT3 | `adapter::types::unidirectional::ALR` | Plug (Output) | Third output of the split signal. |

| OUT4 | `adapter::types::unidirectional::ALR` | Plug (Output) | Fourth output of the split signal. |

| OUT5 | `adapter::types::unidirectional::ALR` | Plug (Output) | Fifth output of the split signal. |

OUT6 | `adapter::types::unidirectional::ALR` | Plug (Output) | Sixth output of the split signal. |

OUT7 | `adapter::types::unidirectional::ALR` | Plug (Output) | Seventh output of the split signal. |

## Functionality

The `ALR_SPLIT_7` module forwards the ALR signal present at its socket `IN` unchanged to all seven plugs (`OUT1` to `OUT7`). No transformation, delay, or filtering of the signal takes place. The module functions purely as a splitter for a unidirectional ALR data stream.

## Technical Features
- **Generic FB:** The function block is implemented as a generic function block (`GenericClassName = 'GEN_ALR_SPLIT'`) and can be parameterized or instantiated depending on the application.
- **Unidirectional:** All adapters are of type `adapter::types::unidirectional::ALR`, meaning data flows in only one direction – from the input to the outputs.
- **No Event Control:** The function block has no event inputs or outputs; signal transmission is continuous (data-driven).

## State Overview

The function block does not have an internal state machine. There are no states in the sense of an ECC (Execution Control Chart). It operates purely combinationally and always outputs the input signal to all outputs.

## Application Scenarios
- **Distributing an Alarm to Multiple Units:** A central alarm signal (e.g., a fault) is to be forwarded to seven different controllers or display elements.
- **Parallel Processing:** An ALR signal is required to trigger or monitor multiple independent subsystems simultaneously.
- **Redundancy and Testing:** The signal is sent to multiple test or logging components without interfering with each other.

## Comparison with Similar Components

| Component | Number of Outputs | Special Feature |

|----------|------------------|--------------|

| `ALR_SPLIT_2` | 2 | Simple Dual Distribution |

| `ALR_SPLIT_4` | 4 | Quad Distribution |

| `ALR_SPLIT_7` | 7 | Seven-Way Distribution (this module) |

| `ALR_SPLIT_N` (generic) | Configurable | Flexible splitter with adjustable number of paths |

All variations are based on the same principle: unidirectional distribution without signal modification.

## Conclusion

The `ALR_SPLIT_7` is a simple yet useful function block for splitting a single ALR signal into seven parallel paths. Its generic implementation allows it to be used in various industrial or agricultural automation scenarios where a signal is needed multiple times. It does not offer complex logic but reliably fulfills its function as a passive splitter.

# ALR_SPLIT_8

![ALR_SPLIT_8](./ALR_SPLIT_8.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_SPLIT_8** is used to split a single ALR signal (via a socket) into eight identical ALR outputs (plugs). This block is designed as a generic function block and enables signal distribution within an IEC 61499-based controller.

## Interface Structure
### **Event Inputs**
None

### **Event Outputs**
None

### **Data Inputs**
None

#### **Data Outputs**
None

#### **Adapter**

| Name | Type | Direction | Description |

|-------------|-----|-----------|--------------|

| **IN** | `adapter::types::unidirectional::ALR` | Socket | Input signal that is routed to all outputs |

**OUT1** | `adapter::types::unidirectional::ALR` | Plug | Output 1 – duplicated signal |

**OUT2** | `adapter::types::unidirectional::ALR` | Plug | Output 2 – duplicated signal |

**OUT3** | `adapter::types::unidirectional::ALR` | Plug | Output 3 – duplicated signal |

**OUT4** | `adapter::types::unidirectional::ALR` | Plug | Output 4 – duplicated signal |

**OUT5** | `adapter::types::unidirectional::ALR` | Plug | Output 5 – duplicated signal |

**OUT6** | `adapter::types::unidirectional::ALR` | Plug | Output 6 – Duplicated Signal |

| **OUT7** | `adapter::types::unidirectional::ALR` | Plug | Output 7 – Duplicated Signal |

| **OUT8** | `adapter::types::unidirectional::ALR` | Plug | Output 8 – Duplicated Signal |

## Functionality
The function block forwards the ALR signal received via socket **IN** unchanged to all eight output adapters **OUT1** to **OUT8**. No data processing or time delay occurs – the signals are passed through directly. This allows multiple subsequent function blocks to be supplied with the same signal in parallel.

## Technical Features

- **Generic Type:** The function block is implemented as a generic function block (`GenericClassName = 'GEN_ALR_SPLIT'`), so the underlying ALR type can be specified during instantiation.


## - **Pure Signal Distribution:** No states, no data conversion, and no inherent timing behavior – the function block operates purely passively.

- **Adapter-Based:** All communication occurs via adapters, ensuring loose coupling and easy reuse.

## State Overview
The function block has no events and no internal state machine. Execution is strictly data flow-driven: If the signal at the input changes, it is immediately propagated to all outputs.

## Application Scenarios

- **Signal Splitting** in control architectures when an ALR signal is needed multiple times (e.g., for parallel evaluations or redundancy).

- **Interconnecting multiple subsystems** with identical control data, without multiple signal generation.

- **Test setups** for simultaneously stimulating multiple receivers with the same value.

## Comparison with Similar Function Blocks
Other splitter function blocks (e.g., SPLIT_4 or SPLIT_16) differ only in the number of outputs. The ALR_SPLIT_8 is specifically designed for the ALR adapter type, while generic splitters (e.g., ANY_SPLIT) can be used for any data type. This component provides an optimized, type-safe solution for ALR distribution applications.

## Conclusion
The **ALR_SPLIT_8** is a simple yet effective functional block for multiplying an ALR signal to eight outputs. Its generic nature, adapter-based interface, and passive operation make it a robust and flexible component for IEC 61499 applications.
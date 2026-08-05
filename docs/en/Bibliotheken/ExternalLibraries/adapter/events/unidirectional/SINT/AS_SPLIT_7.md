# AS_SPLIT_7
![AS_SPLIT_7](./AS_SPLIT_7.svg)

* * * * * * * * * *
## Introduction
The function block **AS_SPLIT_7** is used to distribute an incoming unidirectional AS signal (e.g., an analog or binary automation signal) to seven identical outputs. The block is implemented as a generic FB and is frequently used in automation technology to provide a signal to multiple subsequent consumers or process steps.
## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None (Signal transmission occurs exclusively via adapters.)

### **Data Outputs**

None

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| IN | `adapter::types::unidirectional::AS` | Socket | Receives the AS signal to be distributed. |

| OUT1 | `adapter::types::unidirectional::AS` | Plug | First output – same signal as the input. |

| OUT2 | `adapter::types::unidirectional::AS` | Plug | Second output – same signal as the input. |

| OUT3 | `adapter::types::unidirectional::AS` | Plug | Third output – same signal as the input. |

| OUT4 | `adapter::types::unidirectional::AS` | Plug | Fourth output – same signal as the input. |

| OUT5 | `adapter::types::unidirectional::AS` | Plug | Fifth output – same signal as the input. |

OUT6 | `adapter::types::unidirectional::AS` | Plug | Sixth output – same signal as the input. |

OUT7 | `adapter::types::unidirectional::AS` | Plug | Seventh output – same signal as the input. |

## Functionality

The function block forwards the AS signal present at socket `IN` unchanged to all seven plug outputs. No signal conditioning, amplification, or processing takes place. The function block operates purely passively and without any time delay – as soon as a signal is present at the input, it is available at all outputs simultaneously.

## Technical Features

- **Generic Function Block:** The function block is implemented as a generic type (`GEN_AS_SPLIT`) and can be used in various contexts by configuring its parameters.
- **Adapter-Based Interface:** Communication occurs exclusively via unidirectional adapters of type `adapter::types::unidirectional::AS`. This makes the function block particularly suitable for modular architectures where signals are exchanged via clearly defined interfaces.
- **No State Logic:** The function block has no internal states, events, or processing logic – distribution is purely combinatorial.
- **Easy Extensibility:** Due to the generic nature of the function block, analog splitter variants (e.g., `AS_SPLIT_2`, `AS_SPLIT_4`) can be easily derived or created by adjusting the parameters.

## State Overview

The **AS_SPLIT_7** has no state machines, as it operates purely passively. There are no start, stop, or error states. Its behavior is determined solely by the current value of the input signal at all times.

## Application Scenarios
- **Signal Distribution in Control Systems:** An analog measurement signal (e.g., pressure, temperature) is distributed to multiple displays, controllers, or data loggers.
- **Parallel Connection of Actuators:** A control signal (e.g., 0-10V) is intended to control multiple actuators simultaneously.
- **Redundant Signal Paths:** The same signal is provided to multiple independent processing units to create redundancy.
- **Test and Simulation Environments:** A generated test signal is distributed across multiple simulation components.

## Comparison with Similar Function Blocks

The **AS_SPLIT_7** belongs to a family of splitter function blocks that differ only in the number of outputs (e.g., `AS_SPLIT_2`, `AS_SPLIT_3`, ..., `AS_SPLIT_N`). Compared to manual wiring, the function block offers the advantages of reusability, clear interface definition, and easy parameterization. Unlike active signal distributors (e.g., with amplification), the function block has no effect on the signal and is therefore ideal for passive applications.

## Conclusion

The **AS_SPLIT_7** is a simple yet useful function block for passively distributing a unidirectional AS signal to seven outputs. Thanks to its generic implementation and adapter interface, it integrates seamlessly into modern, component-based automation solutions. For applications requiring simple signal multiplication without processing, it offers a reliable and easy-to-understand solution.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Total resistance in series & parallel circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)

]

# iSTATES

![iSTATES](./iSTATES.svg)

* * * * * * * * * *

## Introduction

The **iSTATES** block is a special GlobalConstants block in the 4diac IDE. It defines a set of named constants that represent the possible states of a (slider) actuator. The constants are stored as `USINT` values and enable a uniform, human-readable reference to the states in the control logic.

## Interface Structure

### **Event Inputs**

None. The block has no event inputs.

### **Event Outputs**

None. The block has no event outputs.

### **Data Inputs**

None. The block has no data inputs.

### **Data Outputs**

None. The function block has no data outputs. The defined constants are available as globally accessible symbols within the project context.

### **Adapter**

None.

## Functionality

The **iSTATES** function block provides five symbolic constants that can be used throughout the application. Each constant represents a discrete state of a slider or similar actuator. The values are defined as `USINT` (unsigned short integer) and are assigned as follows:

| Constant | Value (USINT) | Meaning |

|------------|---------------|------------------|

| Unknown | 0 | Unknown state |

| Closed | 1 | Closed |

| Opening | 2 | Opens |

| Opened | 3 | Opened |

| Closing | 4 | Closes |

These values can be used directly in FB networks for initializing variables or for comparison with status feedback.

## Technical Features

- **Type: GlobalConstants** – The function block is not instantiated but integrated into the project as a global constant definition.

- **Value Range**: All states are declared as `USINT`, which guarantees low memory usage and compatibility with many fieldbus protocols.

- **Extensibility**: The scheme can easily be extended with additional states if the application requires it.

- **Package**: The function block is organized in the package `logiBUS::utils::sequence::schieber::const`, which allows for clear structuring within the project.

## State Overview

The five states cover a complete lifecycle of a slider:

1. **Unknown** (0) – Initial state or error state if the current position is unknown.

2. **Closed** (1) – Slide is closed (end position closed).

3. **Opening** (2) – Slide is in the opening phase.

4. **Opened** (3) – Slide is fully open (end position open).

5. **Closing** (4) – Slide is in the closing phase.

## Application Scenarios

- **State Function Blocks for Slides, Valves, or Gates** – This function block provides the basis for state management in sequential controllers.

- **Visualization** – The symbolic names can be used in HMI or SCADA systems to display the current state.

- **Fault Detection** – The `Unknown` state allows for the unambiguous identification of invalid or initial states.


## Comparison with Similar Blocks

Similar GlobalConstants blocks often exist in other packages (e.g., for motor controllers, conveyor systems). The difference lies in the specific definition of the states – while other blocks use `Idle`, `Running`, `Error`, etc., **iSTATES** is specifically tailored to the five typical slider states. Using `USINT` instead of `BOOL` or `INT` is platform-efficient and standards-compliant.

## Conclusion

The **iSTATES** block is a simple yet useful tool for the consistent definition of slider states. Using global constants makes the code more readable, fault-resistant, and maintainable. It is ideally suited for all applications where an actuator cycles through the state sequence "Closed → Opens → Open → Closes → Closed".

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
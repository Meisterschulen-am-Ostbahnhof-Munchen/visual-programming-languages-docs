# SET_DATE
![SET_DATE](./SET_DATE.svg)

* * * * * * * * * *
## Introduction
The **SET_DATE** function block is used to write a date value (data type `DATE`) from an input to an InOut variable. The InOut variable is written directly and is available with the new value after execution. This enables efficient transfer of date values without an additional output variable.
## Interface Structure
### **Event Inputs**

| Event | Description | With Variables |

|----------|---------------|---------------|

| REQ | Normal Execution Request | IN, OUT |

### **Event Outputs**

| Event | Description | With Variables |

|----------|--------------|---------------|

| CNF | Execution Confirmation | OUT |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| IN | DATE | Value to be written to the target variable |

| OUT | DATE | Target variable (InOut) – initial value can be read but will be overwritten |

### **Data Outputs**

| Variable | Type | Description |

|----------|-------|--------------|

| OUT | DATE | Target variable (InOut) – contains the value of IN after execution |

### **Adapter**
None.

## Functionality
When the **REQ** event is triggered, the function block executes the algorithm `REQ`:

- The value of the input `IN` is assigned to the InOut variable `OUT` (`OUT := IN;`).
- The **CNF** event is then sent to signal successful completion.

The InOut variable `OUT` serves as both an input and an output. The current value can be read before execution, and the new value is available after execution.

## Technical Features
- **InOut Variable:** The function block uses an InOut variable that is referenced directly in the calling environment. Changes take effect immediately on the connected variable without any additional data output.
- **Data Type:** Designed exclusively for the data type `DATE`.
- **Simple State Logic:** The function block consists of only one state, which directly performs the assignment.

## State Overview

| State | Description |

|---------|---------------|

| REQ | Executes the value assignment `OUT := IN` and sends CNF |

No other state exists; the function block is immediately ready for execution.

## Application Scenarios
- Setting a date value in a PLC controller, e.g., initializing a current date.
- Transferring a calculated or parent date to a global or parent variable.
- Switching between different date values by repeated calls with different `IN` values.

## Comparison with similar function blocks
Similar function blocks exist for other data types:

- **SET_TIME** (for `TIME`)
- **SET_DT** (for `DATE_AND_TIME`)

The main difference lies in the data type used. The functionality and the InOut interface are identical.

## Conclusion

**SET_DATE** is a simple yet useful function block for directly setting a date variable. By using an InOut variable, memory and communication overhead are kept to a minimum. The function block is particularly suitable for standardization tasks in automation technology where date values need to be transferred efficiently and reliably.

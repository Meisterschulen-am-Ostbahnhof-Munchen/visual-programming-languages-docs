# SET_DWORD
![SET_DWORD](./SET_DWORD.svg)
* * * * * * * * * *
## Introduction
The function block `SET_DWORD` is used to write a DWORD value to a target variable declared as InOut via an input. It provides a simple and efficient way to set values during operation without requiring a separate assignment in the program.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|---------|

| REQ | Event | Normal Execution Request – triggers the write operation |

The event `REQ` simultaneously provides the data `IN` and `OUT`.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|---------|

| CNF | Event | Execution Confirmation – sent after successful execution |

The output `CNF` references the modified variable `OUT`.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|---------|

| IN | DWORD | Value to be written to the target variable (initial value: 0) |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|---------|

| OUT | DWORD | Target variable (InOut) – the value of `IN` is written here (initial value: 0) |

**Note:** `OUT` is declared as an InOut variable, meaning it can be referenced externally and its memory location is directly modified by the function block. It appears in the function block network as both an output and an input.

### **Adapters**
No adapters available.

## Functionality
The function block has a single action that is executed when the event `REQ` occurs:

```structured text
OUT := IN;

The event `CNF` is then sent. The function block is stateless and executes the assignment on every `REQ` event, regardless of the current value.

## Technical Features
- **InOut Variable**: Using an InOut variable allows direct access to the memory location of an external variable. This reduces data copying overhead and enables the modification of variables that are also used elsewhere in the system.
- **No State Logic**: The function block does not implement a state machine with multiple states – it always reacts the same way to the input event.
- **Initial Values**: Both variables are initially set to 0, but are usually overwritten at runtime.

## State Overview

The function block consists of a simple state machine with exactly one state:

| State | Triggering Event | Action | Output |

|---------|----------------------|--------|---------|

| `REQ` | `REQ` | `OUT := IN;` | `CNF` |

There are no wait states or branches.

## Application Scenarios
- **Peripheral Configuration**: Setting a DWORD register in a module (e.g., time base, threshold).
- **Parameter Passing**: Passing a constant or calculated value to a globally available variable (e.g., via an InOut data type).
- **Testing and Debugging**: Temporarily overwriting a value during operation without modifying the source code.
- **Plain Text Assignment Migration**: Replacing a simple `OUT := IN` instruction in an IEC 61499 network with a reusable function block.

## Comparison with Similar Function Blocks
- **MOVE / MV**: Available in many libraries, but usually work with simple input/output variables and require explicit buffering. `SET_DWORD`, on the other hand, directly accesses an existing variable (InOut).
- **SET_BOOL / SET_INT / SET_REAL**: Analogous function blocks for other data types; the principle is identical, only the data type varies.
- **WRITE_DWORD**: Some libraries offer a function block that writes via an address bus. `SET_DWORD` is simpler and does not require address logic.

## Conclusion

`SET_DWORD` is a minimal but very useful function block for directly assigning values to a DWORD InOut variable. Its simplicity makes it error-resistant, and the absence of state logic ensures predictable real-time behavior. It is particularly suitable for configuration and initialization tasks where fast, straightforward value assignment is required.
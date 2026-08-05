# SET_LINT
![SET_LINT](./SET_LINT.svg)

* * * * * * * * * *
## Introduction
The function block **SET_LINT** is used to write a value of type `LINT` (64-bit integer) from a data input to a variable declared as an InOut parameter. It is typically used to explicitly set the value of a variable defined outside the block. The block complies with the IEC 61499-1 standard and provides simple, event-driven write access.
## Interface Structure
### **Event Inputs**

| Name | Type | Description | With Variables |

|------|-------|---------------------------------------|----------------|

| REQ | Event | Triggers Write Operation | IN, OUT |

### **Event Outputs**

| Name | Type | Description | With Variables |

|------|-------|---------------------------------------|----------------|

| CNF | Event | Confirmation after successful write | OUT |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|------|--------------|-----------------------------|

| IN | LINT | 0 | The value to be written |

### **Data Outputs**

This function block does not have traditional data outputs, but rather an **InOut parameter** `OUT`, which functions as both an input and an output. This parameter is the target memory location for the value of `IN`.

### **Adapter**
None.

## Functionality
The behavior of the function block is reduced to a single step:

1. An event at the **REQ** input triggers the internal processing.

2. The algorithm executes the assignment `OUT := IN`. This copies the value of the data input `IN` to the InOut variable `OUT`.

3. After the assignment is complete, the **CNF** event is sent to signal successful execution.

The InOut variable `OUT` must be bound to a memory location (e.g., a global or device-specific variable) in the application. The function block overwrites the value stored there with the value of `IN`.

## Technical Features
- The function block uses an **InOut parameter** instead of a separate data output. This allows direct writing to an external variable without requiring additional wiring via a data output.
- The data type `LINT` (64-bit signed integer) is platform-dependent; the implementation requires that the target system supports this type.
- There is no error handling or range checking – the assignment always occurs as soon as `REQ` is triggered.
- The function block is a **SimpleFB** with only one ECR state; therefore, its behavior is deterministic and fast.

## State Overview
The function block has only one state, `REQ`. After the algorithm executes, it automatically returns to its initial state (implicitly). A state machine in the classical sense does not exist – the function block is stateless. Exactly one write operation is performed after each ``REQ`` event.

## Application Scenarios
- **Initializing LINT Variables**: Setting a global configuration variable to a defined initial value.
- **Changing Control Parameters**: Dynamically overriding a parameter (e.g., setpoint or limit value) by a higher-level function block.
- **Test and Debug Interfaces**: Enables manual setting of variables at runtime via an HMI or script.
- **Message Header/Payload Setting**: In communication, `IN` can contain the value of a message, which is written to a buffer (`OUT`).

## Comparison with Similar Function Blocks
- **SET_DINT / SET_INT**: Analogous function blocks for `DINT` (32-bit) and `INT` (16-bit), respectively. The only difference is the data type.
- **MOVE**: A more general function block for copying arbitrary values, often also with InOut parameters. `SET_LINT` is specialized for `LINT` and offers no further data or event inputs.
- **WRITE_LINT (hypothetical)**: A function block that explicitly writes an address via a pointer. `SET_LINT` operates without addressing and expects a directly linked variable.

## Conclusion
SET_LINT` is a minimalist function block that reliably performs a single task: assigning a `LINT` value to an InOut variable. Due to its simplicity, it is particularly suitable for performance-critical or manageable control tasks where no complex logic is required. The absence of error handling makes it transparent and predictable, but requires the user to correctly link the InOut variable.

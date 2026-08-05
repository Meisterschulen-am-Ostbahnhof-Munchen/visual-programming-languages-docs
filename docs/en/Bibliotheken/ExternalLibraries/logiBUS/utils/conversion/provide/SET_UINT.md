# SET_UINT

![SET_UINT](./SET_UINT.svg)

* * * * * * * * * *
## Introduction
The SET_UINT function block is used to write a UINT value, which is present at a data input, into a variable declared as an InOut parameter. This simple but fundamental operation allows data to be copied from the FB context into an external or referenced variable.

## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-------|----------------------------|

| REQ | Event | Normal Execution Command |

### **Event Outputs**

| Name | Type | Description |

|------|-------|--------------------------------|

| CNF | Event | Execution Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|------|--------------|-----------------------------|

| IN | UINT | 0 | Value to be written |

### **Data Outputs**
*No separate outputs available.* The target value is provided via the InOut variable `OUT`.

### **Adapters**
*No adapters.*

## Operation
Processing occurs in one step:

1. An event at the input `REQ` triggers the execution of the algorithm.

2. The algorithm copies the value of the data input `IN` to the InOut variable `OUT`.

3. Upon completion, the event `CNF` is output.

The InOut variable `OUT` is interpreted as a referenced variable – the function block writes directly to the memory location connected to the `OUT` interface during the call.

## Technical Features
- **InOut Variable as Target:** The function block uses an InOut variable (`OUT`) instead of a simple output. This allows the function block to directly access and overwrite an existing variable in call environments (e.g., within resources or other function blocks).

- **Single-line algorithm:** The assignment `OUT := IN` is performed in a single ST instruction; no further calculations or intermediate storage are carried out.

- **No state machines:** The function block (FB) has only one entry state (`REQ`); state changes or loops are not implemented.

## State overview

| State | Action | Output |

|---------|--------|---------|

| REQ | `OUT := IN` | CNF |

After execution, the FB remains in an implicit end state; it is ready for each new request `REQ`.


## Application Scenarios

- **Setting a Configuration Value:** A setpoint or parameter (e.g., a threshold in a control block) is input externally and written to the corresponding internal variable.

- **Copying UINT Data to a Central Memory Location:** In a controller, `SET_UINT` can be used to transfer measured values or calculation results to a global data block.

- **Exchanging Data Between Function Blocks:** Two different function blocks can access the same variable via the InOut variable – the `SET_UINT` function block is used for targeted overwriting.

## Comparison with Similar Function Blocks

- **SET_BOOL / SET_INT / SET_*:** These function blocks differ only in the data type used. Their functionality – "writing the value from IN to OUT" – is identical.

- **MOVE (e.g., `MOVE` in IEC 61131-3):** A general copy function, which is usually implemented as a standard function (without its own event interface). The `SET_UINT` function block provides explicit event control for its execution.

- **Special Case InOut:** Unlike pure output blocks, `SET_UINT` allows direct access to the target variable, which offers advantages when passing data across hierarchy boundaries.

## Conclusion
The `SET_UINT` function block is a minimal but useful block for writing a UINT value to a referenced variable. Its simple structure—an event triggers an assignment—makes it particularly useful in environments where explicitly "setting" a variable via an event is required. If it does not meet any further conditions, it is suitable as a template for similar data type-specific set functions.
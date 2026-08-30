# GET_DINT

![GET_DINT](./GET_DINT.svg)

* * * * * * * * * *
## Introduction

The function block **GET_DINT** reads a DINT value from an InOut variable and provides it as a buffered output value. The variable itself is not modified; the block serves purely as a read and buffer block.
## Interface Structure

### **Event Inputs**

- **REQ** – Normal execution command (activates reading the InOut variable).

### **Event Outputs**

- **CNF** – Confirmation of execution (sent after successful value transfer).

### **Data Inputs**

There are no traditional data inputs. The value source is provided via the InOut variable described below.

### **Data Outputs**

- **OUT** (Type: DINT, Initial Value: 0) – Buffered output value containing the current value of the InOut variable.

### **Adapter**

None.

**Special Feature:** The function block uses an **InOut variable** named **IN** (Type: DINT, Initial Value: 0). This variable serves as the source for the read operation. It is neither a pure data input nor a pure data output, but allows direct access to a memory location within the caller context. The function block accesses this variable for reading.

## Functionality

When the **REQ** event input is activated, the function block performs the following steps:

1. The current value of the InOut variable **IN** is read.
2. This value is copied (buffered) to the data output **OUT**.
3. The event output **CNF** is then sent to signal successful execution.

Since this is a single action, the function block is deterministic and requires no further state transitions.

## Technical Features

- **Direct Memory Access:** By using an InOut variable, the function block can access a variable outside its own instance. This allows data sharing between different function blocks without additional input connections.
- **Buffering:** The **OUT** output holds the read value until the next activation of **REQ**. This allows the value to be used multiple times without re-querying the source.
- **No Side Effects:** The function block does not modify the InOut variable **IN**; it only reads its value.

## State Overview

The function block has a single state, **REQ**. When this state is activated, the algorithm's action (copying the value) is executed, and the state is exited, sending **CNF**.

- - **REQ** (Start state and only state)
- Action: `OUT := IN;`
- Output event: **CNF**

There are no branches, loops, or wait times.

## Application Scenarios

- **Buffering a DINT Value:** In a control application, a measured value (e.g., from a sensor) should only be read on request and temporarily stored for further processing.
- **Reading Shared Variables:** If multiple function blocks need access to a shared variable, **GET_DINT** can provide the current value without requiring the variable to be used as a data input for each function block.
- **Interface Decoupling:** Separating the read time from the actual processing through event-driven buffering.

## Comparison with Similar Function Blocks

In the 4diac IDE, analogous function blocks exist for other data types (e.g., `GET_INT`, `GET_BOOL`). The basic mechanism is identical; only the data type differs.

Unlike a **MOVE** function block, which copies a value from an input to an output, **GET_DINT** reads the value from an InOut variable and buffers it. This allows reading variables that cannot be directly connected as data inputs.

## Conclusion

**GET_DINT** is a simple yet useful function block for event-driven reading and buffering of a DINT value from an InOut variable. Its strength lies in its ability to access shared variables and provide the read value without any side effects. Its clear structure and low complexity make it a reliable tool for many control tasks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

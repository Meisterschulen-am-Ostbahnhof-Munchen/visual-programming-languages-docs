# SET_LWORD
![SET_LWORD](./SET_LWORD.svg)

* * * * * * * * * *
## Introduction
The function block **SET_LWORD** is used to transfer an LWORD value (64-bit integer) from a data input to an InOut variable. It allows the direct setting of a target value that simultaneously functions as an input and output. This makes the block suitable for use in systems where a specific memory location or a connection variable needs to be updated.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal Execution Trigger |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Execution Confirmation |

### **Data Inputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|-------------------------|
| IN | LWORD | 0 | Value to be written |

### **Data Outputs**

| Name | Data Type | Initial Value | Comment |
|------|----------|-------------|------------------------------------|
| OUT | LWORD | 0 | Destination variable (declared as InOut) |

**Note:** OUT is declared in the XML as `<InOutVars>`. It is a combined input/output variable that serves both as a source (read) and a destination (write).

### **Adapter**
None.

## Functionality
When an event is received at the **REQ** input, the function block executes the following algorithm:

OUT := IN;
The value of the data input **IN** is directly transferred to the InOut variable **OUT**. The **CNF** event is then sent to confirm successful execution.

The function block is a simple, stateless function block – there are no delays or concurrency issues.

## Technical Features
- **InOut Variable:** The variable `OUT` is declared as InOut. This means it can be used in the network as both an input (to read an existing value) and an output (to set a new value). The algorithm overwrites the contents of the connected variable with the input value.
- **Type LWORD:** The function block is designed for 64-bit values. When used with shorter data types (e.g., DWORD), an explicit type conversion is required.
- **Initial Value:** Both `IN` and `OUT` are preset to 0.

## State Overview
The function block has only one EC state:

- **REQ:** Executes the algorithm and then sends the CNF event.

There are no wait states or loops.

## Application Scenarios
- **Initializing Memory Locations:** Setting a 64-bit register or a global variable to a defined initial value.
- **Copying Values in InOut Connections:** If another function block provides an LWORD variable as an InOut, SET_LWORD can selectively overwrite it.
- **Test and Debugging Environments:** Manually specifying values in data paths to verify system behavior.

## Comparison with Similar Function Blocks
- **SET_BOOL / SET_DWORD / SET_SINT:** Analogous function blocks for other basic data types (BOOL, DWORD, SINT, etc.). SET_LWORD covers the 64-bit integer range.
- **MOVE:** A general function block that copies values between any data type, but often without InOut support. SET_LWORD specifically uses the InOut declaration and is therefore optimized for direct variable assignments.
- **WRITE_***: Some libraries contain function blocks for writing to peripheral addresses. SET_LWORD is more abstract and operates at the logical variable level.

## Conclusion

The function block **SET_LWORD** is a lean but essential tool for setting a 64-bit value to an InOut variable. Its simple semantics ("write IN to OUT") and support for the standard LWORD data type make it versatile for use in IEC 61499-based automation systems – especially where direct manipulation of variables via event control is required.

# F_REAL_TO_UDINT

<img width="1448" height="213" alt="F_REAL_TO_UDINT" src="https://github.com/user-attachments/assets/2045df2e-f71d-4277-9b58-2a655adc3493" />
* * * * * * * * * *
## Introduction

The function block `F_REAL_TO_UDINT` converts a REAL value to a UDINT value. This block is part of the `iec61131::conversion` package and implements a simple but important type conversion for use in control applications.
![F_REAL_TO_UDINT](F_REAL_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (REAL): The input value to be converted from REAL to UDINT.

### **Data Outputs**

- **OUT** (UDINT): The result of the conversion.

### **Adapters**

This function block does not use any adapters.

## Operation

When an event is received at input `REQ`, the algorithm is executed, which converts the REAL value at input `IN` into a UDINT value and outputs the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features

- The conversion is performed using the built-in function `REAL_TO_UDINT`.
- The function block is deterministic and has no internal states.

## State Overview

Since this is a simple function block, there are no state transitions or machines. The block performs the conversion on each `REQ` event and signals completion with `CNF`.

## Application Scenarios

- Type conversion in control applications where REAL values need to be processed as UDINT.
- Integration into larger function block networks that process different data types.

## ⚖️ Comparison with Similar Function Blocks

- Similar conversion blocks like `F_REAL_TO_INT` or `F_REAL_TO_LREAL` offer conversions to other data types, but not specifically to UDINT.
- Unlike more complex blocks, `F_REAL_TO_UDINT` provides a simple and direct solution for this specific conversion.

## 🛠️ Related Exercises

- [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)

## Conclusion

The `F_REAL_TO_UDINT` function block is a simple yet essential building block for type conversion in IEC 61499-based control applications. Its deterministic and stateless nature makes it reliable and easily integrated into various applications.

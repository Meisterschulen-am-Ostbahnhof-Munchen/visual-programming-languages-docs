# F_LIMIT

![F_LIMIT](https://user-images.githubusercontent.com/113907647/227977194-5735bf57-4df7-4ffb-9457-25cf02c36fc7.png)

* * * * * * * * * *

## Introduction

The F_LIMIT function block is a standard selection function block according to IEC 61131-3 that acts as a limiter. It limits an input value to a defined range between a lower and upper limit.
![F_LIMIT](F_LIMIT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - triggers the limiting operation

### **Event Outputs**

- **CNF**: Acknowledgement of the requested service operation

### **Data Inputs**

- **MN**: Minimum - lower limit for the limit
- **IN**: Input - input value to be limited
- **MX**: Maximum - upper limit for the limit

### **Data Outputs**

- **OUT**: Limited Input - the limited output value

### **Adapters**

No adapter interfaces are available.

## Functionality

The F_LIMIT function block takes an input value (IN) and limits it to the range between the minimum (MN) and maximum (MX). When activated by the REQ event, the following operation is performed:

- If IN < MN, dann OUT = MN
- Wenn IN > MX, then OUT = MX
- If MN ≤ IN ≤ MX, then OUT = IN

After the operation is complete, the CNF event is output with the calculated OUT value.

## Technical Features

- Uses the generic data type ANY_ELEMENTARY, meaning the block can be used with various elementary data types (INT, REAL, etc.)
- All data inputs and the data output use the same data type for consistent operation
- EPL-2.0 License (Eclipse Public License)

## State Transitions

1. **Wait State**: Block waits for a REQ event
2. **Active**: The limiting operation is performed upon a REQ event
3. **Output**: After calculation, a CNF event with an OUT value is output
4. **Return**: Returns to the wait state

## Application Scenarios

- Signal limiting in control engineering
- Protection against exceeding and falling below limit values
- Normalization of measured values to a permissible range
- Safety limiting in process control

![Textfeld:
Bsp. individuelle Eingabe
](https://user-images.githubusercontent.com/113907647/227977195-29734e02-f9c3-4e29-bdab-218a9edc9e4a.png)

## ⚖️ Comparison with similar blocks

Compared to Other selection function blocks:

- F_LIMIT specifically optimized for value limiting
- Simpler than complex comparison blocks with multiple outputs
- More universally applicable due to the ANY_ELEMENTARY data type

## Conclusion

The F_LIMIT function block offers a simple and efficient solution for value limiting in IEC 61131-3 based control systems. Its generic type support makes it flexible for various applications where input values need to be restricted to a defined range.

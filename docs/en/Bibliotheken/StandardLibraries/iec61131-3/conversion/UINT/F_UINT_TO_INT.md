# F_UINT_TO_INT

<img width="1421" height="216" alt="F_UINT_TO_INT" src="https://github.com/user-attachments/assets/52abb253-fd81-47d4-a4b4-ecb1fdf90656" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_INT` converts an unsigned integer value (UINT) to a signed integer value (INT). This functionality is particularly useful when exchanging data between systems that use different integer formats.
![F_UINT_TO_INT](F_UINT_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the function block reads the value at the data input `IN` and performs the conversion.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. Simultaneously, the converted value is output at data output `OUT`.

### **Data Inputs**

- **IN**: The unsigned integer value (UINT) to be converted is entered here.

### **Data Outputs**

- **OUT**: Outputs the converted signed integer value (INT).

#### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

When the event input `REQ` is triggered, the function block's algorithm is activated. It reads the value at input `IN`, converts it from UINT to INT, and outputs the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

The conversion is performed using the built-in function `UINT_TO_INT()`.

## Technical Features

- The function block has a simple structure and contains only one algorithm.
- No additional libraries or adapters are required.
- The conversion is performed directly and without delay.

## State Overview

The function block has no internal states. The conversion is performed anew each time `REQ` is triggered.

## Application Scenarios

- Data conversion between systems that use different integer formats.
- Preprocessing of sensor data that is delivered as UINT but is to be further processed as INT.
- Establishing compatibility between different protocols or interfaces.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_UINT_TO_INT` is specialized and therefore more efficient.
- Similar blocks like `F_INT_TO_UINT` perform the reverse conversion.
- General-purpose blocks like `F_ANY_TO_ANY` offer more flexibility but may be less performant.

## Conclusion

The `F_UINT_TO_INT` function block is a simple yet effective tool for converting between unsigned and signed integer values. Its simplicity and straightforward functionality make it a reliable solution for relevant use cases.

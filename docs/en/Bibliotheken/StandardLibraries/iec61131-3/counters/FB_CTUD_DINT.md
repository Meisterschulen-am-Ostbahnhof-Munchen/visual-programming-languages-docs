# FB_CTUD_DINT
<img width="1418" height="340" alt="FB_CTUD_DINT" src="https://github.com/user-attachments/assets/9e2492b2-42d8-4fe5-a22a-8cf85b070cef" />
* * * * * * * * * *
## Introduction
The FB_CTUD_DINT is a function block that acts as an up/down counter with a DINT counter value. It allows counting in both directions as well as resetting and loading a predefined value. The counter is particularly suitable for control applications where a flexible counting function is required.
![FB_CTUD_DINT](FB_CTUD_DINT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request (triggers the counting operation)

### **Event Outputs**
- **CNF**: Execution confirmation (triggered after completion of the counting operation)

### **Data Inputs**
- **CU** (BOOL): Counts up
- **CD** (BOOL): Counts down
- **R** (BOOL): Resets the counter
- **LD** (BOOL): Loads the preset value
- **PV** (DINT): Preset value

### **Data Outputs**
- **QU** (BOOL): Signals whether the count has reached or exceeded the preset value
- **QD** (BOOL): Signals whether the Output down (CV)
- **CV** (DINT): Current count value

### **Adapter**
No adapters available.

## Functionality
The function block performs the following operations when the REQ event occurs:

1. **Reset (R)**: Sets the count value (CV) to 0 if R is active.

2. **Load (LD)**: Loads the preset value (PV) into the count value (CV) if LD is active.

3. **Count (CU/CD)**:

- If CU is active and the count value has not reached the maximum value (2147483647), the count value is incremented by 1.
- If CD is active and the count value has not reached the minimum value (-2147483648), the count value is decremented by 1.

4. **Setting Outputs**:

- QU is set to TRUE when the counter value reaches or exceeds the preset value.
- QD is set to TRUE when the counter value reaches or falls below 0.

## Technical Features
- The counter value (CV) is of type DINT (32-bit signed integer), which allows for a large counting range.
- The function block prevents the counter value from overflowing by checking the limit values.
- Simultaneously activating CU and CD does not change the counter value.

## State Overview

The function block does not have an internal state in the sense of a state machine. The logic is re-executed with each REQ event.

## Application Scenarios
- Production counting (e.g., piece counting on a conveyor belt)
- Position detection (e.g., in linear axes)
- Event counting with the option to reverse direction

## ⚖️ Comparison with similar function blocks
- Compared to simple counters (e.g., CTU or CTD), this function block offers both counting directions in a single block.
- Compared to counters with a smaller data type (e.g., INT), the DINT type offers a larger counting range.

## Conclusion
The FB_CTUD_DINT is a versatile counter function block for applications requiring bidirectional counting functions with a large counting range. Its integrated reset and load functions, as well as the status outputs QU and QD, make it particularly suitable for complex control tasks.
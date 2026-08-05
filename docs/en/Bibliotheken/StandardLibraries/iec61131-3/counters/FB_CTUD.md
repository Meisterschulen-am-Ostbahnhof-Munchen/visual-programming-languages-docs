# FB_CTUD
<img width="1337" height="340" alt="FB_CTUD" src="https://github.com/user-attachments/assets/c27b281b-91cd-4e44-8224-7fc42017d1a2" />
* * * * * * * * * *
## Introduction
The FB_CTUD (Up Down Counter) is a function block that acts as a counter with up and down counting capabilities. It allows events to be counted in both directions and offers additional functions such as reset and loading a predefined value.
![FB_CTUD](FB_CTUD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal Execution Request. This event input triggers the execution of the counting process and is linked to the data inputs CU, CD, R, LD, and PV.

### **Event Outputs**
- **CNF**: Execution Confirmation. This event is output after the counting process is complete and is linked to the data outputs QU, QD, and CV.

### **Data Inputs**
- **CU** (BOOL): Counts up.
- **CD** (BOOL): Counts down.
- **R** (BOOL): Resets the counter value to 0.
- **LD** (BOOL): Loads the predefined value PV into the counter.
- **PV** (INT): Predefined value that is loaded into the counter when LD is enabled.

### **Data Outputs**
- **QU** (BOOL): Signals whether the counter value is greater than or equal to the predefined value PV.
- **QD** (BOOL): Signals whether the counter value is less than or equal to 0.
- **CV** (INT): Current counter value.

### **Adapters**
The FB_CTUD does not have any adapters.

## Functionality
The function block FB_CTUD performs the following operations:

1. **Reset (R)**: When R is enabled, the counter value (CV) is set to 0.

2. **Load (LD)**: When LD is enabled, the predefined value (PV) is loaded into the counter (CV).

3. **Count (CU/CD)**:

- When CU is enabled and the counter value (CV) is less than 32767, CV is incremented by 1.
- When CD is enabled and the counter value (CV) is greater than -32768, CV is decremented by 1.
- CU and CD cannot be enabled simultaneously.

4. **Outputs (QU/QD)**:

- QU is enabled when CV is greater than or equal to PV.
- QD is enabled when CV is less than or equal to 0.

## Technical Features
- The counter value (CV) is of type INT and has a range of -32768 to 32767.
- The FB_CTUD is a simple function block (SimpleFB) and uses a Structured Text (ST) algorithm to implement its logic.

## State Overview
The FB_CTUD has no explicit states, but the counter value (CV) can be considered a state, which is changed by the inputs CU, CD, R, and LD.

## Application Scenarios
- **Production Lines**: Counting units produced (count up) or remaining units (count down).
- **Warehouse Management**: Monitoring inventory levels.
- **Control Engineering**: Time-controlled processes or event counting.

## ⚖️ Comparison with Similar Function Blocks
- **FB_CTU**: Simple up counter without a down counter function.
- **FB_CTD**: Simple down counter without up counting functionality.
- **FB_CTUD**: Combines both functions in one block and also offers reset and load functions.

## Conclusion
The FB_CTUD is a versatile function block that combines both up and down counting functions in a single block. With its additional functions, such as reset and loading a predefined value, it is suitable for a wide range of control engineering applications. Its ease of use and clear interface structure make it a practical solution for counting tasks.
# FB_TON

<img width="1324" height="243" alt="image" src="https://github.com/user-attachments/assets/b55df574-a026-4d8a-b907-32a7779df532" />
* * * * * * * * * *
## Introduction

**Important note: This function block only functions correctly if it is called cyclically.**
The FB_TON is a standardized timer function block according to IEC 61131-3 that implements an on-delay. This function block is used to implement time-controlled delays in control programs.

![FB_TON](FB_TON.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request - Starts time monitoring when an IN signal is active

### **Event Outputs**

- **CNF**: Execution Confirmation - Confirms completion of time monitoring

### **Data Inputs**

- **IN**: Input - Boolean input that starts the timer (TRUE = timer is running)
- **PT**: Process Time - Time value that defines the delay duration

### **Data Outputs**

- **Q**: Output - Boolean output that becomes TRUE after the delay time has elapsed
- **ET**: Elapsed Time - Displays the elapsed time

### **Adapters**

No adapter interfaces are available.

## Functionality

The FB_TON starts the time measurement when the IN input changes from FALSE to TRUE. Once the specified time PT has elapsed, output Q is set to TRUE. Output ET continuously displays the elapsed time. If IN is set to FALSE during the time measurement, the timer is reset and Q remains FALSE.

## Technical Features

- Time values are processed in the TIME data type
- The timer is immediately reset when IN=FALSE
- ET always displays the current elapsed time, even if the timer is still running
- Implementation compliant with the IEC 61131-3 standard

## State Transitions

1. **Inactive**: IN = FALSE, Q = FALSE, ET = 0
2. **Active (Timer running)**: IN = TRUE, Q = FALSE, ET counts up
3. **Time expired**: IN = TRUE, Q = TRUE, ET = PT

## Application Scenarios

- Delayed switching operations in machine controls
- Safety time monitoring
- Process controls with defined waiting times
- Delayed alarm triggers

## ⚖️ Comparison with similar function blocks

- **FB_TOF**: Off-delay instead of on-delay
- **FB_TP**: Pulse timer with fixed pulse duration
- **FB_TON_EXT**: Extended timer variants with additional functions

## 🛠️ Related Exercises

* [Exercise_020c3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
* [Exercise_020c3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c3_AX.md)

## Conclusion

The FB_TON is a basic and robust timer module for standard turn-on delays in industrial control systems. Its simple and intuitive operation, as well as its compliance with the IEC 61131-3 standard, make it a reliable choice for time-controlled applications.

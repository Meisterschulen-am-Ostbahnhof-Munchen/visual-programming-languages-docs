# FB_TP

<img width="1339" height="243" alt="image" src="https://github.com/user-attachments/assets/81d9eac8-28d0-415d-9678-95305521054c" />
* * * * * * * * * *
## Introduction

**Important note: This function block only functions correctly if it is called cyclically.**
The FB_TP (Timer Pulse) is a standardized timer function block according to IEC 61131-3 that provides a pulsed output function. The function block generates a pulse with a defined duration, independent of the duration of the input signal.

![FB_TP](FB_TP.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - Starts the timer

### **Event Outputs**

- **CNF**: Confirmation of requested service - Signals the end of the time pulse

### **Data Inputs**

- **IN**: Input signal (BOOL) - Controls the start of the timer
- **PT**: Pulse Time (TIME) - Defines the duration of the output pulse

### **Data Outputs**

- **Q**: Output signal (BOOL) - Outputs the current state of the timer
- **ET**: Elapsed Time (TIME) - Displays the elapsed time of the current pulse

### **Adapters**

No adapter interfaces are available.

## Functionality

The FB_TP functions as a monostable multivibrator (one-shot). On a rising edge at the IN input, the timer starts and sets the Q output to TRUE for the duration defined in PT. The elapsed time is continuously output at the ET output. After the set time PT has expired, Q is automatically reset to FALSE, regardless of the state of the IN input.

When a rising edge is detected at the IN input, the timer starts and sets the Q output to TRUE for the duration defined in PT.
## Technical Features

- Time measurement is independent of the input signal duration
- ET output displays the current pulse propagation time
- Immediate response to a rising edge at the IN input
- Automatic reset after time elapses

## State Transitions

1. **Idle State**: IN = FALSE, Q = FALSE, ET = 0
2. **Start**: Rising edge at IN → Q = TRUE, ET counting begins
3. **Progression Time**: Q remains TRUE while ET < PT
4. **End**: When ET ≥ PT → Q = FALSE, ET counting stops

## Application Scenarios

- Generation of precisely defined pulses
- Time-controlled sequences
- Delay circuits
- Clock generation for process control
- Safety time monitoring

## ⚖️ Comparison with similar function blocks

- **FB_TON**: Switch-on delay - Q only becomes active after PT has elapsed
- **FB_TOF**: Switch-off delay - Q remains active for PT after IN reset
- **FB_TP**: Pulse generator - Generates a fixed pulse independent of IN

## 🛠️ Related exercises

- [Exercise_020f2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
- [Exercise_020f2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f2_AX.md)

## Conclusion

The FB_TP is an essential component for time-controlled applications in automation technology. Its ease of use and reliable operation make it ideal for applications requiring precise time pulses. The clear separation of the start pulse and pulse duration enables flexible control concepts.

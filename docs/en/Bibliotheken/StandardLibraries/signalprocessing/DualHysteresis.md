# DualHysteresis
<img width="1018" height="208" alt="DualHysteresis" src="https://github.com/user-attachments/assets/35798c6a-73cc-4b4d-b1ce-f9635b8f4546" />
* * * * * * * * * *
## Introduction
The DualHysteresis function block enables bidirectional conversion of analog to digital signals using hysteresis. It is particularly useful in control applications where reliable switching point conversion with deadband and hysteresis is required.
![DualHysteresis](DualHysteresis.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request (with `QI`)
- `REQ`: Normal Execution Request (with `QI`, `MI`, `DEAD`, `INPUT`, `HYSTERESIS`)

### **Event Outputs**
- `INITO`: Initialization Acknowledgement (with `QO`)
- `CNF`: Execution Confirmation (with `DO_UP`, `DO_DOWN`)

### **Data Inputs**
- `QI` (BOOL): Input Event Qualifier
- `MI` (REAL, Initial Value: 0.5): Average Setting (e.g., 0.5 for 50%)
- `DEAD` (REAL, Initial Value: 0.1): Dead Band around MI (e.g., 0.1 for 10%)
- `HYSTERESIS` (REAL, Initial Value: 0.1): Hysteresis (e.g., 0.1 for 10%)
- `INPUT` (REAL): Input value

### **Data Outputs**
- `QO` (BOOL): Output event qualifier
- `DO_UP` (BOOL): Upward signal
- `DO_DOWN` (BOOL): Downward signal

### **Adapters**
No adapters available.

## Functionality
The function block goes through various states:

1. **Initialization**: Sets the outputs to safe values

2. **Neutral**: Waits for valid input values

3. **UP/DOWN**: Activates the corresponding outputs when the threshold values are exceeded

4. **Deinitialization**: Returns to the safe state

Hysteresis prevents excessive switching for small signal changes around the threshold value.

## Technical Features
- Uses a deadband (DEAD) around the mean (MI)
- Implements symmetrical hysteresis (HYSTERESIS)
- All parameters are configurable
- Safe state upon deactivation (QI=FALSE)

## State Overview
1. **START** → **Init** (when INIT with QI=TRUE)
2. **Init** → **Neutral** (when REQ)
3. **Neutral** → **UP** (when INPUT ≥ MI + DEAD + HYSTERESIS)
4. **Neutral** → **DOWN** (when INPUT ≤ MI - DEAD - HYSTERESIS)
5. **UP/DOWN** → **Neutral** (when returning to the deadband range)
6. **Neutral** → **DeInit** (when INIT with QI=FALSE)
7. **DeInit** → **START** (automatic)

## Application Scenarios
- Position control with deadband
- Temperature monitoring with hysteresis
- Level detection with different switching points for filling/emptying
- General signal conditioning with noise suppression

## ⚖️ Comparison with similar components
- Simple hysteresis blocks typically only have one switching output
- Standard comparators do not offer deadband or hysteresis functionality
- This block combines both directions in a single component with configurable parameters

## Conclusion
The DualHysteresis block offers a flexible solution for applications requiring reliable signal conversion with deadband and hysteresis in both directions. Its clear state machine and configurable parameters make it particularly versatile.
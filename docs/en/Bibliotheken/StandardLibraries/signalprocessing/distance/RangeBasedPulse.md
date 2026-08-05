# RangeBasedPulse
<img width="1038" height="216" alt="RangeBasedPulse" src="https://github.com/user-attachments/assets/7a38dda2-cdee-4a47-be13-09d2637500b0" />
* * * * * * * * * *
## Introduction
The function block `RangeBasedPulse` is a distance-based pulse generator that controls a Boolean output (Q) based on the distance traveled (DIST_IN). The function block is started with a HIGH pulse and periodically generates output pulses according to the configured distance values for HIGH and LOW phases.
![RangeBasedPulse](RangeBasedPulse.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Normal execution request. Linked to the input data DIST_IN, DIST_OFF, DIST_HIGH, and DIST_LOW.

### **Event Outputs**
- `CNF`: Execution confirmation. Linked to output Q.

### **Data Inputs**
- `DIST_IN` (UDINT): Distance traveled
- `DIST_OFF` (UDINT): Distance offset
- `DIST_HIGH` (UDINT): Distance for HIGH output
- `DIST_LOW` (UDINT): Distance for LOW output

### **Data Outputs**
- `Q` (BOOL): Output signal

### **Adapters**
No adapters included.

## Functionality

The function block calculates the remainder (DIST_REMAINDER) of the sum of the distance traveled (DIST_IN) and the offset (DIST_OFF) modulo the sum of DIST_HIGH and DIST_LOW. The output Q is set to HIGH if DIST_REMAINDER is greater than or equal to DIST_HIGH; otherwise, it remains LOW.

## Technical Features
- Uses UDINT (unsigned double integer) for distance calculations
- Implements a simple modulo operation for periodic pulse generation
- Supports an offset value for flexible start positions

## State Overview
- `REQ`: The only state that executes the algorithm and sends the CNF acknowledgment

## Application Scenarios
- Control of machines with distance-based switching operations
- Generation of periodic signals based on distances
- Position-dependent control in vehicle or conveyor systems

## ⚖️ Comparison with Similar Function Blocks
Unlike simple timers, this function block works with distance values instead of time intervals. It offers greater flexibility through the offset parameter and allows the definition of individual HIGH and LOW phases.

## 🛠️ Related Exercises
* [Exercise_071b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_071b.md)]
* [Exercise_072b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_072b.md)]

## Conclusion
The RangeBasedPulse FB is a specialized function block for applications requiring distance-based control signals. Its simple configuration and flexible offset setting make it well-suited for various industrial control tasks.

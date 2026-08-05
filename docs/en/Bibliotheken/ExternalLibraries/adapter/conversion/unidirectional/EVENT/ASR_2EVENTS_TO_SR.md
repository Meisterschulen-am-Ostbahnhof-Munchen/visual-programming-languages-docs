# ASR_2EVENTS_TO_SR
<img width="1224" height="249" alt="image" src="https://github.com/user-attachments/assets/67d010cb-b034-4855-bc18-d9a6b1015a81" />
* * * * * * * * * *
## Introduction
The ASR_2EVENTS_TO_SR function block is a composite function block that converts two separate events into an ASR (Set-Reset) signal. It serves as a bridge between event-based control signals and the ASR adapter format.
![ASR_2EVENTS_TO_SR](ASR_2EVENTS_TO_SR.svg)

## Interface Structure

### **Event Inputs**
- **SET**: Sets the output signal (power on)
- **RESET**: Resets the output signal (power off)

### **Event Outputs**
No direct event outputs available

### **Data Inputs**
No data inputs available

### **Data Outputs**
No data outputs available

### **Adapter**
- **ASR_OUT**: Unidirectional ASR adapter output

## Functionality
This function block forwards incoming SET and RESET events directly to the ASR adapter. A SET event activates the corresponding SET signal on the ASR adapter, while a RESET event activates the RESET signal.

### ## Technical Features
- Composite function block without internal logic processing
- Direct event pass-through to the adapter
- Uses unidirectional ASR adapter technology

## State Overview
The function block has no internal state. It acts purely as a signal relay between the event inputs and the ASR adapter.

## Application Scenarios
- Integration of event-based control systems into ASR-compatible environments
- Connection between different control levels
- Protocol implementation in automation systems

## ⚖️ Comparison with Similar Blocks
Compared to simple event function blocks, ASR_2EVENTS_TO_SR offers a specific interface to the ASR adapter, while other blocks may use direct data outputs.

## 🛠️ Related Exercises
* [Exercise_171_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_171_AX.md)

## Conclusion
ASR_2EVENTS_TO_SR is a specialized function block for converting two separate events into the ASR adapter format. Its simple and straightforward operation makes it a reliable solution for system integrations.
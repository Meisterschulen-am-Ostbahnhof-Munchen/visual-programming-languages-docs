# F_MIN
![F_MIN](https://user-images.githubusercontent.com/116869307/214145380-70470032-f41d-4e56-b478-a1a7d237ca1d.png)
* * * * * * * * * *
## Introduction
The F_MIN function block is a standard selection function block according to IEC 61131-3 that determines the minimum of two input values. The block compares any two elementary data types and returns the smaller of the two values as the result.
![F_MIN](F_MIN.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service Request - triggers the calculation of the minimum

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**
- **IN1**: Input value 1 (any elementary data type)
- **IN2**: Input value 2 (any elementary data type)

### **Data Outputs**
- **OUT**: Minimum value (same data type as the inputs)

### **Adapters**
No adapter interfaces are available.

## Functionality
When the REQ event is activated, the F_MIN block compares the two input values IN1 and IN2. The smaller of the two values is output at OUT. Simultaneously, the CNF event is generated to signal the completion of the operation.

## Technical Features
- Supports any elementary data type (ANY_ELEMENTARY)
- Type safety: Output has the same data type as the inputs
- Real-time capable execution
- Simple and deterministic operation

## State Transitions
1. **Wait State**: Block waits for REQ event
2. **Compute State**: Upon REQ event, IN1 and IN2 are compared
3. **Output State**: Minimum value is output to OUT and a CNF event is generated
4. Return to Wait State

## Application Scenarios
- Limit monitoring in control engineering
- Minimum selection in data processing chains
- Safety-relevant limits
- Signal processing with dynamic input values

## ⚖️ Comparison with similar function blocks
Compared to F_MAX (maximum function), F_MIN determines the smaller value instead of the larger one. Both blocks share the same interface structure and work with any elementary data type.

## Conclusion
The F_MIN block represents a simple, reliable, and standards-compliant solution for minimum determination in IEC 61131-3-based control systems. Its flexibility regarding supported data types makes it a universally applicable building block in various automation applications.
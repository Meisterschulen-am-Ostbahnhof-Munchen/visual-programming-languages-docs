# F_MAX
![F_MAX](https://user-images.githubusercontent.com/116869307/214145353-715ae0b0-3c42-4651-b1ee-ec625ee25ad1.png)

* * * * * * * * * *
## Introduction
The F_MAX function block is a standard selection function block according to IEC 61131-3 that determines the maximum value from two input values. The block compares any two elementary data types and returns the larger of the two values as the result.
![F_MAX](F_MAX.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service Request - triggers the calculation of the maximum

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals completion of the calculation

### **Data Inputs**
- **IN1**: Input value 1 (any elementary data type)
- **IN2**: Input value 2 (any elementary data type)

### **Data Outputs**
- **OUT**: Maximum value (same data type as the inputs)

### **Adapters**
No adapter interfaces are available.

## Functionality
When a REQ event arrives, the F_MAX block compares the two input values IN1 and IN2. The larger of the two values is output at OUT. Simultaneously, a CNF event is generated to signal the completion of the operation. The block supports all elementary data types (ANY_ELEMENTARY), making it universally applicable for various numeric and non-numeric comparisons.

## Technical Features
- Use of the generic data type ANY_ELEMENTARY for maximum flexibility
- Automatic type matching between inputs and output
- Real-time capable execution
- Standard-compliant implementation according to IEC 61131-3

## State Transitions
1. **Wait State**: Block waits for REQ event

2. **Calculation State**: Upon REQ event, IN1 and IN2 are compared

3. **Output State**: Maximum is output to OUT and a CNF event is generated

4. Return to Wait State

## Application Scenarios
- Determining the maximum in control algorithms
- Limit monitoring in process control systems
- Signal processing and filtering
- Quality assurance of measured values
- Prioritization logic in controllers

## ⚖️ Comparison with similar blocks
Compared to specific maximum blocks (such as MAX_INT, MAX_REAL, etc.), F_MAX offers the advantage of type independence. While specific blocks can only process one data type, F_MAX is universally applicable to all elementary data types.

## Conclusion
The F_MAX function block represents a flexible and standards-compliant solution for determining maximum values in automation systems. Its type independence makes it particularly versatile, while its simple interface structure enables intuitive integration into various applications.

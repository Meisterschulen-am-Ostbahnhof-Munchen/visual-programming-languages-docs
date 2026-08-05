# OR_5

![OR_5](https://user-images.githubusercontent.com/116869307/214143625-4af69974-60f8-424f-a81f-1dbeafacb707.png)

* * * * * * * * * *

## Introduction
The OR_5 function block is a generic function block for performing a bitwise OR operation with five inputs. It implements a standard bit function according to IEC 61131-3 and can work with any bit data type.


![OR_5](OR_5.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the OR operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1**: OR input 1 (ANY_BIT data type)
- **IN2**: OR input 2 (ANY_BIT data type)
- **IN3**: OR input 3 (ANY_BIT data type)
- **IN4**: OR input 4 (ANY_BIT data type)
- **IN5**: OR input 5 (ANY_BIT data type)

### **Data Outputs**
- **OUT**: OR result (ANY_BIT data type)

### **Adapters**
No adapter interfaces are available.

## Functionality
The OR_5 function block performs a bitwise OR operation on all five input values. When the REQ event is triggered, the values at IN1 to IN5 are processed, and the result is output to OUT. The CNF event signals the completion of the operation.

The OR operation is performed according to the following logic:

```
OUT = IN1 OR IN2 OR IN3 OR IN4 OR IN5
```

## Technical Features
- **Generic Data Type**: Uses ANY_BIT, enabling use with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)
- **Five Inputs**: Offers more flexibility than standard OR blocks with typically two inputs
- **Event-Driven**: Operates in real time with REQ/CNF signaling

## State Transitions
1. **Wait State**: Block waits for a REQ event

2. **Compute State**: Upon REQ, all inputs are processed

3. **Output State**: Result is set to OUT and CNF is triggered

4. Returns to Wait State

## Application Scenarios

- Combining multiple binary signals in control applications

- Monitoring systems with multiple input conditions
- Signal processing in industrial automation systems
- Use in safety circuits with multiple monitoring sensors

## ⚖️ Comparison with similar devices Function Blocks

- **Standard OR Blocks**: Typically only two inputs, OR_5 offers five inputs

- **AND Blocks**: Perform AND operations instead of OR operations

- **XOR Blocks**: Perform exclusive OR operations

## Conclusion
The OR_5 function block is a versatile and powerful five-input block for bitwise OR operations. Its generic nature allows for use in various application areas, while its event-driven architecture ensures precise control over execution timing.
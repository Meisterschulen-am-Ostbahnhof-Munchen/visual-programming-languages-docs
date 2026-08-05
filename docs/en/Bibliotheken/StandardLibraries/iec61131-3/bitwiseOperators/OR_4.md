# OR_4

![OR_4](https://user-images.githubusercontent.com/116869307/214143582-4f76941e-a1fd-411f-96d2-9a28b48f8147.png)

* * * * * * * * * *

## Introduction
The OR_4 function block is a generic function block for calculating bitwise OR operations with four inputs. It performs a bitwise OR operation on the input data and outputs the result. The function block is suitable for all ANY_BIT data types, thus enabling flexible use with various bit data types.


![OR_4](OR_4.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the OR operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1**: OR input 1 (ANY_BIT)
- **IN2**: OR input 2 (ANY_BIT)
- **IN3**: OR input 3 (ANY_BIT)
- **IN4**: OR input 4 (ANY_BIT)

### **Data Outputs**
- **OUT**: OR result (ANY_BIT)

### **Adapters**
No adapters available.


## Functionality
Upon arrival of the REQ event, the OR_4 block performs a bitwise OR operation on all four inputs. The operation is executed separately for each bit position: OUT[i] = IN1[i] OR IN2[i] OR IN3[i] OR IN4[i]. After completion of the calculation, the CNF event is output along with the result.


``` ## Technical Features
- Generic building block for ANY_BIT data types
- Supports various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)

- Bitwise processing of all inputs
- Four independent inputs for maximum flexibility

## State Transitions
1. **Wait State**: Block waits for REQ event

2. **Compute State**: Upon REQ event, block performs OR calculation
3. **Output State**: Sends CNF event with result and returns to wait state

## Application Scenarios
- Bitmask operations in control systems
- Combining multiple status bits into an overall status
- Parallel processing of multiple conditions
- Signal processing in industrial automation systems

## ⚖️ Comparison with Similar Building Blocks
Compared to simpler OR blocks with fewer inputs, OR_4 offers the ability to process four inputs in parallel, reducing the number of blocks required in complex circuits. Compared to function blocks with fixed data types, OR_4 offers greater flexibility through the use of ANY_BIT.

## Conclusion
The OR_4 function block is a versatile and efficient four-input function block for bitwise OR operations. Its generic nature allows for use in various applications, while its clear event-driven control ensures reliable integration into more complex control sequences.
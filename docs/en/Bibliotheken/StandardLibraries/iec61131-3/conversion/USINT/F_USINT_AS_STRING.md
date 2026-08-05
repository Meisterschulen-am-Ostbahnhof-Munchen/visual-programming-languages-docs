# F_USINT_AS_STRING
<img width="1481" height="214" alt="F_USINT_AS_STRING" src="https://github.com/user-attachments/assets/bdc5d422-b30f-4da1-89aa-4becb5d9337d" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_AS_STRING` converts an unsigned 8-bit integer value (USINT) into a string (STRING). This functionality is particularly useful when numeric values need to be converted into a readable text format for display or logging.
![F_USINT_AS_STRING](F_USINT_AS_STRING.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: An unsigned 8-bit integer value (USINT) to be converted to a string.

### **Data Outputs**
- **OUT**: The resulting string (STRING) containing the converted value.

#### **Adapters**
- No adapters are present.

## Functionality
When the event input `REQ` is triggered, the algorithm is executed, converting the USINT value `IN` to a string and outputting the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

### **Adapters**

#
## Technical Features
- The function block uses the function `USINT_AS_STRING` for conversion.
- It is a simple function block without a state machine or complex logic.

## State Overview
Since it is a simple function block, there are no state transitions or management. The operation is executed on each `REQ` event and acknowledged with `CNF`.

## Application Scenarios
- Displaying numerical values on a control panel.
- Logging measured values to a text file or database.
- Preparing data for communication via text protocols (e.g., HTTP, MQTT).

## ⚖️ Comparison with Similar Building Blocks
- Compared to generic conversion blocks, `F_USINT_AS_STRING` specializes in converting USINT to STRING and is therefore more efficient in this specific application.
- Other blocks might offer additional options such as formatting or locale settings, which is not the case here.

## Conclusion
The `F_USINT_AS_STRING` function block is a simple and efficient tool for converting unsigned 8-bit integers to strings. Its simplicity makes it particularly suitable for applications where performance and reliability are paramount.

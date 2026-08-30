# F_INT_AS_STRING

<img width="1244" height="182" alt="F_INT_AS_STRING" src="https://github.com/user-attachments/assets/c27e3bee-e252-420c-846b-caa7085610b7" />
* * * * * * * * * *
## Introduction

The function block `F_INT_AS_STRING` converts an integer value (`INT`) into a string (`STRING`). This functionality is particularly useful when numeric values need to be output in a user-readable format or further processed in a word processor.
![F_INT_AS_STRING](F_INT_AS_STRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the input value. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`INT`): The integer value to be converted to a string.

### **Data Outputs**

- **OUT** (`STRING`): The resulting string after the input value has been converted.

#### **Adapters**

- This function block has no adapters.

## Functionality

When the event `REQ` is triggered, the algorithm is executed that converts the integer value `IN` to a string and outputs the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features

- The conversion is performed using the function `INT_AS_STRING`, which directly converts the `INT` value into a `STRING` value.
- The function block is simple and efficient because it does not require complex state machines or additional processing steps.

## State Overview

Because it is a simple function block, there are no explicit states. The functionality is executed directly upon triggering the `REQ` event.

## Application Scenarios

- Displaying numeric values in user interfaces or logs.
- Preparing data for output in text formats (e.g., CSV, JSON).
- Integration into systems that require strings for further processing.

## ⚖️ Comparison with similar building blocks

- Compared to generic conversion blocks, `F_INT_AS_STRING` specializes in converting `INT` to `STRING` and is therefore more efficient and easier to use.
- Other blocks might support additional parameters such as formatting or locale settings, which is not the case here.

## Conclusion

The `F_INT_AS_STRING` function block offers a simple and effective way to convert integer values to strings. Its simplicity and direct functionality make it ideal for applications that require fast and straightforward conversion.

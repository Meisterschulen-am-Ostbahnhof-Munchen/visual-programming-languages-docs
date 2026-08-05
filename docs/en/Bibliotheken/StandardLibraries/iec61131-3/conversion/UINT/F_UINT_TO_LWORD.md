# F_UINT_TO_LWORD

<img width="1452" height="216" alt="F_UINT_TO_LWORD" src="https://github.com/user-attachments/assets/be6bea7a-7598-41df-9c89-9d0b6d2272ef" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_LWORD` converts a `UINT` value (16-bit unsigned integer) to a `LWORD` value (64-bit unsigned integer). This conversion is particularly necessary in scenarios where data with different bit widths needs to be processed or transmitted.

![F_UINT_TO_LWORD](F_UINT_TO_LWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `UINT`, which is to be converted to a `LWORD` value.

### **Data Outputs**

- **OUT**: The converted output value of type `LWORD`.

### **Adapters**
This function block has no adapters.

## Operation
The function block performs the conversion using the algorithm `REQ`, which is activated when the event `REQ` is triggered. The algorithm converts the `UINT` input value `IN` into a `LWORD` value and assigns it to the output `OUT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features

- The conversion is performed without data loss because the `LWORD` type covers a larger range of values than `UINT`.

- The function block is deterministic and has no internal states.

## State Overview
Since this is a simple function block, there are no state transitions or internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Data conversion in control systems where different data types need to be processed.

- Integration into larger function block networks that process data with varying bit widths.

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, `F_UINT_TO_LWORD` specializes in converting `UINT` to `LWORD`, thus offering an optimized and type-safe solution.

- Other conversion blocks might offer additional features such as error handling or overflow checking, which is not the case here.


## Conclusion

The `F_UINT_TO_LWORD` function block offers a simple and efficient way to convert `UINT` values to `LWORD` values. Its simplicity and determinism make it a reliable component in control applications. However, for more complex requirements, such as error handling, more advanced function blocks should be considered.
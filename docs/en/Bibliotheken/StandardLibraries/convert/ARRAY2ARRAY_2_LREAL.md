# ARRAY2ARRAY_2_LREAL

<img width="1219" height="160" alt="image" src="https://github.com/user-attachments/assets/57ce3ad0-2da9-4075-8d37-abf71840b469" />
* * * * * * * * * *
## Introduction

The function block (FB) `ARRAY2ARRAY_2_LREAL` is a service interface function block designed to copy values from an input array to an output array. It serves as a simple, event-driven interface for transferring data between arrays within a 4diac application.
![ARRAY2ARRAY_2_LREAL](ARRAY2ARRAY_2_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Event): Triggers the copying process. This event signals the function block to start the data transfer.
- Associated with data variable: `IN`

### **Event Outputs**

- **CNF** (Event): Confirms completion of the copy process. This event is triggered after successful data transfer.
- Associated with data variable: `OUT`

### **Data Inputs**

- **IN** (Type: `LREAL`, Array Size: `2`): The source array whose values are to be copied. This is a double-precision floating-point array of long real numbers.

### **Data Outputs**

- **OUT** (Type: `LREAL`, Array Size: `2`): The target array into which the copied values are written. This is also an array of long real numbers.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block `ARRAY2ARRAY_2_LREAL` operates in an event-driven manner. As soon as the input event `REQ` is received, the function block reads the current values from the data input array `IN`. These values are then copied directly into the data output array `OUT`. After the copying process is complete, the output event `CNF` is triggered to signal the successful completion of the operation. The block thus processes a one-to-one copy of the array elements.

## Technical Features

- **Service Interface:** The function block is designed as a "Service Interface Function Block Type," indicating a standard interface for specific services.
- **Generic Implementation:** Internally, this function block likely uses a generic implementation, as indicated by the attribute value `'GEN_ARRAY2ARRAY'`. This allows for the flexible creation of similar function blocks for different array sizes and data types.
- * **Fixed Array Size:** The array size for `IN` and `OUT` is fixed at `2`, limiting its use to specific scenarios with this array dimension.
- **Data Type `LREAL`:** The function block is specialized for the data type `LREAL` (Long Real Number), making it ideal for processing high-precision floating-point numbers.

## State Overview

The function block typically exists in two main states:

1. **Waiting for Request:** The block waits for the `REQ` event. In this state, it is passive and performs no operations.
2. **Processing the Request:** After receiving `REQ`, the block switches to this state, executes the copy process from `IN` to `OUT`, and then emits `CNF` before returning to the "Waiting for Request" state.

## Application Scenarios

- **Data Routing:** Forwarding `LREAL` data packets of size 2 between different parts of a control system.
- **Data Buffering:** Short-term storage or transmission of measured values or setpoints.
- **Interface Adaptation:** If a function block outputs a `LREAL` array of size 2 and another function block requires the same array as input, this function block can act as a bridge.
- * **Constant Data Transfer:** Transferring static or infrequently updated `LREAL` arrays from one point to another.

## ⚖️ Comparison with Similar Building Blocks

This building block is very specific in its function. Compared to more general data manipulation building blocks, which often allow flexible data types or array sizes via configuration parameters, `ARRAY2ARRAY_2_LREAL` is specifically designed for `LREAL` arrays of size 2. If building blocks for generic array copies existed (e.g., `ARRAY_COPY` with configurable size and type), this building block would be a specialized instance of one. It is simpler than such generic building blocks but less flexible. However, for its specific task, it offers a clear and efficient solution.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2014 Profactor GmbH |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-08-05, Matthias Plasch) |
| 4diac Package | eclipse4diac::convert |

## Conclusion

The `ARRAY2ARRAY_2_LREAL` function block provides a straightforward, event-driven method for copying `LREAL` arrays of size 2. Its specialization for this data type and array size makes it a useful tool for defined use cases where this precise data structure is required. It contributes to the modularity and readability of 4diac applications by providing an explicit function for this type of data transfer.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

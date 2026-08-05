# VALUES2ARRAY_2_LREAL
<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction
The function block `VALUES2ARRAY_2_LREAL` is used to convert two individual floating-point numbers of type LREAL into an array of the same type. It is designed as a service interface function block, providing a simple interface for this conversion task.
![VALUES2ARRAY_2_LREAL](VALUES2ARRAY_2_LREAL.svg)

## Interface Structure

### **Event Inputs**
* **REQ** (Type: `Event`)
* Comment: Service Request
* Associated Data: `IN_1`, `IN_2`
* Description: This event triggers the conversion of the two input values `IN_1` and `IN_2` into the array `OUT`.

### **Event Outputs**
* **CNF** (Type: `Event`)
* Comment: Confirmation of Requested Service
* Associated Data: `OUT`
* Description: This event is triggered after the conversion is successful and the output array `OUT` is updated.

### **Data Inputs**
* **IN_1** (Type: `LREAL`)
* Comment: Input number 1
* Description: The first floating-point number to be added to the array.
* **IN_2** (Type: `LREAL`)
* Comment: Input number 2
* Description: The second floating-point number to be added to the array.

### **Data Outputs**
* **OUT** (Type: `LREAL`, Size: `2`)
* Comment: Array output
* Description: An array of type LREAL containing the values of `IN_1` and `IN_2`. `IN_1` occupies the first index, and `IN_2` the second index of the array.

### **Adapters**
This function block does not have any adapter interfaces.

## Functionality

When a `REQ` event is received at the input of the function block, `VALUES2ARRAY_2_LREAL` reads the current values of the data inputs `IN_1` and `IN_2`. These two values are then transferred to the output array `OUT`, with `IN_1` being assigned to element `OUT[0]` and `IN_2` to element `OUT[1]`. After successful completion of this operation, a `CNF` event is issued to signal the completion of the request.

## Technical Features
* The function block is specialized for converting exactly two LREAL values.
* The output array `OUT` is fixed at size 2.
* Processing is event-driven, allowing for explicit requests to initiate the conversion process.

## State Overview
The `VALUES2ARRAY_2_LREAL` function block is stateless. Each `REQ` request is processed independently, without maintaining internal state across requests. The function depends solely on the input values at the time of the `REQ` event.

## Application Scenarios
* **Data Bundling**: When two separate LREAL values need to be passed as a single data packet (array) to other function blocks that expect arrays as input.

## Application Scenarios * **Array Interface Compatibility**: Adapting scalar data to interfaces that explicitly require arrays.
* **Preprocessing for Mathematical Operations**: Preparing data pairs for array-based operations, such as vector addition or scaling.

## ⚖️ Comparison with Similar Blocks

This function block is specifically for converting two LREAL values into an LREAL array. General "value-to-array" blocks might be more flexible regarding the number and data type of inputs, but this block provides a simple, specialized solution for the specified use case. For a larger number of values or different data types, corresponding, specially adapted blocks would be required.

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2014 Profactor GmbH |
| License | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-07-09, Matthias Plasch) |
| 4diac package | eclipse4diac::convert |

## Conclusion

The `VALUES2ARRAY_2_LREAL` function block is a useful and efficient block for the specific task of converting two LREAL values into a fixed-dimensional LREAL array. Its simplicity and event-driven operation make it a natural component in scenarios where such data aggregation is required, and contribute to the modularity and readability of the application.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

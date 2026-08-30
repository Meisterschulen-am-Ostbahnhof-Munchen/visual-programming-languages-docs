# ARR08B_TO_ST08B

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/6f2c370a-b183-4202-8424-1b736a6424dd" />
![ARR08B_TO_ST08B](./ARR08B_TO_ST08B.svg)

* * * * * * * * * *
## Introduction

This function converts an 8-byte array into an 8-byte structure. It is used to convert linear byte data into a structured format.
## Interface Structure

### **Event Inputs**

- **REQ**: A rising event at this input triggers the conversion of the data from input `IN` to output `OUT`.
- Associated with: `IN`

### **Event Outputs**

- **CNF**: An event at this output signals the completion of the conversion and that the output data at `OUT` has been updated.
- Associated with: `OUT`

### **Data Inputs**

- **IN** (Type: `BYTE`, Array Size: `[0..7]`): The input data array containing the 8 bytes to be converted.
- Comment: `ARR08B Input`

### **Data Outputs**

- **OUT** (Type: `logiBUS::utils::conversion::types::ST08B`): The output structure containing the converted 8 bytes.
- Comment: `ST08B Output`

### **Adapters**

No adapters are defined for this function block.

## Functionality

The function block `ARR08B_TO_ST08B` performs a direct byte-by-byte assignment. When a `REQ` event is received, the individual elements of the input array `IN` are assigned to the corresponding components of the output structure `OUT`:

- `OUT.B_00` is assigned to `IN[0]`.
- `OUT.B_01` is assigned to `IN[1]`.
- `OUT.B_07` is assigned to `IN[7]`.

After these assignments are complete, a `CNF` event is triggered to indicate that the conversion is finished and the new data is available at the `OUT` output.

## Technical Details

- **Data Types:** The input array is of type `BYTE`, and the output structure `ST08B` is a user-defined type consisting of 8 individual `BYTE` components (e.g., `B_00` to `B_07`).

- **Direct Assignment:** No data manipulation or conversion takes place; the bytes are copied directly from the array position to the structure component.

- **Stateless:** The function block has no internal state and always produces the same result for the same input.

## State Overview

The `ARR08B_TO_ST08B` function block is **stateless**. It performs a purely functional transformation: On each trigger event (`REQ`), the current input values (`IN`) are converted, and the result (`OUT`) is output. No values are stored between calls.

## Application Scenarios

This function block is useful in scenarios where:

- Raw data received as a byte array (e.g., via communication interfaces such as CAN, SPI, UART) needs to be converted into a structured format to improve readability and further processing.
- Data is exchanged between systems that use different representations for the same 8-byte data set (array vs. structure).
- A clear and explicit type conversion from a linear to a named structure is required to improve program logic.

## ⚖️ Comparison with Similar Function Blocks

- **Generic Copy Functions (e.g., `MEMCPY`):** Unlike a generic memory copy function that copies memory areas byte by byte, `ARR08B_TO_ST08B` provides a type-safe and explicit assignment of array elements to structured fields. This can help avoid errors in resizing or type matching and improve code readability.
- **Manual Assignments:** The functionality could also be achieved through eight individual assignment lines in ST code. However, this function block encapsulates this logic in a reusable and easily integrated unit, promoting modularity and maintainability.
- **Type Casting:** While a type cast might enable a similar conversion in some languages, this function block provides an explicit, event-driven interface that fits well into the 4diac model and allows for clear triggering of the conversion.

## Conclusion

The `ARR08B_TO_ST08B` function block is a specialized and efficient building block for converting an 8-byte array into a predefined 8-byte structure. It improves code structure, readability, and maintainability by encapsulating a frequently used conversion task in a clear and reusable unit. Its stateless nature ensures predictable and reliable operation.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

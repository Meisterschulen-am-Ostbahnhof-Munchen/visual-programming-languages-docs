# ST02X

*(No image available for this data type.)*

* * * * * * * * * *
## Introduction

The **ST02X** data type is a structured data type designed to encapsulate two Boolean values. It serves as a simple data structure for organizing and transporting two individual bits, or Boolean states, in a single unit. The name "ST02X" suggests a "structure with 2 [Boolean values]".
## Interface Structure

Because ST02X is a data type and not a function block, it does not have external event or data inputs/outputs in the usual sense of a function block. Its "structure" refers to the definition of its internal components, which represent the actual data.

## **Event Inputs**

Not applicable, as ST02X is a data type and not a function block, and therefore does not process events.

### **Event Outputs**

Not applicable, as ST02X is a data type and not a function block, and therefore does not generate events.

### **Data Inputs**

The internal components of this data type can be considered its "data," which can be set or read when a variable of this type is used.

- **X_00** (Type: BOOL, Comment: BIT 00)
- The first Boolean value within the structure.
- **X_01** (Type: BOOL, Comment: BIT 01)
- The second Boolean value within the structure.

### **Data Outputs**

The internal components can also be considered "data outputs," as their values can be read by external function blocks or program sections when a variable of type ST02X is used.

### **Adapters**

Not applicable, as ST02X is a data type and not a function block, and therefore does not have adapter interfaces.

## Functionality

The ST02X data type is a passive container for data. It does not perform any operations or logic itself. Its function is limited to logically grouping the two Boolean values `X_00` and `X_01`. When a variable of type ST02X is declared, its components can be accessed using the dot operator (e.g., `meineVariable.X_00`) to read or write its values.

## Technical Features

- **Compact Structure:** The data type is very simple and consists of only two Boolean variables.
- **Typical Application:** It is particularly suitable for grouping two related status bits, flags, or switch states that need to be handled together.
- **Packaging:** The internal structure can help keep data compact and improve code readability by grouping logically related information.

## State Overview

Since ST02X itself has no active logic, it does not have a "state" in the sense of a state machine. The "state" of a variable of type ST02X is determined by the combination of the values of its two Boolean components (`X_00` and `X_01`). There are four possible states for an instance of ST02X:

- `X_00 = FALSE, X_01 = FALSE`
- `X_00 = TRUE, X_01 = FALSE`
- `X_00 = FALSE, X_01 = TRUE`
- `X_00 = TRUE, X_01 = TRUE`

## Application Scenarios

- **Status Display:** Grouping of two status flags (e.g., "Alarm Active" and "Warning Pending").
- **Configuration Parameters:** Bundling of two binary configuration settings.
- **Sensor Data:** Summary of the states of two simple sensors (e.g., two limit switches).
- **Interfaces:** As parameters for function blocks that need to process or return two Boolean pieces of information at once, which simplifies interface definition.

## ⚖️ Comparison with Similar Building Blocks

- **Single BOOL Variables:** Instead of using ST02X, two separate BOOL variables could be declared. The advantage of ST02X lies in its logical grouping and potentially clearer passing as a single parameter to function blocks.
- **ARRAY OF BOOL:** An array like `ARRAY[0..1] OF BOOL` could also hold two Boolean values. However, ST02X offers the advantage of named accesses (`.X_00`, `.X_01`), which can improve readability compared to indexed accesses (`[0]`, `[1]`).

**ARRAY OF BOOL:** An array like `ARRAY[0..1] OF BOOL` could also hold two Boolean values. However, ST02X offers the advantage of named accesses (`.X_00`, `.X_01`), which can improve readability compared to indexed accesses (`[0]`, `[1]`).

- * **Other Structured Types:** Depending on the application, more complex structured data types with more Boolean values (e.g., ST04X, ST08X) or mixed data types might be more suitable if more or different information needs to be grouped. ST02X is specifically optimized for the case of exactly two Boolean values.

## Conclusion

ST02X is a simple yet useful structured data type that enables the logical grouping of two Boolean values. It improves code organization and readability, especially when dealing with two related binary pieces of information. Its strength lies in its simplicity and clear definition, making it a good choice for specific use cases where exactly two Boolean states need to be grouped.

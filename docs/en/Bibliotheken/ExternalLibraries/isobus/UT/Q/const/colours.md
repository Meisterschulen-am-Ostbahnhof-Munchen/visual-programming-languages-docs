# colours

![colours](./colours.svg)

* * * * * * * * * *
## Introduction

The global constant package `colours` defines a set of named constants for color values. These constants represent a set of 16 predefined colors, encoded by numeric values of type `USINT` (Unsigned Short Integer). Using such constants improves the readability and maintainability of IEC 61499 applications because meaningful identifiers like `COLOR_RED` or `COLOR_BLUE` can be used instead of magic numbers.
## Interface Structure

A global constant package is not a function block in the classical sense; therefore, no event or data interfaces exist. Instead, the package provides a collection of constant declarations that can be imported and used in other function blocks or programs within the same project or namespace.

### **Event Inputs**

*Not applicable.* Global constants do not have event inputs.

### **Event Outputs**

*Not applicable.* Global constants do not have event outputs.

### **Data Inputs**

*Not applicable.* Global constants do not have data inputs.

### **Data Outputs**

*Not applicable.* Global constants do not have data outputs.

### **Adapters**

*Not applicable.* Global constants do not have adapter interfaces.

## How it Works

The `colours` package declares 16 constants of data type `USINT`. Each constant is assigned a fixed numeric value that represents a specific color. The values range from `USINT#0` to `USINT#15`. Once the package is imported into an application or function block, these constant names can be used wherever a `USINT` value is expected. The compiler replaces the constant name with the assigned numeric value during compilation.

## Technical Details

* **Data Type:** All constants are of type `USINT` (Unsigned Short Integer), an unsigned 8-bit data type.
* **Value Range:** The defined values range from 0 to 15 and thus fit well within the value range of the `USINT` type.
* **Naming Convention:** The constant names follow the convention `COLOR_<FARBNAME>` (e.g., `COLOR_GREEN`), making them easily identifiable.
* **Compilation:** Values declared as `CONSTANT` are set at compile time and cannot be changed at runtime.

## State Overview

*Not applicable.* Because they are static, unchanging values, global constants do not have a state machine.

## Application Scenarios

This constant package is particularly useful in applications that require a limited color palette for user interfaces, visual status indicators (e.g., on HMIs or operator terminals), or for indicating process states. Typical use cases include:

* **Visualization:** Assigning colors to different machine states (e.g., Green = Operation, Red = Fault, Yellow = Warning).
* **ISOBUS-compliant applications (UT/Universal Terminal):** Standardizing color values in agricultural applications that use the ISOBUS protocol to ensure consistent display across different terminal devices.
* **Code improvement:** Replacing opaque numerical values in algorithms or configurations with self-explanatory identifiers.

## ⚖️ Comparison with similar building blocks

Unlike function blocks that execute logic or process data, a global constant package simply provides named values. Alternatives include:

1. **Direct use of numerical values:** Leads to code that is less readable and harder to maintain ("magic numbers").
2. **Defining constants within each function block:** Leads to redundancy and makes it difficult to centrally modify values.
3. **Using Enum Types:** Offers even greater type safety, but is not directly available as a global construct in the IEC 61499 standard library. Using `USINT` constants is a practical and widely used alternative.

## Conclusion

The global constant package `colours` is a simple yet effective tool for structuring and improving IEC 61499 applications. By providing a standardized color palette as named constants, it promotes code quality, facilitates maintenance, and supports the development of consistent and understandable control applications, especially in the context of ISOBUS and visual interfaces.

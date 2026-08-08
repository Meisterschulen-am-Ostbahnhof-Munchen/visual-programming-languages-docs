# Computers
## Introduction
The global constants `Computers` provide a collection of predefined network addresses (IP addresses and ports) as strings (`WSTRING`). They serve to centrally manage connection information for various computers or stations within a logiBUS project. Using these constants improves the maintainability and readability of the code, as changes to network addresses only need to be made in one central location.
## Interface Structure
Global constants are not function blocks in the traditional sense; therefore, no event or data interfaces exist. Instead, constant declarations are provided that are available project-wide.
![Computers](./Computers.svg)
### **Data Inputs**
*Not applicable.* Constants are fixed values and have no inputs.

### **Data Outputs**
*Not applicable.* Constants are directly incorporated into expressions or assignments.

### **Adapters**
*Not applicable.*

## Functionality
The constants are defined when the project is compiled. Each constant is assigned a fixed, unchanging value of type `WSTRING` (Wide String). Once the program is running, these constant names (`C_LO`, `C_ET`, etc.) can be used instead of the hard-coded strings in any part of the program that imports or recognizes these constants.

## Technical Specifications
* **Type:** All constants are of type `WSTRING`, which supports Unicode strings.

* **Type:** All constants are of type `WSTRING`, which supports Unicode strings.
* **Scope:** As global constants, they are available within the declared package (`logiBUS::stations`).
* **Initialization:** The values are assigned directly upon declaration and are read-only at runtime.
* **Usage:** They are typically intended for configuring communication modules (e.g., `PUBLISH`, `SUBSCRIBE`, `CLIENT`, `SERVER`) where the address of the communication partner is required.

## State Overview
*Not applicable.* Constants have no state.

## Application Scenarios

1. **Simplified Address Configuration:** In a distributed control system with multiple controllers (e.g., main controller, floor controller), the IP addresses of the individual devices can be stored centrally here. 2. **Portability between environments:** By simply swapping the values in this constant file, a program can be quickly adapted between different network environments (e.g., development local host, test network, production network).

3. **Typo prevention:** Using the constant name `C_ET` is less error-prone than repeatedly typing the string `"192.168.5.1:61499"`.

## ⚖️ Comparison with similar components
* **`VAR_GLOBAL` (Global variables):** Unlike global variables, constants (`CONSTANT`) cannot be changed after initialization. They therefore offer greater program security.
* **`VAR_CONFIG` (Configuration variables):** Configuration variables are also constants, but they can be configured per resource. The global constants defined here have a fixed, project-wide value.
* **Direct Value Specification:** While it's possible to directly use string literals in the code, this leads to poorer maintainability and a higher susceptibility to errors compared to using central constants.

## Conclusion
The global constants `Computers` are a simple yet extremely useful tool for structuring and maintaining network connection data in 4diac projects. They promote clean programming practices, reduce redundancy, and make the code more adaptable to changes in the network topology. Their use is particularly recommended in larger or distributed automation systems.

--

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

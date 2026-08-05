# BOOL_TO_QUARTER
## 🎧 Podcast
![BOOL_TO_QUARTER](./BOOL_TO_QUARTER.svg)
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
<img width="1677" height="214" alt="image" src="https://github.com/user-attachments/assets/78d7da91-c9c9-424a-a08b-2ac7b67c5662" />

* * * * * * * * * *
## Introduction
The function block `BOOL_TO_QUARTER` converts a binary BOOL signal into a special, predefined quarter byte. It translates the logical states `TRUE` and `FALSE` into corresponding, semantically meaningful byte constants, typically used for control commands (e.g., ENABLE/DISABLE). This block is part of the `logiBUS::utils::quarter` library.

## Interface Structure

### **Event Inputs**
* **REQ**: This event triggers the conversion function. Upon its arrival, the current value at the data input `I` is read and processed.

### **Event Outputs**
* **CNF**: This event signals the completion of the conversion. It is output along with the calculated output value `QB`.

### **Data Inputs**
* **I** (BOOL, Initial value: `FALSE`): The binary input value to be converted.

### **Data Outputs**
* **QB** (BYTE, Initial value: `quarter::COMMAND_DISABLE`): The output value as a byte. The block uses a so-called "quarter byte" (2 bits), which can represent four states, of which only two are used in this implementation. The specific value is derived from the constants of the imported library.

### **Adapter**
This function block has no adapter interfaces.

## Functionality
When triggered by the `REQ` event, the block evaluates the value at the input `I`. The processing is performed via a `CASE` instruction:

* If `I` has the value `BOOL#TRUE`, the output `QB` is set to the constant `quarter::COMMAND_ENABLE`.

### **Adapter**

### **Adapter**

### **Adapter**

### **Operating**

### **Operating**

### **Operating**

### **Operating**

### **Operating**

### **Operating**
`#** ... * In all other cases (i.e., by default with `FALSE`), the output `QB` is set to the constant `quarter::COMMAND_DISABLE`.

Immediately after the assignment, the `CNF` event is output along with the new value of `QB`.

## Technical Features
* **Library Dependency**: The block imports and uses constants (`quarter::COMMAND_ENABLE`, `quarter::COMMAND_DISABLE`) from the `logiBUS::utils::quarter::const::quarter` package. The actual byte values are therefore defined there and can be changed centrally.
* **Quarter Byte Concept**: The output is declared as `BYTE`, but conceptually only uses the lower two bits (a "quarter byte"). This allows for later expansion to include additional states without having to change the interface.
* **Initial Values**: Both the input `I` and the output `QB` have defined initial values (`FALSE` and `COMMAND_DISABLE`, respectively), which ensures deterministic startup behavior.

## State Overview
The block does not have an internal state in the sense of a memory. It behaves purely combinatorially with respect to the input data when the `REQ` event occurs. The output `QB` retains its last assigned value until the next execution cycle.

## Application Scenarios
* **Actuator Control**: Conversion of a simple enable signal (`BOOL`) into a device-specific enable/disable command, which is sent as a byte via a fieldbus protocol.
* **Interface Adaptation**: Connection of logic blocks that work with BOOL values to control components that expect commands in quarter-byte format.
* **Code Standardization**: Ensuring that the same centrally defined constants for enable/disable commands are always used in a project.
*
## ⚖️ Comparison with similar building blocks
* **`BOOL_TO_BYTE`**: A generic converter that typically maps `TRUE` to `1` and `FALSE` to `0`. `BOOL_TO_QUARTER` is more specialized and uses project-specific, semantic constants instead of numeric values.
* **Direct assignment**: The functionality could also be replicated by direct assignment in ST code (`QB := I`), but this would eliminate the advantages of centralized constant definition and a clear interface (events).

## 🛠️ Related Exercises
* [Exercise_055](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_055.md)]
* [Exercise_056](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)]

## Conclusion
The `BOOL_TO_QUARTER` function block is a specialized but useful converter for control applications. It offers a clean interface with event-driven control, uses centrally managed constants for consistent semantics, and is potentially extensible thanks to the quarter-byte concept. Its strength lies in combining simple binary logic with device-specific control protocols.

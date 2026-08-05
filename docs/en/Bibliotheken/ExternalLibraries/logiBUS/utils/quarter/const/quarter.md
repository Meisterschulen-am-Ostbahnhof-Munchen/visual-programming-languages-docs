# quarter
## 🎧 Podcast
![quarter](./quarter.svg)
* [The Secret of the 2-Bit Quarter: Efficiency in CAN Bus for Commercial Vehicles ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Das-Geheimnis-des-2-Bit-Quarter-Effizienz-im-CAN-Bus-fr-Nutzfahrzeuge-e3673bk)
* [QUARTER ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----

* * * * * * * * *
## Introduction
The `quarter` library is a collection of global constants designed for working with SAE J1939-compliant status and command values in logiBUS applications. It defines standardized 2-bit values (represented as `BYTE`) and associated plaintext descriptions (`STRING`) for states and control commands. These constants serve to standardize and improve the readability of code that works with binary status information and control commands.

## Interface Structure
`quarter` is a collection of global constants (`GLOBALCONSTANTS`). Therefore, it is not a function block (FB) in the traditional sense with event or data interfaces. The interface consists solely of the defined constants, which can be referenced directly in the code.

### **Data Inputs**
Not present (constant collection).

### **Data Outputs**
Not present (constant collection). The constants themselves represent symbolic names for fixed values.

### **Event Inputs**
Not present (constant collection).

### **Event Outputs**
Not present (constant collection).

### **Adapters**
Not present (constant collection).

## Functionality

The library provides only named constants. When used in code, the symbolic name (e.g., `STATUS_ENABLED`) is replaced by the assigned value (e.g., `2#01`). The `_msg` variants contain descriptive text that can be used for debugging, logging, or user output.

## Technical Details
* **Data Types:** All status and command constants are of type `BYTE`, even though they only use the lower two bits (values 0-3). The corresponding text constants are of type `STRING`.
* **Values:** The values are defined as binary literals (`2#00`, `2#01`, etc.), which clearly indicates their interpretation as 2-bit fields.
* **Package:** The constants are organized in the package `logiBUS::utils::quarter::const`.

## State Overview
Not applicable, as this is a static collection of values.

## Application Scenarios
* **SAE J1939 Communication:** Used in function blocks that send or receive parameters according to SAE J1939, especially for status and control information transmitted as 2-bit fields.
* **Status Management:** Assigning and querying device or function states (e.g., on/off, faulty, unavailable) within a control application.

## * **Command Interfaces:** Definition of control commands for remote devices or subsystems (disable, enable, no action).
* **Logging and Diagnostics:** Use of the `_msg` strings to generate readable log entries or displays in the control panel.

## ⚖️ Comparison with Similar Blocks
* **`logiBUS::utils::bit::const`:** Contains constants for single bits (e.g., `BIT_FALSE`, `BIT_TRUE`). `quarter` extends this concept to 2-bit fields with application-specific semantics.
* **Manual Definition:** Instead of using this library, the values could be written directly in the code as numbers or binary literals. However, using `quarter` increases maintainability, readability, and consistency across the entire project.

**SAE J1939-Specific Libraries:** `quarter` is a basic utility library. More comprehensive J1939 libraries would likely rely on these constants to define more specific messages (PGNs) or parameters (SPNs).

## Conclusion
The `quarter` constant library is a useful tool for developing control software in the SAE J1939 environment and other systems that use 2-bit status and control fields. It promotes standardized, self-explanatory programming and reduces the potential for errors through the use of "magic numbers." Its integration into the `logiBUS::utils` package makes it a fundamental component for structured logiBUS applications.
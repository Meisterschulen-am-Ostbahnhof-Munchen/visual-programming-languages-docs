# AQ
![AQ](./AQ.svg)

* * * * * * * * * *
## Introduction
The `AQ` adapter provides a unidirectional interface (plug side) for transmitting an event and a byte value (used for 2 bits). It serves as a standard definition for communication between function blocks according to IEC 61499-1 and enables simple, directed data transfer.
## Interface Structure
### **Event Inputs**
None.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|------------|

| E1 | Event | Indication (or Request) Event from Plug (triggered together with D1) |

### **Data Inputs**
None.

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| D1 | BYTE | Indication (or Request) Data from Plug (2 bits used) |

### **Adapter**
None.

## Functionality
The `AQ` adapter defines a unidirectional connection. A connected function block can signal via the `E1` event that the byte value at the `D1` data output is valid. The data value is a byte, of which the lower 2 bits carry the actual information. The remaining 6 bits are not defined for the application. The adapter itself contains no processing logic – it solely represents the interface specification.

## Technical Features
- **Unidirectional**: Only event and data outputs are present; no inputs. Suitable for plug pages in adapter pairings.
- **Data Usage**: Of the 8 bits of the byte value, only the lower 2 bits are considered significant. The remaining bits should be set to `0` or ignored by the sending function block.
- **Event + Data**: The event `E1` is linked to the data output `D1` (`With` relation). Both are sent together.
- **Compact**: Minimal interface with one event and one byte.

## State Overview

The adapter itself has no internal state. The sending function block controls the outputs based on its own state machine. The adapter simply defines the protocol: Events and data are transmitted together.

## Application Scenarios
- Transmission of 2-bit status information (e.g., operating state “On/Off/Fault” or two separate flags).
- Simple command transmission with encoded bytes (e.g., 2-bit control words in automation systems).
- As part of a higher-level adapter pairing for minimal, directed communication between function blocks.

## Comparison with Similar Function Blocks

| Feature | AQ (this adapter) | Other adapters (e.g., with multiple events) |

|---------|---------------------|--------------------------------------------|

| Events | 1 output | Often multiple inputs/outputs |

| Data | 1 byte (2 bits used) | Frequently multiple variables or complex types |

| Alignment | Unidirectional (Plug-side) | Bidirectional or pure socket-side |

Complexity | Very low | Medium to high |

The `AQ` adapter is specifically optimized for the minimal case of "one event + one byte".

## Conclusion
The `AQ` adapter offers a streamlined and standardized interface for the unidirectional transmission of an event and a 2-bit signal. Its simplicity makes it ideal for applications requiring reduced communication while maintaining IEC 61499 compatibility. The adapter is defined as a plug-side and expects a corresponding socket counterpart.

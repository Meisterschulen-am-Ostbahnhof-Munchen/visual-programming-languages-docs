# AIWS

![AIWS](./AIWS.svg)

* * * * * * * * * *

## Introduction

The **AIWS** adapter provides a unidirectional interface for transmitting exactly one event and its associated WSTRING data. It defines the communication direction from a source to a destination, with the event always accompanied by the data. The adapter serves as a basic building block for loosely coupled, event-driven data flows in IEC 61499 applications.

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|------------|

| E1 | Event | Indication (or Request) |

### **Data Inputs**

No data inputs available.

### **Data Outputs**

| Name | Type | Comment |

|------|---------|--------------------------------|

| D1 | WSTRING | Indication (or Request) Data from Plug |

### **Adapter**

The adapter itself is to be understood as an interface definition. It has no further internal adapters.

## Functionality

The **AIWS** adapter transmits an event **E1** along with a WSTRING value **D1** in a fixed coupling. As soon as the sending component triggers the event, the current value of **D1** is passed to the receiving side. The direction is strictly from the plug side to the socket side (or vice versa, depending on the use case) – no feedback or acknowledgment takes place. The adapter thus defines a simple, unidirectional data channel.

## Technical Features

- **Unidirectionality**: There is only one event output side, no inputs. This enforces a clear flow direction.

- **Compactness**: Exactly one event with a simple data type (WSTRING) minimizes interface complexity.

- **No Error Handling**: The adapter does not provide mechanisms for timeouts, retries, or error detection. Data integrity must be ensured by the connected function blocks.

- **Standard Compliant**: Complies with the IEC 61499-1 specification for adapter types.

## State Overview

The adapter itself has no internal state. It serves solely as an interface definition and does not implement its own sequence control. The state logic resides with the connected function blocks.

## Application Scenarios

- **Integration of Sensor Data**: Transmission of an event with a measured value (e.g., status message or identification) as a WSTRING to a higher-level controller.

- **Text-Based Commands**: Sending commands (e.g., "START", "STOP") as events with parameters.

- **Logging and Diagnostics**: Output of descriptive events with plain text information to a log component.


## Comparison with Similar Components

| Component | Events | Data | Direction | Special Feature |

|----------|------------|-------|----------|------------|

**AIWS** | 1 Output | 1 WSTRING | Unidirectional | Simplest adapter for WSTRING |

**AI** (hypothetical) | 1 Output | 1 ANY (generic) | Unidirectional | Flexible data type, but more complex |

**BIWS** (bidirectional) | 2 Events (in/out) | 2 WSTRING in both directions | Bidirectional | Requires handshake |

The **AIWS** stands out due to its minimal interface and is particularly suitable for simple, clearly defined point-to-point connections where no return channel is required.


## Conclusion

The **AIWS** adapter is a fundamental and efficient building block for the unidirectional transmission of an event with a WSTRING data. Its simplicity reduces coupling between components and facilitates the modular design of automation solutions according to IEC 61499. It is ideally suited for tasks requiring fast and straightforward event-driven communication.
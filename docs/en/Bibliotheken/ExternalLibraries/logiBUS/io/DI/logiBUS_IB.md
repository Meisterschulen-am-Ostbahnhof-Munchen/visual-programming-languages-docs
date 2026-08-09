# logiBUS_IB

<img width="1903" height="313" alt="image" src="https://github.com/user-attachments/assets/56357e8e-ea36-427f-8c9a-3e990b8f634c" />
* * * * * * * * * *
## Introduction

The logiBUS_IB is a Service Interface Function Block for processing byte input data. This block serves as an input interface for logiBUS systems and enables communication with digital inputs. It supports special event handling such as key press repetitions and provides a standardized interface for initializing and operating input devices.
![logiBUS_IB](logiBUS_IB.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- Linked to: QI, PARAMS, Input, InputEvent
- **REQ**: Service Request Event
- Linked to: QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Service Operation
- Linked to: QO, STATUS, IN
- **IND**: Indication from Resource Interface
- Linked to: QO, STATUS, IN

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Controls the execution of service operations
- **PARAMS** (STRING): Service Parameters for Configuration
- **Input** (logiBUS_DI_S): Identifies the input (I1..I8), Initial value: Invalid
- **InputEvent** (logiBUS_DI_Events_S): Identifies the event (currently only REPEAT supported), Initial value: Invalid

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - Status of the service operation
- **STATUS** (STRING): Service status information
- **IN** (BYTE): Input data from the resource

### **Adapter**

No adapter interfaces available.

## Functionality

The logiBUS_IB Function Block operates as an input service interface for logiBUS systems. During initialization (INIT event), the service parameters are configured and the inputs are defined. The block can respond to both explicit requests (REQ event) and asynchronous events from the hardware. It offers special support for repeated button press events (BUTTON_PRESS_REPEAT).

## Technical Features

- Supports special event types such as BUTTON_PRESS_REPEAT and BUTTON_PRESS_REPEAT_DONE
- Byte-based data input (8-bit)
- Flexible input configuration via PARAMS string
- Separate event outputs for acknowledgments (CNF) and hardware indications (IND)
- Initial value "Invalid" for unconfigured inputs

## State Overview

The function block has the following operating states:

- **Not Initialized**: Before INIT event
- **Initialized**: After successful INIT operation
- **Ready**: For REQ requests and IND events
- **Error State**: In case of faulty operations (reportable via STATUS)

## Application Scenarios

- Digital input modules with 8 inputs
- Keyboard interface with repeat function
- General digital input interfaces in logiBUS systems
- Hardware-related input operations with event handling

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital input blocks, logiBUS_IB offers enhanced service functionality with:

- Configurable configuration
- Event-based communication
- Status feedback
- Special support for key press repetitions

## 🛠️ Related Exercises

* [Exercise_006c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006c.md)]
* [Exercise_011a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a.md)]

## Conclusion

The logiBUS_IB Function Block represents a powerful and flexible solution for byte input data in logiBUS systems. Its service-oriented architecture and support for special event types make it particularly suitable for applications requiring advanced input functionalities such as key press repetitions.
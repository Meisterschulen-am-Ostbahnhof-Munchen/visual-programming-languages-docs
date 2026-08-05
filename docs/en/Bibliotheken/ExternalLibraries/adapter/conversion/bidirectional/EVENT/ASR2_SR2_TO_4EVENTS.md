# ASR2_SR2_TO_4EVENTS

<img width="1144" height="209" alt="image" src="https://github.com/user-attachments/assets/86e61c8f-102b-496b-bc1f-d0e024540466" />

* * * * * * * * * *

## Introduction
The ASR2_SR2_TO_4EVENTS function block is a composite function block that provides the ASR2 adapter signals as four discrete event endpoints. It enables bidirectional conversion between ASR2 adapter interfaces and discrete event inputs and outputs.

![ASR2_SR2_TO_4EVENTS](ASR2_SR2_TO_4EVENTS.svg)

## Interface Structure

### **Event Inputs**
- **EI_SET**: Set / Turn On
- **EI_RESET**: Reset / Turn Off

### **Event Outputs**
- **EO_SET**: Set / Turn On
- **EO_RESET**: Reset / Turn Off

### **Data Inputs**
No data inputs available.


### **Data Outputs**
No data outputs available.

#### **Adapters**

- **ASR_IN**: Adapter input of type `adapter::types::bidirectional::ASR2`

## Functionality
This function block acts as a bridge between the ASR2 adapter and discrete events. The event inputs EI_SET and EI_RESET are passed directly to the ASR2 adapter, while the event outputs EO_SET and EO_RESET are fed directly from the ASR2 adapter. This enables bidirectional communication between the two interfaces.

## Technical Features
- Implemented as a composite function block
- Uses bidirectional adapter communication
- Contains no internal data processing logic, but primarily serves as a signal relay
- Supports Eclipse 4diac standard compliance

## State Overview
This function block has no internal states, as it functions exclusively as a pass-through block for events. All incoming events are immediately forwarded to the corresponding interface.

## Application Scenarios
- Integration of ASR2-compatible components into 4diac systems
- Conversion between adapter-based and event-based interfaces
- Bidirectional signal transmission in automation systems
- Coupling of different communication protocols

## ⚖️ Comparison with similar modules
Compared to simple converter blocks, ASR2_SR2_TO_4EVENTS offers the unique feature of bidirectional communication and specific adaptation to ASR2 adapters. Other converter blocks are often unidirectional or support different adapter types.

## Conclusion
The ASR2_SR2_TO_4EVENTS function block represents an efficient solution for integrating ASR2 interfaces into 4diac-based control systems. Its simple yet effective pass-through architecture enables seamless communication between different interface types without additional processing latency.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
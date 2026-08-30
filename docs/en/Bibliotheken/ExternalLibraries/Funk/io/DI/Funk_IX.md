# Funk_IX

<img width="1912" height="337" alt="image" src="https://github.com/user-attachments/assets/7b367819-772a-47fa-a298-1324da5fda1a" />
* * * * * * * * * *
## Introduction

The Funk_IX is a Service Interface Function Block for Boolean input data. It serves as an interface for communication with digital inputs in distributed automation systems and enables the initialization, querying, and asynchronous notification of input signals.
![Funk_IX](Funk_IX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization
- Linked to: QI, PARAMS, Input
- **REQ**: Service Request
- Linked to: QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Service
- Linked to: QO, STATUS, IN
- **IND**: Indication from Resource
- Linked to: QO, STATUS, IN

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL) - Qualifier for event inputs
- **PARAMS**: Service Parameters (STRING) - Service parameters
- **Input**: Identifies the input (Funk::io::DI::Funk_DI_S) - Identifies the digital input (e.g., DigitalInput_Key_01)

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL) - Qualifier for event outputs
- **STATUS**: Service Status (STRING) - Service status
- **IN**: Input data from resource (BOOL) - Input data from the resource

### **Adapter**

No adapter interfaces are available.

## Functionality

The Funk_IX Function Block implements a Service Interface Pattern for digital inputs. During initialization (INIT event), the service parameters are configured and the specific digital input is identified. Input values can be queried via the REQ event, resulting in a CNF response with the current input value. Additionally, the block supports asynchronous IND events, which are triggered by changes in the input signal's state.

## Technical Features

- Uses the special data type `Funk::io::DI::Funk_DI_S` to identify digital inputs
- Initial value for input is set to "Invalid"
- Supports both synchronous queries (REQ/CNF) and asynchronous notifications (IND)
- Includes comprehensive status feedback via the STATUS output

## State Overview

The Function Block goes through the following states:

1. **Not Initialized**: Before INIT event
2. **Initialized**: After successful INIT/INITO sequence
3. **Query Ready**: Ready for REQ/CNF cycles
4. **Notification Ready**: Ready for asynchronous IND events

## Application Scenarios

- Monitoring of digital sensors and switches
- Integration into distributed control systems
- Connection of field devices in industrial automation
- Condition monitoring of machines and systems

## ⚖️ Comparison with Similar Function Blocks

Compared to Funk_IX offers simple digital input blocks with enhanced service functionality, including parameterization, status feedback, and asynchronous notifications. Its unique input identification enables precise addressing in complex systems.

## 🛠️ Related Exercises

- [Exercise_003b2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003b2_sub.md)

## Conclusion

The Funk_IX Function Block provides a powerful and flexible solution for integrating digital inputs into 4diac-based automation systems. Its service-oriented architecture, with initialization, query, and notification functions, makes it particularly suitable for demanding industrial applications.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

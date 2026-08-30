# PKP_2200_LI_IX

<img width="1893" height="365" alt="image" src="https://github.com/user-attachments/assets/4ab8ed94-c625-4318-8cef-598f76879881" />
* * * * * * * * * *
## Introduction

The PKP_2200_LI_IX is a service interface function block for Boolean input data. This block serves as an interface for digital inputs and enables communication with corresponding hardware resources.
![PKP_2200_LI_IX](PKP_2200_LI_IX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization with parameters QI, PARAMS, u8SAMember, and Input
- **REQ**: Service request with parameter QI

### **Event Outputs**

- **INITO**: Initialization acknowledgment with parameters QO and STATUS
- **CNF**: Acknowledgement of the requested service operation with parameters QO, STATUS, and IN
- **IND**: Indication from the resource with parameters QO, STATUS, and IN

### **Data Inputs**

- **QI**: Event input qualifier (BOOL)
- **PARAMS**: Service parameter (STRING)
- **u8SAMember**: Node SA (USINT) - Default value: PKP_2200::PKP_2200_DEFAULT (21h)
- **Input**: Identifies input Input_Q1..Q8 (Type: BlinkMarine::io::DI::PKP_2200_LI_DI_S) - Initial value: Invalid

### **Data Outputs**

- **QO**: Event output qualifier (BOOL)
- **STATUS**: Service status (STRING)
- **IN**: Input data from the resource (BOOL)

### **Adapter**

No adapter interfaces are available.

## Functionality

This function block initializes and manages communication with digital input resources. The INIT event initializes the service with the appropriate parameters. The REQ event allows service operations to be requested. The INITO, CNF, and IND output events return acknowledgments and status information.

## Technical Features

- Uses specific PKP_2200 communication parameters
- Supports up to 8 digital inputs (Q1-Q8)
- Includes default values for SA members (21h = PKP_2200_DEFAULT)
- Implements invalid initialization for inputs

## State Transitions

The function block goes through the following states:

1. **Initialization Phase**: INIT event processed, INITO response generated
2. **Service Operation**: REQ event processed, CNF response generated
3. **Resource Indication**: Automatic IND events upon state changes

## Application Scenarios

- Connecting digital input sensors in automation systems
- Integration into marine applications (BlinkMarine environment)
- Communication with PKP_2200-compatible hardware
- Monitoring of switching states and signal levels

## ⚖️ Comparison with Similar Function Blocks

Compared to simple The PKP_2200_LI_IX offers enhanced service functionalities for digital input modules, including status feedback and parameterization options. Its specific PKP_2200 integration distinguishes it from generic I/O modules.

## Conclusion

The PKP_2200_LI_IX is a specialized service interface module for the reliable connection of digital inputs in industrial automation systems, particularly in marine environments. Its enhanced functionality, including status feedback and parameterization options, makes it a robust solution for demanding I/O applications.

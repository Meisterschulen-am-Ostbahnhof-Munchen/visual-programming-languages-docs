# eIXconfig
<img width="1406" height="219" alt="image" src="https://github.com/user-attachments/assets/0d14f01f-7aa9-4cd7-93a2-74a47d4f4646" />
* * * * * * * * * *
## Introduction
The eIXconfig function block serves as a Service Interface Function Block for configuring eIO instances. It allows you to set trigger properties for inputs and outputs and provides a connection to eIO instances via an adapter.
![eIXconfig](eIXconfig.svg)

## Interface Structure

### **Event Inputs**
- **CONF**: Configuration Request - triggers the configuration of the eIO instance

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals the completion of the configuration

### **Data Inputs**
- **FE** (BOOL): Falling Edge Trigger Enable - enables edge triggering on a falling edge
- **RE** (BOOL): Rising Edge Trigger Enable - enables edge triggering on a rising edge

### **Data Outputs**
- **STATUS** (WSTRING): Service Status - provides status information about the configuration process

### **Adapter**
- **eIX**: Connection to the eIO instance - establishes communication with the eIO hardware

## Functionality
The eIXconfig block receives a Configuration request. Along with the data inputs FE and RE, the trigger settings for the eIO instance are configured. After successful configuration, the CNF event is output with the corresponding status. Actual communication with the hardware takes place via the eIX adapter.

## Technical Features
- Uses WSTRING for status outputs, enabling comprehensive status information
- Supports separate configuration of rising and falling edge detection
- Implemented as a Service Interface Function Block according to the IEC 61499-2 standard

## State Transitions
1. **Initialization State**: Block waits for a CONF event

2. **Configuration State**: Processes trigger settings and transmits them to the eIO instance

3. **Acknowledgement State**: Outputs CNF with status information

## Application Scenarios
- Configuration of eIO hardware components in industrial control systems
- Setting trigger properties for digital inputs
- Integration into larger automation systems with eIO components

## ⚖️ Comparison with Similar Blocks
Compared to simple IO configuration blocks, eIXconfig offers specific eIO integration and advanced trigger configuration options. Using an adapter allows for a clean separation between functionality and hardware communication.

## Conclusion

The eIXconfig function block represents a specialized solution for configuring eIO instances. Its clear separation of configuration logic and hardware communication, along with flexible trigger settings, makes it ideally suited for demanding industrial applications.

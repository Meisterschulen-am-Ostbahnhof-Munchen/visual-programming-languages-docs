# AX2_X_TO_BOOL
<img width="1186" height="196" alt="image" src="https://github.com/user-attachments/assets/f72801f7-3cc1-4935-9f9d-8c58011e6876" />
* * * * * * * * * *
## Introduction
The AX2_X_TO_BOOL function block is a composite function block for converting AX2 data to BOOL values. It serves as a bidirectional adapter for data type conversion between different interfaces in automation systems.
![AX2_X_TO_BOOL](AX2_X_TO_BOOL.svg)

## Interface Structure

### **Event Inputs**
- **REQ** (Request to Adapter): Initiates the conversion request to the adapter

### **Event Outputs**
- **CNF** (Confirmation from Adapter): Confirms the completion of the conversion from the adapter

### **Data Inputs**
- **OUT** (BOOL): Output data for transfer to the adapter

### **Data Outputs**
- **IN** (BOOL): Input data from the adapter after successful conversion

### **Adapter**
- **AX2_IN** (adapter::types::bidirectional::AX2): Bidirectional AX2 adapter for data type conversion

## Functionality
The function block receives a conversion request via the REQ event and forwards it to the AX2 adapter. The adapter converts AX2 data to BOOL values. After successful conversion, the CNF event containing the converted data is output at the IN output. Simultaneously, BOOL data can be returned to the adapter via the OUT input.

```
## Technical Features
- Bidirectional data transfer between AX2 and BOOL data types
- Composite function block with integrated adapter
- Automatic event forwarding between interfaces
- Positioned elements for optimized display in the development environment

## State Transitions
1. **Wait State**: No active conversion
2. **Active State**: On REQ event - data is forwarded to the adapter
3. **Confirmation State**: Upon completion of the conversion - CNF event is triggered

## Application Scenarios
- Integration of AX2 sensor data into BOOL-based control systems
- Data type conversion in mixed automation environments
- Bidirectional communication between different protocols
- Adapter solutions for existing systems with different data types

## ⚖️ Comparison with similar blocks
Compared to simple conversion blocks, AX2_X_TO_BOOL offers bidirectional functionality with an integrated adapter interface. While simple converters typically only work in one direction, this block enables bidirectional data exchange.

## Conclusion
The AX2_X_TO_BOOL function block provides a robust solution for bidirectional conversion between AX2 and BOOL data types. Its integrated adapter architecture and clear event handling make it particularly suitable for complex automation applications with mixed data type environments.

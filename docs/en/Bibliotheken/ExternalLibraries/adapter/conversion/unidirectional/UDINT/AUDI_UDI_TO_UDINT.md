# AUDI_UDI_TO_UDINT
## Introduction
The AUDI_UDI_TO_UDINT function block is a composite function block used to convert the AUDI adapter format to a UDINT value.
![AUDI_UDI_TO_UDINT](AUDI_UDI_TO_UDINT.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: UDINT output value of the converted data

### **Adapter**
- **AUDI_IN**: Socket of type `AUDI`

## Functionality
The function block receives data via the AUDI adapter socket and makes the contained UDINT value available at the IN output as soon as an event arrives via the adapter (CNF).
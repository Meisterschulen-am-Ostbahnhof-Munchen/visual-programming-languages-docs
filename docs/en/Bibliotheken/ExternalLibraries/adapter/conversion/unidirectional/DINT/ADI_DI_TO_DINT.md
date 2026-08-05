# ADI_DI_TO_DINT
## Introduction
The ADI_DI_TO_DINT function block is a composite function block used to convert the ADI adapter format to a DINT value.
![ADI_DI_TO_DINT](ADI_DI_TO_DINT.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: DINT output value of the converted data

### **Adapter**
- **ADI_IN**: Socket of type `ADI`

## Functionality
The function block receives data via the ADI adapter socket and makes the contained DINT value available at the IN output as soon as an event arrives via the adapter (CNF).
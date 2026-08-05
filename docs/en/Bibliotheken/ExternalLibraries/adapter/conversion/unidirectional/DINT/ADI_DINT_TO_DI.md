# ADI_DINT_TO_DI
## Introduction
The ADI_DINT_TO_DI function block is a composite function block used to convert a DINT value to the ADI adapter format.
![ADI_DINT_TO_DI](ADI_DINT_TO_DI.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Request event to trigger the conversion

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **OUT**: DINT input value to be converted

### **Data Outputs**
- No direct data outputs available

### **Adapter**
- **ADI_OUT**: Plug of type `ADI`

## Functionality
The function block receives a DINT value at the data input OUT and converts it to the ADI adapter format upon arrival of the REQ event.
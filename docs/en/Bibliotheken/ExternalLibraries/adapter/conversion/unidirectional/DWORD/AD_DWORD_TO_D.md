# AD_DWORD_TO_D
## Introduction
The AD_DWORD_TO_D function block is a composite function block used to convert a DWORD value to the AD adapter format.
![AD_DWORD_TO_D](AD_DWORD_TO_D.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Request event to trigger the conversion

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **OUT**: DWORD input value to be converted

### **Data Outputs**
- No direct data outputs available

### **Adapter**
- **AD_OUT**: Plug of type `AD`

## Functionality
The function block receives a DWORD value at the OUT data input and converts it to the AD adapter format upon arrival of the REQ event.
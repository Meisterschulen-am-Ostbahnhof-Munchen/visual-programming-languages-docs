# AL_LWORD_TO_L
## Introduction
The AL_LWORD_TO_L function block is a composite function block used to convert an LWORD value to the AL adapter format.
![AL_LWORD_TO_L](AL_LWORD_TO_L.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Request event to trigger the conversion

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **OUT**: LWORD input value to be converted

### **Data Outputs**
- No direct data outputs available

### **Adapter**
- **AL_OUT**: Plug of type `AL`

## Functionality
The function block receives an LWORD value at the OUT data input and converts it to the AL adapter format upon arrival of the REQ event.
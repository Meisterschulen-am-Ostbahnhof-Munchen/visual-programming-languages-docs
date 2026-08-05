# AI_INT_TO_I
## Introduction
The AI_INT_TO_I function block is a composite function block used to convert an INT value to the AI adapter format.
![AI_INT_TO_I](AI_INT_TO_I.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Request event to trigger the conversion

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **OUT**: INT input value to be converted

### **Data Outputs**
- No direct data outputs available

### **Adapter**
- **AI_OUT**: Plug of type `AI`

## Functionality
The function block receives an INT value at the data input OUT and converts it to the AI adapter format upon arrival of the REQ event.

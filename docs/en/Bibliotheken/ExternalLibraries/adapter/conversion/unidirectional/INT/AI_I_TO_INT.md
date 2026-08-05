# AI_I_TO_INT
## Introduction
The AI_I_TO_INT function block is a composite function block used to convert the AI adapter format to an INT value.
![AI_I_TO_INT](AI_I_TO_INT.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: INT output value of the converted data

### **Adapter**
- **AI_IN**: Socket of type `AI`

## Functionality
The function block receives data via the AI adapter socket and makes the contained INT value available at the IN output as soon as an event arrives via the adapter (CNF).
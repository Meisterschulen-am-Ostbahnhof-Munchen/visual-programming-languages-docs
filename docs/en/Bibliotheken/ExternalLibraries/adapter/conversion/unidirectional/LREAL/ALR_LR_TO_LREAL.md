# ALR_LR_TO_LREAL
## Introduction
The ALR_LR_TO_LREAL function block is a composite function block used to convert the ALR adapter format to an LREAL value.
![ALR_LR_TO_LREAL](ALR_LR_TO_LREAL.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: LREAL output value of the converted data

### **Adapter**
- **ALR_IN**: Socket of type `ALR`

## Functionality
The function block receives data via the ALR adapter socket and makes the contained LREAL value available at the IN output as soon as an event arrives via the adapter (CNF).
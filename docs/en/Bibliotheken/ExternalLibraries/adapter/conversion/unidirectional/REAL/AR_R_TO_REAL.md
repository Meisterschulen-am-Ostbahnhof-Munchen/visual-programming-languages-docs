# AR_R_TO_REAL
## Introduction
The AR_R_TO_REAL function block is a composite function block used to convert the AR adapter format into a REAL value.
![AR_R_TO_REAL](AR_R_TO_REAL.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: REAL output value of the converted data

### **Adapter**
- **AR_IN**: Socket of type `AR`

## Functionality
The function block receives data via the AR adapter socket and makes the contained REAL value available at the IN output as soon as an event arrives via the adapter (CNF).
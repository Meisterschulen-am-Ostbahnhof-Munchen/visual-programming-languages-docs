# AUI_UI_TO_UINT
## Introduction
The AUI_UI_TO_UINT function block is a composite function block used to convert the AUI adapter format to a UINT value.
![AUI_UI_TO_UINT](AUI_UI_TO_UINT.svg)
## Interface Structure
### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: UINT output value of the converted data

### **Adapter**
- **AUI_IN**: Socket of type `AUI`

## Functionality
The function block receives data via the AUI adapter socket and makes the contained UINT value available at the IN output as soon as an event arrives via the adapter (CNF).
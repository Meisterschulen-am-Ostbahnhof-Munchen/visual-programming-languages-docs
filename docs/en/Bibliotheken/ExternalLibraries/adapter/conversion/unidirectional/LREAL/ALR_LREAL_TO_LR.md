# ALR_LREAL_TO_LR

## Introduction

The ALR_LREAL_TO_LR function block is a composite function block used to convert an LREAL value to the ALR adapter format.
![ALR_LREAL_TO_LR](ALR_LREAL_TO_LR.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: LREAL input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **ALR_OUT**: Plug of type `ALR`

## Functionality

The function block receives an LREAL value at the OUT data input and converts it to the ALR adapter format upon arrival of the REQ event.

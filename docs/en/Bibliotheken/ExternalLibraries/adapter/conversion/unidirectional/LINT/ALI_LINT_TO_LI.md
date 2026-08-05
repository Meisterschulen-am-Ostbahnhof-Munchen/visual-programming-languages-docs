# ALI_LINT_TO_LI

## Introduction
The ALI_LINT_TO_LI function block is a composite function block used to convert a LINT value to the ALI adapter format.


![ALI_LINT_TO_LI](ALI_LINT_TO_LI.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**

- **OUT**: LINT input value to be converted

### **Data Outputs**
- No direct data outputs available

### **Adapter**

- **ALI_OUT**: Plug of type `ALI`

## Functionality
The function block receives a LINT value at the OUT data input and converts it to the ALI adapter format upon arrival of the REQ event.
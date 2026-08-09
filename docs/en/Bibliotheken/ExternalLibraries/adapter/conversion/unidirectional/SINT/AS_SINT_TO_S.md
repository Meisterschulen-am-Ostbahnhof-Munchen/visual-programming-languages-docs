# AS_SINT_TO_S

## Introduction

The AS_SINT_TO_S function block is a composite function block used to convert a SINT value into the AS adapter format.
![AS_SINT_TO_S](AS_SINT_TO_S.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: SINT input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AS_OUT**: Plug of type `AS`

## Functionality

The function block receives a SINT value at the OUT data input and converts it to the AS adapter format upon arrival of the REQ event.

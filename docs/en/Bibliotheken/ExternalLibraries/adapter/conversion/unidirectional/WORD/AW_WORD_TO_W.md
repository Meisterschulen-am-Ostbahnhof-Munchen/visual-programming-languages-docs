# AW_WORD_TO_W

## Introduction

The AW_WORD_TO_W function block is a composite function block used to convert a WORD value to the AW adapter format.
![AW_WORD_TO_W](AW_WORD_TO_W.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: WORD input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AW_OUT**: Plug of type `AW`

## Functionality

The function block receives a WORD value at the OUT data input and converts it to the AW adapter format upon arrival of the REQ event.

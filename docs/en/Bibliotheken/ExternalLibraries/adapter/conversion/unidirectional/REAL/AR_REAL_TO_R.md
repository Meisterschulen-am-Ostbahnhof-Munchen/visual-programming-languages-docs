# AR_REAL_TO_R

## Introduction

The AR_REAL_TO_R function block is a composite function block used to convert a REAL value to the AR adapter format.
![AR_REAL_TO_R](AR_REAL_TO_R.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: REAL input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AR_OUT**: Plug of type `AR`

## Functionality

The function block receives a REAL value at the data input OUT and converts it to the AR adapter format upon arrival of the REQ event.

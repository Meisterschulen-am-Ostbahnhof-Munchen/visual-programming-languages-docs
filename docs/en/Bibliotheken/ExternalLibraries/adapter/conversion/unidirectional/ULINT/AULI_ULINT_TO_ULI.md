# AULI_ULINT_TO_ULI

## Introduction

The AULI_ULINT_TO_ULI function block is a composite function block used to convert a ULINT value to the AULI adapter format.
![AULI_ULINT_TO_ULI](AULI_ULINT_TO_ULI.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: ULINT input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AULI_OUT**: Plug of type `AULI`

## Functionality

The function block receives a ULINT value at the OUT data input and converts it to the AULI adapter format upon arrival of the REQ event.

# AUS_USINT_TO_US

## Introduction

The AUS_USINT_TO_US function block is a composite function block used to convert a USINT value to the AUS adapter format.
![AUS_USINT_TO_US](AUS_USINT_TO_US.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: USINT input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AUS_OUT**: Plug of type `AUS`

## Functionality

The function block receives a USINT value at the OUT data input and converts it to the AUS adapter format upon arrival of the REQ event.

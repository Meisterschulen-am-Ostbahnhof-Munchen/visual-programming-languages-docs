# AUDI_UDINT_TO_UDI

## Introduction

The AUDI_UDINT_TO_UDI function block is a composite function block used to convert a UDINT value to the AUDI adapter format.
![AUDI_UDINT_TO_UDI](AUDI_UDINT_TO_UDI.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: UDINT input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AUDI_OUT**: Plug of type `AUDI`

## Functionality

The function block receives a UDINT value at the OUT data input and converts it to the AUDI adapter format upon arrival of the REQ event.

## 🛠️ Related Exercises

- [Exercise_083_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_083_AX.md)

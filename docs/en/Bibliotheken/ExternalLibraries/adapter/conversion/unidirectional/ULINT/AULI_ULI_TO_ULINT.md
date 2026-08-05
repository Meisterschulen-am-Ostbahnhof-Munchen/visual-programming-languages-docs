# AULI_ULI_TO_ULINT

## Introduction
The AULI_ULI_TO_ULINT function block is a composite function block used to convert the AULI adapter format to a ULINT value.


![AULI_ULI_TO_ULINT](AULI_ULI_TO_ULINT.svg)

## Interface Structure

### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: ULINT output value of the converted data

### **Adapter**
- **AULI_IN**: Socket of type `AULI`

## Functionality
The function block receives data via the AULI adapter socket and makes the contained ULINT value available at the IN output as soon as an event arrives via the adapter (CNF).
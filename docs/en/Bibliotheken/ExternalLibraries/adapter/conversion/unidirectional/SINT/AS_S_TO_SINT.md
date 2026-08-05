# AS_S_TO_SINT

## Introduction
The AS_S_TO_SINT function block is a composite function block used to convert the AS adapter format to a SINT value.


![AS_S_TO_SINT](AS_S_TO_SINT.svg)

## Interface Structure

### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: SINT output value of the converted data

### **Adapter**
- **AS_IN**: Socket of type `AS`

## Functionality
The function block receives data via the AS adapter socket and makes the contained SINT value available at the IN output as soon as an event arrives via the adapter (CNF).
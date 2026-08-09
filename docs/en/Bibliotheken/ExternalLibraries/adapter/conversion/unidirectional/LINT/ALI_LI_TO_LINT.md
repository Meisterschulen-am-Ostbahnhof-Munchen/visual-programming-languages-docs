# ALI_LI_TO_LINT

## Introduction

The ALI_LI_TO_LINT function block is a composite function block used to convert the ALI adapter format to a LINT value.
![ALI_LI_TO_LINT](ALI_LI_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- No direct event inputs available

### **Event Outputs**

- **CNF**: Confirmation event after successful conversion

### **Data Inputs**

- No direct data inputs available

### **Data Outputs**

- **IN**: LINT output value of the converted data

### **Adapter**

- **ALI_IN**: Socket of type `ALI`

## Functionality

The function block receives data via the ALI adapter socket and makes the contained LINT value available at the IN output as soon as an event arrives via the adapter (CNF).

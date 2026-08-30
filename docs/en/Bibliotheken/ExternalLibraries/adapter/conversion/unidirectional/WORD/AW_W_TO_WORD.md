# AW_W_TO_WORD

## Introduction

The AW_W_TO_WORD function block is a composite function block used to convert the AW adapter format to a WORD value.
![AW_W_TO_WORD](AW_W_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- No direct event inputs available

### **Event Outputs**

- **CNF**: Confirmation event after successful conversion

### **Data Inputs**

- No direct data inputs available

### **Data Outputs**

- **IN**: WORD output value of the converted data

### **Adapter**

- **AW_IN**: Socket of type `AW`

## Functionality

The function block receives data via the AW adapter socket and makes the contained WORD value available at the IN output as soon as an event arrives via the adapter (CNF).

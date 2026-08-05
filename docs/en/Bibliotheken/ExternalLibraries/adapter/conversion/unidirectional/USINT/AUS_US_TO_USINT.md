# AUS_US_TO_USINT

## Introduction
The AUS_US_TO_USINT function block is a composite function block used to convert the AUS adapter format to a USINT value.


![AUS_US_TO_USINT](AUS_US_TO_USINT.svg)

## Interface Structure

### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- **CNF**: Confirmation event after successful conversion

### **Data Inputs**
- No direct data inputs available

### **Data Outputs**
- **IN**: USINT output value of the converted data

### **Adapter**
- **AUS_IN**: Socket of type `AUS`

## Functionality
The function block receives data via the AUS adapter socket and makes the contained USINT value available at the IN output as soon as an event arrives via the adapter (CNF).
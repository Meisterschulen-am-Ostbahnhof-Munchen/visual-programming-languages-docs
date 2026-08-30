# AD_D_TO_DWORD

## Introduction

The AD_D_TO_DWORD function block is a composite function block used to convert the AD adapter format to a DWORD value.
![AD_D_TO_DWORD](AD_D_TO_DWORD.svg)

## Interface Structure

### **Event Inputs**

- No direct event inputs available

### **Event Outputs**

- **CNF**: Confirmation event after successful conversion

### **Data Inputs**

- No direct data inputs available

### **Data Outputs**

- **IN**: DWORD output value of the converted data

### **Adapter**

- **AD_IN**: Socket of type `AD`

## Functionality

The function block receives data via the AD adapter socket and makes the contained DWORD value available at the IN output as soon as an event arrives via the adapter (CNF).

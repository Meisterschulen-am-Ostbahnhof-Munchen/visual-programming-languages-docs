# AL_L_TO_LWORD

## Introduction

The AL_L_TO_LWORD function block is a composite function block used to convert the AL adapter format to an LWORD value.
![AL_L_TO_LWORD](AL_L_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**

- No direct event inputs available

### **Event Outputs**

- **CNF**: Confirmation event after successful conversion

### **Data Inputs**

- No direct data inputs available

### **Data Outputs**

- **IN**: LWORD output value of the converted data

### **Adapter**

- **AL_IN**: Socket of type `AL`

## Functionality

The function block receives data via the AL adapter socket and makes the contained LWORD value available at the IN output as soon as an event arrives via the adapter (CNF).

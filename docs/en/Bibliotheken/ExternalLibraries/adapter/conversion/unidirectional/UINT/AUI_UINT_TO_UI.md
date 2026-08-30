# AUI_UINT_TO_UI

## Introduction

The AUI_UINT_TO_UI function block is a composite function block used to convert a UINT value to the AUI adapter format.
![AUI_UINT_TO_UI](AUI_UINT_TO_UI.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to trigger the conversion

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **OUT**: UINT input value to be converted

### **Data Outputs**

- No direct data outputs available

### **Adapter**

- **AUI_OUT**: Plug of type `AUI`

## Functionality

The function block receives a UINT value at the data input OUT and converts it to the AUI adapter format upon arrival of the REQ event.

# ST_DEL_FB

![ST_DEL_FB](https://user-images.githubusercontent.com/116869307/214154809-ea8eaf7b-a851-4b0e-9cc9-2d7cdd14fcbd.png)

* * * * * * * * * *

## Introduction

The ST_DEL_FB function block is used to delete a function block instance of a specific function block type. This function block belongs to the category of reconfiguration services and enables the dynamic management of function block instances at runtime.

![ST_DEL_FB](ST_DEL_FB.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Event to request the deletion of a function block instance

### **Event Outputs**

- **CNF**: Event confirming that the function block instance has been deleted

### **Data Inputs**

- **QI** (BOOL): Event input qualifier
- **FB_NAME** (WSTRING): Name of the function block instance to be deleted
- **DST** (WSTRING): Destination where the function block instance must be deleted (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Event output qualifier
- **STATUS** (WSTRING): Service status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapter**

No adapter interfaces are available.

## Functionality

The ST_DEL_FB function block responds to the REQ event and attempts to delete the specified function block instance at the indicated destination. Upon successful execution, a CNF event with the corresponding status is output. The block supports various operating states and error handling.

## Technical Features

- Supports dynamic reconfiguration of function blocks
- Uses WSTRING data types for international character sets
- Provides detailed status feedback on the deletion process
- Implemented according to the IEC 61499-1 standard for structured services

## State Overview

The function block supports several service sequences:

- Normal Establishment
- Unsuccessful Establishment
- Request Confirmation
- Suppressed Request Inhibited
- Request Error
- Application-Initiated Termination
- Resource-Initiated Termination

## Application Scenarios

- Dynamic reconfiguration of control systems
- Resource management in distributed automation systems
- Runtime adaptation of function block architectures
- Maintenance and updates of automation systems

## ⚖️ Comparison with similar Function Blocks

Compared to static function blocks, ST_DEL_FB enables the dynamic management of function block instances at runtime. It differs from creation blocks through its specific deletion functionality, thus offering complementary functionality for complete lifecycle management.

## Conclusion

The ST_DEL_FB function block is an essential tool for systems requiring dynamic reconfiguration. Its robust error handling and detailed status feedback make it a reliable solution for managing function block instances in complex automation environments.

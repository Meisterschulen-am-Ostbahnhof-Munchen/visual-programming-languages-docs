# ST_CREATE_FB

![ST_CREATE_FB](https://user-images.githubusercontent.com/116869307/214154744-19129832-9477-4d2a-a6e6-11e55744ad45.png)

* * * * * * * * * *

## Introduction

The ST_CREATE_FB function block is used to dynamically create function block or resource instances during the runtime of an IEC 61499 system. This block enables the reconfiguration of automation systems by generating new function blocks based on specific FB types.

![ST_CREATE_FB](ST_CREATE_FB.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Event requesting the creation of a function block (FB) or resource instance

### **Event Outputs**

- **CNF**: Event confirming that the FB or resource instance has been created

### **Data Inputs**

- **QI** (BOOL): Event input qualifier
- **FB_NAME** (WSTRING): Name of the FB instance to be created
- **FB_TYPE** (WSTRING): FB type name
- **DST** (WSTRING): Destination where the FB or resource instance should be created (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Event output qualifier
- **STATUS** (WSTRING): Service status (RDY, UNSUPPORTED_TYPE, INVALID_OPERATION, INVALID_STATE)

### **Adapter**

No adapter interfaces are available.

## Functionality

The ST_CREATE_FB function block receives a request to create a new function block instance via the REQ event. The required parameters (FB_NAME, FB_TYPE, DST) are included in the request. After successful processing of the request, the function block returns a confirmation via the CNF event, which contains the status of the operation in the STATUS output.

## Technical Features

- Supports dynamic reconfiguration of IEC 61499 systems
- Uses WSTRING data types for international character set support
- Provides detailed status feedback for fault diagnosis
- Implemented as a structural service according to the IEC 61499-1 standard

## Status Overview

The function block has several service sequences:

- **normal_establishment**: Successful initialization
- **unsuccessful_establishment**: Failed initialization
- **request_confirm**: Successful request processing
- **request_inhibited**: Suppressed request
- **request_error**: Failed request processing
- **application_initiated_termination**: Application-initiated termination
- **resource_initiated_termination**: Resource-initiated termination

## Application Scenarios

- Dynamic expansion of automation systems
- Adaptive control systems that adjust to changing production requirements
- Modular systems Architectures where components are added at runtime
- Reconfigurable manufacturing systems

## ⚖️ Comparison with similar function blocks

Compared to static function blocks, ST_CREATE_FB offers the unique ability to create instances at runtime. While standard function blocks are defined at compile time, this block enables a flexible system architecture.

## Conclusion

The ST_CREATE_FB function block is an essential tool for developing dynamic and reconfigurable automation systems according to IEC 61499. Its ability to create function block instances at runtime makes it particularly valuable for applications requiring adaptability and flexibility.

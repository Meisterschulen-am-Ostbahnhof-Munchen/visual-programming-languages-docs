# GetInstancePath
![GetInstancePath](https://github.com/user-attachments/assets/325783e2-0c06-4d8f-bdf5-56508a4e6f25)
* * * * * * * * * *
## Introduction
The function block `GetInstancePath` is used to determine the instance path of the function block within the 4diac IDE. This path can be used, for example, for diagnostic purposes or for dynamic configuration. The function block is particularly useful in complex applications where precise identification of the instance location is required.
![GetInstancePath](GetInstancePath.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Service request. Triggers the determination of the instance path.

### **Event Outputs**
- **CNF**: Acknowledgement of the service request. Signals successful determination of the instance path.

### **Data Inputs**
- **Sep**: Separator character (CHAR) for the generated path. The default value is `'/'`.

### **Data Outputs**
- **Path**: The determined instance path as a STRING.

#### **Adapters**
No adapters available.

## Functionality
1. Upon receiving the `REQ` event, the function block begins determining its own instance path.

2. The path is formatted with the specified separator character (`Sep`).

3. The `CNF` event is triggered, and the determined path is output via the `Path` output.

## Technical Features
- The function block uses a service interface to communicate with the resource level.

## Technical Features - The default separator is `'/'`, but it can be customized by the user.

## State Overview
- **Idle**: Waiting for a `REQ` request.
- **Processing**: Determines the instance path and outputs it via `CNF`.

## Application Scenarios
- Diagnostics and Logging: Identifying the exact location of a function block instance in a complex application.
- Dynamic Configuration: Using the path to dynamically adjust parameters or behaviors.

## ⚖️ Comparison with Similar Function Blocks
- Unlike static path specifications, `GetInstancePath` allows for dynamic path determination, which is particularly advantageous in reusable or nested components.

## Conclusion

The `GetInstancePath`-FB is a useful tool for dynamically determining the instance path in 4diac applications. Its simple interface and flexible configuration make it ideal for diagnostic and configuration purposes.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

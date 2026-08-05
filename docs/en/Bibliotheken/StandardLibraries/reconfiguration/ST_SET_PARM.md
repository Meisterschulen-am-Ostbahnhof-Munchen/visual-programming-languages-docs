# ST_SET_PARM

![ST_SET_PARM](https://user-images.githubusercontent.com/116869307/214154843-5ee498fe-8e20-4dda-812a-f1f976ab28fe.png)

* * * * * * * * * *

## Introduction
The ST_SET_PARM function block is used to set parameters for data inputs of function blocks, resources, or device instances within a 4diac system. This function block enables the dynamic configuration of system parameters at runtime.

![ST_SET_PARM](ST_SET_PARM.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the process of setting a parameter. Associated with the data ELEM_NAME, ELEM_DATA_IN, PARM_VAL, DST, and QI.

### **Event Outputs**

- **CNF**: Confirms that the parameter was set successfully. Associated with the data STATUS and QO.


### **Data Inputs**

- **QI** (BOOL): Event input qualifier

- **ELEM_NAME** (WSTRING): Reference to element instance

- **ELEM_DATA_IN** (WSTRING): Reference to data input

- **PARM_VAL** (WSTRING): Parameter value

- **DST** (WSTRING): Destination where the parameter must be set (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Event output qualifier

- **STATUS** (WSTRING): Service status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapters**
No adapters available.



**Data Inputs** ## Functionality
Upon arrival of the REQ event, the ST_SET_PARM function block attempts to set the specified parameter value (PARM_VAL) for the specified data input (ELEM_DATA_IN) of the target instance (ELEM_NAME) at the specified destination (DST). Upon completion of the process, the CNF event is output with the corresponding status.


``` ## Technical Features
- Supports wide-string data types for all text-based parameters
- Provides detailed status feedback on the success or failure of the operation
- Enables configuration across resource boundaries
- Implemented as a reconfiguration service according to the IEC 61499-1 standard

## State Overview
1. **Idle State**: Waits for a REQ event
2. **Processing State**: Sets the parameter based on the input data
3. **Acknowledgement State**: Sends a CNF event with status information

## Application Scenarios
- Dynamic adjustment of system parameters during operation
- Configuration of function block parameters in distributed systems
- Automated parameterization in production plants
- Maintenance and optimization of control systems

## ⚖️ Comparison with Similar Function Blocks
Compared to static parameterization methods, ST_SET_PARM offers the ability to change parameters at runtime, enabling greater flexibility in adaptive control systems. Other configuration blocks typically only operate during the initialization phase.

## Conclusion
The ST_SET_PARM function block is an essential tool for the dynamic reconfiguration of 4diac systems. Its ability to set parameters at runtime makes it particularly valuable for applications requiring adaptability and flexibility. The clear interface definition and detailed status feedback ensure reliable integration into complex automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
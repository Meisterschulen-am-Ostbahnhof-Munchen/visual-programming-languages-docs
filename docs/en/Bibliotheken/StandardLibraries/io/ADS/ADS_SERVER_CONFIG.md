# ADS_SERVER_CONFIG

<img width="1348" height="238" alt="image" src="https://github.com/user-attachments/assets/3b924f75-67ac-48e2-9abf-411c3f4906fd" />

* * * * * * * * * *

## Introduction
The ADS_SERVER_CONFIG function block is used to configure ADS server connections in 4diac systems. It enables the initialization and parameterization of connection settings for ADS communication, which can be used in downstream I/O function blocks.


![ADS_SERVER_CONFIG](ADS_SERVER_CONFIG.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event - Starts the configuration of the ADS server

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Signals successful completion of the configuration

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Enables/disables initialization

- **FRIENDLY_NAME** (WSTRING): User-friendly server name for use in I/O function blocks

- **SERVER_ADS_ADDRESS** (WSTRING): ADS address of the server

- **ADS_PORT** (UINT): ADS port of the server

- **SERVER_IPV4_OR_HOSTNAME** (WSTRING): IPv4 address or hostname of the ADS server

### **Data Outputs**

- **QO** (BOOL): Event output qualifier - Indicates the initialization status

- **STATUS** (WSTRING): Service status information

### **Adapter**
No adapter interfaces are available.

## Functionality
The function block is activated by the INIT event and processes the provided configuration parameters. Upon successful processing, it outputs the INITO event and makes the configured parameters available to downstream ADS-IO function blocks. The STATUS output provides detailed information about the configuration process.


## ## Technical Features
- Uses WSTRING data types for international character support
- Supports both IPv4 addresses and hostnames for maximum flexibility
- Separate parameters for ADS address and network address enable complex network configurations

- Port configuration as UINT for numeric port specification

## State Overview
1. **Inactive**: Waiting for INIT event

2. **Configuration**: Processing input parameters

3. **Active**: Configuration completed successfully, parameters are available
4. **Error**: Configuration failed, STATUS contains error information

## Application Scenarios
- Initial system configuration in ADS-based automation systems
- Central management of ADS server connection parameters
- Dynamic reconfiguration of network settings
- Integration into larger I/O management systems

## ⚖️ Comparison with Similar Blocks
Compared to simple ADS I/O blocks, ADS_SERVER_CONFIG provides a central configuration option for multiple downstream blocks. It separates the configuration logic from the actual data communication, thus enabling reusable server settings.

## Conclusion
ADS_SERVER_CONFIG is an essential component for structured ADS communication in 4diac systems. Through centralized configuration management, it simplifies the maintenance and modification of network settings and promotes consistent connection parameters across various I/O function blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
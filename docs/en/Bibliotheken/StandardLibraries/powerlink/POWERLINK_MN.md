# POWERLINK_MN
* * * * * * * * * *
## Introduction
The POWERLINK_MN function block is used to configure the openPOWERLINK fieldbus. It acts as a Managing Node (MN) and initializes the network.
![POWERLINK_MN](POWERLINK_MN.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Initializes the service. Starts the configuration process.

### **Event Outputs**
- **INITO**: Confirms initialization. Indicates whether the start was successful.

### **Data Inputs**
- **QI** (BOOL): Qualifier for the INIT input (TRUE = Start, FALSE = Stop).
- **CDC_CFG** (STRING): Device Configuration.
- **APP_CFG** (STRING): Application Configuration.
- **DEV_NAME** (STRING): Name of the Ethernet device to be used for POWERLINK (e.g., "eth0").

### **Data Outputs**
- **QO** (BOOL): Qualifier for the INITO output.
- **STATUS** (STRING): Service status information.

## Functionality
This block initializes the openPOWERLINK stack on the specified Ethernet interface (`DEV_NAME`). The configuration files for the device (`CDC_CFG`) and application (`APP_CFG`) are loaded.

## Application Scenarios
- Central control of a POWERLINK network.
- Master component in a real-time Ethernet system.

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | (c) 2011 AIT |

License | EPL-2.0 |

Version | 3.0 (2025-04-14, Patrick Aigner) |

4diac Package | powerlink |

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
# INI_AX2
![INI_AX2](./INI_AX2.svg)
* * * * * * * * * *
## Introduction
The INI_AX2 function block is used to read and write real data from a settings.ini file via an AX2 adapter. It combines the INI block with a bidirectional AX2 adapter to read values from or write them back to a configuration file. Initialization is performed via the INIT event, where the section and key are specified. The read value is offered via the adapter, and a write operation is triggered via the adapter event.
## Interface Structure

### **Event Inputs**

| Name | Description |

|------|--------------|

| INIT | Initialization event to start the read operation. Expects the parameters QI, SECTION, KEY, and DEFAULT_VALUE. |

### **Event Outputs**

| Name | Description |

|------|--------------|

| INITO | Initialization confirmation. Sent after the read operation is complete. Status information is available via QO and STATUS. |

### **Data Inputs**

| Name | Type | Description |

|------|-----|--------------|

| QI | BOOL | Input qualifier for controlling processing. |

| SECTION | STRING | Name of the section in the settings.ini file. |

| KEY | STRING | Name of the key within the section. |

| DEFAULT_VALUE | BOOL | Default value read if the key is not present in the file. Default: FALSE. |

### **Data Outputs**

| Name | Type | Description |

|------|-----|--------------|

| QO | BOOL | Output qualifier, indicates successful processing. |

| STATUS | STRING | Service status message (e.g., error messages). |

### **Adapters**

| Name | Type | Description |

|------|-----|--------------|

| VAL | adapter::types::bidirectional::AX2 | Bidirectional adapter for exchanging values. This adapter provides the read value as an output (DO1) and receives a write value as an input (DI1). |

## Functionality

The INI_AX2 function block contains an internal INI function block (eclipse4diac::storage::INI) that performs the actual file operation. The network connections implement the following processes:

- Upon arrival of INIT, QI, SECTION, KEY, and DEFAULT_VALUE are forwarded to the INI function block.
- The INI function block performs a read operation and passes the result (via VALUE) to the adapter output (VAL.DI1).
- Simultaneously, after a successful read, the GET event is triggered, which activates the adapter input (VAL.EI1) to transmit the value.
- A write operation is initiated as soon as the adapter sends an EO1 event. This event triggers the SET event on the INI function block, setting the value received via VAL.DO1 as the new VALUE.
- The INI block confirms the write operation with SETO and sends this back to the adapter (VAL.EI1).
- The QO and STATUS outputs are directly taken from the INI block.

Thus, read and write access to the settings.ini file can be controlled via the AX2 adapter.

## Technical Features
- The block uses a bidirectional AX2 adapter that can both send and receive values.
- A BOOL value is used as the default, although the comment indicates REAL data. The actual value type is determined by the adapter.
- The internal INI block is part of the eclipse4diac standard library for file access.
- The connections in the FBNetwork are configured so that event control is synchronized between read and write operations.

## State Overview

The block itself does not have explicit states, as it is implemented as a pure network of subordinate blocks. The state logic is determined by the internal INI block and the adapter. Typical states are:

- **Initialization**: Waiting for an INIT event.
- **Read**: Processing the read operation via the INI block.
- **Write**: Processing a write command via the adapter.
- **Wait**: After completing an operation, waiting for the next event.

## Application Scenarios
- Reading configuration parameters from an INI file in an automation application, where the values are passed to other components via an AX2 adapter.
- Writing modified parameters back to the file, e.g., after user input or an algorithm.
- Combining with other blocks for persistent storage of settings in an IEC 61499 system.

## Comparison with Similar Blocks
- The simple **INI** block offers direct read/write access to INI files, but without adapter connectivity. INI_AX2 extends this with a standardized AX2 interface for value exchange.

Other memory blocks, such as **CSV** or **JSON** blocks, serve different file formats; INI_AX2 is specific to the INI format with a bidirectional adapter.

## Conclusion
The INI_AX2 function block is a useful component for IEC 61499 applications that require easy access to configuration files via an AX2 adapter. By encapsulating the INI block and using event-driven control, it enables both read and write operations to a settings.ini file. The use of a bidirectional adapter allows for flexible integration into complex networks.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

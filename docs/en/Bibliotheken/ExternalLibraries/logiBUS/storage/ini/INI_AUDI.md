# INI_AUDI
![INI_AUDI](./INI_AUDI.svg)
* * * * * * * * * *
## Introduction
The **INI_AUDI** function block enables reading and saving UDINT data from a `settings.ini` file. Access to the file is implemented via an internal `INI` function block. Communication with the environment is handled via two **AUDI adapters** (unidirectional), implemented as a plug (`AUDI_OUT`) and a socket (`AUDI_IN`). This allows for modular integration with other function blocks that use the same adapter type.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|-------|-------|-----------------------------------|

| INIT | EInit | Service Initialization |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|----------------------------------|

| INITO | EInit | Initialization Confirm |

### **Data Inputs**

| Name | Type | Comment |

|----------------|--------|-----------------------------------------------------|

| QI | BOOL | Event Input Qualifier |

| SECTION | STRING | Section name in settings.ini |

| KEY | STRING | Key name in settings.ini |

| DEFAULT_VALUE | UDINT | Fallback value if the key is not found |

### **Data Outputs**

| Name | Type | Comment |

|--------|--------|------------------|

| QO | BOOL | Output Qualifier |

| STATUS | STRING | Service Status |

## **Adapter**

| Name | Type | Direction | Comment |

|----------|----------|----------------|---------------------------------|

| AUDI_OUT | AUDI | Plug (Output) | Output of the read value |

| AUDI_IN | AUDI | Socket (Input) | Input of the value to be stored |

## Functionality
This function block works in conjunction with the internal `INI` function block. The basic sequence is:

1. **Initialization (`INIT` event)**

- The input data associated with `INIT` (`QI`, `SECTION`, `KEY`, `DEFAULT_VALUE`) is forwarded to the internal `INI` module.
- `INI` is started and acknowledged with `INITO`.

2. **Reading a Value**

- After INIT confirmation, the `GET` command of the `INI` block is automatically triggered.
- The read value (or `DEFAULT_VALUE`) is output to the `AUDI_OUT.D1` adapter via `INI.VALUEO`.
- Simultaneously, the event `AUDI_OUT.E1` is sent to notify the connected block.

3. **Writing a Value**

- If the adapter `AUDI_IN` receives an event `E1` with a data value `D1`, `INI_AUDI` forwards this to the `INI` block as a `SET` command.
- The internal `INI` block stores the value in the INI file under the specified section and key and acknowledges it with `SETO`.
- The acknowledgment event is output via `AUDI_OUT.E1`.

... 4. **Feedback**

- The status outputs `QO` and `STATUS` are directly inherited from the internal `INI` block and are available at the output.

## Technical Features
- The block uses the **adapter `adapter::types::unidirectional::AUDI`**, which is specifically designed for the directed communication of values and events.
- The data is processed as **UDINT (Unsigned Double Integer)**, enabling efficient storage and transmission.
- The internal `INI` block is from the `eclipse4diac::storage` library and supports standard INI file formats.

## Technical Features
- The block uses the **adapter `adapter::types::unidirectional::AUDI`**, which is specifically designed for the directed communication of values and events. - The fallback mechanism via `DEFAULT_VALUE` ensures that a defined value is returned even if entries are missing in the INI file.

## State Overview
Since the function block operates in an event-driven manner, the following logical states result:

- **Idle**: Waiting for a `INIT` event.
- **Initialize**: After `INIT` – internal forwarding to the INI function block.
- **Read** (automatically after `INITO`): The `INI` function block executes a GET command.
- **Write**: Upon receiving an event via `AUDI_IN.E1`.
- **Confirm**: Output of the corresponding OUT event and update of the status outputs.

The function block is stateless in the sense of a continuous data flow; each action is triggered by an event and terminates synchronously.

## Application Scenarios
- **Configuration Management** in automation systems: Reading settings (e.g., limits, parameters) from a central `settings.ini` and writing back changed values.
- **Adapter-based sensor/actuator coupling**: Connecting a function block that reads or sets values via the AUDI adapter without having to implement the file access logic itself.
- **Persistent Data Storage**: Saving counter readings or machine states to an INI file while simultaneously communicating via standardized adapters.

## Comparison with Similar Function Blocks
- **Compared to a pure `INI` function block**: `INI_AUDI` encapsulates the adapter communication and offers a higher level of abstraction. The user does not have to directly handle events and data connections between multiple components.
- **Compared to Function Blocks with Other Data Types**: This function block is specifically designed for `UDINT`. Separate versions are required for other data types (e.g., `STRING`, `REAL`). However, the basic structure remains the same.
- **Advantage**: By using adapters (AUDI), the function block can easily be replaced with other interfaces, provided they implement the same adapter type.

## Conclusion

The `INI_AUDI` function block provides a compact and reusable solution for reading and writing UDINT values from an INI file, connecting to the environment via standardized AUDI adapters. Its clear separation of initialization, reading, and writing, along with the inclusion of a fallback value, makes it particularly suitable for robust configuration and data storage tasks in automation environments. Its simple structure facilitates integration into complex 4diac networks.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

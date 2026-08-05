# INI_AS

![INI_AS](./INI_AS.svg)

* * * * * * * * * *
## Introduction
The function block **INI_AS** is used to load and save SINT data from a `settings.ini` file. It accesses a configuration value via a section name (`SECTION`) and a key (`KEY`). The value can be both read and written via the adapter interface `AS`. The block encapsulates the internal `INI` function block and extends it with a standardized adapter interface.

## Interface Structure
### **Event Inputs**

| Event | Type | With Vars | Description |

| Event | Type | With Vars | Description | |----------|------|----------|--------------|

| `INIT` | EInit | QI, SECTION, KEY, DEFAULT_VALUE | Service Initialization: Reads the value from the INI file and outputs it via the adapter. |

### **Event Outputs**

| Event | Type | With Vars | Description |

|----------|------|-----------|--------------|

| `INITO` | EInit | QO, STATUS | Confirmation of initialization. |

### **Data Inputs**

| Name | Data Type | Description |
|---------------|----------|--------------|

| `QI` | BOOL | Input qualifier (e.g., enable). |

| `SECTION` | STRING | Name of the section in the INI file. |

| `KEY` | STRING | Name of the key within the section. |

| `DEFAULT_VALUE` | SINT | Value returned if the key is not present in the INI file. |

### **Data Outputs**

| Name | Data Type | Description |

| |----------|----------|--------------|

| `QO` | BOOL | Output qualifier (indicates successful operation). |

| `STATUS` | STRING | Status message (e.g., error messages). |

### **Adapter**

| Name | Type | Direction | Description |

|-------------|---------------------|----------|--------------|

| `AS_IN` | `adapter::types::unidirectional::AS` | Input (Socket) | Receives a new value to be stored (SET operation). |

| `AS_OUT` | `adapter::types::unidirectional::AS` | Output (Plug) | Outputs the currently read or stored value (GET operation). |

## Functionality

1. **Initialization and First Read (INIT Event)**

The parameters `SECTION`, `KEY`, and `DEFAULT_VALUE` are passed via the `INI` event. The internal `INI` block is started, reads the value from `settings.ini`, and outputs it via the adapter output `AS_OUT`. Simultaneously, the `INITO` event is triggered, reporting the completion of the initialization.

Subsequently (possibly within the same cycle), a `GET` event is automatically executed on the `INI` block, so that the read value is immediately available at the adapter.

2. **Writing a Value (via the Adapter Input)**

A new value (event `E1` and data `D1`) can be sent to the block via the socket `AS_IN`. This event is forwarded to the `SET` input of the internal `INI` block, which saves the value to the INI file. After successful saving, the `SETO` event of the `INI` block is triggered, which in turn serves the adapter output `AS_OUT` (event `E1`) and outputs the saved value via `D1`.









... 3. **Feedback**

The internal `INI` module provides the output signals `QO` and `STATUS`, which are directly routed to the corresponding outputs of the `INI_AS` module.

## Technical Features

- **Adapter Interface `AS`**: The module uses a unidirectional adapter (`adapter::types::unidirectional::AS`). This enables standardized connectivity to other modules that support the same adapter type.

- **Data Type SINT**: The read and stored value is of the "Short Integer" (SINT, 8-bit) type. This makes the module particularly suitable for small integer configuration values.

- **Reuse of the `INI` block**: All logic for accessing the INI file is taken over from the proven `eclipse4diac::storage::INI` block. The `INI_AS` block encapsulates this and extends the adapter interface.

- **Automatic GET after INIT**: After initialization, a read operation is started immediately, so the current value is available at the adapter output without a separate event.

## State Overview
The block does not have an explicit state machine (ECC). Its behavior is controlled purely via event chaining within the internal FB network:

- After `INIT`, the sequence is: INIT of the `INI` block → INITO → GET (automatic) → VALUO at the adapter output.

- After a SET event from the adapter input: SET of the `INI` block → SETO → adapter output with the new value.

## Application Scenarios

- **Persistent Configuration**: Saving and reading settings such as thresholds, mode flags, or device addresses in a `settings.ini` block.

- **Parameterization of Control Applications**: When a PLC or other automation system needs to load or modify values from a configuration file at runtime.

- **Adapter-Based Communication**: Integration into a higher-level adapter structure that groups several such read/write blocks.


## Comparison with Similar Function Blocks

- **INI_STRING, INI_INT, INI_BOOL**: These function blocks also use the internal `INI` function block, but support different data types (STRING, INT, BOOL) and often have a different interface structure (no adapters). The `INI_AS` function block offers a uniform and reusable interface through its adapter.

- **Direct `INI` Function Block**: The `INI` function block itself has several event inputs (INIT, GET, SET) and requires manual wiring of read and write operations. The `INI_AS` simplifies handling by standardizing typical usage (reading on startup, writing via adapters).


## Conclusion

The function block `INI_AS` is a convenient building block for persistently reading and writing SINT values from an INI file. Its adapter interface allows for easy integration into existing architectures and reduces wiring effort. It is particularly suitable for configuration tasks where a single integer value needs to be cached.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```
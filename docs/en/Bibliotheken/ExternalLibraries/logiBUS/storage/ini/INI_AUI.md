# INI_AUI

![INI_AUI](./INI_AUI.svg)

* * * * * * * * * *
## Introduction

The function block `INI_AUI` is used to read and store **UINT data** (more precisely: `UDINT` values) from a `settings.ini` file. The parameters **Section** and **Key** determine which value is read. Additionally, a **Default Value** can be specified if no entry exists in the INI file. The function block offers both direct access via its inputs and an **Adapter Interface (AUI)** for unidirectional communication with other function blocks.
## Interface Structure

### **Event Inputs**

| Event | Type | Short Description |
|----------|-------|---------------------------------------------------------------|
| INIT | EInit | Service Initialization: Triggers loading the value from the INI file |

### **Event Outputs**

| Event | Type | Short Description |
|----------|-------|--------------------------------------------------------------|
| INITO | EInit | Initialization Acknowledgement (sent after completion of read/write operations) |

### **Data Inputs**

| Name | Type | Short Description |
|----------------|--------|---------------------------------------------------------------|
| QI | BOOL | Qualifier for the event input (enables processing) |
SECTION | STRING | Name of the section in `settings.ini` (e.g., `[MySection]`) |
KEY | STRING | Key name within the section |
DEFAULT_VALUE | UDINT | Value returned if no entry exists |

### **Data Outputs**

| Name | Type | Short Description |
|--------|--------|--------------------------------------------------------------|
QO | BOOL | Qualifier for the event output (indicates successful execution) |
STATUS | STRING | Status message (e.g., Error or Success) |

### **Adapters**

| Direction | Adapter Type | Short Description |
|-----------|-------------------------------------|---------------------------------------------------------------------------------|
| Plug | `adapter::types::unidirectional::AUI` | **Output (OUT):** Provides the read/written value via the adapter |
| Socket | `adapter::types::unidirectional::AUI` | **Input (IN):** Receives the value to be stored via the adapter |

## Functionality

The `INI_AUI` function block encapsulates an internal `INI` function block (`eclipse4diac::storage::INI`). The essential processes are:

1. **Reading a Value**
- An **INIT** event at the input triggers the internal `INI.INIT`.
- The data `QI`, `SECTION`, `KEY`, and `DEFAULT_VALUE` are forwarded to the `INI` function block.
- After successful processing, `INI.INITO` sends the confirmation event and internally triggers `INI.GET` to load the value from the file.
- The read value appears at `INI.VALUEO` and is output via the **AUI_OUT** adapter (plug) as `D1`.
- Simultaneously, `QO` and `STATUS` are taken from the internal function block.
2. **Writing a Value**
- An event at the **AUI_IN.Socket** (via the input adapter) triggers the internal `INI.SET`.
- The value provided via the adapter (D1) is passed to `INI.VALUE` and written to `settings.ini`.
- After writing, `INI.SETO` sends the confirmation event, which is output via the **AUI_OUT.Plug** as `E1`.
- Here too, the outputs `QO` and `STATUS` are updated.

> **Note:** The adapter **AUI_IN** acts as a socket (receiving), and **AUI_OUT** as a plug (providing). Both use the same unidirectional AUI type.

## Technical Features

- **Adapter-based communication:** The function block enables the exchange of configuration data via a unidirectional adapter (AUI) without requiring direct data connections. This simplifies module communication in distributed systems.
- **Dual operation:** The value can be set via the classic data inputs (`SECTION`, `KEY`, `DEFAULT_VALUE`) as well as via the adapter (`AUI_IN.D1`).
- **Default Value:** If an entry is missing in the INI file, `DEFAULT_VALUE` is used – this prevents undefined states.
- **Status Information:** The user can check the success of each operation via `STATUS` and `QO`.

## State Overview

The function block `INI_AUI` does **not have its own state machine**. The entire process control is implemented by the integrated `INI` function block and the defined event connections (e.g., INIT → INI.INIT, INI.INITO → INITO, INI.INITO → INI.GET). Therefore, the function block operates strictly event-driven and executes read/write operations sequentially.

## Application Scenarios

- **Parameter Management** in modular automation systems where multiple components access shared configuration data via an adapter.
- **Initialization** of control functions with a default value that can be overwritten from an INI file if needed.
- **Exchange of settings** between different function blocks connected via the AUI adapter (e.g., a higher-level manager block and multiple worker blocks).

## Comparison with Similar Blocks

- **`INI` (Basic Function Block):** The `INI_AUI` extends the simple `INI` function block with a standardized adapter interface. While the `INI` only has direct inputs/outputs, the `INI_AUI` allows loose coupling via AUI.
- **Other memory blocks (e.g., `Memory`, `Persist`):** These usually work with internal variables or files, but often lack an adapter interface and dedicated `settings.ini` integration.

## Conclusion

The `INI_AUI` function block is a flexible solution for reading and saving configuration values in a `settings.ini`-file. By combining direct data inputs and a unidirectional AUI adapter interface, it is ideally suited for both simple initialization tasks and modular, adapter-based system architectures. The integration of a default value and clear status feedback increase the robustness and maintainability of the control software.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

# AULI_MUX_4
![AULI_MUX_4](./AULI_MUX_4.svg)

* * * * * * * * * *
## Introduction
The function block **AULI_MUX_4** is a generic multiplexer for the adapter interface `adapter::types::unidirectional::AULI`. It selects exactly one of four inputs (IN1 to IN4) based on a numeric index **K** and forwards its data to the output **OUT**. This function block belongs to the library of HR Agrartechnik GmbH and was developed for use in the IEC 61499-1 standard environment.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|---------------|

| **REQ** | Trigger to set the index **K** and perform the multiplex selection. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirmation that the selection is complete and the output has been updated. |

### **Data Inputs**

| Name | Type | Description |

|------|-------|--------------|

| **K** | UINT | Selection index (value range 0…3). Determines which input is connected to the output. |

### **Data Outputs**

No direct data outputs. Output is via the **adapter output** (plug).

### **Adapter**

| Category | Name | Type (Interface) | Description |

|-----------|------|---------------------|--------------|

**Plugs** (Output) | **OUT** | `adapter::types::unidirectional::AULI` | Output adapter that passes on the selected input. |

**Sockets** (Inputs) | **IN1** | `adapter::types::unidirectional::AULI` | First input (selected when K=0). |

**IN2** | `adapter::types::unidirectional::AULI` | Second input (K=1). |

**IN3** | `adapter::types::unidirectional::AULI` | Third input (K=2). |

**IN4** | `adapter::types::unidirectional::AULI` | Fourth input (K=3). |

**IN1** | `adapter::types::unidirectional::AULI` | Fourth input (K=3).
## Functionality

1. The function block waits for an event at the **REQ** input.

2. Upon receiving **REQ**, the current value of the data input **K** is read.

3. Depending on **K**, the corresponding socket input (IN1 to IN4) is switched to the plug output **OUT**.

* K = 0 → IN1
* K = 1 → IN2
* K = 2 → IN3
* K = 3 → IN4
4. After successful switching, the **CNF** event is sent to acknowledge execution.

## Technical Features
- **Generic Type**: The function block is declared as a generic function block (`GenericClassName` = `'GEN_AULI_MUX'`) and can therefore be reused in different projects with different AULI adapter instances.
- **TypeHash**: Contains a placeholder (`''`) that is replaced by the runtime environment during concrete instantiation.
- **Package Dependency**: The module imports the type `eclipse4diac::core::TypeHash` and uses namespaces from `adapter::selection::unidirectional`.
- **Simplest Implementation**: No complex state machine; the logic is purely combinatorial with event-driven updates.

## State Overview

The AULI_MUX_4 does not have an explicit state machine in the XML. Its behavior is event-driven:

| State (implicit) | Description |

|--------------------|--------------|

| **Idle** | Waiting for a REQ event. The adapter inputs are inactive. |

| **Selection** | After REQ, K is evaluated and the corresponding input is switched to the output.

After sending **CNF**, the function block returns to the idle state.

## Application Scenarios
- **Data Source Switching**: Selection between four measured values or control signals provided via AULI adapters.
- **Prioritized Signal Passing**: Implementation of simple priority logic through targeted index selection.
- **Test and Diagnostic Systems**: Switching between normal operation and test signals.

## Comparison with Similar Function Blocks
- **Standard MUX (e.g., E_MUX)**: Usually works with simple data types (BOOL, REAL). The AULI_MUX_4 is specifically designed for the AULI adapter interface and enables the transfer of complex, structured adapter data.
- **DEMUX (Demultiplexer)**: Distributes a signal to multiple outputs – reverse functionality.

**AULI_MUX_4** is more compact than a generic MUX with many inputs/outputs because it is limited to four channels.

## Conclusion

The **AULI_MUX_4** is a lean yet effective function block for selecting one of four AULI signals. Its generic declaration facilitates reuse in various automation projects. Its clear, event-driven interface allows it to integrate seamlessly into IEC 61499 applications and makes it particularly suitable for applications requiring flexible switching between signal sources.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

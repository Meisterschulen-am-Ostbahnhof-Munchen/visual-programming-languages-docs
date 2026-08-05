# AE_MUX_3
![AE_MUX_3](./AE_MUX_3.svg)
* * * * * * * * * *
## Introduction
The function block **AE_MUX_3** is a generic multiplexer for the AE adapter type (unidirectional). It selects one of three analog or other AE signal inputs and routes it to a common output. The selection is made via a numeric index (K). This block is particularly suitable for applications where different signal sources need to be switched to a subsequent processing unit depending on a condition.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |

|------|----------|---------------|

| REQ | Event | Starts the switching to the input specified via `K`. |

### **Event Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| CNF | Event | Confirms that the switch to the selected input is complete. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| K | UINT | Index of the input to be selected: 0 → IN1, 1 → IN2, 2 → IN3. |

### **Data Outputs**
None.

### **Adapter**
**Output (Plug)**

| Name | Type | Description |

|------|----------------------------------|--------------|

| OUT | adapter::types::unidirectional::AE | Output that switches the selected input (IN1/IN2/IN3). |

**Inputs (Sockets)**

| Name | Type | Description |

|------|----------------------------------|--------------|

| IN1 | adapter::types::unidirectional::AE | First AE input – is connected to OUT when K=0. |

| IN2 | adapter::types::unidirectional::AE | Second AE input – is connected to OUT when K=1. |

| IN3 | adapter::types::unidirectional::AE | Third AE input – is connected to OUT when K=2. |

## Functionality

1. The function block waits for an event at the **REQ** input.

| 2. Upon receipt of REQ, the current value of index **K** is evaluated:

- K = 0 → Adapter **IN1** is switched to output **OUT**.
- K = 1 → Adapter **IN2** is switched to **OUT**.
- K = 2 → Adapter **IN3** is switched to **OUT**.

3. After successful switching, the **CNF** event is output to signal the completion of the operation to the calling function block.

The switching occurs immediately – there is no additional delay or intermediate states.

## Technical Features
- **Generic Function Block:** The function block has the attribute `GenericClassName = 'GEN_AE_MUX'` and can therefore be used as a generic function block in the 4diac IDE. This allows for flexible adaptation to different application execution units (AEs).
- **License:** The function block is provided under the **Eclipse Public License 2.0**. It is open source and may be used, modified, and distributed in accordance with the license terms.
- **Adapter Type Used:** Both the input sockets and the output plug use the `adapter::types::unidirectional::AE` type. This adapter only transmits values in one direction (from the socket to the plug) and is suitable for simple analog or binary signals.

## State Overview
The **AE_MUX_3** does not have an explicit state machine (ECA). Its operation is purely event-triggered:

- In its idle state, the module waits for a REQ event.
- After REQ, the module switches to a new state, followed by CNF.

It then returns to its idle state. There are no persistent internal states.

## Application Scenarios
- **Sensor Selection:** In a machine control system, different sensors (e.g., pressure sensors) are to be evaluated depending on the operating mode. With AE_MUX_3, the appropriate sensor can be switched to the controller via an index.
- **Signal Routing:** In a modular system, analog AE signals from various modules are collected and routed via a common bus. This function block enables dynamic selection.
- **Test and Diagnostic System:** For manual testing, switching between the normal operating signal and a test signal is possible without changing the wiring.

## Comparison with Similar Function Blocks
- **AE_MUX_2:** Offers only two inputs (K=0,1) and is more compact when only two sources are required.
- **AE_MUX_N:** An expandable multiplexer configured via a list of inputs (e.g., an array). AE_MUX_3, on the other hand, has three fixed inputs, offering a simpler structure and lower complexity.
- **MUX (for basic data types):** The standard library contains multiplexers for simple types (BOOL, INT, REAL). The AE_MUX_3 is specifically designed for adapters of type `AE` and is therefore suitable for signal paths that carry multiple values or structured data.

## Conclusion
The **AE_MUX_3** is a simple yet robust multiplexer for three AE signals. Its index selection via REQ and K makes it easy to integrate into control logic. Its generic nature and clear separation of event and data paths make it a useful tool for modular, event-driven automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
# AIWS_MUX_5
![AIWS_MUX_5](./AIWS_MUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **AIWS_MUX_5** is a generic multiplexer for AIWS adapter data. It selects one of five AIWS inputs (IN1…IN5) connected to the **Socket** and forwards the value to the **Plug** output OUT. The selection is made using the integer index **K** (0-4), which is inherited from an event at the **REQ** input. The block confirms the executed selection with a **CNF** event.
## Interface Structure
### **Event Inputs**

| Event | With Variable | Description |
|----------|--------------|--------------|
| **REQ** | K | Takes the index K and updates the output OUT. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Confirms the index take and the update of OUT. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| **K** | UINT | Selection index (0…4). |

### **Data Outputs**
No direct data outputs; the output data is provided via the **OUT** adapter.

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| **Plug** | OUT | `adapter::types::unidirectional::AIWS` | Output that provides the value of the selected input. |
| **Socket** | IN1 | `adapter::types::unidirectional::AIWS` | Input 1 (Index 0) |
| **Socket** | IN2 | `adapter::types::unidirectional::AIWS` | Input 2 (Index 1) |
| **Socket** | IN3 | `adapter::types::unidirectional::AIWS` | Input 3 (Index 2) |
| **Socket** | IN4 | `adapter::types::unidirectional::AIWS` | Input 4 (Index 3) |
| **Socket** | IN5 | `adapter::types::unidirectional::AIWS` | Input 5 (Index 4) |

## Functionality
The function block (FB) operates in an event-driven manner:

1. A rising edge on the **REQ** event takes over the current value of **K**.

2. Depending on **K** (0…4), the corresponding socket **(IN1…IN5)** is selected and its data is forwarded to the **OUT** plug.

3. After a successful switchover, the **CNF** event is output.

If **K** is outside the valid range (0…4), the behavior remains undefined; typically, no selection is made or the output is not updated.

## Technical Features
- The FB is declared as a **generic block** (`GenericClassName = 'GEN_AIWS_MUX'`), i.e., It can be parameterized in an IEC 61499 environment for different adapter types or channel counts.
- The interface uses only **unidirectional AIWS adapters** – this enables a clear separation between input and output data flows.
- No internal states or timing behaviors are defined; the selection is purely combinatorial with each REQ call.

## State Overview
The function block (FB) does not have an explicit state machine. The process is event-driven and deterministic:

- **Waiting for REQ** → on REQ: perform selection, send CNF.
- The function block remains active after execution and ready for the next REQ event.

## Application Scenarios
- **Sensor Multiplexing** in agricultural technology: Selection of one of five analog sensors (e.g., pressure, temperature, pH value) via a central index.
- **Signal switching** in control systems where multiple AIWS sources exist, but only one is to be processed further.
- **Test and diagnostic modules** that alternately query different inputs.

## Comparison with similar modules
Compared to a classic **MUX** module (e.g., with simple `ANY` data ports), **AIWS_MUX_5** works exclusively with the specialized **AIWS adapter**. This increases type reliability and simplifies integration into existing AIWS-based components. A disadvantage is the fixed number of five inputs; for other channel numbers, the generic parameter would have to be adjusted or a different function block would have to be used.

## Conclusion
The **AIWS_MUX_5** is a compact, event-driven multiplexer for five AIWS signals. It is particularly suitable for use in modular control systems where flexible and type-safe switching between analog input values is required. The generic declaration allows for easy adaptation to different requirements.

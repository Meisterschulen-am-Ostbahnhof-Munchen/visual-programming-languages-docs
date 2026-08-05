# ADI_MUX_3
![ADI_MUX_3](./ADI_MUX_3.svg)
* * * * * * * * * *
## Introduction
The function block **ADI_MUX_3** is a generic multiplexer (MUX) for three input signals. It was developed for use in automation systems and selects one of the three connected adapter inputs based on an index value and forwards its signal via the output. The block is implemented as a generic FB and is particularly suitable for flexible signal switching in control applications. Copyright HR Agrartechnik GmbH (2026).
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| REQ | Event | Signals a new index request. Evaluated with the data input **K**. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation that the selected input has been switched to the output. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0, 1, 2) for selecting the active input. |

### **Data Outputs**
- (none)

### **Adapters**

| Name | Direction | Type | Comment |

|------|----------|-----|-----------|

| OUT | Plug | adapter::types::unidirectional::ADI | Output signal; IN1 corresponds to K=0, IN2 to K=1, and IN3 to K=2. |

| IN1 | Socket | adapter::types::unidirectional::ADI | First input value (K=0). |

| IN2 | Socket | adapter::types::unidirectional::ADI | Second input value (K=1). |

| IN3 | Socket | adapter::types::unidirectional::ADI | Third input value (K=2). |

## Functionality
The function block operates as a 3-to-1 multiplexer. Upon the arrival of a **REQ** event, the current value of the data input **K** is read. Based on this index (0, 1, or 2), the signal of the corresponding socket adapter (IN1, IN2, or IN3) is passed through to the plug adapter **OUT**. The **CNF** event is then triggered to acknowledge the successful operation.

``` The input and output signals are transmitted via the standardized **ADI** adapter (unidirectional), which can be configured for any analog or digital values.

## Technical Features
- **Generic Function Block**: The function block is implemented as a generic function block (GenericClassName `'GEN_ADI_MUX'`) and can be adapted to different data types during instantiation.
- **Pure Adapter-Based Communication**: No separate data inputs/outputs are used; all signals are transmitted via the ADI adapters.
- **Simple Index Handling**: The **K** index of type UINT allows selection from three possible sources; values greater than 2 are not specified and should be avoided in the application.

## State Overview
Since the XML does not contain an explicit state machine (ECC), the function block operates in an event-driven manner according to the following simple sequence:

1. **IDLE** – Waiting for a **REQ** event. 2. **SELECT** – Upon arrival of **REQ**, the index **K** is evaluated and the corresponding input is switched to **OUT**.

3. **CONFIRM** – Sending the **CNF** event and returning to the IDLE state.

This sequence repeats with each new **REQ** event.

## Application Scenarios
- **Sensor Multiplexing**: Selection between three different sensors (e.g., temperature, pressure, speed) via a common measurement adapter.
- **Signal Switching in Agricultural Engineering**: Switching between different analog input channels in control units for tractors or harvesters.
- **Configurable Channel Selection**: Flexible routing of control data in modular automation systems.

## Comparison with Similar Components

| Component | Number of Inputs | Special Feature |

|----------|-----------------|--------------|
| ADI_MUX_2 | 2 | Simpler 2-to-1 multiplexer function. |

| ADI_MUX_3 | 3 | The function block described here. |

| ADI_MUX_4 | 4 | Extended version with four inputs. |

Compared to a generic `MUX` function block (with standard data types), the adapter variant offers a clearer interface definition and facilitates the reuse of signal configurations.

## Conclusion
The **ADI_MUX_3** is a compact, generic multiplexer for three adapter inputs. Its clear event-driven operation and the use of ADI adapters make it ideal for modular automation solutions where signals need to be switched efficiently. The simple interface and generic nature allow for flexible adaptation to various applications.

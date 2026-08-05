# AE_SPLIT_4
![AE_SPLIT_4](./AE_SPLIT_4.svg)

* * * * * * * * * *
## Introduction
The function block **AE_SPLIT_4** distributes an incoming event from a unidirectional **AE adapter** to four identical output adapters. It is executed as a generic function block (Generic FB) and can therefore be used for any data type of the adapter. The distribution occurs without delay or state change – the incoming event is forwarded to all four outputs simultaneously.
## Interface Structure
### **Event Inputs**
The function block has no explicit event inputs. Event control is handled exclusively via the **IN** socket (see section Adapter).

### **Event Outputs**
The function block has no explicit event outputs. Event propagation is handled via the **OUT1** to **OUT4** plugs (see section Adapter).

### **Data Inputs**
None.

### **Data Outputs**
None.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket (Input) | **IN** | `adapter::types::unidirectional::AE` | Receives a unidirectional adapter event (event + associated data). |

| Plug (Output) | **OUT1** | `adapter::types::unidirectional::AE` | First output – receives the same event and data as the input. |

| Plug (Output) | **OUT2** | `adapter::types::unidirectional::AE` | Second output. |

| Plug (Output) | **OUT3** | `adapter::types::unidirectional::AE` | Third output. |

Plug (Output) | **OUT4** | `adapter::types::unidirectional::AE` | Fourth output. |

## Functionality
As soon as an event from the AE adapter is received at socket **IN** (with all data associated with that event), this event is immediately and simultaneously passed on to all four plugs **OUT1**, **OUT2**, **OUT3**, and **OUT4**. The output is simultaneous – there are no priorities or sequences. Due to the generic design of the function block, the data types of the adapters are freely selectable (e.g., `INT`, `REAL`, `BOOL`, etc.), as long as all participating adapters use the same data type.

## Technical Features
- **Generic Function Block** – The function block is implemented as a generic type (`GenericClassName = 'GEN_AE_SPLIT'`). This allows the specific data type of the adapter to be defined during the project planning phase.
- **Unidirectional Adapters** – The function block works exclusively with adapters of type `unidirectional::AE`. Return channels or bidirectional communication are not supported.
- **License** – The source code is subject to the **Eclipse Public License 2.0** (EPL-2.0).

## State Overview
The **AE_SPLIT_4** is a purely combinational function block and has no internal states. The output signal depends solely on the current input signal – there is no storage or delay.

## Application Scenarios
- **Sensor Distribution** – A single sensor (e.g., temperature, speed) provides data via an AE adapter; this data is to be distributed to several control functions operating in parallel.
- **Signal Propagation in a Control Chain** – An event must reach several downstream function blocks in parallel, e.g., for triggering alarms and logging.
- **Event Source Multiplexing** – (in conjunction with a preceding AE-MUX) different sources can be routed to the same four outputs.

## Comparison with Similar Function Blocks
- **E_SPLIT** – Standard 4diac function block for distributing an event to multiple event outputs without data transmission. **AE_SPLIT_4** extends this functionality by also enabling the transmission of adapter data associated with the event.
- **F_SPLIT** – Data splitters (e.g., for IEC 61131-3 "MUX") typically do not operate in an event-driven manner. **AE_SPLIT_4** is specifically optimized for event-based adapter communication.
- **AE_MERGE** – The reverse function block: combines multiple AE inputs into a single output.

## Conclusion
The **AE_SPLIT_4** is a simple yet powerful function block that enables the event-driven distribution of adapter data to up to four equal outputs. Thanks to its generic design, it can be used for any data type without modification and is ideally suited for modular, parallel control architectures.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

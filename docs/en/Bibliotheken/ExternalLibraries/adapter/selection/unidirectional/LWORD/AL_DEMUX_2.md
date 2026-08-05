# AL_DEMUX_2
![AL_DEMUX_2](./AL_DEMUX_2.svg)
* * * * * * * * * *
## Introduction
The function block **AL_DEMUX_2** is a generic AL demultiplexer. It routes an incoming data stream via an adapter socket to either one of two adapter plugs. The output is selected via an index parameter, which is set and activated by an event. The block is designed for use in automated systems where data path switching based on discrete control signals is required.
## Interface Structure
### **Event Inputs**

| Event | Data Parameter | Description |

|----------|----------------|--------------|

| `REQ` | `K` | Sets the index `K` and starts forwarding the current value from the input to the corresponding output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirms the successful switching and forwarding of the value. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|---------------|

| `K` | `UINT` | Index for selecting the output (0 → OUT1, 1 → OUT2). |

### **Data Outputs**
No dedicated data outputs. Data is transmitted exclusively via the adapter plugs.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket | `IN` | `adapter::types::unidirectional::AL` | Input adapter providing the value to be demultiplexed. |

| Plug | `OUT1` | `adapter::types::unidirectional::AL` | First output (active when K = 0). |

| Plug | `OUT2` | `adapter::types::unidirectional::AL` | Second output (active when K = 1). |

## Functionality

The module operates in an event-driven manner:

1. In its idle state, it waits for the event `REQ`.

2. Upon arrival of `REQ`, the value at `K` is read.

3. The current value of the input adapter `IN` is copied to the output adapter determined by `K` (`OUT1` if K=0, `OUT2` if K=1).

4. After successful transmission, the confirmation event `CNF` is sent.

If `K` is a value outside the valid range (≥2), no forwarding occurs and no `CNF` is triggered (or the behavior is application-specific).

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GEN_AL_DEMUX`) and can be reused for various AL adapter variants.
- **Unidirectional Adapters**: All adapters used are of type `unidirectional::AL`, meaning that data flows only in one direction (from the socket to the plug). This simplifies the coupling and reduces potential side effects.
- **No State Machine in the XML**: The logic is implemented implicitly through event handling; there is no explicit ECC, which keeps the implementation lean.
- **No State Machine in the XML**:
## State Overview
A formal state machine is not defined. The function block behaves as follows:

- **Idle**: Waiting for `REQ`.
- **Processing**: After receiving `REQ`, the data is forwarded.
- **Done**: After successful forwarding, `CNF` is output, and the function block returns to the idle state.

## Application Scenarios
- **Actuator Selection**: In a machine control system, an analog or digital value (e.g., speed setting) can be selectively forwarded to two different motor drivers.
- **Data Path Switching**: In a measurement system where a sensor value must be alternately transferred to two evaluation modules.
- **Resource Saving**: Instead of two parallel communication channels, a demultiplexer can be used to share hardware interfaces.

## Comparison with Similar Components
- **AL_MUX_2** (Multiplexer): Combines multiple sources into a single output – the counterpart to the demultiplexer.
- **SIMPLE_SELECT**: Simple switch based on a Boolean signal. AL_DEMUX_2, on the other hand, uses an integer index and AL adapter interfaces.
- **Standard Demultiplexers in Libraries**: Many IEC 61499 libraries offer demultiplexers with more than two outputs (e.g., `DEMUX_4`), but these often only use simple data types and no adapters. AL_DEMUX_2 is specifically optimized for adapter-based applications.

## Conclusion

The function block **AL_DEMUX_2** represents a compact, generic solution for forwarding data to two adapter outputs. Its event-driven selection via index makes it particularly suitable for time-controlled or sequential switching operations in automation systems. The use of AL adapters ensures easy integration into existing adapter-based architectures.

# SPLIT_BYTE_INTO_QUARTERS

Image not available

![SPLIT_BYTE_INTO_QUARTERS](./SPLIT_BYTE_INTO_QUARTERS.svg)

* * * * * * * * * *
## Introduction
The function block `SPLIT_BYTE_INTO_QUARTERS` is used to split an incoming byte data value into four separate quarter outputs. It implements a logical decomposition of a byte (8 bits) into four 2-bit groups, which are routed externally via unidirectional adapters. The internal implementation uses a combination of flip-flops and a recursive instance of the same function block to control the split synchronously and data-driven.

## Interface Structure

### **Event Inputs**
Not present. The function block has no independent event inputs; control is exclusively via the adapter interfaces.

### **Event Outputs**
Not present.

### **Data Inputs**
Not present.


### **Data Outputs**
Not available.

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| **Socket** (Input) | `IN` | `adapter::types::unidirectional::AB` | Byte input that provides the data to be split. |

| **Plug** (Output) | `QUARTER_BYTE_00` | `adapter::types::unidirectional::AQ` | Output for the first quarter (least significant 2 bits). |

| **Plug** (Output) | `QUARTER_BYTE_01` | `adapter::types::unidirectional::AQ` | Output for the second quarter (bits 2-3). |

**Plug** (Output) | `QUARTER_BYTE_02` | `adapter::types::unidirectional::AQ` | Output for the third quarter (bits 4-5). |

**Plug** (Output) | `QUARTER_BYTE_03` | `adapter::types::unidirectional::AQ` | Output for the fourth quarter (most significant 2 bits). |

## Functionality
The function block operates as a **composite function block** with an internal network. As soon as socket `IN` receives an event (via `E1`) and the associated data, this data is forwarded to an internal instance of the same function block (`SPLIT_BYTE_INTO_QUARTERS`). Their outputs (also four quarter-wave adapters) are buffered in four parallel **E_D_FF_ANY flip-flops**. The flip-flops receive the data at the clock signal from the internal `CNF` event chain and synchronously pass it on to the outer plug-in adapters (`QUARTER_BYTE_00` … `QUARTER_BYTE_03`). The precise mapping of the bits to the quarter-waves is implicit via the internal wiring; it is assumed that the byte is divided into four consecutive 2-bit groups (from LSB to MSB).

## Technical Features

- **Recursive Type Usage**: The internal network topology includes another instance of the `SPLIT_BYTE_INTO_QUARTERS` component, enabling multi-stage or iterative decomposition. The actual depth, however, remains limited to one level due to the fixed wiring.

- **Adapter-based design**: Instead of conventional data ports, only unidirectional adapters are used, encapsulating both event and data channels. This promotes loose coupling and reusability.

- **Synchronization via flip-flops**: The four output flip-flops ensure that all quarters are updated simultaneously with a common clock signal as soon as the internal partitioning is complete.

## State overview
The component has **no explicit state machine** (ECC). Its functionality is solely determined by the data and event wiring of the internal components. The system behavior is therefore purely combinatorial, triggered by a clock edge from the flip-flops.

## Application scenarios

- **Parallelization of byte data**: Partitioning a received byte into four independent 2-bit channels, e.g. B. for controlling four parallel output devices or for distributed processing.

- **Serial-to-Parallel Conversion**: Conversion of a serial byte data stream into four parallel quarter signals.

- **Protocol Preparation**: Extracting partial information from a byte when each quarter has a separate meaning (e.g., status flags, configuration values).

## Comparison with Similar Components

- **SPLIT_WORD_INTO_HALF_WORDS**: Analog component for splitting a 16-bit word into two 8-bit halves; usually operates with direct data ports.

- **EXTRACT_BITS_4TO1**: Standard splitting components often operate bitwise or with selectable index ranges. This module is specifically optimized for the fixed quarter-division of a byte and uses adapters instead of simple data inputs/outputs.

- **MUX/DEMUX Modules**: Multiplexers and demultiplexers offer generic division but require additional control lines. The `SPLIT_BYTE_INTO_QUARTERS` is more specialized and easier to configure.

## Conclusion
The `SPLIT_BYTE_INTO_QUARTERS` function block provides a compact, adapter-based solution for decomposing a byte into four quarter-division outputs. The combination of a recursive structure and flip-flop synchronization ensures reliable, parallel data delivery. It is suitable for applications requiring a fixed division of an 8-bit value into four 2-bit units and offers good integration capabilities into modular 4diac projects thanks to its standardized adapter interface.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
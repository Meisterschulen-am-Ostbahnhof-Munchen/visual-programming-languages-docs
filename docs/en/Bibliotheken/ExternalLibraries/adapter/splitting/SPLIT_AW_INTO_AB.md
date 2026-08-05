# SPLIT_AW_INTO_AB
![SPLIT_AW_INTO_AB](./SPLIT_AW_INTO_AB.svg)

* * * * * * * * * *
## Introduction
The function block **SPLIT_AW_INTO_AB** is used to split a word data packet (type AW, 16 bits) into two separate byte data packets (type AB, 8 bits each). The input data is received via a socket and output via two separate plugs. This function block is typically used in environments that rely on adapter-based communication, e.g., in automation technology when decomposing word-based protocols.
## Interface Structure

### **Event Inputs**

The function block does not have its own event inputs. Event control is handled indirectly via the **IN** adapter.

### **Event Outputs**

The function block does not have its own event outputs. Events are transmitted externally via the output adapters **BYTE_00** and **BYTE_01**.

### **Data Inputs**

The FB has no direct data inputs. Data input is indirect via the **IN** adapter.

### **Data Outputs**

The FB has no direct data outputs. Data output is indirect via the **BYTE_00** and **BYTE_01** adapters.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| **IN** | Socket | `adapter::types::unidirectional::AW` | Receives a 16-bit word (WORD). The adapter provides the data and an associated event. |

| **BYTE_00** | Plug | `adapter::types::unidirectional::AB` | Outputs the least significant byte (byte 0). |

| **BYTE_01** | Plug | `adapter::types::unidirectional::AB` | Outputs the most significant byte (byte 1). |

## Functionality

1. An incoming event on the **IN** (E1) adapter triggers the internal function block **SPLIT_WORD_INTO_BYTES**.

2. This splits the received WORD (16 bits) into two bytes: **BYTE_00** (less significant) and **BYTE_01** (most significant).

3. The completion event (CNF) of **SPLIT_WORD_INTO_BYTES** is passed to the clock inputs of two **E_D_FF_ANY** flip-flops.

4. Each flip-flop stores the corresponding byte and outputs it via its **Q** output on the next clock pulse.

5. The flip-flops each generate an event on **EO**, which is sent to the output adapters **BYTE_00** and **BYTE_01**. This makes the split bytes available externally along with an event.

## Technical Features
- **Adapter-based interface:** The function block (FB) does not contain any direct event or data inputs/outputs. All communication takes place via adapters (sockets for inputs, plugs for outputs). It is therefore particularly suitable for applications that rely on the adapter-based 4diac type system.
- **Data caching:** The two **E_D_FF_ANY** flip-flops keep the split bytes stable until new data arrives. This prevents inconsistent states during the splitting process.
- **Event synchronization:** The bytes are output simultaneously because the same CNF event triggers both flip-flops.

## State Overview

The function block (FB) does not have an explicit state machine. It processes pulses in an event-driven manner and outputs the split bytes on **IN** for each event. The flip-flops have the typical two states: stored value (0 or 1 per bit, depending on the byte).

## Application Scenarios
- **Byte-Oriented Communication:** When a sensor or actuator sends data in WORD format, but downstream components expect individual bytes.
- **Protocol Preparation:** Splitting telegrams consisting of a 16-bit value into separate byte adapters for further processing.
- **Modbus/IO-Link Integration:** Adapting 16-bit register values to 8-bit interfaces.

## Comparison with Similar Components
- **SPLIT_WORD_INTO_BYTES:** A pure data splitter without adapter encapsulation. It operates at the data level and requires its own event and data interfaces.
- **MUX/DEMUX Components:** Multiplexers or demultiplexers for multiple values, but usually with different data types and without adapter integration.
- **Adapter Wrappers like SPLIT_AW_INTO_AB:** Specifically developed for the adapter-based 4diac architecture. They encapsulate the splitting logic behind standardized adapter interfaces.

## Conclusion

**SPLIT_AW_INTO_AB** is a specialized adapter wrapper that cleanly splits an incoming WORD into two separate BYTE adapters. The use of flip-flops ensures a stable data flow and avoids timing inconsistencies. This component is ideal for systems that use adapter-based communication according to IEC 61499-2 and require simple transformation between 16-bit and 8-bit data.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

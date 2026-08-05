# AULI_DEMUX_2
![AULI_DEMUX_2](./AULI_DEMUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **AULI_DEMUX_2** is a generic demultiplexer that receives an incoming data stream via an **AULI** adapter and forwards it to one of two outputs (**OUT1** or **OUT2**). The output is selected via the input parameter **K**.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Vars |

|------|-----|-----------|----------|

| REQ | Event | Set Index K | K |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | index |

**Note:** The index K determines the destination output: typically, K = 0 is assigned to output **OUT1** and K = 1 to output **OUT2**.

### **Data Outputs**

No direct data outputs defined.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Socket (Input) | IN | aULI | Input Value to demultiplex |

| Plug (Output) | OUT1 | aULI | - |

| Plug (Output) | OUT2 | aULI | - |

## Functionality

As soon as a signal is present at the **REQ** event input, the current value of the **K** index is evaluated.

- If **K = 0**, the data stream arriving via the **IN** adapter, along with all its attributes, is passed to the **OUT1** output.
- If **K = 1**, the data is passed to **OUT2**.

After the switching and data transfer are complete, the **CNF** event is output to confirm the successful operation.

## Technical Features
- The function block is declared as a **generic function block** (GenericClassName `GEN_AULI_DEMUX`).
- It uses only **unidirectional AULI adapters**, therefore it is suitable for data flows that only run in one direction.
- The index **K** is defined as `UINT`; values other than 0 and 1 are ignored or can lead to undefined behavior.

## State Overview

The internal process can be described as a simple state machine:

1. **IDLE** – Waiting for a REQ event.

2. **SELECT** – Evaluating index K and connecting the IN adapter to the corresponding OUT adapter.

3. **SEND_CNF** – After successful switching, CNF is sent; return to IDLE.

## Application Scenarios
- **Route Switching:** An AULI data stream coming from a sensor should be selectively sent to one of two processing units.
- **Actuator Control:** A central control signal is distributed to two different actuators via the demultiplexer, controlled by an index.
- **Test and Simulation Environments:** Switching between real and simulated data paths.

## Comparison with Similar Function Blocks

| Function Block | Description |

|----------|--------------|

| **AULI_MUX_2** | Multiplexer: Selects one of two inputs and routes it to an output. |

| **AULI_SWITCH** | Generic switch, often with multiple outputs and extended index logic. |

| **AULI_DEMUX_2** (this FB) | Demultiplexer: Distributes one input to one of two outputs – simpler and more specific than a generic switch. |

## Conclusion

The **AULI_DEMUX_2** is a compact yet powerful basic function block for AULI-based communication. It enables the flexible distribution of data streams across two paths and, due to its generic nature, can be easily integrated into a wide variety of control and automation scenarios.

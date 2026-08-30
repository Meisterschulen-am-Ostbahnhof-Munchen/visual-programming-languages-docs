# AULI_FB_CTU

![AULI_FB_CTU](./AULI_FB_CTU.svg)

* * * * * * * * * *
The function block **AULI_FB_CTU** implements an up counter based on the ULINT (unsigned long integer) data type. It is designed as an IEC 61499-compliant component with an **AULI adapter interface**. Internally, the counter uses a standardized IEC 61131-3 CTU component (`FB_CTU_ULINT`) and makes its functionality available via adapter ports. Events are triggered with every update – regardless of a value change.

No dedicated event inputs. Events are received exclusively via the **AX adapters** of the sockets (CU, R, PV).

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Execution Confirmation – triggered with each counter update |

No direct data inputs. The required data (CU pulse, reset signal, preset value) is provided via the **AULI or AX adapters** of the sockets.

No direct data outputs. The result values (current counter value CV and threshold status Q) are output via the **AULI or AX adapters** of the plugs.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Direction | Adapter Name | Type | Comment |
**Socket (Input)** | CU | `adapter::types::unidirectional::AX` | Count-Up Pulse (Event + Data) |
**Socket (Input)** | R | `adapter::types::unidirectional::AX` | Reset Pulse (Event + Data) |
**Socket (Input)** | PV | `adapter::types::unidirectional::AULI` | Preset Value (Comparison Value for Q Output) |
**Plug (Output)** | Q | `adapter::types::unidirectional::AX` | Counter Reading ≥ Preset? (Boolean Status) |
| **Plug (Output)** | CV | `adapter::types::unidirectional::AULI` | Current Meter Reading (ULINT) |

## Functionality

This module encapsulates an IEC 61131-3 compliant CTU meter (`FB_CTU_ULINT`). Events and data are received via the **socket adapters**:

- **CU Update**: A rising edge at CU triggers a counting step (CV = CV + 1).
- **R Update**: A reset resets the meter reading (CV = 0).
- **PV Update**: The preset value is applied; CV is compared to PV with each counting step.

The event at a socket is internally routed to the `REQ` input of the embedded CTU block. After processing, the `CNF` event of the CTU block is forwarded to all three outputs:

- **Q-Plug**: Outputs the status event (Q.E1) – sent **with every update**, regardless of whether the boolean value has changed.
- **CV-Plug**: Outputs the event (CV.E1) – also **with every update**.
- **CNF-Event**: Provided as an external event.

The data flows are analogous: The socket data (CU.D1, R.D1, PV.D1) is transferred to the corresponding data inputs of the internal counter. The output data (Q.D1, CV.D1) is output via the plugs.

- **Always Update**: The function block triggers the output events (Q.E1, CV.E1, CNF) with **every** incoming event (CU, R, PV) – even if the counter reading or the Q value does not change.
- **Filter Recommendation**: If triggering is only desired upon an actual value change, the use of an **AX_D_FF** function block as a pre-filter is recommended (see comment in the identification).
- **Data Width**: The counter uses the ULINT data type (64-bit unsigned integer), suitable for large counting ranges.
- **Adapter Interface**: All inputs and outputs are handled via standardized adapters (`AX` for Boolean/event-based values, `AULI` for ULINT values). This facilitates modular design and reuse in adapter-based projects.
- **No Top-Level State Machine**: The function block is purely transaction-based: Every incoming event triggers immediate processing.

The function block does not have its own state machine. The internal `FB_CTU_ULINT` can pass through the following states (simplified):

- **Idle**: Waiting for an event.
- **Increment**: Upon a CU event, the internal counter is incremented.
- **Reset**: Upon a R event, the counter is reset to 0.
- **Preset Update**: The comparison value is updated upon a PV event.

After each processing operation, the outputs are updated and the CNF event is sent.

- **High-Frequency Pulse Counting**: Acquisition of counting pulses (e.g., encoders, clock signals) with 64-bit resolution.
- **Threshold Monitoring**: Counting of products or events up to a configurable threshold (PV); the Q output is activated upon reaching this threshold.
- **Reset-Controlled Batch Counting**: After an R pulse, the counter starts from zero; the current count is output via CV.
- **Adapter-Based Automation Modules**: Easy integration into systems that rely on AX/AULI adapters (e.g., standardized I/O modules).
- **Standard CTU (IEC 61131-3)**: Typically offers separate event and data ports. The `AULI_FB_CTU` encapsulates these in adapters, which simplifies bus-level wiring.
- **CTU with Change Detection**: Some counter function blocks only fire output events when a value changes. This function block triggers with every update – resulting in deterministic behavior (one event per input event), but may require downstream filters.
- **CTU as a Basic Function Block**: Other implementations use their own state machine; this function block delegates the logic to an embedded block, thus remaining lean.

The **AULI_FB_CTU** offers an IEC 61499-compliant, adapter-based increment counter function with ULINT data width. Its strengths lie in its modular interface and reliable event triggering with every update. For applications requiring only change detection, an external filter block (AX_D_FF) is recommended. Overall, the block is suitable for a wide range of counting scenarios in industrial automation, especially in adapter-oriented architectures.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

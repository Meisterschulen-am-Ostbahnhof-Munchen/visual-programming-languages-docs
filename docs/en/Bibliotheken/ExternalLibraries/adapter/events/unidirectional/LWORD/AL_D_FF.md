# AL_D_FF

![AL_D_FF](./AL_D_FF.svg)

* * * * * * * * * *

## Introduction

The function block **AL_D_FF** implements a data latch flip-flop (D flip-flop). It serves to store a digital data value upon each incoming event and make the stored value available via an adapter output. The block encapsulates the recurring task of a D flip-flop and provides a clean, typed interface for event and data exchange via adapters.

## Interface Structure

### **Event Inputs**

No direct event inputs. The event for transferring the data value is provided via the adapter socket **I** (E1).

### **Event Outputs**

No direct event outputs. The output event is provided via the adapter plug **Q** (E1).

### **Data Inputs**

No direct data inputs. The data value to be stored is supplied via the adapter socket **I** (D1).

### **Data Outputs**

No direct data outputs. The stored data value is output via the adapter plug **Q** (D1).

### **Adapters**

| Name | Type | Direction | Comment |
| ------ | ----- | ---------- | ----------- |
| I | `adapter::types::unidirectional::AL` | Socket | Value to be latched |
| Q | `adapter::types::unidirectional::AL` | Plug | Latched value |

The adapters are unidirectional and of type `AL`. Each adapter contains an event input/output (E1) and a data input/output (D1). Socket **I** serves as the input interface, and plug **Q** as the output interface.

## Functionality

The function block internally uses the standard function block `iec61499::events::E_D_FF_ANY`.

Upon each event at the adapter input **I** (E1), the data value from **I.D1** is taken and stored at the adapter output **Q.D1**. Simultaneously, an event is generated at output **Q.E1** to signal the availability of the new value to the downstream logic.

The takeover is edge-triggered (rising edge) – the behavior corresponds to a clocked D-latch or D-flip-flop, depending on the definition of the internally used function block.

## Technical Features

- **Adapter-based interface**: Instead of individual inputs/outputs, the entire signal group (event + data) is combined via an adapter. This simplifies the connection in the application and ensures clear semantic encapsulation.
- **Reusing Existing Logic**: The function block delegates the core function to the IEC 61499 standard function block `E_D_FF_ANY`, thus using a proven and portable implementation.
- **Type Safety**: By using a defined adapter type (`AL`), it is ensured that only compatible signals can be connected.

## State Overview

The function block does not have its own ECC state machine. Its internal behavior is entirely determined by the embedded function block `E_D_FF_ANY`. This implements a D flip-flop with two logical states:

- **State 0**: The stored value is `false` (or the adapter's data value is 0).
- **State 1**: The stored value is `true` (or the adapter's data value is 1).

A state change occurs only upon an event at **I.E1**; the value present at **I.D1** is then adopted.

## Application Scenarios

- **Signal Delay and Synchronization**: A data value should only be passed on upon a defined event (e.g., clock edge).
- **Storage of a Binary State**: e.g., as part of a shift register, a state register, or marker logic.
- **Coupling with Adapter-Based Components**: Easy integration into applications that already use the adapter type `adapter::types::unidirectional::AL`.

## Comparison with Similar Components

- **E_D_FF_ANY**: Standard D flip-flop with single event and data inputs. `AL_D_FF` encapsulates this function block and provides an adapter interface.
- **SR_FF or JK_FF**: Other flip-flop types with multiple control inputs. `AL_D_FF` is limited to basic D functionality.
- **AL_D_LATCH**: A simple latch without event control? (Not available). `AL_D_FF` operates on an edge and is therefore suitable for clock-synchronous systems.

## Conclusion

The function block `AL_D_FF` offers an encapsulated, adapter-based solution for basic D flip-flop functionality. It simplifies the handling of signal and event groups in IEC 61499 applications, increases reusability, and remains reliable and traceable through traceability to a standardized core component.

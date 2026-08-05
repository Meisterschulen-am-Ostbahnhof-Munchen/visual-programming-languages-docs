# AIS_D_FF
![AIS_D_FF](./AIS_D_FF.svg)

* * * * * * * * * *
## Introduction
The `AIS_D_FF` function block implements a clock-edge-triggered D flip-flop (data latch). It is used to store and output a data value upon receiving a clock event. Communication is exclusively via AIS adapters (unidirectional), allowing the function block to be integrated into adapter-based component architectures.
## Interface Structure

### **Event Inputs**
No direct event inputs. The clock signal is provided via the socket adapter **I** (event port `E1`).

### **Event Outputs**
No direct event outputs. The output event is sent via the plug adapter **Q** (event port `E1`).

### **Data Inputs**
No direct data inputs. The data value to be received is received via the socket adapter **I** (data port `D1`).

### **Data Outputs**
No direct data outputs. The stored value is output via the plug adapter **Q** (data port `D1`).

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| **I** | `adapter::types::unidirectional::AIS` | Socket | Input adapter: Clock signal (event `E1`) and data input (data `D1`) |
| **Q** | `adapter::types::unidirectional::AIS` | Plug | Output adapter: Acknowledge event (event `E1`) and stored data value (data `D1`) |

## Functionality

This component encapsulates the IEC 61499 standard component `E_D_FF_ANY`. On a rising edge of the clock signal (event `I.E1`), the current value of `I.D1` is taken and stored internally in the flip-flop. An event is then triggered at output `Q.E1`, and the stored value is made available at port `Q.D1`. The output value remains until the next clock event arrives.

## Technical Features
- **Pure Adapter Interface**: The module has no direct event or data ports but uses only AIS adapters. This allows for flexible integration with other adapter-based components.
- **Generic Data Type**: The internal `E_D_FF_ANY` module supports any data type. The data width and type are determined by the adapter implementation used.
- **Event-Driven Data Pass-Through**: The output is only updated upon an incoming clock event. Without a clock event, the output remains unchanged.

## State Overview

Since the component implements the behavior of a D flip-flop, two states can be distinguished:

| State | Description |
|---------|--------------|
| **Idle State** | The stored value remains constant. No output event is generated. |
| **Takeover** | Upon the arrival of a clock event, the current input value is taken, the output is updated, and an output event is sent. |

The flip-flop is edge-triggered (rising edge) and not level-triggered.

## Application Scenarios
- **Data Buffer in Adapter Networks**: Temporarily storing values that are only valid for specific events (e.g., clock signals from sensors).
- **Synchronization**: Synchronizing data between components that communicate via asynchronous events.
- **Registers in Control Applications**: Construction of shift registers or simple memory cells in IEC 61499 systems using AIS adapters.

## Comparison with Similar Devices
- **`E_D_FF_ANY`** – The direct function block equivalent with standard event and data ports. `AIS_D_FF` encapsulates this device in an adapter-based interface.
- **SR Flip-Flop** – Stores a binary state via set and reset inputs, while `AIS_D_FF` stores an arbitrary data value via a clock signal.
- **Latch (Level-Controlled)** – A latch holds the input value as long as the clock signal is active; In contrast, `AIS_D_FF` only reacts to an edge and is therefore less susceptible to noise and glitches.

## Conclusion

AIS_D_FF` is a useful component for implementing an edge-triggered D flip-flop in adapter-based architectures. By encapsulating the proven `E_D_FF_ANY` functional block, it offers reliable memory functionality and can be seamlessly integrated into existing AIS communication structures.

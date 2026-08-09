# AUDI_D_FF

![AUDI_D_FF](./AUDI_D_FF.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_D_FF** implements a clock-controlled D flip-flop (data latch) based on IEC 61499 adapters. Upon an event at the input adapter, it receives the incoming data value, stores it, and outputs it via the output adapter. The block encapsulates all control logic in a compact, adapter-based interface, thus allowing for a clean separation of event and data communication.
## Interface Structure

### **Event Inputs**

None – event control is handled exclusively via the socket adapter.

#### **Event Outputs**

None – event output is handled exclusively via the plug adapter.

#### **Data Inputs**

None – data acquisition is handled exclusively via the socket adapter.

### **Data Outputs**

None – data output is exclusively via the plug adapter.

### **Adapters**

| Name | Type | Direction | Description |
|------------|-----|----------|--------------|
| **I** | `adapter::types::unidirectional::AUDI` | Socket (Input) | Provides the clock event (E1) and the data value to be received (D1). |
| **Q** | `adapter::types::unidirectional::AUDI` | Plug (Output) | Outputs the output event (E1) and the stored data value (D1). |

Both adapters are of the same unidirectional type **AUDI**, which transports an event and a data value together. The socket **I** serves as the source, the plug **Q** as the sink.

## Functionality

The function block operates according to the classic D flip-flop function:

1. **Waiting for Clock**: As long as no event is present at input **I.E1**, the internal memory retains its last value.
2. **Takeover on Clock Edge**: An event at **I.E1** (interpreted as a rising edge) causes the function block to take the current data value from **I.D1** and store it in the internal memory.
3. **Output**: After the takeover, an event is output at **Q.E1**, and the stored data value appears at **Q.D1**. This value remains stable until the next clock event arrives.

The internal implementation uses the IEC 61499 standard function block `E_D_FF_ANY`, which provides a type-independent D flip-flop function. Adapters **I** and **Q** are directly connected to its event and data ports.

## Technical Features

- **Adapter-based interface**: The function block (FB) does not use individual event or data inputs/outputs, but communicates exclusively via unidirectional adapters. This simplifies connections in complex networks and supports modular type checking.
- **Type independence**: The internal block `E_D_FF_ANY` works with any data type (ANY). The actual data type is defined by the adapter definition of type `AUDI`.
- **Unidirectional communication**: The adapter type `adapter::types::unidirectional::AUDI` transmits events and data only in one direction – from the socket to the plug. Feedback is not provided.
- **No additional initialization state**: The FB starts without a defined data value; The internal state corresponds to the initial state of the `E_D_FF_ANY` function block used.

## State Overview

Since this is a purely combinational, event-driven memory, its behavior can be described by two stable states:

- **State A (Waiting)**: No clock event is received – output **Q.D1** holds the last acquired value.
- **State B (Accepting)**: A clock event at **I.E1** triggers the acquisition of **I.D1**. After processing, the function block immediately returns to the waiting state (not a multi-stage state machine).

A graphical representation as a state machine is not required, as the logic is delegated to the internal `E_D_FF_ANY`, whose state diagram is defined in the IEC 61499 specification.

## Application Scenarios

- **Data Buffer**: Acquires a sensor signal at a defined measurement time and forwards it to a controller.
- **Synchronization**: Simultaneous reading of multiple data sources via a common clock event.
- **Register Implementation**: Multiple `AUDI_D_FF` modules can be connected in parallel to create an n-bit register.
- **Interface to Event-Driven Communication Protocols**: The adapter is particularly suitable for systems that use standardized data-event pairs (e.g., OPC UA or MQTT connections).

## Comparison with Similar Modules

- **`E_D_FF_ANY`** (IEC 61499 standard module): Has separate event and data inputs/outputs, no adapter interface. The `AUDI_D_FF` encapsulates these interfaces in an adapter, thus simplifying their use in adapter-based networks.
- **SR Flip-Flop (Set-Reset)**: Has two data inputs (Set/Reset) and does not allow pure clock operation. The `AUDI_D_FF` is tailored to the simple D flip-flop application.
- **AUDI Adapter-Based Function Blocks (e.g., `AUDI_D_FF_2`)**: Other implementations might include additional logic such as asynchronous reset. This function block implements the minimal D flip-flop without additional control functions.

**SR Flip-Flop (Set-Reset)**
## Conclusion

The **AUDI_D_FF** represents a cleanly encapsulated, adapter-based implementation of a D flip-flop. By using the unidirectional `AUDI` adapter type, the interface is reduced to the essentials – one event and one data value per side. The internal use of the proven `E_D_FF_ANY` function block ensures robust, standards-compliant functionality. The function block is particularly suitable for modular architectures that rely on adapter connectivity and facilitates reuse in various control projects.

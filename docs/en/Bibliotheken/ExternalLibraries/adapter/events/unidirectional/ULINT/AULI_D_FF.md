# AULI_D_FF

![AULI_D_FF](./AULI_D_FF.svg)

* * * * * * * * * *
## Introduction

The AULI_D_FF function block implements a clock-edge-triggered D flip-flop (data latch). Upon receiving an event, it accepts the incoming data value and holds it until the next clock cycle. Input and output are handled via standardized unidirectional adapters, allowing for easy integration of the block into modular control architectures.

## Interface Structure

### **Event Inputs**

- **I.E1** – Clock event (rising edge): triggers the transfer of the data value

### **Event Outputs**

- **Q.E1** – Output event: sent after successful transfer of the value

### **Data Inputs**

- **I.D1** – Data value to be latched (any type, as the internal function block `E_D_FF_ANY` is used)

### **Data Outputs**

- **Q.D1** – Latched data value (corresponds to the last value transferred from I.D1)

### **Adapters**

The function block has two unidirectional adapters of type `adapter::types::unidirectional::AULI`:

- **Socket I** (input): receives the clock event and the data value.
- **Plug Q** (Output): Passes on the acknowledgment event and the stored data value.

## Functionality

As soon as an event arrives at **I.E1** on input adapter I, the current value of **I.D1** is transferred to the internal flip-flop. Immediately afterward, the event **Q.E1** is sent at output adapter Q, and the new value is output to **Q.D1**. The stored value is retained until another clock event transfers a new value.

The function block operates as **clocked memory** and is particularly suitable for synchronizing data flows in event-driven automation systems.

## Technical Features

- The function block is implemented as a **composition** and internally uses the standard function block `iec61499::events::E_D_FF_ANY`, which provides the actual flip-flop functionality.
- The use of adapters enables **uniform connectivity** to a wide variety of components that support the same adapter type.

`` - No further configuration parameters or initializations are required – the function block operates deterministically after the first clock edge.

## State Overview

The internal state of the D flip-flop can be logical 0 or 1. Since the data value can be arbitrary, the state corresponds to the last latched value. An explicit state diagram is not required, as the behavior is fully described by the simple edge triggering.

| Clock (I.E1) | Previous Q value | New Q value |
|-------------|-------------------|--------------|
| Event | arbitrary | Value of I.D1|
| no event | unchanged | unchanged |

## Application Scenarios

- **Data Buffering** in production lines: A sensor value is acquired and buffered at each clock cycle.
- **State Machines**: Implementation of memory cells for step sequences where the next state depends on the current output.
- **Synchronization**: Adapting asynchronous data streams to a uniform clock in distributed control systems.
- **Signal Processing**: Holding a digital signal for the duration of a clock cycle.

## Comparison with Similar Components

| Component | Description | Difference from AULI_D_FF |
|----------|---------------|-----------------------------|
| SR-FF | Set-Reset Flip-Flop | Requires two separate inputs; can have illegal states. |
| JK-FF | Universal Flip-Flop | More complex, with toggle functionality; not needed here. |
| T-FF | Toggle Flip-Flop | Changes the state on each clock cycle; no data input. |
| AULI_D_FF| D Flip-Flop | Simple, no toggle, no illegal states, ideal for storing a value. |

## Conclusion

The AULI_D_FF is a compact, event-driven D flip-flop component that communicates via standardized adapters. It is ideally suited for intermediate data storage in discrete-event control environments. Its internal use of a proven standard function block ensures robust and deterministic behavior. The modular adapter interface facilitates integration into complex automation projects.

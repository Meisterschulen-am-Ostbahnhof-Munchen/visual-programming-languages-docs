# AUI_D_FF

![AUI_D_FF](./AUI_D_FF.svg)

* * * * * * * * * *

## Introduction
The function block **AUI_D_FF** implements a clock-controlled D flip-flop (data latch). It takes the value of a data input when an event occurs and outputs the stored value. The input and output interfaces are implemented as unidirectional **adapters**, enabling a flexible and standardized connection in the 4diac IDE.

## Interface Structure

### **Event Inputs**
None – event control is handled exclusively via the **I** adapter.

### **Event Outputs**
None – event output is handled exclusively via the **Q** adapter.

### **Data Inputs**
None – data transfer is handled exclusively via the **I** adapter.


## ### **Data Outputs**

None – data output is exclusively via the **Q** adapter.

### **Adapters**

| Name | Type | Direction | Description |

|-------------|-----|----------|-------------|

| **I** | `adapter::types::unidirectional::AUI` | Socket (Input) | Input value (D) and clock event (CLK) |

| **Q** | `adapter::types::unidirectional::AUI` | Plug (Output) | Stored value (Q) and output event (EO) |

The **AUI** adapter type provides a unidirectional channel that transmits exactly one event and one data value. Thus, the internal connections between the flip-flop and the outside world are implemented via adapters.


## Functionality
The function block internally uses the function block `E_D_FF_ANY` from the IEC 61499 standard library.

- On each **clock event** on `I.E1`, the current data value is taken from `I.D1`.

- The taken value is made available at output `Q.D1`, and an **output event** is triggered simultaneously on `Q.E1`.

- The stored value is retained until a new clock event takes over a new data value.

## Technical Features
- The interface consists exclusively of **adapters**, not separate event and data ports. This allows for loose coupling and reusability of the adapter type in different contexts.


- The adapter `AUI` is **unidirectional** – data and events flow in only one direction.

- The function block is type-safe: The data type is defined by the adapter (`ANY` by default).

## State Overview
The function block has two logical states, corresponding to the internal flip-flop:

| State | Description |

|---------|--------------|

| **Q = 0** | Output value is LOW (logical 0). |

| **Q = 1** | Output value is HIGH (logical 1). |

The state changes only on a rising edge of the clock event (provided the event is triggered in the adapter).

## Application Scenarios

- **Synchronization**: Transfer of a data value at a precisely defined time (e.g., upon a sensor event).

- **Central Storage**: Buffering a value for further processing in subsequent components.

- **State Machines**: Storing states in discrete controllers when a simple D flip-flop function is sufficient.

## Comparison with Similar Components

- **E_D_FF** (Standard IEC 61499): Offers the same flip-flop functionality, but with separate event and data ports. The `AUI_D_FF` encapsulates these ports in an adapter, enabling clean, adapter-based communication.

- **E_RS** or **E_SR** (Reset-Set Flip-Flops): Unlike the D flip-flop, these components require separate set/reset events and no clock signal. The `AUI_D_FF` is optimized for clock-driven applications.


## Conclusion

The `AUI_D_FF` is a standards-compliant D flip-flop in the 4diac IDE that offers a modular and reusable interface through the use of **adapters**. It is particularly suitable for applications where a uniform, unidirectional connection structure is desired without having to forgo the proven flip-flop logic.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```
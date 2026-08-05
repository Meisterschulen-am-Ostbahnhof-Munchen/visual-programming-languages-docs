# AX_FB_TON_LTIME
![AX_FB_TON_LTIME](./AX_FB_TON_LTIME.svg)

* * * * * * * * * *
## Introduction
The **AX_FB_TON_LTIME** function block implements an on-delay timer according to IEC 61131-3 with the data type `LTIME` and an integrated **AX adapter** interface. It is particularly suitable for time-critical control tasks where both events and data must be exchanged via standardized adapters.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|--------------|

| REQ | `Event` | Normal execution trigger (not edge-triggered); The timer starts when the signal at data input `IN` or at adapter `IN.E1` is active. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|-------------|

| CNF | `Event` | Confirmation of execution. Triggered as soon as the timer expires or the condition is met. |

### **Data Inputs**

| Name | Type | Description |

|------|-----|--------------|

| PT | `LTIME` | Preset time for the power-on delay. |

### **Data Outputs**

| Name | Type | Description |

|------|-----|-------------|

| ET | `LTIME` | Elapsed time since the start of the timer. |

### **Adapter**

| Type | Direction | Description |

|-----|----------|-------------|

| `IN` | Socket (Input) | Unidirectional AX adapter for input data. Contains an event (`E1`) and a data value (`D1`). The event starts the timer; the data value determines the timer input (`IN`). |

| `Q` | Plug (Output) | Unidirectional AX adapter for output data. Outputs the result of the time check: `1` if the elapsed time has reached the target time, otherwise `0`. |

## Functionality

The function block is implemented as a composite and internally contains the IEC 61131-3 timer **FB_TON_LTIME** and an edge-triggered D flip-flop (**E_D_FF**).

- **Start Conditions**: The timer starts as soon as an event arrives at the adapter `IN.E1` or at the event input `REQ`. Simultaneously, the data value `IN.D1` (or the internal timer input) must be set to `TRUE`.
- **Expiration**: The internal timer counts up the time. The output `ET` outputs the currently elapsed time.
- **End**: When the elapsed time `ET` reaches the target time `PT`, the timer output (`Q`) is set to `TRUE`. This triggers the event `CNF` and clocks the D flip-flop.
- **Output Adapter**: The D flip-flop stores the state and outputs it via the adapter `Q.D1`. The event `Q.E1` signals the output change.

## Technical Features
- **LTIME Data Type**: Enables very high time resolution (nanosecond range) and large time ranges.
- **Adapter Interface**: The component can be integrated into existing systems via standardized AX adapters without requiring direct event or data connections.
- **Edge-Triggered Output**: The internal D flip-flop updates the output state only on a rising edge of the timer termination – this prevents unwanted fluctuations.
- **Internal Network**: Functionality is achieved through the combination of standard function blocks, making the implementation transparent and testable.

## State Overview
The function block itself does not have its own state diagram, as it consists of an internal function block network. However, its behavior can be derived from the underlying IEC timer function block:

1. **Inactive** – Timer is not running, `ET` = 0, output `Q` = `FALSE`.

2. **Timer is running** – Input `IN` = `TRUE`, timer is incrementing `ET`.

3. **Expired** – `ET` ≥ `PT`; `Q` changes to `TRUE` and remains until `IN` falls to `FALSE` or a new REQ resets the timer.

## Application Scenarios
- **Delayed Actuator Activation**: A valve or motor should only be activated after a defined delay time.
- **Process Synchronization**: Waiting for a signal to arrive via the adapter before triggering a time-critical action.
- **Response Time Monitoring**: Recording the elapsed time between an event and a specific condition.
- **Extension of existing AX-based systems**: Replacement of standard timer modules with the adapter variant without changing the overall structure.

## Comparison with similar modules
- **FB_TON_LTIME** (pure IEC timer): Does not have adapters and requires direct event and data connections. The AX_FB_TON_LTIME extends this with a standardized, easily connectable interface.
- **Event-driven timers** (e.g., E_TON): Often use Boolean inputs and do not have native LTIME support. The module presented here combines precise long-term measurement with flexible adapter connectivity.

## Conclusion

The **AX_FB_TON_LTIME** is a powerful, adapter-based turn-on delay module for the IEC 61499 environment. It combines the advantages of the standardized IEC 61131-3 timer (LTIME, precise time measurement) with the modularity and reusability of AX adapters. The internal integration with a D flip-flop ensures reliable, edge-triggered output. It is ideally suited for time-critical controllers embedded in an adapter-based architecture model.

# AI_TO_AB

![AI_TO_AB](./AI_TO_AB.svg)

* * * * * * * * * *
## Introduction

The composite function block `AI_TO_AB` converts an **INT** value, provided via a unidirectional **AI** adapter, into a **BYTE** value and forwards it via a unidirectional **AB** adapter. The actual conversion is performed by the internally used function block `F_INT_TO_BYTE`. This function block is part of an adapter conversion library and enables the seamless integration of components with different data types in IEC 61499 systems.

## Interface Structure

### **Event Inputs**

No standalone event inputs. Event-driven communication is handled via the AI_IN adapter (see Adapters).


### **Event Outputs**

No standalone event outputs. Event-driven output is handled via the AB_OUT adapter (see Adapters).

### **Data Inputs**

No standalone data inputs. The INT value to be converted is provided via the AI_IN adapter.

### **Data Outputs**

No standalone data outputs. The converted BYTE value is output via the AB_OUT adapter.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket (Input) | `AI_IN` | `adapter::types::unidirectional::AI` | Provides the INT input value (D1) and the triggering event (E1). |

| Plug (Output) | `AB_OUT` | `adapter::types::unidirectional::AB` | Outputs the converted BYTE value (D1) and the associated event (E1). |

## Functionality

The FB `AI_TO_AB` operates as a pure data converter based on event control:

1. An event **E1** is received at the **AI_IN** adapter.

2. This event triggers the internal FB `Convert` of type `F_INT_TO_BYTE` via its **REQ** input.

3. Simultaneously, the INT data value from `AI_IN.D1` is forwarded to the **IN** input of `Convert`.

4. After the conversion is complete, `Convert` generates an acknowledgment event (**CNF**).

5. This event is sent to **AB_OUT.E1**, and the converted BYTE value (`Convert.OUT`) is passed to **AB_OUT.D1**.

Thus, every incoming INT value is synchronously converted into a BYTE value via an event and made available through the output adapter.

## Technical Features

- **Composite FB:** The function block encapsulates the logic in a network consisting of a single conversion function block. It is not itself an elementary function block but utilizes the reuse of `F_INT_TO_BYTE`.

- **Adapter-Based Interface:** Events and data are transmitted exclusively via unidirectional adapters, resulting in loose coupling between source and target components.

- **Type Conversion:** The actual conversion of `INT -> BYTE` follows the IEC 61131-3 convention (e.g., value range <0,255>; an overflow occurs if the range is exceeded). This depends on the implementation of the `F_INT_TO_BYTE` function block used.

- **No Internal State Machine:** The function block is purely combinatorial with event-driven execution.

## State Overview

Since it is a composite function block, `AI_TO_AB` does not have its own state machine. The internal function block `F_INT_TO_BYTE` may have a simple state machine (IDLE, EXECUTING), depending on the implementation, but this is not visible within the scope of this function block. The data and event flows are deterministic and are controlled by the interaction of the connections.


## State Overview ## Application Scenarios

- **Sensor Connection:** A sensor delivers INT values that must be processed as BYTE by a control unit (e.g., for simple I/O cards).

- **Data Format Conversion:** in heterogeneous IEC 61499 systems to connect components with different adapter types.

- **Adapter Translation:** in libraries designed for unidirectional communication, e.g., when using fieldbus protocols that expect BYTE-oriented data.

## Comparison with Similar Components

- **Direct Converters (e.g., `F_INT_TO_BYTE`):** These operate at the data port level and require explicit event control. `AI_TO_AB` encapsulates this in an adapter-based interface.

- **Additional Adapter Converters:** Possible modules include `AI_TO_AW` (INT to WORD) or `AB_TO_AI` (BYTE to INT). `AI_TO_AB` is specifically designed for combining the two unidirectional adapters `AI` and `AB`.

- **Composite Converters vs. Elementary Converters:** Composite function blocks offer a higher level of abstraction and reusability, while elementary function blocks allow more control over the internal logic.


## Conclusion

The composite function block `AI_TO_AB` provides an efficient, adapter-based solution for converting INT to BYTE values. It simplifies the integration of components with different data types into IEC 61499 applications by encapsulating the conversion logic in a standardized, reusable interface. Event-driven execution and the use of an established conversion block ensure reliable and deterministic data processing.
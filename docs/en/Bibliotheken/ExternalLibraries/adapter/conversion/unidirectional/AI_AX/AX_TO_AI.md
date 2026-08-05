# AX_TO_AI
![AX_TO_AI](./AX_TO_AI.svg)

* * * * * * * * * *
## Introduction
The function block **AX_TO_AI** is a composite function block that converts a BOOL adapter (AX) into an INT adapter (AI). It serves as a bridge between interfaces that process Boolean signals (TRUE / FALSE) and those that expect integer values. The conversion is performed via an internal call to the function block `F_BOOL_TO_INT` from the IEC 61131 library.
## Interface Structure

### **Event Inputs**

No direct event inputs. The function block's event input is implemented via socket `AX_IN` (E1).

#### **Event Outputs**

No direct event outputs. The event output of the function block is implemented via the plug `AI_OUT` (E1).

### **Data Inputs**

No direct data inputs. The data input of the function block is implemented via the socket `AX_IN` (D1) (BOOL).

### **Data Outputs**

No direct data outputs. The data output of the function block is implemented via the plug `AI_OUT` (D1) (INT).

### **Adapters**

| Direction | Name | Type (Adapter) | Explanation |

|----------|--------|----------------|------------------------------------|

| Socket | AX_IN | `AX` | Boolean Input Adapter (BOOL) |

| Plug | AI_OUT | `AI` | Integer Output Adapter (INT) |

The adapter `AX` provides an event input `E1` and a data input `D1` (BOOL).

The adapter `AI` provides an event output `E1` and a data output `D1` (INT).

## Functionality

This function block operates as a so-called *Composite FB*, meaning it internally uses another function block to implement its logic.

- A BOOL signal is received at socket `AX_IN` via the data input `D1`.
- An incoming event at `AX_IN.E1` triggers the internal function block `Convert` (type: `F_BOOL_TO_INT`) via its input `REQ`.
- The function block `F_BOOL_TO_INT` converts the BOOL value at input `IN` into an INT value (0 for `FALSE`, 1 for `TRUE`).

`` - The result is provided at output `OUT` and forwarded to plug `AI_OUT.D1`.

- After the conversion is complete, the internal block sends an acknowledgment event (`CNF`), which is output via `AI_OUT.E1`.

Processing is strictly sequential: first, the Boolean input is processed, then the integer output is provided.

## Technical Features
- **Adapter-based communication:** The block uses only adapter interfaces (socket and plug) and no traditional input/output ports. This enables loose coupling between components and easy reuse in different environments.
- **Unidirectional Data Exchange:** The adapters used, `AX` and `AI`, are defined as unidirectional types, meaning data flows only in one direction – from the socket to the plug.
- **External Library:** For conversion, the function block `F_BOOL_TO_INT` is imported from the library `iec61131::conversion`. This eliminates the need to implement custom conversion logic.
- **No Internal State Machine:** Because this is a composite function block, it does not have its own Execution Control Chart (ECC). The state logic is fully implemented by the internal function block.

## State Overview

The function block does not have its own state machine. Execution is event-driven:

1. **Wait:** The function block waits for an event at socket `AX_IN`.

2. **Convert:** Upon receiving an event, the internal function block `F_BOOL_TO_INT` is executed, and the result is passed to plug `AI_OUT`.

3. **Completed:** An acknowledgment event is sent via `AI_OUT.E1`; the function block returns to the wait state.

This behavior is implicitly controlled by the event cabling in the network.

## Application Scenarios
- **Signal Conversion in Automation Technology:** If a sensor or controller delivers Boolean values (e.g., "door open/closed"), but a downstream module expects integer values (0/1), this function block can handle the conversion.
- **Adapter Integration:** It serves as a converter between different adapter types to connect components from different manufacturers or libraries.
- **Protocol Adaptation:** In heterogeneous systems, Boolean signals can be converted into standardized integer formats using this function block.

## Comparison with Similar Function Blocks

| Function Block | Function | Difference from AX_TO_AI |

|---------------------|-------------------------------------------|-------------------------------------------------------------|

| `DI_TO_AI` | Converts digital input to INT adapter | Requires separate input/output ports; no adapter interface |

| `AX_TO_DINT` | BOOL adapter → DINT adapter | Returns a 32-bit integer; 16-bit INT is used here |

| `F_BOOL_TO_INT` | Standard conversion (BOOL→INT) | No adapter wrapper; available only as an internal block |

Unlike these alternatives, AX_TO_AI offers an addressable, event-driven adapter interface and facilitates modular interconnection in IEC 61499 projects.

## Conclusion

The `AX_TO_AI` function block provides a simple yet effective solution for converting Boolean adapter signals to integer adapter signals. It encapsulates the logic in a reusable composite block, utilizes standard libraries, and enables clean, adapter-based communication. This block is particularly well-suited for modular automation solutions where different interface types need to be coordinated.

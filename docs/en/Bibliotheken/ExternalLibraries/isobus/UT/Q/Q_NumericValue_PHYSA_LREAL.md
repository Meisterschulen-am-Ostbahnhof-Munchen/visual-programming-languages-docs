# Q_NumericValue_PHYSA_LREAL
![Q_NumericValue_PHYSA_LREAL](./Q_NumericValue_PHYSA_LREAL.svg)
* * * * * * * * * *
## Introduction
The function block **Q_NumericValue_PHYSA_LREAL** serves as a command for changing a numeric value in the ISOBUS context (ISO 11783-6). It receives a physical LREAL value via the **ALR** adapter and handles the actual processing via the embedded function block **Q_NumericValue_PHYS_LREAL**. The function block uses adapter interfaces for physical value input as well as for signaling when the permissible range limits are exceeded or fallen below.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|-------|-------|---------------------------------------------|

| INIT | EInit | Initialization of the function block (with stObj). |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|--------------------------------------------------|

| INITO | EInit | Confirmation of successful initialization. |

| CNF | Event | Confirmation of the requested value change (contains STATUS and s16result). |

### **Data Inputs**

| Name | Type | Comment |

|-------|--------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|

| stObj | logiBUS::utils::conversion::phys::NumericObjectPool_S | Properties of the object pool (ObjID, scale, offset, decimal places). Initial: (u16ObjId := ID_NULL, r32Scale := 1.0, i32Offset := 0, u8Decimals := 0). |

### **Data Outputs**

| Name | Type | Comment |

|-----------|--------|--------------------------------------------------------------------------|

| STATUS | STRING | Service status message. |

| s16result | INT | Return value – see Q_NumericValue (result of the value change request). |

### **Adapters**
**Sockets (Input Adapters)**

| Name | Type | Comment |

|--------|-------------------------|---------------------------------------------------------------|

| lrPhys | ALR (unidirectional) | Input for the physical LREAL value (triggered via E1). |

**Plugs (Output Adapters)**

| Name | Type | Comment |

|--------|-------------------------|---------------------------------------------------------------|

| xOver | AX (unidirectional) | Signals that the physical value exceeds the upper ISOBUS limit. |

| xUnder | AX (unidirectional) | Signals that the physical value falls below the lower ISOBUS limit. |

## Functionality

1. **Initialization** (`INIT`): The function block is initialized with the object pool properties (`stObj`). The event is forwarded directly to the inner block `Q_NumericValue_PHYS_LREAL`. Upon successful initialization, `INITO` is triggered.

2. **Value Change**: As soon as the event `E1` arrives at the adapter `lrPhys`, the physical LREAL value is transferred to the inner block via the data connection `lrPhys.D1`, triggering the event `REQ`.

3. **Result**: The inner block performs the actual processing. The status (`STATUS`) and the return value (`s16result`) are output via `CNF`. Simultaneously, the plugs `xUnder` and `xOver` can signal whether the incoming value violates the defined ISOBUS limits.

4. The output events of the inner block (`INITO`, `CNF`, `xUnder.E1`, `xOver.E1`) are forwarded directly to the corresponding outputs of `Q_NumericValue_PHYSA_LREAL`.

## Technical Features
- **Wrapper Design**: The block encapsulates the function block `Q_NumericValue_PHYS_LREAL` and provides a more convenient physical interface via adapters.
- **Adapter-based communication**: Value input and limit signaling are handled via unidirectional adapters (`ALR`, `AX`), which facilitates encapsulation and reuse in different contexts.
- **Configurable object pool parameters**: The object ID, scaling, offset, and decimal places are defined via `stObj`, allowing the block to be flexibly adapted to various sensor or actuator values.
- **Standard compliance**: The function block (FB) is developed according to ISO 11783-6 (ISOBUS) and optimized for agricultural applications.

## State overview
An explicit state machine is not represented in the XML, as the FB is implemented as a pure network consisting of an internal building block. However, the typical behavior follows a simple sequence:

- **Idle** – waits for INIT.
- **Initialized** – after INIT and before the first value changes.
- **Processing** – from the E1 trigger (REQ) until the CNF event is received.
- **Completion** – output of STATUS/s16result via CNF, followed by readiness resumption.

## Application Scenarios
- **ISOBUS Command**: Changing a setpoint (e.g., speed, position, pressure) in an agricultural control unit, where the value is available as a physical quantity (LREAL).
- **Limit Monitoring**: Used in applications that require additional alarms or responses when permissible range limits are exceeded (e.g., for sensor data) (via `xOver` / `xUnder`).
- **Scaled Values**: Using scaling and offset parameters to convert raw ISOBUS values into user-friendly physical units.

## Comparison with Similar Function Blocks
In direct comparison to the inner function block **Q_NumericValue_PHYS_LREAL**, the **Q_NumericValue_PHYSA_LREAL** offers a higher level of abstraction:

- Instead of direct input/output signals, communication is implemented via adapters – this allows for loose coupling in modular control architectures.
- The outer function block does not add its own logic, but simplifies integration through the adapter-based interface (e.g., `ALR` input).
- Unlike pure function blocks with fixed data ports, `Q_NumericValue_PHYSA_LREAL` can be flexibly adapted to different environments without having to change the signal paths in the network.

## Conclusion
The **Q_NumericValue_PHYSA_LREAL** is a practical wrapper function block that simplifies physical value changes in the ISOBUS context via adapters. It combines the proven logic of `Q_NumericValue_PHYS_LREAL`With a convenient, adapter-based interface for LREAL inputs and limit signaling. Thanks to its configurable object pool parameters and compliance with ISO 11783-6, it is particularly suitable for use in modular agricultural control systems.
# AUDI_UDINT_EQ
![AUDI_UDINT_EQ](./AUDI_UDINT_EQ.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_UDINT_EQ** compares two values of type `UDINT` for equality. The first value is obtained via a socket adapter (`IN1`), the second via the direct data input `IN2`. The result is output as a Boolean value via a plug adapter (`OUT`). The comparison is triggered by an event – either by the external event `REQ` or by an event from the socket adapter `IN1`.
## Interface Structure
### **Event Inputs**

| Event | Description |

|-------|--------------|

| `REQ` | Service Request: Starts the comparison. The value of `IN2` is compared with the current value of the adapter `IN1`. |

Note: The comparison can also be started by an event from the socket adapter `IN1` (its event `E1`). This is internally wired in the FB network and allows for event-driven updates when the input value changes.

### **Event Outputs**
The FB does not have direct event outputs. The result of the comparison is output via the plug adapter `OUT`, which carries the event `E1` (see adapter). The output event is generated after the comparison is complete.

### **Data Inputs**

| Name | Type | Description |

|------|-----|--------------|

| `IN2` | `UDINT` | Second comparison value (direct input). |

Note: The first comparison value is obtained via the socket adapter `IN1` (whose data input is `D1`).

### **Data Outputs**
No direct data outputs. The comparison result (BOOL) is output via the plug adapter `OUT` (its data output is `D1`).

### **Adapter**

| Type | Direction | Description |

|-----|----------|--------------|

| `IN1` – Socket | Input | Adapter of type `adapter::types::unidirectional::AUDI`. Provides the first comparison value (data input `D1`) and can send an event (`E1`) to start the comparison.

| `OUT` – Plug | Output | Adapter of type `adapter::types::unidirectional::AX`. Outputs the comparison result as a Boolean value (`D1`) and generates an event (`E1`) upon completion. |

## Functionality

1. The function block waits for a start event – either at the external event input `REQ` or at the event `E1` of the socket adapter `IN1`.

2. Upon receiving the event, the values `IN1.D1` (from the adapter) and `IN2` (from the direct input) are passed to the internal comparison block `F_EQ` (of type `iec61131::comparison::F_EQ`).

3. The data output of `F_EQ` is `true` if both values are equal; otherwise, it is `false`.

4. This result is passed to the data output `OUT.D1` of the plug adapter.

5. Simultaneously, the event `OUT.E1` is triggered to inform the output side about the completed result.

## Technical Features
- **Adapter-Based Input/Output**: Instead of direct data ports, adapters are used for the first input and output variables. This enables loose coupling and easy reuse in different contexts (e.g., bus systems or encapsulated values).
- **Dual Triggering Options**: The comparison can be triggered via the external event `REQ` or via an event from the input adapter `IN1`. This allows the function block to operate either cyclically or on a change-driven basis.
- **Unidirectional Adapters**: Both the socket (`IN1`) and the plug (`OUT`) are declared as unidirectional adapters, which defines a clear data and event flow direction.

**Unidirectional Adapters**:** - **Internal use of `F_EQ`**: The actual comparison is implemented using the IEC 61131-3 standard function block `F_EQ`, which is specifically designed for 64-bit comparisons (though here it is applied to `UDINT`).

## State Overview
The function block does not have an explicit state machine. It operates purely event-driven:

- **Idle**: Waiting for an event (`REQ` or `IN1.E1`).
- **Completion**: As soon as an event arrives, the comparison is executed and the result is passed to `OUT`.
- **Completion**: After outputting the result and the subsequent event, the function block immediately returns to the idle state.

## Application Scenarios
- **Monitoring Two Measured Values**: A sensor value (e.g., rotational speed) is read via the `IN1` adapter, and a setpoint value via `IN2`. A signal is generated when the values are equal.
- **Modular Coupling**: The module can be embedded in larger networks, where adapters serve as standardized interfaces between components.
- **Event-Driven Processes**: When the input value `IN1` changes, a comparison can be triggered automatically without requiring an external clock.

## Comparison with Similar Modules
- **`F_EQ` (Direct)**: The standard comparison module expects two scalar inputs and provides a Boolean output. The `AUDI_UDINT_EQ` encapsulates this and extends it with adapters for more flexible integration.
- **`AUDI_UDINT_NE` (Not Equal)**: An analogous block for not equal comparison; the interface and functionality are identical, only the comparison logic differs.
- **Blocks with Direct Data Input**: Conventional comparison blocks (e.g., `EQ`, `NE`) often only use direct data ports; the adapter approach increases reusability in heterogeneous systems.

## Conclusion
The `AUDI_UDINT_EQ` is an event-driven comparison block for `UDINT` values that utilizes the flexibility of adapters. Thanks to its dual triggering capability and standardized adapter interface, it is particularly suitable for modular and expandable automation solutions. The internal use of the proven `F_EQ` module guarantees reliable, standards-compliant comparison logic.
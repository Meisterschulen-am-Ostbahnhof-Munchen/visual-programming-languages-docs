# UDINT_AUI_LE
![UDINT_AUI_LE](./UDINT_AUI_LE.svg)
* * * * * * * * * *
## Introduction
The function block **UDINT_AUI_LE** performs a less-than-equal-to comparison of two values. It is classified as a standard comparison function according to IEC 61131-3 and is specifically designed for use with adapter interfaces. The block encapsulates an internal `F_LE` comparison block and provides its functionality via a unidirectional input adapter (socket) and a unidirectional output adapter (plug).
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| `REQ` | Event | Service Request – triggers the comparison |

### **Event Outputs**

This function block (FB) does not have its own independent event outputs. The result event is signaled via the output adapter `OUT.E1`.

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `IN1` | ANY_ELEMENTARY | First comparison value (any elementary data type) |

### **Data Outputs**

This function block (FB) does not have its own independent data outputs. The result (Boolean) is provided via the output adapter `OUT.D1`.

### **Adapters**

| Adapter | Type | Direction | Comment |

|---------|-----|----------|-----------|

| `IN2` | `adapter::types::unidirectional::AUI` | Socket (Input) | Second comparison value, provided via the adapter as data point `D1` and event `E1` |

| `OUT` | `adapter::types::unidirectional::AX` | Plug (Output) | Outputs the comparison result as a Boolean value (`D1`) and an acknowledgment event (`E1`) |

## Functionality

The function block performs a comparison `IN1 <= IN2`. The comparison is triggered either by an event at input `REQ` or by an incoming event from adapter `IN2.E1` (e.g., after a value update). The internal block `F_LE` (type `iec61131::comparison::F_LE`) compares the two values and sets the result to `OUT.D1`. Simultaneously, the event output `OUT.E1` signals that a new result is available.

The logic corresponds to an OR operation of the two trigger sources – both the explicit call via `REQ` and the implicit update of the input adapter trigger the comparison. This enables flexible control of the comparison process.

## Technical Features
- **Adapter-based interface**: Instead of direct input/output variables, adapters (Socket `IN2`, Plug `OUT`) are used. This makes the function block particularly suitable for use in modular and reusable components.
- **Dual triggering**: The comparison is triggered by both the `REQ` event and the input adapter event. This prevents data loss and simplifies connection to continuously updated data sources.
- **ANY_ELEMENTARY for IN1**: The first input accepts any elementary data type (e.g., INT, REAL, UDINT), making the function block universally applicable.
- **No dedicated event or data outputs**: All external communication takes place exclusively via the adapters, which improves encapsulation.

## State Overview

The function block (FB) does not have an explicit state machine; its behavior is purely functional:

1. **Idle**: Waiting for a trigger signal (either `REQ` or `IN2.E1`).

2. **Comparison**: The internal block `F_LE` is executed as soon as a trigger is received.

3. **Output**: The result (`True` if `IN1 <= IN2`, otherwise `False`) is set to `OUT.D1`, and the event `OUT.E1` is triggered.

4. Return to **Idle**.

## Application Scenarios
- **Limit Value Monitoring**: The current measured value is entered via `IN1` (e.g., as `REAL`), and the limit value is entered via the adapter `IN2` from a higher-level controller. The output signal `OUT.D1` indicates whether the limit value has been reached or fallen below.
- **Comparison in Modular Systems**: In a distributed automation application, different function block types can communicate via adapters. This block serves as a standardized comparison component with a uniform interface.
- **Data-Driven Logic**: Automatic triggering via `IN2.E1` enables reactive execution as soon as the second comparison value changes – without cyclic polling.

## Comparison with Similar Function Blocks

Compared to the direct `F_LE` function block from the IEC 61131-3 library, which uses standard inputs/outputs, `UDINT_AUI_LE` offers adapter-based encapsulation. This facilitates integration into hierarchical function block networks and reusability in different contexts. Dual triggering (via `REQ` and adapter events) extends the purely event-driven functionality of `F_LE` and increases flexibility.

## Conclusion

The `UDINT_AUI_LE` function block is a powerful and flexible component for comparison operations in automation technology. The use of unidirectional adapters provides a clear and standardized interface, making it particularly suitable for modular and distributed architectures. The combination of explicit triggering and automatic updating via the input adapter makes the FB versatile and robust against data changes.
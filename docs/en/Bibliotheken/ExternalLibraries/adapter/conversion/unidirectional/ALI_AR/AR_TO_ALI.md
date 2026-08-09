# AR_TO_ALI

![AR_TO_ALI](./AR_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The composite function block `AR_TO_ALI` converts a REAL adapter (`AR-IN`) into a LINT adapter (`ALI-OUT`). It enables the seamless integration of floating-point values from adapter `AR` into applications that expect 64-bit integer values via adapter `ALI`. The conversion is performed via an internal function block `F_REAL_TO_LINT` according to IEC 61131.
## Interface Structure

The function block does not have any independent event or data inputs/outputs at the block level. All signal transmission occurs via adapter sockets or plugs.

### **Event Inputs**

No dedicated event inputs. The event is received via socket `AR_IN` (interface `E1`).

### **Event Outputs**

No dedicated event outputs. The event is sent via plug `ALI_OUT` (interface `E1`).

### **Data Inputs**

No dedicated data inputs. Data is received via socket `AR_IN` (interface `D1`).

### **Data Outputs**

No dedicated data outputs. The data is sent via the plug `ALI_OUT` (interface `D1`).

### **Adapter**

| Direction | Label | Type | Compatible Adapter Type | Description |
|----------|-------------|-----|------------------------|--------------|
| Socket | `AR_IN` | `adapter::types::unidirectional::AR` | AR Adapter (REAL) | Receiving adapter for the REAL value. |
| Plug | `ALI_OUT` | `adapter::types::unidirectional::ALI` | ALI Adapter (LINT) | Providing adapter for the converted LINT value. |

## Functionality

The function block `iec61131::conversion::F_REAL_TO_LINT` is instantiated within the internal network. As soon as an event occurs at socket `AR_IN` (via interface `E1`), the internal conversion block is triggered using the designated event connection `AR_IN.E1 -> Convert.REQ`. Simultaneously, the data value `AR_IN.D1` is passed to input `Convert.IN`. After the conversion (REAL → LINT) is complete, the converter confirms with the event `Convert.CNF`. This event is forwarded to plug `ALI_OUT.E1`, and the converted value `Convert.OUT` is output to `ALI_OUT.D1`.

## Technical Features

- **Pure Adapter Coupling**: The function block does not use direct event or data inputs, but communicates exclusively via the standardized unidirectional adapters `AR` and `ALI`. This makes it easy to integrate into existing adapter structures.
- **IEC 61131 Compliance**: The conversion block used, `F_REAL_TO_LINT`, complies with the IEC standard and ensures a standardized, deterministic conversion.
- **Runtime Behavior**: The conversion is event-driven and occurs without any additional delay. The output value is available in the same execution cycle in which the input event is received.

## State Overview

The Composite FB itself does not have its own state machine. Its behavior is entirely determined by its internal circuitry. The following logical states exist:

- **Idle**: No event at the input. The output `ALI_OUT` remains unchanged.
- **Converting**: An event is received at socket `AR_IN`. The internal converter is activated, and the conversion process begins.
- **Completed**: The conversion is complete; the output event is sent, and the new data value is available at the plug.

## Application Scenarios

- **Sensor-Actuator Coupling**: A REAL adapter (e.g., from an analog sensor) must be connected to a control module that processes only LINT values via the ALI adapter.
- **Protocol Conversion**: In heterogeneous automation networks where data formats need to be converted to connect different adapter types.
- **Test and Simulation Environments**: Replacing an ALI adapter with a simulated REAL adapter and converting back for testing purposes.

## Comparison with Similar Function Blocks

| FB | Conversion | Interface | Note |
|----|---------------|---------------|-----------|
| `AR_TO_ALI` | REAL → LINT | AR / ALI Adapter | Specifically for Adapter Coupling |
| `F_REAL_TO_LINT` | REAL → LINT | Standalone I/O (REQ/CNF, IN/OUT) | Direct converter without adapters |
The `AR_TO_ALI` encapsulates the `F_REAL_TO_LINT` and adds the adapter connections. The advantage lies in its simple, adapter-network-compatible connection. A direct converter without adapters would not be usable in adapter structures. |

## Conclusion

The `AR_TO_ALI` is a compact, purpose-built composite function block that enables the conversion of REAL to LINT values via the standardized unidirectional adapters `AR` and `ALI`. Its clean encapsulation and the use of an IEC-compliant core component provide a reliable and reusable solution for industrial automation. The FB is particularly suitable for scenarios where a clean separation between data format and adapter interface is required.

# AQ_TO_AB
![AQ_TO_AB](./AQ_TO_AB.svg)

* * * * * * * * * *
## Introduction
The function block `AQ_TO_AB` converts an AQ adapter (Quarter Byte) to an AB adapter (BYTE). It enables the seamless connection of components using different adapter interfaces by passing the signals through unchanged. The block is implemented as a pure "pass-through" function block that does not manipulate any data.
## Interface Structure
### **Event Inputs**
The function block has no explicit top-level event inputs. Events are transmitted via the adapter interfaces.

## **Event Outputs**
The function block has no explicit top-level event outputs. Events are transmitted via the adapter interfaces.

### **Data Inputs**
The FB has no explicit top-level data inputs. Data transmission occurs via the adapter interfaces.

### **Data Outputs**
The FB has no explicit top-level data outputs. Data transmission occurs via the adapter interfaces.

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AQ` | IN | Input (Socket) | AQ adapter as input interface for quarter-byte data |
| `adapter::types::unidirectional::AB` | OUT | Output (Plug) | AB adapter as output interface for byte data |

## Functionality

The function block internally connects the event and data channels of the input adapter `IN` directly to the corresponding channels of the output adapter `OUT`. Specifically, the following connections are established:

- Event connection: `IN.E1` → `OUT.E1`
- Data connection: `IN.D1` → `OUT.D1`

Thus, all incoming events and data from the AQ adapter are passed on to the AB adapter unchanged. The function block itself does not process or convert the user data – it functions solely as an interface adapter.

## Technical Features
- **Unidirectional Data Flow:** The function block supports only one direction (AQ → AB).
- **No State Change:** Since no logic or memory is present, this is a purely combinational function block.
- **Simple Loop-Through:** The implementation is limited to two direct connections in the FBNetwork.
- **Adapter Conversion:** The function block allows the integration of AQ-compatible components into a system that expects AB adapters without requiring any modifications to the connected function blocks.

## State Overview
The function block does not have a state machine. Its behavior is deterministic: Every incoming event immediately triggers the corresponding output event, and every incoming data value is forwarded to the output without delay.

## Application Scenarios
- **System Integration:** Connecting a sensor module with an AQ interface to a controller that uses AB adapters.
- **Protocol Implementation:** Use in libraries to make different adapter types compatible.
- **Test Environments:** Use as a simple adapter in test setups to adapt interfaces.

#
# State Overview ## Comparison with Similar Function Blocks
- **AB_TO_AQ:** Performs the reverse conversion (AB → AQ).
- **AQ_TO_BYTE_EXT:** A hypothetical function block that additionally performs data conversions (e.g., scaling, formatting), while `AQ_TO_AB` only changes the interface.
- **Generic Adapter Wrappers:** Other platforms often offer generic conversion blocks, but these require more complex configuration. `AQ_TO_AB` is specialized and therefore very lightweight.

## Conclusion
The function block `AQ_TO_AB` offers a lean and efficient solution for adapter conversion from AQ to AB. Its simple pass-through structure makes it reliable, resource-efficient, and ideal for situations where only the interface type needs to be changed without affecting the signals. It is particularly suitable for modular systems with different adapter standards.

# AUDI_TO_AULI
![AUDI_TO_AULI](./AUDI_TO_AULI.svg)
*Image not available*
* * * * * * * * * *
## Introduction
This composite function block converts an AUDI adapter (UDINT) to an AULI adapter (ULINT). It serves as an interface between components that use different adapter types for unsigned integers. The function block is licensed under the Eclipse Public License 2.0 (EPL 2.0) and is provided by HR Agrartechnik GmbH.
## Interface Structure
### **Event Inputs**
None (events are received via the AUDI_IN adapter).

## **Event Outputs**
None (events are sent via the AULI_OUT adapter).

## **Data Inputs**
None (data is received via the AUDI_IN adapter).

#
# ### **Data Outputs**

None (data is sent via the AULI_OUT adapter).

### **Adapters**
- **AUDI_IN** (Socket): Receives an AUDI adapter (type: `adapter::types::unidirectional::AUDI`). Contains one event input (E1) and one data input (D1) of type UDINT.
- **AULI_OUT** (Plug): Sends an AULI adapter (type: `adapter::types::unidirectional::AULI`). Contains one event output (E1) and one data output (D1) of type ULINT.

## Functionality
The function block forwards incoming events and data from the AUDI_IN adapter directly to the AULI_OUT adapter:

- The event `E1` from `AUDI_IN` is transferred to `E1` from `AULI_OUT`.
- The data value `D1` (UDINT) from `AUDI_IN` is transferred to `D1` (ULINT) from `AULI_OUT`. The 32-bit UDINT value is implicitly converted to the 64-bit ULINT value (null extension). No additional logic is performed.

...
## Technical Features
- **Composite FB**: Contains no function block logic or state machine, but merely wiring between two adapters.
- **Package**: `adapter::conversion::unidirectional`
- **Version**: 1.0, created on 2026-02-17.
- **License**: EPL 2.0.

## State Overview
The FB has no internal state or algorithm. It operates strictly in a flow-oriented manner and reacts immediately to every incoming event.

## Application Scenarios
- **System Integration**: If one system component provides data via an AUDI adapter (UDINT), but another component expects an AULI adapter (ULINT), this FB acts as a bridge.
- **Protocol Adaptation**: Use in control systems that use different integer widths for buses or interfaces (e.g., 32-bit to 64-bit).

## Comparison with Similar Function Blocks
- **Simple Data Type Converters** (e.g., `UDINT_TO_ULINT`): These only convert data without adapters. This function block operates at the adapter level and also forwards events.
- **Adapter Transceivers**: Other function blocks could perform more complex conversions (e.g., scaling, offsetting). This function block is minimal.

## Conclusion

`AUDI_TO_AULI` is a practical composite function block for lossless conversion from UDINT to ULINT at the adapter level. It is simple, easy to understand, and ideal for clean interface separation in modular systems.

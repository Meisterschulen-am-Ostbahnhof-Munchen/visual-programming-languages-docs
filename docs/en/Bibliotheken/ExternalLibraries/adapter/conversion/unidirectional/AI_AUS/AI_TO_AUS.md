# AI_TO_AUS
![AI_TO_AUS](./AI_TO_AUS.svg)
*Image of the function block – not included in the XML, therefore no automatically generated image is available.*
* * * * * * * * * *
## Introduction
The **AI_TO_AUS** function block is a composite function block that converts an **AI adapter** (data stream of type `INT`) into an **AUS adapter** (data stream of type `USINT`). It serves as a bridge between components that use different data types for analog input and output signals. The implementation uses the internal function block `F_INT_TO_USINT` from the `iec61131::conversion` library.

## Interface Structure

The function block does not have its own separate event or data ports, but communicates exclusively via adapters.

### **Event Inputs**
- No direct event inputs. Event control is handled indirectly via the `AI_IN` adapter (socket) – this is where the event `E1` is received.

### **Event Outputs**
- No direct event outputs. The converted event is output as `E1` via the `AUS_OUT` adapter (plug).

### **Data Inputs**
- No direct data inputs. The data value to be converted (`INT`) is obtained as `D1` via the `AI_IN` adapter (socket).

### **Data Outputs**
- No direct data outputs. The converted value (`USINT`) is provided as `D1` via the adapter `AUS_OUT` (Plug).

### **Adapters**
- **`AI_IN`** (Socket)

Type: `adapter::types::unidirectional::AI`

Description: Accepts a `INT` value and an associated event.

- **`AUS_OUT`** (Plug)

Type: `adapter::types::unidirectional::AUS`

Description: Outputs the converted `USINT` value along with an event.

## Functionality

1. An incoming event at the adapter `AI_IN.E1` triggers the internal function block `Convert` (`F_INT_TO_USINT`) via its event input `REQ`.

2. Simultaneously, the data value `AI_IN.D1` (type `INT`) is passed to the input `IN` of the conversion block.

3. The block `F_INT_TO_USINT` performs the type conversion from `INT` to `USINT`.

4. After the conversion is complete, `Convert` sends an acknowledgment event (`CNF`) to the output adapter, and the converted value (`OUT`) is forwarded to `AUS_OUT.D1`.

5. The event `AUS_OUT.E1` signals to the subsequent component that a new data value is available at the adapter.

## Technical Features
- **Library Used:** The function block uses the IEC 61131 standard function block `F_INT_TO_USINT`, which implements a typical conversion with possible range limitation or overflow behavior.
- **Adapter Encapsulation:** The composite block abstracts the conversion at the adapter level, so only the two matching adapters need to be connected in the network configuration.
- **Data Range Conflict:** `INT` encompasses values from -32,768 to +32,767, while `USINT` can only represent 0…255. For input values outside the USINT range, the behavior depends on `F_INT_TO_USINT` (e.g., saturation to 0 or 255, or modular overflow). The exact mapping rule must be verified in the specific target system.

## State Overview

Since the block consists exclusively of sequential data processing (repeated conversion with each event), it does not have its own state machines. The states of the internal block `F_INT_TO_USINT` are not visible to the function; the composite block operates event-driven and without internal state storage.

## Application Scenarios
- **Sensor-Actuator Coupling:** A sensor provides measured values as `INT` (e.g., temperature −10…50 °C scaled to integers), while a downstream actuator expects a control variable as `USINT` (e.g., 0…100%). The block handles the necessary type conversion.
- **Adapter Compatibility:** In a 4diac application, two modules are defined via different adapters (`AI` and `AUS`). The Composite Function Block (FB) enables direct connection without additional conversion logic in the main network.

## Comparison with Similar Function Blocks
- **Direct Converters (`F_INT_TO_USINT`):** Provides pure type conversion at the data level but requires separate event and data connections. `AI_TO_AUS` extends this with adapter connectivity, thus simplifying network design.
- **Other Adapter Converters (`AI_TO_...`, `..._TO_AUS`):** Depending on the required adapter types, corresponding Composite Function Blocks are conceivable. `AI_TO_AUS` covers the specific combination `INT` → `USINT`.

## Conclusion

The **AI_TO_AUS** function block is a compact composite module for easy adapter conversion from `INT` to `USINT`. It encapsulates the IEC 61131 converter and provides data and event flows via standardized adapters. This significantly simplifies the integration of components with different analog interfaces into 4diac applications. When using this module, potential data type overflow should be considered.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

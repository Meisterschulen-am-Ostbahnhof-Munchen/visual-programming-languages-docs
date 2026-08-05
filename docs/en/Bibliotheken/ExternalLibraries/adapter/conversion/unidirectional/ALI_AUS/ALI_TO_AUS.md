# ALI_TO_AUS
![ALI_TO_AUS](./ALI_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The **ALI_TO_AUS** is a composite function block according to IEC 61499, used to convert an **ALI adapter** (data of type **LINT**, Long Integer) into an **AUS adapter** (data of type **USINT**, Unsigned Short Integer). The block encapsulates the necessary conversion logic to enable a simple and type-safe connection between differently typed adapter interfaces.
## Interface Structure

### **Event Inputs**
- **ALI_IN.E1** (via adapter socket) – triggers the conversion as soon as an event arrives from the connected ALI source.

### **Event Outputs**
- **AUS_OUT.E1** (via adapter plug) – signals the completion of the conversion to the downstream OFF sink.

### **Data Inputs**
- **ALI_IN.D1** (via adapter socket) – the LINT (Long Integer) value to be converted.

### **Data Outputs**
- **AUS_OUT.D1** (via adapter plug) – the converted USINT (Unsigned Short Integer) value.

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| **Socket (Input)** | ALI_IN | adapter::types::unidirectional::ALI | Receives the LINT data value and the associated event |
| **Plug (Output)** | OFF_OUT | adapter::types::unidirectional::OFF | Provides the converted USINT value and the confirmation event |

## Functionality

The function block internally contains an instance of the function block **F_LINT_TO_USINT** from the IEC 61131 conversion library. The process is as follows:

1. An event **ALI_IN.E1** triggers the data transfer.

2. The LINT value present at **ALI_IN.D1** is forwarded to the input **IN** of the internal converter.

3. The internal function block performs the type conversion from LINT to USINT (taking value range limits into account).

4. After successful conversion, the internal function block generates a **CNF** event, which is output as **OFF_OUT.E1**.

5. The converted result is sent from **OUT** of the internal block to **AUS_OUT.D1**.

Event and data flows are coupled entirely via the internal network; the user only sees the two adapter interfaces.

## Technical Features
- **Reusable Converter**: The block uses the standardized **F_LINT_TO_USINT** (iec61131::conversion), so the conversion logic does not need to be reimplemented.
- **Adapter-Based**: The entire interface is implemented as a unidirectional adapter, simplifying exchange and reuse in larger systems.
- **License**: The block is provided under the **Eclipse Public License 2.0** (EPL-2.0).

## State Overview

Since this is a composite block, there is no explicit top-level state machine. The internal converter **F_LINT_TO_USINT** operates in an event-driven manner and performs exactly one conversion step after each **REQ** event. The function block remains inactive as long as no event is present.

## Application Scenarios
- **Interface Adaptation**: Connecting components that use **LINT** (e.g., high-resolution counters) to those that expect **USINT** (e.g., simple actuator controllers).
- **System Integration**: When a predefined adapter type (ALI) is available and a different adapter type (AUS) is required – e.g., when combining modules from different manufacturers.
- **Protocol Conversion**: Used in data preprocessing chains where long integer values need to be mapped to a smaller range.

## Comparison with Similar Function Blocks

Numerous data type-specific conversion blocks exist (e.g., LINT_TO_INT, LINT_TO_DINT, USINT_TO_LINT). The **ALI_TO_AUS** stands out because it not only encapsulates the pure type conversion but also embeds it directly into an **adapter interface**. This reduces the wiring effort at the block level and increases the readability of the overall design.

## Conclusion

The **ALI_TO_AUS** is a practical and robust function block for converting LINT adapter data to USINT adapter data. By using a standardized converter and clear adapter encapsulation, a reusable, type-safe, and easy-to-maintain solution is provided for various control systems.

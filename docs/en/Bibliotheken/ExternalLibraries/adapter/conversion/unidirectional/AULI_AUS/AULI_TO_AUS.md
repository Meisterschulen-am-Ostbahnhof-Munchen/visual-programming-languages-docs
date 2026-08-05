# AULI_TO_AUS
![AULI_TO_AUS](./AULI_TO_AUS.svg)

* * * * * * * * * *
## Introduction
The **AULI_TO_AUS** function block is a composite function block that performs a conversion from an **AULI adapter** (ulint, 64-bit unsigned) to an **AUS adapter** (usint, 8-bit unsigned). It encapsulates the IEC 61131 function **F_ULINT_TO_USINT** in an adapter-based environment, enabling data exchange via standardized adapters.
## Interface Structure
The function block has no direct event or data inputs/outputs at the FB level. All communication takes place via the two adapters.

### **Event Inputs**
- via **Socket AULI_IN** (Type AULI): Event **E1** – initiates data transfer and conversion.

### **Event Outputs**
- via **Plug AUS_OUT** (Type AUS): Event **E1** – is triggered as soon as the converted value is present at the output.

### **Data Inputs**
- via **Socket AULI_IN** (Type AULI): Data input **D1** (ULINT) – the 64-bit value to be converted.

### **Data Outputs**
- via **Plug AUS_OUT** (Type AUS): Data output **D1** (USINT) – the converted 8-bit value.

### **Adapter**

| Name | Type | Direction | Description |

|-------------|------------|-----------|----------------------------------|

| AULI_IN | AULI | Socket | Input adapter for ULINT data |

| AUS_OUT | AUS | Plug | Output adapter for USINT data |

## Functionality
1. The FB receives an event at **E1** via the **AULI_IN** socket. Simultaneously, the corresponding ULINT value is provided at **D1**.

2. This event is forwarded to the internal function block **F_ULINT_TO_USINT** (name: `Convert`) (via the event connection `REQ`).

3. The ULINT value is passed to the **IN** data input of the converter.

4. After the conversion is complete, the converter generates the **CNF** event.

5. This event is transferred to the **AUS_OUT** plug at its **E1** event input, while the converted USINT value is transferred from the **OUT** output of the converter to the **D1** data output of the plug.

6. The connected receiver can now process the event and the USINT value.

## Technical Features
- **Composite Block** – It contains an internal instance of **F_ULINT_TO_USINT** from the IEC 61131 library.
- **Adapter-Based Communication** – No direct data/events at the top-level function block; input/output is handled exclusively via the supplied adapters (AULI / AUS).
- **Data loss possible** – Since the USINT data type only comprises 8 bits, values > 255 are lost (truncated or wrapped around, depending on the converter implementation).
- **No dedicated state machine** – The function block (FB) is a pure network of existing blocks and does not have its own state machine.

## State overview
Due to its composite nature and the lack of a dedicated state machine, a state overview is not available. Its behavior is entirely determined by the internal FB **F_ULINT_TO_USINT**.

## Application scenarios
- **Integration of ULINT data sources** (e.g., high-resolution counters, timestamps, or large sensor data) into an automation system that can only process USINT values due to memory or protocol limitations.
- **Adapter conversion** in a distributed application to mediate between two different adapter types (AULI ↔ AUS) without changing the underlying logic.
- **Prototypical conversions** from 64-bit to 8-bit data paths during development.

## Comparison with similar components
Similar components such as **AULI_TO_AINT** (ULINT → AINT) or **AULI_TO_AWORD** (ULINT → AWORD) implement analogous conversions for other output types. This component specializes in **USINT** – a particularly memory-efficient target variable. Unlike direct application-level data conversion, the adapter-based approach offers a structured, reusable interface encapsulation that facilitates the exchange of data streams in standardized industrial protocols.

## Conclusion

**AULI_TO_AUS** is a practical composite component that embeds an IEC 61131 conversion function in an adapter-based environment. It enables the transparent conversion of ULINT to USINT values via the corresponding adapters and is particularly suitable for scenarios where high accuracy or large value ranges need to be reduced to a smaller data format. The component is easy to use but requires attention to potential data loss.

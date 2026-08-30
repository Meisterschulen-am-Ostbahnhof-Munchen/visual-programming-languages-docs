# hsv2rgb

<img width="1412" height="272" alt="image" src="https://github.com/user-attachments/assets/d564035b-fcbb-4237-a4be-75da3e2fd29d" />
* * * * * * * * * *
The function block `hsv2rgb` is a utility block for color space conversion. It converts a color defined in the HSV color model (Hue, Saturation, Value) into the corresponding values of the RGB color model (Red, Green, Blue). This is particularly useful for applications that need to control colors based on their perceptual properties (hue, saturation, brightness), while output devices (such as LEDs or displays) expect RGB values.
![hsv2rgb](hsv2rgb.svg)

- **REQ (Service Request):** Triggers the conversion calculation. This event updates the current values at data inputs `hue`, `saturation`, and `value`.
- **CNF (Confirmation of Requested Service):** Triggered once the conversion is complete. This event outputs the calculated RGB values at data outputs `r`, `g`, and `b`.
- **hue (UDINT):** The hue in the HSV model. The value range is not predefined in the function block, but typically a range of 0-360° or 0-65535 is used.
- **value (UDINT):** The brightness value in the HSV model. Typical range: 0-100% or 0-255.
- **r (UDINT):** The calculated red component in the RGB model.
- **g (UDINT):** The calculated green component in the RGB model.
- **b (UDINT):** The calculated blue component in the RGB model.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block does not use adapters.

The block operates in an event-driven manner. The internal algorithm starts when the `REQ` event occurs. It receives the HSV values at the data inputs and calculates the corresponding RGB values according to the standardized HSV-to-RGB conversion algorithm. After the calculation is complete, the results are output at the data outputs `r`, `g`, and `b`, and the `CNF` event signals that the new values are valid and ready for retrieval.

- **Data Type:** All input and output data are of type `UDINT` (unsigned double integer, 32-bit). This enables high resolution and accuracy in color representation.
- **Value Range:** The module itself does not define any scaling or limiting of the value ranges for HSV or RGB. The interpretation of the numerical values (e.g., 0-360 for Hue, 0-255 for RGB) is the responsibility of the connecting application. The conversion algorithm must be designed accordingly for the expected input range.
- **Deterministic Behavior:** The execution is deterministic and always produces the same RGB output values for identical input values.

The function block has a simple, stateless sequence:

1. **Wait State:** The block waits for the `REQ` event.
2. **Calculation State:** At `REQ`, the input data is read and the conversion is performed. This state is transient.
3. **Output State:** The results are written to the outputs and the `CNF` event is generated. The module immediately returns to standby mode.
- **Color Control of RGB LEDs:** User-friendly color selection via HSV parameters (e.g., rotary encoder or touch interface) with subsequent conversion for LED control.
- **Visualization Systems:** Conversion of alarm or status colors defined in HSV for display on RGB monitors or panels.
- **Industrial Lighting:** Dynamic lighting control in production or logistics environments, where color transitions are intuitively defined via brightness and saturation.
*

Unlike general-purpose computing blocks (such as `MUL`, `ADD`) or scalers, `hsv2rgb` is an application-specific block that encapsulates a complex, non-linear algorithm. It saves the user the time-consuming and error-prone implementation of the conversion to Structured Text or other languages. A direct counterpart, `rgb2hsv`, for the reverse conversion would be a similarly specialized block.

- [Exercise_031](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_031.md)

The `hsv2rgb` function block is a useful and specialized tool for all 4diac applications involving color manipulation. By encapsulating the conversion algorithm in a standardized IEC 61499 block, it significantly simplifies programming, promotes reusability, and increases software reliability. Its use is recommended where intuitive, human-perceived color control meets device-oriented RGB output.

---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## 🛠️ Zugehörige Übungen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

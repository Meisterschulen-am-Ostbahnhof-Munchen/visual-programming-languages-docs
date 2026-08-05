# all_colours
![all_colours](./all_colours.svg)
* * * * * * * * * *
## Introduction
The GlobalConstants block **all_colours** provides an extensive color palette with 256 defined colors (0 to 255). Each color is defined as a constant of type `USINT` and has a fixed numerical value. The comments contain the corresponding hexadecimal code, the RGB value, and English and German color names. Colors 0 to 231 correspond to the standardized ISOBUS color space, while colors 232 to 255 are reserved for manufacturer-specific purposes and are assigned a neutral gray.
## Interface Structure
### **Event Inputs**
None.

#### **Event Outputs**
None.

#### **Data Inputs**
None.

### **Data Outputs**
The colors are not provided via dedicated output variables, but are declared as global constants (`COLOR_0` … `COLOR_255`). These can be directly referenced by other function blocks.

### **Adapters**
None.

## Functionality
The function block declares the constants at system startup. The values are pre-initialized and remain unchanged throughout runtime. All constants are immediately valid and can be used in other function blocks without additional initialization. The numbering follows the ISOBUS standard, with the first 16 colors (0–15) covering the basic palette and the subsequent colors (16–231) containing more finely graduated shades.

### **Adapters**

# ## Technical Features
- **Type:** `USINT` (0–255)
- **Standard Compliance:** Colors 0–231 are defined according to ISOBOBus; the remaining 24 entries (232–255) are manufacturer-specific and set to the same gray value (`#808080`).
- **Naming:** The designations `COLOR_0` … `COLOR_255` enable simple numerical referencing in algorithms or visualizations.
- **No Runtime Dependency:** The function block has no internal states or algorithms – it serves solely to provide constants.

## State Overview

This function block has no state machines, as it is a purely declarative collection of constants.

## Application Scenarios
- **ISOBUS-compliant UI development** in agricultural technology (terminals, machine controls)
- **Color coding of status information** (e.g., green = active, red = alarm, yellow = warning)
- **Standardization of colors** across multiple components or projects – all participants use the same color definition.

## Comparison with similar function blocks

Unlike a typical `FUNCTION_BLOCK`, which processes input/output data and is controlled by events, `all_colours` is a **GlobalConstants** function block. It has no dynamic interfaces and no executable logic. Similar function blocks include, for example, `E_CTD` (counter) or `F_TRIG` (edge detection), which, however, exhibit active behavior. Other constant collections (e.g., physical units or thresholds) follow the same declarative pattern.

## Conclusion
The `all_colours` function block provides a standardized, easily reusable color palette for ISOBUS applications. Clear numbering and comprehensive comments ensure consistent color usage across different modules and developers. Reserved colors (232–255) are available for customization.
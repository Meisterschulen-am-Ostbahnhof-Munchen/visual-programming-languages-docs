# strip_set_pixel
<img width="1478" height="315" alt="image" src="https://github.com/user-attachments/assets/1892e226-bd9b-4dfc-bda7-8458f0a53619" />
* * * * * * * * * *
## Introduction
The function block `strip_set_pixel` is used to control an RGB LED strip. Its main function is to set the color of a single pixel (a single LED) on the strip or to turn off the entire strip. It is designed for use in control systems that require precise, pixel-by-pixel control of RGB LEDs.
![strip_set_pixel](strip_set_pixel.svg)
## Interface Structure
### **Event Inputs**
* **INIT**: Initializes the function block. Must be triggered before first use.
* **set_pixel**: Triggers the command to set the color of a specific pixel. Linked to the data `index`, `red`, `green`, and `blue`.
* **clear**: Triggers the command to turn off (clear) all LEDs on the strip.

### **Event Outputs**
* **INITO**: Confirms successful initialization of the function block.
* **set_pixel_CNF**: Confirms execution of the `set_pixel` command. Linked to the data output `set_pixel_return`.
* **clear_CNF**: Confirms execution of the `clear` command. Linked to the data output `clear_return`.

### **Data Inputs**
* **index** (UDINT): The index (position) of the pixel on the LED strip to be set. The count typically starts at 0.
* **red** (UDINT): The red component of the color (value range depends on the hardware, e.g., 0-255).
* **green** (UDINT): The green component of the color (value range depends on the hardware, e.g., 0-255).
* **blue** (UDINT): The blue component of the color (value range depends on the hardware, e.g., 0-255).

### **Data Outputs**
* **set_pixel_return** (DINT): Returns an error status after executing the `set_pixel` command. A value other than 0 indicates an error (e.g., invalid pixel index).
* **clear_return** (DINT): Returns an error status after executing the `clear` command. A value other than 0 indicates an error.

### **Adapter**
This function block has no adapter interfaces.

## Functionality
The function block operates in an event-driven manner. Upon receiving a `INIT` event, the underlying hardware (LED strip) is initialized, and the `INITO` event is generated.

The `set_pixel` event triggers the main command. The values present at the data inputs `index`, `red`, `green`, and `blue` at this time are read and sent to the LED strip to set the corresponding LED to the desired color. The `set_pixel_CNF` event is then output along with a status code (`set_pixel_return`).

The `clear` event sets all pixels of the strip to black (off), which is equivalent to clearing the current pattern. The `clear_CNF` event is then output with a status code (`clear_return`).

``` ## Technical Features

* The data inputs for the color values are of type `UDINT` (unsigned double integer), which allows for a large value range. The actual effective resolution (e.g., 8 bits = 0-255) depends on the connected hardware.
* The data outputs for feedback are of type signed `DINT` to represent positive and negative error codes.
* The function block follows the typical IEC 61499 Service Interface Pattern with separate acknowledgment events (`CNF`) for each command.

## Status Overview

1. **Not Initialized**: After startup. Only the `INIT` event is valid.

2. **Initialized / Ready**: After successful execution of `INITO`, the commands `set_pixel` and `clear` can be received and processed. The function block returns to this state after each command.

## Application Scenarios
* **Status Indicators**: Individual LEDs can be used as status or warning lights (e.g., machine in operation, fault at position X).
* **Simple Lighting Effects**: By sequentially setting individual pixels, chasing or flashing effects can be implemented.
* **Visualization of Process Data**: The color or brightness of a pixel can represent a process value (e.g., temperature, fill level).
* ## ⚖️ Comparison with Similar Components

Compared to components that transfer entire color patterns or images to an LED matrix (e.g., `strip_show` or `matrix_display`), `strip_set_pixel` operates at a very granular, pixel-by-pixel level. It offers maximum control over each individual LED but is less efficient for transferring complex images. Components like `strip_fill` typically set an entire area or all LEDs to a single color at once, while `strip_set_pixel` addresses each LED individually.

Compared to components that transfer entire color patterns or images to an LED matrix (e.g., `strip_show` or `matrix_display`), `strip_set_pixel` operates at a very granular, pixel-by-pixel level. It offers maximum control over each individual LED but is less efficient for transferring complex images. Components like `strip_fill` typically set an entire area or all LEDs to a single color at once, while `strip_set_pixel` addresses LEDs individually. ## 🛠️ Related Exercises

* [Exercise_031](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_031.md)

## Conclusion
The `strip_set_pixel` function block is a fundamental and essential building block for controlling addressable RGB LED strips within 4diac. Its simple, event-based interface allows for precise and direct control of each individual pixel. Its strength lies in its simplicity for point-by-point control tasks, while for more complex animations, combining it with higher-level, sequencing blocks is recommended.

--

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

# SoftKeyActivationCode_S

* * * * * * * * * *

## Introduction

The data type `SoftKeyActivationCode_S` is a structured data structure (struct) used to configure the activation of a softkey in an ISOBUS-compliant system. It defines the specific activation code and a control flag for the key press repetition frequency.

## Interface Structure

This is a data type and therefore does not have event or adapter interfaces in the conventional sense of a function block. The structure consists of the following data fields:

### **Data Inputs**

*(Not applicable – this is a data type)*

### **Data Outputs**

*(Not applicable – this is a data type)*

### **Data Fields (Structure Components)**

| Name | Data Type | Initial Value | Comment |
| :------- | :------- | :---------- | :-------- |
| `code` | `USINT` | 255 | Defines the numeric code that identifies the specific softkey. |
| `bCyclic` | `BOOL` | TRUE | Controls the cyclic sending of the key code. With `FALSE`, the key is not repeatedly sent every 200ms. |

## Functionality

The structure `SoftKeyActivationCode_S` serves as a container for configuration data. The value in the field `code` corresponds to a specific key on a virtual or physical terminal. The field `bCyclic` allows you to control the behavior when a key is held down. If set to `TRUE` (default), the key press is repeatedly sent at a defined interval (e.g., every 200 ms) as long as the key remains pressed. With `FALSE`, only a single event is triggered upon the initial key press.

## Technical Features

- **Initial Values:** Both fields have predefined initial values. The default value `255` for `code` can be interpreted as "invalid" or "unconfigured" code.
- **ISOBUS Context:** This data type is part of the `isobus::UT::io::Softkey` package, indicating its use in ISOBUS Virtual Terminal (VT) or similar I/O contexts.
- **Cycle Control:** Precise control of the repetition rate via `bCyclic` is crucial for user-friendly and reliable keyboard input, especially with long data fields or list controls.

## State Overview

*(Not applicable – this is a passive data type without a state machine.)*

## Application Scenarios

This data structure is typically used as an input or configuration parameter for function blocks that:

1. Emulate or control the virtual keyboard input of an ISOBUS terminal.
2. Process softkey events in application logic (e.g., menu navigation, value input).
3. Dynamically configure the key assignment or key behavior of a device.

## ⚖️ Comparison with Similar Blocks

Unlike a function block (FB), `SoftKeyActivationCode_S` is a pure **data type** (struct). It does not contain any algorithms or event-driven logic.

- **Similarity to `E_SR` or `E_RS`:** These are function blocks with memory functionality and internal state logic. `SoftKeyActivationCode_S`, on the other hand, is a pure data carrier.
- **Comparison with simple data types:** Unlike atomic types such as `INT` or `BOOL`, this struct combines two logically related pieces of information (`code` and behavior `bCyclic`) into a single, reusable unit.

## Conclusion

The data type `SoftKeyActivationCode_S` is an essential auxiliary structure for controlling softkey input in ISOBUS environments. By encapsulating the key code and repeat behavior in a single struct, configuration is simplified and code reusability is increased. Its clear structure and sensible default values make it a robust building block for developing terminal I/O logic.

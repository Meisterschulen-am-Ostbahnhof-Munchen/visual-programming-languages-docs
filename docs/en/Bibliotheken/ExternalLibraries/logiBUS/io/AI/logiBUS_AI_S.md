# logiBUS_AI_S

* * * * * * * * * *
## Introduction

The function block `logiBUS_AI_S` is a structured data type (struct) used to configure an analog input (AI) channel within the logiBUS library. It defines the basic parameter structure required to address a physical pin of a logiBUS hardware module for acquiring analog signals.
## Interface Structure

This is a structured data type (struct), therefore it does not have event or adapter interfaces in the conventional sense of an executable function block. Its structure consists of a single data element.
### **Data Inputs**

The structure itself contains the following data element, which serves as an input parameter for a configuring function block (e.g., `logiBUS_AI`):

* **`Pin`** (`USINT`): This value specifies the physical hardware pin or channel of the logiBUS module from which the analog signal is to be read. The default value is `255`, which is typically interpreted as an invalid or unconfigured state.

## Functionality

The data type `logiBUS_AI_S` is a pure data structure and has no active functionality. It serves as a container for configuration data. Its main purpose is the parametric description of an analog input. A higher-level I/O manager or device driver function block (such as `logiBUS_AI`) reads the values stored in an instance of this structure and uses them to correctly configure and control the corresponding hardware interface.

## Technical Features

* **Initial Value:** The member `Pin` is predefined with the initial value `255`. This value is outside the typical range of valid pin numbers (often 0 to n) and can therefore be used to detect an uninitialized or faulty configuration.
* **Type Safety:** Using a structured data type instead of individual, unconnected parameters increases the type safety and maintainability of the code in the 4diac IDE.
* **Library Affiliation:** This type is part of the `logiBUS::io::AI` package, clearly indicating its membership in the logiBUS IO library for analog inputs.

## Application Scenarios

This struct is used exclusively in scenarios where logiBUS hardware with analog input modules (e.g., for voltage or current measurement) is integrated into a 4diac FORTE application. Typical applications include:

* Process monitoring (temperature, pressure, level via sensors)
* Control voltage acquisition
* Configuration of multi-channel measurement systems where a separate instance of `logiBUS_AI_S` is created for each channel.

## ⚖️ Comparison with Similar Building Blocks

Within the logiBUS library, similar structured data types exist for other I/O functions, such as `logiBUS_DI_S` for digital inputs or `logiBUS_AO_S` for analog outputs. These differ primarily in their context-specific names and are designed for the respective type of signal processing. However, the basic structure (a `Pin` field) is often identical or very similar.

## Conclusion

The `logiBUS_AI_S` data type is an essential configuration element for using analog inputs with logiBUS in 4diac. As a simple, well-defined structure, it enables clear and centralized management of hardware parameters and forms the basis for reliable connection of analog sensors to an IEC 61499 control system.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
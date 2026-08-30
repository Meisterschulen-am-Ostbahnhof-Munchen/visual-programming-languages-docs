# USERFUNC_e

![USERFUNC_e](./USERFUNC_e.svg)

* * * * * * * * * *
The global constant `USERFUNC_e` defines an enumeration of numeric values that represent specific device functions or roles within an ISOBUS network. It serves for the standardized and readable identification of various ISOBUS device types and functions in control applications.
USERFUNC_e` is a collection of global constants and not a function block. Therefore, there are no event or data interfaces in the conventional sense. The structure consists exclusively of named constants of type `SINT` (short integer).

*Not applicable.* This resource provides constants and has no inputs.

*Not applicable.* The constants are referenced directly in the application code.

### Data Outputs

### Data Inputs

## Interface Structure

## Introduction

### **Adapters**

*Not applicable.*

## Functionality

USERFUNC_e` is a collection of predefined constant values. Each name (e.g., `task_controller`) is associated with a fixed numeric value (e.g., `1`). These constants can be used throughout the application to identify device roles, perform comparisons, or set parameters, significantly improving code maintainability and readability compared to directly using "magic numbers."

- **Data Type:** All constants are of type `SINT` (8-bit signed integer).
- **Range:** The defined values range from `-1` (`undefined`) to `21`.
- **ISOBUS Compliance:** The designations and values are based on the device functions defined in the ISOBUS standard (ISO 11783).
- **Special Values:**
- `undefined` (-1): Indicates an undefined or unknown function.
- `all_clients` (20) & `all_server` (21): Values for broadcast or group addressing.

*Not applicable.* Constants have no state.

- **Device Identification:** In a task controller, `IF device_function = USERFUNC_e.virtual_terminal THEN ...` can be used to check whether a connection to a terminal exists.
- **Message Filtering:** Filtering of ISOBUS messages (PGNs) based on the source or destination device function.
- **Configuration:** Parameterization of network services that should only be available for specific device roles (e.g., `file_server`).
- **Diagnostics:** Readable output of device roles in diagnostic logs or on user interfaces.

Unlike function blocks that contain active logic, `USERFUNC_e` is a passive data type/constant definition. It is comparable to a `ENUM` data type in higher-level programming languages or a `CONSTANT` section in Structured Text (ST). Its primary purpose is to provide semantically meaningful names for numeric values used in the ISOBUS context.

The global constant `USERFUNC_e` is an essential tool for developing readable and maintainable ISOBUS applications in 4diac. It abstracts the raw, standard-defined numeric values for device functions into meaningful identifiers, thus significantly contributing to error prevention and improved code quality. Its use is recommended for all projects that work with ISOBUS device communication.

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Application Scenarios

## State Overview

## Technical Features

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

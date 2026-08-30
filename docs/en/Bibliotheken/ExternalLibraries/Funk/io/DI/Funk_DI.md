# Radio_DI

![Funk_DI](./Funk_DI.svg)

* * * * * * * * * *
## Introduction

Radio_DI is a GlobalConstants package for the 4diac IDE that defines constants for digital inputs in radio systems. The package provides predefined pin configurations for various digital input signals that can be used in control applications.
## Interface Structure

Because Radio_DI is a GlobalConstants package, it does not have traditional function block interfaces. Instead, it provides global constants.

### **Event Inputs**

Not available - GlobalConstants package

### **Event Outputs**

Not available - GlobalConstants package

### **Data Inputs**

Not available - GlobalConstants package

### **Data Outputs**

Not available - GlobalConstants package

### **Adapters**

Not available - GlobalConstants package

## Functionality

The Funk_DI package defines a collection of global constants of type `Funk_DI_S`, representing digital input pins. Each constant contains a pin number that identifies the physical or logical input. The constants can be used in other function blocks to reference specific digital inputs.

## Technical Features

- **Pin Assignments**: The pin numbers follow a specific scheme:
- Standard Inputs: Pins 1-15
- Special Functions: Pin 0 (STOP), Pin 25 (START)
- System Functions: Pin -1 (STATUS), Pin -6 (COUNTER)
- Invalid Value: Pin 127 (Invalid)
- **Data Type**: All constants use the structured data type `Funk_DI_S`
- **Package Structure**: Organized in the namespace `Funk::io::DI`

## State Overview

Since this is a constant package, there are no state transitions. All values are hard-coded at compile time and are unchangeable.

## Application Scenarios

- **Digital Input Configuration**: Simplified configuration of digital inputs in control applications
- **Standardization**: Ensuring consistent pin assignments across different projects
- **Maintainability**: Centralized management of all digital input configurations
- **Wireless Systems**: Specifically designed for applications in wireless control systems

## ⚖️ Comparison with Similar Components

Compared to other digital input constant packages, Funk_DI offers:

- Specific pin assignments for wireless systems
- Predefined constants for special functions (START, STOP, STATUS, COUNTER)
- Structured organization within the I/O area of the Funk namespace

## Conclusion

The Funk_DI GlobalConstants package provides a convenient collection of predefined constants for digital inputs in wireless systems. Its standardized pin assignments and clear naming conventions enable efficient and easy-to-maintain configuration of control applications. The special functions such as START, STOP, and STATUS make it particularly suitable for industrial control applications with wireless components.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

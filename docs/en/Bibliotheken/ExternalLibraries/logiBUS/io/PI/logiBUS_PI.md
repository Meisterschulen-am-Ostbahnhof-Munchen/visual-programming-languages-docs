# logiBUS_PI

![logiBUS_PI](./logiBUS_PI.svg)

* * * * * * * * * *
## Introduction

The function block `logiBUS_PI` is a collection of global constants for configuring pulse inputs in logiBUS systems. It defines preconfigured structures that represent the physical input pins of a logiBUS I/O module. These constants facilitate the simple and error-free assignment of hardware pins in higher-level function blocks or applications.
## Interface Structure

logiBUS_PI` is a GlobalConstants block, not a traditional function block with event or data interfaces. Therefore, it has no event inputs, outputs, data inputs, outputs, or adapters.

The interface consists solely of the defined global constants. Each constant is of data type `logiBUS::io::PI::logiBUS_PI_S` and is instantiated with a specific initial value.

### **Defined Constants**

The following constants are provided:

* `PulseInput_I1` to `PulseInput_I9`: Represent the physical pulse inputs 1 to 9. The initial value sets the structure field `Pin` to the corresponding value (1-9).
* `Invalid`: Represents an invalid or unused input. The initial value sets the structure field `Pin` to the value 255.

## Functionality

The block `logiBUS_PI` itself does not perform any active functionality. It merely provides a library of predefined values. These values are of type `logiBUS_PI_S`, a structure that presumably contains at least the member `Pin`.

The constants are inserted into the application code at compile time. If another function block (e.g., a driver or measurement module) expects a parameter of type `logiBUS_PI_S`, one of these constants can be passed to uniquely select a specific hardware input.

## Technical Features

* **Typing:** All constants are strictly of the structured data type `logiBUS_PI_S`. This enforces type-safe usage and prevents the unintentional assignment of simple integer values.
* **Initialization:** The initial values are specified using the ST syntax `(Pin := X)`, indicating structured initialization.
* **Invalid State:** The constant `Invalid` with pin value 255 provides a standardized way to indicate an unused or faulty channel.

## State Overview

Since it is a constant block, `logiBUS_PI` has no internal state or state machine. The constant values are immutable (read-only) and remain constant throughout the application's runtime.

## Application Scenarios

* **Hardware Configuration:** Primarily used to configure logiBUS I/O modules that provide pulse inputs (e.g., for encoders, frequency, or speed measurement).
* **Function Block Parameterization:** Simplified and readable parameterization of function blocks that require a specific pulse input. Instead of the magic number `3`, the self-explanatory constant `PulseInput_I3` is used.
* **Maintenance and Readability:** Increases the maintainability and readability of the application code, as the hardware assignment is directly apparent in the constant name.

## ⚖️ Comparison with Similar Blocks

Unlike function blocks such as `E_SR` (flip-flop) or `E_CYCLE` (cyclic event generator), `logiBUS_PI` does not implement any logic or algorithms. It is comparable to other constant blocks or ENUM definitions in IEC 61499 that encapsulate hardware-related parameters (e.g., `GPIO_PIN_XX` constants for Raspberry Pi). Its purpose is purely declarative and configurative.

## Conclusion

The `logiBUS_PI` GlobalConstants block is an essential tool for low-level programming of logiBUS systems. By providing type-safe, predefined constants for pulse inputs, it enables clean, fault-resistant, and easily maintainable configuration of the input/output hardware. Its use promotes best practices in industrial automation programming.

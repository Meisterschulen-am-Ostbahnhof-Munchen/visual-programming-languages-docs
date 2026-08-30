# AUDI_TO_AD

## Introduction

The AUDI_TO_AD function block is a specialized adapter conversion module. It converts a unidirectional **AUDI** (UDINT) adapter socket into a unidirectional **AD** (DWORD) adapter plug.
Internally, the module uses the standard conversion function `F_UDINT_TO_DWORD` to ensure clean type conversion between the numeric format (UDINT) and the bit string format (DWORD).
![AUDI_TO_AD](AUDI_TO_AD.svg)

## Interface Structure

### **Adapters**

- **AUDI_IN** (Socket): Input adapter of type `AUDI` (UDINT).
- **AD_OUT** (Plug): Output adapter of type `AD` (DWORD).

## Functionality

As soon as an event (`E1`) arrives at `AUDI_IN` along with data (`D1`), the UDINT value is internally converted into a DWORD value. This is then immediately passed on via the `AD_OUT` adapter (event `E1`, data `D1`).

## Technical Features

✔ **Direct adapter-to-adapter coupling**.

✔ **Standard-compliant conversion** through the use of `F_UDINT_TO_DWORD`.

✔ **Event-driven**: Every update at the input immediately triggers an update at the output.

## Application Scenarios

- Feeding numerical calculation results back to ISOBUS output modules (e.g., bar graph or numeric display), which often expect DWORD as the input format.
- Compatibility layer in adapter-based control architectures.

# AUS_TO_ALI

![AUS_TO_ALI](./AUS_TO_ALI.svg)

* * * * * * * * * *

## Introduction
The function block `AUS_TO_ALI` is a composite function block (FB) that converts an AUS adapter (USINT values) into an ALI adapter (LINT values). It encapsulates the conversion process and provides a unidirectional interface between these two adapter types. Internally, the function block `F_USINT_TO_LINT` from the IEC 61131 library is used.

## Interface Structure
### **Event Inputs**
No dedicated event inputs. Event control is handled via the `AUS_IN` adapter (socket).

## **Event Outputs**
No dedicated event outputs. Event output is handled via the `ALI_OUT` adapter (plug).

### **Data Inputs**
No dedicated data inputs. Data is received via the `AUS_IN` adapter.

### **Data Outputs**
No dedicated data outputs. Data is output via the `ALI_OUT` adapter.

### **Adapters**
- **OFF_IN** (Socket) – Receives an OFF adapter with a unidirectional USINT data type. Includes:

- Event input `E1`

- Data input `D1` (USINT)

- **ALI_OUT** (Plug) – Sends an ALI adapter with a unidirectional LINT data type. Includes:

- Event output `E1`

- Data output `D1` (LINT)

## Functionality
The function block operates in an event-driven manner:

1. An event at the `E1` input of the `AUS_IN` adapter initiates processing.

2. The current value of `AUS_IN.D1` (USINT) is passed to the internal function block `Convert` (`F_USINT_TO_LINT`).

3. After conversion, the result (LINT) is output via `ALI_OUT.D1`, and simultaneously an event is sent to the `E1` output of the `ALI_OUT` adapter.

Type conversion is performed according to the IEC 61131 definition of `F_USINT_TO_LINT`: USINT (0..255) is mapped to LINT (64-bit) without loss of sign.

## Technical Features

- **Composite Block**: The conversion logic is encapsulated and reusable.

- **Adapter-Based**: Input/output is exclusively via adapters (`AUS` and `ALI`), which facilitates integration into adapter-oriented architectures.

- **Unidirectional**: The function block supports only one data flow direction (OFF → ALI).

- **Library Import**: It uses the function block `iec61131::conversion::F_USINT_TO_LINT` from the IEC 61131 library.

- **Package Structure**: The function block is organized in the package `adapter::conversion::unidirectional`.

## State Overview
The `AUS_TO_ALI` function block does not have its own state machines. The internal process is purely event-driven and stateless:

- **Wait**: for an event from `AUS_IN.E1`

- **Convert**: immediate conversion of the USINT value to LINT

- **Output**: immediate sending of the result via `ALI_OUT`

Each conversion is independent of previous calls.


## Application Scenarios

- **Interface Adaptation**: A system that provides data as an AUS adapter (USINT) must be connected to a receiver that expects an ALI adapter (LINT).

- **Data Preparation**: Conversion of low-resolution sensor data or manipulated variables (USINT) into a wider range of values (LINT) for further calculations.

- **Adapter Cascading**: As part of a chain of adapter conversions, e.g., in a modular control architecture.

## Comparison with Similar Function Blocks

- **Direct Use of `F_USINT_TO_LINT`**: This function block operates at the data level without an adapter. `AUS_TO_ALI` additionally encapsulates the adapter logic and is therefore better suited for adapter-based communication.

- **Further Adapter Conversions**: For other type combinations (e.g., `INT_TO_DINT`, `BYTE_TO_WORD`), analogous composite devices exist that follow the same design pattern.

## Conclusion
The `AUS_TO_ALI` device is a simple yet effective solution for unidirectional conversion between USINT and LINT adapters. It increases reusability and clarity in systems that rely on adapter interfaces and avoids the manual wiring of conversion logic.
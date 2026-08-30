# IA_GBSD

![IA_GBSD](./IA_GBSD.svg)

* * * * * * * * * *

## Introduction

The function block **IA_GBSD** serves as an adapter wrapper for the ISOBUS-compatible module **I_GBSD** ("Ground Based Speed and Distance"). It encapsulates the initialization and data communication of a ground-based speed and distance sensor according to ISO 11783-7 (PGN 65097) and provides the values via unidirectional adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|---------------------------------|
| INIT | EInit | Service Initialization |

### **Event Outputs**

| Name | Type | Comment |
|-------|-------|-------------------------------|
| INITO | EInit | Initialization Confirm |

### **Data Inputs**

| Name | Type | Comment |
|------|------|----------------------------|
| QI | BOOL | Event Input Qualifier |

### **Data Outputs**

| Name | Type | Comment |
| -------- | -------- | ------------------------------ |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Status Information |

### **Adapters**

| Name | Type | Comment |
| ---------- | ------------------------------- | ---------------------------------------- |
| SPEED | adapter::types::unidirectional::AUI | Ground-based machine speed |
| DISTANCE | adapter::types::unidirectional::AUDI | Ground-based machine distance |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout status |

## Functionality

The function block is implemented as a pure adapter wrapper:

- An INIT event at the input is directly forwarded to the internal block **I_GBSD**.
- The data input **QI** activates or deactivates processing.
- After initialization, the **INITO** event is output with the qualifier **QO** and a **STATUS**.
- The calculated values (speed and distance) are output via the adapters **SPEED** and **DISTANCE**. If a timeout occurs, the **TIMEOUT** adapter is activated.
- All data connections are established within the FB network between the inputs/outputs and the internal module.

## Technical Features

- **Adapter-based interface**: The output data is not provided as fixed variables, but via unidirectional adapters (AUI, AUDI, AX), allowing for flexible integration with other components.
- **ISOBUS compliance**: The FB implements PGN 65097 according to ISO 11783-7 – the standard for ground-based speed and distance in agricultural technology.
- **Timeout monitoring**: The separate timeout adapter signals whether the sensor values have been updated within an expected time period.
- **Compact design**: There is no separate state machine; all control logic resides in the internal module **I_GBSD**.

## State Overview

The function block itself does not have an explicit finite state machine. The internal block goes through an initialization state (triggered by INIT) and an operating state in which speed, distance, and timeout status are continuously updated.

## Application Scenarios

- **ISOBUS Control Units (TECUs)**: Integration of a radar sensor or other ground-based speed/distance sensor into an ISOBUS-compatible system.
- **Agricultural Vehicles**: Provision of driving speed and distance traveled for downstream functions (e.g., metered applications, section control).
- **Test and Simulation Environments**: Use of the adapter wrapper to replace the real sensor with a simulated data source.

## Comparison with Similar Modules

- **IA_GBSD** vs. **I_GBSD**: I_GBSD is the natively programmed ISOBUS module, while IA_GBSD makes its functionality accessible exclusively via adapters. The wrapper simplifies wiring in graphical editors and separates the actual logic from the interface connection.
- **Alternative Adapter Wrappers**: Similar wrappers exist for other ISOBUS PGNs (e.g., for navigation data or hydraulic systems), which also provide adapters for their output values.

## Conclusion

IA_GBSD is an efficient adapter wrapper that encapsulates ground-based speed and distance measurement according to ISO 11783-7. The adapter interfaces enable clean, modular integration into higher-level control logic, while the actual ISOBUS implementation remains intact. This makes the component usable for both direct applications and for simulation and testing purposes.

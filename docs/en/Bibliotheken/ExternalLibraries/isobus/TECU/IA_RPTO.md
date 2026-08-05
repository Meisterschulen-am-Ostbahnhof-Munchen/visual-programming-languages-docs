# IA_RPTO
![IA_RPTO](./IA_RPTO.svg)
**********
## Introduction
The IA_RPTO function block is an ISOBUS adapter for the rear power take-off (RPTO) according to ISO 11783-7 (PGN 65091). It provides an encapsulated interface to an internal I_RPTO function block and outputs the most important parameters (speed, setpoint, timeout status) via adapter ports.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |
|-------|--------|-------------------------------|-----------|
| INIT | EInit | Service Initialization | QI |

### **Event Outputs**

| Name | Type | Comment | With Data |
|-------|--------|-------------------------------|--------------------|
| INITO | EInit | Initialization Confirm | QO, STATUS |

### **Data Inputs**

| Name | Type | Comment |
|------|--------|------------------------------|
| QI | BOOL | Event Input Qualifier |

### **Data Outputs**

| Name | Type | Comment |
|--------|--------|-------------------------------|
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Status Message |

### **Adapter**

| Name | Type | Comment |
|-----------|----------------------------------------|---------------------------------------------|
| SPEED | adapter::types::unidirectional::AUI | Rear PTO output shaft speed |
| SPEED_SET | adapter::types::unidirectional::AUI | Rear PTO output shaft speed set point |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout Status |

## Functionality

This function block internally instantiates a `I_RPTO` block, which handles the actual ISOBUS communication for the rear PTO shaft. Initialization is triggered via an INIT event; upon successful execution, INITO acknowledges with QO = TRUE and a corresponding STATUS. The values `REAR_PTO_OUTP_SHAFT_SPEED`, `REAR_PTO_OUTP_SH_SPEED_SET`, and `Q_timeout` of the inner block are forwarded directly to the corresponding adapter ports SPEED, SPEED_SET, and TIMEOUT.

## Technical Specifications

– The block operates according to ISO 11783-7 (PGN 65091) and is intended for use in agricultural control units (tractor ECUs).

– All adapters are unidirectional (AUI, AX), meaning they only transmit data in one direction.

– The inner block is from the package `isobus::tecu`.

– License: Eclipse Public License 2.0.

## State Overview

The function block has two main states: **not initialized** and **initialized**. Upon receiving INIT, the inner block performs the initialization. Upon success, QO = TRUE is set and the STATUS displays a positive value. If an error or timeout occurs, this is signaled via the TIMEOUT adapter and the STATUS. A detailed state diagram is not included as part of the outer description, as all logic is implemented within the inner block.

## Application Scenarios

– Integration of an ISOBUS-compatible rear PTO into a tractor control unit.

– Monitoring and control of the PTO speed via the ISOBUS network.

– Time monitoring of data communication to detect connection interruptions.

## Comparison with Similar Blocks

Related adapter blocks exist for other ISOBUS functions, e.g., IA_FPTO (front PTO), IA_HITCH (lift mechanism), or IA_TSC (tractor control). The main difference lies in the PGN (65091) used and the specific data points (speed, setpoint, timeout). IA_RPTO thus offers an interface specifically tailored to the rear PTO.

## Conclusion

IA_RPTO encapsulates the ISOBUS communication for the rear PTO and provides the relevant information via clearly defined adapter ports. The module simplifies integration into IEC 61499 applications and ensures standards-compliant connection according to ISO 11783-7.
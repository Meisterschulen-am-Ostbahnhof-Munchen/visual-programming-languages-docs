# SYS_ONTIME

<img width="1095" height="143" alt="SYS_ONTIME" src="https://github.com/user-attachments/assets/154ba5c7-4a31-4dc3-8dbc-c6a731fdf46b" />
* * * * * * * * * *
## Introduction

The SYS_ONTIME function block serves as a service interface for communication between an application and a resource. It enables the transfer of operating time data in decimal minutes (0.01 hours) from the resource to the application.
![SYS_ONTIME](SYS_ONTIME.svg)
## Interface Structure

### **Event Inputs**

- `INIT` (Type: EInit): Initializes the service. Triggered by the application.

### **Event Outputs**

- `INITO` (Type: EInit): Confirms the initialization. Combined with the data output `ONTIME`.
- `IND` (Type: Event): Indication from the resource. Combined with the data output `ONTIME`.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

- `ONTIME` (Type: UINT): Operating time in decimal minutes (0.01 hours).

### **Adapters**

No adapters available.

## Functionality

The SYS_ONTIME function block enables the transfer of operating time data from a resource to the application. Initialization occurs via the `INIT` event, to which the block responds with `INITO`. The operating time data is provided via the `IND` event and the `ONTIME` data output.

## Technical Features

- The function block supports various service sequences for initialization, request acknowledgment, and error handling.
- The operating time is transmitted in decimal minutes (0.01 hours).

## Time Base Configuration

The block operates with an industrial time base (0.6-minute increments) instead of standard minutes:

- **1 industrial minute** = 0.6 standard minutes (36 seconds)
- **100 industrial minutes** = 1 standard hour (60 minutes)
- **Conversion factor**: 1.666... (standard to industrial minutes)

## Conversion Examples

| Industrial minutes | Standard time |
|------------------|------------------|
| 1 | 0.6 min (36 s) |
| 10 | 6 min |
| 100 | 60 min (1 h) |
| 150 | 90 min (1.5 h) |

### Technical Background:

- This time standard originates from process automation
- Enables integer representation of typical time intervals
- Particularly advantageous for batch processes and shift planning
- Also known as "PROFIBUS time base"

## Status Overview

1. **Initialization**: Triggered by `INIT` and confirmed by `INITO`.
2. **Data Transmission**: The operating time data is transmitted via `IND` and `ONTIME`.
3. **Error Handling**: Errors are reported via `IND-` with a status code.

## Application Scenarios

- Monitoring the operating time of machines and systems.
- Integration into maintenance and diagnostic systems.

## ⚖️ Comparison with Similar Function Blocks

Compared to other Service Interface function blocks, SYS_ONTIME offers specialized functionality for transmitting operating time data. Other blocks might transmit more general data or other specific information.

## 🛠️ Related Exercises

* [Exercise_140](../../../../Uebungen/test_B/Uebungen_doc/Uebung_140.md)

## Conclusion

The SYS_ONTIME function block is a specialized tool for transmitting operating time data in IEC 61499-based systems. Its clear interface structure and robust error handling make it a reliable solution for corresponding applications.
# FB_CTD

<img width="1325" height="282" alt="FB_CTD" src="https://github.com/user-attachments/assets/22cf142b-4252-487d-b0dc-2b3379946fbe" />
* * * * * * * * * *
The FB_CTD (Down Counter) is a function block that acts as a down counter. It counts down the internal counter value on each trigger event and outputs a signal when the counter reaches or falls below a specific value.
![FB_CTD](FB_CTD.svg)

- **REQ**: Normal execution request that starts the counting process.
- **CNF**: Acknowledgement of execution, triggered after the counting process.
- **CD (BOOL)**: Count Down - Signal to count down the counter.
- **LD (BOOL)**: Load - Signal to load the preset value into the counter.
- **PV (INT)**: Preset Value - Preset value loaded into the counter.
- **Q (BOOL)**: Output - Signal activated when the counter value is ≤ 0.
- **CV (INT)**: Count Value - Current counter value.

##**Adapters**
No adapters available.

### **Adapter**

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

## Functionality

The FB_CTD performs the following operations:

1. When the **LD** signal is active, the **PV** value is loaded into the counter (**CV**).
2. When the **CD** signal is active and the counter value (**CV**) is greater than -32768, the counter is decremented by 1.
3. The output signal **Q** is set to `TRUE` when the counter value (**CV**) is ≤ 0.
- The counter value (**CV**) is a 16-bit integer with a range of -32768 to 32767.
- The FB_CTD is a simple function block without an internal state machine.

The FB_CTD has no explicit states but reacts directly to the input signals.

- Controlling processes that require a specific number of steps.
- Monitoring time intervals or event counts.
- Use in automation systems where a counting counter is needed.
- **FB_CTU (Up Counter)**: Counts upwards instead of downwards.
- **FB_CTUD (Up-Down Counter)**: Combines up and down counting in one function block.

The FB_CTD is a simple and efficient function block for downcounting operations in automation applications. Its clear interface and simple functionality make it ideal for basic counting tasks.
## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
# Exercise 103: Digital Input I1 to Digital Output Q1, using Plug and Socket and DEMUX

* * * * * * * * * *

## Introduction

This exercise demonstrates the processing of a digital input signal into a digital output signal using plug-and-socket connections and DEMUX and MUX function blocks. The system allows for different signal processing modes for various applications.

## Function Blocks (FBs) Used

### Main Function Blocks

- **DigitalInput_I1** (logiBUS_IXA): Reads digital input signals from Input_I1
- **DigitalOutput_Q1** (logiBUS_QXA): Writes digital output signals to Output_Q1
- **AX_DEMUX_3**: Distributes input signals to three different outputs
- **AX_MUX_3**: Combines three input signals into one output signal
- **InputNumber_I1** (NumericValue_ID): Provides numeric input values
- **C1** (F_DWORD_TO_UDINT): Converts DWORD to UDINT
- **C2** (F_UDINT_TO_UINT): Converts UDINT to UINT

### Sub-Blocks

#### Sub-Block: Latching

- **Type**: FBs::Exercises::Exercise_103::subapp::latching
- **Functionality**: Processes latching (holding) signals

#### Sub-Block: momentary

- **Type**: FBs::Exercises::Exercise_103::subapp::latching
- **Functionality**: Processes momentary (momentary) signals

#### Sub-Block: momentary_TON_5s

- **Type**: FBs::Exercises::Exercise_103::subapp::latching_TON_5s
- **Functionality**: Processes momentary signals with a 5-second time delay

## Program Flow and Connections

The signal flow begins at DigitalInput_I1, which reads the input signal from Input_I1. The signal is forwarded to the AX_DEMUX_3, which distributes it to three different paths:

1. **OUT0** → momentary sub-application → AX_MUX_3 IN0
2. **OUT1** → latching sub-application → AX_MUX_3 IN1
3. **OUT2** → momentary_TON_5s sub-application → AX_MUX_3 IN2

The AX_MUX_3 combines the processed signals and forwards them to DigitalOutput_Q1, which outputs the result to Output_Q1.

Additionally, InputNumber_I1 processes numerical values via conversion modules (C1, C2), which supply both the DEMUX and MUX with control signals.

**Learning Objectives:**

- Understanding plug-and-socket connections
- Working with DEMUX/MUX modules
- Signal distribution and combination
- Integration of sub-applications

**Difficulty Level**: Intermediate

**Required Prior Knowledge**: Basic knowledge of 4diac IDE, digital inputs/outputs, function blocks

**Starting the Exercise**: The system is automatically activated as soon as the QI parameter is set to TRUE.

## Summary

This exercise provides practical experience with signal distribution and combination using DEMUX and MUX modules. The integration of various signal processing modes (latching, momentary, delayed) into sub-applications demonstrates a flexible and modular program structure that is fundamental for more complex control tasks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

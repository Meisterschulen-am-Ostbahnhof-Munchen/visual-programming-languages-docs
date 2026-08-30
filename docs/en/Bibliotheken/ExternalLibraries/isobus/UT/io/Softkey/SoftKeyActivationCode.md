# SoftKeyActivationCode

![SoftKeyActivationCode](./SoftKeyActivationCode.svg)

* * * * * * * * * *

## Introduction

SoftKeyActivationCode is a collection of global constants for processing softkey events in ISOBUS-compatible systems. These constants define various activation states of softkeys on virtual terminals and are used to control user interactions in agricultural machinery.

## Interface Structure

SoftKeyActivationCode consists of global constants and not a function block. Therefore, there are no event or data interfaces in the conventional sense.

### **Constant Definitions**

- **SK_RELEASED**: Softkey released (state change) - Code: 0
- **SK_PRESSED**: Softkey pressed (state change) - Code: 1
- **SK_STILL_HELD**: Softkey still held - Code: 2
- **SK_STILL_HELD_START**: Softkey still held (start) - Code: 2, bCyclic: FALSE
- **SK_ABORTED**: Softkey press aborted (applies to VT version 4 and higher) - Code: 3
- **Invalid**: Invalid state - Code: 255

## Functionality

The constants represent different activation states of softkeys in ISOBUS systems. They are used to indicate the status of user interactions with virtual terminals. The transmission repetition rate is 200 ms when a soft key is pressed/released and every 200 ms when a soft key is held.

## Technical Features

- All constants are of type `isobus::UT::io::Softkey::SoftKeyActivationCode_S`
- The constants are defined as global constants and can be used system-wide
- The abort functionality (SK_ABORTED) is only available in Virtual Terminal version 4 and higher
- The constant SK_STILL_HELD_START additionally contains a Boolean parameter `bCyclic`

## Application Scenarios

- Control of user interfaces in agricultural machinery
- Processing of touch inputs on ISOBUS-compatible displays
- Implementation of softkey interactions in Virtual Terminal applications
- Status monitoring of user inputs in real-time control systems

## ⚖️ Comparison with Similar Blocks

Unlike function blocks, global constants do not offer active functionality but merely serve to standardize state values. They are comparable to ENUM definitions in other programming languages.

## Conclusion

SoftKeyActivationCode provides a standardized collection of constants for softkey processing in ISOBUS environments. Using these constants enables a uniform and maintainable implementation of user interactions in agricultural control systems.

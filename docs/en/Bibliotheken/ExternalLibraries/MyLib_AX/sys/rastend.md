# Rastend

<img width="666" height="233" alt="image" src="https://github.com/user-attachments/assets/b3bfdaca-bb42-428f-a91a-2e367b347faf" />

* * * * * * * * * *

## Introduction

This exercise implements a latching switching function that is triggered when a signal is released. The sub-application uses adapters for signal processing and event control to achieve reliable latching functionality.

## Function Blocks Used (FBs)

### Sub-modules: rastend

- **Type**: SubAppType
- **Internal FBs Used**:
    - **E_T_FF**: iec61499::events::E_T_FF
        - Event Input: CLK
        - Event Output: EO
        - Data Output: Q
    - **E_SWITCH**: iec61499::events::E_SWITCH
        - Event Input: EI
        - Event Output: EO0
        - Data Input: G
    - **AX_X_TO_BOOL**: adapter::conversion::unidirectional::AX_X_TO_BOOL
        - Adapter Input: AX_IN
        - Event Output: CNF
        - Data Input: IN
    - **AX_BOOL_TO_X**: adapter::conversion::unidirectional::AX_BOOL_TO_X
        - Event Input: REQ
        - Adapter Output: AX_OUT
        - Data Input: OUT

- **Functionality**: The subapplication converts incoming AX signals into Boolean values, processes them using a toggle flip-flop, and outputs the result back as an AX signal.

## Program Flow and Connections

The program flow follows this signal processing chain:

1. **Input Signal Processing**: The incoming AX signal is passed through the IN adapter to AX_X_TO_BOOL.
2. **Signal Conversion**: AX_X_TO_BOOL converts the AX signal into a Boolean value.
3. **Switch Control**: The Boolean value controls E_SWITCH, which forwards events to the toggle flip-flop.
4. **Latching Function**: E_T_FF implements the actual latching function and stores the state.
5. **Output Signal Generation**: AX_BOOL_TO_X converts the Boolean output value back into an AX signal.

**Connections in Detail**:

- Event Connections: E_SWITCH.EO0 → E_T_FF.CLK, E_T_FF.EO → AX_BOOL_TO_X.REQ, AX_X_TO_BOOL.CNF → E_SWITCH.EI
- Data connections: E_T_FF.Q → AX_BOOL_TO_X.OUT, AX_X_TO_BOOL.IN → E_SWITCH.G
- Adapter connections: IN → AX_X_TO_BOOL.AX_IN, AX_BOOL_TO_X.AX_OUT → OUT

## Summary

This exercise demonstrates the implementation of a latching switching function with adapters for signal conversion. It shows the use of toggle flip-flops for state storage and structured signal processing via various function blocks. The solution is particularly suitable for applications where a signal should remain active after being released.

## 🛠️ Related Exercises

- [Uebung_103](../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
- [Uebung_103c](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c.md)
- [Uebung_103c2](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c2.md)

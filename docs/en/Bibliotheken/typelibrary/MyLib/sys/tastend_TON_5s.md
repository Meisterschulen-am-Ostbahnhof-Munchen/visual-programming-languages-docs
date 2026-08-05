# tactile_TON_5s
* * * * * * * * * *
## Introduction
This exercise demonstrates the use of a time-delay relay (timer on-delay) with a fixed time setting of 5 seconds. The sub-application serves as a reusable component for time-delayed signal processing.
``` ## Function Blocks Used (FBs)
### Sub-Blocks: tastend_TON_5s
- **Type**: SubAppType
- **Internal FBs Used**:
- **AX_X_TO_BOOL**: adapter::conversion::unidirectional::AX_X_TO_BOOL
- Parameters: None
- Event Output/Input: CNF (Output), REQ (Input)
- Data Output/Input: IN (Input), OUT (Output)
- **E_TON**: iec61499::events::timers::E_TON
- Parameters: PT = t#5s
- Event Output/Input: CNF (Output), REQ (Input)
- Data Output/Input: IN (Input), Q (Output)
- **AX_BOOL_TO_X**: adapter::conversion::unidirectional::AX_BOOL_TO_X
- Parameters: None
- Event output/input: REQ (input), CNF (output)

Data output/input: OUT (input), AX_OUT (output)

Functionality:

The subapplication converts an incoming adapter signal (IN) into a Boolean value via AX_X_TO_BOOL, which is then passed to the E_TON timer. The timer waits 5 seconds before activating the output signal via Q. This signal is then converted back into an adapter signal (OUT) via AX_BOOL_TO_X.

## Program Flow and Connections

**Adapter Connections:**

- Input: IN → AX_X_TO_BOOL.AX_IN
- Output: AX_BOOL_TO_X.AX_OUT → OUT

**Event Connections:**

- AX_X_TO_BOOL.CNF → E_TON.REQ
- E_TON.CNF → AX_BOOL_TO_X.REQ

**Data Connections:**

- AX_X_TO_BOOL.IN → E_TON.IN
- E_TON.Q → AX_BOOL_TO_X.OUT

**Learning Objectives:**

- Understanding of Timer Function Blocks (E_TON)
- Working with Adapter Conversion Blocks
- Building Reusable Subapplications
- Time-Controlled Signal Processing

**Difficulty Level:** Beginner

**Required Prior Knowledge:** Basic knowledge of the 4diac IDE, understanding of function blocks and Adapters

**Start of the exercise**: The sub-application can be integrated into larger applications where a 5-second delay is required.

## Summary
The sub-application tastend_TON_5s provides a compact solution for time-delayed signal processing. Thanks to its fixed 5-second delay and the use of standardized adapter interfaces, it can be easily integrated into various control applications. Its clear structure, including signal conversion, timer functionality, and feedback, makes its operation transparent and comprehensible.

## Summary of the sub-application ## 🛠️ Related Exercises
* [Exercise_103](../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
* [Exercise_103c](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_103c.md)

---

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
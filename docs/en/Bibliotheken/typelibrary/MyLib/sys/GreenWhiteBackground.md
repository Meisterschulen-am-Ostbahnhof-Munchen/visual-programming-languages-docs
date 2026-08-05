# GreenWhiteBackground

<img width="1273" height="233" alt="image" src="https://github.com/user-attachments/assets/ec8d48e6-6d6b-4749-bbe0-e53d06b6be01" />

* * * * * * * * * *

## Introduction
The "GreenWhiteBackground" exercise demonstrates the use of background colors in an ISOBUS-compliant system. The sub-application allows switching between a green and white background color for a specific object based on a selector signal.


## Function Blocks (FBs) Used

### Sub-Blocks: GreenWhiteBackground
- **Type**: SubAppType
- **Internal FBs Used**:

- **Q_BackgroundColour**: isobus::UT::Q::Q_BackgroundColour

- Parameters: No explicit parameters

- Event Output/Input: REQ (Input), CNF (Output)

- Data Output/Input: u16ObjId (Input), u8Colour (Input), s16result (Output), u8OldColour (Output), STATUS (Output)

- **F_SEL_I**: iec61131::selection::F_SEL

- Parameters: IN0 = COLOR_WHITE, IN1 = COLOR_GREEN

- Event Output/Input: REQ (Input), CNF (Output)

- Data Output/Input: G (Input), OUT (Output)

- **Functionality**:

The F_SEL_I function block selects between the colors WHITE (IN0) and GREEN (IN1) based on the DI1 signal. The selected color is passed to Q_BackgroundColour, which changes the background color for the specified object (u16ObjId).


## Program Flow and Connections

**Event Connections:**

- REQ → F_SEL_I.REQ

- F_SEL_I.CNF → Q_BackgroundColour.REQ

- Q_BackgroundColour.CNF → CNF

**Data Connections:**

- DI1 → F_SEL_I.G (Selector Input)

- u16ObjId → Q_BackgroundColour.u16ObjId (Object ID)

- F_SEL_I.OUT → Q_BackgroundColour.u8Colour (Selected Color)

- Q_BackgroundColour.s16result → result_1 (Result)

- Q_BackgroundColour.u8OldColour → u8OldColour_1 (Old Color)

- Q_BackgroundColour.STATUS → STATUS_1 (Status Information)

**Learning Objectives:**

- Use of Selection Function Blocks

- Implementation of Color Change Functionality

- Working with ISOBUS-compliant function blocks

- Processing of Object IDs in ISOBUS Systems

**Difficulty Level**: Easy to Medium

**Required Prior Knowledge**: Basic knowledge of IEC 61499 and ISOBUS standards

**Starting the Exercise**: The exercise is started by the REQ event, where DI1 controls the color change and u16ObjId identifies the target object.

## Summary
The GreenWhiteBackground exercise demonstrates a practical application for dynamically changing background colors in ISOBUS systems. By combining a selection block with an ISOBUS-specific color control block, a simple yet effective color change mechanism is implemented, conveying fundamental concepts of function block programming and ISOBUS communication.


## 🛠️ Related exercises

* [Uebung_010c](../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c.md)
* [Uebung_010c2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c2.md)
* [Uebung_010c3_sub](../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c3_sub.md)
* [Uebung_010c4_sub](../../../../Uebungen/test_B/Uebungen_doc/Uebung_010c4_sub.md)
* [Uebung_039_sub_Outputs](../../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
* [Uebung_039a_sub_Outputs](../../../../Uebungen/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)


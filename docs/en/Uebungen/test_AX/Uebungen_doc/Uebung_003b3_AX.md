# Exercise_003b3_AX: 16 Wireless Buttons on DataPanel 16

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_003b3_AX`. This exercise is the logical continuation of `Uebung_003b2_AX`. It uses explicitly parameterized, typed sub-applications to map 15 wireless buttons to 15 outputs.
----
## Objective of the Exercise

The objective is maximum reusability and clarity. By using typed sub-applications with exposed parameters, the entire configuration (which button to which output) can be made directly in the main view without having to click through to the sub-modules.

-----

## Description and Components

[cite_start]The subapplication `Uebung_003b3_AX.SUB` instantiates the type `Uebung_003b3_sub_AX` 15 times[cite: 1].

### Typed Subapplication: `Uebung_003b3_sub_AX`

[cite_start]This component is identical to the functionality in `Uebung_003b2_sub_AX`, however, the parameters `Input`, `Output`, and `u8SAMember` are clearly exposed[cite: 2].

### Instance Configuration

The assignment is clearly readable in the file:

- **`F1`**: `STOP` -> `Output_1A` (Note: Check the logic to ensure that STOP is inverted or handled specially)
- **`F2`**: `START` -> `Output_1B`
- **`F3`**: `Key_01` -> `Output_2A`
- **`F4`**: `Key_02` -> `Output_2B`
- ...
- **`F15`**: `Key_13` -> `Output_8A`

All instances use `MI_00` as `u8SAMember` (address of the DataPanel).

-----

## Functionality

The functionality is identical to the previous exercise:

1. The main application passes the parameters (e.g., "Use button 1") to the sub-application.
2. The sub-application configures its internal `Funk_IXA` block accordingly.
3. The signal is read and forwarded via adapter to `DataPanel_MI_QXA`.
4. The output switches.

The advantage here is maintainability: If button 1 suddenly needs to switch output 8A, you only need to change the parameter at `F3`, instead of running new wires.

-----

## Application Example

One application example is the **series production of special-purpose machines**:

A company builds waste compactors that are sometimes equipped with 4, sometimes with 8, or sometimes with 12 buttons. The software is always structured the same way: You take the "Button Channel" block and place it as often as needed. The assignment of which hydraulic cylinder belongs to which button is done purely via parameter lists. This reduces errors and greatly speeds up commissioning.

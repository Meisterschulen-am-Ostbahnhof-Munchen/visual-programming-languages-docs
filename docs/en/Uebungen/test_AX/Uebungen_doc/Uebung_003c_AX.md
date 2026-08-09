# Exercise_003c_AX: DigitalInput_I1-2-3-4 on AUX

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_003c_AX`. This exercise demonstrates connecting local digital inputs to the ISOBUS system as "Auxiliary Inputs." This enables the use of local switches to control ISOBUS devices.
----
## Objective of the Exercise

The objective is to make local hardware inputs (`I1` to `I4`) available to the ISOBUS network. In the ISOBUS environment, input devices (joysticks, switch panels) can be defined as "Auxiliary Inputs," which can then be flexibly mapped to machine functions by the user.

-----

## Description and Components

[cite_start]The subapplication `Uebung_003c_AX.SUB` uses untyped (or reused typed) subapplications to define four channels[cite: 1].

### Subcomponent: `Uebung_003c_sub_AX`

[cite_start]This sub-block connects a local digital input to an ISOBUS auxiliary output block[cite: 2].

* **Input**: `logiBUS_IXA` (Reads the local pin)
* **Output**: `Aux_QXA` (Sends the status as an ISOBUS AUX message)
* **Parameters**:
* `Input`: The local input (e.g., `Input_I1`).
* `iInpNr`: The number of the AUX input in the ISOBUS pool (index 0 to n).

### Configuration

This exercise maps four inputs:

* `F1`: `Input_I1` -> AUX Index 0
* `F2`: `Input_I2` -> AUX Index 1 (implicit, check parameter mapping in the .SUB file)
* `F3`: `Input_I3` -> AUX Index 2
* `F4`: `Input_I4` -> AUX Index 3

(Note: In the provided .SUB file, the parameters `Input` and `iInpNr` are not explicitly included in the instances.) `F1`...`F4` are visible, which is typical for untyped sub-apps where the values are set internally. With a properly typed solution, these values would be visible as in `Uebung_003b3_AX`.

-----

## Functionality

1. The operator activates switch `I1`.
2. The `logiBUS_IXA` block detects the signal.
3. The signal is forwarded via adapter to the `Aux_QXA` block.
4. The `Aux_QXA` block generates the corresponding ISOBUS message indicating that "Auxiliary Input 0" has been activated.
5. A connected ISOBUS device (e.g., a sprayer) receives this command and executes the function assigned to this switch by the user.

-----

## Application Example

A **Retrofit Joystick**:

An older tractor doesn't have an ISOBUS joystick. Four simple pushbuttons are installed on the dashboard and connected to the control system. Thanks to this software logic, these four pushbuttons suddenly appear as fully functional ISOBUS control elements on the terminal and can be used to control state-of-the-art implements.

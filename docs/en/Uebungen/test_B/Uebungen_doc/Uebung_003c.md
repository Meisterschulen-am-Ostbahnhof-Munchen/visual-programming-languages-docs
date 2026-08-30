# Exercise_003c: DigitalInput_I1-2-3-4 on AUX

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_003c`. It demonstrates how to connect local hardware inputs to the ISOBUS system as "Auxiliary Inputs," using a standardized sub-application for structuring.
[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)]

## 🎧 Podcast

- [Old Bavarian for Beginners: From Gratler Colds to City Dwellers – A Sound Journey Through Lesson 3C](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Altbayerisch-fr-Einsteiger-Von-Gratler-Schnupfen-und-Stadthodern--Eine-Laute-Reise-durch-Lektion-3C-e376jh4)

----

## Objective of the Exercise

The objective is to make local physical switches (`I1` to `I4`) available for the ISOBUS network. In the ISOBUS world, these inputs can be defined as "Auxiliary Inputs." The end user can then flexibly map these to various machine functions at the terminal (e.g., "Button 1 controls flap open/close").

## Description and Components

[cite_start]The subapplication `Uebung_003c.SUB` uses four instances of type `Uebung_003c_sub` to provide four channels for ISOBUS mapping[cite: 1].

### Typed Subapplication: `Uebung_003c_sub`

[cite_start]This function block connects a standard digital input to an ISOBUS auxiliary output[cite: 2]. It has the following parameters:

- **`Input`**: Selection of the local hardware pin (e.g., `Input_I1`).
- **`iInpNr`**: The sequential number of the AUX input in the object pool (index 0 to n).

Internally, the events (`IND -> REQ`) and data (`IN -> OUT`) are passed from the `logiBUS_IX` to the `Aux_QX` module.

...

### Channel Configuration

In `Uebung_003c`, the mapping is as follows:

- `F1`: `Input_I1` ➡️ AUX Index 0
- `F2`: `Input_I2` ➡️ AUX Index 1
- `F3`: `Input_I3` ➡️ AUX Index 2
- `F4`: `Input_I4` ➡️ AUX Index 3

-----

## Functionality

1. The operator activates one of the physical switches (e.g., `I1`).
2. The corresponding instance (e.g., `F1`) detects the level change.
3. A `IND` event is triggered and activates the `REQ` port of the `Aux_QX` block.
4. The `Aux_QX` block sends a standardized ISOBUS message to the CAN network, indicating the status of "Auxiliary Input N".
5. The connected ISOBUS implement receives this message and executes the action assigned by the user.

-----

## Application Example

**Retrofitting Control Elements**:

A tractor does not have original ISOBUS joystick buttons. A small console with four standard buttons is installed in the cab and connected to the logiBUS control system. Thanks to this software logic, the buttons for all ISOBUS devices (e.g., sprayer, fertilizer spreader) appear as fully functional, freely assignable control elements on the terminal.

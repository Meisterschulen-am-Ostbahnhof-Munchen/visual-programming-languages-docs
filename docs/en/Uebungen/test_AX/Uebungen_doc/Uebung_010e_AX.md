# Exercise_010e_AX: SR+Toggle flip-flop with 3x SoftKey and GreenWhiteBackground

This article describes the logiBUS® exercise `Uebung_010e_AX`.

![Uebung_010e_AX_network](./Uebung_010e_AX_network.svg)

----

## Goal of the exercise

An output should be controllable via three separate softkeys: explicitly set, explicitly reset, or toggle.

-----

## Description and components

The subapplication `Uebung_010e_AX.SUB` extends the pure toggle flip-flop from `Uebung_010d_AX` into a combined SR+toggle flip-flop with three softkeys.

### Function blocks (FBs)

  - **`SoftKey_SET`**: `isobus::UT::io::Softkey::Softkey_IE` on `SoftKey_F1`, event `SK_RELEASED`.
  - **`SoftKey_RESET`**: same on `SoftKey_F2`.
  - **`SoftKey_TOGGLE`**: same on `SoftKey_F3`.
  - **`AX_T_FF_SR`**: SR+toggle flip-flop adapter with inputs `S` (set), `R` (reset), and `CLK` (toggle).
  - **`AX_SPLIT_2`**: Distributes the adapter signal from `AX_T_FF_SR.Q` to both output `Q1` and the feedback block.
  - **`DigitalOutput_Q1`**: Output (lamp), `Output_Q1`.
  - **`GreenWhiteBackground_AX`**: SubApp from `MyLib::sys`, bound to `SoftKey_F3` (the toggle key) — only this key shows the current background color.

-----

## How it works

1.  `SoftKey_SET.IND` → `AX_T_FF_SR.S`: sets the state `Q` to ON, regardless of the previous state.
2.  `SoftKey_RESET.IND` → `AX_T_FF_SR.R`: sets the state `Q` to OFF, regardless of the previous state.
3.  `SoftKey_TOGGLE.IND` → `AX_T_FF_SR.CLK`: inverts the current state `Q`.
4.  `AX_SPLIT_2` distributes the new state to `DigitalOutput_Q1` (physical output) and `GreenWhiteBackground_AX` (background color of the toggle softkey `F3`).

Set and Reset act independently of the current state, while Toggle inverts it — all three softkeys drive the same internal flip-flop state.

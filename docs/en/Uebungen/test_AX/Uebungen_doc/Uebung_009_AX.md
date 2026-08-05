# Exercise_009_AX: Ticker (AX Adapter Based)
This article describes the logiBUS® exercise `Uebung_009_AX`. It demonstrates the functionality of an event-based counter and a numerical display using an AX adapter, resulting in more compact and organized wiring.
----
## Exercise Objective
To learn adapter-based counting (`AUDI_CTUD_UDINT`) and how to display values on an ISOBUS terminal (`Q_NumericValue_AUDI`). The focus is on using adapters to bundle event and data flows.

-----

## Description and Components

The subapplication `Uebung_009_AX.SUB` uses adapter-based function blocks for the clock, counter, and numeric display:

### Function Blocks (FBs)
* **`AE_CYCLE` & `AX_SR`**: Generate a continuous clock and control the blinker status via adapters. `AX_SR` has a `AX` adapter output.
* **`AX_SWITCH`**: An adapter-based switch that toggles the `AX` signal flow based on the internal blinker status.
* **`AX_PERMIT`**: An adapter-based event gate. It only allows events at input `PERMIT.E1` to pass to output `EO` if the data input `PERMIT.D1` is set to `TRUE`.
* **`AUDI_CTUD_UDINT`**: An adapter-based up/down counter. It receives `CU` events and outputs the counter value via a `AUDI` adapter (`CV`).
* **`Q_NumericValue_AUDI`**: An ISOBUS output module for displaying a number on the screen. It receives the value via a `AUDI` adapter (`u32NewValue`).

------

## Functionality

1. **Clock & Blinker**: `AE_CYCLE` generates a `AE` event every second. `AX_SR` toggles its `AX` adapter output (`Q`) on each clock cycle.

2. **Conditioning**: The `AX_PERMIT` receives the `AX` signal from the `AX_SR`. Only if the blinker is `TRUE` is an event (`EO`) forwarded.

3. **Counting**: The passed-through events reach the `CU` input of the `AUDI_CTUD_UDINT`. The counter value is output via the `CV` adapter.

4. **Display**: With each change in the counter value (`AUDI_CTUD_UDINT.CO`), the value is sent to `Q_NumericValue_AUDI` via the `u32NewValue` adapter.

5. The user sees a continuously increasing number on the ISOBUS terminal.

-----

## Conclusion

This exercise demonstrates the advantages of a consistent adapter-based development approach. The modular network is significantly more transparent, as event and data flows are bundled into a single connection. This considerably reduces complexity and the potential for errors, and facilitates integration into distributed systems.
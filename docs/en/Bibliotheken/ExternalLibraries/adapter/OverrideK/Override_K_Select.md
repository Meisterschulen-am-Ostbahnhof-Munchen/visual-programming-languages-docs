# Override_K_Select

![Override_K_Select](Override_K_Select.svg)

* * * * * * * * * *
## Introduction

The `Override_K_Select` function block converts a pair of boolean override signals
(`Aktiv`/`Wert`, each as an [AX](../types/unidirectional/BOOL/AX.md) adapter) into a single
`UINT` selector `K` (as an [AUI](../types/unidirectional/UINT/AUI.md) adapter), as expected by an
`AX_AUI_MUX_3`. It encapsulates the recurring project pattern "a sensor value can be forced to
either `FALSE` or `TRUE` via an RW override" (see `Sensor.Leermelder.Override.*` in
`docs/datenpunkte.md` of the Getreideannahme application) in a single, reusable block, instead of
re-wiring the conversion at every call site.

## Interface Structure

### **Event Inputs**

None of its own. Events flow exclusively through the `Aktiv`/`Wert` adapter sockets.

### **Event Outputs**

None of its own. The result is emitted through the `K` adapter plug.

### **Data Inputs**

None of its own. All data is carried through the adapter sockets.

### **Data Outputs**

None of its own. The result is emitted through the `K` adapter plug.

### **Adapters**

| Direction | Name | Type | Description |
|-----------|------|------|--------------|
| Socket (input) | `Aktiv` | `adapter::types::unidirectional::AX` | `Override.Aktiv` |
| Socket (input) | `Wert` | `adapter::types::unidirectional::AX` | `Override.Wert` |
| Plug (output) | `K` | `adapter::types::unidirectional::AUI` | 0=Normal (`Aktiv`=FALSE), 1=Force FALSE (`Aktiv`=TRUE, `Wert`=FALSE), 2=Force TRUE (`Aktiv`=TRUE, `Wert`=TRUE) |

## Functionality

Internally the block uses two chained, generic `F_SEL` blocks (the standard IEC 61131-3 selector
`OUT := G ? IN1 : IN0`) instead of custom ST logic:

1. **`F_SEL_Wert`**: `G := Wert.D1`. Returns `Override_K_ForceFalse` (1) when `Wert = FALSE`,
   otherwise `Override_K_ForceTrue` (2). Triggered by `Wert.E1`.
2. **`F_MOVE`** (attribute `DataType="UINT"`): captures `F_SEL_Wert.OUT`, triggered by
   `F_SEL_Wert.CNF`. Acts as a type anchor for `F_SEL`'s generic `ANY` result (see Technical
   Details) and then re-triggers `F_SEL_Aktiv`.
3. **`F_SEL_Aktiv`**: `G := Aktiv.D1`. Returns `Override_K_Normal` (0) when `Aktiv = FALSE`,
   otherwise the value most recently held by `F_MOVE` (1 or 2). Triggered both directly by
   `Aktiv.E1` and indirectly via `F_MOVE.CNF`, so a change in `Wert` alone still produces a fresh
   `K` even when `Aktiv` itself hasn't changed.
4. `F_SEL_Aktiv.OUT`/`F_SEL_Aktiv.CNF` are wired directly onto the data output variable `K.D1` and
   the event `K.E1` of the block's own plug — no separate `_TO_AUI` conversion FB in between (see
   Technical Details).

## Technical Details

- **Writing directly onto its own plug pins.** Instead of routing through a `UINT_TO_AUI`-style
  conversion FB, the block connects `F_SEL_Aktiv.OUT`/`.CNF` directly to `K.D1`/`K.E1` — the
  event/data variables the `AUI` adapter type itself declares on the plug side. The same technique
  is used by [const_AX_TRUE](../types/unidirectional/BOOL/constants/const_AX_TRUE.md) and
  [const_AX_FALSE](../types/unidirectional/BOOL/constants/const_AX_FALSE.md) for their own `OUT`
  plug.
- **`F_MOVE` as a type anchor for `F_SEL`'s generic `ANY` result.** `F_SEL.OUT` is generic
  (`ANY`); without a downstream `F_MOVE` carrying a fixed `DataType` attribute, the value can't be
  cleanly passed to the second `F_SEL` call as a `UINT`.
- **The K values are named constants, not literals.** `Override_K_Normal`/
  `Override_K_ForceFalse`/`Override_K_ForceTrue` come from the global constants package
  [Override_K](const/Override_K.md) (`adapter::OverrideK::const`), not as bare `UINT#0`/`UINT#1`/
  `UINT#2` literals directly in the `F_SEL` parameters.
- **No `REQ`/`CNF` of its own.** The block reacts exclusively to the sockets' own events
  (`Aktiv.E1`, `Wert.E1`) — there is no external trigger input.

## State Overview

The block has no state machine of its own (a composite FB without an ECC); its behavior is purely
combinational, recomputed on every change to `Aktiv` or `Wert`.

| Aktiv | Wert | K |
| :---: | :---: | :---: |
| FALSE | — | 0 (Normal) |
| TRUE | FALSE | 1 (Force FALSE) |
| TRUE | TRUE | 2 (Force TRUE) |

## Application Scenarios

- **Sensor override via RW OPC-UA nodes**: feed an `Aktiv`/`Wert` pair subscribed via
  `AX_SUBSCRIBE_1` (e.g. `Sensor.Leermelder.Override.Aktiv`/`.Wert`) directly into the `K` input
  of an `AX_AUI_MUX_3`, whose three inputs supply the normal value, `FALSE`, and `TRUE`.
- **Diagnostic/test pages**: any boolean sensor that a web UI needs to force to a fixed value for
  testing can reuse the same `Aktiv`/`Wert`/`K` pattern.

## ⚖️ Comparison with Similar Blocks

- **[AX_AUI_MUX_3](../selection/unidirectional/BOOL/AX_AUI_MUX_3.md)**: the actual multiplexer
  that `Override_K_Select` drives with its `K` output. `Override_K_Select` only computes the
  selector; it does not select a value itself.
- **[const_AX_TRUE](../types/unidirectional/BOOL/constants/const_AX_TRUE.md) /
  [const_AX_FALSE](../types/unidirectional/BOOL/constants/const_AX_FALSE.md)**: supply the fixed
  `IN2`/`IN3` values (Force FALSE/TRUE) that the selector computed by `Override_K_Select` picks
  out on the `AX_AUI_MUX_3`.
- **[Override_K](const/Override_K.md)**: the global constants package with the three named K
  values this block uses internally.

## Conclusion

`Override_K_Select` bundles the conversion of an Aktiv/Wert override pair into a MUX selector in a
single, reusable block, built entirely from standard blocks (`F_SEL`, `F_MOVE`) with no custom ST
algorithms of its own. Combined with `AX_AUI_MUX_3` and the `const_AX_TRUE`/`const_AX_FALSE`
constants, this forms the complete, reusable pattern for a boolean sensor value that can be
forced via OPC-UA.

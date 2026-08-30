# Background Color Blocks: Shared Pattern

* * * * * * * * * *
## Introduction

`MyLib::sys` contains, in both training systems (`test_AX` and `test_B`), a large family of nearly identical blocks that **switch the VT background color of one or more objects based on a single boolean signal** — e.g. `GreenWhiteBackground1_AX`, `GreenRedBackground4_AXS`, `RedWhiteBackground2_AXC`. This page explains the shared pattern once in full; the individual block pages link back here and only state the concrete differences (color pair, object count, variant).

## Naming Scheme

`<Color1><Color2>Background<N>[_aux][_AX][S][C]`

| Component | Meaning |
|---|---|
| **Color pair** (`GreenWhite`, `GreenRed`, `GreenBlue`, `RedGreen`, `RedWhite`) | `TRUE` → first color, `FALSE` → second color (e.g. `GreenWhiteBackground`: TRUE→green, FALSE→white) |
| **N** (1–4) | Number of VT objects colored **simultaneously from the same selector bit** (not: number of independent channels) |
| **`_aux`** (N=1 only) | Uses `Q_BackgroundColourAux` instead of `Q_BackgroundColour` — targets an ISOBUS **Auxiliary Function** object instead of a regular softkey/button/data-mask object. For N≥2 variants, this role may already be baked into one specific position (see the individual page). |
| **`_AX`** (test_AX only) | The selector signal arrives via an `AX` adapter socket (`DI1`), not as a plain data input. In test_B this suffix is absent — there, `DI1` is a plain `BOOL` data input. |
| **`S`** | Object ID(s) are passed via the structured type `isobus::UT::Q::types::s1ObjectID` (`u16ObjIds`, unpacked internally via `F_MOVE`) instead of individual `UINT u16ObjId` inputs — a later unification of object-ID passing in the library. |
| **`C`** ("Compact") | A thin wrapper that just instantiates the base variant (`_AX` or `_AXS`) and doesn't expose the `CNF` event outputs/intermediate values (`STATUS_n`, `u8OldColour_n`, `result_n`) — for the common case where those diagnostic values aren't needed. |

Examples: `GreenWhiteBackground1_AX` (base, 1 object, adapter), `GreenWhiteBackground1_AXC` (compact wrapper of it), `GreenWhiteBackground1_AXS` (with struct object ID), `GreenWhiteBackground1_AXSC` (struct ID + compact), `GreenWhiteBackground1_aux_AX` (like base, but for an AUX-function object).

## Functionality (base variant, N=1)

1. The selector signal (`DI1` adapter for `_AX`, otherwise `DI1` data value) goes to `AX_SEL`/`F_SEL` (binary selection), parameterized with the two color constants (`IN0`=second color, `IN1`=first color, e.g. `IN0=COLOR_WHITE`, `IN1=COLOR_GREEN`).
2. `AX_SEL.CNF` triggers `Q_BackgroundColour.REQ` (or `Q_BackgroundColourAux.REQ` for `_aux`).
3. `Q_BackgroundColour` sets the background color of the VT object identified by `u16ObjId` and reports back `CNF` with `STATUS`, `u8OldColour` (previous color), and `s16result` (error code).

## Functionality (N≥2)

With multiple objects (`GreenRedBackground4_AX` and similar), there is still **only one** selector (`DI1`/`AX_SEL`), whose output is distributed in parallel to several `Q_BackgroundColour_n` instances (numbered `_1`..`_N`) — each with its own `u16ObjId`/`u16ObjIdA`/`u16ObjIdB` (different object IDs, sometimes for different object roles like softkey/AUX/button) and its own `STATUS_n`/`u8OldColour_n`/`result_n`/`CNF_n` outputs. **Which position uses `Q_BackgroundColourAux` instead of `Q_BackgroundColour` varies per block** (not always the same position) — each block's individual page states the concrete mapping.

## Technical Details

- **One selector, multiple destinations**: the point of N>1 is to apply the same boolean condition (e.g. "channel active") simultaneously to several VT representations of the same logical state (e.g. softkey background AND auxiliary-function background AND button background for the same function).
- **`_aux`/`Q_BackgroundColourAux`**: ISOBUS auxiliary function objects (controls freely assignable by the driver) require their own Q-block, since they use a different object ID range/VT message than regular softkeys/buttons.
- **`S` variant as a later unification**: identifiable by the later `VersionInfo` dates (2026 vs. 2022) — the `S` variants are a follow-up refactor that aligns object-ID passing with a later-established standard (`s1ObjectID`), without replacing the older base variants.

## Family Overview

| Color pair | test_AX (base/_aux, each also with S/SC/C) | test_B (base/_aux, each also with S/SC/C) |
|---|---|---|
| Green/White | 1, 2, 3, 4 | 1, 2, 3, 4 |
| Green/Red | 1, 2, 3, 4 | 1, 2, 3, 4 |
| Green/Blue | 1 | 1 |
| Red/Green | 1, 4 | 1, 4 |
| Red/White | 1, 2, 3, 4 | 1, 2, 3, 4 |

In test_AX every combination additionally carries the `_AX` suffix; in test_B it's absent (selector is a `BOOL` data input instead of an adapter socket) — see [MyLib (test_B) → sys](../../MyLib_B/sys/index.md).

## Summary

The background color blocks are a single recurring idea (boolean signal → color selection → `Q_BackgroundColour`) offered in many small variants for different color pairs, object counts, and object-ID conventions. Understand one variant and you understand them all — the individual pages only state the concrete parameters.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

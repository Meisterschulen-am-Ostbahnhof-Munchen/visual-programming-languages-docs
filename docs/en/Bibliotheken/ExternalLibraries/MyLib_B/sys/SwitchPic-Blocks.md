# SwitchPic(Col) Blocks: Shared Pattern

* * * * * * * * * *

## Introduction

`MyLib::sys` (test_B) contains a family of blocks that **display a different VT picture (object-pointer target) and/or a different background color depending on state** — e.g. a slide-valve animation with the states Unknown/Closed/Opening/Opened/Closing. This page explains the shared pattern; the individual pages only state the concrete differences.

## Naming Scheme

`SwitchPic[Col]_<states>_<variant>[_aux]`

| Component | Meaning |
|---|---|
| **`Col`** (optional) | In addition to the picture, also switches a background color (`Q_BackgroundColour`) to match the state, not just a picture (`Q_NumericValue`). |
| **States** (`2` or `5`) | `2` = boolean selector `DI1` (`up`/`down`, type `s2x1ObjectIDs`/`s2x2ObjectIDs`); `5` = `iSTATE` selector (`USINT`, slide-valve state machine Unknown/Closed/Opening/Opened/Closing, type `SchieberStruct`/`SchieberAuxInStruct`), evaluated via `F_MUX_5`. |
| **Variant** (`1`/`2`/`3`, `SwitchPic` only) | Number/kind of VT objects updated simultaneously: `1`=regular VT object only (softkey/data mask), `2`=plus an AUX object, `3`=plus an AUX object AND a second regular object ("button"). |
| **`_aux`** | Only AUX object(s) are switched, no regular VT object (counterpart to variant `1`, but exclusively for auxiliary function objects). |

## Functionality

1. A structure `pictures`/`Sets` (type depending on states/variant) holds, for every possible state, the associated object ID(s) (picture and, where applicable, color).
2. `F_MOVE` unpacks this structure into individual values.
3. A multiplexer (`F_SEL` for 2 states, `F_MUX_5` for 5 states, driven by `DI1` or `iSTATE`) selects the values matching the current state.
4. `Q_NumericValue`/`Q_NumericValueAux` sets the selected object-pointer value on the VT object identified by `Picture`/`PictureA`/`PictureB`; `Col` variants additionally set `Q_BackgroundColour`/`Q_BackgroundColourAux`'s background color on the object identified by `Color`.
5. With multiple target objects (variant 2/3), several `Q_NumericValue(Aux)` instances are chained in a fixed INIT sequence (each triggers the next via `INITO`) before `INITO` is reported outward.

## Summary

A multiplexer pattern: state → struct lookup (`F_MOVE`) → selection (`F_SEL`/`F_MUX_5`) → one or more `Q_NumericValue(Aux)`/`Q_BackgroundColour(Aux)` targets. The variant number (1/2/3) and `Col`/`_aux` only determine how many targets of which kind (regular/AUX, picture/color) get updated simultaneously.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

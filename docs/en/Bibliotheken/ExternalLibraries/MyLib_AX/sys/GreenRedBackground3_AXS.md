# GreenRedBackground3_AXS

![GreenRedBackground3_AXS_network](./GreenRedBackground3_AXS_network.svg)

* * * * * * * * * *

## Introduction

`GreenRedBackground3_AXS` switches the VT background color of 3 objects based on a boolean selector signal: `TRUE` → **Grün**, `FALSE` → **Rot**. The selector signal arrives via an `AX` adapter socket (`DI1`). The object ID is passed via the structured type `s1ObjectID` (`u16ObjIds`).

| Position | Object ID source | Block |
|---|---|---|
| 1 | `F_MOVE.OUT.u16ObjId` | `Q_BackgroundColour` (regular object) |
| 2 | `F_MOVE.OUT.u16ObjIdA` | `Q_BackgroundColour` (regular object) |
| 3 | `F_MOVE.OUT.u16ObjIdA` | `Q_BackgroundColourAux` (auxiliary function object) |

For the general pattern (selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`), see [Background Color Blocks (shared pattern)](./Background-Color-Blocks.md).

## Summary

One of many variants in the background color block family: color pair Grün/Rot, 3 objects, adapter selector, struct. object ID.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

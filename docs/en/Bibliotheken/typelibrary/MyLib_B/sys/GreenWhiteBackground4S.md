# GreenWhiteBackground4S

![GreenWhiteBackground4S_network](./GreenWhiteBackground4S_network.svg)

* * * * * * * * * *
## Introduction

`GreenWhiteBackground4S` switches the VT background color of 4 objects based on a boolean selector signal: `TRUE` → **Grün**, `FALSE` → **Weiß**. The selector signal arrives as a plain `BOOL` data input (`DI1`). The object ID is passed via the structured type `s1ObjectID` (`u16ObjIds`).

| Position | Object ID source | Block |
|---|---|---|
| 1 | `F_MOVE.OUT.u16ObjId` | `Q_BackgroundColour` (regular object) |
| 2 | `F_MOVE.OUT.u16ObjIdA` | `Q_BackgroundColour` (regular object) |
| 3 | `F_MOVE.OUT.u16ObjIdA` | `Q_BackgroundColourAux` (auxiliary function object) |
| 4 | `F_MOVE.OUT.u16ObjIdB` | `Q_BackgroundColour` (regular object) |

For the general pattern (selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`), see [Background Color Blocks (shared pattern)](../../MyLib_AX/sys/Background-Color-Blocks.md).

## Summary

One of many variants in the background color block family: color pair Grün/Weiß, 4 objects, BOOL selector, struct. object ID.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

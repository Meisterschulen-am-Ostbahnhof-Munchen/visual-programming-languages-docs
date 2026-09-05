# GreenWhiteBackground4

![GreenWhiteBackground4_network](./GreenWhiteBackground4_network.svg)

* * * * * * * * * *

## Introduction

`GreenWhiteBackground4` switches the VT background color of 4 objects based on a boolean selector signal: `TRUE` → **Grün**, `FALSE` → **Weiß**. The selector signal arrives as a plain `BOOL` data input (`DI1`). The object ID is passed via inputs `u16ObjId, u16ObjIdA, u16ObjIdB`.

| Position | Object ID source | Block |
|---|---|---|
| 1 | `u16ObjId` | `Q_BackgroundColour` (regular object) |
| 2 | `u16ObjIdA` | `Q_BackgroundColour` (regular object) |
| 3 | `u16ObjIdA` | `Q_BackgroundColourAux` (auxiliary function object) |
| 4 | `u16ObjIdB` | `Q_BackgroundColour` (regular object) |

For the general pattern (selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`), see [Background Color Blocks (shared pattern)](../../MyLib_AX/sys/Background-Color-Blocks.md).

## Summary

One of many variants in the background color block family: color pair Grün/Weiß, 4 objects, BOOL selector.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

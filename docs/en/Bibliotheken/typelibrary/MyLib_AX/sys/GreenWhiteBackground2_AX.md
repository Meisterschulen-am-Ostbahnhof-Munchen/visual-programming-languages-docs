# GreenWhiteBackground2_AX

![GreenWhiteBackground2_AX_network](./GreenWhiteBackground2_AX_network.svg)

* * * * * * * * * *
## Introduction

`GreenWhiteBackground2_AX` switches the VT background color of 2 objects based on a boolean selector signal: `TRUE` → **Grün**, `FALSE` → **Weiß**. The selector signal arrives via an `AX` adapter socket (`DI1`). The object ID is passed via inputs `u16ObjIdA`.

| Position | Object ID source | Block |
|---|---|---|
| 1 | `u16ObjIdA` | `Q_BackgroundColour` (regular object) |
| 2 | `u16ObjIdA` | `Q_BackgroundColourAux` (auxiliary function object) |

For the general pattern (selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`), see [Background Color Blocks (shared pattern)](./Background-Color-Blocks.md).

## Summary

One of many variants in the background color block family: color pair Grün/Weiß, 2 objects, adapter selector.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

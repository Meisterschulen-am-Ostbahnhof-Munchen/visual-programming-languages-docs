# GreenBlueBackground1_aux_AXS

![GreenBlueBackground1_aux_AXS_network](./GreenBlueBackground1_aux_AXS_network.svg)

* * * * * * * * * *
## Introduction

`GreenBlueBackground1_aux_AXS` switches the VT background color of one object based on a boolean selector signal: `TRUE` → **Blau**, `FALSE` → **Weiß**. The selector signal arrives via an `AX` adapter socket (`DI1`). The object ID is passed via the structured type `s1ObjectID` (`u16ObjIds`).

For the general pattern (selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`), see [Background Color Blocks (shared pattern)](./Background-Color-Blocks.md).

## Summary

One of many variants in the background color block family: color pair Blau/Weiß, 1 object, adapter selector, struct. object ID.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

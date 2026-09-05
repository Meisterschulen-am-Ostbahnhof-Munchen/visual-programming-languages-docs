# Select_EnableOk

![Select_EnableOk_network](./Select_EnableOk_network.svg)

* * * * * * * * * *

## Introduction

`Select_EnableOk` derives one of 3 parameterized USINT values from 2 bools (`bEnable`, `bOk`): `valDisabled` (bEnable=FALSE), `valOk` (bEnable=TRUE and bOk=TRUE), `valFault` (bEnable=TRUE and bOk=FALSE). A generic 2-stage `F_SEL`, not limited to colors - per the source comment, extracted from [`Q_BackgroundColour_EnableOk`](./Q_BackgroundColour_EnableOk.md) to decouple the pure selection logic from the VT background-color application.

## Function blocks used

- **F_SEL_OK_FAULT** (`iec61131::selection::F_SEL`): selects between `valFault`/`valOk` based on `bOk`.
- **F_MOVE** (`iec61131::selection::F_MOVE`, `DataType=USINT`): passes the intermediate value through unchanged (sequencing the two selection stages).
- **F_SEL_ENABLE** (`iec61131::selection::F_SEL`): selects between `valDisabled`/intermediate result based on `bEnable`.

## Program flow and connections

`REQ` -> `F_SEL_OK_FAULT.REQ` -> `F_MOVE.REQ` -> `F_SEL_ENABLE.REQ` -> `CNF`. On the data side: `bOk`/`valFault`/`valOk` -> `F_SEL_OK_FAULT` -> `F_MOVE` -> `F_SEL_ENABLE.IN1`, in parallel `bEnable`/`valDisabled` -> `F_SEL_ENABLE.IN0`/`.G` -> `value`.

## Summary

Generic 2-bool-to-1-of-3-values selection, reusable beyond background colors (e.g. for any enable/ok status display).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

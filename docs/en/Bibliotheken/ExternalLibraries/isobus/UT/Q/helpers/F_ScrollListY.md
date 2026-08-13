# F_ScrollListY

![F_ScrollListY](F_ScrollListY.svg)

* * * * * * * * * *
## Introduction

The `F_ScrollListY` function computes, from the current scroll position (in rows) and the row
height (in pixels), the Y offset that `Container_Scrolling_Content.Top` needs so the correct row
appears inside the viewport. It's a pure calculation helper for the `ScrollFS` scroll block
(package `isobus::UT::Q`) and is used internally there.

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request, reads `i32Pos` and `i32RowHeight`.

### **Event Outputs**

- `CNF`: Confirms the calculation and delivers the return value (unnamed `OutputVar`, addressed
  via `<InstanceName>.` with a trailing dot — the IEC 61131-3 convention for a function's own
  return value).

### **Data Inputs**

- `i32Pos` (DINT): Current scroll position in rows (0…`i32PosMax`).
- `i32RowHeight` (DINT): Row height in pixels.

### **Data Outputs**

- *(unnamed)* (INT): `Container_Scrolling_Content.Top` value (`s16Yposition` for
  `Q_ChildPosition`).

### **Adapters**

No adapters available.

## Functionality

The calculation is a single formula:

```
OUT := DINT_TO_INT(-(i32Pos * i32RowHeight))
```

The larger `i32Pos` gets, the more negative `Top` becomes — the content container shifts up,
later rows scroll into the viewport. At `i32Pos = 0`, `Top = 0` (start of the list, no offset).

## Technical Details

- **`DINT_TO_INT` cast**: The internal calculation runs in `DINT` (32-bit); the result is only
  converted to `INT` (16-bit) at the end, because `Q_ChildPosition.s16Yposition` expects an
  `INT` (ISO 11783-6 F.16, "Change Child Location").
- **Concretely typed, no `ANY`**: Unlike generic blocks such as `F_MOVE` or `F_SEL`, all
  inputs/outputs are fixed-typed (`DINT`/`INT`) — so wiring it inside `ScrollFS` needs no `MOVE`
  anchor, even though the value originates from other generic/struct fields.

## State Overview

Stateless — every `REQ` recomputes the result immediately from the current input values.

## Application Scenarios

- Used exclusively inside `ScrollFS` to recompute `Container_Scrolling_Content.Top` on every
  position change.

## ⚖️ Comparison with Similar Blocks

- **Versus `F_ScrollBarY`**: both compute a Y offset from the scroll position, but
  `F_ScrollBarY` additionally scales it to the (smaller) scrollbar span and applies an offset —
  see [F_ScrollBarY](F_ScrollBarY.md).

## Conclusion

A small, robust calculation function — responsible for exactly one conversion (row position to
list pixel offset), concretely typed and side-effect free.

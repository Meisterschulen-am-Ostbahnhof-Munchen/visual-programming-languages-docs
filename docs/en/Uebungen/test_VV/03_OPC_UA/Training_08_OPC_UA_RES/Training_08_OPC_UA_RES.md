# Training_08_OPC_UA_RES: Toggle Flip-Flop over OPC-UA — Comparison Baseline for Training_09

![Training_08_OPC_UA_RES_network](./Training_08_OPC_UA_RES_network.svg)

* * * * * * * * * *

## Introduction

`Training_08_OPC_UA_RES` uses the exact same composites as
`Training_03_OPC_UA_RES` (`Uebung_010d_PC_A_OPC`/`Uebung_010d_PC_B_OPC`) and
the same OPC-UA addresses (`FF1_*`) — functionally identical to
Training_03.

The reason for its own `.sys` file: Training_08 serves as a direct
**comparison baseline (manual wiring)** immediately next to
`Training_09_OPC_UA_RES` (adapter variant), matching the
Training_04/Training_06 and Training_05/Training_07 pairs. Without
Training_08, the before/after comparison of adapter bundling for the
toggle-only variant would have to reach back to Training_03, which sits
elsewhere in the series.

## Composites Used

Identical to Training_03 — see
[Training_03_OPC_UA_RES](../Training_03_OPC_UA_RES/Training_03_OPC_UA_RES.md)
for the full description of `Uebung_010d_PC_A_OPC` and
`Uebung_010d_PC_B_OPC`.

| Composite | Device |
|---|---|
| [`Uebung_010d_PC_A_OPC`](./Uebung_010d_PC_A_OPC_network.svg) | A (`192.168.1.11`) |
| [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC_network.svg) | B (`192.168.1.12`) |

## OPC-UA Address Space

Identical to Training_03 (`FF1_TRIGGER_*`, `FF1_STATE_*`) — see
[Training_03_OPC_UA_RES](../Training_03_OPC_UA_RES/Training_03_OPC_UA_RES.md#opc-ua-address-space).

## Program Flow and Connections

Identical to Training_03 — the flow and connections are described there in
detail.

## Technical Notes

- **Deliberate reuse, no new logic**: Training_08 introduces no new
  function. It ensures that the "before" side of the toggle-only adapter
  comparison (see `Training_09_OPC_UA_RES`) sits directly next to its
  "after" side in the training series — just as Training_04/06 and
  Training_05/07 already sit as pairs.

## Learning Objectives

- A direct, immediately adjacent before/after comparison (manual vs.
  adapter) for all three action sets in the series (toggle-only, SR-only,
  SR+toggle).

**Difficulty**: Intermediate
**Prerequisites**: `Training_03_OPC_UA_RES` (identical pattern).

## Summary

`Training_08_OPC_UA_RES` is functionally identical to Training_03 and exists
solely as the immediate comparison baseline for the adapter variant
`Training_09_OPC_UA_RES`.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

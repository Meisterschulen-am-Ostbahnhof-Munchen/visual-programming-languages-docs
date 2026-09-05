# Design Pattern: Chain of Actions (incl. Generic Actuation)

![ChainOfActionsDemo](./ChainOfActionsDemo.svg)

![TrueUntil](./TrueUntil.svg)

* * * * * * * * * *

## Introduction

A multi-stage movement sequence (e.g. "extend cylinder A, then extend
cylinder B, then retract cylinder B, then retract cylinder A") can be
implemented as ONE large ECC with many states/transitions — this
quickly becomes unmanageable ("spaghetti code"). The solution: break
the sequence into identical, reusable **action blocks** and chain them
via `DONE`→`TRIGGER` connections into a linear chain — each block only
knows its own step, and the order emerges purely from the wiring, not
from a central ECC.

## Course slide reference

- Slide 65 – *"Generic Actuation"* (Structural, problem: code
  reusability) — introduces the generic `TrueUntil` block.
- Slide 66 – *"Chain of Actions"* (Behavioural, Compositional, problem:
  "spaghetti code") — a vacuum gripper example (two cylinders
  `LC`/`RC`).
- Slide 67 – a more complex example with 5 chained action blocks plus
  `E_SWITCH`/`E_MERGE` for branching — deliberately not rebuilt here
  (see "Scope" below).

## The generic block: `TrueUntil`

- **Event inputs:** `TRIGGER`, `REQ` (alternate trigger)
- **Event outputs:** `TO_POSITION` (drive the actuator), `STOP`,
  `DONE` (continue the chain)
- **BOOL input:** `inPosition` (feedback, position reached)

Idea: "Move to a position and wait until `inPosition` becomes true
(`DONE`)." Generic, because the same block is reused for EVERY kind of
movement — wired externally only via `TRIGGER`/`inPosition`, with no
actuator-specific logic of its own. Deliberately without
`INIT`/`INITO` (no state that would need initializing).

## Demo: `ChainOfActionsDemo`

A chain of 4 `TrueUntil` instances (`Step1`…`Step4`), analogous to the
slide's LCExtend/RCExtend/RCRetract/LCRetract example, but named
generically rather than cylinder-specifically, chained via
`DONE`→`TRIGGER`. Each stage has its own `StepN_InPosition` BOOL
exposed at the subapp interface, letting "position reached" be
simulated manually while testing.

## Scope

The more complex example with branching/`E_MERGE` (slide 67) is a
later extension, not part of this implementation. The
[Decorator pattern](DecoratorPattern.md) (slide 68, `TrueUntil` plus a
`TE` condition) is a separate, distinct pattern.

## Open point

The exact role of `REQ` alongside `TRIGGER` isn't unambiguously
readable from the slide's compressed graphic (possibly an
abort/repeat event). This implementation treats `REQ` the same as
`TRIGGER` for now (re-triggering the movement). Not yet tested in
4diac.

## Summary

`TrueUntil` is the reusable block behind three further patterns in
this collection: [Decorator](DecoratorPattern.md),
[Start/Stop](StartStopPattern.md), and [Reset](ResetPattern.md) all
reuse it unchanged. `ChainOfActionsDemo` shows the core idea: a linear
sequence built from pure wiring instead of a central ECC.

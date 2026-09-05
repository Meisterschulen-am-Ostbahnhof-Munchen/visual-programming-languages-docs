# Design Pattern: Decorator

![DecoratorDemo](./DecoratorDemo.svg)

* * * * * * * * * *

## Introduction

An existing block (here: [`TrueUntil`](ChainOfActionsPattern.md))
sometimes needs to be skippable ("only run this step when condition X
holds"), without changing the block itself — the classic decorator
idea from object orientation: add behavior by rewiring/wrapping instead
of touching the original class.

## Course slide reference

Slide 68 – *"Decorator"* (category: Structural, problem: "Conditional
execution of FBs"). The slide shows two variants: **internal**
(`TrueUntil` itself gets a second BOOL input `TE`, changing the block)
and **external** (a generic gate block is wired in front of the
unchanged block). Only the external variant is implemented here — the
actual decorator idea, matching the already-existing, unchanged
`TrueUntil.fbt`.

## Block: `E_PERMIT`

`E_PERMIT` is a **standard block** from the 4diac standard library
(`iec61499::events::E_PERMIT`), not a new, custom-designed block:

- **Event input:** `EI` (with qualifier `PERMIT`)
- **Event output:** `EO`
- **BOOL input:** `PERMIT`

If `PERMIT` is `FALSE` when `EI` arrives, there's no matching
transition — per standard ECC semantics, the event is simply discarded
(no `EO`, no state change). `E_PERMIT` is generic and reusable beyond
the decorator — the same pattern is also used by the
[Start/Stop pattern](StartStopPattern.md).

## Demo: `DecoratorDemo`

A `TrueUntil` block (reused unchanged from the
[Chain of Actions pattern](ChainOfActionsPattern.md)), whose `TRIGGER`
is gated through `E_PERMIT`: `TRIGGER` → `E_PERMIT.EI`, `TE` (BOOL) →
`E_PERMIT.PERMIT`, `E_PERMIT.EO` → `TrueUntil.TRIGGER`. If `PERMIT` is
`FALSE`, the event is swallowed, `TrueUntil` never receives a
`TRIGGER` and does nothing. `TE` is exposed at the subapp interface so
gating can be controlled manually while testing.

## Summary

The decorator idea is implemented here without a single new,
use-case-specific block — the generic `E_PERMIT` is enough, as long as
it sits unchanged in front of the block being gated. Not yet tested in
4diac.

# Design Pattern: Start/Stop

![StartStopDemo](./StartStopDemo.svg)

* * * * * * * * * *

## Introduction

A plant needs to be switchable on and off overall via a separate HMI
panel (start/stop button), independent of what the actual control
logic is currently doing. Wiring this start/stop permission directly
into the core logic mixes two responsibilities (operating state vs.
functional sequencing) that should really be changeable independently
of each other.

## Course slide reference

Slide 70 – *"The Start/Stop pattern"* (category: Compositional /
Architectural, problem: "Separate start-stop logic implied by HMI
console from the main control logic").

## Blocks (both standard)

The start/stop state is modelled as its own persistent state (an
`E_SR` latch) and wired in front of the actual trigger logic through a
permission gate (`E_PERMIT`, see the
[Decorator pattern](DecoratorPattern.md)):

```
E_SR (iec61499::events::E_SR)
  Event inputs:  S (Set), R (Reset)
  Event output:  EO
  BOOL output:   Q

E_PERMIT (iec61499::events::E_PERMIT)
  Event input:   EI (with qualifier PERMIT)
  Event output:  EO
  BOOL input:    PERMIT
```

Wiring: `START` → `E_SR.S`, `STOP` → `E_SR.R`; `E_SR.Q` →
`E_PERMIT.PERMIT` (the gate is open as long as the plant is started);
the actual trigger event runs through `E_PERMIT.EI` → `EO` and reaches
the control logic only while `Q=TRUE` — exactly the same `E_PERMIT`
mechanism as the decorator pattern, except the permission condition
here isn't an arbitrary external condition but specifically a
persistent start/stop state.

## Demo: `StartStopDemo`

**No new blocks** — just the two standard blocks above. `START`/`STOP`
set/reset an `E_SR`; its `Q` opens an `E_PERMIT` that lets a `TRIGGER`
event through to the (reused unchanged from the
[Chain of Actions pattern](ChainOfActionsPattern.md)) `TrueUntil`
instance — the `TRIGGER` only gets through while the plant is
"started". Structurally almost identical to the decorator demo, just
with `E_SR` as the source of the permission condition instead of an
arbitrary external `TE` variable.

## Summary

Start/Stop separates operating state from application logic by reusing
exactly the same `E_PERMIT` gate mechanism as the decorator — just with
a persistent `E_SR` state instead of an arbitrary condition as the
permission source. The [Reset pattern](ResetPattern.md) builds directly
on this setup, adding an ungated reset path. Not yet tested in 4diac.

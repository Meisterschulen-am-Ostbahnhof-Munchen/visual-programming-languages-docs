# Design Pattern: Purely Event-Driven Function Blocks

![EventDrivenCylinder](./EventDrivenCylinder.svg)

* * * * * * * * * *

## Introduction

A simple control automaton is often modelled like this: sensors (e.g.
`atHome`, `atEnd`) as **BOOL data inputs**, queried in transition
conditions (`REQ AND atHome`), and actuator outputs (`extend`,
`retract`) as **BOOL data outputs**, set by a one-line ST algorithm.
This bloats the model in two ways: every BOOL output needs its own
(trivial) algorithm, and every BOOL data connection is an extra
element that slows down formal verification (state space, model
checking).

The solution: sensor and actuator signals are consistently modelled as
**events** instead of BOOL data. Instead of a continuously available
`atHome` BOOL queried in a transition condition, an `AT_HOME` event
fires exactly once when the sensor triggers. Instead of a BOOL output
`extend` that needs an algorithm, an `EXTEND` event directly triggers
the extension — no assignment, no algorithm needed, the ECC simply
routes the event straight through. Result: transition conditions
become plain event names, and the ECC no longer needs algorithms, only
event wiring.

## Course slide reference

Slide 64 – *"Purely Event-Driven function blocks"* (category:
Structural). Transforms the slide's `DoubleActingCylinder` example
(event inputs `INIT`/`REQ`/`EXTEND`/`RETRACT`, BOOL inputs
`atHome`/`atEnd`, BOOL outputs `extend`/`retract`) fully into its
event-driven final form — skipping the slide's own intermediate step,
where only the outputs are eventified.

## Block: `EventDrivenCylinder`

Basic FB, **no BOOL data pins**, events only — no adapter needed:

- **Event inputs:** `START` (initialize), `EXTEND_REQ` / `RETRACT_REQ`
  (request movement), `AT_HOME` / `AT_END` (position sensors)
- **Event outputs:** `INITO`, `EXTEND` / `RETRACT` (actuator commands),
  `STOP` (fires once at the end of every movement, before `CNF`),
  `CNF` (completion confirmation)

The exact ECC wiring is a self-consistent reconstruction (HOME/Extended
as stable idle states, `EXTEND_REQ`/`RETRACT_REQ` as triggers,
`AT_END`/`AT_HOME` as completion conditions) — the interface names are
directly readable from the slide, but the transition wiring in the
slide's compressed ECC diagram isn't always unambiguous.

No separate demo subapp needed: because it has no data pins, the block
is directly testable in FORTE monitoring (firing events manually on the
instance) without simulating any BOOL values — that's exactly the
advantage this pattern is meant to demonstrate.

## Open point

The exact ECC wiring is a plausible, self-consistent reconstruction,
but not verifiable pixel-for-pixel against the slide — see above. Not
yet tested in 4diac.

## Summary

`EventDrivenCylinder` shows how a classic BOOL-data-heavy control
automaton is converted entirely to events: no data connections, no
algorithms, just event routing in the ECC. It serves as the
application-layer block for the
[IO Abstraction Layer pattern](IOAbstractionPattern.md).

# Design Pattern: IO Abstraction Layer

![IOAbstractionDemo](./IOAbstractionDemo.svg)

* * * * * * * * * *

## Introduction

When application logic accesses raw hardware BOOL signals directly
(continuously read digital inputs/outputs), two responsibilities get
mixed together: "how is a signal physically read/written" and "what
does a signal change mean functionally". This hinders reuse (the same
application logic on different hardware) and makes the application
logic needlessly BOOL-data-heavy — exactly the problem the
[Purely Event-Driven pattern](PurelyEventDrivenPattern.md) also solves.

## Course slide reference

Slide 63 – *"Input/Output (IO) abstraction layer"* (category:
Architectural). Shows a 5-layer architecture: Hardware Layer (Input) →
Input HAL → Application Layer → Output HAL → Hardware Layer (Output).
The slide names `SYMLINKMULTIVARDST`/`SYMLINKMULTIVARSRC` for this —
checked: neither a standard 4diac block nor present anywhere in this
repo, likely a fortiss research block outside the standard
distribution.

## Implementation: this repo's own mechanism instead of the slide's blocks

Instead of an unverified reconstruction of
`SYMLINKMULTIVARDST`/`SRC`, this repo uses an already-existing, real
mechanism for exactly the same problem (raw hardware BOOL ↔ event):

- **Hardware Layer (Input) + Input HAL, combined:** `logiBUS_IE` (reads
  a digital input and directly fires an event — no separate edge
  detector needed). Four instances for `EXTEND_REQ`, `RETRACT_REQ`,
  `AT_HOME`, `AT_END`.
- **Application Layer:** [`EventDrivenCylinder`](PurelyEventDrivenPattern.md)
  (reused unchanged), fully event-driven, no BOOL data pin.
- **Output HAL:** two `E_SR` latches, each reset by the other command
  event — convert a command event (`EXTEND`, `RETRACT`) into a
  persistent BOOL signal for the actuator.
- **Hardware Layer (Output):** `logiBUS_QX`, writes a digital output,
  triggered by an event.

One of the `logiBUS_IE` instances supplies the `START` trigger for
`EventDrivenCylinder` via its own `INITO`, which fires automatically on
deployment.

## Summary

This completes all eight patterns documented in this collection, none
built/tested in 4diac yet. `IOAbstractionDemo` shows how the slide's
5-layer architecture can be implemented with this repo's own,
real, working blocks (`logiBUS_IE`/`QX`, `E_SR`) instead of the
unavailable slide blocks, without touching the actual application
logic (`EventDrivenCylinder`).

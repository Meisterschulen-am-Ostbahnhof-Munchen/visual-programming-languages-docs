# Design Pattern: TokenRing / Mutual Exclusion

![TokenRingPatternDemo](./TokenRingPatternDemo.svg)

![TokenRingNode](./TokenRingNode.svg)

* * * * * * * * * *

## Introduction

Two (or more) controllers share a physical resource that only one of
them may access at a time. Instead of hard-wiring the interlocking
logic between the controllers, a **token-ring protocol** is used: a
"token" (a permission marker) circulates round-robin between the
controllers; only whoever currently holds the token may use the shared
resource; once done, it passes the token to the next controller in the
ring. As with the [Handshake pattern](HandshakePattern.md), this
mechanism is encapsulated as its own, reusable **adapter type**.

## Source reference

Unlike the other patterns in this collection, TokenRing does **not**
appear in the official pattern taxonomy (slides 62/69), only as an
example on slide 15 in the "Modelling PLC systems" chapter, further
confirmed by two independent papers: W. Dai, V. Vyatkin, J. H.
Christensen, V. Dubinin, *"Function Block Implementation of Service
Oriented Architecture: Case Study,"* IEEE INDIN 2014, and R. Sinha, V.
Vyatkin, Z. Salcic, H. J. Park, *"Competitors or Cousins? Studying the
Parallels between Distributed Programming Languages SystemJ and
IEC61499."* Both describe the same two-cylinder example (`CylH`/`CylV`)
sharing a common axis.

## GIVE/RCV semantics

Directly confirmed by the INDIN14 paper: *"an adapter **input** MTXIN
and **output** MTXOUT are reserved"* — `MTXIN` = input adapter =
socket, `MTXOUT` = output adapter = plug (matches the socket/plug
behavior verified against real 4diac in the handshake pattern).

```
TokenRing
  Event inputs:   RCV   – confirmation from the receiver, token arrived
  Event outputs:  GIVE  – pass the token on to the neighbor
```

- **Plug** (`MTXOUT`, "giver"): fires `GIVE`, responds to `RCV`.
- **Socket** (`MTXIN`, "receiver"): responds to `GIVE`, fires `RCV`.

Every controller therefore has **two** adapter instances: `MTXOUT`
(direction toward the next controller) and `MTXIN` (direction from the
previous controller).

## Where is the token actually handed over?

No data is transferred at all — **the token IS the event**.
`TokenRing.adp` is deliberately dataless (no `VarDeclaration`, no
payload). The semantics: firing `GIVE` itself is the hand-off. Whoever
is currently between the ECC states `HANDLE_GIVE` and `PASS_ON` "has"
the token — not because a variable says so, but because the block is
currently in that phase of its state machine. Analogous to real token
ring networks, where the token is also just a specific bit pattern.
Weakness: there's no way to detect a duplicated or lost token (unlike
the data-carrying handshake variant).

## Block: `TokenRingNode`

A controller in the ring, with `MTXIN` (socket) and `MTXOUT` (plug),
following the same Init/Initialized/DeInit pattern as the handshake
blocks, a `REQUEST` event to request the critical section, and a
`SEED` event to bootstrap the ring once. Implements the branching
behavior from the source papers: the token holder works (if a request
is pending) and then passes the token on — or passes it on immediately
if no request is pending.

## Demo: `TokenRingPatternDemo`

A 5-node ring (`NodeA`…`NodeE`, `NodeE.MTXOUT` closes back onto
`NodeA.MTXIN`) — deliberately more than 2 nodes, so it's a real ring
rather than just a two-node back-and-forth as in the papers' example.

## Second occurrence

`TokenRing` also appears in Vyatkin's SoA example (slide 47, see the
[Handshake pattern](HandshakePattern.md)): there the adapter isn't used
for mutual exclusion between two equal controllers, but for
round-robin addressing of several downstream service participants —
the same adapter type, a second, different use.

## Summary

TokenRing encapsulates a classic mutual-exclusion protocol entirely
event-based, with no payload at all — the control flow itself carries
the state. Not yet tested in 4diac.

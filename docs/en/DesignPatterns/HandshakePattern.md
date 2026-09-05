# Design Pattern: Handshake

![HandshakePatternDemo](./HandshakePatternDemo.svg)

![HandshakeRequester](./HandshakeRequester.svg)

![HandshakeResponder](./HandshakeResponder.svg)

* * * * * * * * * *

## Introduction

When two function blocks (or subapplications, or devices) have a
request/response relationship — A asks B for something, B confirms or
unsolicitedly reports something back, A acknowledges that in turn — the
simplest case needs four separate event connections (`REQ`, `CNF`,
`IND`, `RSP`). With several such relationships between many blocks, a
"spaghetti connections" problem quickly emerges. The solution: bundle
the four events (and optional payload) into an **adapter type**. The
connection between the two communication partners is then established
through a single adapter connection (socket ↔ plug) instead of four
separate event lines.

## Course slide reference

Slide 72 – *"The handshake pattern"* (category: Behavioural), part of
a group of three shown together with the start/stop and reset patterns
on a Cylinder↔NextSystem example. Slide 48 ("Implementation of
Adapters") additionally supplies the generic adapter type declaration
that the data-carrying variant here is based on, and slides 41–47
("Message exchange between services") a detailed, multi-step
application example of the same vocabulary.

## The REQ/CNF/IND/RSP vocabulary

The classic Request/Indication/Response/Confirm service model that also
underlies IEC 61499 Service Interface Function Blocks:

- **REQ** – request from the requester to the responder: *"Please do
  X."*
- **CNF** – confirmation from the responder, synchronous to the
  request.
- **IND** – unsolicited notification from the responder: *"Something
  happened."*
- **RSP** – the requester's reply to an `IND`.

Adapter type `EVENT_HS` (location:
`.lib/adapter-3.0.0/typelib/types/bidirectional/Handshake/EVENT_HS.adp`),
minimal/canonical form with no payload:

```
EVENT_HS
  Event inputs:   CNF, IND
  Event outputs:  REQ, RSP
```

## Socket vs. plug

As with every IEC 61499 adapter (verified against real 4diac
behavior): **plug** keeps the declared direction, **socket** mirrors
it. This makes the **requester the plug** (`REQ`/`RSP` fireable,
`CNF`/`IND` queryable) and the **responder the socket** (`CNF`/`IND`
fireable, `REQ`/`RSP` queryable) — the more natural reading direction
(requester left/initiating, responder right/responding).

**Important pitfall:** 4diac's XSD/ECC validation only checks whether
`HS.<Name>` is declared on the adapter at all — not whether the
direction makes sense on that socket/plug side. A block with the
direction swapped compiles cleanly anyway; you have to get the logic
right yourself.

## Blocks: `HandshakeRequester` / `HandshakeResponder`

Two generic demo blocks decoupled from the cylinder example (Basic
FBs):

- **`HandshakeRequester`** — uses `EVENT_HS` as a plug. On `START` it
  sends a `REQ`, reports `DONE` on `CNF`, responds to `IND` with `RSP`
  and reports `NOTIFIED`.
- **`HandshakeResponder`** — uses `EVENT_HS` as a socket. Answers an
  incoming `REQ` with `CNF`, sends an unsolicited `IND` on `TRIGGER`,
  accepts the matching `RSP`.

**Important pitfall (INIT sequence):** INIT handling must not be built
as an entry action of the idle state — otherwise `INITO` (and a reset
of the counters) fires again on every return to the idle state, not
just on real initialization. The correct pattern is a dedicated `Init`
state, reachable only via a qualifier-guarded transition, followed by
an unconditional transition into a separate `Initialized` idle state.

## Demo: `HandshakePatternDemo`

Couples both blocks via a single `AdapterConnections` connection
(requester=plug as source, responder=socket as destination), with an
init chain and test triggers/counters passed through to the subapp
interface.

## Data-carrying variant: `EVENT_HS_WSTRING`

Corresponds 1:1 to the slide's generic "service" adapter (event inputs
`REQ`/`RSP`, event outputs `CNF`/`IND`, plus `REQD`/`RSPD` as WSTRING
inputs and `CNFD`/`INDD` as WSTRING outputs). Matches the text-based
message style from the slide's message-sequence examples (e.g.
`"push,100"`). The blocks `HandshakeRequesterWSTRING`/
`HandshakeResponderWSTRING` and the `HandshakePatternDemoWSTRING` demo
follow the same Init/Initialized/DeInit pattern as the base variant.

## Reduced variants

Four additional adapter types deliberately reduce the full four-event
vocabulary: **`EVENT_HS_UNI`** (`REQ` only, not a real handshake — pure
fire-and-forget), **`EVENT_HS_UNI_WSTRING`** (like UNI, plus payload),
**`EVENT_HS_ACK`** (`REQ`/`CNF`, a real but one-sided handshake, no
`IND`/`RSP` needed), **`EVENT_HS_ACK_WSTRING`** (like ACK, plus
payload). All follow the same socket/plug role scheme.

## Extended example: `MessageExchangeDemo`

A complete implementation of an SoA example (slide 47) with four
cooperating blocks: `WorkpieceSensor` (combines sensor and orchestrator
trigger), `CylinderOrchestrator` (socket to the sensor, two plugs to
the cylinder service and drop-sink service — waits for the drop
confirmation before letting the cylinder retract), `CylinderService`
(simulated cylinder movement with start/end position events),
`DropSinkService` (unconditionally confirms every request). Shows all
three adapter-reduction levels of the `EVENT_HS` family working
together: full `EVENT_HS_WSTRING` where a real intermediate
notification is needed, reduced `EVENT_HS_ACK_WSTRING` where only
request+confirmation are needed.

## Summary

The handshake mechanism (`EVENT_HS` and its variants) is implemented
generically, independent of any concrete use case, and is reused
elsewhere in this collection: the
[TokenRing example](TokenRingPattern.md), in its second occurrence (SoA
example), shows the same service adapter alongside a TokenRing adapter
in the same block. Not yet tested in 4diac.

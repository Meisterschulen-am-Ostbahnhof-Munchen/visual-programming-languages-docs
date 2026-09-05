# 🧩 Design Patterns (IEC 61499)

This collection documents eight reusable design patterns for IEC 61499
applications, based on the UAO *"IEC 61499: primer course"*, Module 6 –
*Design methods and patterns*, by Valeriy Vyatkin (Luleå University of
Technology / Aalto University). Each pattern solves one concrete
modelling problem (spaghetti connections, bloated BOOL data paths,
start/stop logic hard-wired into control logic, …) with a small,
self-contained block or adapter type, instead of re-wiring the same
solution from scratch in every project.

All eight patterns are already implemented in this project as working
blocks and demo subapplications (source: `test_AX/Meins/DesingPatterns/`
in the 4diac workspace), but none has been built/tested in the 4diac
IDE yet — noted individually per pattern below.

## Overview

| Category | Pattern | Course slide |
|---|---|---|
| Structural | [Purely Event-Driven Function Blocks](PurelyEventDrivenPattern.md) | Slide 64 |
| Structural | [Chain of Actions (incl. Generic Actuation)](ChainOfActionsPattern.md) | Slides 65–67 |
| Structural | [Decorator](DecoratorPattern.md) | Slide 68 |
| Architectural | [IO Abstraction Layer](IOAbstractionPattern.md) | Slide 63 |
| Compositional / Architectural | [Start/Stop Pattern](StartStopPattern.md) | Slide 70 |
| Compositional / Architectural | [Reset Pattern](ResetPattern.md) | Slide 71 |
| Behavioural | [Handshake Pattern](HandshakePattern.md) | Slides 41–48, 69, 72 |
| *(not in the slide taxonomy, separately sourced)* | [TokenRing / Mutual Exclusion](TokenRingPattern.md) | Slide 15 |

Several patterns build on each other: `TrueUntil` (Chain of Actions) is
reused unchanged by the Decorator, Start/Stop, and Reset patterns;
`EventDrivenCylinder` (Purely Event-Driven) is the application-layer
component of the IO Abstraction Layer pattern; the Handshake pattern
also supplies the generic service adapter that accompanies the
TokenRing example in its second occurrence (SoA example, slide 47).

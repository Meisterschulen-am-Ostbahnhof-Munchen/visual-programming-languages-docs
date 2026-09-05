# 🧩 Design Patterns (IEC 61499)

Diese Sammlung dokumentiert acht wiederverwendbare Entwurfsmuster für
IEC-61499-Anwendungen, angelehnt an UAO *"IEC 61499: primer course"*,
Modul 6 – *Design methods and patterns*, Valeriy Vyatkin (Luleå
University of Technology / Aalto University). Jedes Muster löst ein
konkretes Modellierungsproblem (Spaghetti-Verbindungen, aufgeblähte
BOOL-Datenpfade, hart verdrahtete Start/Stopp-Logik, …) mit einem
kleinen, eigenständigen Baustein oder Adaptertyp, statt die Lösung
jedes Mal neu und projektspezifisch zu verdrahten.

Alle acht Muster sind in diesem Projekt bereits als lauffähige
Bausteine und Demo-Subapplications umgesetzt (Quelle:
`test_AX/Meins/DesingPatterns/` im 4diac-Workspace), aber noch nicht in
der 4diac IDE gebaut/getestet – das steht bei jedem Muster einzeln.

## Übersicht

| Kategorie | Muster | Kursfolie |
|---|---|---|
| Structural | [Purely Event-Driven Function Blocks](PurelyEventDrivenPattern.md) | Folie 64 |
| Structural | [Chain of Actions (inkl. Generic Actuation)](ChainOfActionsPattern.md) | Folien 65–67 |
| Structural | [Decorator](DecoratorPattern.md) | Folie 68 |
| Architectural | [IO Abstraction Layer](IOAbstractionPattern.md) | Folie 63 |
| Compositional / Architectural | [Start/Stop Pattern](StartStopPattern.md) | Folie 70 |
| Compositional / Architectural | [Reset Pattern](ResetPattern.md) | Folie 71 |
| Behavioural | [Handshake Pattern](HandshakePattern.md) | Folien 41–48, 69, 72 |
| *(nicht in der Folien-Taxonomie, separat vorgeschlagen)* | [TokenRing / Mutual Exclusion](TokenRingPattern.md) | Folie 15 |

Mehrere Muster bauen aufeinander auf: `TrueUntil` (Chain of Actions)
wird vom Decorator-, Start/Stop- und Reset-Pattern unverändert
wiederverwendet; `EventDrivenCylinder` (Purely Event-Driven) ist die
Application-Layer-Komponente des IO-Abstraction-Layer-Patterns; das
Handshake-Pattern liefert außerdem den generischen Service-Adapter, den
auch das TokenRing-Beispiel in seiner zweiten Fundstelle (SoA-Beispiel,
Folie 47) begleitet.

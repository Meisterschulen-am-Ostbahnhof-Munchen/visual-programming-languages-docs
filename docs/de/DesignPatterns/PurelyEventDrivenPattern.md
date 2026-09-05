# Design Pattern: Purely Event-Driven Function Blocks

![EventDrivenCylinder](./EventDrivenCylinder.svg)

* * * * * * * * * *

## Einleitung

Ein einfacher Steuerautomat wird oft so modelliert: Sensoren (z. B.
`atHome`, `atEnd`) als **BOOL-Dateneingänge**, die in
Transitionsbedingungen abgefragt werden (`REQ AND atHome`), und
Aktuatorausgänge (`extend`, `retract`) als **BOOL-Datenausgänge**, die
per Ein-Zeilen-ST-Algorithmus gesetzt werden. Das bläht das Modell auf
zwei Arten auf: Jeder BOOL-Ausgang braucht einen eigenen (trivialen)
Algorithmus, und jede BOOL-Datenverbindung ist ein zusätzliches
Element, das die formale Verifikation (Zustandsraum, Modellprüfung)
verlangsamt.

Die Lösung: Sensor- und Aktuatorsignale werden konsequent als
**Events** statt als BOOL-Daten modelliert. Statt eines kontinuierlich
verfügbaren `atHome`-BOOL, das man in einer Transitionsbedingung
abfragt, feuert ein `AT_HOME`-Event genau einmal, wenn der Sensor
auslöst. Statt eines BOOL-Ausgangs `extend`, der einen Algorithmus
braucht, löst ein `EXTEND`-Event direkt das Ausfahren aus – keine
Zuweisung, kein Algorithmus nötig, die ECC routet das Event einfach
direkt weiter. Ergebnis: Transitionsbedingungen werden zu reinen
Event-Namen, und die ECC braucht keine Algorithmen mehr, nur noch
Event-Verdrahtung.

## Bezug zur Kursfolie

Folie 64 – *"Purely Event-Driven function blocks"* (Kategorie:
Structural). Transformiert das Folienbeispiel `DoubleActingCylinder`
(Eventeingänge `INIT`/`REQ`/`EXTEND`/`RETRACT`, BOOL-Eingänge
`atHome`/`atEnd`, BOOL-Ausgänge `extend`/`retract`) vollständig in die
event-getriebene Endfassung – ohne einen von der Folie gezeigten
Zwischenschritt, in dem nur die Ausgänge eventifiziert sind.

## Baustein: `EventDrivenCylinder`

Basic FB, **keine BOOL-Datenpins**, nur Events – kein Adapter nötig:

- **Eventeingänge:** `START` (Initialisieren), `EXTEND_REQ` /
  `RETRACT_REQ` (Bewegung anfordern), `AT_HOME` / `AT_END`
  (Positionssensoren)
- **Eventausgänge:** `INITO`, `EXTEND` / `RETRACT` (Aktuatorbefehle),
  `STOP` (feuert am Ende jeder Bewegung, vor `CNF`), `CNF`
  (Abschlussquittung)

Die genaue ECC-Verdrahtung ist eine eigene, in sich schlüssige
Ableitung (HOME/Extended als stabile Ruhezustände, `EXTEND_REQ`/
`RETRACT_REQ` als Auslöser, `AT_END`/`AT_HOME` als
Abschlussbedingung), da die Interface-Namen zwar direkt von der Folie
ablesbar sind, die Transitionsverdrahtung im komprimierten
ECC-Diagramm der Folie aber nicht immer eindeutig ist.

Kein separates Demo-Subapp nötig: Der Baustein ist wegen der
fehlenden Datenpins direkt im FORTE-Monitoring testbar (Events manuell
auf der Instanz feuern), ohne dass man BOOL-Werte simulieren müsste –
das ist gerade der Vorteil, den das Pattern demonstrieren soll.

## Offener Punkt

Die genaue ECC-Verdrahtung ist eine plausible, in sich konsistente
Rekonstruktion, aber nicht pixelgenau gegen die Folie verifizierbar –
siehe oben. Noch nicht in 4diac getestet.

## Zusammenfassung

`EventDrivenCylinder` zeigt, wie ein klassischer BOOL-datenlastiger
Steuerautomat vollständig auf Events umgestellt wird: keine
Datenverbindungen, keine Algorithmen, nur Event-Routing in der ECC.
Dient als Application-Layer-Baustein für das
[IO-Abstraction-Layer-Pattern](IOAbstractionPattern.md).

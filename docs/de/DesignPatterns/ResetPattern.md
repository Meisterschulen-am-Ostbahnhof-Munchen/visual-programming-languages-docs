# Design Pattern: Reset

![ResetDemo](./ResetDemo.svg)

* * * * * * * * * *

## Einleitung

Eine Anlage braucht neben der normalen, ggf. per Start/Stop gegateten
Betriebslogik einen **Reset-/Homing-Pfad**, der die Anlage in einen
sicheren/definierten Ausgangszustand zurückfährt. Würde dieser
Reset-Pfad genau wie die normale Betriebslogik durch dasselbe
Start/Stop-`E_PERMIT`-Gate laufen (siehe
[Start/Stop-Pattern](StartStopPattern.md)), könnte man die Anlage nicht
zurücksetzen, während sie gestoppt ist – gerade dann ist Reset aber oft
am wichtigsten (z. B. nach einem Not-Stopp, vor dem nächsten Start).

## Bezug zur Kursfolie

Folie 71 – *"The reset pattern"* (Kategorie: Compositional /
Architectural). Zeigt dieselbe Cylinder-Beispielgrafik wie
Handshake-/Start-Stop-Pattern, mit einem eigenen `CylinderReset`-Zweig,
der direkt von einem externen `RESET`-Event getriggert wird –
**nicht** über das `E_PERMIT`-Gate aus dem Start/Stop-Pattern.

## Lösung: architektonisch getrennter Reset-Pfad

Der Reset-Pfad wird **architektonisch getrennt** von der normalen
Betriebslogik geführt – eigener, direkter Trigger-Eingang (`RESET`),
der **nicht** durch das `E_PERMIT`-Gate läuft, sondern die zuständige
Aktion unmittelbar und bedingungslos auslöst.

## Demo: `ResetDemo`

**Keine neuen Bausteine** – Wiederverwendung von
[`TrueUntil`](ChainOfActionsPattern.md) für den Reset-Baustein selbst,
kein Gate davor. Kombiniert das Start/Stop-Muster (`START`/`STOP` →
`E_SR` → `E_PERMIT` → `Worker.TRIGGER`, wie in `StartStopDemo`) mit
einem **separaten, ungegateten** `RESET` → `ResetWorker.TRIGGER`-Pfad,
um den architektonischen Kernpunkt zu zeigen: Reset funktioniert auch,
wenn die Anlage gestoppt ist (`E_SR.Q=FALSE`), der normale `TRIGGER`
dagegen nicht.

## Zusammenfassung

Reset zeigt, dass nicht jeder Signalpfad durch dasselbe Gate laufen
darf – ein Sicherheits-/Homing-Pfad muss unabhängig von der
Start/Stop-Freigabe funktionieren. Baut auf
[Start/Stop](StartStopPattern.md) und
[Chain of Actions](ChainOfActionsPattern.md) auf, ohne einen einzigen
neuen Baustein zu benötigen. Noch nicht in 4diac getestet.

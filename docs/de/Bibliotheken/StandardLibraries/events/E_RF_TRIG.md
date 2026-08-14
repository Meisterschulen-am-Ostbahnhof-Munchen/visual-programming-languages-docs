# E_RF_TRIG

* * * * * * * * * *
## Einleitung

Der `E_RF_TRIG` (Rising/Falling Trigger) erkennt sowohl steigende als auch fallende Flanken eines `BOOL`-Werts und meldet sie über zwei getrennte Ausgangsereignisse. Er kombiniert die Funktionalität von `E_R_TRIG` (steigende Flanke) und `E_F_TRIG` (fallende Flanke) in einem einzigen Baustein.

![E_RF_TRIG](E_RF_TRIG.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **EI**: Prüft `QI` auf eine steigende oder fallende Flanke.
    - **Verbundene Daten**: `QI`

### **Ereignis-Ausgänge**

- **ER**: Bestätigt eine erkannte steigende Flanke (`QI` von `FALSE` nach `TRUE`).
- **EF**: Bestätigt eine erkannte fallende Flanke (`QI` von `TRUE` nach `FALSE`).

### **Daten-Eingänge**

- **QI** (BOOL): Der auf Flankenwechsel zu prüfende Wert.

## Funktionsweise

Intern speichert ein `E_D_FF` den zuletzt bekannten Wert von `QI` und liefert bei jedem `EI`-Ereignis über sein `EO` den neuen Wert an einen `E_SWITCH`. Dieser leitet das Ereignis abhängig vom aktuellen `Q`-Wert (`G`-Eingang) entweder an `EO1` (→ `ER`, steigende Flanke) oder `EO0` (→ `EF`, fallende Flanke) weiter. Da `E_D_FF` `EO` nur bei tatsächlicher Änderung von `Q` auslöst, wird bei unverändertem `QI` weder `ER` noch `EF` ausgelöst.

## Technische Besonderheiten

- **Zusammengesetzt aus zwei Standardbausteinen**: `E_D_FF` (Änderungserkennung) + `E_SWITCH` (Verzweigung nach Wert), keine eigene ECC.
- **Nur bei tatsächlicher Änderung**: Wiederholte `EI`-Ereignisse mit unverändertem `QI` erzeugen kein Ausgangsereignis, da `E_D_FF` intern bereits filtert.
- **Basis für [E_TLIM](timers/E_TLIM.md)**: Dort wird `E_RF_TRIG` zur Erkennung von Beginn (`ER`) und Ende (`EF`) eines `TRUE`-Zustands verwendet.

## Zustandsübersicht

Zustandslose Verdrahtungslogik: Der einzige gespeicherte Zustand ist der zuletzt bekannte `QI`-Wert im internen `E_D_FF`.

## Anwendungsszenarien

- **Flankenerkennung ohne zwei getrennte Bausteine**: Überall dort, wo sowohl der Beginn als auch das Ende eines `TRUE`-Zustands erkannt werden muss (z. B. Start und Ende eines Signals), spart `E_RF_TRIG` einen zweiten Baustein gegenüber der getrennten Verwendung von `E_R_TRIG`/`E_F_TRIG`.
- **Zeitmessung von Zuständen**: In Kombination mit `E_DELAY`/`E_SR` (siehe [E_TLIM](timers/E_TLIM.md)) zur Messung, wie lange ein `BOOL`-Signal in einem Zustand verharrt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_R_TRIG`**: erkennt nur steigende Flanken.
- **`E_F_TRIG`**: erkennt nur fallende Flanken.
- **[E_TLIM](timers/E_TLIM.md)**: verwendet `E_RF_TRIG` intern zur Zeitbegrenzung eines `TRUE`-Zustands.

## Fazit

`E_RF_TRIG` liefert kompakte, kombinierte Flankenerkennung für steigende und fallende Übergänge eines `BOOL`-Signals und ist Baustein für komplexere Zeit- und Zustandslogik wie `E_TLIM`.

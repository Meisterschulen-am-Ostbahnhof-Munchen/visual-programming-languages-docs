# F_MUX_5

![F_MUX_5](F_MUX_5.svg)

* * * * * * * * * *

## Einleitung

Der `F_MUX_5` ist die generische 5-Eingangs-Variante des Standard-Multiplexer-Bausteins `F_MUX` (vgl. `F_MUX_2`/`F_MUX_3`/`F_MUX_4`). Er wählt anhand des Selektors `K` einen von 5 Eingangswerten (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`) aus und gibt ihn über `OUT` aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Auswahl aus, trägt `K` und `IN1`, `IN2`, `IN3`, `IN4`, `IN5`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **K** (ANY_INT): Wählt einen der 5 Eingänge aus (`0`-basiert).
- `IN1`, `IN2`, `IN3`, `IN4`, `IN5` (ANY): Die 5 zur Auswahl stehenden Eingangswerte.

### **Daten-Ausgänge**

- **OUT** (ANY): Der ausgewählte Eingangswert: `IN1` bei `K = 0`, `IN2` bei `K = 1`, `IN3` bei `K = 2`, `IN4` bei `K = 3`, `IN5` bei `K = 4`.

## Funktionsweise

Bei Eintreffen von `REQ` wird abhängig vom Wert von `K` der entsprechende Eingang (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`) auf `OUT` durchgeschaltet: `IN1` bei `K = 0`, `IN2` bei `K = 1`, `IN3` bei `K = 2`, `IN4` bei `K = 3`, `IN5` bei `K = 4`. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_F_MUX'`, dieselbe C++-Basis wie `F_MUX_2`/`F_MUX_3`/`F_MUX_4`; nur die Anzahl der Eingänge unterscheidet sich pro Instanziierung.
- **`ANY`-Datentyp**: Sowohl die Eingänge `IN1`…`IN5` als auch `OUT` sind generisch typisiert und passen sich beim Verdrahten an den angeschlossenen Datentyp an.
- **`0`-basierter Selektor**: `K = 0` wählt `IN1`, `K = 4` wählt `IN5`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Auswahl und zu `CNF`.

## Anwendungsszenarien

- **Mehrfachauswahl mit mehr als 4 Quellen**: Überall dort, wo zwischen mehr als den von `F_MUX_4` unterstützten 4 Eingängen ausgewählt werden muss, ohne mehrere `F_MUX`-Bausteine zu kaskadieren.
- **Signalumschaltung**: Auswahl eines von mehreren Sensor- oder Quellsignalen anhand eines Steuerwerts `K`.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`F_MUX_4`**: dieselbe generische Implementierung mit 4 statt 5 Eingängen.
- **`F_SEL`**: die binäre Auswahl zwischen genau zwei Werten anhand eines `BOOL`-Selektors, funktional ein Spezialfall von `F_MUX_2`.

## Fazit

`F_MUX_5` erweitert das Multiplexer-Prinzip von `F_MUX_2`/`F_MUX_3`/`F_MUX_4` auf 5 wählbare Eingänge und ist die generische, für 5 Eingänge instanziierte Variante derselben zugrunde liegenden Implementierung.

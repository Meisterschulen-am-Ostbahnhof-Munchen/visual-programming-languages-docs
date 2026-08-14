# F_MUX_7

![F_MUX_7](F_MUX_7.svg)

* * * * * * * * * *
## Einleitung

Der `F_MUX_7` ist die generische 7-Eingangs-Variante des Standard-Multiplexer-Bausteins `F_MUX` (vgl. `F_MUX_2`/`F_MUX_3`/`F_MUX_4`). Er wählt anhand des Selektors `K` einen von 7 Eingangswerten (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`) aus und gibt ihn über `OUT` aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Auswahl aus, trägt `K` und `IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **K** (ANY_INT): Wählt einen der 7 Eingänge aus (`0`-basiert).
- `IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7` (ANY): Die 7 zur Auswahl stehenden Eingangswerte.

### **Daten-Ausgänge**

- **OUT** (ANY): Der ausgewählte Eingangswert: `IN1` bei `K = 0`, `IN2` bei `K = 1`, `IN3` bei `K = 2`, `IN4` bei `K = 3`, `IN5` bei `K = 4`, `IN6` bei `K = 5`, `IN7` bei `K = 6`.

## Funktionsweise

Bei Eintreffen von `REQ` wird abhängig vom Wert von `K` der entsprechende Eingang (`IN1`, `IN2`, `IN3`, `IN4`, `IN5`, `IN6`, `IN7`) auf `OUT` durchgeschaltet: `IN1` bei `K = 0`, `IN2` bei `K = 1`, `IN3` bei `K = 2`, `IN4` bei `K = 3`, `IN5` bei `K = 4`, `IN6` bei `K = 5`, `IN7` bei `K = 6`. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_F_MUX'`, dieselbe C++-Basis wie `F_MUX_2`/`F_MUX_3`/`F_MUX_4`; nur die Anzahl der Eingänge unterscheidet sich pro Instanziierung.
- **`ANY`-Datentyp**: Sowohl die Eingänge `IN1`…`IN7` als auch `OUT` sind generisch typisiert und passen sich beim Verdrahten an den angeschlossenen Datentyp an.
- **`0`-basierter Selektor**: `K = 0` wählt `IN1`, `K = 6` wählt `IN7`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Auswahl und zu `CNF`.

## Anwendungsszenarien

- **Mehrfachauswahl mit mehr als 4 Quellen**: Überall dort, wo zwischen mehr als den von `F_MUX_4` unterstützten 4 Eingängen ausgewählt werden muss, ohne mehrere `F_MUX`-Bausteine zu kaskadieren.
- **Signalumschaltung**: Auswahl eines von mehreren Sensor- oder Quellsignalen anhand eines Steuerwerts `K`.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`F_MUX_6`**: dieselbe generische Implementierung mit 6 statt 7 Eingängen.
- **`F_SEL`**: die binäre Auswahl zwischen genau zwei Werten anhand eines `BOOL`-Selektors, funktional ein Spezialfall von `F_MUX_2`.

## Fazit

`F_MUX_7` erweitert das Multiplexer-Prinzip von `F_MUX_2`/`F_MUX_3`/`F_MUX_4` auf 7 wählbare Eingänge und ist die generische, für 7 Eingänge instanziierte Variante derselben zugrunde liegenden Implementierung.

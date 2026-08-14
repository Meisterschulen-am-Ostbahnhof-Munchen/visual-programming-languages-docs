# F_ATAN2

![F_ATAN2](F_ATAN2.svg)

* * * * * * * * * *
## Einleitung

Der `F_ATAN2` berechnet den Hauptwert des Arkustangens von `Y/X` unter Berücksichtigung der Vorzeichen beider Argumente (Zwei-Parameter-Arkustangens). Im Gegensatz zur einfachen `ATAN`-Funktion (die nur ein Argument entgegennimmt) liefert `F_ATAN2` den Winkel im korrekten Quadranten über den vollen Winkelbereich von `-π` bis `+π`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Berechnung aus, trägt `Y` und `X`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **Y** (ANY_REAL): Ordinate (Y-Koordinate).
- **X** (ANY_REAL): Abszisse (X-Koordinate).

### **Daten-Ausgänge**

- **OUT** (ANY_REAL): Der berechnete Winkel in Radiant, im Bereich `(-π, π]`.

## Funktionsweise

Bei Eintreffen von `REQ` berechnet der Baustein den Winkel zwischen der positiven X-Achse und dem Punkt `(X, Y)` — äquivalent zu `ATAN(Y/X)`, jedoch unter Auswertung der Vorzeichen von `X` und `Y` einzeln, um den korrekten Quadranten zu bestimmen (inklusive der Sonderfälle `X = 0`). Das Ergebnis wird über `OUT` ausgegeben, anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **Quadrantenkorrektheit**: Im Gegensatz zu `ATAN(Y/X)` liefert `F_ATAN2` auch bei negativem `X` (2. und 3. Quadrant) den korrekten Winkel, ohne dass der Aufrufer den Quadranten manuell nachkorrigieren muss.
- **`ANY_REAL`-Typisierung**: Akzeptiert sowohl `REAL` als auch `LREAL` für `Y`, `X` und `OUT`.
- **Sonderfall `X = 0`**: Liefert `+π/2` bzw. `-π/2` je nach Vorzeichen von `Y`, statt einer Division-durch-Null wie bei direkter Verwendung von `ATAN(Y/X)`.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Berechnung und zu `CNF`.

## Anwendungsszenarien

- **Winkelberechnung aus kartesischen Koordinaten**: z. B. Ermittlung der Blickrichtung oder Ausrichtung eines Objekts aus dessen X/Y-Position relativ zu einem Referenzpunkt.
- **Regelungstechnik**: Berechnung von Phasenwinkeln oder Lenkwinkeln aus zwei Komponentensignalen.
- **Navigation**: Kursberechnung aus Geschwindigkeitskomponenten.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`F_ATAN`**: berechnet den Arkustangens eines einzelnen Werts, liefert nur Winkel im Bereich `(-π/2, π/2)` und benötigt eine manuelle Quadrantenkorrektur.

## Fazit

`F_ATAN2` liefert eine quadrantenkorrekte Winkelberechnung aus zwei kartesischen Komponenten und ist der Standardbaustein für Winkel-/Richtungsberechnungen, bei denen `ATAN` allein nicht ausreicht.

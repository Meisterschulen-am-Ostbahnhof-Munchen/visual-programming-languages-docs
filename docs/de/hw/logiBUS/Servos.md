# Servos

Diese Seite beschreibt, wie Modellbau-Servos an einen logiBUS-Ausgang angeschlossen werden und welche Werte für `FREQ`, `PULSE_MIN` und `PULSE_MAX` des Bausteins [logiBUS_QW_SERVO](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/Bibliotheken/ExternalLibraries/logiBUS/io/DO-Servo/logiBUS_QW_SERVO/) passen.

!!! note "Herkunft der Angaben"
    Die Herstellerangaben stammen aus der Produktbeschreibung. Die Werte für den 9-g-Servo hat Franz am Aufbau getestet (Servo fährt 90° in jede Richtung). Die Impulsbreiten des Treibers hat Franz am Oszilloskop gemessen (2026-11-06). Ich habe nichts davon selbst geprüft.

## 9-g-Servo, 180°

Servo „5 Stück 9G Servo Motor, Mikro-Servomotoren mit Kabel, 180 Grad Hochleistungs-Servos“ (Amazon B0H3BC3PSS).

| Angabe | Wert |
|---|---|
| Zyklus | 20 ms (50 Hz) |
| Impulsbreite | 0,5 bis 2,5 ms für 0 bis 180° |
| Betriebsspannung | 3 bis 7,2 V |

Passende Werte für den Baustein:

| Parameter | Wert |
|---|---|
| `FREQ` | `50` |
| `PULSE_MIN` | `T#500us` |
| `PULSE_MAX` | `T#2500us` |

Die Mitte liegt bei 1,5 ms. Mit diesen Werten fährt der Servo exakt 90° in jede Richtung. Mit den Initialwerten des Bausteins (`T#1000us` bis `T#2000us`) sind es nur etwa ±35°.

## Empfehlung für Übungen am Trainer

!!! warning "Keine geprüften Werte"
    Diese Liste ist eine Empfehlung aus allgemeinem Wissen (Claude), keine Messung und kein Datenblatt. Drehmoment, Pulsbereich und Strom sind nicht nachgeschlagen. Nur der 9-g-Servo oben (B0H3BC3PSS) ist mit 500/2500 µs bei 50 Hz auf der Hardware getestet.

| Einsatz | Empfehlung | Warum |
|---|---|---|
| Standard für die Übungen | MG90S (9 g, Metallgetriebe) | Gleiche Größe und gleicher Anschluss wie die 9-g-Servos, aber mit Metallgetriebe. Hält Anfahren gegen den Anschlag und Herumdrehen von Hand besser aus als die Kunststoffgetriebe der SG90-Klone. |
| Wenn es billig sein soll | SG90 (Tower Pro original) | Für reines Zeigen in Ordnung. Die Klone streuen stark in Winkel und Mitte, das Getriebe bricht leicht. |
| Wenn sichtbar etwas bewegt werden soll | Hitec HS-311 oder HS-422 (Standardgröße, analog) | Robust, verlässliche Kennlinie, gut dokumentiert. Laufen laut allgemeinem Wissen an 4,8 bis 6 V. |
| Mit mehr Kraft | MG996R (Standardgröße, Metall) | Viel Kraft. Zieht aber im Anlauf und blockiert über 1 A, braucht also eine kräftige 5-V-Versorgung. Die Klone sind ungenau. |
| Wenn Präzision zählt | Digitalservo, zum Beispiel Feetech oder Savöx in Standardgröße | Hält die Position steifer, kein Zittern. Manche vertragen auch höhere Frequenzen als 50 Hz, das kann der Baustein über `FREQ`. |

Allgemeine Hinweise:

- **Versorgung:** Servos nie aus dem 3,3-V-Regler des ESP speisen, sondern aus einer eigenen 5-V-Quelle mit genug Strom. Pro 9-g-Servo etwa 0,5 bis 1 A Spitze einplanen, für Standardgröße mehr (Richtwert, nicht gemessen). Gemeinsame Masse mit dem Board.
- **Signal:** 3,3 V vom ESP reichen den meisten Servos. Das Signal vor der Leistungsstufe abgreifen.
- **Pulsbreite:** Die Werte unterscheiden sich je nach Modell. `PULSE_MIN` und `PULSE_MAX` pro Servo einstellen, am besten mit dem Oszilloskop und vorsichtig bis kurz vor den mechanischen Anschlag, symmetrisch um 1,5 ms.

## Anschluss

- **Versorgung:** aus einer eigenen 5-V-Quelle, nicht aus dem 3,3-V-Regler des ESP.
- **Masse:** gemeinsame Masse von Servo-Versorgung und logiBUS-Board.
- **Signal:** Der Servo braucht ein Logikpegel-Signal. Auf Boards mit Leistungsstufe wird das Signal **vor** der Leistungsstufe abgegriffen, nicht am Leistungsausgang (siehe [Leistungsstufen der Ausgänge](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/hw/logiBUS/Leistungsstufen/)).

## Hinweis zum mechanischen Anschlag

Fährt ein Servo mit zu großer Spanne gegen den mechanischen Anschlag, brummt er und wird warm. Dann `PULSE_MIN` und `PULSE_MAX` symmetrisch um 1,5 ms zurücknehmen.

## Weitere Servos

Weitere Servotypen mit ihren Werten (zum Beispiel Autoservos mit 250 Hz) stehen in der Tabelle auf der Seite des Bausteins [logiBUS_QW_SERVO](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/Bibliotheken/ExternalLibraries/logiBUS/io/DO-Servo/logiBUS_QW_SERVO/).

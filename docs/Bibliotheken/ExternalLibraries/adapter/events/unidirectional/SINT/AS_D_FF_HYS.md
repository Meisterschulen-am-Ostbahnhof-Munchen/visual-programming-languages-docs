# AS_D_FF_HYS


![AS_D_FF_HYS](./AS_D_FF_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_D_FF_HYS** realisiert ein datengetaktetes Flip-Flop (D-Latch) mit einer **Hysterese** (Schalthysterese). Der Baustein wird typischerweise in der Signalverarbeitung eingesetzt, um verrauschte oder schwankende Eingangssignale zu glätten und definierte Schaltpunkte zu erzeugen. Er verfügt über einen Ereigniseingang `INIT`, um den Hysterese-Wert zu setzen, sowie über zwei Adapter-Schnittstellen: einen Eingangs-Adapter `I` für das zu latchnde Signal und einen Ausgangs-Adapter `Q` für das gelatchte und mit Hysterese gefilterte Ausgangssignal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Typ    | Kommentar           | Mit Daten |
|--------|--------|---------------------|-----------|
| `INIT` | EInit  | Setzt den Hysterese-Wert | `HYSTERESIS` |

### **Ereignis-Ausgänge**

| Name    | Typ    | Kommentar            |
|---------|--------|----------------------|
| `INITO` | EInit  | Bestätigung der INIT-Verarbeitung |

### **Daten-Eingänge**

| Name         | Typ  | Kommentar                     |
|--------------|------|-------------------------------|
| `HYSTERESIS` | SINT | Hysterese-Bandbreite (ganzzahliger Wert) |

### **Daten-Ausgänge**

Keine direkten Datenausgänge – der Ausgangswert wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ                                     | Kommentar                          |
|----------|------|-----------------------------------------|------------------------------------|
| Socket   | `I`  | `adapter::types::unidirectional::AS`    | Eingangssignal (Wert und Takt)     |
| Plug     | `Q`  | `adapter::types::unidirectional::AS`    | Ausgangssignal (gelatcht mit Hysterese) |

Die Adapter vom Typ `AS` (unidirectional) besitzen typischerweise einen Ereignis-Port `E1` und einen Daten-Port `D1`. Der Socket `I` liefert über `I.E1` das Taktsignal und über `I.D1` den Datenwert, der gelatcht werden soll. Der Plug `Q` gibt über `Q.E1` ein Ereignis und über `Q.D1` den gefilterten Ausgangswert aus.

## Funktionsweise

Der FB empfängt über den Adapter `I` ein Taktsignal (Ereignis `I.E1`) und einen Datenwert (`I.D1`). Bei jedem Takt wird der aktuelle Datenwert mit dem zuletzt ausgegebenen Wert verglichen, unter Berücksichtigung des Hysterese-Bandes. Der Ausgang `Q.D1` ändert sich nur dann, wenn der neue Eingangswert außerhalb des Intervalls `[letzter Ausgangswert - HYSTERESIS , letzter Ausgangswert + HYSTERESIS]` liegt. Dadurch werden kleine Schwankungen (Rauschen) um den eingestellten Arbeitspunkt unterdrückt.

Das Ereignis `INIT` dient zur einmaligen Konfiguration des Hysterese-Werts. Der Hysterese-Wert vom Dateneingang `HYSTERESIS` wird dabei übernommen. Nach erfolgreicher Initialisierung wird das Ereignis `INITO` ausgelöst.

Der FB nutzt intern den Baustein `E_D_FF_ANY_HYS` aus der Bibliothek `logiBUS::signalprocessing::hysteresis`, der die eigentliche Flip-Flop-Logik mit Hysterese implementiert.

## Technische Besonderheiten

- Der Hysterese-Wert ist als `SINT` (signed integer) festgelegt.
- Die eigentliche Signalverarbeitung wird durch einen untergeordneten FB (`E_D_FF_ANY_HYS`) realisiert, der vom Anwender nicht direkt eingesehen wird.
- Die Adapter-Schnittstelle erlaubt eine lose Kopplung des Bausteins an andere Komponenten.
- Das Ereignis `INIT` verarbeitet keinen Wert – die Hystereseparameter können nur vor dem ersten Betrieb gesetzt werden; ein nachträgliches Ändern ist nur durch erneutes Senden von `INIT` möglich.

## Zustandsübersicht

Der FB besitzt **keine explizite Zustandsmaschine**, die nach außen sichtbar ist. Intern wird der aktuelle Ausgangswert gespeichert. Die Hysterese bewirkt ein Zustandsgedächtnis: Der Ausgang springt nicht bei jeder Änderung des Eingangs, sondern nur bei Über- oder Unterschreiten der Hysterese-Schwellen.

## Anwendungsszenarien

- **Entprellung von Schaltkontakten** – Unterdrückung von Prellern und kurzen Störpulsen.
- **Schwellwertschalter mit Hysterese** – z. B. Temperaturregler, die Ein- und Ausschaltpunkte trennen.
- **Signalglättung in der Sensorik** – Verarbeitung verrauschter Analogwerte in diskrete Zustände.
- **Daten-Latch mit Rauschunterdrückung** – für langsame, aber störungsbehaftete Datensignale.

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Eigenschaft                                         | Unterschied zu AS_D_FF_HYS                          |
|-------------------|-----------------------------------------------------|-----------------------------------------------------|
| `E_D_FF`          | Klassisches D-Flip-Flop ohne Hysterese              | Keine Filterung; Ausgang folgt jedem Takt.          |
| `E_D_FF_HYS`      | D-Flip-Flop mit Hysterese (gleiche Logik)           | Kein eigener `INIT`-Eingang; Hysterese wird ggf. über Daten gesetzt. |
| `AS_FF_HYS`       | Flip-Flop mit Hysterese und eigener Adapter-Schnittstelle | Möglicherweise andere Kopplung, ähnliche Funktion. |

## Fazit

Der `AS_D_FF_HYS` kombiniert ein D-Flip-Flop mit einer einstellbaren Hysterese und kapselt die komplexe Logik in einem einfach zu verwendenden Adapter-basierten Baustein. Er eignet sich besonders für Anwendungen, in denen verrauschte diskrete Signale sauber und mit definierten Schaltpunkten verarbeitet werden müssen. Die initiale Konfiguration über `INIT` ermöglicht eine flexible Anpassung an verschiedene Störumgebungen.
# AX_D_FF_TMIN


![AX_D_FF_TMIN](./AX_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_D_FF_TMIN** realisiert ein data-latch D-Flip-Flop, das zusätzlich eine minimale Zeit zwischen aufeinanderfolgenden Ereignisausgängen (z. B. EO) erzwingt. Er dient als modulare Hülle um den IEC‑61499‑Standardbaustein `E_D_FF_TMIN` und verwendet einen unidirektionalen Adapter (`adapter::types::unidirectional::AX`) für die ereignisgesteuerte Datenübergabe. Der Baustein eignet sich besonders für Anwendungen, die eine zuverlässige Datenübernahme mit einstellbarem Mindestabstand zwischen Ausgangsimpulsen erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INIT`   | EInit | Initialisierungsanforderung; legt die minimale Verzögerungszeit fest (Parameter `Tmin`). |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INITO`  | EInit | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `Tmin` | TIME | Minimale Sperrzeit (inter-disposal time) zwischen zwei aufeinanderfolgenden Ereignissen am Ausgang `EO`. Der Wert wird nur bei einem `INIT`-Ereignis übernommen. |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge; der latchende Datenwert wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Rolle | Name | Typ | Beschreibung |
|-------|------|-----|--------------|
| Socket | `I` | adapter::types::unidirectional::AX | Eingangsadapter; liefert das zu latchende Datenwort (`D1`) und das Taktereignis (`E1`). |
| Plug   | `Q` | adapter::types::unidirectional::AX | Ausgangsadapter; stellt das latchende Datenwort (`D1`) und das Ausgangsereignis (`E1`) zur Verfügung. |

Die Adapter `AX` sind unidirektional ausgelegt: Sie übertragen genau ein Ereignis und einen zugehörigen Datenwert.

## Funktionsweise

Der Baustein kapselt den internen Funktionsblock `E_D_FF_TMIN`, der wie folgt arbeitet:

1. **Initialisierung**: Wird ein `INIT`-Ereignis empfangen, wird die aktuelle Zeit `Tmin` als minimale Sperrzeit für den Ausgang `EO` gespeichert. Der Baustein quittiert dies mit `INITO`.

2. **Takten (D‑Flip‑Flop)**:
   - Ein Ereignis am Socket `I.E1` wird als Taktsignal (CLK) an das interne Flip‑Flop weitergeleitet.
   - Gleichzeitig wird der Datenwert `I.D1` als neuer Eingangswert `D` übernommen.
   - Bei jeder steigenden Flanke des Takts (hier: jedes `E1`-Ereignis) wird der aktuelle Datenwert `D` übernommen und am Ausgang `Q` bereitgestellt.
   - Nach der Übernahme wird ein Ausgangsereignis `EO` am Plug `Q.E1` erzeugt – allerdings erst nach Ablauf der minimalen Sperrzeit seit dem letzten `EO`. Dadurch wird sichergestellt, dass Ausgangsimpulse nicht schneller als durch `Tmin` vorgegeben aufeinanderfolgen.

3. **Ausgang**: Der latchende Datenwert erscheint am Plug `Q.D1`, das zugehörige Ereignis am Plug `Q.E1`.

## Technische Besonderheiten

- **Minimale Zwischenzeit**: Der Baustein erzwingt eine einstellbare Mindestzeit (`Tmin`) zwischen zwei Ausgangsereignissen. Überschreitet die Frequenz des Taktsignals diese Zeit, werden einzelne Taktereignisse unterdrückt, sodass der Ausgang eine maximal erlaubte Ereignisfolge nicht überschreitet.
- **Adapter‑Schnittstelle**: Durch die Verwendung des unidirektionalen Adapters `AX` wird eine lose Kopplung zwischen Sender und Empfänger erreicht. Der Adapter transportiert sowohl das Ereignis als auch den Datenwert in einer logischen Einheit.
- **Initialisierungsabhängigkeit**: Die minimale Zeit `Tmin` wird nur einmal beim `INIT` gesetzt und bleibt bis zum nächsten `INIT` konstant. Eine Änderung während des Betriebs ist nicht vorgesehen.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine. Die innere Logik des eingebetteten `E_D_FF_TMIN` kann jedoch folgende Zustände annehmen:

- **Idle**: Warten auf ein `INIT` oder ein Taktereignis.
- **Initialisiert**: `Tmin` wurde übernommen; der Baustein ist betriebsbereit.
- **Sperrzeit aktiv**: Nach einem Ausgangsereignis wird die durch `Tmin` festgelegte Verzögerung durchlaufen; eingehende Taktereignisse werden ignoriert.
- **Bereit**: Nach Ablauf der Sperrzeit kann das nächste Taktereignis ein neues Ausgangsereignis auslösen.

## Anwendungsszenarien

- **Gepufferte Sensorwerte**: Ein Sensor liefert Daten mit unregelmäßiger Rate. Der `AX_D_FF_TMIN` übernimmt den letzten gültigen Wert und gibt ihn an eine nachfolgende Steuerung mit einer maximal zulässigen Ausgabefrequenz weiter.
- **Entprellung von Signalen**: Mechanische Taster oder Schalter erzeugen Prellimpulse. Die minimale Zwischenzeit unterdrückt zu schnelle Zustandswechsel.
- **Datenweiterleitung mit Bandbreitenbegrenzung**: In Kommunikationsnetzen kann der Baustein verwendet werden, um die Ausgaberate eines Datenkanals zu begrenzen, ohne dass der Absender adaptiert werden muss.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|-------------|
| `E_D_FF` (Standard‑D‑Flip‑Flop) | Keine zeitliche Begrenzung der Ausgangsimpulse; Ereignisse werden sofort weitergeleitet. |
| `AX_D_FF_TMIN` (vorliegend) | Fügt die minimale Zwischenzeit `Tmin` zwischen Ausgangsereignissen ein, realisiert über den eingebauten `E_D_FF_TMIN`. |
| `E_CTD` / `E_CTU` (Zähler) | Zählen Ereignisse; bieten keine Datenübernahme oder Latch‑Funktion. |

Der `AX_D_FF_TMIN` vereint die latchende Datenübernahme eines Flip‑Flops mit der zeitlichen Filterung eines Monoflops, ist aber als reiner Ereignis‑Daten‑Adapter ausgeführt.

## Fazit

Der **AX_D_FF_TMIN** ist ein spezialisierter Funktionsblock für Anwendungen, die eine getaktete Datenübernahme mit garantierter Mindestzeit zwischen Ausgabeereignissen benötigen. Die Kapselung des Standardbausteins `E_D_FF_TMIN` und die Adapter‑Schnittstelle erleichtern die Integration in modulare 4diac‑Projekte. Der Baustein bietet eine saubere Trennung von Initialisierung und dynamischem Betrieb und eignet sich insbesondere für zeitkritische, ereignisgesteuerte Systeme.
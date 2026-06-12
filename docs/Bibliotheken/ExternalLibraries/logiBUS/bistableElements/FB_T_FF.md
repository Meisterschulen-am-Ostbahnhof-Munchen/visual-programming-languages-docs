# FB_T_FF

[[Bild des Funktionsbausteins – in der 4diac-IDE als Symbol mit einem Ereigniseingang REQ, Ausgang CNF, Dateneingängen CLK (BOOL) und RST (BOOL) sowie Datenausgang Q (BOOL) dargestellt]]


![FB_T_FF](./FB_T_FF.svg)

* * * * * * * * * *

## Einleitung

Der **FB_T_FF** (Toggle Flip-Flop) realisiert einen flankengesteuerten, asynchron rücksetzbaren Frequenzteiler oder Umschalter. Bei jedem ansteigenden Taktflanke am Eingang **CLK** wird der Ausgang **Q** invertiert (getoggelt). Ein hoher Pegel am **RST**-Eingang setzt **Q** sofort zurück auf `FALSE`. Der Baustein eignet sich insbesondere für binäre Zustandswechsel in Steuerungsabläufen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | assoziierte Daten | Beschreibung                               |
|----------|-------------------|--------------------------------------------|
| `REQ`    | `CLK`, `RST`      | Normaler Ausführungsauftrag; triggert den Algorithmus |

### **Ereignis-Ausgänge**

| Ereignis | assoziierte Daten | Beschreibung                                     |
|----------|-------------------|--------------------------------------------------|
| `CNF`    | `Q`               | Bestätigt die Ausführung, liefert den aktuellen Wert von `Q` |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung                    |
|------|-------|---------------------------------|
| `CLK`| BOOL  | Taktsignal (Flankenauswertung)  |
| `RST`| BOOL  | Asynchroner Reset (aktiv High)  |

### **Daten-Ausgänge**

| Name | Typ   | Beschreibung                               |
|------|-------|--------------------------------------------|
| `Q`  | BOOL  | Ausgang – toggelt bei steigender CLK-Flanke, es sei denn, Reset ist aktiv |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Baustein wird mit dem **REQ**-Ereignis aufgerufen. Bei jedem Aufruf wird die interne Variable **EDGE** (Bool, initial `TRUE`) wie folgt aktualisiert:

1. **Reset-Vorrang:** Ist `RST = TRUE`, wird `Q` sofort auf `FALSE` gesetzt.
2. **Flankendetektion:** Falls `RST` nicht aktiv ist und die Bedingung `CLK AND NOT EDGE` erfüllt ist, liegt eine **steigende Flanke** von `CLK` vor. In diesem Fall wird `Q` invertiert: `Q := NOT Q`.
3. **Speicherung:** Nach der Auswertung wird `EDGE := CLK` gesetzt, damit bei nächsten Aufruf die Flanke erkannt werden kann.

Der Algorithmus wird im internen Zustand **REQ** ausgeführt; nach dem Algorithmus wird das **CNF**-Ereignis gesendet.

## Technische Besonderheiten

- **Flankenerkennung ohne Verzögerung:** Die Erkennung einer steigenden Flanke erfolgt durch den Vergleich des aktuellen `CLK`-Werts mit dem vorherigen (gespeichert in `EDGE`). Dies ist eine typische Software-Realisation eines flankengesteuerten Flipflops.
- **Asynchroner Reset:** Der Reset wirkt sofort bei jedem Aufruf, unabhängig von der Taktflanke.
- **Initialzustand:** `Q` ist nach dem Starten des Bausteins nicht definiert; es wird erst durch den ersten REQ-Aufruf oder einen Reset gesetzt. Die interne **EDGE** ist initial `TRUE`, sodass die erste steigende Flanke (von `FALSE` auf `TRUE`) korrekt erkannt wird.

## Zustandsübersicht

Der Baustein ist als **SimpleFB** mit einem einzigen EC‑Zustand implementiert:

| Zustand | Eingehende Ereignisse | Ausgehende Aktion | Ausgehendes Ereignis |
|---------|-----------------------|-------------------|----------------------|
| `REQ`   | `REQ`                 | Führe Algorithmus `REQ` aus (Toggle/Reset-Logik) | `CNF` |

Der Zustand wird nach Abarbeitung sofort wieder scharf geschaltet; es gibt keine Warte- oder Folgezustände.

## Anwendungsszenarien

- **Frequenzteiler:** Anlegen eines Rechtecksignals an `CLK`; an `Q` erscheint die halbe Frequenz.
- **Binärer Zustandswechsel:** Umschalten einer Leuchte oder eines Ventils bei jedem Taktimpuls.
- **Reset-gesicherter Toggle:** Durch Ansteuern von `RST` kann der Ausgang in eine definierte Grundstellung gezwungen werden.
- **Pulszähler:** Kombination mehrerer FB_T_FF hintereinander ergibt einen binären Zähler.

## Vergleich mit ähnlichen Bausteinen

| Baustein       | Eigenschaft                                                                 |
|----------------|-----------------------------------------------------------------------------|
| **SR-Flipflop**| Setzt und rückgesetzt durch separate Eingänge; kein Toggle-Verhalten.      |
| **D-Flipflop** | Übernimmt den Wert von `D` bei Taktflanke; kein Toggle, kein Reset integriert. |
| **FB_T_FF**    | Invertiert den Ausgang bei jeder steigenden Flanke, asynchroner Reset möglich. |

Der **FB_T_FF** ist damit ideal für einfache Umschaltaufgaben, bei denen kein Setz-/Rücksetz-Eingang benötigt wird.

## Fazit

Der **FB_T_FF** realisiert ein robustes, flankengesteuertes Toggle-Flipflop mit asynchronem Reset. Durch die kompakte Implementierung eignet er sich für zeitkritische Steuerungen in der Automatisierungstechnik, bei denen zuverlässige Zustandswechsel erforderlich sind. Die Flankendetektion ist softwaremäßig sauber gelöst und benötigt keine zusätzliche Hardware.
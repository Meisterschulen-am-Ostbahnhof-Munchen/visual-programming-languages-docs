# E_T_FF_SR_SYM


![E_T_FF_SR_SYM](./E_T_FF_SR_SYM.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **E_T_FF_SR_SYM** ist ein ereignisgesteuerter, bistabiler Kippschalter mit integrierter Toggle-Funktion. Er vereint die Eigenschaften eines SR-Flipflops (Set‑Reset) und eines Toggle‑Flipflops (umschalten bei Takt). Die Besonderheit liegt im symmetrischen Startverhalten: Im Initialzustand führen sowohl Set‑ als auch Clock‑Ereignisse zum Set‑Zustand, während ein Reset‑Ereignis direkt zum Reset‑Zustand führt. Dies ermöglicht ein definiertes und vorhersagbares Verhalten direkt nach der Inbetriebnahme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| S | Event | Setzen des Ausgangs Q (auf TRUE) |
| R | Event | Zurücksetzen des Ausgangs Q (auf FALSE) |
| CLK | Event | Takt zum Umschalten des Ausgangs Q (Toggle) |

### **Ereignis-Ausgänge**

| Name | Typ | Mit Variable | Kommentar |
|------|-----|--------------|-----------|
| EO | Event | Q | Ausgang Q hat sich geändert |

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| Q | BOOL | Wert des Flipflops (TRUE = gesetzt, FALSE = zurückgesetzt) |

### **Adapter**

Keine.

## Funktionsweise

Der Baustein arbeitet als endlicher Automat mit drei Zuständen: **START**, **SET** und **RESET**.

- Im **START**-Zustand (Initialzustand) wird bei Eintreten eines **S**-Ereignisses oder eines **CLK**-Ereignisses in den **SET**-Zustand gewechselt. Bei einem **R**-Ereignis wechselt er in den **RESET**-Zustand.
- Im **SET**-Zustand führt ein **R**-Ereignis zum Wechsel in den **RESET**-Zustand, ein **CLK**-Ereignis ebenfalls. Ein **S**-Ereignis würde den Zustand halten (nicht explizit modelliert, aber durch die Ausgabeänderung nur bei Wechsel).
- Im **RESET**-Zustand führt ein **S**-Ereignis oder ein **CLK**-Ereignis in den **SET**-Zustand. Ein **R**-Ereignis würde den Zustand halten.

Bei jedem Zustandswechsel wird der entsprechende Algorithmus ausgeführt:
- **SET**: `Q := TRUE;`
- **RESET**: `Q := FALSE;`

Anschließend wird das Ereignis **EO** ausgegeben, das den neuen Wert von **Q** begleitet.

Das **Toggle**-Verhalten ist dadurch realisiert, dass ein CLK-Ereignis immer den aktuellen Zustand umschaltet – unabhängig davon, ob SET oder RESET aktiv ist.

## Technische Besonderheiten

- Keine Dateneingänge: Die Steuerung erfolgt ausschließlich über Ereignisse. Dies reduziert die Anzahl der benötigten Verbindungen und vereinfacht die zeitliche Analyse.
- Symmetrisches Startverhalten: Der Initialzustand START ist nicht gleichbedeutend mit einem definierten Ausgangswert. Stattdessen wird bei jedem der drei möglichen Startereignisse (S, R, CLK) sofort ein definierter Folgezustand eingenommen. Dies vermeidet undefinierte Zustände nach dem Start.
- Alle Algorithmen sind in ST (Structured Text) implementiert und bestehen aus einfachen Zuweisungen.
- Der Ausgang Q wird nur bei einem Zustandswechsel aktualisiert – das EO-Ereignis zeigt genau diese Änderung an.

## Zustandsübersicht

| Zustand | Beschreibung |
|---------|--------------|
| START | Initialzustand nach Aktivierung des Bausteins |
| SET   | Ausgang Q = TRUE |
| RESET | Ausgang Q = FALSE |

**Übergänge** (Ereignis → Zielzustand):

| Ausgangszustand | Ereignis | Zielzustand |
|-----------------|----------|-------------|
| START | S | SET |
| START | R | RESET |
| START | CLK | SET |
| SET   | R | RESET |
| SET   | CLK | RESET |
| RESET | S | SET |
| RESET | CLK | SET |

Hinweis: Verbleiben S‑Ereignisse im SET‑Zustand oder R‑Ereignisse im RESET‑Zustand werden nicht explizit abgebildet – der Zustand bleibt erhalten, und es erfolgt keine EO‑Ausgabe.

## Anwendungsszenarien

- **Umschaltvorgänge mit Takt**: Der Baustein eignet sich für Anwendungen, bei denen ein Binärsignal durch einen Takt umgeschaltet werden soll, aber auch ein separates Setzen oder Rücksetzen möglich sein muss (z. B. manuelle Vorrangsteuerung).
- **Symmetrische Startinitialisierung**: In sicherheitskritischen Systemen kann durch das gleichberechtigte Reagieren auf S oder CLK im Startzustand vermieden werden, dass ein undefinierter Wert vorliegt.
- **Pulsweitenmodulation oder Toggle-Sperren**: Als einfacher Toggle-Baustein mit Set/Reset-Vorrang.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|-------------|
| E_FF_SR | Reines SR-Flipflop ohne Toggle. Keine Taktfunktion. |
| E_FF_Toggle | Reines Toggle-Flipflop, kein Set/Reset. |
| E_T_FF_SR | Ähnlich, jedoch ohne symmetrisches Startverhalten. Hier führt CLK im START-Zustand ggf. zu undefiniertem Verhalten. |
| E_T_FF_SR_SYM | Kombiniert SR und Toggle mit definiertem Startverhalten für alle Eingangssignale. |

## Fazit

Der **E_T_FF_SR_SYM** ist ein vielseitiger ereignisgesteuerter Flipflop-Baustein, der sowohl Set‑/Reset‑ als auch Toggle‑Funktionen vereint. Das symmetrische Startverhalten macht ihn besonders für Anwendungen geeignet, bei denen direkt nach der Aktivierung ein definierter Zustand erreicht werden muss – unabhängig davon, welches Ereignis zuerst eintrifft. Dank der reinen Ereignissteuerung lässt er sich einfach in zeitkritische Steuerungsabläufe einbinden.
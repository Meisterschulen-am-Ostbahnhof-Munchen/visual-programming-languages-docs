# A2X_TO_A2X2

![A2X_TO_A2X2](A2X_TO_A2X2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock A2X_TO_A2X2 hängt einen bidirektionalen [A2X2](../../../types/bidirectional/BOOL/A2X2.md)-Abzweig ("Tap") in eine unidirektionale [A2X](../../../types/unidirectional/BOOL/A2X.md)-Kette ein. Anders als eine einfache 1:1-Konvertierung nutzt er dafür **drei** Adapter: Ein eingehendes unidirektionales A2X-Signal wird sowohl auf die bidirektionale A2X2-Schnittstelle veröffentlicht als auch – was A2X2 auf seiner Anfrage-Seite zurückliefert – als eigenständiges unidirektionales A2X-Signal wieder ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Eingänge – die Kommunikation läuft ausschließlich über die Adapter.

### **Ereignis-Ausgänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Ausgänge.

### **Daten-Eingänge**

Der Funktionsblock verfügt über keine direkten Daten-Eingänge.

### **Daten-Ausgänge**

Der Funktionsblock verfügt über keine direkten Daten-Ausgänge.

### **Adapter**

- **A2X_IN** (Socket): unidirektionale UP/DOWN-Quelle, Typ `adapter::types::unidirectional::A2X`
- **A2X2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `A2X_IN` gespeist wird und dessen eingehende Seite an `A2X_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::A2X2`
- **A2X_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `A2X2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::A2X`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `A2X_IN` eintrifft (`E_UP`/`UP`, `E_DOWN`/`DOWN`), wird direkt auf die ausgehende Seite von `A2X2_BIDIR` (`EO_UP`/`DO_UP`, `EO_DOWN`/`DO_DOWN`) veröffentlicht – A2X2_BIDIR meldet also nach außen dasselbe UP/DOWN-Signal, das über A2X_IN hereinkommt. Umgekehrt wird alles, was `A2X2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI_UP`/`DI_UP`, `EI_DOWN`/`DI_DOWN` – also was ein an A2X2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständiges unidirektionales Signal über den Plug `A2X_OUT` ausgegeben. A2X2_BIDIR fungiert damit als Abzweigpunkt, der die unidirektionale Kette nicht unterbricht, sondern um eine bidirektionale Beobachtungs-/Einspeisemöglichkeit erweitert.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `A2X_OUT` gibt nur wieder, was über `A2X2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `A2X_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- A2X_IN.E_UP → A2X2_BIDIR.EO_UP, A2X_IN.UP → A2X2_BIDIR.DO_UP
- A2X_IN.E_DOWN → A2X2_BIDIR.EO_DOWN, A2X_IN.DOWN → A2X2_BIDIR.DO_DOWN
- A2X2_BIDIR.EI_UP → A2X_OUT.E_UP, A2X2_BIDIR.DI_UP → A2X_OUT.UP
- A2X2_BIDIR.EI_DOWN → A2X_OUT.E_DOWN, A2X2_BIDIR.DI_DOWN → A2X_OUT.DOWN

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale A2X-Signalkette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl den Status eines unidirektionalen Signalgebers anzeigen als auch selbst Kommandos zurücksenden soll
- Brücke zwischen einer unidirektionalen A2X-Zone und einer bidirektionalen A2X2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[A2X2_TO_A2X](A2X2_TO_A2X.md) ist das Spiegelbild dieses Bausteins – dort steht `A2X2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen den einkanaligen Adaptern siehe die Konvertierungs-Bausteine zwischen [AX](../../../types/unidirectional/BOOL/AX.md) und [AX2](../../../types/bidirectional/BOOL/AX2.md) in derselben Bibliothek.

## Fazit

A2X_TO_A2X2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales A2X-Signal an einem bidirektionalen A2X2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Signalkette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-Signal als eigenständiges A2X-Signal weiter.

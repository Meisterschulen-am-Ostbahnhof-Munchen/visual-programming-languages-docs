# AR_TO_AR2

![AR_TO_AR2](AR_TO_AR2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AR_TO_AR2 hängt einen bidirektionalen [AR2](../../../types/bidirectional/REAL/AR2.md)-Abzweig ("Tap") in eine unidirektionale [AR](../../../types/unidirectional/REAL/AR.md)-Kette ein. Anders als eine einfache 1:1-Konvertierung nutzt er dafür **drei** Adapter: Ein eingehendes unidirektionales AR-Signal wird sowohl auf die bidirektionale AR2-Schnittstelle veröffentlicht als auch – was AR2 auf seiner Anfrage-Seite zurückliefert – als eigenständiges unidirektionales AR-Signal wieder ausgegeben.

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

- **AR_IN** (Socket): unidirektionale REAL-Quelle, Typ `adapter::types::unidirectional::AR`
- **AR2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `AR_IN` gespeist wird und dessen eingehende Seite an `AR_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::AR2`
- **AR_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `AR2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AR`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `AR_IN` eintrifft (`E1`/`D1`), wird direkt auf die ausgehende Seite von `AR2_BIDIR` (`EO1`/`DO1`) veröffentlicht – AR2_BIDIR meldet also nach außen dasselbe Signal, das über AR_IN hereinkommt. Umgekehrt wird alles, was `AR2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI1`/`DI1` – also was ein an AR2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständiges unidirektionales Signal über den Plug `AR_OUT` ausgegeben. AR2_BIDIR fungiert damit als Abzweigpunkt, der die unidirektionale Kette nicht unterbricht, sondern um eine bidirektionale Beobachtungs-/Einspeisemöglichkeit erweitert.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AR_OUT` gibt nur wieder, was über `AR2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `AR_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AR_IN.E1 → AR2_BIDIR.EO1, AR_IN.D1 → AR2_BIDIR.DO1
- AR2_BIDIR.EI1 → AR_OUT.E1, AR2_BIDIR.DI1 → AR_OUT.D1

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale AR-Signalkette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl den Status eines unidirektionalen Messwertgebers anzeigen als auch selbst Sollwerte zurücksenden soll
- Brücke zwischen einer unidirektionalen AR-Zone und einer bidirektionalen AR2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AR2_TO_AR](AR2_TO_AR.md) ist das Spiegelbild dieses Bausteins – dort steht `AR2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen einem plain REAL-Signal und AR2 siehe [AR2_R_TO_REAL](AR2_R_TO_REAL.md)/[AR2_REAL_TO_R](AR2_REAL_TO_R.md).

## Fazit

AR_TO_AR2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales AR-Signal an einem bidirektionalen AR2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Signalkette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-Signal als eigenständiges AR-Signal weiter.

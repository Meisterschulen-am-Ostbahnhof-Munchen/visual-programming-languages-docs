# AX_TO_AX2

![AX_TO_AX2](AX_TO_AX2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AX_TO_AX2 hängt einen bidirektionalen [AX2](../../../types/bidirectional/BOOL/AX2.md)-Abzweig ("Tap") in eine unidirektionale [AX](../../../types/unidirectional/BOOL/AX.md)-Kette ein. Anders als eine einfache 1:1-Konvertierung nutzt er dafür **drei** Adapter: Ein eingehendes unidirektionales AX-Signal wird sowohl auf die bidirektionale AX2-Schnittstelle veröffentlicht als auch – was AX2 auf seiner Anfrage-Seite zurückliefert – als eigenständiges unidirektionales AX-Signal wieder ausgegeben.

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

- **AX_IN** (Socket): unidirektionale BOOL-Quelle, Typ `adapter::types::unidirectional::AX`
- **AX2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `AX_IN` gespeist wird und dessen eingehende Seite an `AX_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::AX2`
- **AX_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `AX2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AX`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `AX_IN` eintrifft (`E1`/`D1`), wird direkt auf die ausgehende Seite von `AX2_BIDIR` (`EO1`/`DO1`) veröffentlicht – AX2_BIDIR meldet also nach außen dasselbe Signal, das über AX_IN hereinkommt. Umgekehrt wird alles, was `AX2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI1`/`DI1` – also was ein an AX2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständiges unidirektionales Signal über den Plug `AX_OUT` ausgegeben. AX2_BIDIR fungiert damit als Abzweigpunkt, der die unidirektionale Kette nicht unterbricht, sondern um eine bidirektionale Beobachtungs-/Einspeisemöglichkeit erweitert.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AX_OUT` gibt nur wieder, was über `AX2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `AX_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AX_IN.E1 → AX2_BIDIR.EO1, AX_IN.D1 → AX2_BIDIR.DO1
- AX2_BIDIR.EI1 → AX_OUT.E1, AX2_BIDIR.DI1 → AX_OUT.D1

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale AX-Signalkette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl den Status eines unidirektionalen Signalgebers anzeigen als auch selbst Kommandos zurücksenden soll
- Brücke zwischen einer unidirektionalen AX-Zone und einer bidirektionalen AX2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AX2_TO_AX](AX2_TO_AX.md) ist das Spiegelbild dieses Bausteins – dort steht `AX2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen einem plain BOOL-Signal und AX2 siehe [AX2_BOOL_TO_X](AX2_BOOL_TO_X.md)/[AX2_X_TO_BOOL](AX2_X_TO_BOOL.md). Das Gegenstück für den 2-kanaligen A2X/A2X2 ist [A2X_TO_A2X2](A2X_TO_A2X2.md).

## Fazit

AX_TO_AX2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales AX-Signal an einem bidirektionalen AX2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Signalkette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-Signal als eigenständiges AX-Signal weiter.

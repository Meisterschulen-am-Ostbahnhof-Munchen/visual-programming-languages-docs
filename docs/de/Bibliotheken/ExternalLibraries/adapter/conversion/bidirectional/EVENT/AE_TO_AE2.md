# AE_TO_AE2

![AE_TO_AE2](AE_TO_AE2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AE_TO_AE2 hängt einen bidirektionalen [AE2](../../../types/bidirectional/EVENT/AE2.md)-Abzweig ("Tap") in eine unidirektionale [AE](../../../types/unidirectional/EVENT/AE.md)-Ereigniskette ein. Anders als eine einfache 1:1-Konvertierung nutzt er dafür **drei** Adapter: Ein eingehendes unidirektionales AE-Ereignis wird sowohl auf die bidirektionale AE2-Schnittstelle veröffentlicht als auch – was AE2 auf seiner Anfrage-Seite zurückliefert – als eigenständiges unidirektionales AE-Ereignis wieder ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Eingänge – die Kommunikation läuft ausschließlich über die Adapter.

### **Ereignis-Ausgänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Ausgänge.

### **Daten-Eingänge**

Der Funktionsblock verfügt über keine Daten-Ein- oder -Ausgänge – AE und AE2 transportieren ausschließlich Ereignisse, keine Nutzdaten.

### **Daten-Ausgänge**

Der Funktionsblock verfügt über keine Daten-Ein- oder -Ausgänge – AE und AE2 transportieren ausschließlich Ereignisse, keine Nutzdaten.

### **Adapter**

- **AE_IN** (Socket): unidirektionale EVENT-Quelle, Typ `adapter::types::unidirectional::AE`
- **AE2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `AE_IN` gespeist wird und dessen eingehende Seite an `AE_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::AE2`
- **AE_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `AE2_BIDIR` als unidirektionales Ereignis, Typ `adapter::types::unidirectional::AE`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `AE_IN` eintrifft (`E1`), wird direkt auf die ausgehende Seite von `AE2_BIDIR` (`EO1`) veröffentlicht – AE2_BIDIR meldet also nach außen dasselbe Ereignis, das über AE_IN hereinkommt. Umgekehrt wird alles, was `AE2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI1` – also was ein an AE2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständiges unidirektionales Ereignis über den Plug `AE_OUT` ausgegeben. Da AE/AE2 reine Ereignisadapter ohne Nutzdaten sind, entfallen DataConnections vollständig.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Ereignisrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- Kein Datentransport: AE/AE2 tragen ausschließlich Ereignisse, daher besitzt dieser Baustein keine DataConnections
- `AE_OUT` gibt nur wieder, was über `AE2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `AE_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AE_IN.E1 → AE2_BIDIR.EO1
- AE2_BIDIR.EI1 → AE_OUT.E1

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale AE-Ereigniskette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl ein unidirektionales Ereignis anzeigen als auch selbst ein Ereignis zurücksenden soll
- Brücke zwischen einer unidirektionalen AE-Zone und einer bidirektionalen AE2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AE2_TO_AE](AE2_TO_AE.md) ist das Spiegelbild dieses Bausteins – dort steht `AE2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen einem plain EVENT-Signal und AE2 siehe [AE2_EVENT_TO_E](AE2_EVENT_TO_E.md)/[AE2_E_TO_EVENT](AE2_E_TO_EVENT.md). Für zwei gekoppelte Ereignisse (SET/RESET) siehe [ASR_TO_ASR2](ASR_TO_ASR2.md).

## Fazit

AE_TO_AE2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales AE-Ereignis an einem bidirektionalen AE2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Ereigniskette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-Ereignis als eigenständiges AE-Ereignis weiter.

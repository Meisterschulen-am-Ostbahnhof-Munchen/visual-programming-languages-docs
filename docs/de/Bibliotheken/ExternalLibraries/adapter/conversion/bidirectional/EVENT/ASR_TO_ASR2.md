# ASR_TO_ASR2

![ASR_TO_ASR2](ASR_TO_ASR2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock ASR_TO_ASR2 hängt einen bidirektionalen [ASR2](../../../types/bidirectional/EVENT/ASR2.md)-Abzweig ("Tap") in eine unidirektionale [ASR](../../../types/unidirectional/EVENT/ASR.md)-Kette ein. ASR/ASR2 transportieren zwei gekoppelte Ereignisse, SET und RESET, statt eines einzelnen E1. Wie bei den anderen Bridge-Bausteinen nutzt ASR_TO_ASR2 dafür **drei** Adapter: Eingehende unidirektionale SET/RESET-Ereignisse werden sowohl auf die bidirektionale ASR2-Schnittstelle veröffentlicht als auch – was ASR2 auf seiner Anfrage-Seite zurückliefert – als eigenständige unidirektionale SET/RESET-Ereignisse wieder ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Eingänge – die Kommunikation läuft ausschließlich über die Adapter.

### **Ereignis-Ausgänge**

Der Funktionsblock verfügt über keine direkten Ereignis-Ausgänge.

### **Daten-Eingänge**

Der Funktionsblock verfügt über keine Daten-Ein- oder -Ausgänge – ASR und ASR2 transportieren ausschließlich die Ereignisse SET/RESET, keine Nutzdaten.

### **Daten-Ausgänge**

Der Funktionsblock verfügt über keine Daten-Ein- oder -Ausgänge – ASR und ASR2 transportieren ausschließlich die Ereignisse SET/RESET, keine Nutzdaten.

### **Adapter**

- **ASR_IN** (Socket): unidirektionale SET/RESET-Quelle, Typ `adapter::types::unidirectional::ASR`
- **ASR2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `ASR_IN` gespeist wird und dessen eingehende Seite an `ASR_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::ASR2`
- **ASR_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `ASR2_BIDIR` als unidirektionale SET/RESET-Ereignisse, Typ `adapter::types::unidirectional::ASR`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `ASR_IN` eintrifft (`SET`/`RESET`), wird direkt auf die ausgehende Seite von `ASR2_BIDIR` (`EO_SET`/`EO_RESET`) veröffentlicht – ASR2_BIDIR meldet also nach außen dieselben Ereignisse, die über ASR_IN hereinkommen. Umgekehrt wird alles, was `ASR2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI_SET`/`EI_RESET` – also was ein an ASR2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständige unidirektionale Ereignisse über den Plug `ASR_OUT` (`SET`/`RESET`) ausgegeben. Da ASR/ASR2 reine Ereignisadapter ohne Nutzdaten sind, entfallen DataConnections vollständig.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Ereignisrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Zwei parallele, aber unabhängig geführte Ereignispaare (SET und RESET), keine Verrechnung oder Zusammenführung der beiden
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- Kein Datentransport: ASR/ASR2 tragen ausschließlich SET/RESET-Ereignisse, daher besitzt dieser Baustein keine DataConnections
- `ASR_OUT` gibt nur wieder, was über `ASR2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `ASR_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- ASR_IN.SET → ASR2_BIDIR.EO_SET, ASR_IN.RESET → ASR2_BIDIR.EO_RESET
- ASR2_BIDIR.EI_SET → ASR_OUT.SET, ASR2_BIDIR.EI_RESET → ASR_OUT.RESET

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale ASR-SET/RESET-Kette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl SET/RESET-Zustände anzeigen als auch selbst SET/RESET-Ereignisse zurücksenden soll
- Brücke zwischen einer unidirektionalen ASR-Zone und einer bidirektionalen ASR2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[ASR2_TO_ASR](ASR2_TO_ASR.md) ist das Spiegelbild dieses Bausteins – dort steht `ASR2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen zwei plain EVENT-Signalen und ASR2 siehe [ASR2_4EVENTS_TO_SR2](ASR2_4EVENTS_TO_SR2.md)/[ASR2_SR2_TO_4EVENTS](ASR2_SR2_TO_4EVENTS.md). Für ein einzelnes Ereignis ohne SET/RESET-Kopplung siehe [AE_TO_AE2](AE_TO_AE2.md).

## Fazit

ASR_TO_ASR2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales ASR-SET/RESET-Paar an einem bidirektionalen ASR2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Kette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-SET/RESET-Paar als eigenständiges ASR-Signal weiter.

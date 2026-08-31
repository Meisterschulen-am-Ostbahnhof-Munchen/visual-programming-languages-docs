# ASR2_TO_ASR

![ASR2_TO_ASR](ASR2_TO_ASR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock ASR2_TO_ASR ist das Spiegelbild von [ASR_TO_ASR2](ASR_TO_ASR2.md): Hier steht der bidirektionale [ASR2](../../../types/bidirectional/EVENT/ASR2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [ASR](../../../types/unidirectional/EVENT/ASR.md)-Socket und einen unidirektionalen ASR-Plug.

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

- **ASR2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `ASR_OUT` weitergereicht wird und dessen ausgehende Seite von `ASR_IN` gespeist wird, Typ `adapter::types::bidirectional::ASR2`
- **ASR_IN** (Socket): unidirektionale SET/RESET-Quelle, Typ `adapter::types::unidirectional::ASR`
- **ASR_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `ASR2_BIDIR` als unidirektionale SET/RESET-Ereignisse, Typ `adapter::types::unidirectional::ASR`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `ASR2_BIDIR` auf seiner Indikations-Seite empfängt (`EO_SET`/`EO_RESET` – also was ein an ASR2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständige unidirektionale Ereignisse über den Plug `ASR_OUT` (`SET`/`RESET`) ausgegeben. Umgekehrt wird alles, was am Socket `ASR_IN` eintrifft (`SET`/`RESET`), auf die Anfrage-Seite von `ASR2_BIDIR` (`EI_SET`/`EI_RESET`) veröffentlicht – ASR2_BIDIR sendet also dieselben Ereignisse an den angeschlossenen bidirektionalen Teilnehmer weiter. Da ASR/ASR2 reine Ereignisadapter ohne Nutzdaten sind, entfallen DataConnections vollständig.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Ereignisrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Zwei parallele, aber unabhängig geführte Ereignispaare (SET und RESET), keine Verrechnung oder Zusammenführung der beiden
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- Kein Datentransport: ASR/ASR2 tragen ausschließlich SET/RESET-Ereignisse, daher besitzt dieser Baustein keine DataConnections
- `ASR_OUT` gibt nur wieder, was über `ASR2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `ASR_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- ASR2_BIDIR.EO_SET → ASR_OUT.SET, ASR2_BIDIR.EO_RESET → ASR_OUT.RESET
- ASR_IN.SET → ASR2_BIDIR.EI_SET, ASR_IN.RESET → ASR2_BIDIR.EI_RESET

## Anwendungsszenarien

- Auslesen eines bidirektionalen ASR2-Teilnehmers als einfaches unidirektionales ASR-SET/RESET-Paar, kombiniert mit dem Einspeisen eines separaten unidirektionalen SET/RESET-Paars
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf ASR2 umzustellen
- Brücke zwischen einer bidirektionalen ASR2-Zone und einer unidirektionalen ASR-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[ASR_TO_ASR2](ASR_TO_ASR2.md) ist das Spiegelbild dieses Bausteins – dort steht `ASR2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen ASR2 und zwei plain EVENT-Signalen siehe [ASR2_SR2_TO_4EVENTS](ASR2_SR2_TO_4EVENTS.md)/[ASR2_4EVENTS_TO_SR2](ASR2_4EVENTS_TO_SR2.md). Für ein einzelnes Ereignis ohne SET/RESET-Kopplung siehe [AE2_TO_AE](AE2_TO_AE.md).

## Fazit

ASR2_TO_ASR ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen ASR2-Teilnehmers als eigenständiges unidirektionales SET/RESET-Paar sichtbar und speist gleichzeitig ein separates unidirektionales SET/RESET-Paar in die bidirektionale Seite ein.

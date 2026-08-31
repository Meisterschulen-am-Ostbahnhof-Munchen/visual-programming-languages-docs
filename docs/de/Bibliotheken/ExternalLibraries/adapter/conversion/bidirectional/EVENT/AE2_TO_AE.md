# AE2_TO_AE

![AE2_TO_AE](AE2_TO_AE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AE2_TO_AE ist das Spiegelbild von [AE_TO_AE2](AE_TO_AE2.md): Hier steht der bidirektionale [AE2](../../../types/bidirectional/EVENT/AE2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [AE](../../../types/unidirectional/EVENT/AE.md)-Socket und einen unidirektionalen AE-Plug.

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

- **AE2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `AE_OUT` weitergereicht wird und dessen ausgehende Seite von `AE_IN` gespeist wird, Typ `adapter::types::bidirectional::AE2`
- **AE_IN** (Socket): unidirektionale EVENT-Quelle, Typ `adapter::types::unidirectional::AE`
- **AE_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `AE2_BIDIR` als unidirektionales Ereignis, Typ `adapter::types::unidirectional::AE`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `AE2_BIDIR` auf seiner Indikations-Seite empfängt (`EO1` – also was ein an AE2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständiges unidirektionales Ereignis über den Plug `AE_OUT` ausgegeben. Umgekehrt wird alles, was am Socket `AE_IN` eintrifft (`E1`), auf die Anfrage-Seite von `AE2_BIDIR` (`EI1`) veröffentlicht – AE2_BIDIR sendet also dasselbe Ereignis an den angeschlossenen bidirektionalen Teilnehmer weiter. Da AE/AE2 reine Ereignisadapter ohne Nutzdaten sind, entfallen DataConnections vollständig.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Ereignisrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- Kein Datentransport: AE/AE2 tragen ausschließlich Ereignisse, daher besitzt dieser Baustein keine DataConnections
- `AE_OUT` gibt nur wieder, was über `AE2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `AE_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AE2_BIDIR.EO1 → AE_OUT.E1
- AE_IN.E1 → AE2_BIDIR.EI1

## Anwendungsszenarien

- Auslesen eines bidirektionalen AE2-Teilnehmers als einfaches unidirektionales AE-Ereignis, kombiniert mit dem Einspeisen eines separaten unidirektionalen Ereignisses
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf AE2 umzustellen
- Brücke zwischen einer bidirektionalen AE2-Zone und einer unidirektionalen AE-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AE_TO_AE2](AE_TO_AE2.md) ist das Spiegelbild dieses Bausteins – dort steht `AE2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen AE2 und einem plain EVENT-Signal siehe [AE2_E_TO_EVENT](AE2_E_TO_EVENT.md)/[AE2_EVENT_TO_E](AE2_EVENT_TO_E.md). Für zwei gekoppelte Ereignisse (SET/RESET) siehe [ASR2_TO_ASR](ASR2_TO_ASR.md).

## Fazit

AE2_TO_AE ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen AE2-Teilnehmers als eigenständiges unidirektionales AE-Ereignis sichtbar und speist gleichzeitig ein separates unidirektionales Ereignis in die bidirektionale Seite ein.

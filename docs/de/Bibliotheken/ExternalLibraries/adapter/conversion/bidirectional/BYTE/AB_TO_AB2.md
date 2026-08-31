# AB_TO_AB2

![AB_TO_AB2](AB_TO_AB2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AB_TO_AB2 hängt einen bidirektionalen [AB2](../../../types/bidirectional/BYTE/AB2.md)-Abzweig ("Tap") in eine unidirektionale [AB](../../../types/unidirectional/BYTE/AB.md)-Kette ein. Anders als eine einfache 1:1-Konvertierung nutzt er dafür **drei** Adapter: Ein eingehendes unidirektionales AB-Signal wird sowohl auf die bidirektionale AB2-Schnittstelle veröffentlicht als auch – was AB2 auf seiner Anfrage-Seite zurückliefert – als eigenständiges unidirektionales AB-Signal wieder ausgegeben.

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

- **AB_IN** (Socket): unidirektionale BYTE-Quelle, Typ `adapter::types::unidirectional::AB`
- **AB2_BIDIR** (Plug): bidirektionaler Abzweig, dessen ausgehende Seite von `AB_IN` gespeist wird und dessen eingehende Seite an `AB_OUT` weitergereicht wird, Typ `adapter::types::bidirectional::AB2`
- **AB_OUT** (Plug): spiegelt die eingehende (Anfrage-)Seite von `AB2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AB`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was am Socket `AB_IN` eintrifft (`E1`/`D1`), wird direkt auf die ausgehende Seite von `AB2_BIDIR` (`EO1`/`DO1`) veröffentlicht – AB2_BIDIR meldet also nach außen dasselbe Signal, das über AB_IN hereinkommt. Umgekehrt wird alles, was `AB2_BIDIR` auf seiner Anfrage-Seite empfängt (`EI1`/`DI1` – also was ein an AB2_BIDIR angeschlossener bidirektionaler Teilnehmer "zurücksendet"), unverändert als eigenständiges unidirektionales Signal über den Plug `AB_OUT` ausgegeben. AB2_BIDIR fungiert damit als Abzweigpunkt, der die unidirektionale Kette nicht unterbricht, sondern um eine bidirektionale Beobachtungs-/Einspeisemöglichkeit erweitert.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die eingehende und die vom Tap zurückkommende Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AB_OUT` gibt nur wieder, was über `AB2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer zurückkommt – ohne einen solchen Teilnehmer bleibt `AB_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AB_IN.E1 → AB2_BIDIR.EO1, AB_IN.D1 → AB2_BIDIR.DO1
- AB2_BIDIR.EI1 → AB_OUT.E1, AB2_BIDIR.DI1 → AB_OUT.D1

## Anwendungsszenarien

- Nachträgliches Einhängen eines bidirektionalen Diagnose- oder Steuerpunkts in eine bestehende unidirektionale AB-Signalkette, ohne diese zu unterbrechen
- Systeme, in denen ein bidirektionaler Teilnehmer (z. B. ein Bedienpanel) sowohl den Status eines unidirektionalen Byte-Signalgebers anzeigen als auch selbst Kommandos zurücksenden soll
- Brücke zwischen einer unidirektionalen AB-Zone und einer bidirektionalen AB2-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AB2_TO_AB](AB2_TO_AB.md) ist das Spiegelbild dieses Bausteins – dort steht `AB2_BIDIR` als Socket auf der linken Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen einem plain BYTE-Signal und AB2 siehe [AB2_B_TO_BYTE](AB2_B_TO_BYTE.md)/[AB2_BYTE_TO_B](AB2_BYTE_TO_B.md).

## Fazit

AB_TO_AB2 ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht ein unidirektionales AB-Signal an einem bidirektionalen AB2-Punkt sichtbar, ohne die ursprüngliche unidirektionale Signalkette zu unterbrechen, und gibt gleichzeitig das dort empfangene Anfrage-Signal als eigenständiges AB-Signal weiter.

# AR2_TO_AR

![AR2_TO_AR](AR2_TO_AR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AR2_TO_AR ist das Spiegelbild von [AR_TO_AR2](AR_TO_AR2.md): Hier steht der bidirektionale [AR2](../../../types/bidirectional/REAL/AR2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [AR](../../../types/unidirectional/REAL/AR.md)-Socket und einen unidirektionalen AR-Plug.

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

- **AR2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `AR_OUT` weitergereicht wird und dessen ausgehende Seite von `AR_IN` gespeist wird, Typ `adapter::types::bidirectional::AR2`
- **AR_IN** (Socket): unidirektionale REAL-Quelle, Typ `adapter::types::unidirectional::AR`
- **AR_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `AR2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AR`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `AR2_BIDIR` auf seiner Indikations-Seite empfängt (`EO1`/`DO1` – also was ein an AR2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständiges unidirektionales Signal über den Plug `AR_OUT` ausgegeben. Umgekehrt wird alles, was am Socket `AR_IN` eintrifft (`E1`/`D1`), auf die Anfrage-Seite von `AR2_BIDIR` (`EI1`/`DI1`) veröffentlicht – AR2_BIDIR sendet also dasselbe Signal an den angeschlossenen bidirektionalen Teilnehmer weiter.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AR_OUT` gibt nur wieder, was über `AR2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `AR_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AR2_BIDIR.EO1 → AR_OUT.E1, AR2_BIDIR.DO1 → AR_OUT.D1
- AR_IN.E1 → AR2_BIDIR.EI1, AR_IN.D1 → AR2_BIDIR.DI1

## Anwendungsszenarien

- Auslesen des Status eines bidirektionalen AR2-Teilnehmers als einfaches unidirektionales AR-Signal, kombiniert mit dem Einspeisen eines separaten unidirektionalen Sollwertsignals
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf AR2 umzustellen
- Brücke zwischen einer bidirektionalen AR2-Zone und einer unidirektionalen AR-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AR_TO_AR2](AR_TO_AR2.md) ist das Spiegelbild dieses Bausteins – dort steht `AR2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen AR2 und einem plain REAL-Signal siehe [AR2_REAL_TO_R](AR2_REAL_TO_R.md)/[AR2_R_TO_REAL](AR2_R_TO_REAL.md).

## Fazit

AR2_TO_AR ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen AR2-Teilnehmers als eigenständiges unidirektionales AR-Signal sichtbar und speist gleichzeitig ein separates unidirektionales Signal in die bidirektionale Seite ein.

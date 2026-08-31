# AB2_TO_AB

![AB2_TO_AB](AB2_TO_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AB2_TO_AB ist das Spiegelbild von [AB_TO_AB2](AB_TO_AB2.md): Hier steht der bidirektionale [AB2](../../../types/bidirectional/BYTE/AB2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [AB](../../../types/unidirectional/BYTE/AB.md)-Socket und einen unidirektionalen AB-Plug.

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

- **AB2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `AB_OUT` weitergereicht wird und dessen ausgehende Seite von `AB_IN` gespeist wird, Typ `adapter::types::bidirectional::AB2`
- **AB_IN** (Socket): unidirektionale BYTE-Quelle, Typ `adapter::types::unidirectional::AB`
- **AB_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `AB2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AB`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `AB2_BIDIR` auf seiner Indikations-Seite empfängt (`EO1`/`DO1` – also was ein an AB2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständiges unidirektionales Signal über den Plug `AB_OUT` ausgegeben. Umgekehrt wird alles, was am Socket `AB_IN` eintrifft (`E1`/`D1`), auf die Anfrage-Seite von `AB2_BIDIR` (`EI1`/`DI1`) veröffentlicht – AB2_BIDIR sendet also dasselbe Signal an den angeschlossenen bidirektionalen Teilnehmer weiter.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AB_OUT` gibt nur wieder, was über `AB2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `AB_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AB2_BIDIR.EO1 → AB_OUT.E1, AB2_BIDIR.DO1 → AB_OUT.D1
- AB_IN.E1 → AB2_BIDIR.EI1, AB_IN.D1 → AB2_BIDIR.DI1

## Anwendungsszenarien

- Auslesen des Status eines bidirektionalen AB2-Teilnehmers als einfaches unidirektionales AB-Signal, kombiniert mit dem Einspeisen eines separaten unidirektionalen Kommandosignals
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf AB2 umzustellen
- Brücke zwischen einer bidirektionalen AB2-Zone und einer unidirektionalen AB-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AB_TO_AB2](AB_TO_AB2.md) ist das Spiegelbild dieses Bausteins – dort steht `AB2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen AB2 und einem plain BYTE-Signal siehe [AB2_BYTE_TO_B](AB2_BYTE_TO_B.md)/[AB2_B_TO_BYTE](AB2_B_TO_BYTE.md).

## Fazit

AB2_TO_AB ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen AB2-Teilnehmers als eigenständiges unidirektionales AB-Signal sichtbar und speist gleichzeitig ein separates unidirektionales Signal in die bidirektionale Seite ein.

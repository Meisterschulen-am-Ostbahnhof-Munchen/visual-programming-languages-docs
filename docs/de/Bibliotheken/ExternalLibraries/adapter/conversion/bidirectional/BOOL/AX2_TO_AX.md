# AX2_TO_AX

![AX2_TO_AX](AX2_TO_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AX2_TO_AX ist das Spiegelbild von [AX_TO_AX2](AX_TO_AX2.md): Hier steht der bidirektionale [AX2](../../../types/bidirectional/BOOL/AX2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [AX](../../../types/unidirectional/BOOL/AX.md)-Socket und einen unidirektionalen AX-Plug.

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

- **AX2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `AX_OUT` weitergereicht wird und dessen ausgehende Seite von `AX_IN` gespeist wird, Typ `adapter::types::bidirectional::AX2`
- **AX_IN** (Socket): unidirektionale BOOL-Quelle, Typ `adapter::types::unidirectional::AX`
- **AX_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `AX2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::AX`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `AX2_BIDIR` auf seiner Indikations-Seite empfängt (`EO1`/`DO1` – also was ein an AX2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständiges unidirektionales Signal über den Plug `AX_OUT` ausgegeben. Umgekehrt wird alles, was am Socket `AX_IN` eintrifft (`E1`/`D1`), auf die Anfrage-Seite von `AX2_BIDIR` (`EI1`/`DI1`) veröffentlicht – AX2_BIDIR sendet also dasselbe Signal an den angeschlossenen bidirektionalen Teilnehmer weiter.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `AX_OUT` gibt nur wieder, was über `AX2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `AX_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- AX2_BIDIR.EO1 → AX_OUT.E1, AX2_BIDIR.DO1 → AX_OUT.D1
- AX_IN.E1 → AX2_BIDIR.EI1, AX_IN.D1 → AX2_BIDIR.DI1

## Anwendungsszenarien

- Auslesen des Status eines bidirektionalen AX2-Teilnehmers als einfaches unidirektionales AX-Signal, kombiniert mit dem Einspeisen eines separaten unidirektionalen Kommandosignals
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf AX2 umzustellen
- Brücke zwischen einer bidirektionalen AX2-Zone und einer unidirektionalen AX-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[AX_TO_AX2](AX_TO_AX2.md) ist das Spiegelbild dieses Bausteins – dort steht `AX2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen AX2 und einem plain BOOL-Signal siehe [AX2_X_TO_BOOL](AX2_X_TO_BOOL.md)/[AX2_BOOL_TO_X](AX2_BOOL_TO_X.md). Das Gegenstück für den 2-kanaligen A2X2/A2X ist [A2X2_TO_A2X](A2X2_TO_A2X.md).

## Fazit

AX2_TO_AX ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen AX2-Teilnehmers als eigenständiges unidirektionales AX-Signal sichtbar und speist gleichzeitig ein separates unidirektionales Signal in die bidirektionale Seite ein.

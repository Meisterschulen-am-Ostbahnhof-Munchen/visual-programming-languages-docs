# A2X2_TO_A2X

![A2X2_TO_A2X](A2X2_TO_A2X.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock A2X2_TO_A2X ist das Spiegelbild von [A2X_TO_A2X2](A2X_TO_A2X2.md): Hier steht der bidirektionale [A2X2](../../../types/bidirectional/BOOL/A2X2.md)-Abzweig als Socket auf der linken (Eingangs-)Seite, ergänzt um einen zweiten unidirektionalen [A2X](../../../types/unidirectional/BOOL/A2X.md)-Socket und einen unidirektionalen A2X-Plug.

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

- **A2X2_BIDIR** (Socket): bidirektionaler Abzweig, dessen eingehende Seite an `A2X_OUT` weitergereicht wird und dessen ausgehende Seite von `A2X_IN` gespeist wird, Typ `adapter::types::bidirectional::A2X2`
- **A2X_IN** (Socket): unidirektionale UP/DOWN-Quelle, Typ `adapter::types::unidirectional::A2X`
- **A2X_OUT** (Plug): spiegelt die eingehende (Indikations-)Seite von `A2X2_BIDIR` als unidirektionales Signal, Typ `adapter::types::unidirectional::A2X`

## Funktionsweise

Der Baustein arbeitet in zwei Richtungen gleichzeitig: Was der Socket `A2X2_BIDIR` auf seiner Indikations-Seite empfängt (`EO_UP`/`DO_UP`, `EO_DOWN`/`DO_DOWN` – also was ein an A2X2_BIDIR angeschlossener bidirektionaler Teilnehmer meldet), wird unverändert als eigenständiges unidirektionales Signal über den Plug `A2X_OUT` ausgegeben. Umgekehrt wird alles, was am Socket `A2X_IN` eintrifft (`E_UP`/`UP`, `E_DOWN`/`DOWN`), auf die Anfrage-Seite von `A2X2_BIDIR` (`EI_UP`/`DI_UP`, `EI_DOWN`/`DI_DOWN`) veröffentlicht – A2X2_BIDIR sendet also dasselbe UP/DOWN-Signal an den angeschlossenen bidirektionalen Teilnehmer weiter.

## Technische Besonderheiten

- Drei statt zwei Adapter: Die vom Tap empfangene und die separat eingespeiste Signalrichtung werden bewusst getrennt gehalten, statt sie zu vermischen
- Reine Verdrahtung ohne Logik oder Zustand, jede Zielvariable hat genau einen Schreiber
- `A2X_OUT` gibt nur wieder, was über `A2X2_BIDIR` von einem angeschlossenen bidirektionalen Teilnehmer gemeldet wird – ohne einen solchen Teilnehmer bleibt `A2X_OUT` inaktiv

## Zustandsübersicht

Der Baustein ist zustandslos:

- A2X2_BIDIR.EO_UP → A2X_OUT.E_UP, A2X2_BIDIR.DO_UP → A2X_OUT.UP
- A2X2_BIDIR.EO_DOWN → A2X_OUT.E_DOWN, A2X2_BIDIR.DO_DOWN → A2X_OUT.DOWN
- A2X_IN.E_UP → A2X2_BIDIR.EI_UP, A2X_IN.UP → A2X2_BIDIR.DI_UP
- A2X_IN.E_DOWN → A2X2_BIDIR.EI_DOWN, A2X_IN.DOWN → A2X2_BIDIR.DI_DOWN

## Anwendungsszenarien

- Auslesen des Status eines bidirektionalen A2X2-Teilnehmers als einfaches unidirektionales A2X-Signal, kombiniert mit dem Einspeisen eines separaten unidirektionalen Kommandosignals
- Systeme, in denen ein bidirektionaler Teilnehmer überwacht werden soll, ohne die restliche Steuerung auf A2X2 umzustellen
- Brücke zwischen einer bidirektionalen A2X2-Zone und einer unidirektionalen A2X-Zone

## ⚖️ Vergleich mit ähnlichen Bausteinen

[A2X_TO_A2X2](A2X_TO_A2X2.md) ist das Spiegelbild dieses Bausteins – dort steht `A2X2_BIDIR` als Plug auf der rechten Seite. Für eine reine, nicht abzweigende 1:1-Umsetzung zwischen den einkanaligen Adaptern siehe die Konvertierungs-Bausteine zwischen [AX](../../../types/unidirectional/BOOL/AX.md) und [AX2](../../../types/bidirectional/BOOL/AX2.md) in derselben Bibliothek.

## Fazit

A2X2_TO_A2X ist kein einfacher Konverter, sondern ein Abzweigpunkt: Es macht den Zustand eines bidirektionalen A2X2-Teilnehmers als eigenständiges unidirektionales A2X-Signal sichtbar und speist gleichzeitig ein separates unidirektionales Signal in die bidirektionale Seite ein.

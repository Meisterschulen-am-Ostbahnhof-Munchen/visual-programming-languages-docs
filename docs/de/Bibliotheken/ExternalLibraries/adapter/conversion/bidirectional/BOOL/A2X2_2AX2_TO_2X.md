# A2X2_2AX2_TO_2X

![A2X2_2AX2_TO_2X](A2X2_2AX2_TO_2X.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock A2X2_2AX2_TO_2X setzt einen [A2X2](../../../types/bidirectional/BOOL/A2X2.md)-Plug aus zwei [AX2](../../../types/bidirectional/BOOL/AX2.md)-Sockets zusammen – einem für den UP-Kanal, einem für den DOWN-Kanal. Da AX2 selbst schon bidirektional ist (1 Ereignis/1 Bool je Richtung), genügt pro Kanal ein einziger AX2, um beide Richtungen von A2X2 abzudecken.

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

- **A2X2_OUT** (Plug): zusammengesetzter Ausgang vom Typ `adapter::types::bidirectional::A2X2`
- **UP** (Socket): Kanal UP, vom Typ `adapter::types::bidirectional::AX2` – TRUE = vorwärts, hoch, rechts, im Uhrzeigersinn
- **DOWN** (Socket): Kanal DOWN, vom Typ `adapter::types::bidirectional::AX2` – TRUE = rückwärts, runter, links, gegen den Uhrzeigersinn

## Funktionsweise

Für jeden Kanal wird die komplette bidirektionale Verdrahtung zwischen A2X2 und dem zugehörigen AX2-Socket hergestellt: Was `A2X2_OUT` auf seiner Anfrage-Seite empfängt (`EI_UP`/`DI_UP`), wird an `UP.EI1`/`UP.DI1` weitergereicht; was `UP` auf seiner Indikations-Seite liefert (`EO1`/`DO1`), erscheint an `A2X2_OUT.EO_UP`/`DO_UP`. Für DOWN gilt dieselbe Verdrahtung mit dem `DOWN`-Socket. Beide Kanäle sind vollständig unabhängig.

## Technische Besonderheiten

- Nutzt die Bidirektionalität von AX2 direkt aus – jeder Kanal braucht nur einen einzigen Adapter, nicht zwei
- Reine Verdrahtung ohne Logik oder Zustand
- Jede Zielvariable hat genau einen Schreiber, keine Mehrfach-Datenverbindungen

## Zustandsübersicht

Der Baustein ist zustandslos:

- A2X2_OUT.EI_UP → UP.EI1, A2X2_OUT.DI_UP → UP.DI1
- UP.EO1 → A2X2_OUT.EO_UP, UP.DO1 → A2X2_OUT.DO_UP
- A2X2_OUT.EI_DOWN → DOWN.EI1, A2X2_OUT.DI_DOWN → DOWN.DI1
- DOWN.EO1 → A2X2_OUT.EO_DOWN, DOWN.DO1 → A2X2_OUT.DO_DOWN

## Anwendungsszenarien

- Aufbau eines A2X2-Endgeräts aus zwei bereits vorhandenen, unabhängigen AX2-Kanälen
- Systeme, in denen UP und DOWN aus historischen Gründen getrennt als AX2 verdrahtet sind, aber nach außen als ein A2X2 auftreten sollen
- Modulare Zusammensetzung größerer Adapter aus kleineren, wiederverwendbaren Bausteinen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Das Gegenstück [A2X2_2X_TO_2AX2](A2X2_2X_TO_2AX2.md) zerlegt statt zu komponieren. Für dieselbe Aufgabe gibt es mit [A2X2_4AX_TO_2X](A2X2_4AX_TO_2X.md) eine Alternative, die statt zwei bidirektionalen AX2 vier unidirektionale [AX](../../../types/unidirectional/BOOL/AX.md) verwendet (zwei je Kanal, je einer pro Richtung) – sinnvoll, wenn nur unidirektionale AX-Infrastruktur zur Verfügung steht. Der unidirektionale Vorgänger [A2X_2AX_TO_2X](../../unidirectional/BOOL/A2X_2AX_TO_2X.md) komponiert analog aus zwei einfachen [AX](../../../types/unidirectional/BOOL/AX.md)-Adaptern.

## Fazit

A2X2_2AX2_TO_2X ist der effizienteste Weg, ein A2X2 aus zwei vorhandenen AX2-Kanälen zu bauen, da beide Adapter bereits bidirektional sind und keine zusätzliche Logik nötig ist.

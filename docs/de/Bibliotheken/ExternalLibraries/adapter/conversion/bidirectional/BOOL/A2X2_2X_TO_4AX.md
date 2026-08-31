# A2X2_2X_TO_4AX

![A2X2_2X_TO_4AX](A2X2_2X_TO_4AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock A2X2_2X_TO_4AX zerlegt einen [A2X2](../../../types/bidirectional/BOOL/A2X2.md)-Socket in **vier** unidirektionale [AX](../../../types/unidirectional/BOOL/AX.md)-Adapter. Da A2X2 zwei Kanäle (UP/DOWN) hat und jeder davon selbst bidirektional ist, braucht man pro Kanal zwei unidirektionale AX, um beide Richtungen abzudecken – eins für die Indikations-Richtung, eins für die Anfrage-Richtung. 2 Kanäle × 2 Richtungen = 4 AX.

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

- **A2X2_IN** (Socket): zu zerlegender Eingang vom Typ `adapter::types::bidirectional::A2X2`
- **REQ_UP** (Socket): Anfrage UP, von außen empfangen und an `A2X2_IN.EI_UP` weitergereicht, Typ `adapter::types::unidirectional::AX`
- **REQ_DOWN** (Socket): Anfrage DOWN, von außen empfangen und an `A2X2_IN.EI_DOWN` weitergereicht, Typ `adapter::types::unidirectional::AX`
- **IND_UP** (Plug): Indikation UP, aus `A2X2_IN.EO_UP` nach außen veröffentlicht, Typ `adapter::types::unidirectional::AX`
- **IND_DOWN** (Plug): Indikation DOWN, aus `A2X2_IN.EO_DOWN` nach außen veröffentlicht, Typ `adapter::types::unidirectional::AX`

## Funktionsweise

Was der A2X2-Socket auf seiner Indikations-Seite empfängt (`EO_UP`/`DO_UP` bzw. `EO_DOWN`/`DO_DOWN`), wird unverändert über die unidirektionalen Plugs `IND_UP`/`IND_DOWN` veröffentlicht. Umgekehrt wird alles, was an den unidirektionalen Sockets `REQ_UP`/`REQ_DOWN` von außen ankommt, an die Anfrage-Seite des A2X2-Sockets (`EI_UP`/`DI_UP` bzw. `EI_DOWN`/`DI_DOWN`) weitergereicht. Damit stehen beide Richtungen jedes Kanals als eigener, rein unidirektionaler AX-Adapter zur Verfügung.

## Technische Besonderheiten

- Vier separate AX-Adapter statt zwei AX2, weil AX kein `EventInputs`/`EventOutputs`-Paar in einem Adapter vereint – jede Richtung braucht ihren eigenen Adapter
- Reine Verdrahtung ohne Logik oder Zustand
- Jede Zielvariable hat genau einen Schreiber, keine Mehrfach-Datenverbindungen

## Zustandsübersicht

Der Baustein ist zustandslos:

- A2X2_IN.EO_UP → IND_UP.E1, A2X2_IN.DO_UP → IND_UP.D1
- A2X2_IN.EO_DOWN → IND_DOWN.E1, A2X2_IN.DO_DOWN → IND_DOWN.D1
- REQ_UP.E1 → A2X2_IN.EI_UP, REQ_UP.D1 → A2X2_IN.DI_UP
- REQ_DOWN.E1 → A2X2_IN.EI_DOWN, REQ_DOWN.D1 → A2X2_IN.DI_DOWN

## Anwendungsszenarien

- Anbindung eines A2X2-Signals an eine Infrastruktur, die nur unidirektionale AX-Adapter kennt (z. B. ältere Teilsysteme)
- Getrennte Verarbeitung von Anfrage- und Indikations-Richtung, etwa zur unabhängigen Protokollierung oder Filterung
- Systeme, in denen bidirektionale AX2-Adapter nicht verfügbar oder nicht gewünscht sind

## ⚖️ Vergleich mit ähnlichen Bausteinen

Für dieselbe Aufgabe (A2X2 zerlegen) gibt es mit [A2X2_2X_TO_2AX2](A2X2_2X_TO_2AX2.md) eine einfachere Alternative, die nur zwei bidirektionale [AX2](../../../types/bidirectional/BOOL/AX2.md) statt vier unidirektionaler AX benötigt – wo AX2-Infrastruktur zur Verfügung steht, ist das die schlankere Lösung. Das Gegenstück zu diesem Baustein ist [A2X2_4AX_TO_2X](A2X2_4AX_TO_2X.md), das aus vier AX wieder ein A2X2 zusammensetzt.

## Fazit

A2X2_2X_TO_4AX ist die richtige Wahl, wenn ein A2X2-Signal in eine rein unidirektionale AX-Landschaft integriert werden muss – auf Kosten von doppelt so vielen Adaptern wie bei der AX2-basierten Alternative.

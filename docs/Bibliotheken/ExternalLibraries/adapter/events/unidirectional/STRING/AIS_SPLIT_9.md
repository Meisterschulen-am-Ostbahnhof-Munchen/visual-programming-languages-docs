# AIS_SPLIT_9


![AIS_SPLIT_9](./AIS_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIS_SPLIT_9** dient dazu, einen eingehenden unidirektionalen **AIS**-Adapter (Application Interface Socket) auf neun identische ausgehende **AIS**-Adapter (Plugs) zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine einfache Vervielfachung eines AIS-Signals für bis zu neun nachgeschaltete Funktionsblöcke.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Bezeichnung | Typ                 | Richtung | Beschreibung                                        |
|-------------|----------------------|----------|-----------------------------------------------------|
| **IN**      | AIS (unidirectional) | Socket   | Eingangsadapter – das zu verteilende AIS-Signal.    |
| **OUT1**    | AIS (unidirectional) | Plug     | Erster Ausgang – identische Kopie des Eingangssignals. |
| **OUT2**    | AIS (unidirectional) | Plug     | Zweiter Ausgang – identische Kopie des Eingangssignals. |
| **OUT3**    | AIS (unidirectional) | Plug     | Dritter Ausgang – identische Kopie des Eingangssignals. |
| **OUT4**    | AIS (unidirectional) | Plug     | Vierter Ausgang – identische Kopie des Eingangssignals. |
| **OUT5**    | AIS (unidirectional) | Plug     | Fünfter Ausgang – identische Kopie des Eingangssignals. |
| **OUT6**    | AIS (unidirectional) | Plug     | Sechster Ausgang – identische Kopie des Eingangssignals. |
| **OUT7**    | AIS (unidirectional) | Plug     | Siebter Ausgang – identische Kopie des Eingangssignals. |
| **OUT8**    | AIS (unidirectional) | Plug     | Achter Ausgang – identische Kopie des Eingangssignals. |
| **OUT9**    | AIS (unidirectional) | Plug     | Neunter Ausgang – identische Kopie des Eingangssignals. |

## Funktionsweise

Der **AIS_SPLIT_9** ist ein rein kombinatorischer Baustein ohne eigene Zustandslogik oder Ereignissteuerung. Er empfängt am **Socket IN** ein AIS-Signal und leitet dieses unverändert an alle neun **Plugs OUT1** bis **OUT9** weiter. Jede Änderung am Eingang wird sofort auf alle Ausgänge übertragen. Der Baustein fungiert somit als passiver Signalverteiler („Broadcast“) auf der AIS‑Schnittstelle.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ definiert (`GenericClassName = GEN_AIS_SPLIT`). Dies ermöglicht eine flexible Wiederverwendung in unterschiedlichen AIS‑Kontexten, ohne dass der Baustein für jede Anwendung erneut erstellt werden muss.
- **Unidirektionale Übertragung**: Sowohl Eingang als auch Ausgänge verwenden den unidirektionalen **AIS**‑Adaptertyp, d. h. die Daten fließen nur in eine Richtung (vom Eingang zu den Ausgängen).
- **Keine Datenpufferung oder Verzögerung**: Aufgrund des fehlenden Ereignis‑ und Daten‑Handlings arbeitet der Baustein ohne Zwischenspeicher oder Taktung – er ist strikt signaldurchschaltend.
- **Einfaches Interface**: Der Baustein besitzt weder Ereignisse noch Daten‑Ein‑/Ausgänge, sondern ausschließlich Adapter. Dies macht ihn besonders leichtgewichtig und für reine Signalkopplungen geeignet.

## Zustandsübersicht

Der **AIS_SPLIT_9** besitzt keine internen Zustände oder Ablaufsteuerungen. Sein Verhalten ist deterministisch und jederzeit durch das Eingangssignal bestimmt. Es existieren keine initialisierenden oder fehlerhaften Zustände.

## Anwendungsszenarien

- **Signalvervielfachung**: Ein AIS‑basiertes Steuerungssignal soll parallel an mehrere unabhängige Aktoren, Regler oder Anzeigen weitergegeben werden.
- **Broadcast in Modularen Systemen**: In einer verteilten Automatisierungsumgebung wird ein zentraler Messwert (z. B. Temperatur, Druck) über AIS bereitgestellt und muss gleichzeitig von mehreren Funktionsblöcken konsumiert werden.
- **Prototyping und Test**: Ein Testsignal soll auf mehrere Instanzen eines gleichen FB‑Typs verteilt werden, ohne dass der Quell‑FB mehrfach instanziiert werden muss.

## Vergleich mit ähnlichen Bausteinen

- **AIS_SPLIT_2 / AIS_SPLIT_4 / AIS_SPLIT_8** etc.: Diese Bausteine verteilen das Eingangssignal auf 2, 4 oder 8 Ausgänge. Der **AIS_SPLIT_9** ist speziell für Anwendungen ausgelegt, die genau neun parallele Verbindungen benötigen. Die Funktionsweise ist identisch – der einzige Unterschied liegt in der Anzahl der Ausgänge.
- **AIS_MERGE**: Im Gegensatz zum Split‑Baustein fasst ein Merge‑Baustein mehrere Eingänge zu einem Ausgang zusammen. **AIS_SPLIT_9** realisiert den umgekehrten Datenfluss.
- **Direkte Kopplung**: Anstelle eines Split‑Bausteins könnte man auch eine manuelle Verdrahtung (mehrere OUT‑Adapter) in der 4diac‑IDE vornehmen. Der **AIS_SPLIT_9** vereinfacht jedoch die grafische Darstellung und reduziert die Komplexität des Netzwerks.

## Fazit

Der **AIS_SPLIT_9** ist ein einfacher, aber äußerst nützlicher Funktionsblock zur Vervielfältigung eines unidirektionalen AIS‑Signals auf neun Ausgänge. Seine generische Auslegung, der Verzicht auf Ereignis‑ oder Datenlogik und die klare Schnittstelle machen ihn zu einem verlässlichen Werkzeug für modulare Automatisierungslösungen. Er eignet sich besonders für Anwendungen, bei denen ein Signal ohne Verzögerung oder Änderung an mehrere Empfänger verteilt werden muss.
# AUS_SPLIT_8


![AUS_SPLIT_8](./AUS_SPLIT_8.svg)

* * * * * * * * * *

## Einleitung

Der **AUS_SPLIT_8** ist ein generischer Funktionsbaustein zur Verteilung eines eingehenden AUS-Signals auf bis zu acht separate Ausgänge. Er dient als einfacher „Splitter“ für Signale vom Typ **adapter::types::unidirectional::AUS** und ermöglicht die parallele Ansteuerung mehrerer Verbraucher oder nachfolgender Bausteine.

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

| Schnittstelle | Typ | Richtung | Beschreibung |
|---|---|---|---|
| **IN** | `adapter::types::unidirectional::AUS` | Socket | Eingang – empfängt das zu verteilende AUS-Signal |
| **OUT1** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 1 – gibt das eingehende Signal weiter |
| **OUT2** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 2 – gibt das eingehende Signal weiter |
| **OUT3** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 3 – gibt das eingehende Signal weiter |
| **OUT4** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 4 – gibt das eingehende Signal weiter |
| **OUT5** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 5 – gibt das eingehende Signal weiter |
| **OUT6** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 6 – gibt das eingehende Signal weiter |
| **OUT7** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 7 – gibt das eingehende Signal weiter |
| **OUT8** | `adapter::types::unidirectional::AUS` | Plug | Ausgang 8 – gibt das eingehende Signal weiter |

## Funktionsweise

Der Baustein leitet das am Socket **IN** anliegende AUS-Signal unverändert an alle acht Plugs **OUT1** bis **OUT8** weiter. Es findet keine Verzögerung, Filterung oder logische Verarbeitung statt. Das Signal wird auf allen Ausgängen gleichzeitig zur Verfügung gestellt. Die Funktion entspricht einer 1-zu-8-Verteilung.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB wird als generischer Typ (`GEN_AUS_SPLIT`) ausgeführt. Die konkrete Typisierung erfolgt zur Laufzeit über das Attribut `eclipse4diac::core::GenericClassName`.
- **Keine Zustandsmaschine**: Da der Baustein nur eine direkte Weiterleitung ohne Logik vornimmt, besitzt er keine eigene Ausführungssteuerung (ECC). Die Signalweitergabe erfolgt rein über die Adapter-Schnittstellen.
- **Adapter-Typ**: Alle Schnittstellen verwenden den unidirektionalen `AUS`-Adaptertyp, der eine standardisierte Signalübertragung ermöglicht.

## Zustandsübersicht

Der Baustein besitzt keine Zustandsmaschine. Es existieren keine internen Zustände oder Übergänge.

## Anwendungsszenarien

- **Verteilen eines zentralen Steuersignals**: Ein einzelnes „Aus“-Signal (z. B. Ausschaltbefehl) wird an mehrere Aktoren oder Unterbausteine weitergegeben.
- **Parallelschaltung von Verbrauchern**: In landwirtschaftlichen oder industriellen Steuerungen, wenn ein Signal gleichzeitig mehrere Ventile, Motoren oder Leuchten ansteuern soll.
- **Bussignale aufteilen**: Wenn ein Adapter-basierter Signalpfad in mehrere parallele Pfade verzweigt werden muss.

## Vergleich mit ähnlichen Bausteinen

- **AUS_SPLIT_4**: Verteilt ein Signal auf vier Ausgänge. Der AUS_SPLIT_8 bietet mit acht Ausgängen eine höhere Fan-Out-Kapazität.
- **AUS_MERGE / AUS_JOIN**: Führen mehrere Signale zusammen – funktional das Gegenteil.
- **AUS_ROUTER**: Kann ein Signal wahlweise auf einen von mehreren Ausgängen leiten, während der Splitter immer alle Ausgänge aktiviert.

## Fazit

Der **AUS_SPLIT_8** ist ein einfacher, aber nützlicher Funktionsbaustein zur Vervielfachung eines AUS-Signals. Durch den Verzicht auf Logik und Zustände ist er effizient und leicht verständlich. Er eignet sich besonders für Anwendungen, in denen ein Steuersignal auf mehrere Empfänger verteilt werden muss, ohne dass eine Auswahl oder Verarbeitung erforderlich ist.
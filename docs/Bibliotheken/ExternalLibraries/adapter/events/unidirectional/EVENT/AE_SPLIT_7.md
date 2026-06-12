# AE_SPLIT_7


![AE_SPLIT_7](./AE_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AE_SPLIT_7** dient dazu, ein einzelnes eingehendes Adapter-Ereignis (AE) auf sieben gleichartige Ausgangsadapter zu verteilen. Es handelt sich um einen generischen Baustein, der für unidirektionale Adapter des Typs `adapter::types::unidirectional::AE` ausgelegt ist. Der FB ermöglicht eine sternförmige Weiterleitung eines Ereignissignals an mehrere nachgelagerte Bausteine, ohne dass die Ereignisse verändert oder verzögert werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – die Kommunikation erfolgt ausschließlich über Adapter.

### **Ereignis-Ausgänge**
Keine – die Ausgabe erfolgt über Adapter.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AE` | **IN** | Socket | Eingangsadapter, der das zu verteilende Ereignis empfängt. |
| `adapter::types::unidirectional::AE` | **OUT1** | Plug    | Erster Ausgangsadapter, das empfangene Ereignis wird hierhin weitergeleitet. |
| `adapter::types::unidirectional::AE` | **OUT2** | Plug    | Zweiter Ausgangsadapter. |
| `adapter::types::unidirectional::AE` | **OUT3** | Plug    | Dritter Ausgangsadapter. |
| `adapter::types::unidirectional::AE` | **OUT4** | Plug    | Vierter Ausgangsadapter. |
| `adapter::types::unidirectional::AE` | **OUT5** | Plug    | Fünfter Ausgangsadapter. |
| `adapter::types::unidirectional::AE` | **OUT6** | Plug    | Sechster Ausgangsadapter. |
| `adapter::types::unidirectional::AE` | **OUT7** | Plug    | Siebter Ausgangsadapter. |

## Funktionsweise
Der Baustein ist passiv und leitet ein ankommendes Ereignis am Eingangsadapter **IN** unverändert an alle sieben Ausgangsadapter **OUT1** bis **OUT7** weiter. Die Weiterleitung erfolgt gleichzeitig (logisch parallel), d.h. nach dem Empfang eines Ereignisses werden alle Ausgänge mit demselben Ereignis versorgt. Es findet keine Pufferung, Priorisierung oder Datenmanipulation statt. Da es sich um unidirektionale Adapter handelt, ist nur eine Richtung (vom Socket zum Plug) gegeben.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_AE_SPLIT`) deklariert und kann in verschiedenen Kontexten mit dem entsprechenden Adaptertyp verwendet werden. Die Typüberprüfung erfolgt zur Entwurfszeit.
- **Keine Latenz:** Das Ereignis wird ohne Verzögerung durchgereicht; die Laufzeit hängt ausschließlich von der Infrastruktur des IEC 61499 Laufzeitsystems ab.
- **Typgleichheit:** Alle beteiligten Adapter müssen denselben Typ (`AE` – unidirectional) aufweisen. Eine Mischung unterschiedlicher Adaptertypen ist nicht zulässig.
- **Keine Zustandsspeicherung:** Der FB besitzt kein internes Gedächtnis – er führt lediglich eine 1:n‑Weiterleitung durch.

## Zustandsübersicht
Da der FB keine eigene Zustandsmaschine besitzt und ausschließlich reaktiv auf eingehende Ereignisse arbeitet, besteht nur ein einziger impliziter Zustand: **Bereit**. In diesem Zustand werden Ereignisse am Eingang sofort an alle Ausgänge weitergegeben. Es gibt keine Fehlerzustände oder Start/Stopp‑Logik.

## Anwendungsszenarien
- **Ereignisverteilung in Steuerungsanwendungen:** Ein einzelner Sensor oder Bus‑Teilnehmer löst ein Ereignis aus, das gleichzeitig mehrere Aktoren, Alarme oder Überwachungsblöcke erreichen soll.
- **Parallele Verarbeitung:** Ein Ereignis soll in mehreren unabhängigen Funktionsblöcken gleichzeitig verarbeitet werden, z.B. für Redundanz oder unterschiedliche Auswertungen.
- **Strukturierung der Anwendung:** Ersetzt mehrere manuelle Verbindungsknoten und erhöht die Übersichtlichkeit im Netzwerkdiagramm.

## Vergleich mit ähnlichen Bausteinen
- **AE\_SPLIT\_2, AE\_SPLIT\_3, ... :** Diese Bausteine bieten die gleiche Funktionalität, jedoch mit einer geringeren Anzahl an Ausgängen. Die Wahl hängt von der benötigten Anzahl ab.
- **E\_SPLIT (Ereignis-Splitter, datenlos):** Ein reiner Ereignis‑Splitter (ohne Adapterkapselung) verteilt Ereignisse, kann aber nicht mit Adapter‑Schnittstellen umgehen. Der AE\_SPLIT\_7 ist speziell für die Verwendung mit Adapter‑Typen wie `AE` vorgesehen.
- **Adapter‑Merger (z.B. AE\_MERGE):** Führt mehrere Adapter‑Ereignisse zu einem zusammen – das Gegenteil des vorliegenden Bausteins.

## Fazit
Der **AE\_SPLIT\_7** ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfältigung von Adapter‑Ereignissen in IEC 61499 Anwendungen. Seine generische Natur, die vollständige Ereignistreue und die einfache Handhabung machen ihn zu einem grundlegenden Werkzeug für die strukturierte Ereignisverteilung. Er ist ideal geeignet, wenn ein Ereignis an mehrere gleichartige Zieladapter weitergeleitet werden muss und kein Dateninhalt transportiert wird.
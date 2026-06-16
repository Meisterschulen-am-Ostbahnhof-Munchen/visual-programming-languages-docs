# AD_DEMUX_5


![AD_DEMUX_5](./AD_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_DEMUX_5** ist ein generischer Demultiplexer für Adapterverbindungen. Er verteilt einen eingehenden unidirektionalen Adapterdatenstrom auf einen von fünf Ausgangskanälen, gesteuert durch einen Indexwert. Der Baustein dient zur dynamischen Umschaltung von Signalen in verteilten Automatisierungssystemen und erweitert die Flexibilität bei der Verschaltung von Kommunikationsadaptern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Setzt den Index K und löst die Demultiplexer-Aktion aus |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung, dass der Index K übernommen und die Verbindung aktiviert wurde |

### **Daten-Eingänge**

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| K        | UINT     | Zielindex (Wertebereich 1..5) für die Auswahl des Ausgangsadapters |

### **Daten-Ausgänge**
*Keine* – die Datenweitergabe erfolgt über die Adapterschnittstellen.

### **Adapter**

| Richtung | Bezeichner | Typ                        | Kommentar                          |
|----------|------------|----------------------------|------------------------------------|
| Socket   | IN         | adapter::types::unidirectional::AD | Eingangsadapter (zu verteilendes Signal) |
| Plug     | OUT1       | adapter::types::unidirectional::AD | Ausgang 1                          |
| Plug     | OUT2       | adapter::types::unidirectional::AD | Ausgang 2                          |
| Plug     | OUT3       | adapter::types::unidirectional::AD | Ausgang 3                          |
| Plug     | OUT4       | adapter::types::unidirectional::AD | Ausgang 4                          |
| Plug     | OUT5       | adapter::types::unidirectional::AD | Ausgang 5                          |

## Funktionsweise
Der Baustein erwartet einen Index **K** (1‑basiert) am Dateneingang. Wird das Ereignis **REQ** empfangen, kopiert der Demultiplexer den gesamten Datenstrom des Adapter-Sockets **IN** auf den durch **K** bestimmten Ausgangs-Plug (**OUT1** bis **OUT5**). Nach erfolgreicher Umschaltung wird das Bestätigungsereignis **CNF** gesendet.

Liefert **K** einen Wert außerhalb des gültigen Bereichs (z. B. 0 oder >5), wird das Ereignis **CNF** nicht ausgelöst und keine Aktion durchgeführt (Fehlerbehandlung liegt in der übergeordneten Applikation).

Der Baustein ist **nicht zustandsbehaftet** bezüglich einer vorherigen Verbindung – jeder REQ-Aufruf überschreibt die vorherige Zuordnung.

## Technische Besonderheiten
- **Generischer Typ:** Der Funktionsblock ist als generischer FB implementiert (ClassName `'GEN_AD_DEMUX'`) und kann in unterschiedlichen Adapter-Kontexten wiederverwendet werden.
- **Unidirektionale Adapter:** Sowohl Eingangs- als auch Ausgangsadapter sind vom Typ `unidirectional::AD`, d. h. der Datenfluss verläuft nur in einer Richtung (vom Socket zum ausgewählten Plug).
- **Einfache Erweiterbarkeit:** Durch die generische Definition kann die Anzahl der Ausgänge angepasst werden, sofern die Schnittstellendefinition entsprechend erweitert wird.
- **Keine Datenpufferung:** Die Umschaltung erfolgt ohne Zwischenspeicher – Verzögerungen entstehen nur durch die Ereignisverarbeitung.

## Zustandsübersicht
Der Funktionsblock besitzt eine minimalistische Ablaufsteuerung – er besteht implizit aus zwei Zuständen:

1. **IDLE** – Warten auf das Ereignis **REQ**.  
   - Nach Eintreffen von REQ wird der Index **K** ausgewertet.
2. **ACTIVE** – Weiterleitung des Adapterstroms an den ausgewählten Ausgang und Senden von **CNF**.  
   - Danach Rückkehr in den IDLE-Zustand.

Eine Zustandsmaschine ist im XML nicht explizit definiert, entspricht aber dem typischen Verhalten eines ereignisgesteuerten Dienstbausteins.

## Anwendungsszenarien
- **Dynamische Signalverteilung:** In Produktionsanlagen, wo ein Sensorwert (z. B. analoger Messwert) je nach Betriebsmodus an unterschiedliche Steuerungseinheiten weitergeleitet werden muss.
- **Multiplexing in Kommunikationsnetzen:** Umschaltung von Adapterverbindungen in Systemen mit mehreren Peripheriegeräten (z. B. BUS‑Koppler, IO‑Module).
- **Test‑ und Simulationsumgebungen:** Einfaches Umleiten von Datenströmen zwischen verschiedenen logischen Einheiten zur Fehlersuche.

## Vergleich mit ähnlichen Bausteinen

| Baustein               | Besonderheiten |
|------------------------|----------------|
| **AD_DEMUX_5**         | Adapter-basiert, unidirektional, 5 Ausgänge, generisch |
| **E_DEMUX** (Standard) | Verteilt Ereignisse an einen von mehreren Ausgängen – keine Adapterdatenweitergabe |
| **F_DEMUX** (Daten)    | Verteilt Datenwerte auf mehrere OUT‑Ports über INDEX – arbeitet mit elementaren Datentypen |
| **Adapter‑SELECT**     | Ähnliche Funktion, aber häufig mit bidirektionalen Adaptern und mehreren Sockets |

Der **AD_DEMUX_5** hebt sich durch seine rein adaptergestützte Schnittstelle hervor, die eine lose Kopplung und flexible Typanpassung über generische Adapterdefinitionen ermöglicht.

## Fazit
Der **AD_DEMUX_5** ist ein kompakter und effizienter Funktionsblock zur Adapter‑Demultiplexierung. Er erlaubt die dynamische Auswahl eines von fünf Ausgangskanälen und eignet sich besonders für Systeme, die auf unidirektionale Adapterverbindungen setzen. Durch seine generische Auslegung kann er in verschiedenen Automatisierungsumgebungen ohne Anpassung der inneren Logik wiederverwendet werden. Der Baustein vereinfacht die Implementierung von Umschaltlogiken auf Adapterebene und trägt zu einer übersichtlicheren, modularen Systemarchitektur bei.
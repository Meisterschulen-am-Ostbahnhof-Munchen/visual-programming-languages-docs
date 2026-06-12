# AULI_DEMUX_2


![AULI_DEMUX_2](./AULI_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_DEMUX_2** ist ein generischer Demultiplexer, der einen eingehenden Datenstrom über einen **AULI**-Adapter entgegennimmt und auf einen von zwei Ausgängen (**OUT1** oder **OUT2**) weiterleitet. Die Auswahl des Ausgangs erfolgt über den Eingangsparameter **K**.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit Vars |
|------|-----|-----------|----------|
| REQ | Event | Set Index K | K |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Confirmation of Set Index K |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | index |

**Hinweis:** Der Index K bestimmt den Zielausgang: typischerweise wird K = 0 dem Ausgang **OUT1** und K = 1 dem Ausgang **OUT2** zugeordnet.

### **Daten-Ausgänge**

Keine direkten Datenausgänge definiert.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | IN | aULI | Input Value to demultiplex |
| Plug (Ausgang) | OUT1 | aULI | - |
| Plug (Ausgang) | OUT2 | aULI | - |

## Funktionsweise

Sobald am Ereigniseingang **REQ** ein Signal anliegt, wird der aktuelle Wert des Index **K** ausgewertet.  
- Bei **K = 0** wird der über den Adapter **IN** eingehende Datenstrom mit allen seinen Attributen an den Ausgang **OUT1** durchgereicht.  
- Bei **K = 1** erfolgt die Weiterleitung an **OUT2**.  

Nachdem die Umschaltung und Datenweitergabe abgeschlossen ist, wird das Ereignis **CNF** ausgegeben, um den erfolgreichen Vorgang zu bestätigen.

## Technische Besonderheiten

- Der Baustein ist als **generischer Funktionsblock** deklariert (GenericClassName `GEN_AULI_DEMUX`).
- Verwendet ausschließlich **unidirektionale AULI-Adapter**, daher eignet er sich für Datenflüsse, die nur in eine Richtung verlaufen.
- Der Index **K** ist als `UINT` definiert; Werte außerhalb von 0 und 1 werden nicht behandelt oder können zu undefiniertem Verhalten führen.

## Zustandsübersicht

Der interne Ablauf lässt sich als einfache Zustandsmaschine beschreiben:

1. **IDLE** – Warten auf ein REQ-Ereignis.  
2. **SELECT** – Auswerten des Index K und Verbinden des IN-Adapters mit dem entsprechenden OUT-Adapter.  
3. **SEND_CNF** – Nach erfolgreicher Umschaltung wird CNF gesendet; Rücksprung nach IDLE.

## Anwendungsszenarien

- **Routenumschaltung:** Ein von einem Sensor kommender AULI-Datenstrom soll wahlweise an eine von zwei Verarbeitungseinheiten gesendet werden.  
- **Aktuatorsteuerung:** Ein zentrales Steuersignal wird über den Demultiplexer auf zwei verschiedene Aktuatoren verteilt, gesteuert durch einen Index.  
- **Test- und Simulationsumgebungen:** Umschalten zwischen echtem und simuliertem Datenpfad.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|--------------|
| **AULI_MUX_2** | Multiplexer: wählt einen von zwei Eingängen aus und leitet ihn an einen Ausgang weiter. |
| **AULI_SWITCH** | Generischer Umschalter, oft mit mehreren Ausgängen und erweiterter Indexlogik. |
| **AULI_DEMUX_2** (dieser FB) | Demultiplexer: ein Eingang wird auf einen von zwei Ausgängen verteilt – einfacher und spezifischer als ein generischer Switch. |

## Fazit

Der **AULI_DEMUX_2** ist ein kompakter, aber leistungsfähiger Basisbaustein für die AULI-basierte Kommunikation. Er ermöglicht die flexible Verteilung von Datenströmen auf zwei Pfade und lässt sich aufgrund seiner generischen Natur problemlos in unterschiedlichste Steuerungs- und Automatisierungsszenarien integrieren.
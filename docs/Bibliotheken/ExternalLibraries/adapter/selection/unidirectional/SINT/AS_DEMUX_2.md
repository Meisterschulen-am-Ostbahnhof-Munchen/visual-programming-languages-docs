# AS_DEMUX_2


![AS_DEMUX_2](./AS_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung

Der **AS_DEMUX_2** (Generic FB) ist ein applikationsneutraler, ereignisgesteuerter Demultiplexer für Adapter vom Typ `adapter::types::unidirectional::AS`. Er verteilt einen ankommenden Datenwert (über den Socket **IN**) an einen von zwei möglichen Ausgangsadaptern (**OUT1** oder **OUT2**). Die Zielauswahl erfolgt über den Daten-Eingang **K**.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit Variablen |
|------|-----|-----------|---------------|
| REQ  | Event | Set Index K | K |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | index |

### **Daten-Ausgänge**

Keine.

### **Adapter**

* **IN** (Socket): `adapter::types::unidirectional::AS` – Eingangswert, der demultiplext werden soll.
* **OUT1** (Plug): `adapter::types::unidirectional::AS` – Erster Ausgangskanal.
* **OUT2** (Plug): `adapter::types::unidirectional::AS` – Zweiter Ausgangskanal.

## Funktionsweise

Der Baustein arbeitet nach einem einfachen 1-zu-2 Demultiplex-Prinzip. Ein externer Aufruf des Ereignisses **REQ** triggert die Auswertung des Index **K**. Der aktuell am Socket **IN** anliegende Wert wird je nach Wert von **K** an den entsprechenden Adapter-Plug weitergeleitet:

- Falls `K = 0` → Daten werden an **OUT1** übergeben.
- Falls `K = 1` → Daten werden an **OUT2** übergeben.
- Für andere Werte von **K** (wenn nicht 0 oder 1) kann das Verhalten entweder als undefiniert oder als Fehlerfall betrachtet werden – der Baustein liefert in solchen Fällen keine Ausgabe und quittiert dennoch mit **CNF**.

Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generisch deklariert (`GenericClassName = 'GEN_AS_DEMUX'`) und kann daher in verschiedenen Typvariationen des Adapters `AS` eingesetzt werden.
- **Adapterbasiert**: Die Schnittstellen sind vollständig über Adapter realisiert, was eine hohe Modularität und Wiederverwendbarkeit in verschiedenen Steuerungsarchitekturen ermöglicht.
- **Keine Zustandsautomaten**: Der FB besitzt keinen expliziten Zustandsautomaten; die Verarbeitung erfolgt rein ereignisgesteuert und kombinatorisch.

## Zustandsübersicht

Da der Baustein keinen internen Zustand speichert (reines kombinatorisches Verhalten), existiert nur ein einziger impliziter Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| *Idle* | Warten auf das Ereignis **REQ**. Nach **REQ** wird sofort der Ausgang gewählt, die Daten weitergereicht und **CNF** gesendet. Rückkehr in *Idle*. |

## Anwendungsszenarien

- **Datenverteilung in modularen Automatisierungssystemen**: Ein Sensorwert (z. B. Drehzahl, Druck) soll wahlweise an verschiedene nachgelagerte Verarbeitungseinheiten weitergeleitet werden.
- **Kanalumschaltung**: In einer Steuerung mit mehreren Aktoren kann der Demultiplexer genutzt werden, um einen gemeinsamen Datenstrom auf den gerade aktiven Kanal zu schalten.
- **Test- und Debug-Funktionen**: Temporäre Umleitung von Diagnosedaten auf einen separaten Überwachungspfad.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ausgänge | Besonderheit |
|----------|----------|--------------|
| **AS_DEMUX_2** | 2 | Basis-Demultiplexer für zwei Kanäle, generisch |
| **AS_DEMUX_4** (hypothetisch) | 4 | Erweiterte Version mit vier Ausgängen |
| **AS_MUX_2** | – | Multiplexer: mehrere Eingänge auf einen Ausgang |
| **AS_SELECT** | – | Direkte Adapter-Weiche ohne Indexierung (fest verdrahtet) |

Der AS_DEMUX_2 ist speziell für die bidirektionale (hier aber unidirektional verwendete) AS-Adapter-Schnittstelle optimiert und arbeitet im Gegensatz zu allgemeinen Datenbausteinen ausschließlich auf Adapterebene.

## Fazit

Der **AS_DEMUX_2** stellt einen einfachen, aber flexiblen Demultiplexer für adapterbasierte Applikationen dar. Dank seines generischen Designs und der reinen Ereignissteuerung eignet er sich hervorragend für dynamische Umschaltaufgaben in IEC‑61499‑Systemen, bei denen ein Datenstrom wahlweise auf zwei Pfade gelenkt werden muss. Seine geringe Komplexität erleichtert die Integration und macht ihn zu einem zuverlässigen Grundbaustein in modularen Steuerungsarchitekturen.
# AIS_DEMUX_4


![AIS_DEMUX_4](./AIS_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIS_DEMUX_4** ist ein generischer AIS-Demultiplexer. Er empfängt einen AIS-Datenstrom über einen einzelnen Eingangsadapter und leitet ihn wahlweise an einen von vier Ausgangsadaptern weiter. Die Umschaltung erfolgt über den Index-Eingang K. Der Baustein ist für den Einsatz in IEC 61499‑Anwendungen konzipiert, die eine flexible Verteilung von AIS‑Signalen erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführtes Signal |
|----------|--------------|---------------------|
| REQ      | Setzt den Index K und löst die Weiterleitung aus | K (UINT) |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigt, dass die Weiterleitung entsprechend des Index K abgeschlossen wurde |

### **Daten-Eingänge**

| Variable | Typ    | Beschreibung |
|----------|--------|--------------|
| K        | UINT   | Index des gewünschten Ausgangs (1‑4) |

### **Daten-Ausgänge**

Keine expliziten Daten-Ausgänge. Die Ausgabe erfolgt über die Adapter OUT1 … OUT4.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Plug (Ausgang) | OUT1 | `adapter::types::unidirectional::AIS` | Erster AIS-Ausgangskanal |
| Plug (Ausgang) | OUT2 | `adapter::types::unidirectional::AIS` | Zweiter AIS-Ausgangskanal |
| Plug (Ausgang) | OUT3 | `adapter::types::unidirectional::AIS` | Dritter AIS-Ausgangskanal |
| Plug (Ausgang) | OUT4 | `adapter::types::unidirectional::AIS` | Vierter AIS-Ausgangskanal |
| Socket (Eingang) | IN  | `adapter::types::unidirectional::AIS` | AIS-Eingangssignal, das demultiplext wird |

## Funktionsweise

1. Im Initialzustand ist der Baustein bereit, einen neuen Index zu empfangen.
2. Ein Ereignis am Eingang **REQ** übernimmt den aktuellen Wert von **K** (ganze Zahl zwischen 1 und 4).
3. Der Baustein verbindet den Eingangsadapter **IN** mit dem durch K bestimmten Ausgangsadapter **OUT_K**. Alle anderen Ausgänge bleiben inaktiv oder behalten einen neutralen Zustand.
4. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** gesendet.
5. Der Baustein verhält sich wie eine 1‑zu‑4‑Weiche für AIS‑Datenströme. Jedes REQ‑Ereignis schaltet die Verbindung neu.

Die genaue Behandlung des Eingangssignals (z. B. ob Pufferung oder direkte Durchleitung) hängt von der Implementierung des zugrunde liegenden AIS‑Adaptertyps ab.

## Technische Besonderheiten

- **Generischer Typ** – Der Baustein wird unter dem generischen Klassennamen `GEN_AIS_DEMUX` geführt und kann für verschiedene AIS‑Adapterausprägungen instanziiert werden.
- **Adapterbasierte Kommunikation** – Statt direkter Daten‑Ein‑/Ausgänge nutzt der FB das IEC 61499‑Adapterkonzept, was eine lose Kopplung und einfache Wiederverwendung in verschiedenen Verteilungsarchitekturen ermöglicht.
- **Kein interner Zustandsautomat vorgegeben** – Die genaue Ablaufsteuerung obliegt der Implementierung; typischerweise wird ein einfacher Zwei‑Zustands‑Automat (IDLE → ROUTE → IDLE) verwendet.

## Zustandsübersicht

Ein explizites ECC‑Diagramm ist in dieser Typdefinition nicht enthalten. Übliche Zustände wären:

1. **IDLE** – Warten auf ein REQ‑Ereignis.
2. **ROUTE** – Weiterleitung des Eingangs an den durch K bestimmten Ausgang.

Der Übergang von IDLE zu ROUTE erfolgt durch REQ, und nach Abschluss der Weiterleitung wird CNF ausgelöst und der Baustein kehrt nach IDLE zurück.

## Anwendungsszenarien

- **AIS‑Datenverteilung** – Ein eingehender AIS‑Datenstrom soll je nach Kontext (z. B. Saison oder Betriebsmodus) an unterschiedliche nachgelagerte Verarbeitungseinheiten weitergeleitet werden.
- **Last‑ oder Signal‑Routing** – Vier parallele Pfade stehen zur Verfügung; der Index K kann dynamisch aus einer übergeordneten Steuerung gesetzt werden.
- **Test‑ und Simulationsumgebungen** – Umschalten zwischen verschiedenen Signalquellen oder -senken während des Betriebs.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Ausgänge | Besonderheit |
|----------|-----|----------|--------------|
| `AIS_DEMUX_4` | Adapter‑basiert | 4 | Speziell für AIS‑Daten, generische Klasse |
| `GEN_DEMUX` (generischer Daten‑Demultiplexer) | Direkte Daten | variabel | Arbeitet mit elementaren Datentypen, keine Adapter |
| `MUX` (Multiplexer) | Adapter‑/Daten | 1 Eingang → mehrere Ausgänge | Umgekehrte Richtung |

Der AIS_DEMUX_4 hebt sich durch seine Adapter‑Schnittstelle und die spezifische Ausrichtung auf AIS‑Protokolle ab.

## Fazit

Der **AIS_DEMUX_4** ist ein einfacher, aber effektiver Demultiplexer für AIS‑Adapterverbindungen. Seine generische Auslegung erlaubt den Einsatz in verschiedenen Umgebungen, während die klare Ereignissteuerung eine robuste Umschaltung zwischen vier Ausgangspfaden gewährleistet. Er ist eine ideale Komponente, wenn AIS‑Datenströme flexibel auf mehrere Senken verteilt werden müssen.
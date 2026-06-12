# AR2


![AR2](./AR2.svg)

* * * * * * * * * *

## Einleitung
Der Adapter-Typ **AR2** stellt eine bidirektionale Schnittstelle zwischen zwei Funktionsblöcken bereit. Er überträgt genau ein Ereignis zusammen mit einem REAL-Wert in beide Richtungen. Die Bezeichnung "AR2" steht dabei für "Adapter Real 2-Wege". Der Baustein ist als generischer Steckverbinder (Plug/Socket) innerhalb der 4diac-IDE konzipiert und ermöglicht eine saubere, typsichere Kopplung von Komponenten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar | mit Daten |
|------|-----|-----------|-----------|
| EI1  | Event | Request (or Indication) | DI1 |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar | mit Daten |
|------|-----|-----------|-----------|
| EO1  | Event | Indication (or Request) | DO1 |

### **Daten-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| DI1  | REAL     | Request (or Indication) to Socket |

### **Daten-Ausgänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| DO1  | REAL     | Indication (or Request) Data from Plug |

### **Adapter**
Keine definiert.

## Funktionsweise
Der AR2-Adapter arbeitet ereignisgesteuert und bidirektional:
- Wird der Ereigniseingang **EI1** ausgelöst, so wird der aktuell an **DI1** anliegende REAL-Wert zum gegenüberliegenden Adapterende übertragen. Dort erscheint das Ereignis **EO1** zusammen mit dem Wert auf **DO1**.
- In der Gegenrichtung gilt das Gleiche: Triggert der verbundene Gegenadapter sein Ereignis, so empfängt dieser AR2 das Ereignis an **EI1** und stellt den empfangenen Wert an **DI1** bereit.

Die Kommentare „Request (or Indication)“ und „Indication (or Request)“ verdeutlichen, dass der Adapter je nach Einbausituation (Plug oder Socket) die Rolle eines anfordernden oder eines anzeigenden Kanals einnehmen kann. Somit eignet sich AR2 sowohl für Master/Slave- als auch für Peer-to-Peer-Kommunikation.

## Technische Besonderheiten
- **Typisierte Datenübertragung:** Es wird ausschließlich der Datentyp **REAL** unterstützt, was eine klare Semantik für physikalische Messwerte oder Steuergrößen bietet.
- **Bidirektionalität:** Ein einziger Adapter realisiert den Datenaustausch in beide Richtungen, was die Anzahl der benötigten Schnittstellen reduziert.
- **Versionierung:** Der Baustein liegt in Version 1.0 vor, erstellt von der HR Agrartechnik GmbH (Copyright 2026, EPL 2.0).
- **Compiler-Information:** Das Paket ist unter `adapter::types::bidirectional` abgelegt und nutzt einen Typ-Hash (`eclipse4diac::core::TypeHash`) für Integritätsprüfungen.
- **Keine Zustandsmaschine:** Der Adapter selbst besitzt keine eigene Zustandslogik; er fungiert als reine Verbindung zwischen zwei Ereignis-/Datenpaaren.

## Zustandsübersicht
Der AR2-Adapter implementiert keine explizite Zustandsmaschine. Der Datenfluss erfolgt ohne Verzögerung oder Zwischenspeicherung beim Auftreten der Ereignisse – die Signale werden direkt von Eingang zu Ausgang durchgereicht.

## Anwendungsszenarien
- **Sensorwertübertragung:** Ein Funktionsblock erfasst einen analogen Sensorwert (z.B. Temperatur, Druck) und sendet diesen über AR2 an einen Auswerteblock. Gleichzeitig kann der Auswerteblock über die Gegenrichtung einen Sollwert zurückgeben.
- **Regelungskopplung:** In einer modularen Steuerung verbindet AR2 einen PID-Regler mit einem Stellglied. Der Regler sendet den Stellwert (REAL) und empfängt gleichzeitig die aktuelle Regelabweichung.
- **Parametrierung:** Über AR2 können Konfigurationsparameter (z.B. Grenzwerte) zwischen einem Bediengerät und der Steuerungslogik ausgetauscht werden.

## Vergleich mit ähnlichen Bausteinen
- **AR1 (unidirektional):** Ein Adapter, der Daten nur in eine Richtung überträgt. AR2 hingegen ermöglicht bidirektionalen Austausch, was den Verkabelungsaufwand reduziert.
- **AE2 (Adapter Event 2-Wege):** Überträgt zwei Ereignisse, aber keine Daten. AR2 kombiniert ein Ereignis mit einem REAL-Wert – ideal für wertbasierte Kommunikation.
- **AR4 (Adapter Real 4-Wege):** Bietet vier voneinander unabhängige REAL-Kanäle. AR2 ist kompakter, wenn nur ein Wert benötigt wird.

## Fazit
Der AR2-Adapter ist ein eleganter Baustein für die bidirektionale Übertragung eines REAL-Werts mit zugehörigem Ereignis. Seine klare Schnittstelle und die einfache Handhabung machen ihn besonders geeignet für modulare Automatisierungslösungen, bei denen Messdaten oder Steuergrößen zwischen Funktionsblöcken ausgetauscht werden müssen. Durch die Einhaltung des 61499‑Standards und die Lizenz unter EPL 2.0 ist AR2 offen und erweiterbar.
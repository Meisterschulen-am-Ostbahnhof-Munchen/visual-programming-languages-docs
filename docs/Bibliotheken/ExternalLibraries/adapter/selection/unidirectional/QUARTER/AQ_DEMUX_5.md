# AQ_DEMUX_5


![AQ_DEMUX_5](./AQ_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AQ_DEMUX_5** realisiert einen 1-zu-5 Demultiplexer für Adapter des Typs `AQ` (unidirektional). Er leitet eingehende Daten von einem zentralen Adaptereingang wahlweise an einen von fünf Ausgängen weiter. Die Auswahl des Zielausgangs erfolgt über den Index `K`. Der Baustein ist als generischer Typ (`GEN_AQ_DEMUX`) definiert und kann dadurch in verschiedenen Umgebungen wiederverwendet werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Startet die Weiterleitung des aktuellen Werts aus dem Eingangsadapter `IN` an den durch `K` bestimmten Ausgang. |

### **Ereignis-Ausgänge**
| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Quittiert die erfolgreiche Ausführung der Demultiplex-Operation. |

### **Daten-Eingänge**
| Name | Typ   | Kommentar                 |
|------|-------|---------------------------|
| `K`  | `UINT`| Index des gewünschten Ausgangs (1..5). |

### **Daten-Ausgänge**
– Keine eigenen Datenausgänge; die Ausgabe erfolgt über die Adapter-Plugs.

### **Adapter**
| Richtung | Name  | Typ                               | Kommentar                            |
|----------|-------|-----------------------------------|--------------------------------------|
| Socket (Eingang) | `IN`  | `adapter::types::unidirectional::AQ` | Eingangsdaten, die demultiplext werden. |
| Plug (Ausgang)   | `OUT1`| `adapter::types::unidirectional::AQ` | Erster Ausgangskanal.                |
| Plug (Ausgang)   | `OUT2`| `adapter::types::unidirectional::AQ` | Zweiter Ausgangskanal.               |
| Plug (Ausgang)   | `OUT3`| `adapter::types::unidirectional::AQ` | Dritter Ausgangskanal.               |
| Plug (Ausgang)   | `OUT4`| `adapter::types::unidirectional::AQ` | Vierter Ausgangskanal.               |
| Plug (Ausgang)   | `OUT5`| `adapter::types::unidirectional::AQ` | Fünfter Ausgangskanal.               |

## Funktionsweise
1. **Eingangssignalbereitstellung:** Der angeschlossene Socket `IN` liefert kontinuierlich Daten eines unidirektionalen `AQ`-Kanals.  
2. **Auslösung:** Ein Ereignis am Eingang `REQ` startet die Demultiplex-Operation. Dabei wird der aktuelle Wert des Index `K` ausgelesen.  
3. **Weiterleitung:** Der FB verbindet intern den Eingang `IN` mit dem durch `K` referenzierten Ausgangsadapter (`OUT1` … `OUT5`). Die Daten werden **einmalig** an den gewählten Ausgang propagiert.  
4. **Bestätigung:** Nach erfolgreicher Übertragung wird ein Ereignis am Ausgang `CNF` gesendet, um dem aufrufenden Baustein die Fertigstellung zu signalisieren.

> **Hinweis:** Der Index `K` muss im gültigen Bereich `1 … 5` liegen. Werte außerhalb dieses Bereichs werden ignoriert oder führen zu einem undefinierten Verhalten – je nach konkreter Implementierung.

## Technische Besonderheiten
- **Generischer Typ:** Der FB trägt das Attribut `GenericClassName` mit dem Wert `'GEN_AQ_DEMUX'` und kann daher als Basis für ähnliche Demultiplexer mit anderer Kanalzahl dienen.
- **Typ-Hash:** Ein eindeutiger Hash (`TypeHash`) wird vom Entwicklungwerkzeug verwaltet und dient der Versionskontrolle und Identifikation des Bausteins.
- **Unidirektionale Adapter:** Alle beteiligten Adapter sind vom Typ `adapter::types::unidirectional::AQ`, d.h. Daten fließen nur in eine Richtung (vom Eingang zu den Ausgängen). Eine Rückmeldung von den Ausgängen ist nicht vorgesehen.

## Zustandsübersicht
Der FB durchläuft intern zwei Hauptzustände:

| Zustand   | Beschreibung                                     |
|-----------|--------------------------------------------------|
| **IDLE**  | Warten auf ein `REQ`-Ereignis.                   |
| **BUSY**  | Aktuelle Demultiplex-Operation wird ausgeführt.  |
| **DONE**  | Operation abgeschlossen; `CNF` wird gesendet; Rücksprung zu **IDLE**. |

Der Übergang von **IDLE** zu **BUSY** erfolgt durch ein `REQ`-Ereignis. Nach erfolgreicher Weiterleitung wechselt der FB kurzzeitig in den Zustand **DONE** und sendet `CNF`, bevor er wieder in **IDLE** zurückkehrt.

## Anwendungsszenarien
- **Kanalumschaltung:** Verteilen eines analogen Messwerts (z.B. Temperatur, Druck) an verschiedene übergeordnete Steuerungen, wobei der Zielkanal zur Laufzeit umgeschaltet wird.
- **Datenrouting:** Weiterleitung eines seriellen Datenstroms (z.B. Modbus-RTU über Adapter) an wechselnde Endgeräte in Abhängigkeit von einer Indexvorgabe.
- **Test- und Simulationsumgebungen:** Verfahren zum zyklischen Aktivieren verschiedener Ausgänge, indem der Index `K` schrittweise erhöht wird.

## Vergleich mit ähnlichen Bausteinen
- **AQ_DEMUX_N** (andere Ausgangsanzahl): Bausteine wie `AQ_DEMUX_2`, `AQ_DEMUX_8` unterscheiden sich nur durch die Anzahl der Ausgangsadapter. Der hier beschriebene `AQ_DEMUX_5` bietet genau fünf Kanäle.
- **AQ_MUX_5 (Multiplexer)**: Ein Multiplexer kehrt die Richtung um – er liest aus mehreren Eingängen einen aus und gibt einen Wert aus. Der Demultiplexer verteilt dagegen einen Eingang auf mehrere Ausgänge.
- **Unidirektionale vs. bidirektionale Demultiplexer**: Bidirektionale Varianten (z.B. `AQ_BI_DEMUX`) erlauben auch Datenfluss von einem Ausgang zurück zum Eingang, was hier nicht der Fall ist.

## Fazit
Der `AQ_DEMUX_5` ist ein spezialisierter Funktionsblock zur punktuellen Verteilung unidirektionaler `AQ`-Daten auf fünf Kanäle. Sein generischer Aufbau erleichtert die Wiederverwendung in unterschiedlichen Steuerungssystemen. Die klare Ereignissteuerung (REQ/CNF) und die einfache Indizierung machen ihn zu einem zuverlässigen Element für Anwendungen, die eine dynamische Kanalwahl erfordern.
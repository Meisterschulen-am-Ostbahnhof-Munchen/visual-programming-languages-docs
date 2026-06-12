# ADI_DEMUX_4


![ADI_DEMUX_4](./ADI_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ADI_DEMUX_4` ist ein generischer Demultiplexer, der einen eingehenden Datenwert über einen unidirektionalen Adapter (Socket) auf einen von vier Ausgangsadaptern (Plugs) verteilt. Die Auswahl des Zielausgangs erfolgt über einen Index-Eingang. Der Baustein wird typischerweise in der industriellen Automatisierung eingesetzt, um Signalwege dynamisch umzuschalten oder Daten an verschiedene Verbraucher zu routen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| REQ | Event | Ereignis zur Ausführung der Demultiplex-Operation; löst die Verarbeitung des Index `K` aus |

### **Ereignis-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| CNF | Event | Bestätigung, dass der Demultiplex-Vorgang abgeschlossen ist |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| K | UINT | Index (1‑basiert) für die Auswahl des Zielausgangs (1→OUT1, 2→OUT2, 3→OUT3, 4→OUT4) |

### **Daten-Ausgänge**
_Keine_

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|-------------|
| Socket | IN | ADI (unidirektional) | Eingangsadapter, über den der zu verteilende Datenwert anliegt |
| Plug | OUT1 | ADI (unidirektional) | Erster Ausgangsadapter |
| Plug | OUT2 | ADI (unidirektional) | Zweiter Ausgangsadapter |
| Plug | OUT3 | ADI (unidirektional) | Dritter Ausgangsadapter |
| Plug | OUT4 | ADI (unidirektional) | Vierter Ausgangsadapter |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Nach Eintreffen von `REQ` wird der aktuelle Wert des Index `K` ausgelesen.
3. Der über den Socket `IN` bereitgestellte Datenwert (z. B. ein `INT`, `REAL` oder benutzerdefinierter Typ – abhängig von der konkreten Adapter-Instanziierung) wird an den durch `K` adressierten Ausgangsadapter (`OUT1`, `OUT2`, `OUT3` oder `OUT4`) weitergeleitet.
4. Anschließend wird das Ereignis `CNF` ausgegeben, um den erfolgreichen Abschluss zu signalisieren.

> **Hinweis:** Der Index `K` wird als vorzeichenlose Ganzzahl interpretiert. Werte außerhalb des Bereichs 1…4 führen zu undefiniertem Verhalten – in einer robusten Implementierung sollte der aufrufende Baustein für gültige Indizes sorgen.

## Technische Besonderheiten

- **Generischer Typ:** Der FB ist als generischer Baustein (`eclipse4diac::core::GenericClassName = 'GEN_ADI_DEMUX'`) ausgelegt. Er kann in Verbindung mit verschiedenen Datenadaptern (z. B. für `INT`, `REAL`, `BOOL`) parametrisiert werden, ohne dass die Logik selbst angepasst werden muss.
- **Unidirektionale Adapter:** Alle Adapter sind unidirektional ausgelegt – die Daten fließen nur vom Socket `IN` zu einem der Plugs. Dies ermöglicht lose Kopplung und einfache Austauschbarkeit der Datenquellen und -senken.
- **Ereignisgesteuerte Ausführung:** Die Demultiplex-Operation wird nur durch das `REQ`-Ereignis ausgelöst. Es existiert kein kontinuierlicher Datenstrom; der Baustein arbeitet streng nach dem ereignisgesteuerten Paradigma der IEC 61499.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände. Das Verhalten kann als einfacher Ablauf beschrieben werden:

- **Start:** Warten auf `REQ`.
- **REQ empfangen:** Auslesen von `K`, Weiterleitung des `IN`-Werts an den entsprechenden `OUTn`-Plug, Ausgabe von `CNF`.
- **Rückkehr zum Wartezustand.**

## Anwendungsszenarien

- **Signalverteilung:** Ein Sensor liefert Messwerte über einen ADI-Adapter. Je nach Betriebsmodus (Index `K`) werden die Werte an verschiedene Aktoren oder Steuerungslogiken weitergeleitet.
- **Prozessumschaltung:** In einer Mehrprozessanlage kann derselbe Dateneingang wahlweise an unterschiedliche Verarbeitungsstationen geroutet werden.
- **Diagnose & Test:** Ein zentraler Datenstrom wird auf verschiedene Test- oder Überwachungsblöcke umgeschaltet, ohne dass die Verdrahtung geändert werden muss.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied |
|----------|--------------|-------------|
| `ADI_MUX_4` | Multiplexer – sammelt Daten von vier Eingängen und leitet sie über einen Ausgang weiter | Richtung umgekehrt (mehrere Eingänge → ein Ausgang) |
| `DEMUX_2` / `DEMUX_8` | Demultiplexer mit anderer Kanalzahl | `ADI_DEMUX_4` bietet genau vier Ausgänge; andere Varianten passt man durch eigene Adapter oder generische Parameter an |
| `SELECT` (IEC‑Standard) | Auswahl zwischen zwei Werten (boolesche Steuerung) | Arbeitet mit einfachen Datentypen, nicht mit Adaptern; weniger flexibel hinsichtlich unterschiedlicher Datenquellen |

## Fazit

Der `ADI_DEMUX_4` ist ein kompakter, generischer Demultiplexer für die ereignisgesteuerte Verteilung von Adapterdaten. Dank der unidirektionalen Adapter‑Schnittstelle und der generischen Auslegung eignet er sich hervorragend für modulare Automatisierungslösungen, bei denen Datenflüsse dynamisch umgeschaltet werden müssen. Die einfache Schnittstelle – ein Ereignis, ein Index und fünf Adapter – ermöglicht eine unkomplizierte Integration in größere Steuerungssysteme.
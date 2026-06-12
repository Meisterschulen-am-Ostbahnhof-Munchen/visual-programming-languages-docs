# AR_DEMUX_3


![AR_DEMUX_3](./AR_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AR_DEMUX_3** ist ein generischer Demultiplexer für unidirektionale Adapter vom Typ `adapter::types::unidirectional::AR`. Er verteilt einen eingehenden Adapter-Datenstrom (über den Socket `IN`) auf einen von drei Ausgangsadaptern (`OUT1`, `OUT2`, `OUT3`), abhängig von einem Indexwert `K`. Der Baustein wird über ein Ereignis `REQ` gesteuert und bestätigt die Operation mit `CNF`. Dies ermöglicht eine flexible und dynamische Signalweiterleitung in adapterbasierten IEC 61499 Applikationen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Demultiplex-Operation. Der Datenwert `K` wird ausgewertet, um die Verbindung zwischen `IN` und einem der drei Ausgänge herzustellen. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigt die erfolgreiche Durchführung der Demultiplex-Aktion nach Verarbeitung von `REQ`. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| `K`  | `UINT` | Index (1–3), der festlegt, welcher Ausgang (`OUT1` bis `OUT3`) mit dem Eingangsadapter `IN` verbunden wird. Werte außerhalb des gültigen Bereichs führen zu keiner Verbindung. |

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|------|----------|--------------|
| `IN` | `adapter::types::unidirectional::AR` | Socket | Eingangsadapter, der die zu verteilenden Daten bereitstellt. |
| `OUT1` | `adapter::types::unidirectional::AR` | Plug | Erster Ausgangsadapter (Index 1). |
| `OUT2` | `adapter::types::unidirectional::AR` | Plug | Zweiter Ausgangsadapter (Index 2). |
| `OUT3` | `adapter::types::unidirectional::AR` | Plug | Dritter Ausgangsadapter (Index 3). |

## Funktionsweise
Der Funktionsblock verhält sich wie ein 1‑zu‑N‑Demultiplexer auf Adapterebene. Beim Eintreffen eines `REQ`-Ereignisses wird der aktuelle Wert des Index `K` ausgelesen. Abhängig von `K` wird die logische Verbindung zwischen dem Socket `IN` und dem entsprechenden Plug (`OUT1`, `OUT2` oder `OUT3`) aktiviert. Anschließend wird das Ausgangsereignis `CNF` gesendet, um die erfolgreiche Umschaltung zu quittieren. Die nicht ausgewählten Ausgänge bleiben inaktiv.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AR_DEMUX`) deklariert und kann für verschiedene Ausgangszahlen (hier 3) wiederverwendet werden.
- **Adapter‑basierte Kommunikation**: Der Datenaustausch erfolgt ausschließlich über unidirektionale Adapter des Typs `AR`. Dies ermöglicht eine lose Kopplung und einfache Wiederverwendung der Schnittstellen.
- **Keine Datenausgänge**: Die gesamte Datenweitergabe geschieht über die Adapter, nicht über separate Variablen.
- **Wertebereich von K**: Der Index `K` vom Typ `UINT` sollte auf die Werte 1 bis 3 beschränkt werden, um eine definierte Zuordnung zu gewährleisten.

## Zustandsübersicht
Da es sich um einen service‑orientierten generischen FB handelt, wird keine explizite Zustandsmaschine in der XML‑Definition mitgeliefert. Die Funktionsweise lässt sich jedoch auf zwei logische Zustände reduzieren:

1. **IDLE**: Warten auf ein `REQ`-Ereignis. Alle Ausgangsadapter sind von `IN` getrennt.
2. **ACTIVE**: Nach Eintreffen von `REQ` wird der Index `K` ausgewertet und die Verbindung hergestellt. Nach dem Senden von `CNF` kehrt der FB sofort in den IDLE‑Zustand zurück.

## Anwendungsszenarien
- **Datenverteilung in Steuerungssystemen**: Auswahl eines Zielgeräts oder einer Steuerungseinheit aus mehreren identisch aufgebauten Adaptern.
- **Umschaltung von Signalquellen**: In Leitsystemen kann der Demux verwendet werden, um einen Messwert abwechselnd an verschiedene Anzeigen oder Verarbeitungsblöcke weiterzuleiten.
- **Prototypen‑ und Testumgebungen**: Schnelle Konfiguration von Datenpfaden ohne Änderung der Netzwerktopologie.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu klassischen IEC 61439‑Demultiplexern (z. B. `DEMUX_BOOL`, `DEMUX_INT`) arbeitet der `AR_DEMUX_3` auf Adapterebene. Während konventionelle Demultiplexer einzelne Datenwerte auf mehrere Ausgangsvariablen verteilen, überträgt dieser Baustein komplette Adapterschnittstellen. Dies reduziert die Verdrahtung und erhöht die Abstraktion. Ähnliche Blöcke wie ein `MUX_3` (Multiplexer) arbeiten umgekehrt und fassen mehrere Adaptereingänge auf einen Ausgang zusammen.

## Fazit
Der `AR_DEMUX_3` ist ein spezialisierter, aber flexibler Baustein zur dynamischen Verteilung von Adapterverbindungen in IEC‑61499‑Systemen. Seine generische Natur und die einfache Indexsteuerung machen ihn ideal für modulare Automatisierungslösungen, bei denen ein Datenpfad auf verschiedene Empfänger geschaltet werden muss. Die Verwendung von unidirektionalen AR‑Adaptern gewährleistet dabei eine klare Trennung von Steuerung und Datenfluss.
# AI_DEMUX_3


![AI_DEMUX_3](./AI_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_DEMUX_3** realisiert einen generischen Demultiplexer für einen analogen Eingangswert. Anhand eines Indexparameters wird der am Adapter-Eingang anliegende Wert auf einen von drei Adapter-Ausgängen umgeleitet. Der Baustein arbeitet unidirektional und ereignisgesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Übernimmt den Index **K** und leitet den aktuellen Wert des Adapter-Eingangs **IN** auf den entsprechenden Adapter-Ausgang (**OUT1**, **OUT2** oder **OUT3**) um. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigt die erfolgreiche Weiterleitung nach Bearbeitung eines **REQ**-Ereignisses. |

### **Daten-Eingänge**
| Name | Typ  | Beschreibung |
|------|------|--------------|
| K    | UINT | Index zur Auswahl des Ausgangs (gültige Werte: 1, 2, 3). |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden – die Ausgabe erfolgt ausschließlich über die Adapter-Ausgänge.

### **Adapter**
| Typ   | Name  | Richtung | Beschreibung |
|-------|-------|----------|--------------|
| AI    | IN    | Socket   | Eingangsadapter für den zu verteilenden analogen Wert. |
| AI    | OUT1  | Plug     | Erster Ausgangsadapter. |
| AI    | OUT2  | Plug     | Zweiter Ausgangsadapter. |
| AI    | OUT3  | Plug     | Dritter Ausgangsadapter. |

## Funktionsweise
Wird ein **REQ**-Ereignis empfangen, liest der Baustein den Index **K** aus. Der aktuelle Wert des Adapter-Eingangs **IN** wird dann auf den durch **K** bestimmten Ausgangs-Adapter übertragen:
- `K = 1` → Weiterleitung nach **OUT1**
- `K = 2` → Weiterleitung nach **OUT2**
- `K = 3` → Weiterleitung nach **OUT3**

Nach erfolgter Übertragung wird das **CNF**-Ereignis ausgelöst. Bei ungültigen Werten von **K** (ungleich 1–3) wird die Anfrage ignoriert oder kein Ausgang aktiviert; die Dokumentation des Herstellers gibt hierzu das genaue Verhalten vor.

## Technische Besonderheiten
- **Generischer Baustein:** Der Funktionsblock ist als generischer Typ (`GEN_AI_DEMUX`) definiert und kann für unterschiedliche Adapter-Instanzen des Typs `adapter::types::unidirectional::AI` verwendet werden.
- **Unidirektionale Adapter:** Alle Adapter (sowohl Eingang als auch Ausgänge) sind unidirektional, d.h. der Datenfluss erfolgt nur vom Socket zum Plug.
- **Keine Datenausgänge:** Die Ausgabe wird nicht über klassische Datenausgänge, sondern ausschließlich über Adapter realisiert, was eine modulare Verdrahtung mit anderen Komponenten erleichtert.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine. Seine Funktionalität ist rein ereignisgesteuert: Auf ein **REQ**-Ereignis folgt nach der Verarbeitung ein **CNF**-Ereignis. Ein interner Zustand wird nicht gespeichert.

## Anwendungsszenarien
- **Verteilung eines Messwerts** an mehrere Steuerungskomponenten, z. B. in der Landtechnik zur gleichzeitigen Versorgung mehrerer Steuergeräte mit einem analogen Sensorwert.
- **Multiplexen in Industrieanlagen**, wenn ein analoges Signal je nach Betriebsmodus verschiedenen Aktoren zugeführt werden soll.
- **Prototyping und flexible Verschaltung** in modularen Automatisierungssystemen, die auf Adapter-basierte Datenflüsse setzen.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einem klassischen **Demultiplexer-FB** mit Datenausgängen bietet der **AI_DEMUX_3** den Vorteil der Adapter-Schnittstellen. Dadurch wird die Verdrahtung auf Funktionsblockebene vereinfacht und die Wiederverwendbarkeit erhöht. Nachteile können in der geringeren Anzahl von Ausgängen (3 statt variabel) und der Bindung an den Adaptertyp **AI** liegen. Ein vergleichbarer **Demux-FB** mit generischen Datenausgängen erfordert zusätzliche Typumwandlungen.

## Fazit
Der **AI_DEMUX_3** ist ein effektiver und spezialisierter Baustein zur Verteilung analoger Werte auf bis zu drei Ausgänge. Durch die Verwendung von unidirektionalen Adaptern fügt er sich nahtlos in moderne, adapterbasierte Architekturen ein und eignet sich besonders für modulare Automatisierungslösungen, bei denen klare Schnittstellen und einfache Konfiguration gefragt sind.
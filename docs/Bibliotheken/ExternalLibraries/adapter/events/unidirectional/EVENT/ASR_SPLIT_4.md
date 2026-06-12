# ASR_SPLIT_4


![ASR_SPLIT_4](./ASR_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ASR_SPLIT_4** ist ein generischer Baustein, der einen eingehenden unidirektionalen ASR-Adapter (Antriebs-Steuerungs-Adapter) auf vier separate, identische ASR-Ausgänge verteilt. Er ermöglicht die gleichzeitige Ansteuerung von bis zu vier unabhängigen Aktoren oder Subsystemen mit demselben Signal, ohne dass die Signalintegrität beeinträchtigt wird. Der Baustein ist für den Einsatz in verteilten Automatisierungssystemen nach IEC 61499 konzipiert.

## Schnittstellenstruktur
### **Adapter-Eingänge (Sockets)**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| IN | `adapter::types::unidirectional::ASR` | Eingangs-Adapter, der die zu verteilende ASR-Verbindung bereitstellt. |

### **Adapter-Ausgänge (Plugs)**
| Name | Typ | Beschreibung |
|------|-----|-------------|
| OUT1 | `adapter::types::unidirectional::ASR` | Erster Ausgangs-Adapter (identische Kopie des Eingangs). |
| OUT2 | `adapter::types::unidirectional::ASR` | Zweiter Ausgangs-Adapter. |
| OUT3 | `adapter::types::unidirectional::ASR` | Dritter Ausgangs-Adapter. |
| OUT4 | `adapter::types::unidirectional::ASR` | Vierter Ausgangs-Adapter. |

> **Hinweis:** Der konkrete Aufbau des ASR-Adapters (Ereignis-/Daten-Elemente) ist nicht im Baustein selbst definiert, sondern wird durch den zugehörigen Adaptertyp `adapter::types::unidirectional::ASR` festgelegt. Typischerweise umfasst dieser jedoch Steuer- und Rückmeldesignale für Antriebe.

## Funktionsweise
Der ASR_SPLIT_4-Baustein arbeitet als reiner Signalverteiler: Alle über den `IN`-Socket eingehenden ASR-Verbindungselemente (Ereignisse und Daten) werden **1:1 auf alle vier Ausgangs-Plugs** (OUT1–OUT4) repliziert. Es erfolgt keine Signalverstärkung, Filterung oder logische Verarbeitung. Sobald der Eingangs-Adapter eine aktive Verbindung herstellt, wird diese sofort auf alle Ausgänge durchgeschaltet. Der Baustein benötigt keine eigene Zustandslogik – er agiert vollständig kombinatorisch.

## Technische Besonderheiten
- **Generischer Funktionsblock:** Der Baustein ist als generischer Typ (`GEN_ASR_SPLIT`) deklariert, was bedeutet, dass die Schnittstellendefinition des ASR-Adapters zur Kompilierzeit aufgelöst wird. Er kann mit verschiedenen Ausprägungen des ASR-Adapters verwendet werden, solange diese dem unidirektionalen Protokoll entsprechen.
- **Unidirektionale Signalrichtung:** Die Adapter sind als unidirectional ausgelegt, d.h. Daten fließen nur vom Eingang zu den Ausgängen (kein Rückkanal vom Ausgang zum Eingang).
- **Keine Latenzpufferung:** Alle Ausgänge werden gleichzeitig mit demselben Signal versorgt; es gibt keine zeitliche Staffelung oder Zwischenspeicherung.

## Zustandsübersicht
Der FB besitzt **keine expliziten internen Zustände**. Die Ausgänge folgen stets direkt den Eingangssignalen. Eine Zustandsmaschine ist nicht vorhanden. Das Verhalten kann als eine einzige „Durchschalt“-Operation beschrieben werden.

## Anwendungsszenarien
- **Steuerung mehrerer paralleler Antriebe:** Ein zentraler Fahrtbefehlsgeber (z.B. ein AGV-Steuerblock) verteilt das Geschwindigkeits- oder Richtungssignal auf vier unabhängige Motorcontroller.
- **Redundante Signalverteilung:** In sicherheitskritischen Systemen kann derselbe Befehl an mehrere redundante Aktuatoren gesendet werden, um Ausfallsicherheit zu gewährleisten.
- **Test- und Simulationsumgebungen:** Ein simuliertes ASR-Signal wird gleichzeitig an mehrere Testinstanzen angelegt.

## Vergleich mit ähnlichen Bausteinen
- **ASR_SPLIT_2 / ASR_SPLIT_N:** Diese Bausteine teilen den ASR-Eingang auf zwei bzw. eine beliebige Anzahl von Ausgängen auf. Der `ASR_SPLIT_4` ist eine spezielle, vierkanalige Variante.
- **Signal-Multiplexer:** Im Gegensatz zu einem echten Multiplexer, der aus mehreren Quellen auswählt, verteilt der Split-Baustein die *gleiche* Quelle auf mehrere Senken.
- **Adapter-Coupler:** Manche Bibliotheken bieten Koppel-Bausteine für die Adapter-Weiterleitung; der Split-Baustein erweitert dies um die Vervielfachung.

## Fazit
Der **ASR_SPLIT_4** ist ein einfacher, aber nützlicher Funktionsblock, der die modulare und wiederverwendbare Kopplung von ASR-Adapter-Verbindungen in IEC-61499-Systemen ermöglicht. Seine generische Implementierung erlaubt den Einsatz in verschiedenen Kontexten, in denen ein Eingangssignal auf mehrere identische Ausgangsschnittstellen verteilt werden muss. Dank des adaptiven, zustandslosen Designs fügt er sich nahtlos in ereignisgesteuerte Automatisierungsarchitekturen ein.
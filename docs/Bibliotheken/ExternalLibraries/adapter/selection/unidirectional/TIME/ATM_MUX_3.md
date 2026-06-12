# ATM_MUX_3


![ATM_MUX_3](./ATM_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ATM_MUX_3** ist ein generischer Multiplexer für ATM-Adapter (Automation Transfer Module). Er ermöglicht die selektive Durchschaltung eines von drei eingehenden ATM-Adaptern (IN1, IN2, IN3) auf einen ausgehenden ATM-Adapter (OUT). Die Auswahl des aktiven Eingangs erfolgt über den Index-Parameter K, der über das Ereignis REQ gesetzt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und löst die Umschaltung aus. |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der erfolgten Index-Setzung und Umschaltung. |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index zur Auswahl des aktiven Eingangs (0 für IN1, 1 für IN2, 2 für IN3). |

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (OUT) | OUT | adapter::types::unidirectional::ATM | Ausgangs-Adapter, der je nach K mit einem der drei Sockets verbunden wird. |
| Socket (IN1) | IN1 | adapter::types::unidirectional::ATM | Erster Eingangs-Adapter (für K=0). |
| Socket (IN2) | IN2 | adapter::types::unidirectional::ATM | Zweiter Eingangs-Adapter (für K=1). |
| Socket (IN3) | IN3 | adapter::types::unidirectional::ATM | Dritter Eingangs-Adapter (für K=2). |

## Funktionsweise
Der Baustein arbeitet nach dem Prinzip eines **1-aus-3-Multiplexers** für ATM-Adapter. Ein eingehendes Ereignis **REQ** übernimmt den aktuellen Wert des Daten-Eingangs **K** und schaltet daraufhin den entsprechenden Socket (IN1, IN2 oder IN3) auf den Plug **OUT** durch. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben. Die Umschaltung erfolgt ereignisgesteuert, d.h. solange kein neues REQ eintrifft, bleibt die aktuelle Verbindung bestehen.

## Technische Besonderheiten
- **Generische Realisierung**: Der FB ist als generischer Baustein (`GEN_ATM_MUX`) implementiert und kann durch Anpassung der Typ-Parameter auf andere Adapter-Typen übertragen werden.
- **Unidirektionale Adapter**: Alle beteiligten ATM-Adapter sind als unidirektionale Schnittstellen definiert. Die Flussrichtung verläuft von den Eingangs-Sockets zum Ausgangs-Plug.
- **Keine Daten-Ausgänge**: Der Baustein leitet ausschließlich die Adapter-Kommunikation weiter – es werden keine zusätzlichen Datenwerte ausgegeben.
- **Sicherheitsaspekt**: Der Index K wird nicht auf Gültigkeit geprüft. Werte außerhalb 0..2 führen zu undefiniertem Verhalten (kein gültiger Eingang ausgewählt). Der Anwender muss sicherstellen, dass K immer im zulässigen Bereich liegt.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten. Er befindet sich immer in einem von drei logischen Zuständen, die durch den zuletzt gesetzten Index K bestimmt werden:

- **Zustand 0**: OUT ist mit IN1 verbunden.
- **Zustand 1**: OUT ist mit IN2 verbunden.
- **Zustand 2**: OUT ist mit IN3 verbunden.

Ein Wechsel erfolgt ausschließlich bei Eintreffen des REQ-Ereignisses. Der Zustand bleibt bis zum nächsten REQ erhalten.

## Anwendungsszenarien
- **Alternative ATM-Quellen umschalten**: In einer Steuerungsanwendung, bei der je nach Betriebsmodus unterschiedliche Sensordaten (z.B. Temperatur, Druck, Füllstand) über einen einheitlichen Ausgangskanal weitergegeben werden sollen.
- **Redundanz und Failover**: Drei identische ATM-Adapterquellen (z.B. von verschiedenen Sensoren) können überwacht und bei Bedarf auf eine gemeinsame Ausgangsleitung geschaltet werden.
- **Test- und Simulationsumgebungen**: Umschaltung zwischen Echt- und Testdatenquellen ohne Änderung der Verkabelung.

## Vergleich mit ähnlichen Bausteinen
- **Ereignisbasierte Multiplexer für Standard-Datentypen**: Im Gegensatz zu Multiplexern, die einfache Datentypen (BOOL, INT) umschalten, arbeitet ATM_MUX_3 auf der Ebene von ATM-Adaptern – also ganzen Schnittstellen mit mehreren Signalen und Protokollen.
- **Mehrstufige Multiplexer**: Sollen mehr als drei Eingänge unterstützt werden, ist eine Kaskadierung mehrerer ATM_MUX_3-Bausteine oder ein eigenständiger FB mit größerer K-Anzahl erforderlich.
- **Adapter-Selektor (z.B. SELECT-Adapter)**: Einige Bibliotheken bieten direkt Adapter-Selektoren an, die jedoch oft keine explizite Indexsteuerung über einen Daten-Eingang besitzen, sondern nur über Ereignisse umschalten.

## Fazit
Der **ATM_MUX_3** ist ein kompakter und flexibler Baustein zur dynamischen Umschaltung von drei ATM-Adaptern auf einen gemeinsamen Ausgang. Seine einfache Handhabung über Ereignis und Index macht ihn ideal für Steuerungsanwendungen, bei denen mehrere gleichartige Quellen bedarfsgerecht angebunden werden müssen. Die generische Auslegung erlaubt eine breite Wiederverwendung in verschiedenen Projekten.
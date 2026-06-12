# AS_DEMUX_4


![AS_DEMUX_4](./AS_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_DEMUX_4** dient als Demultiplexer für einen unidirektionalen Adapter des Typs `AS`. Er leitet den an einem einzelnen Eingang anliegenden Adapter wahlweise auf einen von vier möglichen Ausgängen weiter. Die Auswahl des Zielausgangs erfolgt über einen numerischen Index, der bei einer Ereignisanforderung angegeben wird. Der Baustein ist als generischer Typ (`GEN_AS_DEMUX`) implementiert und eignet sich für den Einsatz in modularen Steuerungsarchitekturen, bei denen Datenflüsse dynamisch umgeschaltet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Anforderung zur Weiterleitung des Eingangsadapters. Der Wert von `K` legt den Zielausgang fest. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung der erfolgreichen Umschaltung. Signalisiert, dass der Adapter auf dem gewählten Ausgang bereitsteht. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `K`      | UINT  | Index des gewünschten Ausgangs (erwartet Werte 1 … 4). |

### **Daten-Ausgänge**

Keine eigenständigen Datenausgänge – die Ausgabe erfolgt ausschließlich über die Adapter-Ports.

### **Adapter**

#### Socket (Eingang)

| Adapter | Typ                                       | Beschreibung                       |
|---------|-------------------------------------------|------------------------------------|
| `IN`    | `adapter::types::unidirectional::AS`      | Eingangswert, der demultiplext wird |

#### Plugs (Ausgänge)

| Adapter | Typ                                       | Beschreibung                           |
|---------|-------------------------------------------|----------------------------------------|
| `OUT1`  | `adapter::types::unidirectional::AS`      | Erster Ausgang (Index 1)               |
| `OUT2`  | `adapter::types::unidirectional::AS`      | Zweiter Ausgang (Index 2)              |
| `OUT3`  | `adapter::types::unidirectional::AS`      | Dritter Ausgang (Index 3)              |
| `OUT4`  | `adapter::types::unidirectional::AS`      | Vierter Ausgang (Index 4)              |

## Funktionsweise

Der Baustein arbeitet als **1‑zu‑4‑Demultiplexer** auf Adapterebene. Sobald ein Ereignis am Eingang `REQ` eintrifft, wird der am Socket `IN` anliegende Adapter (einschließlich seiner gesamten Daten‑ und Ereignisschnittstelle) auf den durch die Variable `K` bestimmten Ausgangs-Port (`OUT1` … `OUT4`) geschaltet.

Dabei gilt:
- Der Wert von `K` bestimmt den Zielausgang (1‑basiert).
- Nur der ausgewählte Ausgang erhält eine Verbindung zum Eingang; alle anderen Ausgänge bleiben inaktiv oder behalten ihren letzten Zustand (abhängig von der konkreten Adapter‑Implementierung).
- Nach erfolgter Umschaltung wird das Bestätigungsereignis `CNF` ausgelöst.

Die Kopplung zwischen Ereignis- und Datenpfad ist über das `With`-Attribut von `REQ` sichergestellt: `K` wird zusammen mit dem Ereignis ausgewertet.

## Technische Besonderheiten

- **Generische Auslegung**: Der FB ist als generischer Typ (`GEN_AS_DEMUX`) definiert. Dadurch kann er für beliebige Adapter‑Instanzen des unidirektionalen `AS`‑Typs wiederverwendet werden, ohne dass der Quellcode angepasst werden muss.
- **Indexbereich**: Wird ein Wert außerhalb des gültigen Bereichs (1 … 4) für `K` übergeben, ist das Verhalten undefiniert. Der Baustein führt keine Bereichsprüfung durch. Der Anwender ist für die Validierung des Indexes verantwortlich.
- **Ereignisgesteuerter Betrieb**: Die Umschaltung erfolgt ausschließlich durch das `REQ`‑Ereignis. Ein statischer Wechsel des Indexes ohne Ereignis hat keine Wirkung.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine im XML‑Modell. Sein Verhalten ist rein reaktiv: Auf jedes `REQ`‑Ereignis folgt unmittelbar die Umschaltung und die Ausgabe von `CNF`. Es gibt keinen internen Zustand, der über eine Ereignisausführung hinaus bestehen bleibt.

| Zustand / Phase | Beschreibung |
|----------------|--------------|
| **Warten**     | Der FB erwartet ein `REQ`‑Ereignis. Der letzte Index `K` bleibt intern gespeichert, jedoch ohne Auswirkung. |
| **Umschalten** | Bei Eintreffen von `REQ` wird der Wert von `K` ausgelesen und der entsprechende Ausgang aktiviert. |
| **Bestätigen** | Nach der Umschaltung wird `CNF` gesendet, und der FB kehrt in den Wartezustand zurück. |

## Anwendungsszenarien

- **Werkzeugwechsler in der Fertigung**: Ein zentraler Sensor‑ oder Aktor‑Adapter liefert Daten, die je nach aktueller Bearbeitungsstation auf einen von vier Maschinen‑Adaptern umgeschaltet werden müssen.
- **Modulare Steuerungsarchitekturen**: Ein übergeordneter Funktionsblock wählt aus mehreren parallel konfigurierten Subsystemen dasjenige aus, mit dem kommuniziert werden soll.
- **Test‑ und Simulationsumgebungen**: Umschalten zwischen realem Prozessadapter und simuliertem Ersatzadapter, z. B. für Inbetriebnahme oder Fehlersuche.

## Vergleich mit ähnlichen Bausteinen

- **`AS_MUX_4`** (Multiplexer): Führt die umgekehrte Operation aus – mehrere Eingänge werden auf einen einzigen Ausgang geschaltet. Der AS_DEMUX_4 ergänzt diesen Baustein zu einem vollständigen Umschaltsystem.
- **`SELECT`‑FB** (IEC 61499 Standard): Wählt basierend auf einem Booleschen Eingang einen von zwei Datenpfaden aus. Der AS_DEMUX_4 arbeitet auf Adapterebene und bietet vier statt zwei Pfade, ist jedoch nicht auf einfache Datentypen beschränkt.
- **Generische Demultiplexer**: Andere Implementierungen verwenden häufig einzelne Daten‑Ereignis‑Paare. Der AS_DEMUX_4 nutzt Adapter, wodurch komplexe Schnittstellen (Ereignisse + Daten) in einem Rutsch umgeschaltet werden können.

## Fazit

Der **AS_DEMUX_4** ist ein kompakter, generischer Funktionsblock zur dynamischen Verteilung eines unidirektionalen `AS`‑Adapters auf bis zu vier Ausgänge. Seine ereignisgesteuerte Auswahl über einen numerischen Index macht ihn vielseitig einsetzbar in modularen Steuerungssystemen. Durch die Verwendung von Adaptern werden nicht nur Daten, sondern auch die zugehörigen Ereignispfade umgeschaltet, was eine saubere und kapselnde Schnittstellenstruktur ermöglicht. Eine Validierung des Indexes muss außerhalb des Bausteins erfolgen.
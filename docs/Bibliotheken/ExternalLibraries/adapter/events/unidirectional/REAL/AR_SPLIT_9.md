# AR_SPLIT_9


![AR_SPLIT_9](./AR_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_SPLIT_9** teilt einen eingehenden AR‑Adapter (Typ `unidirectional`) in neun separate AR‑Ausgänge auf. Er dient als Verteiler für ein AR‑Signal an mehrere nachgeschaltete Komponenten. Der Baustein ist vollständig generisch ausgelegt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis‑Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis‑Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten‑Eingänge vorhanden.

### **Daten-Ausgänge**
Keine Daten‑Ausgänge vorhanden.

### **Adapter**
| Richtung | Adapter | Typ | Beschreibung |
|----------|---------|-----|--------------|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AR` | Eingehendes AR‑Signal, das verteilt wird. |
| **Plug** (Ausgang) | `OUT1` … `OUT9` | `adapter::types::unidirectional::AR` | Neun identische Ausgänge, die das eingehende AR‑Signal weiterleiten. |

## Funktionsweise
Der Baustein leitet das am **IN**‑Socket anliegende AR‑Signal unverändert an alle neun Ausgänge **OUT1** bis **OUT9** weiter. Es findet keine Verzögerung, Filterung oder Umwandlung statt. Die Signalausbreitung erfolgt rein kombinatorisch.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB verwendet ein generisches Class‑Name‑Attribut (`eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AR_SPLIT'`) und ein Typ‑Hash‑Attribut, um eine flexible Typanpassung im IEC 61499‑Modell zu ermöglichen.
- **Unidirektionale Adapter**: Sowohl der Eingang als auch alle Ausgänge sind als unidirektionale AR‑Adapter definiert. Eine Rückkopplung oder bidirektionale Kommunikation ist nicht vorgesehen.
- **Keine Ereignisse oder Daten**: Die gesamte Logik erfolgt ausschließlich über Adapter‑Schnittstellen – Ereignis‑ oder Daten‑Ein‑/Ausgänge sind nicht vorhanden.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand (keine Zustandsmaschine). Das Ausgangssignal entspricht zu jedem Zeitpunkt dem aktuellen Eingangssignal. Es gibt keine Initialisierungs‑ oder Fehlerzustände.

## Anwendungsszenarien
- **Verteilung eines Start‑/Stopp‑Signals**: Ein zentraler AR‑Befehl (z. B. „Start“) wird auf mehrere Aktoren oder Maschinenteile verteilt.
- **Multicast‑Kopplung**: Ein AR‑Signal, das von einer übergeordneten Steuerung kommt, wird gleichzeitig an mehrere untergeordnete Module gesendet.
- **Parallele Ansteuerung** von neun identischen oder unterschiedlichen Komponenten, die dasselbe AR‑Protokoll verwenden.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Anzahl Ausgänge | Bemerkung |
|----------|------------------|-----------|
| `AR_SPLIT_4` | 4 | Gleiche Funktionsweise, aber nur vier Ausgänge. |
| `AR_SPLIT_9` | 9 | Vorliegender Baustein (neun Ausgänge). |
| `AR_SPLIT_2` | 2 | Minimaler Splitter für zwei Pfade. |

Die Bausteine unterscheiden sich lediglich in der Anzahl der Ausgänge; die Funktionsweise und die generische Eigenschaft sind identisch.

## Fazit
Der **AR_SPLIT_9** ist ein einfacher, aber hilfreicher Verteilerbaustein für unidirektionale AR‑Signale. Aufgrund seiner generischen Auslegung kann er flexibel in unterschiedlichen Steuerungsarchitekturen eingesetzt werden, ohne dass eine Typanpassung von Hand erforderlich ist. Er eignet sich besonders für Szenarien, in denen ein Signal auf viele Pfade gleichzeitig dupliziert werden muss.
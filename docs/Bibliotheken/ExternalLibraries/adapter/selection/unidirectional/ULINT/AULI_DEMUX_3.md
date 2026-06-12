# AULI_DEMUX_3


![AULI_DEMUX_3](./AULI_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_DEMUX_3** realisiert einen generischen Demultiplexer für unidirektionale AULI‑Adapter. Er leitet einen eingehenden Wert (über den Socket `IN`) an einen der drei Ausgangsadapter (`OUT1`, `OUT2`, `OUT3`) weiter, wobei die Auswahl durch den Index `K` gesteuert wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Beschreibung             | Mit Variablen |
|------|-------|--------------------------|---------------|
| REQ  | Event | Setzt den Index K und löst die Weiterleitung aus | K (UINT) |

### **Ereignis-Ausgänge**
| Name | Typ   | Beschreibung                      |
|------|-------|-----------------------------------|
| CNF  | Event | Bestätigung der erfolgten Weiterleitung |

### **Daten-Eingänge**
| Name | Typ  | Beschreibung                 |
|------|------|------------------------------|
| K    | UINT | Index des Zielausgangs (1..3) |

### **Daten-Ausgänge**
Keine eigenen Datenausgänge. Die Daten werden über die Adapter‑Plugs übertragen.

### **Adapter**
**Plugs** (Ausgänge):
- `OUT1`: Typ `adapter::types::unidirectional::AULI`
- `OUT2`: Typ `adapter::types::unidirectional::AULI`
- `OUT3`: Typ `adapter::types::unidirectional::AULI`

**Socket** (Eingang):
- `IN`: Typ `adapter::types::unidirectional::AULI` – Eingangswert, der demultiplext werden soll.

## Funktionsweise
1. Der Baustein befindet sich im Ruhezustand und wartet auf ein Ereignis am **REQ**‑Eingang.
2. Mit dem Ereignis **REQ** wird der aktuelle Wert des Index‑Parameters `K` ausgelesen. `K` muss im Bereich 1 bis 3 liegen (die Anzahl der Ausgangsadapter).
3. Der aktuell am Socket `IN` anliegende Wert des AULI‑Adapters wird an den durch `K` bestimmten Plug (`OUT1`, `OUT2` oder `OUT3`) weitergeleitet.
4. Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.
   > Hinweis: Bei ungültigen Indexwerten (z. B. 0 oder >3) ist das Verhalten nicht spezifiziert; in der Praxis sollte die Applikation nur gültige Werte bereitstellen.

## Technische Besonderheiten
- **Generischer Baustein**: Die tatsächliche Implementierung wird durch das Attribut `GenericClassName` als `'GEN_AULI_DEMUX'` identifiziert. Dies erlaubt eine flexible Anpassung der Anzahl der Ausgänge durch Parametrierung.
- **Unidirektionale Adapter**: Alle AULI‑Adapter sind als `unidirectional` deklariert, d.h. die Datenflüsse erfolgen nur in eine Richtung (vom Socket zu den Plugs).
- **Keine Zustandsmaschine**: Der Baustein besitzt keine explizite ECC (Execution Control Chart); die Abarbeitung erfolgt ereignisgesteuert und deterministisch.

## Zustandsübersicht
Da keine Zustandsmaschine im XML definiert ist, kann die interne Logik als einfacher Ablauf ohne mehrfache Zustände betrachtet werden:
- **Warten**: Nach Initialisierung oder nach **CNF** wird auf das nächste **REQ** gewartet.
- **Verarbeitung**: Bei Eintreffen von **REQ** wird die Weiterleitung durchgeführt und unmittelbar **CNF** erzeugt.

## Anwendungsszenarien
- **Signalverteilung**: Ein von einer Quelle kommender AULI‑Wert (z. B. ein Sensorwert) soll wahlweise auf verschiedene Aktoren oder Verarbeitungseinheiten geschaltet werden.
- **Kanalumschaltung**: In einer Steuerung können unterschiedliche Betriebsmodi durch die Wahl des Ausgangskanals realisiert werden.
- **Test- und Simulationsumgebungen**: Ein generischer Demultiplexer erlaubt es, Datenströme gezielt an verschiedene Analyse‑ oder Logging‑Module zu leiten.

## Vergleich mit ähnlichen Bausteinen
- **AULI_MUX** (Multiplexer): Führt die umgekehrte Funktion aus – wählt einen von mehreren Eingängen und leitet ihn an einen gemeinsamen Ausgang.
- **AULI_SELECT**: Oft ein spezialisierterer Baustein mit fester Anzahl von Kanälen; `AULI_DEMUX_3` ist explizit für drei Kanäle ausgelegt.
- **Generische Demultiplexer**: Die generische Natur des Bausteins erlaubt es, die Kanalanzahl (z. B. `AULI_DEMUX_N`) durch Parametrierung zu ändern, ohne den Baustein neu zu erstellen.

## Fazit
Der **AULI_DEMUX_3** ist ein einfacher, aber nützlicher Funktionsblock zur gezielten Verteilung eines AULI‑Werts auf drei Ausgänge. Seine generische Architektur und die klare ereignisgesteuerte Schnittstelle machen ihn zu einem flexiblen Werkzeug in der Automatisierungstechnik, insbesondere wenn es um die Kanalumschaltung oder Signalverteilung geht.
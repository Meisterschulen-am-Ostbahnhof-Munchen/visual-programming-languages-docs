# AB_DEMUX_5


![AB_DEMUX_5](./AB_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AB_DEMUX_5** ist ein generischer AB-Demultiplexer mit fünf Ausgängen. Er empfängt über einen einzigen AB-Adapter-Socket einen Datenwert und leitet diesen wahlweise an einen der fünf AB-Adapter-Plugs weiter. Die Auswahl des Zielausgangs erfolgt über einen Index, der über den Ereigniseingang **REQ** zusammen mit dem Datenwert **K** gesetzt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Stößt die Demultiplex-Operation an; übernimmt den Index **K** und gibt den Wert am entsprechenden Ausgangsadapter weiter. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigt die erfolgreiche Durchführung der Demultiplex-Operation. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| K    | UINT     | Index, der den Zielausgang (1–5) festlegt. |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge – die Ausgabe erfolgt über die Adapter-Plugs.

### **Adapter**
**Socket (Eingang):**

| Name | Adaptertyp | Beschreibung |
|------|------------|--------------|
| IN   | adapter::types::unidirectional::AB | Wert, der demultiplext werden soll. |

**Plugs (Ausgänge):**

| Name | Adaptertyp | Beschreibung |
|------|------------|--------------|
| OUT1 | adapter::types::unidirectional::AB | Zielausgang bei K = 1 |
| OUT2 | adapter::types::unidirectional::AB | Zielausgang bei K = 2 |
| OUT3 | adapter::types::unidirectional::AB | Zielausgang bei K = 3 |
| OUT4 | adapter::types::unidirectional::AB | Zielausgang bei K = 4 |
| OUT5 | adapter::types::unidirectional::AB | Zielausgang bei K = 5 |

## Funktionsweise
1. Der Baustein erwartet am Socket **IN** einen gültigen Wert des AB-Adapters.
2. Sobald das Ereignis **REQ** eintrifft, wird der am Eingang **K** anliegende Index ausgewertet.
3. Der Wert von **IN** wird auf den Plug **OUTX** (X = K) übertragen. Für K = 1 wird OUT1 bedient, für K = 2 OUT2 usw.
4. Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.
5. Falls K außerhalb des Bereichs 1–5 liegt, ist das Verhalten nicht spezifiziert – typischerweise wird keine Ausgabe aktualisiert und CNF bleibt aus.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (siehe Attribut `GenericClassName = 'GEN_AB_DEMUX'`) deklariert und kann für verschiedene AB-Adapter-Varianten instanziiert werden.
- **Adapter-basiert**: Der Datenaustausch erfolgt ausschließlich über Adapter (unidirektionaler AB-Typ), nicht über klassische Datenports.
- **Kein ECC hinterlegt**: Die Logik ist implizit – der Baustein führt bei jedem REQ sofort die Demultiplex-Operation aus, ohne expliziten Zustandsautomaten.
- **Einfaches Index-Schema**: Der Index K wird direkt als 1‑basierte Nummer der Ausgänge interpretiert.

## Zustandsübersicht
Der Baustein besitzt keinen offengelegten Zustandsautomaten. Das interne Verhalten lässt sich wie folgt beschreiben:

- **Bereit**: Warten auf REQ.
- **Verarbeitung**: Nach REQ wird K gelesen und der Wert von IN zum passenden OUT weitergeleitet.
- **Bestätigung**: Senden von CNF.

Mögliche Fehlerzustände (ungültiger Index) sind nicht definiert; dies sollte durch den Aufrufer vermieden werden.

## Anwendungsszenarien
- **Aktorauswahl**: Ein Sensorwert (z. B. AB‑Daten) soll wahlweise an eine von fünf Maschinen übergeben werden.
- **Signalrouting**: In einer Steuerung mit mehreren parallelen Kommunikationspfaden kann der Demultiplexer verwendet werden, um einen Datenstrom auf einen von fünf Zweigen zu lenken.
- **Testumgebungen**: Simulation von Multiplex-/Demultiplex-Operationen in Verbindung mit entsprechenden Gegenbausteinen.

## Vergleich mit ähnlichen Bausteinen
- **AB_DEMUX_5 vs. AB_MUX_5**: Während der Multiplexer mehrere Eingänge auf einen Ausgang zusammenführt, verteilt der Demultiplexer einen Eingang auf mehrere Ausgänge.
- **AB_DEMUX_5 vs. AB_DEMUX_3**: Die Anzahl der Ausgänge ist die wesentliche Unterscheidung; der Demultiplexer mit drei Ausgängen hat nur die Plugs OUT1–OUT3.
- **Generische Varianten**: Durch die generische Deklaration kann derselbe Baustein in unterschiedlichen Adapter‑Kontexten (z. B. mit anderen Datenformaten) wiederverwendet werden.

## Fazit
Der AB_DEMUX_5 ist ein kompakter, generischer Demultiplexer für unidirektionale AB-Adapter. Er ermöglicht eine saubere und flexible Datenweiterleitung an bis zu fünf Ziele auf Basis eines Index und eignet sich besonders für modulare Steuerungsarchitekturen, bei denen eine Kommunikationsschnittstelle auf mehrere Aktoren aufgeteilt werden muss.
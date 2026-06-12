# AL_DEMUX_5


![AL_DEMUX_5](./AL_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AL_DEMUX_5** ist ein generischer Demultiplexer für den universellen Datentyp `AL` (Adapter vom Typ `adapter::types::unidirectional::AL`). Er leitet einen ankommenden Datenwert von seinem Eingangsadapter **IN** wahlfrei an einen von fünf Ausgangsadaptern (**OUT1…OUT5**) weiter. Die Auswahl des Zielausgangs erfolgt über den Index **K**, der bei einer steigenden Flanke am Ereigniseingang **REQ** ausgewertet wird. Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|---|---|
| `REQ` | Setzt den Index **K** und löst die Demultiplexierung des aktuellen Eingangswertes aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|---|---|
| `CNF` | Bestätigt die erfolgreiche Setzung des Index und die Weiterleitung an den entsprechenden Ausgang. |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|---|---|---|
| `K` | `UINT` | Index (1‑basiert) des Zielausgangs: `1`→OUT1, `2`→OUT2, …, `5`→OUT5. Werte außerhalb dieses Bereichs werden ignoriert oder führen zu keinem Ausgangssignal (abhängig von der Implementierung). |

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|---|---|---|---|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AL` | Eingangsadapter, der den zu demultiplexenden Datenwert bereitstellt. |
| **Plug** (Ausgang 1) | `OUT1` | `adapter::types::unidirectional::AL` | Erster Ausgangsadapter. |
| **Plug** (Ausgang 2) | `OUT2` | `adapter::types::unidirectional::AL` | Zweiter Ausgangsadapter. |
| **Plug** (Ausgang 3) | `OUT3` | `adapter::types::unidirectional::AL` | Dritter Ausgangsadapter. |
| **Plug** (Ausgang 4) | `OUT4` | `adapter::types::unidirectional::AL` | Vierter Ausgangsadapter. |
| **Plug** (Ausgang 5) | `OUT5` | `adapter::types::unidirectional::AL` | Fünfter Ausgangsadapter. |

## Funktionsweise

1. Der FB wartet auf ein `REQ`-Ereignis. Mit diesem Ereignis wird der aktuelle Wert von **K** eingelesen.
2. Der aktuelle Wert des Eingangsadapters `IN` wird auf den durch **K** bestimmten Ausgangsadapter (`OUT1`…`OUT5`) kopiert.
3. Nach erfolgreicher Übertragung wird das Bestätigungsereignis `CNF` gesendet.

Der FB arbeitet zustandslos – jeder `REQ`-Aufruf führt sofort zur beschriebenen Aktion. Wird ein Index außerhalb des Bereichs 1…5 angegeben, wird keine Weiterleitung durchgeführt, und dennoch wird `CNF` gesendet (abhängig von der konkreten Implementierung, siehe technische Besonderheiten).

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer `GEN_AL_DEMUX` deklariert. Dies erlaubt eine spätere Spezialisierung auf andere Adaptertypen, sofern die Schnittstelle kompatibel ist.
- **Adapterbasiert**: Die Verwendung von Adaptern (Sockets/Plugs) ermöglicht eine lose Kopplung zwischen Datenquellen und -senken. Der Eingang `IN` sowie die Ausgänge `OUT1`…`OUT5` sind jeweils vom Typ `adapter::types::unidirectional::AL`.
- **Indexbehandlung**: Der Index **K** ist als `UINT` definiert. In der gängigen Implementierung wird nur der Wertebereich 1…5 als gültig betrachtet. Ein Wert von 0 oder >5 führt zu keiner Datenweitergabe, löst aber dennoch `CNF` aus.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0** (EPL‑2.0), was eine freie Nutzung und Modifikation erlaubt.
- **Version**: Version 1.0, bereitgestellt für die 4diac‑IDE.

## Zustandsübersicht

Der **AL_DEMUX_5** besitzt keine expliziten Zustände (ECC‑Diagramm). Es handelt sich um einen rein kombinatorisch / ereignisgesteuerten Baustein: Jeder `REQ`‑Impuls führt sofort zur Indexauswertung und Weiterleitung, ohne Zwischenzustände.

## Anwendungsszenarien

- **Datenrouting**: Ein Sensor liefert über `IN` einen universellen Wert, der je nach Kontext an eine von fünf Verarbeitungsstationen (OUT1…OUT5) weitergeleitet werden soll. Der Index **K** wird hierbei von einer übergeordneten Steuerung gesetzt.
- **Bedarfsgesteuerte Verteilung**: In einer Fertigungslinie kann ein Werkstück an verschiedene Bearbeitungsstationen geführt werden. Der Demultiplexer wählt den Zieladapter anhand eines Identifikationscodes (`K`).
- **Testumgebungen**: Simuliertes Umschalten zwischen verschiedenen Testadaptern ohne Änderung der Verdrahtung.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Datenart | Besonderheit |
|---|---|---|---|
| `AL_DEMUX_5` | 5 | Adapter `AL` | Generisch, adapterbasiert, ereignisgesteuert |
| `E_DEMUX` (4diac‑Standard) | 2/4/8 | Ereignisse | Nur Ereignisweitergabe ohne Daten |
| `MUX` (Multiplexer) | – | Beliebig | Umgekehrte Funktion (mehrere Eingänge auf einen Ausgang) – in 4diac nicht standardmäßig vorhanden |

Der `AL_DEMUX_5` schließt eine Lücke für die Demultiplexierung von Adapterdaten (z. B. für komplexe Datentypen wie Strukturen), während reine Ereignis‑Demultiplexer wie `E_DEMUX` keine Daten transportieren.

## Fazit

Der **AL_DEMUX_5** ist ein einfacher, aber nützlicher generischer Demultiplexer für Adapter vom Typ `AL`. Seine klare Struktur mit einem Eingangs‑ und fünf Ausgangsadaptern macht ihn ideal für Routing‑Anwendungen in IEC 61499‑Systemen. Die EPL‑Lizenzierung und die generische Auslegung fördern die Wiederverwendbarkeit und Anpassbarkeit. Der Baustein ergänzt die vorhandenen Standard‑Demultiplexer um die wichtige Fähigkeit, strukturierte Datenadapter gezielt zu verteilen.
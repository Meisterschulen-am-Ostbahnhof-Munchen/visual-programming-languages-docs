# AIS_DEMUX_2


![AIS_DEMUX_2](./AIS_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_DEMUX_2** ist ein generischer AIS-Demultiplexer für die 4diac-IDE. Er ermöglicht die Weiterleitung eines eingehenden AIS-Signals an einen von zwei Ausgängen, gesteuert durch einen Index. Der Baustein ist auf die Verwendung mit dem unidirektionalen AIS-Adapter ausgelegt und wird in der Landtechnik eingesetzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Setzt den Auswahlindex K und löst die Demultiplexierung aus. Der Eingang IN wird auf den durch K bestimmten Ausgang geleitet. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigt die erfolgreiche Verarbeitung des REQ-Ereignisses. |

### **Daten-Eingänge**

| Variable | Typ  | Beschreibung       |
|----------|------|--------------------|
| K        | UINT | Index zur Auswahl des Ausgangs (1 oder 2). |

### **Daten-Ausgänge**
Der Funktionsblock besitzt keine Daten-Ausgänge. Die Ausgabe erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Adapter**

| Richtung | Name | Typ                              | Beschreibung                                   |
|----------|------|----------------------------------|------------------------------------------------|
| Socket   | IN   | adapter::types::unidirectional::AIS | Eingangs-AIS-Signal, das demultiplext wird. |
| Plug     | OUT1 | adapter::types::unidirectional::AIS | Erster Ausgang für das AIS-Signal.            |
| Plug     | OUT2 | adapter::types::unidirectional::AIS | Zweiter Ausgang für das AIS-Signal.           |

## Funktionsweise
Der Baustein arbeitet als 1-zu-2-Demultiplexer für AIS-Datenströme. Bei Eintreffen des Ereignisses **REQ** wird der anliegende Wert des Index **K** ausgewertet:
- Ist **K = 1**, wird das am Socket **IN** anliegende AIS-Signal an den Plug **OUT1** weitergeleitet.
- Ist **K = 2**, erfolgt die Weiterleitung an **OUT2**.
- Für andere Werte von **K** wird kein Ausgang aktiviert (das Signal verworfen).

Nach der Umschaltung wird das Ereignis **CNF** gesendet. Es wird davon ausgegangen, dass die AIS-Daten auf den Ausgängen bis zum nächsten **REQ** gültig bleiben.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AIS_DEMUX`) deklariert, sodass er in unterschiedlichen Kontexten parametrisiert werden kann.
- **Unidirektionale Adapter**: Alle AIS-Adapter sind unidirektional ausgelegt, d. h. der Datenfluss erfolgt nur vom Socket zu den Plugs.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0**.
- **Keine Daten-Ausgänge**: Die Ausgabe erfolgt rein über die Plug-Adapter, was die Integration in adapterbasierte Architekturen erleichtert.

## Zustandsübersicht
Der Baustein verfügt über keinen expliziten Zustandsautomaten in der XML-Beschreibung. Das implizite Verhalten kann wie folgt beschrieben werden:
1. **Idle**: Warten auf ein **REQ**-Ereignis.
2. **Processing**: Nach Eintreffen von **REQ** wird der Index K ausgelesen und die entsprechende Weiterleitung gesetzt.
3. **Done**: Ausgabe von **CNF** und Rückkehr in den Idle-Zustand.

## Anwendungsszenarien
- **Steuerung von AIS-Signalen in landwirtschaftlichen Maschinen**: Verteilung eines zentralen AIS-Datenstroms auf zwei verschiedene Verbraucher (z. B. zwei Aktoren oder Sensorgruppen).
- **Test und Simulation**: Einsatz in Simulationsumgebungen, um den Datenfluss zwischen verschiedenen Komponenten gezielt umzuleiten.
- **Redundanz**: Möglichkeit, das AIS-Signal auf einen Ersatzausgang zu schalten, falls der primäre Empfänger ausfällt.

## Vergleich mit ähnlichen Bausteinen
- **Standard-Demultiplexer (z. B. `DEMUX_2`)**: Diese arbeiten in der Regel mit skalaren Datentypen und Ereignissen. Der `AIS_DEMUX_2` ist speziell für das AIS-Protokoll und adapterbasierte Kommunikation optimiert.
- **Multiplexer (`AIS_MUX_2`)**: Der Multiplexer führt mehrere AIS-Eingänge zu einem Ausgang zusammen; der Demultiplexer stellt die Umkehrfunktion dar.
- **Vorteile**: Die Verwendung von Adaptern erlaubt eine lose Kopplung und einfache Wiederverwendung in verschiedenen Anwendungen.

## Fazit
Der **AIS_DEMUX_2** ist ein spezialisierter, generischer Funktionsblock zur Demultiplexierung von AIS-Signalen. Er bietet eine klare, ereignisgesteuerte Schnittstelle mit Adaptern und eignet sich besonders für den Einsatz in der Agrartechnik und anderen Bereichen, in denen unidirektionale AIS-Daten verteilt werden müssen. Durch seine Lizenzierung als EPL 2.0 ist er offen und erweiterbar.
# AI_SPLIT_5


![AI_SPLIT_5](./AI_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_SPLIT_5** dient dazu, ein eingehendes analogen Signal (AI) auf fünf identische Ausgänge zu verteilen. Es handelt sich um einen generischen Baustein, der speziell für die Aufteilung eines Analogwerts in mehrere parallele Pfade ausgelegt ist. Die Anwendung erfolgt über unidirektionale Adapter vom Typ `AI`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Die Signalübertragung erfolgt ausschließlich über den Adapter-Eingang.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Die Signalübertragung erfolgt ausschließlich über die Adapter-Ausgänge.

### **Adapter**

| Richtung | Name   | Typ                          | Beschreibung                                        |
|----------|--------|------------------------------|-----------------------------------------------------|
| Socket   | IN     | `adapter::types::unidirectional::AI` | Empfängt das eingehende analoge Signal.             |
| Plug     | OUT1   | `adapter::types::unidirectional::AI` | Erster Ausgang, stellt das gleiche Signal wie IN bereit. |
| Plug     | OUT2   | `adapter::types::unidirectional::AI` | Zweiter Ausgang, stellt das gleiche Signal wie IN bereit. |
| Plug     | OUT3   | `adapter::types::unidirectional::AI` | Dritter Ausgang, stellt das gleiche Signal wie IN bereit. |
| Plug     | OUT4   | `adapter::types::unidirectional::AI` | Vierter Ausgang, stellt das gleiche Signal wie IN bereit. |
| Plug     | OUT5   | `adapter::types::unidirectional::AI` | Fünfter Ausgang, stellt das gleiche Signal wie IN bereit. |

## Funktionsweise
Der Baustein leitet das am Adapter-Eingang *IN* anliegende analoge Signal unverändert an alle fünf Adapter-Ausgänge *OUT1* bis *OUT5* weiter. Es findet keinerlei Signalverarbeitung oder Pufferung statt; die Verteilung erfolgt rein topologisch auf der Verbindungsebene. Der FB ist dadurch ideal geeignet, um ein einzelnes Analog-Signal an mehrere nachfolgende Funktionen oder Geräte zu verteilen, ohne dass eine Vervielfältigung auf Applikationsebene programmiert werden muss.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Baustein (`GEN_AI_SPLIT`) implementiert und kann durch entsprechende Typzuweisungen an unterschiedliche analoge Signaltypen angepasst werden.
- **Unidirektionale Adapter**: Sämtliche Adapter sind unidirektional ausgelegt, d.h. die Daten fließen nur vom Eingang zu den Ausgängen.
- **Kein internes Zustandsverhalten**: Der FB besitzt kein eigenes Zustandsmodell (ECC), da er rein kombinatorisch arbeitet.
- **Skalierbarkeit**: Der Baustein ist auf fünf Ausgänge fest ausgelegt. Für andere Anzahlen können ähnliche Bausteine (z.B. AI_SPLIT_2, AI_SPLIT_3) verwendet oder durch Anpassung des generischen Musters erstellt werden.

## Zustandsübersicht
Der FB besitzt kein explizites Zustandsdiagramm. Da keine Ereignisse verarbeitet werden, ist das Verhalten statisch: das Signal am Eingang wird permanent auf die Ausgänge durchgeschaltet. Eine Initialisierung oder ein spezielles Verhalten bei Inbetriebnahme ist nicht erforderlich.

## Anwendungsszenarien
- **Verteilung eines Messwerts**: Ein analoger Sensor (z.B. Temperatur, Druck) liefert einen Wert, der parallel an mehrere Regelungs-, Überwachungs- oder Visualisierungskomponenten weitergegeben werden muss.
- **Parallele Verarbeitung**: In einer Steuerungsapplikation soll derselbe Analogwert in verschiedenen Zweigen unterschiedlich weiterverarbeitet werden (z.B. sowohl in einer PID-Regelung als auch in einer Grenzwertüberwachung).
- **Redundanz**: Das Signal wird an mehrere unabhängige Auswerteeinheiten gesendet, um Ausfallsicherheit zu gewährleisten.

## Vergleich mit ähnlichen Bausteinen
- **AI_SPLIT_2, AI_SPLIT_3, AI_SPLIT_N**: Diese Bausteine teilen ein analoges Signal auf eine andere Anzahl von Ausgängen auf. AI_SPLIT_5 ist speziell für fünf Ausgänge optimiert.
- **Analoge Splitter in anderen Bibliotheken**: Oft werden solche Funktionen durch Adapter-Kopplung oder Datenkopierer realisiert. Der AI_SPLIT_5 bietet eine saubere, wiederverwendbare Struktur innerhalb des 4diac-Frameworks.
- **Unterschied zu Daten-Ereignis-basierten Splittern**: Da der FB keine Ereignisse nutzt, ist er rein signalflussorientiert und benötigt keine Synchronisation oder Ablaufsteuerung.

## Fazit
Der AI_SPLIT_5 ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfältigung eines analogen Signals. Seine generische Natur und die klare Adapter-Schnittstelle machen ihn zu einem idealen Baustein für modulare Automatisierungslösungen, bei denen ein Analogwert mehrfach benötigt wird. Die fehlende Ereignissteuerung reduziert die Komplexität und ermöglicht eine direkte Signalweitergabe ohne zeitliche Verzögerungen.
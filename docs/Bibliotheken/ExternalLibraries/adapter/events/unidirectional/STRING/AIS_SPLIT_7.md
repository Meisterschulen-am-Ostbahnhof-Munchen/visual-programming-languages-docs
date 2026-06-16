# AIS_SPLIT_7


![AIS_SPLIT_7](./AIS_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_SPLIT_7** dient zur Verteilung eines eingehenden AIS-Datenstroms auf sieben identische Ausgänge. Er ist als generischer Baustein implementiert und ermöglicht die Aufteilung eines unidirektionalen AIS-Adapters (Socket IN) auf sieben gleichartige Adapter-Plugs (OUT1 … OUT7). Die Bezeichnung „AIS“ steht hier für einen anwendungsspezifischen, abstrakten Datentyp im Adapter-Kontext der IEC 61499.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | IN | `adapter::types::unidirectional::AIS` | Eingehender AIS-Datenstrom, der auf alle Ausgänge verteilt wird. |
| Plug (Ausgang) | OUT1 … OUT7 | `adapter::types::unidirectional::AIS` | Sieben identische Ausgänge, die den eingehenden AIS-Datenstrom jeweils unverändert weiterleiten. |

## Funktionsweise
Der Baustein fungiert als reiner Verteiler (Splitter) für AIS-Adapterverbindungen. Jedes ankommende Datum oder Ereignis am Socket `IN` wird **ohne Verzögerung oder Verarbeitung** auf alle sieben Adapter-Plugs `OUT1` bis `OUT7` repliziert. Die Weiterleitung erfolgt parallel, d. h. alle Ausgänge erhalten gleichzeitig die gleichen Informationen. Eine interne Logik oder Zustandsmaschine ist nicht erforderlich, da es sich um eine passive, verbindungsorientierte Datenweitergabe handelt.

## Technische Besonderheiten
- **Generischer Baustein** – Der FB ist als generische Instanz (`GEN_AIS_SPLIT`) deklariert und kann für beliebige AIS-Typen parametrisiert werden.
- **Unidirektionale Adapter** – Sowohl Eingang als auch Ausgänge verwenden ausschließlich den unidirektionalen Adaptertyp, sodass eine reine Flussrichtung vom Eingang zu den Ausgängen sichergestellt ist.
- **Keine Ereignis- oder Daten-Ein-/Ausgänge** – Die gesamte Kommunikation erfolgt ausschließlich über Adapter, was eine saubere Kapselung und Wiederverwendung ermöglicht.
- **Skalierbarkeit** – Das Prinzip lässt sich leicht auf andere Anzahlen von Ausgängen (z. B. AIS_SPLIT_2, AIS_SPLIT_8) übertragen.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten (ECC), da er keinerlei sequentielle Logik oder verzögerte Operationen ausführt. Die Funktion reduziert sich auf eine statische, durchgehende Weiterleitung. Ein Betriebszustand ist daher nicht definiert.

## Anwendungsszenarien
- **Verteilung von AIS-Signalen** an mehrere parallele Verarbeitungseinheiten, z. B. in Automatisierungsanlagen, wenn ein Sensorwert gleichzeitig an mehrere Regelkreise, Anzeigen oder Analysewerkzeuge übergeben werden muss.
- **Redundante Signalweiterleitung** – Einsatz zur Einspeisung eines AIS-Datenstroms in mehrere unabhängige Pfade zu Test- oder Überwachungszwecken.
- **Modulare Systemarchitektur** – Als Komponente in einer Bibliothek generischer Adapter-Bausteine, um die Wiederverwendung und Austauschbarkeit von Verbindungen zu erhöhen.

## Vergleich mit ähnlichen Bausteinen
- **Daten-Splitter (z. B. SPLIT_1_to_N)** – Diese teilen meist einfache Datentypen (BOOL, INT, REAL) auf. Der AIS_SPLIT_7 ist speziell für Adapter-Schnittstellen ausgelegt und nutzt das Adapterkonzept, das in IEC 61499 für komplexe, strukturierte Datenströme vorgesehen ist.
- **Adapter-Multiplexer (z. B. AIS_MERGE)** – Während ein Splitter einen Eingang auf mehrere Ausgänge verteilt, fasst ein Merger mehrere Eingänge zu einem Ausgang zusammen. Der AIS_SPLIT_7 ist das Gegenstück dazu.
- **Event-Splitter** – Unterscheiden sich durch die Verarbeitung von Ereignissen; der AIS_SPLIT_7 arbeitet hingegen rein adapterbasiert ohne separate Ereigniskanäle.

## Fazit
Der **AIS_SPLIT_7** ist ein einfacher, aber effektiver Funktionsblock zur Verteilung eines unidirektionalen AIS-Datenstroms auf sieben parallele Ausgänge. Seine generische Ausführung und die ausschließliche Nutzung von Adaptern machen ihn zu einem flexiblen Werkzeug in der automatisierungstechnischen Anwendungsentwicklung nach IEC 61499. Durch das Fehlen von Zustandslogik und Ereignissteuerung ist er leichtgewichtig und für reine Verteilungsaufgaben optimal geeignet.
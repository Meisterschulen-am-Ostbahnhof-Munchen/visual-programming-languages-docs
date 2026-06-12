# AI_SPLIT_4


![AI_SPLIT_4](./AI_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_SPLIT_4** ist ein generischer Baustein, der einen unidirektionalen Analog-Eingang (AI) auf vier separate Analog-Ausgänge aufteilt. Er dient als Signalverteiler für analoge Signale und erlaubt, ein einzelnes AI-Signal an verschiedene nachfolgende Bausteine weiterzugeben. Der Baustein ist vollständig adapterbasiert und besitzt keine eigenen Ereignis- oder Datenschnittstellen. Er ist unter der Eclipse Public License 2.0 verfügbar.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine

### **Ereignis-Ausgänge**

- Keine

### **Daten-Eingänge**

- Keine

### **Daten-Ausgänge**

- Keine

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket (Eingang)** | `IN` | `adapter::types::unidirectional::AI` | Eingang des zu verteilenden analogen Signals |
| **Plug (Ausgang)** | `OUT1` | `adapter::types::unidirectional::AI` | Erster Ausgang (Kopie des Eingangssignals) |
| **Plug (Ausgang)** | `OUT2` | `adapter::types::unidirectional::AI` | Zweiter Ausgang (Kopie des Eingangssignals) |
| **Plug (Ausgang)** | `OUT3` | `adapter::types::unidirectional::AI` | Dritter Ausgang (Kopie des Eingangssignals) |
| **Plug (Ausgang)** | `OUT4` | `adapter::types::unidirectional::AI` | Vierter Ausgang (Kopie des Eingangssignals) |

## Funktionsweise

Der Baustein stellt eine einfache 1:4-Verteilung eines analogen Signals dar. Das am Adapter `IN` anliegende Signal wird unverändert auf alle vier Ausgangs-Adapter (`OUT1` … `OUT4`) durchgereicht. Es findet keinerlei Skalierung, Filterung oder Umwandlung statt – das Signal wird auf feldbussebene 1:1 kopiert. Die Anzahl der Kanäle ist auf vier festgelegt.

## Technische Besonderheiten

- **Reiner Adapter-Baustein**: Der FB enthält keine Ereignis- oder Datenschnittstellen; die gesamte Kommunikation erfolgt über Adapter.
- **Generischer Typ**: Über das Attribut `GenericClassName` (`'GEN_AI_SPLIT'`) wird der Baustein als generisch ausgewiesen. In der 4diac-IDE kann dadurch ein konkreter Typ abgeleitet werden.
- **Unidirektional**: Der verwendete Adaptertyp `unidirectional::AI` überträgt Daten nur in eine Richtung (vom Socket zu den Plugs).
- **Kein Zustandsautomat**: Da keine Ereignisse vorhanden sind, existiert kein ECC (Execution Control Chart). Der FB ist rein datenflussorientiert.

## Zustandsübersicht

Der Baustein verfügt über keinen Zustandsautomaten – er ist ereignisfrei und gibt das Eingangssignal kontinuierlich an alle Ausgänge weiter. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Analog-Signalverteilung**: Ein einzelner Sensorwert (z. B. Temperatur, Druck, Füllstand) soll an mehrere Steuerungslogiken oder Visualisierungskomponenten gleichzeitig gesendet werden.
- **Redundanz oder Monitoring**: Das Signal wird parallel an einen Hauptregler und einen unabhängigen Überwachungsbaustein weitergeleitet.
- **Entkopplung von Subsystemen**: In einer modularen Steuerung können verschiedene Subsysteme denselben Analogwert empfangen, ohne dass ein Mehrfachzugriff auf den Sensor erforderlich ist.

## Vergleich mit ähnlichen Bausteinen

- **AI_SPLIT_2 / AI_SPLIT_8**: Ähnliche Bausteine mit 2 bzw. 8 Ausgängen. Die Wahl hängt von der benötigten Anzahl paralleler Signale ab.
- **AI_SELECT** oder **AI_MUX**: Diese Bausteine wählen aus mehreren Eingängen einen aus, während der AI_SPLIT das Eingangssignal vervielfacht.
- **Standard-Adaptersplit**: Manche Bibliotheken bieten generische Split-Bausteine, die jedoch oft zusätzliche Ereignis- oder Datenschnittstellen benötigen. Der AI_SPLIT_4 ist durch seinen reinen Adapteransatz besonders einfach in Adapterketten integrierbar.

## Fazit

Der Funktionsblock **AI_SPLIT_4** ist ein spezialisierter, aber einfach einsetzbarer Baustein zur Vervielfachung analoger Signale. Dank seiner reinen Adapterschnittstelle lässt er sich nahtlos in 4diac-Projekte einbinden, ohne zusätzliche Ereignislogik. Er eignet sich besonders für modulare und skalierbare Automatisierungslösungen, bei denen ein einzelner Messwert an mehrere Verbraucher verteilt werden muss.
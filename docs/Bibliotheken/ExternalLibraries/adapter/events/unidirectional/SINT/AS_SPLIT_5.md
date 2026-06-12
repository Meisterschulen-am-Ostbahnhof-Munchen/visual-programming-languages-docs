# AS_SPLIT_5


![AS_SPLIT_5](./AS_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AS_SPLIT_5 ist ein generischer Baustein, der einen eingehenden Adapter vom Typ "AS" (unidirectional) auf fünf separate Ausgangsadapter desselben Typs verteilt. Er dient zur Signalvervielfachung in Steuerungs- und Automatisierungssystemen, basierend auf der IEC 61499-2 Norm.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge definiert.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge definiert.

### **Daten-Eingänge**
Keine Daten-Eingänge definiert.

### **Daten-Ausgänge**
Keine Daten-Ausgänge definiert.

### **Adapter**

| Rolle | Name | Typ | Beschreibung |
|-------|------|-----|--------------|
| Socket | IN | adapter::types::unidirectional::AS | Eingangs-Adapter, der das zu verteilende AS-Signal empfängt. |
| Plug | OUT1 | adapter::types::unidirectional::AS | Erster Ausgangs-Adapter für das verteilte Signal. |
| Plug | OUT2 | adapter::types::unidirectional::AS | Zweiter Ausgangs-Adapter. |
| Plug | OUT3 | adapter::types::unidirectional::AS | Dritter Ausgangs-Adapter. |
| Plug | OUT4 | adapter::types::unidirectional::AS | Vierter Ausgangs-Adapter. |
| Plug | OUT5 | adapter::types::unidirectional::AS | Fünfter Ausgangs-Adapter. |

## Funktionsweise

Der AS_SPLIT_5 Baustein fungiert als passiver Verteiler. Das am Socket "IN" anliegende AS-Signal wird ohne Verzögerung oder Veränderung identisch an alle fünf Ausgangs-Plugs (OUT1 bis OUT5) weitergeleitet. Die Verteilung erfolgt strikt nach dem Prinzip des Broadcasts – jedes ausgehende Signal entspricht dem Originalsignal. Die Implementierung ist rein adapterbasiert und benötigt keine zusätzlichen Ereignis- oder Datenportverbindungen.

## Technische Besonderheiten

- Der Baustein ist als generischer Typ (GenericClassName = 'GEN_AS_SPLIT') definiert und kann daher durch die 4diac-IDE parametrisiert werden.
- Es wird ein TypeHash verwendet, um die Eindeutigkeit des Bausteins im Projekt sicherzustellen.
- Die Anzahl der Ausgänge ist fest auf fünf festgelegt, eine dynamische Konfiguration ist nicht vorgesehen.
- Die Laufzeitumgebung muss das unidirektionale Adapter-Interface "adapter::types::unidirectional::AS" unterstützen.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten. Die Signalverteilung erfolgt kontinuierlich und ohne sequentielle Logik. Daher entfällt eine Zustandsübersicht.

## Anwendungsszenarien

- **Steuerungsverdrahtung**: Aufteilung eines von einer übergeordneten Steuerung kommenden AS-Signals auf mehrere Unterstationen oder Aktoren.
- **Simulation und Test**: Vervielfachung eines Testsignals zur parallelen Ansteuerung mehrerer simulierter Komponenten.
- **Redundanz**: Bereitstellung desselben Signals auf verschiedenen Pfaden, um Redundanz oder Lastverteilung zu ermöglichen.

## Vergleich mit ähnlichen Bausteinen

Da AS_SPLIT_5 für eine spezifische Adapterarchitektur (unidirectional AS) konzipiert ist, existieren typischerweise ähnliche Bausteine wie z. B. "AS_SPLIT_2", "AS_SPLIT_3" oder verallgemeinerte Splitter mit variabler Anzahl von Ausgängen. Der vorliegende Baustein unterscheidet sich durch die feste Anzahl von fünf Ausgängen und die reine Adapter-Schnittstelle ohne Daten- oder Ereignisports.

## Fazit

Der AS_SPLIT_5 ist ein einfacher, aber effektiver Funktionsblock zur Vervielfachung eines AS-Adaptersignals auf fünf parallele Ausgänge. Durch seine generische Implementierung und klare Schnittstelle eignet er sich gut für modulare Automatisierungslösungen nach IEC 61499.
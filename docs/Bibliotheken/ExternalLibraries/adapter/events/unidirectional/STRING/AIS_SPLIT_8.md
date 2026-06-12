# AIS_SPLIT_8


![AIS_SPLIT_8](./AIS_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIS_SPLIT_8** dient der Verteilung eines eingehenden AIS (Application Interface Socket) auf acht identische Ausgangsadapter. Er ist als generischer Baustein konzipiert und erlaubt die gleichzeitige Weitergabe eines AIS-Signals an mehrere nachfolgende Funktionsblöcke ohne Datenverlust oder Verzögerung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine vorhanden.

### **Ereignis-Ausgänge**
Keine vorhanden.

### **Daten-Eingänge**
Keine vorhanden.

### **Daten-Ausgänge**
Keine vorhanden.

### **Adapter**
| Richtung | Name  | Typ                              | Beschreibung                                      |
|----------|-------|----------------------------------|---------------------------------------------------|
| Eingang  | IN    | `adapter::types::unidirectional::AIS` | Eingehendes AIS-Signal, das verteilt werden soll. |
| Ausgang  | OUT1  | `adapter::types::unidirectional::AIS` | Erster Ausgangskanal (identisch zu IN).           |
| Ausgang  | OUT2  | `adapter::types::unidirectional::AIS` | Zweiter Ausgangskanal (identisch zu IN).          |
| Ausgang  | OUT3  | `adapter::types::unidirectional::AIS` | Dritter Ausgangskanal (identisch zu IN).          |
| Ausgang  | OUT4  | `adapter::types::unidirectional::AIS` | Vierter Ausgangskanal (identisch zu IN).          |
| Ausgang  | OUT5  | `adapter::types::unidirectional::AIS` | Fünfter Ausgangskanal (identisch zu IN).          |
| Ausgang  | OUT6  | `adapter::types::unidirectional::AIS` | Sechster Ausgangskanal (identisch zu IN).         |
| Ausgang  | OUT7  | `adapter::types::unidirectional::AIS` | Siebter Ausgangskanal (identisch zu IN).          |
| Ausgang  | OUT8  | `adapter::types::unidirectional::AIS` | Achter Ausgangskanal (identisch zu IN).           |

## Funktionsweise
Der Baustein leitet das am Adapter-Eingang `IN` anliegende AIS-Signal unverändert und ohne Zeitverzögerung an alle acht Ausgangsadapter `OUT1` bis `OUT8` weiter. Es findet keine Transformation, Filterung oder Pufferung statt. Das Verhalten entspricht einer passiven Verteilung (Broadcast) eines AIS-Interfaces.

## Technische Besonderheiten
- **Generischer Typ** – Der Baustein ist als `GEN_AIS_SPLIT` deklariert und kann über Typparametrisierung an spezifische AIS-Ausprägungen angepasst werden (z. B. für verschiedene Datentypen oder Ereignisstrukturen).
- **Keine Laufzeitlogik** – Die gesamte Funktionalität wird allein durch die Verschaltung der Adapter realisiert; es existieren keine internen Algorithmen oder Zustandsautomaten.
- **Minimaler Ressourcenbedarf** – Da keine aktive Verarbeitung stattfindet, verursacht der Baustein weder CPU-Last noch Speicherverbrauch bei der Ausführung.

## Zustandsübersicht
Der Baustein besitzt keine internen Zustände. Das Ausgangssignal ist stets eine direkte Abbildung des Eingangssignals.

## Anwendungsszenarien
- **Parallelverarbeitung** – Aufteilung eines Sensorsignals auf mehrere unabhängige Auswertungsblöcke.
- **Redundanz** – Verteilung eines Steuersignals an mehrere Aktoren in sicherheitskritischen Systemen.
- **Test- und Simulationsumgebungen** – Bereitstellung eines identischen Signals für verschiedene Beobachter oder Logger.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Bausteinen wie `AIS_MERGE_2` oder `AIS_SELECT` besitzt `AIS_SPLIT_8` keine Selektions- oder Priorisierungslogik. Verwandte Varianten unterscheiden sich lediglich in der Anzahl der Ausgänge (z. B. `AIS_SPLIT_2` oder `AIS_SPLIT_4`). `AIS_SPLIT_8` ist die maximale Standardausführung für acht Kanäle.

## Fazit
`AIS_SPLIT_8` ist ein einfacher und effizienter Baustein zur Vervielfältigung eines AIS-Interfaces. Durch seine generische Natur und die reine Adapter-basierte Umsetzung eignet er sich ideal für den Aufbau modularer Automatisierungsarchitekturen, die eine verteilte Signalweiterleitung benötigen.
# AS_SPLIT_4


![AS_SPLIT_4](./AS_SPLIT_4.svg)

*Kein Bild verfügbar.*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_SPLIT_4** teilt einen eingehenden unidirektionalen AS-Adapter in vier identische Ausgänge auf. Er dient als generischer Splitter, der das über den Socket `IN` empfangene Signal unverändert an die vier Plugs `OUT1` bis `OUT4` weiterleitet.

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

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AS` | IN | Socket | Eingehender AS-Signalpfad (Eingang) |
| `adapter::types::unidirectional::AS` | OUT1 | Plug | Erster Ausgang (identisch zu IN) |
| `adapter::types::unidirectional::AS` | OUT2 | Plug | Zweiter Ausgang (identisch zu IN) |
| `adapter::types::unidirectional::AS` | OUT3 | Plug | Dritter Ausgang (identisch zu IN) |
| `adapter::types::unidirectional::AS` | OUT4 | Plug | Vierter Ausgang (identisch zu IN) |

## Funktionsweise

Der FB arbeitet rein passiv: Jedes über den Adapter `IN` eingehende Signal wird ohne Verzögerung oder Transformation an alle vier Plugs (`OUT1`–`OUT4`) weitergegeben. Es findet keine Datenpufferung, keine logische Verarbeitung und keine Zustandsänderung statt. Die Verteilung ist deterministisch und erfolgt zur Kompilier- oder Laufzeit entsprechend der Adapterverträge.

## Technische Besonderheiten

- **Keine Ereignis-/Datenschnittstellen:** Die gesamte Kommunikation läuft ausschließlich über Adapter.
- **Einheitlicher Typ:** Alle fünf Adapter sind vom gleichen unidirektionalen Typ `AS`.
- **Generische Parametrisierung:** Der FB trägt die Attribute `GenericClassName` (Wert: `'GEN_AS_SPLIT'`) und `TypeHash`, wodurch er anwendungsspezifisch angepasst werden kann (z. B. durch Refactoring oder Modelltransformation).
- **Zustandslos:** Kein ECC, keine internen Variablen – das Verhalten ist vollständig durch die Adapterverträge definiert.

## Zustandsübersicht

Der FB besitzt keine Zustandsautomaten. Das Verhalten ist zeitlos und gleichbleibend: Das Eingangssignal wird stets unmittelbar auf alle Ausgänge dupliziert.

## Anwendungsszenarien

- **Signalverteilung in Steuerungen:** Aufteilung einer Geschwindigkeits- oder Positionsvorgabe auf mehrere parallele Achsen.
- **Sensorwert-Multiplex:** Verteilen eines gemessenen Werts an mehrere Auswerte- oder Überwachungsinstanzen.
- **Modulare Anbindung:** Einsatz in hierarchischen Systemen, bei denen ein Adaptersignal mehrfach benötigt wird, ohne den Sender mehrfach zu instanziieren.

## Vergleich mit ähnlichen Bausteinen

- **AS_MERGE:** Führt mehrere AS-Eingänge zu einem Ausgang zusammen – das funktionale Gegenstück zum Split.
- **AS_SPLIT_2:** Gleiche Funktionalität, aber nur zwei Ausgänge. `AS_SPLIT_4` erweitert dies auf vier.
- **Ereignis-basierte Splitter (z. B. E_SPLIT):** Arbeiten mit Ereignis- und Dateneingängen/-ausgängen und verbreiten Ereignisse. `AS_SPLIT_4` operiert dagegen auf Adapterebene und leitet den gesamten Adaptervertrag (inkl. aller darin enthaltenen Ereignisse und Daten) weiter.

## Fazit

`AS_SPLIT_4` ist ein einfacher, aber essentieller Baustein zur strukturellen Vervielfältigung von unidirektionalen AS-Adapterverbindungen in 4diac-Anwendungen. Seine generische Auslegung und die reine Adapterschnittstelle machen ihn ideal für modulare und skalierbare Steuerungsarchitekturen.
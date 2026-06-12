# AIS_SPLIT_5


![AIS_SPLIT_5](./AIS_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AIS_SPLIT_5** dient als generischer Verteiler (Splitter) für Adapter vom Typ `AIS` (unidirektional). Er nimmt ein eingehendes AIS-Signal über einen Socket entgegen und leitet es an fünf separate AIS-Plugs weiter. Dies ermöglicht die Vervielfachung eines Adaptersignals auf mehrere Zielbausteine.

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
| Socket (Eingang) | IN | `adapter::types::unidirectional::AIS` | Eingehendes AIS-Adapter-Signal |
| Plug (Ausgang 1) | OUT1 | `adapter::types::unidirectional::AIS` | Erster ausgehender AIS-Adapter-Anschluss |
| Plug (Ausgang 2) | OUT2 | `adapter::types::unidirectional::AIS` | Zweiter ausgehender AIS-Adapter-Anschluss |
| Plug (Ausgang 3) | OUT3 | `adapter::types::unidirectional::AIS` | Dritter ausgehender AIS-Adapter-Anschluss |
| Plug (Ausgang 4) | OUT4 | `adapter::types::unidirectional::AIS` | Vierter ausgehender AIS-Adapter-Anschluss |
| Plug (Ausgang 5) | OUT5 | `adapter::types::unidirectional::AIS` | Fünfter ausgehender AIS-Adapter-Anschluss |

## Funktionsweise

Der Baustein arbeitet als reine Durchleitung (Broadcast) ohne eigene Logik oder Zustände. Sobald ein Ereignis oder eine Datenänderung über den Socket `IN` ankommt, wird dieses Signal unverändert an alle fünf Plugs (`OUT1`–`OUT5`) weitergegeben. Jeder Plug kann mit einem anderen Empfängerbaustein verbunden werden, sodass das ursprüngliche Signal gleichzeitig von mehreren Komponenten verarbeitet werden kann.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Funktionsbaustein markiert (`eclipse4diac::core::GenericClassName = 'GEN_AIS_SPLIT'`). Dadurch kann er in verschiedenen Kontexten mit jeweils passenden AIS-Adapter-Typen instanziiert werden.
- **Keine Ereignis- oder Daten-Ein-/Ausgänge**: Die gesamte Kommunikation erfolgt ausschließlich über die Adapter-Schnittstellen. Dies macht ihn besonders einfach und effizient.
- **Unidirektional**: Der Adaptertyp `AIS` ist unidirektional, d. h. die Signalrichtung ist festgelegt (vom Socket zu den Plugs). Eine Rückkopplung ist nicht vorgesehen.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandslogik (kein ECC). Es gibt keinen internen Automaten oder Verzögerung. Die Funktionsweise entspricht einer starren, kombinatorischen Weiterleitung.

## Anwendungsszenarien

- **Signalverteilung in Steuerungssystemen**: Ein von einer Quelle (z. B. Sensor oder Kommunikationsbaustein) geliefertes AIS-Signal soll an mehrere unabhängige Verarbeitungsblöcke weitergegeben werden.
- **Test- und Simulationsumgebungen**: Ein Testsignal kann gleichzeitig an verschiedene Überwachungs- oder Analysebausteine gesendet werden.
- **Redundante Verarbeitung**: Das gleiche Signal wird mehrfach ausgewertet, um Fehler zu erkennen oder unterschiedliche Algorithmen zu vergleichen.

## Vergleich mit ähnlichen Bausteinen

Es gibt weitere Splitter-Bausteine wie `AIS_SPLIT_2`, `AIS_SPLIT_3` oder `AIS_SPLIT_4`, die eine geringere Anzahl an Ausgängen bereitstellen. Gemeinsam ist allen, dass sie ein einzelnes AIS-Eingangssignal auf mehrere Ausgänge verteilen. Der `AIS_SPLIT_5` bietet die maximale Anzahl von fünf Ausgängen dieser Familie. Je nach Bedarf kann der passende Splitter gewählt werden, um unnötige Verkabelung zu vermeiden.

## Fazit

Der `AIS_SPLIT_5` ist ein einfacher, aber wirkungsvoller generischer Funktionsbaustein zur Vervielfachung eines unidirektionalen AIS-Adapter-Signals. Er reduziert den Verkabelungsaufwand in der 4diac-IDE und ermöglicht eine saubere, modulare Strukturierung von Steuerungsanwendungen. Für Anwendungen, die eine Aufteilung eines Signals auf bis zu fünf Empfänger erfordern, stellt er eine optimale Lösung dar.
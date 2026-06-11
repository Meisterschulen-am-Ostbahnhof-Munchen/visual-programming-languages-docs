# A2X_SPLIT_5


![A2X_SPLIT_5](./A2X_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **A2X_SPLIT_5** dient dazu, einen eingehenden A2X-Adapter in fünf identische A2X-Ausgänge aufzuteilen. Er wird als generischer Baustein bereitgestellt, der über Attribute konfiguriert werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ            | Beschreibung                         |
|----------|------|----------------|--------------------------------------|
| Socket   | IN   | A2X (unidirectional) | Eingangsadapter (wird aufgeteilt)   |
| Plug     | OUT1 | A2X (unidirectional) | Erster Ausgangsadapter               |
| Plug     | OUT2 | A2X (unidirectional) | Zweiter Ausgangsadapter              |
| Plug     | OUT3 | A2X (unidirectional) | Dritter Ausgangsadapter              |
| Plug     | OUT4 | A2X (unidirectional) | Vierter Ausgangsadapter              |
| Plug     | OUT5 | A2X (unidirectional) | Fünfter Ausgangsadapter              |

## Funktionsweise

Der Baustein leitet den am Socket `IN` anliegenden A2X-Adapter unverändert und parallel an alle fünf Plugs (`OUT1` bis `OUT5`) weiter. Eine Verzögerung oder Pufferung findet nicht statt – jede Änderung am Eingang wird sofort an alle Ausgänge propagiert. Somit verhält sich der Baustein wie ein einfacher Verteiler (Splitter) für A2X-Schnittstellen.

## Technische Besonderheiten

- **Generischer Baustein:** Die tatsächliche Instanz kann über die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` konfiguriert werden, wodurch eine Anpassung an verschiedene A2X-Varianten möglich ist.
- **Keine Ereignis- oder Daten-Ports:** Die gesamte Kommunikation erfolgt ausschließlich über Adapter. Dies vereinfacht die Kopplung mit anderen A2X-basierten Komponenten.
- **Skalierbarkeit:** Der Baustein kann als Grundlage für Splitter mit anderer Anzahl von Ausgängen dienen (z. B. `A2X_SPLIT_2`, `A2X_SPLIT_10`).

## Zustandsübersicht

Der Baustein besitzt keine internen Zustände oder Zustandsautomaten. Er arbeitet rein kombinatorisch als passive Weiterleitung.

## Anwendungsszenarien

- **Verteilen eines Bus-Signals:** Wenn ein A2X-Adapter (z. B. für einen Feldbus) an mehrere nachgelagerte Module übergeben werden muss, ohne dass diese sich gegenseitig beeinflussen.
- **Test- und Simulationsaufbauten:** Ein eingehender A2X-Datenstrom kann parallel an verschiedene Analyse- oder Überwachungskomponenten geschaltet werden.
- **Erweiterung von Steuerungssystemen:** Ein Sensor- oder Aktor-Adapter kann auf mehrere Funktionsblöcke aufgeteilt werden, die unterschiedliche Logiken implementieren.

## Vergleich mit ähnlichen Bausteinen

- **A2X_SPLIT_2 / A2X_SPLIT_N:** Diese Varianten unterscheiden sich nur in der Anzahl der Ausgänge. `A2X_SPLIT_5` bietet einen festen 5‑fachen Split.
- **A2X_MERGE:** Während der Splitter einen Eingang auf viele Ausgänge verteilt, fasst der Merge-Baustein mehrere A2X-Eingänge zu einem Ausgang zusammen.
- **Datensplitter (z. B. SPLIT_INT):** Letztere arbeiten auf Daten-Ebene (z. B. ganze Zahlen) und nicht auf Adapterebene. Der hier beschriebene Baustein operiert auf der Adapterebene, was eine strukturelle Entkopplung ermöglicht.

## Fazit

Der `A2X_SPLIT_5` ist ein einfacher, aber nützlicher Adapter-Splitter für A2X-Schnittstellen. Durch seine generische Natur und die reine Adapter-Kommunikation fügt er sich nahtlos in IEC 61499‑basierte Steuerungssysteme ein. Er eignet sich besonders für Anwendungen, bei denen ein A2X-Signal auf mehrere Pfade verteilt werden muss, ohne zusätzliche Logik oder Zustände zu erfordern.
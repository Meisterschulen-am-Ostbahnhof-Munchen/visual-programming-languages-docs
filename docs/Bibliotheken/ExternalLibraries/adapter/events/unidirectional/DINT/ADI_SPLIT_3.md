# ADI_SPLIT_3


![ADI_SPLIT_3](./ADI_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ADI_SPLIT_3** dient dazu, einen eingehenden ADI-Datenstrom (Adapter-Interface) auf drei identische Ausgänge zu verteilen. Er ist als generischer Baustein ausgelegt und ermöglicht eine einfache Signalvervielfachung in adapterbasierten 4diac-Anwendungen.

## Schnittstellenstruktur

Der Baustein besitzt ausschließlich Adapter-Schnittstellen – weder Ereignis- noch Datenein-/-ausgänge sind vorhanden.

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::ADI` | Socket (Eingang) | Eingehender ADI-Datenstrom, der aufgeteilt wird. |
| `OUT1` | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | Erster ausgehender ADI-Datenstrom (Kopie des Eingangs). |
| `OUT2` | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | Zweiter ausgehender ADI-Datenstrom. |
| `OUT3` | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | Dritter ausgehender ADI-Datenstrom. |

## Funktionsweise

Der Baustein leitet alle an seinem Socket `IN` ankommenden ADI-Datenpakete unverändert an die drei Ausgangs-Plugs `OUT1`, `OUT2` und `OUT3` weiter. Es findet keine Verarbeitung oder Pufferung statt – die Verteilung erfolgt direkt und ohne Verzögerung. Somit entspricht das Verhalten einer passiven Signalvervielfachung (1:N‑Splitter).

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein ist mittels eines generischen Klassennamens (`GEN_ADI_SPLIT`) definiert, sodass er für beliebige ADI-konforme Datentypen wiederverwendet werden kann.
- **Typ-Hash:** Ein leerer Typ-Hash ist hinterlegt, was auf eine einfache, unparametrisierte Implementierung hinweist.
- **Keine Laufzeitlogik:** Da weder Ereignis- noch Datenschnittstellen existieren, ist der Baustein vollständig durch die Adapterverbindungen gesteuert und benötigt keinen eigenen ECC (Execution Control Chart).

## Zustandsübersicht

Der Baustein besitzt keine internen Zustände. Seine Funktionalität beschränkt sich auf das passive Durchreichen von Adapterdaten – es gibt daher keine Zustandsmaschine.

## Anwendungsszenarien

- **Signalverteilung in Steuerungssystemen:** Wenn ein ADI-Sensorwert gleichzeitig an mehrere Verbraucher (z. B. Visualisierung, Regelung, Protokollierung) gesendet werden muss.
- **Test- und Simulationsumgebungen:** Ein reales ADI-Signal kann mit `ADI_SPLIT_3` an verschiedene Testmodule oder Simulationskomponenten verteilt werden, ohne dass die Quelle mehrfach angesprochen werden muss.
- **Redundanz und Sicherheitskonzepte:** Verteilung eines sicherheitskritischen Signals an mehrere unabhängige Auswerteeinheiten.

## Vergleich mit ähnlichen Bausteinen

- **`ADI_SPLIT_2`** – Aufteilung auf zwei Ausgänge, ansonsten identische Funktionalität.
- **`ADI_MERGE`** – Fasst mehrere ADI-Eingänge zu einem Ausgang zusammen (Gegenstück zum Splitter).
- **`ADI_SELECT`** – Wählt einen von mehreren ADI-Eingängen basierend auf einem Steuersignal aus (keine reine Verteilung).

Der `ADI_SPLIT_3` ist speziell für den Fall optimiert, dass genau drei identische Kopien eines ADI-Signals benötigt werden. Falls mehr oder weniger Ausgänge erforderlich sind, können andere Splitter-Varianten oder Kombinationen eingesetzt werden.

## Fazit

Der **ADI_SPLIT_3** ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfachung von ADI-Datenströmen auf drei Wege. Durch seine reine Adapter-Schnittstelle lässt er sich nahtlos in bestehende 4diac-Projekte integrieren, ohne zusätzliche Ereignis- oder Datenverarbeitung zu erfordern. Er eignet sich besonders für passive Signalverteilungen in modularen, adapterbasierten Automatisierungslösungen.
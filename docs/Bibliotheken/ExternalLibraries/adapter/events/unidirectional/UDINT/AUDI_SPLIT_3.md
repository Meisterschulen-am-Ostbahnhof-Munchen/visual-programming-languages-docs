# AUDI_SPLIT_3


![AUDI_SPLIT_3](./AUDI_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_SPLIT_3** dient der Vervielfachung eines eingehenden **AUDI**-Adapter-Signals auf drei separate Ausgänge. Er ist als generischer Baustein (Generic FB) konzipiert und eignet sich besonders für Architekturen, bei denen ein Signal (z. B. ein Steuer- oder Datenstrom) an mehrere nachgelagerte Komponenten verteilt werden muss.

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

| Typ | Name | Beschreibung |
|-----|------|--------------|
| Socket (adapter::types::unidirectional::AUDI) | **IN** | Eingangsadapter zum Empfang des AUDI-Signals |
| Plug (adapter::types::unidirectional::AUDI) | **OUT1** | Erster Ausgangsadapter |
| Plug (adapter::types::unidirectional::AUDI) | **OUT2** | Zweiter Ausgangsadapter |
| Plug (adapter::types::unidirectional::AUDI) | **OUT3** | Dritter Ausgangsadapter |

## Funktionsweise
Der Baustein leitet das am **IN**-Socket anliegende AUDI-Signal unverändert an alle drei **OUT**-Plugs weiter. Es findet keine Umwandlung, Filterung oder logische Verarbeitung statt – die Verteilung erfolgt transparent. Durch die Nutzung von Adaptern des Typs `unidirectional::AUDI` wird sichergestellt, dass die Signalrichtung (Eingang → Ausgänge) eindeutig definiert ist.

## Technische Besonderheiten
- **Generische Realisierung**: Der Baustein ist als generischer FB (`eclipse4diac::core::GenericClassName = 'GEN_AUDI_SPLIT'`) implementiert. Das ermöglicht eine einfache Wiederverwendung in unterschiedlichen Kontexten, ohne dass der konkrete AUDI-Typ bereits zur Entwicklungszeit vollständig festgelegt sein muss.
- **Typ-Hash**: Der Typ-Hash kann bei Bedarf zur Laufzeit gesetzt werden, um eine statische Typprüfung zu ermöglichen.
- **Reine Adapter-Schnittstelle**: Der FB besitzt weder Ereignis- noch Datenein-/ausgänge im klassischen Sinne, sondern kommuniziert ausschließlich über Adapter.

## Zustandsübersicht
Da der FB über keine Ereignis-Eingänge verfügt, besitzt er keinen expliziten Zustandsautomaten. Die Signalweitergabe erfolgt kontinuierlich und asynchron, sobald der IN-Adapter verbunden ist.

## Anwendungsszenarien
- **Signalvervielfachung**: Verteilung eines gemeinsamen Steuer- oder Messsignals an verschiedene Funktionsblöcke (z. B. Parallelschaltung mehrerer Aktoren oder Sensoren).
- **Test- und Simulationsumgebungen**: Einschleusen eines simulierten AUDI-Signals in mehrere unabhängige Analyse- oder Überwachungspfade.
- **Architektur‑Kopplung**: Einsatz in modularen Systemen, bei denen ein Datenstrom an verschiedene Subsysteme weitergegeben werden muss, ohne das Originalsignal zu schwächen.

## Vergleich mit ähnlichen Bausteinen
- **AUDI_MERGE** (Gegenstück): Ein kombinierendes Element, das mehrere AUDI-Eingänge auf einen Ausgang vereint – im Gegensatz zum split‑Baustein.
- **AUDI_SPLIT_2**: Ein auf zwei Ausgänge reduzierter Splitter; der vorliegende Block erweitert dies auf drei Abzweigungen.
- **Generische Splitter**: In vielen Bibliotheken existieren Splitt-Varianten für andere Adaptertypen (z. B. `DATA_SPLIT`), die jedoch datentypspezifisch sind.

## Fazit
Der **AUDI_SPLIT_3** ist ein einfacher, aber nützlicher Funktionsblock zur Verteilung eines unidirektionalen AUDI-Adaptersignals auf drei Ausgänge. Durch seine generische Natur und die reine Adapterschnittstelle fügt er sich nahtlos in ereignisgesteuerte und datenstromorientierte IEC 61499‑Anwendungen ein. Er bietet eine saubere, wartbare Lösung für architektonische Signalfächerungen und reduziert die Notwendigkeit manueller Signalweiterschaltung.
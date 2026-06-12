# AIWS_SPLIT_3


![AIWS_SPLIT_3](./AIWS_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AIWS_SPLIT_3** dient dazu, einen einzelnen eingehenden AIWS-Adapter (Typ `adapter::types::unidirectional::AIWS`) auf drei identische Ausgangsadapter aufzuteilen. Alle Daten, die über den Eingangsadapter empfangen werden, werden unverändert an alle drei Ausgänge weitergeleitet. Der Baustein ist generisch ausgelegt und kann mit verschiedenen AIWS-Typen verwendet werden.

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
| Socket (Eingang) | IN | `adapter::types::unidirectional::AIWS` | Eingangsadapter, der das zu verteilende Signal empfängt. |
| Plug (Ausgang) | OUT1 | `adapter::types::unidirectional::AIWS` | Erster Ausgangsadapter. |
| Plug (Ausgang) | OUT2 | `adapter::types::unidirectional::AIWS` | Zweiter Ausgangsadapter. |
| Plug (Ausgang) | OUT3 | `adapter::types::unidirectional::AIWS` | Dritter Ausgangsadapter. |

## Funktionsweise
Die interne Logik des Bausteins ist denkbar einfach: Sobald der Socket **IN** Daten vom angeschlossenen Adapter empfängt, werden diese Daten simultan an die drei Plugs **OUT1**, **OUT2** und **OUT3** weitergegeben. Es findet keine Transformation, Filterung oder Pufferung statt. Die Datenweitergabe erfolgt unidirektional und ohne zeitliche Verzögerung.

## Technische Besonderheiten
- **Generischer Funktionsbaustein:** Der FB ist als generischer Baustein (`eclipse4diac::core::GenericClassName = 'GEN_AIWS_SPLIT'`) implementiert. Dadurch kann er mit verschiedenen Spezialisierungen des AIWS-Adapters verwendet werden, solange diese dem unidirektionalen Kommunikationsprotokoll entsprechen. Die konkrete Typisierung erfolgt zur Entwurfszeit in der 4diac-IDE.
- **Keine Zustandsautomatik:** Der Baustein besitzt keine Ereignisse und keine Zustandsmaschine (ECC). Die Datenweitergabe erfolgt rein datenflussgetrieben.
- **Skalierbarkeit:** Der Baustein ist speziell für eine 1-zu-3-Aufteilung ausgelegt. Für andere Aufteilungsverhältnisse stehen separate Bausteine (z. B. AIWS_SPLIT_2, AIWS_SPLIT_4) zur Verfügung.

## Zustandsübersicht
Der Baustein besitzt keine Zustandsmaschine (ECC), daher gibt es keine Zustände oder Zustandsübergänge. Die Funktion ist rein kombinatorisch auf Adapterebene.

## Anwendungsszenarien
- **Signalverteilung:** Ein von einer Quelle kommender AIWS-Datenstrom soll parallel an mehrere nachfolgende Verarbeitungsblöcke weitergeleitet werden (z. B. Überwachung, parallele Filterung oder Visualisierung).
- **Redundanz:** Das gleiche Signal wird auf verschiedenen Pfaden genutzt, um Redundanz oder Vergleichbarkeit zu erreichen.
- **Test und Simulation:** In Testumgebungen kann das Eingangssignal ohne Nebenwirkungen mehreren Testmodulen gleichzeitig zur Verfügung gestellt werden.

## Vergleich mit ähnlichen Bausteinen
- **AIWS_SPLIT_2 / AIWS_SPLIT_N:** Bausteine mit gleicher Funktionalität, aber unterschiedlicher Anzahl von Ausgängen (2 bzw. n Ausgänge).
- **ALL_SPLIT (für Daten):** Ein generischer Baustein zum Aufteilen von Daten-Ein-/Ausgängen, nicht spezifisch für Adapter. AIWS_SPLIT_3 ist dagegen speziell für den AIWS-Adapter-Typ optimiert und arbeitet auf Adapterebene.
- **AIWS_JOIN_3:** Der inverse Baustein, der drei AIWS-Eingänge zu einem Ausgang zusammenführt.

## Fazit
Der **AIWS_SPLIT_3** ist ein einfacher aber effektiver generischer Funktionsbaustein zur Vervielfältigung eines AIWS-Adapter-Signals auf drei parallele Ausgänge. Dank seiner generischen Natur lässt er sich flexibel in verschiedenen Automatisierungs- und Steuerungsanwendungen einsetzen, in denen ein Datenstrom mehrfach benötigt wird.
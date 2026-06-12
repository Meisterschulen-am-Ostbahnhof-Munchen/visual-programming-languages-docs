# AQ_SPLIT_3


![AQ_SPLIT_3](./AQ_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AQ_SPLIT_3` realisiert eine 1-zu-3-Aufteilung (Fan-Out) eines unidirektionalen AQ-Adapter-Signals. Ein eingehender AQ-Adapter wird auf drei identische Ausgangs-Adapter kopiert und parallel bereitgestellt.

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

**Socket (Eingang)**

| Bezeichnung | Typ                                      | Beschreibung |
|-------------|------------------------------------------|--------------|
| `IN`        | `adapter::types::unidirectional::AQ`     | Eingangs-Adapter, dessen Signal auf drei Ausgänge verteilt wird |

**Plug (Ausgänge)**

| Bezeichnung | Typ                                      | Beschreibung |
|-------------|------------------------------------------|--------------|
| `OUT1`      | `adapter::types::unidirectional::AQ`     | Erster Ausgang (Kopie des Eingangssignals) |
| `OUT2`      | `adapter::types::unidirectional::AQ`     | Zweiter Ausgang (Kopie des Eingangssignals) |
| `OUT3`      | `adapter::types::unidirectional::AQ`     | Dritter Ausgang (Kopie des Eingangssignals) |

## Funktionsweise

Der Baustein leitet das am Socket `IN` anliegende AQ-Signal ohne Verzögerung oder Datenmanipulation an alle drei Plugs (`OUT1`, `OUT2`, `OUT3`) weiter. Es handelt sich um eine reine Signalverteilung (Fan-Out) – das eingehende Adapter-Interface wird auf drei identische Ausgangs-Interfaces gespiegelt. Da keine Ereignisse oder Daten außerhalb des Adapters verarbeitet werden, erfolgt die Weiterleitung passiv und transparent.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein verwendet das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `'GEN_AQ_SPLIT'`. Dadurch kann er in verschiedenen Kontexten als generischer AQ-Splitter eingesetzt werden.
- **Unidirektional**: Die Adapter sind als unidirektionale AQ-Schnittstellen definiert – die Daten fließen nur vom Eingang zu den Ausgängen.
- **Keine Zustandslogik**: Der Baustein besitzt keine Ereignis-E/A, keinen internen Zustand und keine Daten-E/A. Er fungiert als reine Verbindungslogik.

## Zustandsübersicht

Der Baustein ist zustandslos. Er führt keine zeitabhängigen oder sequenziellen Abläufe aus. Die Ausgangssignale entsprechen stets unmittelbar dem aktuellen Eingangssignal.

## Anwendungsszenarien

- **Signalverteilung in der Automatisierung**: Wenn ein AQ-Signal (z. B. ein Qualitätswert, ein Messwert- oder Status-Adapter) gleichzeitig an mehrere Verbraucher weitergegeben werden muss.
- **Multicasting von Adaptern**: In Architekturen, in denen ein Dienst sein Ergebnis über einen AQ-Adapter an mehrere nachfolgende Bausteine sendet.
- **Generische Kopplung**: Einsatz als generischer Splitter in Bibliotheken oder Frameworks, die auf dem `GEN_AQ_SPLIT`-Typ basieren.

## Vergleich mit ähnlichen Bausteinen

- **AQ_SPLIT_2**: Verteilt nur auf zwei Ausgänge – `AQ_SPLIT_3` bietet einen zusätzlichen dritten Ausgang.
- **Manuelle Dreifachverdrahtung**: Statt eines Bausteins könnte man das Eingangssignal manuell auf drei Sockets verbinden. Der Splitter erhöht jedoch die Übersichtlichkeit und Wartbarkeit des Netzwerks.
- **Generische Splitter anderer Adaptertypen**: Ähnliche Bausteine existieren z. B. für Daten- oder Ereignis-Signale (z. B. `DATA_SPLIT_3`). `AQ_SPLIT_3` ist speziell auf den AQ-Adapter-Typ zugeschnitten.

## Fazit

`AQ_SPLIT_3` ist ein einfacher, funktionaler Fan-Out-Baustein für unidirektionale AQ-Adapter. Dank seiner generischen Auslegung und der klaren 1-zu-3-Verteilung eignet er sich ideal für alle Anwendungen, die ein AQ-Signal mehrfach bereitstellen müssen. Die Abwesenheit von Ereignis- und Daten-E/A macht ihn leichtgewichtig und in beliebigen Ablaufkontexten einsetzbar.
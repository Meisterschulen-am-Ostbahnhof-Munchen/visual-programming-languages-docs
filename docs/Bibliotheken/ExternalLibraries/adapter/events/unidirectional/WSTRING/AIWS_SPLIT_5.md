# AIWS_SPLIT_5


![AIWS_SPLIT_5](./AIWS_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIWS_SPLIT_5** ist ein generischer Baustein zur Aufteilung eines einzelnen **AIWS**‑Adapters auf fünf identische **AIWS**‑Adapter. Er ermöglicht es, ein von einem Socket bereitgestelltes AIWS‑Signal an mehrere unabhängige Adapter‑Plugs weiterzuleiten, ohne dass eine event‑ oder datenverarbeitende Logik erforderlich ist. Dieser FB eignet sich besonders für die Signalverteilung in industriellen Automatisierungsarchitekturen, die auf dem **IEC 61499**‑Standard basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis‑Eingänge vorhanden. Der Baustein arbeitet rein daten‑ bzw. adapter‑basiert.

### **Ereignis-Ausgänge**
Keine Ereignis‑Ausgänge vorhanden. Die Weiterleitung erfolgt implizit über die Adapter‑Schnittstellen.

### **Daten-Eingänge**
Keine Daten‑Eingänge vorhanden. Die gesamte Informationsübertragung erfolgt über den Socket‑Adapter.

### **Daten-Ausgänge**
Keine Daten‑Ausgänge vorhanden. Die Ausgabe geschieht über die Plug‑Adapter.

### **Adapter**

| Typ | Bezeichnung | Richtung | Adapter‑Typ |
|-----|-------------|----------|-------------|
| **Socket (Eingang)** | IN | Eingang | `adapter::types::unidirectional::AIWS` |
| **Plug (Ausgang)** | OUT1 | Ausgang | `adapter::types::unidirectional::AIWS` |
| **Plug (Ausgang)** | OUT2 | Ausgang | `adapter::types::unidirectional::AIWS` |
| **Plug (Ausgang)** | OUT3 | Ausgang | `adapter::types::unidirectional::AIWS` |
| **Plug (Ausgang)** | OUT4 | Ausgang | `adapter::types::unidirectional::AIWS` |
| **Plug (Ausgang)** | OUT5 | Ausgang | `adapter::types::unidirectional::AIWS` |

Der FB enthält einen einzelnen **Socket** (`IN`) und fünf **Plugs** (`OUT1` … `OUT5`), die alle vom gleichen, unidirektionalen **AIWS‑Adaptertyp** sind.

## Funktionsweise

Der **AIWS_SPLIT_5** leitet das an seinem Socket `IN` anliegende Adapter‑Signal unverändert an alle fünf Plug‑Adapter `OUT1` bis `OUT5` weiter. Es erfolgt keine Transformation oder Filterung der Daten – der Baustein fungiert als reiner **Signalverteiler** (Fan‑Out). Sobald eine Verbindung über den Socket hergestellt ist, stehen die Ausgangsadapter sofort für die Kommunikation zur Verfügung. Ereignissteuerung oder zustandsabhängige Logik sind nicht erforderlich.

## Technische Besonderheiten

- **Generische Ausprägung**: Der FB besitzt die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash`, die eine nachträgliche Konfiguration bzw. Typanpassung erlauben. Standardmäßig ist der Klassenname auf `'GEN_AIWS_SPLIT'` gesetzt; der TypeHash ist leer.
- **Einheitlicher Adaptertyp**: Alle Schnittstellen verwenden denselben unidirektionalen AIWS‑Adapter. Dadurch ist die Kompatibilität zwischen Ein‑ und Ausgängen sichergestellt.
- **Keine Daten‑ oder Event‑Ports**: Die gesamte Kommunikation erfolgt ausschließlich über die Adapter‑Schnittstellen, was die Konfiguration vereinfacht und die Anzahl der Verbindungen reduziert.

## Zustandsübersicht

Der **AIWS_SPLIT_5** besitzt keine explizite Zustandsmaschine. Seine Funktionalität ist rein kombinatorisch – sobald der Socket verbunden ist, liegen an allen Ausgängen die gleichen Adapter‑Signale an. Daher existieren keine internen Zustände, die das Verhalten beeinflussen.

## Anwendungsszenarien

- **Signalverteilung in modularen Anlagen**: Ein von einem Sensor oder einer Steuerung bereitgestelltes AIWS‑Signal muss parallel an mehrere Verbraucher (z. B. Aktoren, HMI‑Systeme, übergeordnete Controller) weitergeleitet werden.
- **Test‑ und Simulationsumgebungen**: Ein einzelnes AIWS‑Signal wird zur Überwachung oder Aufzeichnung an verschiedene Test‑ und Analysekomponenten verteilt.
- **Redundante Verarbeitung**: In sicherheitskritischen Systemen kann das identische Signal an mehrere unabhängige Logikeinheiten geführt werden, um eine parallele Auswertung zu ermöglichen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Typ | Besonderheit |
|----------|-----------------|-----|--------------|
| **AIWS_SPLIT_5** | 5 | AIWS‑Adapter | Generisch, keine Events/Daten |
| AIWS_SPLIT_2 | 2 | AIWS‑Adapter | Gleiche Funktionsweise, minimale Verteilung |
| AIWS_SPLIT_3 | 3 | AIWS‑Adapter | Mittlere Anzahl Ausgänge |
| AIWS_SPLIT_4 | 4 | AIWS‑Adapter | Alternative zu **5** |

Alle Split‑Varianten basieren auf demselben Prinzip und unterscheiden sich lediglich in der Anzahl der Ausgangsadapter. Der **AIWS_SPLIT_5** deckt einen mittleren Verteilungsbedarf ab und ist besonders dann vorteilhaft, wenn genau fünf parallele Ausgänge benötigt werden.

## Fazit

Der **AIWS_SPLIT_5** ist ein einfacher, aber essenzieller Funktionsblock zur Vervielfältigung von AIWS‑Adapter‑Signalen. Durch seine generische Auslegung und den Verzicht auf Events oder Datenportierung lässt er sich ohne zusätzliche Konfiguration in bestehende IEC 61499‑Applikationen integrieren. Ideal für Anwendungen, die eine punktgenaue Verteilung eines Adapters auf bis zu fünf unabhängige Pfade erfordern.
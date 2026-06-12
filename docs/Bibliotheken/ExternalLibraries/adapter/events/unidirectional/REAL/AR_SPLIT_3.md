# AR_SPLIT_3


![AR_SPLIT_3](./AR_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AR_SPLIT_3** dient als generischer Splitter für Adapterverbindungen. Er verteilt einen eingehenden Daten- und Ereignisstrom (über einen `AR`-Adapter) auf drei separate, identisch strukturierte Ausgangsadapter. Dies ermöglicht eine effiziente Mehrfachnutzung von Informationen in Automatisierungsabläufen, ohne die Logik zu duplizieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine – der Baustein besitzt ausschließlich Adapter-Schnittstellen. Ereignisse werden implizit über den Socket `IN` (vom Typ `AR`) übertragen.

### **Ereignis-Ausgänge**
Keine – Ereignisse werden über die Plugs `OUT1`, `OUT2` und `OUT3` (Typ `AR`) weitergegeben.

### **Daten-Eingänge**
Keine – alle Daten werden über den Adapter `IN` bereitgestellt.

### **Daten-Ausgänge**
Keine – alle Daten werden über die drei Ausgangsadapter (`OUT1`, `OUT2`, `OUT3`) ausgegeben.

### **Adapter**

| Richtung | Name  | Typ                        | Beschreibung                                    |
|----------|-------|----------------------------|-------------------------------------------------|
| Socket   | `IN`  | `adapter::types::unidirectional::AR` | Eingehender Adapter als Quelle der Daten/Ereignisse. |
| Plug     | `OUT1`| `adapter::types::unidirectional::AR` | Erster ausgehender Adapter (Ziel 1).            |
| Plug     | `OUT2`| `adapter::types::unidirectional::AR` | Zweiter ausgehender Adapter (Ziel 2).           |
| Plug     | `OUT3`| `adapter::types::unidirectional::AR` | Dritter ausgehender Adapter (Ziel 3).           |

## Funktionsweise

Der Baustein realisiert eine **1:3-Verteilung** auf Adapterebene. Ein an `IN` anliegender `AR`-Adapter (unidirektional) wird intern auf die drei Ausgangsadapter `OUT1`, `OUT2` und `OUT3` aufgeschaltet.  
Jedes an `IN` eingehende Ereignis oder Datenpaket wird gleichzeitig an alle drei Ausgänge weitergeleitet. Die Verteilung erfolgt ohne Verzögerung und ohne Datenveränderung. Der Baustein ist generisch und kann mit beliebigen `AR`-Adapterprofilen verwendet werden – seine interne Logik passt sich automatisch der Struktur des eingesetzten Adaptertyps an.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Baustein (`GEN_AR_SPLIT`) ausgelegt und kann mit unterschiedlichen `AR`-Adapterdefinitionen (unidirektional) verwendet werden, sofern die Schnittstellen kompatibel sind.
- **Unidirektionale Adapter**: Sowohl Eingang als auch Ausgänge sind unidirektional, d.h. die Daten‑/Ereignisrichtung ist fest vorgegeben (vom Sender zum Empfänger). Eine Rückkopplung ist über diesen Baustein nicht möglich.
- **Einfache Skalierung**: Die Aufteilung erfolgt ohne zusätzliche Konfiguration. Für andere Anzahlen von Ausgängen können Varianten wie `AR_SPLIT_2` oder ein parametrierbarer Splitter (`AR_SPLIT_N`) eingesetzt werden.
- **Keine Zustandsänderung**: Der Baustein besitzt keinen internen Speicher und keine Zustandsmaschine – jedes Ereignis wird sofort und vollständig repliziert.

## Zustandsübersicht

Der Baustein ist **zustandslos** (kombinatorisch). Es gibt keine internen Zustände oder sequenziellen Abläufe. Die Verteilung erfolgt rein durch Verbindung der Adapter‑Signale.

## Anwendungsszenarien

- **Verteilen von Sensordaten** an mehrere parallele Verarbeitungslogiken (z.B. Auswertung, Visualisierung, Protokollierung).
- **Ansteuern mehrerer Aktorik‑Gruppen** mit einem identischen Steuersignal (z.B. parallele Ventil‑ oder Motorsteuerung).
- **Aufteilen eines Steuerungsereignisses** in verschiedene Funktionsbausteine, ohne die Quelllogik zu kopieren.
- **Debugging und Monitoring**: Ein Signal kann an einen echten Empfänger und parallel an eine Überwachungskomponente geleitet werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein       | Beschreibung                                                                 |
|----------------|-----------------------------------------------------------------------------|
| **AR_SPLIT_2** | Verteilung auf zwei Ausgänge – kompakter für kleinere Anwendungen.          |
| **AR_SPLIT_N** | Verteilung auf eine konfigurierbare Anzahl von Ausgängen (generischer).     |
| **AR_CONNECT** | Einfache 1:1-Verbindung (keine Verteilung).                                 |

Im Gegensatz zu dedizierten Splittern mit Daten‑ oder Ereignis‑Ein‑/Ausgängen arbeitet der `AR_SPLIT_3` ausschließlich über Adapter, was ihn besonders flexibel und typenunabhängig macht.

## Fazit

**AR_SPLIT_3** ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Mehrfachverteilung von Adapter‑Signalen. Er reduziert den Aufwand für die Signalvervielfältigung in IEC 61499‑Applikationen und trägt durch seine generische Natur zur Wiederverwendbarkeit und Übersichtlichkeit von Steuerungslogiken bei. Dank des reinen Adapter‑Ansatzes kann er ohne Modifikation in unterschiedlichste Umgebungen integriert werden.
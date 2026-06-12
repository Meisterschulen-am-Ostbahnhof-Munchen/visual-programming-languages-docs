# ALI_SPLIT_2


![ALI_SPLIT_2](./ALI_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_SPLIT_2** dient als generischer Verteiler für einen unidirektionalen ALI‑Adapter (Application Layer Interface). Er kopiert alle eingehenden Daten und Ereignisse von einem einzelnen Eingangs‑Socket auf zwei Ausgangs‑Plugs. Dadurch kann ein Signal oder eine Datenquelle an zwei unabhängige Empfänger weitergegeben werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden. Die Datenweitergabe erfolgt rein über die Adapter‑Schnittstelle.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden. Die Ereignissteuerung wird über die Adapter‑Verbindungen abgewickelt.

### **Daten-Eingänge**

Keine dedizierten Daten-Eingänge. Alle Daten werden über den eingehenden Adapter **IN** bereitgestellt.

### **Daten-Ausgänge**

Keine dedizierten Daten-Ausgänge. Die verteilten Daten werden über die beiden ausgehenden Adapter **OUT1** und **OUT2** bereitgestellt.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| **Socket** | `IN` | Eingang | Unidirektionaler ALI‑Adapter, der die eingehenden Daten/Ereignisse empfängt. |
| **Plug** | `OUT1` | Ausgang | Erster unidirektionaler ALI‑Adapter, an den die Daten/Ereignisse weitergeleitet werden. |
| **Plug** | `OUT2` | Ausgang | Zweiter unidirektionaler ALI‑Adapter, an den die Daten/Ereignisse weitergeleitet werden. |

Alle Adapter sind vom Typ `adapter::types::unidirectional::ALI`.

## Funktionsweise

Der Baustein realisiert eine 1‑zu‑2‑Verteilung (Split) auf der Adapter‑Ebene. Sobald Daten oder Ereignisse am Socket **IN** anliegen, werden diese unverändert und gleichzeitig an beide Plugs **OUT1** und **OUT2** weitergegeben. Es erfolgt keine Pufferung oder Verarbeitung der Daten – der Baustein arbeitet als reiner Signalverteiler.

## Technische Besonderheiten

- **Generischer Baustein**: Über das Attribut `eclipse4diac::core::GenericClassName` wird der Baustein als generische Instanz `GEN_ALI_SPLIT` markiert. Er kann daher mit unterschiedlichen ALI‑Typen oder ‑Parametern verwendet werden, solange die zugrundeliegende Adapter‑Definition kompatibel ist.
- **Keine Zustandshaltung**: Der Baustein besitzt keine internen Zustände oder Variablen – die Funktionalität ist rein kombinatorisch.
- **Unidirektionalität**: Die Adapter sind als unidirektional definiert, d.h. die Daten fließen nur vom Eingang zu den Ausgängen; Rückwärtskommunikation ist nicht vorgesehen.

## Zustandsübersicht

Da der Baustein keine Ereignis‑Eingänge/Ausgänge oder internen Zustände besitzt, existiert keine Zustandsmaschine. Die Datenweitergabe erfolgt kontinuierlich und ohne Verzögerung.

## Anwendungsszenarien

- **Verteilen eines Sensorsignals**: Ein analoger oder digitaler ALI‑Sensor wird an zwei Steuerungseinheiten angeschlossen, die unabhängig voneinander auf die Messdaten zugreifen müssen.
- **Parallele Verarbeitung**: Ein Datenstrom soll gleichzeitig von zwei verschiedenen Funktionsblöcken verarbeitet werden, ohne dass eine manuelle Verzweigung in der Applikation nötig ist.
- **Redundanz**: Eine Anwendung erfordert die doppelte Ausführung einer ALI‑Kommunikation, um Ausfallsicherheit zu erhöhen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| **ALI_SPLIT_2** | Verteilt einen ALI‑Eingang auf zwei ALI‑Ausgänge. | – |
| **ALI_SPLIT_3** (hypothetisch) | Verteilt auf drei Ausgänge. | Höhere Ausgangszahl. |
| **ALI_MERGE_2** | Fasst zwei ALI‑Eingänge zu einem ALI‑Ausgang zusammen. | Gegenteilige Funktion (Join). |
| **ALI_FILTER** | Leitet nur bestimmte Daten/Ereignisse weiter. | Enthält Filterlogik. |

## Fazit

**ALI_SPLIT_2** ist ein einfacher, aber essenzieller Funktionsblock für die Verteilung unidirektionaler ALI‑Schnittstellen. Seine generische Natur und die schlanke Implementierung machen ihn zu einem universellen Werkzeug in der IEC 61499‑Komponentenentwicklung, wenn ein Signal oder Datenstrom an mehrere nachfolgende Blöcke weitergegeben werden muss.
# ADI_DEMUX_3


![ADI_DEMUX_3](./ADI_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_DEMUX_3** ist ein generischer Demultiplexer für Adapter-Daten (ADI). Er leitet einen eingehenden ADI-Wert über den Adapter-Socket **IN** abhängig vom Index **K** an einen der drei Ausgangs-Adapter **OUT1**, **OUT2** oder **OUT3** weiter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**   | Setzt den Index **K** und löst die Weiterleitung des eingehenden Werts an den entsprechenden Ausgang aus. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**   | Bestätigung, dass der Demultiplex-Vorgang abgeschlossen ist und der Index **K** übernommen wurde. |

### **Daten-Eingänge**
| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **K**    | UINT  | Index (1‑basiert) zur Auswahl des Ausgangs. Gültige Werte: 1, 2, 3. Werte außerhalb dieses Bereichs führen zu keinem aktiven Ausgang. |

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die Adapter.

### **Adapter**
| Richtung | Bezeichnung | Typ | Beschreibung |
|----------|-------------|-----|--------------|
| **Socket** (Eingang) | **IN** | `adapter::types::unidirectional::ADI` | Eingangs-Adapter, der den zu multiplexenden Datenwert bereitstellt. |
| **Plug** (Ausgang) | **OUT1** | `adapter::types::unidirectional::ADI` | Erster Ausgang (Auswahl bei K=1). |
| **Plug** (Ausgang) | **OUT2** | `adapter::types::unidirectional::ADI` | Zweiter Ausgang (Auswahl bei K=2). |
| **Plug** (Ausgang) | **OUT3** | `adapter::types::unidirectional::ADI` | Dritter Ausgang (Auswahl bei K=3). |

## Funktionsweise
Der Baustein arbeitet als 1‑zu‑3‑Demultiplexer über die ADI‑Adapter:
1. Der Wert am Socket **IN** wird permanent empfangen.
2. Beim Eintreffen eines Ereignisses **REQ** wird der aktuelle Wert des Index **K** ausgewertet.
3. Abhängig von **K** wird der eingehende ADI‑Wert an den entsprechenden Plug weitergegeben:
   - **K = 1** → **OUT1** wird mit dem Wert von **IN** versorgt.
   - **K = 2** → **OUT2** wird aktiv.
   - **K = 3** → **OUT3** wird aktiv.
4. Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben.
5. Bei ungültigen Werten von **K** (z. B. 0 oder >3) wird kein Ausgang aktiv und **CNF** dennoch signalisiert, um eine konsistente Ablaufsteuerung zu ermöglichen.

## Technische Besonderheiten
- **Generische Auslegung**: Der Baustein ist als generischer FB mit dem Klassennamen `'GEN_ADI_DEMUX'` deklariert. Er kann über Attribute wie `eclipse4diac::core::GenericClassName` in der Entwicklungsumgebung als Vorlage für andere Demultiplexer-Varianten verwendet werden.
- **Versionsinformationen**: Entwickelt von **Franz Höpfinger** für die **HR Agrartechnik GmbH**, Version 1.0, veröffentlicht am **2026‑05‑28**.
- **Lizenz**: Unter der **Eclipse Public License 2.0** (EPL‑2.0) veröffentlicht.
- **Compiler-Import**: Der Baustein importiert `eclipse4diac::core::TypeHash` zur Unterstützung von Typüberprüfungen.

## Zustandsübersicht
Der FB besitzt keine explizit modellierten Zustände. Die interne Logik verarbeitet bei jedem **REQ**‑Ereignis den Index **K** und aktualisiert die Ausgangs‑Adapter instantan. Eine sequenzielle Zustandsmaschine ist nicht erforderlich, da der Demultiplex-Vorgang ereignisgesteuert und atomar abläuft.

## Anwendungsszenarien
- **Signalverteilung in Adapter‑basierten Steuerungen**: Ein einzelner Sensor‑ oder Daten‑Adapter (z. B. für Temperatur, Druck) soll auf mehrere parallele Verarbeitungspfade aufgeteilt werden.
- **Kanalumschaltung in modularen Automatisierungslösungen**: Je nach Auswahlindex wird eine Verbindung zu verschiedenen Aktoren oder Subsystemen hergestellt.
- **Test‑ und Simulationsumgebungen**: Ein Testsignal kann dynamisch an unterschiedliche Funktionsblöcke weitergeleitet werden, ohne die Verkabelung zu ändern.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Anzahl Ausgänge | Adaptertyp | Besonderheit |
|----------|-----------------|------------|--------------|
| **ADI_DEMUX_3** (dieser FB) | 3 (OUT1‑3) | ADI unidirektional | Generisch, ereignisgesteuerte Umschaltung |
| Andere Demultiplexer (z. B. `MUX`‑Familie) | variabel (2, 4, …) | ADI oder Standard‑Datentypen | Oft mit Enable‑Eingang oder mehreren Auswahlbits |
| Einfache Adapter‑Splits (z. B. `ADAPTER_SPLIT`) | meist feste Anzahl | bidirektional oder unidirektional | Keine Auswahlmöglichkeit – alle Ausgänge erhalten das gleiche Signal |

Der **ADI_DEMUX_3** zeichnet sich durch die explizite Index‑Auswahl (UINT) aus, was eine flexible Programmierung ohne zusätzliche Multiplex‑Logik ermöglicht. Im Gegensatz zu festverdrahteten Splits erlaubt er die gezielte Kanalwahl zur Laufzeit.

## Fazit
Der Funktionsblock **ADI_DEMUX_3** ist ein einfacher, aber effektiver Demultiplexer für ADI‑Datenströme. Dank seiner generischen Struktur und der klaren ereignisgesteuerten Arbeitsweise eignet er sich hervorragend für den Einsatz in modularen, adapterbasierten Automatisierungsprojekten. Durch die Auswahl eines von drei Ausgängen über einen Index entsteht eine saubere Trennung von Signalquellen und Senken, ohne dass aufwändige eigene Multiplex‑Logik implementiert werden muss.
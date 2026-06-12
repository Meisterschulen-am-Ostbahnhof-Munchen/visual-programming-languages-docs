# AULI_SPLIT_4


![AULI_SPLIT_4](./AULI_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_SPLIT_4** dient dazu, einen eingehenden **AULI**-Adapter in vier separate, identische Ausgänge aufzuteilen. Er ist als generischer Baustein (Generic FB) ausgelegt und wird unter der Eclipse Public License 2.0 vertrieben. Entwickelt wurde er für die Verwendung in der Automatisierungstechnik, insbesondere im Umfeld der HR Agrartechnik GmbH.

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

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AULI` | `IN` | Socket | Eingangsadapter für das zu verteilende AULI-Signal |
| `adapter::types::unidirectional::AULI` | `OUT1` | Plug | Erster Ausgangsadapter (identisch zum Eingang) |
| `adapter::types::unidirectional::AULI` | `OUT2` | Plug | Zweiter Ausgangsadapter |
| `adapter::types::unidirectional::AULI` | `OUT3` | Plug | Dritter Ausgangsadapter |
| `adapter::types::unidirectional::AULI` | `OUT4` | Plug | Vierter Ausgangsadapter |

## Funktionsweise

Der Baustein arbeitet als passive Verteiler-Struktur. Der an `IN` anliegende AULI-Adapter wird intern auf die vier Ausgänge `OUT1` bis `OUT4` durchgeschaltet. Da keine aktive Logik, Verarbeitung oder Zwischenspeicherung stattfindet, werden die am Eingang anliegenden Daten (z. B. Signale, Werte, Zustände) unverändert an alle vier Ausgänge weitergegeben. Die Verbindung ist unidirektional – Änderungen an den Ausgängen wirken nicht auf den Eingang zurück.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als Generic FB mit dem generischen Klassennamen `GEN_AULI_SPLIT` deklariert. Das ermöglicht eine flexible Anpassung und Wiederverwendung in verschiedenen Kontexten (z. B. durch Parametrisierung bei der Instanziierung).
- **Unidirektionale Adapter**: Alle verwendeten Adapter sind vom Typ `adapter::types::unidirectional::AULI`, d. h. sie unterstützen nur einen Datenfluss in eine Richtung.
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 lizenziert und darf entsprechend den Bedingungen dieser Lizenz genutzt und modifiziert werden.
- **Keine eigenen Ereignisse oder Daten**: Die gesamte Funktionalität wird ausschließlich über Adapter realisiert. Dies reduziert den Overhead und vereinfacht die Integration in bestehende 4diac-Architekturen.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten (keine ECC‑Zustände). Er verhält sich stateless: Die Ausgänge spiegeln stets den aktuellen Zustand des Eingangs wider. Eine Initialisierung oder besondere Zustandsübergänge sind nicht erforderlich.

## Anwendungsszenarien

- **Signalverteilung**: Ein AULI‑basiertes Signal (z. B. Steuerbefehl, Messwert) soll an mehrere Verbraucher oder nachgeschaltete Funktionsblöcke weitergeleitet werden.
- **Redundanz oder Parallelverarbeitung**: Mehrere unabhängige Instanzen einer Komponente benötigen denselben Eingangswert – der Split ermöglicht eine einfache Aufteilung ohne zusätzliche Logik.
- **Test- und Simulationsumgebungen**: In Testaufbauten kann ein AULI‑Signal an mehrere Beobachter oder Protokollierer verteilt werden.

## Vergleich mit ähnlichen Bausteinen

Der **AULI_SPLIT_4** ist ein spezialisierter Split-Baustein ausschließlich für den unidirektionalen AULI‑Adaptertyp. Im Gegensatz zu allgemeinen Split-Bausteinen (z. B. `SPLIT` für verschiedene Datentypen) ist er auf genau eine Adapter‑Schnittstelle festgelegt, was die Typklarheit erhöht und Fehlkonfigurationen vermeidet. Er unterscheidet sich von aktiven Verteilern (z. B. `MUX` oder `DEMUX`) durch seine passive, verlustfreie Verteilung ohne Umschaltlogik oder Adressierung.

## Fazit

Der **AULI_SPLIT_4** ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfachung eines AULI-Adapters auf vier Ausgänge. Durch die generische Auslegung und den Verzicht auf überflüssige Logik fügt er sich nahtlos in modulare 4diac‑Projekte ein. Er eignet sich besonders für Anwendungen, in denen ein Signal an mehrere Empfänger weitergegeben werden muss, ohne dass eine Weiterverarbeitung oder Selektion gewünscht ist.
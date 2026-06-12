# AUS_TO_ALR


![AUS_TO_ALR](./AUS_TO_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUS_TO_ALR** ist ein Composite-Baustein, der einen **AUS-Adapter** (mit USINT-Daten) in einen **ALR-Adapter** (mit LREAL-Daten) umwandelt. Er dient als reine Weiterleitungsschnittstelle und führt keine komplexe Logik oder Konvertierungsberechnung durch.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge vorhanden. Die Ereignisweiterleitung erfolgt über den **AUS_IN**‑Adapter.

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt über den **ALR_OUT**‑Adapter.

### **Daten-Eingänge**
Keine separaten Daten-Eingänge vorhanden. Die Datenweiterleitung erfolgt über den **AUS_IN**‑Adapter.

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge vorhanden. Die Datenweiterleitung erfolgt über den **ALR_OUT**‑Adapter.

### **Adapter**

| Rolle | Name | Typ | Kommentar |
|-------|------|-----|-----------|
| **Socket (Eingang)** | AUS_IN | `adapter::types::unidirectional::AUS` | USINT‑Adapter‑Eingang |
| **Plug (Ausgang)**  | ALR_OUT | `adapter::types::unidirectional::ALR` | LREAL‑Adapter‑Ausgang |

- Der **AUS_IN**‑Adapter stellt die Schnittstelle für eingehende USINT-Daten inklusive eines zugehörigen Ereignisses bereit.
- Der **ALR_OUT**‑Adapter stellt die Schnittstelle für ausgehende LREAL-Daten inklusive eines zugehörigen Ereignisses bereit.
- Im Inneren des Bausteins werden die Ereignisse (`E1`) und Daten (`D1`) direkt von der *AUS_IN*‑Schnittstelle auf die *ALR_OUT*‑Schnittstelle durchverbunden.

## Funktionsweise

1. **Ereignisweiterleitung**: Das am **AUS_IN**‑Adapter anliegende Ereignis (`E1`) wird unverändert an den **ALR_OUT**‑Adapter (`E1`) weitergegeben.
2. **Datenweiterleitung**: Der Datenwert (`D1`) vom **AUS_IN**‑Adapter wird direkt an den **ALR_OUT**‑Adapter (`D1`) übergeben.
3. **Datentypumwandlung**: Die eigentliche Umwandlung von `USINT` (ganzzahliger 8‑Bit‑Wert) in `LREAL` (64‑Bit‑Gleitkommazahl) erfolgt **nicht innerhalb des FB** – hierfür ist der **AUS_TO_ALR**‑Block lediglich eine strukturelle Hülle. Die Konvertierung muss entweder durch die angeschlossenen Adapter oder durch vorgelagerte Funktionsbausteine realisiert werden.

Der Baustein selbst enthält keine Berechnungslogik und keine Zustandsmaschine; er besteht ausschließlich aus Verbindungen zwischen den Adaptern.

## Technische Besonderheiten

- **Composite‑FB**: Der Baustein ist als Komposit (Composite Function Block) realisiert, dessen internes Netzwerk nur zwei Verbindungen enthält.
- **Keine eigene Logik**: Alle Funktionalität wird durch externe Bausteine oder die Adapter‑Implementierung bereitgestellt.
- **Typkonformität**: Die Verbindung von `AUS.D1` (USINT) zu `ALR.D1` (LREAL) setzt voraus, dass die zugrundeliegende Adapter‑Implementierung eine implizite Typumwandlung erlaubt. Bei Vorsicht ist eine explizite Konvertierung außerhalb des FB notwendig.

## Zustandsübersicht

Der Baustein besitzt **keine eigene Zustandsmaschine**. Er arbeitet transparent: Sobald ein Ereignis am Eingangsadapter eintrifft, wird es sofort an den Ausgangsadapter weitergeleitet. Es gibt keine Verzögerungen, Speicherung oder interne Zustände.

## Anwendungsszenarien

- **Anbindung heterogener Steuerungssysteme**: Ein Sensor liefert Werte als USINT über einen AUS‑Adapter, während das nachfolgende Steuerungsmodul LREAL über einen ALR‑Adapter erwartet.
- **Strukturelle Anpassung**: Der FB dient als reiner Umsetzungsadapter, wenn Protokoll‑/Schnittstellen‑Adaptertypen unterschiedliche Datenformate verwenden.
- **Test‑ und Simulationsumgebungen**: Einfaches Durchschleifen von Daten und Ereignissen zur Erprobung von Adapter‑Kommunikation.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | AUS_TO_ALR | Typische Konvertierungs‑FBs (z. B. USINT_TO_LREAL) |
|---------|------------|-----------------------------------------------------|
| Eingang / Ausgang | Adapter‑Schnittstellen | Einzelne Daten‑Eingänge/-Ausgänge |
| Ereignisverarbeitung | Durchleitung über Adapter | Eigene Ereignis‑E/K‑Paare |
| Implementierung | Composite (nur Verbindungen) | Ausführbare Algorithmen |
| Typumwandlung | Nicht im FB enthalten | Explizite Konvertierung durch Algorithmus |

Während ein klassischer *USINT_TO_LREAL*‑FB die Wertkonvertierung selbst vornimmt, bietet **AUS_TO_ALR** nur die Adapter‑Anpassung. Für die eigentliche Datenumwandlung muss ein separater Funktionsbaustein zwischengeschaltet werden.

## Fazit

Der **AUS_TO_ALR**‑Funktionsblock ist ein einfacher, aber nützlicher Composite‑Baustein zur strukturellen Adaption zwischen einem AUS‑ und einem ALR‑Adapter. Er übernimmt keine Datenkonvertierung, sondern ermöglicht die nahtlose Weiterleitung von Ereignissen und Werten zwischen unterschiedlichen Adapter‑Schnittstellen. Aufgrund seiner minimalistischen Ausführung eignet er sich besonders für Integrations‑ und Testaufgaben, bei denen die eigentliche Typumwandlung extern erfolgt.
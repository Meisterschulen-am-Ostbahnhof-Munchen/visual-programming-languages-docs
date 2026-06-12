# AULI_FB_CTUD


![AULI_FB_CTUD](./AULI_FB_CTUD.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_FB_CTUD** implementiert einen Aufwärts-/Abwärtszähler für vorzeichenlose 64-Bit-Ganzzahlen (ULINT). Er nutzt ausschließlich Adapter-Schnittstellen nach dem IEC 61499‑2 Standard für Ereignis- und Datenverbindungen. Der Baustein kapselt den Standard-FB `FB_CTUD_ULINT` und erweitert dessen Ein‑ und Ausgänge um adapterbasierte Anschlüsse, was eine flexible und standardisierte Integration in adapterorientierte Architekturen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Block verfügt über keine klassischen Ereigniseingänge. Stattdessen werden die Zählereignisse über die **Adapter-Sockets** übertragen:
- **CU** (Count Up) – Ereignis über `CU.E1`
- **CD** (Count Down) – Ereignis über `CD.E1`
- **R** (Reset) – Ereignis über `R.E1`
- **LD** (Load) – Ereignis über `LD.E1`
- **PV** (Preset Value) – Ereignis über `PV.E1`

### **Ereignis-Ausgänge**

- **CNF** – Standard-Ereignisausgang, der bei jeder Zähleraktualisierung ausgelöst wird.

Zusätzlich werden Ereignisse über die **Adapter-Plugs** ausgegeben:
- **QU.E1** – Ereignis bei Zählerüberlauf (Maximalwert erreicht)
- **QD.E1** – Ereignis bei Zählerunterlauf (Wert 0)
- **CV.E1** – Ereignis zur Aktualisierung des aktuellen Zählerstands

### **Daten-Eingänge**

Der Block besitzt keine separaten Dateneingänge. Alle Eingangsdaten werden über die Adapter-Sockets bereitgestellt:
- **CU.D1** (BOOL) – Aktivierung Inkrement (TRUE steigert den Zähler bei CU.E1)
- **CD.D1** (BOOL) – Aktivierung Dekrement
- **R.D1** (BOOL) – Aktivierung Reset
- **LD.D1** (BOOL) – Aktivierung Load
- **PV.D1** (ULINT) – Wert für den Load-Vorgang

### **Daten-Ausgänge**

Es gibt keine separaten Datenausgänge. Die Ausgangsdaten werden über die Adapter-Plugs ausgegeben:
- **QU.D1** (BOOL) – Signalisiert Erreichen des Maximalwerts
- **QD.D1** (BOOL) – Signalisiert Erreichen von 0
- **CV.D1** (ULINT) – Aktueller Zählerstand

### **Adapter**

| Adapter | Richtung | Typ   | Zweck |
|---------|----------|-------|-------|
| **CU**  | Socket   | AX    | Count Up – Ereignis + Boolesche Freigabe |
| **CD**  | Socket   | AX    | Count Down – Ereignis + Boolesche Freigabe |
| **R**   | Socket   | AX    | Reset – Ereignis + Boolesche Freigabe |
| **LD**  | Socket   | AX    | Load – Ereignis + Boolesche Freigabe |
| **PV**  | Socket   | AULI  | Preset Value – Ereignis + ULINT-Wert |
| **QU**  | Plug     | AX    | Output Up – Ereignis + Boolescher Zustand |
| **QD**  | Plug     | AX    | Output Down – Ereignis + Boolescher Zustand |
| **CV**  | Plug     | AULI  | Current Value – Ereignis + ULINT-Zählerstand |

## Funktionsweise

Der Baustein reagiert auf Ereignisse an den Eingangsadaptern (`CU.E1`, `CD.E1`, `R.E1`, `LD.E1`, `PV.E1`). Für jedes Ereignis wird der zugehörige Datenwert (`DX.D1`) ausgewertet:

- **CU**: Wenn `CU.E1` kommt und `CU.D1 = TRUE`, wird der Zähler inkrementiert.
- **CD**: Wenn `CD.E1` kommt und `CD.D1 = TRUE`, wird der Zähler dekrementiert.
- **R**: Wenn `R.E1` kommt und `R.D1 = TRUE`, wird der Zähler auf 0 zurückgesetzt.
- **LD**: Wenn `LD.E1` kommt und `LD.D1 = TRUE`, wird der Zähler auf den Wert von `PV.D1` gesetzt.

Nach jeder Verarbeitung wird das Ereignis `CNF` ausgegeben. Gleichzeitig werden die Ausgangsadapter aktualisiert:
- `QU.D1` wird `TRUE`, wenn der Zähler den Maximalwert (`2^64 - 1`) erreicht hat.
- `QD.D1` wird `TRUE`, wenn der Zählerstand 0 ist.
- `CV.D1` liefert den aktuellen Zählerstand.

Der gesamte Ablauf erfolgt synchron – jedes eingehende Ereignis löst eine Berechnung und anschließend die Ausgabe der Ergebnisse aus.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**: Alle Ein- und Ausgaben erfolgen über Adapter (Sockets/Plugs). Dies ermöglicht eine losgelöste Verbindung zwischen Bausteinen und vereinfacht die Wiederverwendung in verschiedenen Kontexten.
- **Unidirektionale Adapter**: Die verwendeten Adapter (AX, AULI) sind unidirektional – Sockets empfangen, Plugs senden.
- **Triggerverhalten**: Der Baustein feuert die Ausgangsereignisse (`QU.E1`, `QD.E1`, `CV.E1`) bei **jeder** Zähleraktualisierung (auch bei Reset oder Load). Für eine änderungsbasierte Auslösung muss ein AX_D_FF (Differentiator) vorgeschaltet werden.
- **Wertebereich**: Der Zähler arbeitet im Bereich 0 … 2^64‑1 (ULINT). Überläufe werden durch `QU` signalisiert, Unterläufe durch `QD`.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten; das Zählverhalten wird durch den internen `FB_CTUD_ULINT` realisiert. Im Wesentlichen werden drei Zustände unterschieden:

1. **Normalbetrieb** – Der Zählerwert liegt zwischen 1 und `2^64‑2`. Weder `QU` noch `QD` sind aktiv.
2. **Überlauf** – Der Zähler hat den Maximalwert erreicht. `QU.D1 = TRUE`.
3. **Unterlauf** – Der Zählerstand ist 0. `QD.D1 = TRUE`.

Nach Reset (`R`) oder Load (`LD`) kann der Zähler sofort in einen dieser Zustände springen.

## Anwendungsszenarien

- **Industrielle Stückzähler**: Erfassung von Produktionsmengen mit Auf‑ und Abwärtszählung (z. B. Gut‑/Schlechtteile).
- **Paletten‑ oder Werkstückverfolgung**: Zählen von Ein‑ und Ausgängen in einem Pufferspeicher.
- **Ereignisgesteuerte Systeme**: Kombination mit Sensoren (Lichtschranken, Näherungsschalter) über die Adapter‑Schnittstellen.
- **Adapter‑basierte Steuerungsarchitekturen**: Nahtlose Integration in Projekte, die das Socket/Plug‑Konzept von IEC 61499‑2 nutzen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| `FB_CTUD_ULINT` | Gleiche Zählerlogik, aber mit separaten Ereignis‑ und Dateneingängen/-ausgängen (keine Adapter). |
| `AULI_FB_CTU` | Nur Aufwärtszähler, als Adapterversion. |
| `AULI_FB_CTD` | Nur Abwärtszähler, als Adapterversion. |
| `CTUD` (Standard IEC 61499) | Ähnliche Funktionalität, aber meist mit anderen Datentypen (z. B. INT) und ohne Adapter. |

Der `AULI_FB_CTUD` vereint Auf‑ und Abwärtszählung in einem Block und bietet durch die Adapter‑Schnittstellen eine besonders flexible Anbindung an andere adapterbasierte Komponenten.

## Fazit

Der `AULI_FB_CTUD` ist ein leistungsfähiger Aufwärts-/Abwärtszähler für ULINT‑Werte, der sich durch seine vollständige Adapter‑Schnittstelle auszeichnet. Er kombiniert bewährte Zähllogik mit der Flexibilität des IEC 61499‑2 Adapterkonzepts. Dank der einheitlichen Ereignis‑ und Datenübertragung über Plugs und Sockets eignet er sich besonders für modulare, wiederverwendbare Steuerungsanwendungen. Die einfache Handhabung und die integrierte Überlauf‑/Unterlauferkennung machen ihn zu einem zuverlässigen Grundbaustein in vielen industriellen Zählaufgaben.
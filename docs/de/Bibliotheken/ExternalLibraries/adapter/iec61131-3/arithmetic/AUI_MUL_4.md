# AUI_MUL_4


![AUI_MUL_4](./AUI_MUL_4.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_MUL_4` ist ein generischer Baustein zur Durchführung einer arithmetischen Multiplikation von vier Eingangswerten. Er nutzt unidirektionale Adapter vom Typ `AUI` (Adapter Unit Interface), um Daten und zugehörige Ereignisse gebündelt zu übertragen. Dies ermöglicht eine saubere und übersichtliche Modellierung in der 4diac-ide.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird über die Adapter-Schnittstellen abgewickelt.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung wird über die Adapter-Schnittstellen abgewickelt.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingänge)**

- **IN1** (Typ: `adapter::types::unidirectional::AUI`): Erster Multiplikand.
- **IN2** (Typ: `adapter::types::unidirectional::AUI`): Zweiter Multiplikand.
- **IN3** (Typ: `adapter::types::unidirectional::AUI`): Dritter Multiplikand.
- **IN4** (Typ: `adapter::types::unidirectional::AUI`): Vierter Multiplikand.

#### **Plugs (Ausgänge)**

- **OUT** (Typ: `adapter::types::unidirectional::AUI`): Ausgang für das Ergebnis der Multiplikation ($OUT = IN1 \cdot IN2 \cdot IN3 \cdot IN4$).

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Ereignis signalisiert wird, liest der Funktionsbaustein die aktuellen Werte der vier Eingänge aus. Diese Werte werden miteinander multipliziert:

$$\text{Ergebnis} = \text{Wert von IN1} \cdot \text{Wert von IN2} \cdot \text{Wert von IN3} \cdot \text{Wert von IN4}$$

Das berechnete Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben, und ein entsprechendes Aktualisierungsereignis wird über diesen Plug ausgegeben.

## Technische Besonderheiten

- **Generischer Baustein:** Der Baustein basiert auf der generischen Klasse `GEN_AUI_MUL`. Dies ermöglicht eine flexible Anpassung an unterschiedliche Datentypen innerhalb des verwendeten Adaptertyps.
- **Verwendung von Adaptern:** Durch die Kapselung von Daten und Ereignissen in unidirektionalen Adaptern (`AUI`) wird die Anzahl der Verbindungslinien im Application-Editor von 4diac-ide drastisch reduziert, was die Übersichtlichkeit komplexer Anwendungen deutlich erhöht.

## Zustandsübersicht

Der Baustein arbeitet rein ereignisgesteuert und besitzt keinen internen Zustand, der über die Dauer eines Berechnungszyklus hinaus bestehen bleibt (zustandsloser / statischer Baustein).
- **Wartezustand:** Der Baustein wartet auf ein Aktualisierungsereignis an einem der Sockets (`IN1` bis `IN4`).
- **Berechnung:** Nach Eintreffen eines Ereignisses wird die Multiplikation durchgeführt.
- **Ausgabe:** Das Ergebnis wird an `OUT` angelegt, ein Ereignis am Plug ausgelöst und der Baustein kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

- **Signal-Skalierung:** Kaskadierte Skalierung von Messwerten, bei denen ein Rohwert mit mehreren Korrektur- und Kalibrierungsfaktoren multipliziert werden muss.
- **Leistungsberechnung:** Multiplikation von verschiedenen physikalischen Größen zur Ermittlung einer Zielgröße (z. B. Berechnung einer Gesamtleistung aus verschiedenen Faktoren).
- **Modulare Steuerungskonzepte:** Anwendungen, bei denen strukturierte Datenübergaben mittels standardisierter Adapter-Schnittstellen realisiert werden.

## Vergleich mit ähnlichen Bausteinen

- **Standard-MUL-Bausteine (IEC 61131-3):** Klassische Multiplizierer arbeiten mit direkten elementaren Datentypen (wie `REAL` oder `INT`) und benötigen separate Event-Eingänge (`REQ`) und Event-Ausgänge (`CNF`). `AUI_MUL_4` vereinfacht dies durch die Kapselung in Adaptern.
- **AUI_MUL_2 / AUI_MUL_3:** Ähnliche Bausteine mit weniger Eingängen. `AUI_MUL_4` eignet sich speziell dann, wenn exakt vier Faktoren multipliziert werden müssen, ohne mehrere Multiplikationsbausteine hintereinander schalten zu müssen (was Ressourcen und Latenz im Ausführungsmodell spart).

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der Funktionsbaustein `AUI_MUL_4` stellt eine effiziente und saubere Lösung für arithmetische Multiplikationen von vier Faktoren innerhalb einer adapterbasierten 4diac-Architektur dar. Er fördert das modulare Design und die Übersichtlichkeit der IEC 61499 Applikation.

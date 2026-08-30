# AI_ADD_2


![AI_ADD_2](./AI_ADD_2.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein (FB) **AI_ADD_2** ist ein generischer Baustein zur Durchführung einer arithmetischen Addition zweier analoger Eingangswerte. Er basiert auf dem Konzept generischer Funktionsbausteine (`GEN_AI_ADD`) und nutzt Adapter-Schnittstellen anstelle von klassischen, lose gekoppelten Daten- und Ereignis-Anschlüssen. Dies ermöglicht eine strukturierte, übersichtliche und modulare Signalverarbeitung innerhalb von 4diac-ide-basierten Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt gekapselt über die verwendeten Adapter.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung erfolgt gekapselt über die verwendeten Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

- **IN1** (Typ: `adapter::types::unidirectional::AI`): Der erste Summand der Additionsoperation. Über diesen Adapter werden sowohl der Wert als auch das dazugehörige Aktualisierungsereignis empfangen.
- **IN2** (Typ: `adapter::types::unidirectional::AI`): Der zweite Summand der Additionsoperation.

#### **Plugs (Ausgangs-Schnittstellen)**

- **OUT** (Typ: `adapter::types::unidirectional::AI`): Das Ergebnis der Addition ($OUT = IN1 + IN2$). Über diesen Adapter werden das Ergebnis und das entsprechende Aktualisierungsereignis an nachfolgende Bausteine weitergegeben.

## Funktionsweise

Der Baustein **AI_ADD_2** fungiert als mathematischer Addierer. Sobald an einem der Eingangs-Adapter (`IN1` oder `IN2`) ein neues Ereignis signalisiert, dass sich die Eingangsdaten aktualisiert haben, führt der Baustein die Addition aus:

$$\text{OUT} = \text{IN1} + \text{IN2}$$

Das berechnete Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben, und das zugehörige Aktualisierungsereignis wird ausgelöst, um nachfolgende Programmteile über den neuen Wert zu informieren.

Da es sich um einen generischen Funktionsbaustein (`GEN_AI_ADD`) handelt, ist der zugrundeliegende Datentyp (z. B. `REAL`, `INT`, `LREAL`) flexibel und wird durch die Belegung der verbundenen Adapter bestimmt.

## Technische Besonderheiten

- **Generischer Typ (`GEN_AI_ADD`):** Der Baustein ist nicht auf einen festen Datentyp festgelegt, was seine Wiederverwendbarkeit für unterschiedliche analoge Signalbereiche erhöht.
- **Unidirektionale Adapter:** Durch die Verwendung des Typs `adapter::types::unidirectional::AI` wird der Verdrahtungsaufwand in der 4diac-ide drastisch reduziert, da Werte und Events in einer einzigen Verbindung gebündelt sind.
- **Saubere Kapselung:** Keine losen Event- und Datenleitungen auf der Oberfläche des Funktionsbausteins.

## Zustandsübersicht

Der Funktionsbaustein verhält sich ereignisgesteuert und zustandslos. Es wird kein interner Zustand (wie bei einem Speicherglied) gehalten. Jedes eintreffende Ereignis an den Eingängen triggert sofort die Neuberechnung und die Ausgabe am Ausgang `OUT`.

## Anwendungsszenarien

- **Sensordaten-Aggregation:** Addition zweier Durchflussmengen (z. B. Hauptstrom und Nebenstrom) zu einem Gesamtdurchfluss.
- **Sollwert-Offsetting:** Aufaddieren eines festen oder dynamischen Offsets (z. B. Kalibrierungswert) auf ein analoges Eingangssignal.
- **Signalmischung:** Einfache mathematische Zusammenführung zweier analoger Steuersignale in der Prozessautomatisierung.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-3-Additionsbaustein (`ADD`), welcher mit klassischen Daten-Pins (z. B. `IN1`, `IN2` vom Typ `ANY_NUM`) und expliziten Kontroll-Events (`REQ` / `CNF`) arbeitet, bietet **AI_ADD_2** eine deutlich aufgeräumtere visuelle Darstellung. Durch die Kapselung in Adaptern entfällt das manuelle Ziehen separater Event-Linien, was das Fehlerrisiko bei der Applikationserstellung minimiert.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der **AI_ADD_2** ist ein moderner, hocheffizienter Funktionsbaustein für die 4diac-ide. Er kombiniert die mathematische Grundfunktion der Addition mit den strukturellen Vorteilen von IEC 61499-Adaptern. Dies macht ihn zur idealen Wahl für modular aufgebaute Regelungs- und Steuerungsarchitekturen.

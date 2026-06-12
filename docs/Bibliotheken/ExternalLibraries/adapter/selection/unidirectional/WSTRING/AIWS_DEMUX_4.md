# AIWS_DEMUX_4


![AIWS_DEMUX_4](./AIWS_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AIWS_DEMUX_4** ist ein generischer Demultiplexer für AIWS-Daten. Er verteilt einen eingehenden AIWS-Datenstrom (über den Sockel `IN`) auf einen von vier AIWS-Ausgängen (`OUT1`–`OUT4`), der durch den Index `K` ausgewählt wird. Der Baustein dient der gezielten Weiterleitung von Daten in strukturierten Steuerungssystemen und wird typischerweise in der landwirtschaftlichen Automatisierungstechnik eingesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Mit Var | Kommentar |
|----------|----------|---------|-----------|
| `REQ` | Event | `K` | Setzt den Index `K` und löst die Demultiplexierung aus. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Mit Var | Kommentar |
|----------|----------|---------|-----------|
| `CNF` | Event | – | Bestätigt die erfolgreiche Übernahme des Index und die Aktualisierung der Auswahl. |

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `K` | UINT | Index des gewünschten Ausgangs (Wertebereich typischerweise 1…4). |

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenen Datenausgänge. Die eigentlichen Nutzdaten werden über die Adapter-Schnittstellen transportiert.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| **Plug** (Ausgang) | `OUT1` | `adapter::types::unidirectional::AIWS` | Erster Ausgangsadapter für AIWS-Daten. |
| **Plug** (Ausgang) | `OUT2` | `adapter::types::unidirectional::AIWS` | Zweiter Ausgangsadapter für AIWS-Daten. |
| **Plug** (Ausgang) | `OUT3` | `adapter::types::unidirectional::AIWS` | Dritter Ausgangsadapter für AIWS-Daten. |
| **Plug** (Ausgang) | `OUT4` | `adapter::types::unidirectional::AIWS` | Vierter Ausgangsadapter für AIWS-Daten. |
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AIWS` | Eingangsadapter für den zu demultiplexenden AIWS-Datenstrom. |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis an `REQ`.
2. Mit `REQ` wird der aktuelle Wert des Eingangs `K` übernommen.
3. Der über den Adapter `IN` anliegende AIWS-Datenstrom wird auf den durch `K` bestimmten Ausgangsadapter (`OUT1`–`OUT4`) durchgeschaltet.
4. Nach erfolgreicher Umschaltung wird am Ausgang `CNF` ein Bestätigungsereignis ausgegeben.
5. Die nicht ausgewählten Ausgänge bleiben inaktiv oder liefern keine gültigen Daten (abhängig von der Implementierung des zugrunde liegenden Adaptertyps).

Die Adapter sind vom Typ `unidirectional::AIWS`, was auf eine unidirektionale Datenübertragung ohne Rückmeldung hinweist.

## Technische Besonderheiten

- **Generischer Baustein**: Die Klasse ist generisch (`GEN_AIWS_DEMUX`), sodass sie für beliebige Kanalanzahlen erweitert werden kann. Die vorliegende Ausführung unterstützt genau vier Ausgänge.
- **Adapterbasierte Schnittstelle**: Die Nutzdaten werden nicht über klassische Ein-/Ausgangsvariablen, sondern über plattformunabhängige Adapter ausgetauscht. Dies erhöht die Modularität und Wiederverwendbarkeit.
- **Indexüberprüfung**: Obwohl der Index `K` vom Typ `UINT` ist, wird empfohlen, nur Werte von 1 bis 4 zu verwenden. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten (z.B. kein Ausgang wird aktiv).
- **Keine Daten mit CNF**: Das Bestätigungsereignis `CNF` ist nicht mit weiteren Daten verknüpft – es signalisiert lediglich die erfolgte Aktualisierung der Auswahl.

## Zustandsübersicht

Der Baustein besitzt nur eine sehr einfache Zustandslogik:

- **Idle**: Warten auf `REQ`.
- **Processing**: Bei Eintreffen von `REQ` wird der Index `K` gelesen und die Auswahl aktualisiert. Nach Abschluss wird `CNF` gesendet und der Baustein kehrt in den Idle-Zustand zurück.

Es gibt keine internen Fehlerzustände oder Timeout-Mechanismen.

## Anwendungsszenarien

- **Datenverteilung in Steuerungssystemen**: Ein Sensor liefert AIWS-Daten an einen Bus, der Demultiplexer leitet die Daten je nach Bedarf an verschiedene Aktoren oder nachgelagerte Verarbeitungseinheiten weiter.
- **Landwirtschaftliche Automatisierung**: In Feldrobotern oder bei der Bewässerungssteuerung können mehrere gleichartige Geräte (z.B. Ventile, Düsen) aus einer gemeinsamen Datenquelle versorgt werden.
- **Test- und Simulationsumgebungen**: Einsatz als flexibler Multiplexer-Umschalter, um verschiedene Datenquellen auf einen gemeinsamen Analysepfad zu schalten (hier umgekehrt).

## Vergleich mit ähnlichen Bausteinen

- **AIWS_DEMUX_4 vs. generischer Demux mit Datenports**: Bausteine mit klassischen `ANY`-Datenports sind oft weniger typsicher, während adapterbasierte Lösungen eine klar definierte Schnittstelle (AIWS) bieten.
- **AIWS_DEMUX_4 vs. Multiplexer (AIWS_MUX)**: Der Demultiplexer verteilt einen Eingang auf mehrere Ausgänge, der Multiplexer wählt einen von mehreren Eingängen aus. Beide arbeiten komplementär.
- **AIWS_DEMUX_4 vs. manuelle Indexsteuerung**: Ohne diesen Baustein müsste die Datenweitergabe programmatisch in Funktionsbausteinen oder Skripten umgesetzt werden – der Demux kapselt diese Logik wiederverwendbar.

## Fazit

Der **AIWS_DEMUX_4** ist ein kompakter, adapterbasierter Demultiplexer für AIWS-Datenströme in IEC 61499‑Systemen. Er ermöglicht eine saubere Trennung von Datenweiterleitung und Steuerungslogik und eignet sich besonders für modulare Automatisierungsanwendungen. Die generische Auslegung erlaubt eine einfache Skalierung auf andere Kanalzahlen.
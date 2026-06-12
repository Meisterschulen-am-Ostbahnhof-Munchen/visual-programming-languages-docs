# SPLIT_AW_INTO_AB


![SPLIT_AW_INTO_AB](./SPLIT_AW_INTO_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **SPLIT_AW_INTO_AB** dient zur Aufteilung eines Wort-Datenpakets (Typ AW, 16 Bit) in zwei einzelne Byte-Datenpakete (Typ AB, je 8 Bit). Die Eingangsdaten werden über einen Socket empfangen und über zwei separate Plugs ausgegeben. Der Baustein wird typischerweise in Umgebungen eingesetzt, die auf Adapter-basierte Kommunikation setzen, z. B. in der Automatisierungstechnik beim Zerlegen von Wort-basierten Protokollen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine eigenen Ereignis-Eingänge. Die Ereignissteuerung erfolgt indirekt über den Adapter **IN**.

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenen Ereignis-Ausgänge. Ereignisse werden über die Ausgangs-Adapter **BYTE_00** und **BYTE_01** nach außen getragen.

### **Daten-Eingänge**

Der FB besitzt keine eigenen Daten-Eingänge. Die Dateneingabe erfolgt indirekt über den Adapter **IN**.

### **Daten-Ausgänge**

Der FB besitzt keine eigenen Daten-Ausgänge. Die Datenausgabe erfolgt indirekt über die Adapter **BYTE_00** und **BYTE_01**.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **IN** | Socket | `adapter::types::unidirectional::AW` | Empfängt ein 16‑Bit Wort (WORD). Der Adapter stellt die Daten und ein zugehöriges Ereignis zur Verfügung. |
| **BYTE_00** | Plug | `adapter::types::unidirectional::AB` | Gibt das niederwertige Byte (Byte 0) aus. |
| **BYTE_01** | Plug | `adapter::types::unidirectional::AB` | Gibt das höherwertige Byte (Byte 1) aus. |

## Funktionsweise

1. Ein eingehendes Ereignis auf dem Adapter **IN** (E1) triggert den internen Funktionsblock **SPLIT_WORD_INTO_BYTES**.
2. Dieser teilt das empfangene WORD (16 Bit) in zwei Bytes auf: **BYTE_00** (niederwertig) und **BYTE_01** (höherwertig).
3. Das Abschlussereignis (CNF) von **SPLIT_WORD_INTO_BYTES** wird an die Takt-Eingänge zweier **E_D_FF_ANY** Flip-Flops weitergeleitet.
4. Jeder Flip-Flop speichert das zugehörige Byte und gibt es bei einem neuen Taktimpuls über seinen Ausgang **Q** aus.
5. Die Flip-Flops erzeugen jeweils ein Ereignis auf **EO**, das an die Ausgangs-Adapter **BYTE_00** und **BYTE_01** gesendet wird. So werden die aufgeteilten Bytes zusammen mit einem Ereignis nach außen bereitgestellt.

## Technische Besonderheiten

- **Adapter‑basierte Schnittstelle:** Der FB enthält keine direkten Event- oder Dateneingänge/-ausgänge. Die gesamte Kommunikation erfolgt über Adapter (Socket für Eingang, Plugs für Ausgänge). Er eignet sich daher besonders für Anwendungen, die auf das adapterbasierte 4diac‑Typensystem setzen.
- **Datenzwischenspeicherung:** Die beiden **E_D_FF_ANY** Flip-Flops halten die aufgeteilten Bytes stabil, bis neue Daten anliegen. Dadurch werden inkonsistente Zustände während der Aufteilung vermieden.
- **Ereignissynchronisation:** Die Ausgabe der Bytes erfolgt zeitgleich, da das gleiche CNF-Ereignis beide Flip-Flops taktet.

## Zustandsübersicht

Der FB besitzt keine explizite Zustandsmaschine. Er verarbeitet Impulse ereignisgesteuert und gibt bei jedem Ereignis auf **IN** die aufgeteilten Bytes aus. Die Flip-Flops haben die typischen zwei Zustände: gespeicherter Wert (0 oder 1 pro Bit, abhängig vom Byte).

## Anwendungsszenarien

- **Byte‑orientierte Kommunikation:** Wenn ein Sensor oder Aktor Daten im WORD‑Format sendet, aber nachgelagerte Bausteine einzelne Bytes erwarten.
- **Protokoll‑Aufbereitung:** Zerlegen von Telegrammen, die aus einem 16‑Bit Wert bestehen, in getrennte Byte‑Adapter für weitere Verarbeitungsschritte.
- **Modbus/IO‑Link Integration:** Anpassung von 16‑Bit Registerwerten an 8‑Bit Schnittstellen.

## Vergleich mit ähnlichen Bausteinen

- **SPLIT_WORD_INTO_BYTES:** Ein reiner Daten‑Splitter ohne Adapter‑Kapselung. Er arbeitet auf Datenebene und benötigt eigene Event‑ und Datenschnittstellen.
- **MUX/ DEMUX Bausteine:** Multiplexer oder Demultiplexer für mehrere Werte, jedoch meist mit anderen Datentypen und ohne Adapter‑Integration.
- **Adapter‑Wrapper wie SPLIT_AW_INTO_AB:** Speziell für die adapterbasierte 4diac‑Architektur entwickelt. Sie kapseln die Aufteilungslogik hinter einheitlichen Adapter‑Schnittstellen.

## Fazit

**SPLIT_AW_INTO_AB** ist ein spezialisierter Adapter‑Wrapper, der ein einkommendes WORD sauber in zwei getrennte BYTE‑Adapter aufteilt. Die Verwendung von Flip‑Flops gewährleistet einen stabilen Datenfluss und vermeidet zeitliche Inkonsistenzen. Der Baustein ist ideal für Systeme, die eine adapterbasierte Kommunikation nach IEC 61499-2 verwenden und eine einfache Transformation zwischen 16‑Bit und 8‑Bit Daten benötigen.
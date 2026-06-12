# AW_SPLIT_2

!Bild des FB (nicht verfügbar)


![AW_SPLIT_2](./AW_SPLIT_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AW_SPLIT_2** teilt einen eingehenden unidirektionalen **Adapter (AW)** in zwei identische ausgehende Adapter auf. Er ist als generischer Baustein implementiert und eignet sich für Anwendungen, bei denen ein Signalpfad oder eine Adapterverbindung auf zwei nachfolgende Komponenten aufgespalten werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Kein Ereignis‑Eingang vorhanden.

### **Ereignis-Ausgänge**

Kein Ereignis‑Ausgang vorhanden.

### **Daten-Eingänge**

Kein Daten‑Eingang vorhanden.

### **Daten-Ausgänge**

Kein Daten‑Ausgang vorhanden.

### **Adapter**

| Bezeichnung | Richtung | Typ | Beschreibung |
|-------------|----------|-----|--------------|
| `IN` | Socket | `adapter::types::unidirectional::AW` | Eingangs‑Adapter – der zu teilende unidirektionale AW. |
| `OUT1` | Plug | `adapter::types::unidirectional::AW` | Erster Ausgang – erhält eine identische Kopie des eingehenden Adapters. |
| `OUT2` | Plug | `adapter::types::unidirectional::AW` | Zweiter Ausgang – erhält ebenfalls eine identische Kopie des eingehenden Adapters. |

## Funktionsweise

Der Baustein leitet den an **IN** anliegenden unidirektionalen Adapter (AW) unverändert an beide Ausgänge **OUT1** und **OUT2** weiter. Es findet keine Datenmanipulation, keine Ereignissteuerung und keine Zustandslogik statt – der Baustein fungiert ausschließlich als passive Verteilereinheit auf Adapterebene.

Da der Adaptertyp als generisch deklariert ist (`GEN_AW_SPLIT`), kann der FB mit verschiedenen konkreten Ausprägungen des AW‑Adapters verwendet werden, solange sie dem gleichen `unidirectional::AW` Protokoll folgen.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generische Komponente (GenericClassName `GEN_AW_SPLIT`) definiert. Er kann in Projekten mit unterschiedlichen AW‑Adapter‑Typen eingesetzt werden, ohne dass der Baustein selbst angepasst werden muss.
- **Keine Laufzeitlogik**: Die Aufteilung erfolgt rein strukturell – der FB besitzt weder einen Zustandsautomaten (ECC) noch verarbeitet er Ereignisse oder Daten. Dadurch entsteht kein zusätzlicher Rechenaufwand zur Laufzeit.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0 (EPL‑2.0)**.

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustandsautomaten. Die Weiterleitung ist statisch und erfolgt ohne zeitliche oder ereignisabhängige Steuerung.

## Anwendungsszenarien

- **Verteilen eines Mess‑ oder Status‑Adapterpfades** an zwei unabhängige Verarbeitungseinheiten (z. B. an eine Hauptsteuerung und eine Überwachungskomponente).
- **Aufbau redundanter Verarbeitungsketten**, bei denen derselbe Adapterstrom parallel in zwei separate Logikzweige eingespeist wird.
- **Test‑ und Diagnosearchitekturen**, die einen Datenstrom sowohl in die produktive Logik als auch in einen Analyse‑Pfad aufteilen.

## Vergleich mit ähnlichen Bausteinen

- **AW_MERGE_2** – führt zwei AW‑Eingänge zu einem Ausgang zusammen (Gegenstück zum Split).
- **Daten‑Split‑Bausteine** (z. B. `SPLIT_INT`, `SPLIT_BOOL`) arbeiten auf Datensignalen, nicht auf Adaptern. `AW_SPLIT_2` ist speziell für die Aufteilung von Adapter‑Schnittstellen ausgelegt.

## Fazit

`AW_SPLIT_2` ist ein einfacher, aber wesentlicher generischer Baustein zur Adapter‑Verteilung. Er ermöglicht eine saubere, wiederverwendbare Aufspaltung eines unidirektionalen AW‑Pfades, ohne zusätzliche Logik oder Laufzeitkosten. Besonders in modularen, adapterbasierten Steuerungssystemen erleichtert er die Signalverteilung und fördert die Wiederverwendbarkeit von Komponenten.
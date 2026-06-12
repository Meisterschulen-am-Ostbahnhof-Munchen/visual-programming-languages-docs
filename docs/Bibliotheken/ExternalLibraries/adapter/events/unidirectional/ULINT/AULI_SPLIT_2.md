# AULI_SPLIT_2


![AULI_SPLIT_2](./AULI_SPLIT_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_SPLIT_2** dient dazu, einen eingehenden AULI-Adapter (unidirektional) auf zwei identische Ausgänge zu verteilen. Er ist als generischer Baustein realisiert und ermöglicht die einfache Signalvervielfachung in IEC 61499‑basierten Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket (Eingang)** | IN | AULI (unidirektional) | Eingehender AULI‑Datenstrom |
| **Plug (Ausgang)** | OUT1 | AULI (unidirektional) | Erster Ausgang, identische Kopie von IN |
| **Plug (Ausgang)** | OUT2 | AULI (unidirektional) | Zweiter Ausgang, identische Kopie von IN |

## Funktionsweise

Der Baustein leitet die über den **IN**‑Socket empfangenen AULI‑Daten unverändert an beide Ausgänge **OUT1** und **OUT2** weiter. Es findet keine Datenmanipulation, Pufferung oder Protokollumsetzung statt. Die Verteilung erfolgt passiv und ohne Verzögerung.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist über das Attribut `eclipse4diac::core::GenericClassName` als `'GEN_AULI_SPLIT'` deklariert, was eine flexible Wiederverwendung in verschiedenen Engineering‑Umgebungen ermöglicht.
- **Keine Zustandshaltung**: Der FB besitzt keinen internen Zustandsautomaten (ECC) und kein Speicherverhalten. Er ist vollständig passiv.
- **Reine Adapter‑Schnittstelle**: Es werden ausschließlich Adapter (`Plugs` und `Sockets`) verwendet; Daten‑ oder Ereigniseingänge sind nicht vorhanden.

## Zustandsübersicht

Da der Funktionsblock keine interne Logik oder Zustandsmaschine enthält, existiert keine Zustandsbeschreibung. Das Verhalten beschränkt sich auf die konstante Weiterleitung des eingehenden Signals.

## Anwendungsszenarien

- **Signalverteilung**: Aufteilung eines AULI‑Datenstroms an zwei nachfolgende Funktionsblöcke, z. B. zur parallelen Verarbeitung oder Steuerung.
- **Redundante Übertragung**: Bereitstellung eines zweiten, identischen Datenpfads für Überwachungs‑ oder Sicherheitszwecke.
- **Punkt‑zu‑Mehrpunkt‑Kommunikation**: Ermöglichung einer einfachen 1‑zu‑2‑Verdrahtung in Adapter‑basierten Architekturen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion |
|----------|----------|
| **AULI_SPLIT_2** | Split auf zwei Ausgänge (identisch zu IN) |
| **AULI_SPLIT_N** | Generalisierte Variante mit konfigurierbarer Anzahl an Ausgängen |
| **AULI_MERGE** | Zusammenführung mehrerer Eingänge auf einen Ausgang |

Während **AULI_SPLIT_2** eine feste 1‑zu‑2‑Aufteilung vornimmt, erlauben generische Splitter eine flexible Anzahl von Ausgängen. Zusammenführer wie **AULI_MERGE** lösen die umgekehrte Aufgabe.

## Fazit

Der **AULI_SPLIT_2** ist ein minimaler und effizienter Baustein zur Signalvervielfachung unidirektionaler AULI‑Adapter. Aufgrund seiner passiven, zustandslosen Natur eignet er sich ideal für Echtzeitanwendungen, in denen Kopien eines Datenstroms ohne zusätzliche Latenz oder Logik benötigt werden. Seine generische Implementierung erleichtert den Einsatz in unterschiedlichen Entwicklungswerkzeugen und Bibliotheken.
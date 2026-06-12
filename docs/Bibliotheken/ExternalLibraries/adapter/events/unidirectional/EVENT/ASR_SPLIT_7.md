# ASR_SPLIT_7


![ASR_SPLIT_7](./ASR_SPLIT_7.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_SPLIT_7** ist ein generischer Baustein, der einen einzelnen ASR-Adaptereingang auf sieben ASR-Adapterausgänge verteilt. Er dient als 1:7-Splitter für ASR-Daten und ermöglicht die parallele Weitergabe eines Signals an mehrere nachfolgende Komponenten.

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

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang (Socket) | **IN** | `adapter::types::unidirectional::ASR` | Quelladapter, dessen Daten auf alle Ausgänge verteilt werden. |
| Ausgang (Plug) | **OUT1** | `adapter::types::unidirectional::ASR` | Erster Ausgang, erhält die duplizierten Daten von `IN`. |
| Ausgang (Plug) | **OUT2** | `adapter::types::unidirectional::ASR` | Zweiter Ausgang. |
| Ausgang (Plug) | **OUT3** | `adapter::types::unidirectional::ASR` | Dritter Ausgang. |
| Ausgang (Plug) | **OUT4** | `adapter::types::unidirectional::ASR` | Vierter Ausgang. |
| Ausgang (Plug) | **OUT5** | `adapter::types::unidirectional::ASR` | Fünfter Ausgang. |
| Ausgang (Plug) | **OUT6** | `adapter::types::unidirectional::ASR` | Sechster Ausgang. |
| Ausgang (Plug) | **OUT7** | `adapter::types::unidirectional::ASR` | Siebter Ausgang. |

## Funktionsweise

Der Baustein empfängt über den Socket `IN` ein ASR‑Signal. Dieses Signal wird intern auf alle sieben Plugs (`OUT1` … `OUT7`) dupliziert und ohne Veränderung weitergeleitet. Es findet keine Datenmanipulation oder Filterung statt – das eingehende Signal wird eins zu eins an jeden Ausgang kopiert.

## Technische Besonderheiten

- **Generischer Typ**: Der Funktionsblock ist als generischer Baustein mit dem Klassennamen `GEN_ASR_SPLIT` deklariert. Dadurch kann er in verschiedenen Kontexten eingesetzt werden, in denen ein ASR-Splitter benötigt wird.
- **Reine Adapter‑Schnittstelle**: Es werden ausschließlich Adapter (keine Ereignisse oder Daten‑Ein‑/Ausgänge) verwendet. Die Kommunikation erfolgt über das unidirektionale ASR‑Adapterprotokoll.
- **Kein interner Zustand**: Der Baustein besitzt keine Zustandsautomatik; die Signalverteilung erfolgt kontinuierlich und verzögerungsfrei.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände. Die Funktionalität beschränkt sich auf die statische Duplizierung des Eingangssignals.

## Anwendungsszenarien

- **Signalverteilung**: Ein ASR‑Signal (z. B. ein Steuerbefehl oder eine Konfigurationsnachricht) soll an mehrere unabhängige Empfänger gesendet werden.
- **Parallelverarbeitung**: In einer automatisierten Steuerung muss eine Information gleichzeitig mehrere Subsysteme erreichen, die jeweils auf das ASR‑Protokoll ausgelegt sind.
- **Testumgebungen**: Ein Testadapter wird an `IN` angeschlossen und die Ausgänge mit verschiedenen Überwachungs- oder Logging‑Bausteinen verbunden.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Splitter‑Bausteine wie `ASR_SPLIT_2`, `ASR_SPLIT_4` oder `ASR_SPLIT_n`, die das Eingangssignal auf 2, 4 bzw. `n` Ausgänge verteilen. `ASR_SPLIT_7` stellt eine spezifische Variante mit sieben Ausgängen dar. Allen gemeinsam ist die unveränderte Duplizierung des eingehenden ASR‑Signals.

## Fazit

Der `ASR_SPLIT_7` ist ein einfacher, aber nützlicher Baustein zur Verteilung eines ASR-Signals auf sieben parallele Pfade. Seine generische Definition und der Verzicht auf Ereignisse oder Zustände machen ihn flexibel einsetzbar und robust im Betrieb.
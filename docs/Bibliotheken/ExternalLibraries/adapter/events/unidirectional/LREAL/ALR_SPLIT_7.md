# ALR_SPLIT_7


![ALR_SPLIT_7](./ALR_SPLIT_7.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ALR_SPLIT_7` dient dazu, ein eingehendes ALR-Signal (Agricultural Logic Resource) auf sieben identische Ausgangssignale aufzuteilen. Er ist als generischer Baustein konzipiert und ermöglicht die parallele Verteilung eines Alarm- oder Steuersignals an bis zu sieben nachfolgende Komponenten oder Subsysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| IN | `adapter::types::unidirectional::ALR` | Socket (Eingang) | Eingehendes ALR-Signal, das auf die Ausgänge verteilt wird. |
| OUT1 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Erster Ausgang des geteilten Signals. |
| OUT2 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Zweiter Ausgang des geteilten Signals. |
| OUT3 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Dritter Ausgang des geteilten Signals. |
| OUT4 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Vierter Ausgang des geteilten Signals. |
| OUT5 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Fünfter Ausgang des geteilten Signals. |
| OUT6 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Sechster Ausgang des geteilten Signals. |
| OUT7 | `adapter::types::unidirectional::ALR` | Plug (Ausgang) | Siebter Ausgang des geteilten Signals. |

## Funktionsweise

Der `ALR_SPLIT_7` – Baustein leitet das an seinem Socket `IN` anliegende ALR-Signal unverändert an alle sieben Plugs (`OUT1` bis `OUT7`) weiter. Es findet keine Transformation, Verzögerung oder Filterung des Signals statt. Der Baustein fungiert als reiner Verteiler (Splitter) für einen unidirektionalen ALR-Datenstrom.

## Technische Besonderheiten

- **Generic FB:** Der Baustein ist als generischer Funktionsblock (`GenericClassName = 'GEN_ALR_SPLIT'`) realisiert und kann je nach Anwendung parametriert oder instanziiert werden.
- **Unidirektional:** Alle Adapter sind vom Typ `adapter::types::unidirectional::ALR`, d. h. die Daten fließen nur in eine Richtung – vom Eingang zu den Ausgängen.
- **Keine Ereignissteuerung:** Der Baustein besitzt keine Ereignis-Ein- oder -Ausgänge; die Signalweitergabe erfolgt kontinuierlich (datengesteuert).

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustandsautomaten. Es gibt keine Zustände im Sinne von ECC (Execution Control Chart). Er arbeitet rein kombinatorisch und gibt das Eingangssignal stets auf allen Ausgängen aus.

## Anwendungsszenarien

- **Verteilen eines Alarms auf mehrere Einheiten:** Ein zentrales Alarmsignal (z. B. eine Störung) soll an sieben verschiedene Steuerungen oder Anzeigeelemente weitergegeben werden.
- **Parallele Verarbeitung:** Ein ALR-Signal wird benötigt, um mehrere unabhängige Subsysteme gleichzeitig zu triggern oder zu überwachen.
- **Redundanz und Test:** Das Signal wird an mehrere Prüf- oder Logging-Komponenten gesendet, ohne dass diese sich gegenseitig beeinflussen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Besonderheit |
|----------|------------------|--------------|
| `ALR_SPLIT_2` | 2 | Einfache Zweifachverteilung |
| `ALR_SPLIT_4` | 4 | Vierfachverteilung |
| `ALR_SPLIT_7` | 7 | Siebenfachverteilung (dieser Baustein) |
| `ALR_SPLIT_N` (generisch) | Parametrierbar | Flexibler Splitter mit einstellbarer Anzahl |

Alle Variationen basieren auf dem gleichen Prinzip: unidirektionale Verteilung ohne Signalveränderung.

## Fazit

Der `ALR_SPLIT_7` ist ein einfacher, aber nützlicher Funktionsblock zur Aufteilung eines einzelnen ALR-Signals auf sieben parallele Pfade. Durch seine generische Implementierung kann er in verschiedenen industriellen oder landwirtschaftlichen Automatisierungsszenarien eingesetzt werden, wo ein Signal mehrfach benötigt wird. Er bietet keine komplexe Logik, erfüllt aber zuverlässig seine Aufgabe als passiver Verteiler.
# ALR_SPLIT_5


![ALR_SPLIT_5](./ALR_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALR_SPLIT_5** dient dazu, ein eingehendes ALR-Signal auf fünf identische Ausgänge zu verteilen. Er ist als generischer Baustein (Generic FB) implementiert und ermöglicht eine einfache Signalvervielfachung in Steuerungssystemen, die auf dem Adapterkonzept von IEC 61499 basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Es sind keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Es sind keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Es sind keine Daten-Eingänge vorhanden. Die gesamte Datenübertragung erfolgt ausschließlich über Adapter.

### **Daten-Ausgänge**

Es sind keine Daten-Ausgänge vorhanden.

### **Adapter**

Der Baustein besitzt einen Socket (Eingang) und fünf Plugs (Ausgänge):

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang | IN | `adapter::types::unidirectional::ALR` | Empfängt das zu verteilende ALR-Signal |
| Ausgang | OUT1 | `adapter::types::unidirectional::ALR` | Erster Ausgang mit dem identischen ALR-Signal |
| Ausgang | OUT2 | `adapter::types::unidirectional::ALR` | Zweiter Ausgang mit dem identischen ALR-Signal |
| Ausgang | OUT3 | `adapter::types::unidirectional::ALR` | Dritter Ausgang mit dem identischen ALR-Signal |
| Ausgang | OUT4 | `adapter::types::unidirectional::ALR` | Vierter Ausgang mit dem identischen ALR-Signal |
| Ausgang | OUT5 | `adapter::types::unidirectional::ALR` | Fünfter Ausgang mit dem identischen ALR-Signal |

## Funktionsweise

Der Funktionsblock leitet das vom Socket `IN` eingehende ALR-Signal unverändert an alle fünf Plugs `OUT1` bis `OUT5` weiter. Es handelt sich um eine rein kombinatorische Weiterleitung – es findet keine Logik, Verzögerung oder Datenmanipulation statt. Der Baustein arbeitet ereignis- und zustandslos; sobald ein Signal am Eingang anliegt, steht es an allen Ausgängen bereit.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als Generic FB definiert und verwendet die Eclipse 4diac Generics-Mechanismen (`eclipse4diac::core::GenericClassName`). Dadurch kann er in verschiedenen Kontexten ohne Anpassung der Kernlogik eingesetzt werden.
- **Reine Adapterkommunikation:** Es werden keine klassischen Ereignis- oder Datenein-/ausgänge genutzt. Die gesamte Kommunikation erfolgt über Adapter vom Typ `ALR`, die einen unidirektionalen Datenaustausch ermöglichen.
- **Einfache Struktur:** Keine Zustandsautomaten oder zeitlichen Abhängigkeiten – der FB ist deterministisch und ressourcenschonend.

## Zustandsübersicht

Der Funktionsblock besitzt keine explizite Zustandslogik oder Zustandsmaschine. Er arbeitet vollständig kombinatorisch, d.h. das Ausgangssignal ergibt sich direkt und ohne Verzögerung aus dem Eingangssignal.

## Anwendungsszenarien

- **Signalverteilung in der Automatisierung:** Ein Sensor liefert ein ALR-Signal, das parallel an mehrere Aktoren (z.B. Ventile, Antriebe) weitergeleitet werden muss.
- **Redundanz:** Das Signal kann an verschiedene Steuerungseinheiten oder Überwachungsmodule verteilt werden.
- **Test- und Simulationsumgebungen:** Ein zentrales ALR-Signal wird auf mehrere Testpunkte aufgeteilt, um parallele Auswertungen zu ermöglichen.

## Vergleich mit ähnlichen Bausteinen

- **ALR_SPLIT_2, ALR_SPLIT_3, ALR_SPLIT_4:** Diese Bausteine teilen ein ALR-Signal auf zwei, drei bzw. vier Ausgänge auf. Der vorliegende FB erweitert dies auf fünf Ausgänge.
- **Allgemeine Split-FBs (z.B. DATA_SPLIT):** Ähnliche Bausteine existieren für andere Datentypen. Die Funktionsweise ist identisch, lediglich der verwendete Adaptertyp unterscheidet sich. Der Vorteil des ALR_SPLIT_5 liegt in der direkten Nutzung des ALR-Adapterprotokolls ohne zusätzliche Typkonvertierung.

## Fazit

Der **ALR_SPLIT_5** ist ein einfacher, aber wertvoller Baustein zur Vervielfachung von ALR-Signalen in IEC-61499-Systemen. Seine generische und kombinatorische Implementierung macht ihn leicht integrierbar und ressourceneffizient. Er eignet sich besonders für Anwendungen, in denen ein Signal an mehrere Empfänger verteilt werden muss, ohne zusätzliche Logik oder zeitliche Steuerung zu benötigen.
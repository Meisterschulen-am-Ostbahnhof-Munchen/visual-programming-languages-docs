# A2X_SPLIT_3


![A2X_SPLIT_3](./A2X_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **A2X_SPLIT_3** dient zur Aufteilung eines eingehenden A2X-Adapterdatenstroms auf drei identische Ausgänge. Er ist als generischer Baustein (generic FB) implementiert und eignet sich für Anwendungen, bei denen ein Signal mehrfach benötigt wird.

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

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::A2X` | **IN** | Socket (Eingang) | Quell-Adapter, dessen Datenstrom aufgeteilt wird. |
| `adapter::types::unidirectional::A2X` | **OUT1** | Plug (Ausgang) | Erster identischer Ausgang. |
| `adapter::types::unidirectional::A2X` | **OUT2** | Plug (Ausgang) | Zweiter identischer Ausgang. |
| `adapter::types::unidirectional::A2X` | **OUT3** | Plug (Ausgang) | Dritter identischer Ausgang. |

Die Adapter sind alle vom Typ **A2X** (unidirectional) und übertragen Daten in einer Richtung. Der Baustein ist passiv, d.h. er benötigt keine Ereignissteuerung für die Datenweitergabe.

## Funktionsweise

Der Baustein nimmt den über den Socket **IN** ankommenden A2X-Datenstrom entgegen und leitet ihn unverändert an die drei Plugs **OUT1**, **OUT2** und **OUT3** weiter. Es findet keine Verarbeitung, Filterung oder Pufferung statt – der Datenstrom wird 1:1 auf alle Ausgänge verteilt.

Da es sich um einen generischen Baustein handelt, kann der konkrete Datentyp des A2X-Adapters zur Laufzeit durch eine Typisierung (z.B. über das Attribut `GenericClassName`) festgelegt werden.

## Technische Besonderheiten

- **Generische Auslegung**: Der Baustein ist als generischer FB deklariert (`GenericClassName = 'GEN_A2X_SPLIT'`), sodass der A2X-Adapter je nach Anwendung mit unterschiedlichen konkreten Datenstrukturen parametriert werden kann.
- **Keine Zustandsautomatik**: Der Baustein besitzt keine ECC (Execution Control Chart) und keine Ereignis-Schnittstellen. Er arbeitet rein datenflussorientiert.
- **Laufzeit-Typanpassung**: Über das Attribut `TypeHash` kann eine eindeutige Typkennzeichnung für die generische Instanz hinterlegt werden (hier leer, muss projektspezifisch gesetzt werden).

## Zustandsübersicht

Der Baustein besitzt keine internen Zustände, da er keine sequentielle Logik oder Zustandsmaschine enthält. Die Datenweitergabe erfolgt kontinuierlich ohne Verzögerung.

## Anwendungsszenarien

- **Signalverteilung**: Ein von einem Sensor oder einer Steuerung kommendes A2X-Signal muss parallel an mehrere nachgelagerte Bausteine (z.B. Anzeigen, Logger, Aktoren) weitergeleitet werden.
- **Redundanz / Monitoring**: Ein Datenstrom soll sowohl an die eigentliche Verarbeitung als auch an ein Diagnose- oder Überwachungssystem gesendet werden.
- **Prototypische Aufbauten**: In der Entwicklungsphase kann ein einzelner generischer Splitter flexibel für verschiedene Adaptertypen verwendet werden.

## Vergleich mit ähnlichen Bausteinen

- **A2X_SPLIT_2**: Teilt einen A2X-Stream auf zwei Ausgänge auf. Der vorliegende Baustein erweitert dies auf drei Ausgänge.
- **Manuelles Duplizieren**: Ohne Splitter müsste der Architekt den Quell-Adapter mehrfach in der Konfiguration referenzieren, was die Lesbarkeit und Wartbarkeit verringert.
- **Generische Splitter**: Andere Splitting-Bausteine (z.B. für Daten- oder Ereignisadapter) folgen dem gleichen Prinzip, sind aber auf andere Adaptertypen spezialisiert.

## Fazit

Der **A2X_SPLIT_3** ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Vervielfältigung eines A2X-Datenstroms auf drei Pfade. Durch seinen generischen Charakter passt er sich flexibel an unterschiedliche Datenstrukturen an und erleichtert die modulare Verschaltung in IEC 61499-basierten Automatisierungssystemen.
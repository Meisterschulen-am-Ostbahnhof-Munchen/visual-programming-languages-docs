# ASR_SPLIT_3


![ASR_SPLIT_3](./ASR_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ASR_SPLIT_3` dient dazu, einen eingehenden ASR (Application-Specific Resource) Adapter auf drei identische ausgehende ASR-Adapter zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine einfache Signalfächerung innerhalb einer Adapter-basierten Kommunikationsstruktur.

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

| Typ         | Richtung | Name | Beschreibung                         |
|-------------|----------|------|--------------------------------------|
| Socket      | Eingang  | IN   | Eingehender ASR-Signaladapter.       |
| Plug        | Ausgang  | OUT1 | Erster ausgehender ASR-Signaladapter.|
| Plug        | Ausgang  | OUT2 | Zweiter ausgehender ASR-Signaladapter.|
| Plug        | Ausgang  | OUT3 | Dritter ausgehender ASR-Signaladapter.|

Alle Adapter sind vom Typ `adapter::types::unidirectional::ASR`.

## Funktionsweise

Der Baustein leitet alle über den Socket `IN` eintreffenden Signale und Ereignisse des ASR-Adapters unverändert an die drei Plug-Kanäle `OUT1`, `OUT2` und `OUT3` weiter. Es findet keine logische Verarbeitung oder Pufferung statt – die Verteilung erfolgt passiv und ohne Verzögerung. Der Baustein fungiert als einfacher Splitter für ASR-Verbindungen.

## Technische Besonderheiten

- Der Baustein ist generisch (Attribut `eclipse4diac::core::GenericClassName` = `'GEN_ASR_SPLIT'`), wodurch er für verschiedene Instanzen des ASR-Typs wiederverwendet werden kann.
- Es wird kein ECC (Execution Control Chart) benötigt, da die Weiterleitung direkt durch die Adapter-Kopplung erfolgt.
- Alle drei Ausgänge sind separat adressierbar, sodass unterschiedliche Zielbausteine unabhängig angeschlossen werden können.

## Zustandsübersicht

Da der Baustein keine Ereignisse verarbeitet und zustandslos arbeitet, existiert kein Zustandsdiagramm. Die Funktionalität beschränkt sich auf die passive Durchleitung.

## Anwendungsszenarien

- **Verteilen von Steuersignalen** an mehrere parallele Komponenten in einer Automatisierungsanlage, z. B. an drei Antriebe oder Sensoren.
- **Aufteilung einer ASR-Kommunikation** auf unterschiedliche Subsysteme, die die gleiche Adapterschnittstelle erwarten.
- **Test- und Debugging-Setups**, bei denen ein Signal gleichzeitig an mehrere Überwachungsstellen weitergeleitet werden soll.

## Vergleich mit ähnlichen Bausteinen

- `ASR_SPLIT_2` teilt ein ASR-Signal auf zwei Ausgänge auf; `ASR_SPLIT_3` erweitert diese Funktionalität auf drei Ausgänge.
- `ASR_MERGE` (sofern vorhanden) fasst mehrere ASR-Signale zusammen, während `ASR_SPLIT_3` sie auseinanderfädelt.
- Im Gegensatz zu generischen Daten-Splittern arbeitet der Baustein direkt auf Adapterebene und erfordert keine zusätzlichen Datentypumsetzungen.

## Fazit

Der `ASR_SPLIT_3` ist ein einfacher, aber effektiver Baustein zur Vervielfältigung eines ASR-Signals auf drei identische Ausgänge. Er eignet sich besonders für modulare Strukturen, in denen ein zentrales Signal mehrfach gebraucht wird. Die generische Auslegung erhöht die Wiederverwendbarkeit und reduziert den Konfigurationsaufwand.
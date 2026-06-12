# ADI_SPLIT_9


![ADI_SPLIT_9](./ADI_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ADI_SPLIT_9` ist ein generischer Baustein, der ein eingehendes ADI-Signal (Adapter) auf neun identische Ausgangssignale aufteilt. Er dient als reiner Splitter auf Adapterebene.

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
- **IN** (Socket): Adapter vom Typ `adapter::types::unidirectional::ADI` – Eingangssignal.
- **OUT1** bis **OUT9** (Plugs): Neun Adapter desselben Typs – Ausgänge, die das Eingangssignal unverändert weitergeben.

## Funktionsweise

Der FB leitet das am Socket `IN` anliegende ADI-Signal an alle neun Plugs `OUT1` bis `OUT9` weiter. Es findet keine Signalverarbeitung oder Umwandlung statt; die Verteilung erfolgt rein strukturell über die Adapterverbindungen. Aufgrund des unidirektionalen Adaptertyps ist die Datenflussrichtung vom Socket zu den Plugs festgelegt.

## Technische Besonderheiten

- Der Baustein ist als generischer Funktionsblock definiert (Attribut `eclipse4diac::core::GenericClassName` = `'GEN_ADI_SPLIT'`) und kann dadurch in unterschiedlichen Projekten wiederverwendet werden.
- Er besitzt weder Ereignisse noch Daten-Ein-/Ausgänge; die gesamte Funktionalität liegt in der Adaptertopologie.
- Das Typ-Hash-Attribut ist leer, was auf eine einfache, nicht versionierte Ausführung hinweist.

## Zustandsübersicht

Der Funktionsblock besitzt keine Zustandsautomaten oder Algorithmen. Er ist rein passiv und reagiert nicht auf Ereignisse.

## Anwendungsszenarien

- Verteilen eines analogen oder digitalen Sensorsignals (als ADI) an mehrere nachgeschaltete Bausteine.
- Aufteilen eines Steuersignals in einer Automatisierungsanlage, um identische Aktoren parallel anzusteuern.
- Erzeugen von Signalkopien für Überwachungs-, Test- oder Diagnosezwecke.

## Vergleich mit ähnlichen Bausteinen

- Im Gegensatz zu daten- oder ereignisbasierten Splittern arbeitet `ADI_SPLIT_9` auf der höheren Adapterebene, was eine saubere architekturelle Trennung ermöglicht.
- Ähnliche Bausteine existieren mit variabler Ausgangsanzahl (z. B. `ADI_SPLIT_M`), während dieser FB eine feste Anzahl von neun Ausgängen bietet.

## Fazit

`ADI_SPLIT_9` ist ein einfacher, generischer Funktionsblock zur 1-zu-9-Verteilung eines unidirektionalen ADI-Signals. Er eignet sich für Anwendungen, die ein mehrfaches, identisches Weiterleiten von Adaptersignalen ohne zusätzliche Logik erfordern.
# ALR_SPLIT_3


![ALR_SPLIT_3](./ALR_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALR_SPLIT_3** dient als generischer SPLIT-Baustein, der ein eingehendes ALR-Signal (Alarm- oder Ereignissignal) auf drei identische Ausgänge aufteilt. Er wird vor allem in Automatisierungssystemen eingesetzt, wo ein einzelnes Signal parallel an mehrere nachfolgende Komponenten verteilt werden muss, ohne die Signalqualität oder -logik zu verändern.

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
* **IN** – *Socket* (Eingang) vom Typ `adapter::types::unidirectional::ALR`  
  Nimmt das zu verteilende ALR-Signal entgegen.
* **OUT1** – *Plug* (Ausgang 1) vom Typ `adapter::types::unidirectional::ALR`  
  Gibt das eingehende Signal unverändert weiter.
* **OUT2** – *Plug* (Ausgang 2) vom Typ `adapter::types::unidirectional::ALR`  
  Gibt das eingehende Signal unverändert weiter.
* **OUT3** – *Plug* (Ausgang 3) vom Typ `adapter::types::unidirectional::ALR`  
  Gibt das eingehende Signal unverändert weiter.

## Funktionsweise
Der Baustein arbeitet als reiner Signalverteiler. Sobald am Adapter-Socket **IN** ein ALR-Signal anliegt (z. B. ein Alarmzustand, ein Ereignis oder eine Aktivierung), wird dieses Signal ohne Verzögerung oder Manipulation an alle drei Adapter-Plugs **OUT1**, **OUT2** und **OUT3** weitergeleitet. Es findet keine logische Verarbeitung oder Filterung statt. Die Verteilung erfolgt passiv über die Verbindungslogik der 4diac-IDE.

## Technische Besonderheiten
* **Generischer Funktionsblock** – Über die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` kann der Baustein als generische Instanz angelegt werden. Dies erlaubt eine einfache Wiederverwendung und Parametrisierung in verschiedenen Projekten.
* **Keine eigene Zustandsmaschine** – Der Baustein besitzt kein ECC (Execution Control Chart), da das Verhalten rein durch die Adapter-Konnektivität definiert wird.
* **Unidirektionale Adapter** – Alle verwendeten ALR-Adapter sind vom Typ `unidirectional`; die Signalrichtung ist festgelegt (Eingang → Ausgänge).

## Zustandsübersicht
Der Baustein definiert keine internen Zustände. Das Ausgangssignal entspricht stets momentan dem Eingangssignal. Eine separate Zustandsbeschreibung ist daher nicht erforderlich.

## Anwendungsszenarien
* **Alarmverteilung** – Ein zentraler Alarmmelder (z. B. übergeordnetes Leitsystem) wird auf drei unabhängige Steuerungseinheiten aufgeschaltet, die parallel auf den Alarm reagieren sollen.
* **Signal-Multiplex** – Ein boolesches oder wertbasiertes Signal aus einem Sensor wird an mehrere Aktoren oder Visualisierungen verteilt.
* **Redundanzarchitekturen** – Das gleiche Signal wird an zwei oder drei unabhängige Pfade geschickt, um eine Ausfallsicherheit zu erreichen.

## Vergleich mit ähnlichen Bausteinen
* **ALR_SPLIT_2** – Verteilt ein Signal auf zwei Ausgänge (identische Funktion, aber weniger Ausgänge).
* **ALR_SPLIT_4** – Verteilt ein Signal auf vier Ausgänge.
* **Manuelle Kopplung** – Ohne SPLIT-Baustein müsste das Signal mehrfach in der Applikation abgegriffen oder über eine Sammelleitung verteilt werden, was die Übersichtlichkeit und Wartbarkeit verschlechtert.

## Fazit
Der **ALR_SPLIT_3** ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfachung eines ALR-Signals. Er erleichtert die strukturierte und wiederverwendbare Verschaltung in Automatisierungslösungen, bei denen ein Signal an mehrere Empfänger weitergegeben werden muss, ohne zusätzliche Logik oder Latenz.
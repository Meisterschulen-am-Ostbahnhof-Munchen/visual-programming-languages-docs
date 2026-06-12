# ALI_SPLIT_5


![ALI_SPLIT_5](./ALI_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ALI_SPLIT_5` ist ein generischer Adapter‑Split‑Baustein. Er nimmt einen einzigen eingehenden ALI‑Adapter (`adapter::types::unidirectional::ALI`) entgegen und stellt die gleichen ALI‑Signale an fünf ausgehenden ALI‑Adapter‑Schnittstellen bereit. Dadurch kann eine ALI‑Verbindung auf mehrere nachfolgende Bausteine oder Geräte verteilt werden, ohne die logische Signalkette zu unterbrechen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang (Socket) | `IN` | `adapter::types::unidirectional::ALI` | Einziger Eingang: enthält die ALI‑Daten, die auf die fünf Ausgänge verteilt werden sollen. |
| Ausgang (Plug) | `OUT1` | `adapter::types::unidirectional::ALI` | Erster Ausgang (identische Signale wie am Eingang). |
| Ausgang (Plug) | `OUT2` | `adapter::types::unidirectional::ALI` | Zweiter Ausgang. |
| Ausgang (Plug) | `OUT3` | `adapter::types::unidirectional::ALI` | Dritter Ausgang. |
| Ausgang (Plug) | `OUT4` | `adapter::types::unidirectional::ALI` | Vierter Ausgang. |
| Ausgang (Plug) | `OUT5` | `adapter::types::unidirectional::ALI` | Fünfter Ausgang. |

## Funktionsweise

Sobald der Baustein mit einer gültigen ALI‑Verbindung am Socket `IN` verbunden ist, wird der gesamte Daten‑ und Ereignisverkehr des eingehenden Adapters **unverändert** und **parallel** auf die fünf Plug‑Adapter `OUT1` bis `OUT5` weitergeleitet. Es findet keine logische Verarbeitung, Filterung oder Verzögerung statt – der Baustein wirkt als passive Verteilereinheit („Splitter“) für den ALI‑Kanal.

Die Weiterleitung erfolgt bidirektional entsprechend der ALI‑Adapterdefinition: Sowohl Ereignisse als auch Daten (wie sie im ALI‑Typ vorgesehen sind) werden an allen Ausgängen synchron zur Verfügung gestellt. Der Baustein besitzt keine eigene Laufzeitlogik und keinen inneren Zustand.

## Technische Besonderheiten

- **Generischer Baustein** – Die konkrete Implementierung wird durch die Meta‑Attribute `GenericClassName` und `TypeHash` gesteuert. Dadurch kann dieselbe FB‑Definition für verschiedene ALI‑Varianten (z. B. mit unterschiedlichen Datenstrukturen) wiederverwendet werden.
- **Keine Verzögerung** – Die Signale werden ohne nennenswerte Laufzeitverzögerung auf die Ausgänge repliziert.
- **Einfach erweiterbar** – Das Prinzip dieses Splitters kann auf andere Adapter‑Typen übertragen werden; durch die generische Architektur ist keine Änderung der Basislogik erforderlich.
- **Direkte Kopplung** – Der Ausgangszustand entspricht stets dem aktuellen Eingangszustand; es gibt keine Pufferung oder Zwischenspeicherung.

## Zustandsübersicht

Der Baustein besitzt **keinen internen Zustandsautomaten**. Er arbeitet direkt und ohne Verzögerung als reine Verbindungsweiche („Wired‑Split“). Zustandsänderungen treten nur durch die angeschlossenen Adapter‑Partner auf, diese werden transparent weitergeleitet.

## Anwendungsszenarien

- **Verteilen eines Sensorsignals** an mehrere Auswerteeinheiten oder Steuerungen, die den gleichen ALI‑Datenstrom benötigen.
- **Parallelisierung von ALI‑Kommunikationspfaden** in einer Maschinensteuerung, um redundante oder unabhängige Verarbeitungsketten zu versorgen.
- **Test- und Debugging‑Umgebungen**, bei denen ein ALI‑Signal gleichzeitig beobachtet und aufgezeichnet werden soll.

## Vergleich mit ähnlichen Bausteinen

Andere Split‑ oder Fanout‑Bausteine bieten meist eine feste Anzahl von Ausgängen oder sind auf bestimmte Datentypen festgelegt. Der `ALI_SPLIT_5` ist speziell auf den unidirektionalen ALI‑Adapter zugeschnitten, jedoch durch seine generische Vorlage flexibel einsetzbar. Im Gegensatz zu einem **Multiplexer** oder **Router** leitet dieser Baustein das Signal **ohne Umschaltung** stets an alle Ausgänge weiter.

## Fazit

Der `ALI_SPLIT_5` ist ein einfacher, aber essenzieller Baustein zur Vervielfachung eines ALI‑Signals. Aufgrund seiner generischen Natur lässt er sich problemlos in verschiedene 4diac‑Projekte integrieren und vereinfacht die Signalverteilung in komplexen Automatisierungsarchitekturen. Er ist wartungsarm, da er keine eigene Logik enthält, und trägt zur Modularisierung und Wiederverwendbarkeit von ALI‑Verbindungen bei.
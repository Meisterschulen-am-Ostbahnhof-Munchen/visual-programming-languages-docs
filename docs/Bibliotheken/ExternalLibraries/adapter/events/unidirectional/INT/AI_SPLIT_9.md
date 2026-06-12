# AI_SPLIT_9


![AI_SPLIT_9](./AI_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AI_SPLIT_9** ist ein generischer Baustein, der ein einzelnes analoges Eingangssignal (Adaptertyp `AI`) auf neun identische Ausgänge (OUT1 bis OUT9) verteilt. Er dient als Signalverteiler, der es ermöglicht, ein AI-Signal mehrfach in einer Steuerungsanwendung zu nutzen, ohne die Quelle mehrfach zu verknüpfen.

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
| Eingang (Socket) | `IN` | `adapter::types::unidirectional::AI` | Einzelner analoger Eingang, der auf alle Ausgänge verteilt wird. |
| Ausgang (Plug) | `OUT1` | `adapter::types::unidirectional::AI` | Erster ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT2` | `adapter::types::unidirectional::AI` | Zweiter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT3` | `adapter::types::unidirectional::AI` | Dritter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT4` | `adapter::types::unidirectional::AI` | Vierter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT5` | `adapter::types::unidirectional::AI` | Fünfter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT6` | `adapter::types::unidirectional::AI` | Sechster ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT7` | `adapter::types::unidirectional::AI` | Siebter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT8` | `adapter::types::unidirectional::AI` | Achter ausgehender AI‑Kanal. |
| Ausgang (Plug) | `OUT9` | `adapter::types::unidirectional::AI` | Neunter ausgehender AI‑Kanal. |

## Funktionsweise
Der Baustein arbeitet als reine Signalverteilung: Der am Adapter‑Socket `IN` anliegende AI‑Wert wird unverändert und gleichzeitig an alle neun Adapter‑Plugs `OUT1` … `OUT9` weitergegeben. Es findet keine Signalverarbeitung, Skalierung oder sonstige Manipulation statt. Die Verteilung erfolgt kontinuierlich und ohne internes Zustandsverhalten – der Ausgang folgt dem Eingang ohne Verzögerung.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als `GEN_AI_SPLIT` typisiert und nutzt die Generics‑Mechanismen von Eclipse 4diac (`GenericClassName`, `TypeHash`). Dadurch kann er in Typ‑Hierarchien und Bibliotheken flexibel eingesetzt werden.
- **Adapterbasierte Schnittstelle:** Statt einzelner Daten‑Ports werden Adapter verwendet, die eine gekapselte, wiederverwendbare Schnittstelle für analoge Eingänge (`AI`) bereitstellen. Dies vereinfacht das Verschaltungskonzept in 4diac‑Applikationen.
- **Keine Latenz:** Da keine interne Logik oder Abläufe vorhanden sind, ist die Weiterleitung des Signals verzögerungsfrei.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustandsautomaten (kein ECC). Er verhält sich rein datenflussgesteuert: Der Wert des Eingangs wird permanent auf die Ausgänge durchgeschaltet.

## Anwendungsszenarien
- **Signalvervielfachung:** Ein einzelner analoger Sensor (z. B. Temperatur, Druck) soll in mehreren Funktionsblöcken parallel ausgewertet werden.
- **Redundante Verarbeitung:** Ein AI‑Signal wird an mehrere unabhängige Pfade weitergeleitet, um Ausfallsicherheit oder Plausibilitätsprüfungen zu ermöglichen.
- **Modulare Aufteilung:** In einer großen Steuerungsapplikation wird ein analoges Eingangssignal in verschiedene Module (z. B. Regelung, Überwachung, Visualisierung) geführt.

## Vergleich mit ähnlichen Bausteinen
- **AI_SPLIT_2 / AI_SPLIT_4 / …**: Analoge Bausteine mit 2 bzw. 4 Ausgängen. `AI_SPLIT_9` erweitert das Konzept auf neun Ausgänge und ist daher für Anwendungen mit vielen Empfängern geeignet.
- **AI_MERGE**: Führt mehrere AI‑Eingänge zu einem Ausgang zusammen – die gegenteilige Operation.
- **Direkte Adapter‑Verknüpfung**: In 4diac kann ein einzelner Adapter‑Port konzeptionell auch mehrfach verbunden werden, jedoch ist die explizite Splittung mit diesem FB dokumentierter und klarer strukturiert.

## Fazit
Der **AI_SPLIT_9** ist ein einfacher, aber nützlicher Funktionsblock zur Signalvervielfachung von analogen Eingängen in IEC 61499‑Applikationen. Durch seinen generischen Aufbau und die Adapter‑Schnittstelle fügt er sich nahtlos in das 4diac‑Ökosystem ein und erleichtert die strukturierte Verschaltung von Signalen. Seine Verwendung empfiehlt sich überall dort, wo ein AI‑Signal gleichzeitig an mehrere Verarbeitungseinheiten übergeben werden muss.
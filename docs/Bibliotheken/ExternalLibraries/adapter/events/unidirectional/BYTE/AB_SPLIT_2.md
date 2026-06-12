# AB_SPLIT_2


![AB_SPLIT_2](./AB_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_SPLIT_2** dient der Aufteilung eines unidirektionalen Adapters vom Typ `AB` auf zwei separate Adapterausgänge. Er ist als generischer Baustein (Generic FB) implementiert und ermöglicht die gleichzeitige Weiterleitung des eingehenden Adapters an zwei unabhängige Zieladressaten. Dies vereinfacht die Topologie in Steuerungsapplikationen, wenn ein Signal mehrfach benötigt wird, ohne den ursprünglichen Datenfluss zu beeinträchtigen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden. Die Adapterkommunikation erfolgt ereignislos über den Datenaustauschmechanismus des Adaptertyps.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden. Der Datenfluss erfolgt ausschließlich über den Adapter-Eingang `IN`.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Ausgaben erfolgen über die Adapter-Ausgänge `OUT1` und `OUT2`.

### **Adapter**

| Rolle  | Name | Typ                                | Richtung |
|--------|------|-----------------------------------|----------|
| Socket | IN   | `adapter::types::unidirectional::AB` | Eingang  |
| Plug   | OUT1 | `adapter::types::unidirectional::AB` | Ausgang  |
| Plug   | OUT2 | `adapter::types::unidirectional::AB` | Ausgang  |

## Funktionsweise
Der Baustein leitet den über den Socket `IN` verbundenen Adapter unverändert an beide Plugs `OUT1` und `OUT2` weiter. Jede Veränderung der Daten bzw. des Zustands des eingehenden Adapters wird simultan an beide Ausgänge propagiert. Die Aufteilung erfolgt ohne Verzögerung oder Pufferung – es handelt sich um eine reine Verteilungslogik.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB ist als generischer Typ deklariert (`GEN_AB_SPLIT`), sodass er mit verschiedenen Untertypen des Adapters `AB` arbeiten kann, sofern diese die gleiche unidirektionale Semantik besitzen.
- **Unidirektionalität:** Der Adapter ist ausschließlich in eine Richtung ausgelegt – Daten fließen vom Socket zu den Plugs. Rückwärtige Kommunikation wird nicht unterstützt.
- **Lizenz:** Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0), was die freie Nutzung, Modifikation und Weitergabe in eigenen Projekten erlaubt.
- **Keine Zustandsautomaten:** Der FB besitzt keine inneren Zustände oder ereignisgesteuerten Abläufe, da die Adapterweiterleitung vollständig datengetrieben erfolgt.

## Zustandsübersicht
Der FB besitzt keinen Zustandsautomaten. Die Ausgangsadapter spiegeln stets den aktuellen Zustand des Eingangsadapters wider.

## Anwendungsszenarien
- **Signalverteilung in modularen Anlagen:** Trennung eines Sensorsignals von einer Feldbuskomponente zur parallelen Verarbeitung in zwei unabhängigen Steuerungslogiken.
- **Redundanzaufbau:** Ein eingehendes Signal kann über zwei separate Pfade an verschiedene Regler oder Überwachungseinheiten gesendet werden.
- **Prototypen und Testaufbauten:** Einfaches Duplizieren eines Adapterstroms für Simulations- und Debugzwecke, ohne die eigentliche Applikation zu verändern.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu dedizierten **SPLIT-FBs** mit Ereignis-/Datenports arbeitet `AB_SPLIT_2` rein adapterbasiert. Während klassische Split-Bausteine oft getriggerte Datenkopien erfordern, erfolgt die Verteilung hier kontinuierlich und ohne explizite Aktivierung. Ähnliche Funktionalität bieten Adapter-Multiplexer oder Buskoppler, jedoch mit komplexerer Konfiguration. Der vorliegende Baustein ist speziell auf den unidirektionalen `AB`-Adapter zugeschnitten.

## Fazit
`AB_SPLIT_2` ist ein einfacher, aber effektiver generischer Funktionsblock zur Aufteilung eines unidirektionalen Adapters auf zwei Ausgänge. Er erweitert die Flexibilität in der Adapterverkabelung industrieller Steuerungssysteme gemäß IEC 61499 und ist dank der EPL-2.0-Lizenz frei einsetzbar. Für Anwendungen, die eine 1:2-Verteilung von Adapterdaten benötigen, bietet er eine saubere und wartbare Lösung.
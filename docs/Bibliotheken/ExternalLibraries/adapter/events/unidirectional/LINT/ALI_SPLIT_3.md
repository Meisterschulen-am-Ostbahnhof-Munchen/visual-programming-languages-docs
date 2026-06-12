# ALI_SPLIT_3


![ALI_SPLIT_3](./ALI_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_SPLIT_3** dient dazu, einen eingehenden unidirektionalen Adapter vom Typ **ALI** (Application Layer Interface) auf drei identische Ausgangsadapter desselben Typs zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine Signalvervielfachung ohne Datenveränderung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
– Keine –

### **Ereignis-Ausgänge**
– Keine –

### **Daten-Eingänge**
– Keine (die gesamte Kommunikation erfolgt über die Adapter-Schnittstellen)

### **Daten-Ausgänge**
– Keine (die gesamte Kommunikation erfolgt über die Adapter-Schnittstellen)

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::ALI` | Empfängt das eingehende ALI-Signal. |
| Plug (Ausgang) | `OUT1` | `adapter::types::unidirectional::ALI` | Erste Ausgangskopie des Signals. |
| Plug (Ausgang) | `OUT2` | `adapter::types::unidirectional::ALI` | Zweite Ausgangskopie des Signals. |
| Plug (Ausgang) | `OUT3` | `adapter::types::unidirectional::ALI` | Dritte Ausgangskopie des Signals. |

**Hinweis:** Der Adaptertyp `ALI` ist ein unidirektionaler Interface-Adapter, der in der Regel Daten- und Ereignisfluss in einer Richtung kapselt. Die exakte interne Struktur ist anwendungsspezifisch definiert.

## Funktionsweise
Der FB führt eine reine 1:3-Verteilung des am Socket `IN` anliegenden ALI-Adapters durch. Alle am Eingang empfangenen Informationen (z. B. Datenwerte, Ereignisse oder Zustände) werden ohne Verzögerung oder Transformation parallel an die drei Ausgänge `OUT1`, `OUT2` und `OUT3` weitergeleitet. Es findet keine Pufferung oder Logik statt – der Baustein arbeitet rein datenflusssynchron.

## Technische Besonderheiten
- **Generischer Typ:** Der Baustein ist als generischer Funktionsblock deklariert (`eclipse4diac::core::GenericClassName = 'GEN_ALI_SPLIT'`). Dadurch kann der eigentliche Adaptertyp zur Konfigurationszeit festgelegt werden, sofern das zugrundeliegende System dies unterstützt.
- **Keine Eigendynamik:** Der FB besitzt keine eigenen Ereignis- oder Daten-Ein-/Ausgänge außerhalb der Adapter. Die gesamte Kommunikation läuft ausschließlich über die Adapter-Schnittstellen.
- **Geringe Latenz:** Durch den Verzicht auf interne Verarbeitung ist die Signalverteilung nahezu verzögerungsfrei.

## Zustandsübersicht
Der Baustein besitzt keine Zustandsautomaten oder Zustandsspeicher. Sein Verhalten ist deterministisch und rein kombinatorisch: Der aktuelle Eingangszustand wird unmittelbar auf alle Ausgänge abgebildet.

## Anwendungsszenarien
- **Signalvervielfachung in Steuerungssystemen:** Wenn ein ALI-Signal (z. B. ein Sensordatenstrom) mehrfach von verschiedenen nachgelagerten Bausteinen benötigt wird, kann ALI_SPLIT_3 die Verteilung übernehmen.
- **Test- und Simulationsumgebungen:** Mehrere Komponenten sollen mit demselben Eingangssignal versorgt werden, um parallele Reaktionen zu beobachten.
- **Redundanz:** Ein Signal wird auf drei Pfade aufgeteilt, die unabhängig voneinander weiterverarbeitet werden (z. B. für Vergleich oder Fehlererkennung).

## Vergleich mit ähnlichen Bausteinen
- **ALI_SPLIT_2:** Verteilt ein ALI-Signal auf zwei statt drei Ausgänge. ALI_SPLIT_3 erweitert diese Anzahl auf drei.
- **ALI_MERGE (hypothetisch):** Führt mehrere ALI-Eingänge zu einem Ausgang zusammen – funktional gegensätzlich.
- **Ereignis-basierte Splitter (z. B. E_SPLIT):** Arbeiten mit reinen Ereignissen, während ALI_SPLIT_3 Daten- und Ereignisanteile gemeinsam über einen Adapter verteilt.

## Fazit
ALI_SPLIT_3 ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfachung von ALI-Adapterverbindungen. Seine generische Natur und die reine Signalweitergabe machen ihn zu einem flexiblen Werkzeug in der Automatisierungs- und Steuerungstechnik, insbesondere wenn ein Signal mehrfach benötigt wird.
# A2X_SPLIT_6


![A2X_SPLIT_6](./A2X_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `A2X_SPLIT_6` dient dazu, einen eingehenden A2X-Adapter auf sechs identische A2X-Ausgänge zu verteilen. Er ist als generischer Baustein (Generic FB) realisiert und ermöglicht die Weiterleitung von Adapterdaten ohne Verzögerung oder Zustandsänderung. Typische Einsatzbereiche sind die parallele Versorgung mehrerer Verbraucher oder die Signalkaskadierung in industriellen Steuerungen.

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
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang (Socket) | `IN` | `adapter::types::unidirectional::A2X` | Empfängt das eingehende A2X-Adapter-Signal |
| Ausgang (Plug) 1 | `OUT1` | `adapter::types::unidirectional::A2X` | Erster ausgehender A2X-Adapter |
| Ausgang (Plug) 2 | `OUT2` | `adapter::types::unidirectional::A2X` | Zweiter ausgehender A2X-Adapter |
| Ausgang (Plug) 3 | `OUT3` | `adapter::types::unidirectional::A2X` | Dritter ausgehender A2X-Adapter |
| Ausgang (Plug) 4 | `OUT4` | `adapter::types::unidirectional::A2X` | Vierter ausgehender A2X-Adapter |
| Ausgang (Plug) 5 | `OUT5` | `adapter::types::unidirectional::A2X` | Fünfter ausgehender A2X-Adapter |
| Ausgang (Plug) 6 | `OUT6` | `adapter::types::unidirectional::A2X` | Sechster ausgehender A2X-Adapter |

## Funktionsweise
Der Baustein arbeitet als reiner Verteiler (Splitter). Sobald der Socket `IN` mit einem A2X-Adapter verbunden ist, wird das komplette Adaptersignal – bestehend aus allen in diesem Adapter enthaltenen Daten- und Ereigniskanälen – an alle sechs Plugs (`OUT1` … `OUT6`) weitergegeben. Die Weitergabe erfolgt ohne Pufferung oder eigene Logik; jede Änderung am Eingang spiegelt sich unverzögert auf allen Ausgängen wider.

## Technische Besonderheiten
- **Unidirektionalität** – Der Adapter `A2X` ist unidirektional ausgelegt; eine Datenflussumkehr ist nicht vorgesehen.
- **Generische Auslegung** – Der FB ist als generischer Typ (`GenericClassName = 'GEN_A2X_SPLIT'`) hinterlegt, sodass er in verschiedenen Kontexten eingesetzt werden kann.
- **Keine Zustände oder Ereignisse** – Es existieren keine internen Zustandsautomaten oder ereignisgesteuerten Abläufe; der FB ist rein kombinatorisch.
- **Vollständige Entkopplung** – Durch die Verwendung von Adaptern werden die angeschlossenen Bausteine entkoppelt, was die Wiederverwendbarkeit erhöht.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Er ist jederzeit passiv und aktiv nur durch die am Eingang anliegenden Adapterdaten. Daher existieren keine definierten Zustände wie INIT, RUN oder IDLE.

## Anwendungsszenarien
- **Signalverteilung in der Automatisierung** – Ein Sensor liefert über einen A2X-Adapter Messwerte, die parallel an mehrere Steuerungen oder Auswerteinheiten weitergeleitet werden müssen.
- **Kaskadierung von Adaptersignalen** – In komplexen Hierarchien kann ein A2X-Signal auf mehrere untergeordnete Module aufgeteilt werden.
- **Test- und Simulationsumgebungen** – Zum gleichzeitigen Anschluss mehrerer Prüfstände oder Visualisierungskomponenten an eine Datenquelle.

## Vergleich mit ähnlichen Bausteinen
- **A2X_SPLIT_2 / A2X_SPLIT_4 / A2X_SPLIT_N** – Diese Bausteine bieten die gleiche Funktionalität, jedoch mit zwei, vier oder einer konfigurierbaren Anzahl von Ausgängen. `A2X_SPLIT_6` stellt eine feste 6-fach-Verteilung bereit.
- **A2X_MERGE** – Im Gegensatz zum Splitter fasst dieser Baustein mehrere A2X-Eingänge zu einem Ausgang zusammen.
- **Standard-Daten-Splitter** (z. B. für einfache Datentypen) – Adapterbasierte Splitter wie dieser arbeiten auf einer höheren Abstraktionsebene und kapseln komplexe Signalbündel.

## Fazit
Der `A2X_SPLIT_6` ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfachung von A2X-Adapter-Signalen. Durch seinen generischen Aufbau und die reine Verteilerfunktion eignet er sich besonders für Szenarien, in denen ein Signal ohne Verarbeitungslogik an mehrere Empfänger gesendet werden muss. Die Abwesenheit von Ereignissen und Zuständen macht ihn leicht verständlich und ressourcenschonend einsetzbar.
# A2X_SPLIT_2


![A2X_SPLIT_2](./A2X_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `A2X_SPLIT_2` dient der Aufteilung eines eingehenden A2X-Adapter-Signals auf zwei identische Ausgangs-Adapter. Er ist als generischer Baustein (`GEN_A2X_SPLIT`) implementiert und ermöglicht die Weiterleitung eines A2X-Signals an zwei unabhängige Zielbausteine ohne Signalverlust oder -veränderung.

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
| `adapter::types::unidirectional::A2X` | `IN` | Socket | Eingangs-Adapter, der das zu verteilende A2X-Signal empfängt. |
| `adapter::types::unidirectional::A2X` | `OUT1` | Plug | Erster Ausgangs-Adapter, der eine identische Kopie des Eingangssignals bereitstellt. |
| `adapter::types::unidirectional::A2X` | `OUT2` | Plug | Zweiter Ausgangs-Adapter, der eine identische Kopie des Eingangssignals bereitstellt. |

## Funktionsweise

Der Baustein leitet das am Socket `IN` anliegende A2X-Adapter-Signal ohne jegliche Transformation oder Verzögerung direkt an die beiden Plugs `OUT1` und `OUT2` weiter. Jedes Ereignis, das über den A2X-Adapter übertragen wird, erscheint gleichzeitig und unverändert an beiden Ausgängen. Der Baustein besitzt keine interne Logik, keinen Zustand und keine Latenz.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ `GEN_A2X_SPLIT` deklariert und nutzt das Eclipse 4diac Generic-Class-Konzept. Dies ermöglicht eine flexible Wiederverwendung in verschiedenen Projekten.
- **Reine Adapterweiterleitung**: Es werden keine Ereignis- oder Daten-Ein-/Ausgänge verwendet; die gesamte Kommunikation erfolgt ausschließlich über die A2X-Adapter-Schnittstellen.
- **Unidirektional**: Der A2X-Adapter ist unidirektional, daher fließen Daten und Ereignisse nur vom Socket zu den Plugs (Eingang → Ausgang).

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten und ist vollständig **stateless**. Jeder Eingangswert wird sofort und ohne Speicherung an beide Ausgänge weitergegeben.

## Anwendungsszenarien

- **Signalvervielfachung**: Ein von einem Sensor oder einer Steuerung bereitgestelltes A2X-Signal soll an zwei verschiedene Verbraucher (z. B. Aktoren, Anzeigen, überlagerte Logiken) gleichzeitig verteilt werden.
- **Redundanz oder Überwachung**: Ein Signal soll parallel zu einem Hauptziel auch an einen Diagnose- oder Monitoring-Baustein geführt werden.
- **Test und Simulation**: Ein A2X-Signal soll während des Tests sowohl an die reale Hardware als auch an einen Simulator angeschlossen werden.

## Vergleich mit ähnlichen Bausteinen

- **A2X_SPLIT_3**: Analoger Baustein mit drei Ausgängen statt zwei. Beide Bausteine arbeiten identisch, unterscheiden sich nur in der Anzahl der Ausgangsplugs.
- **A2X_MERGE**: Führt zwei A2X-Signale zu einem zusammen – gegensätzliche Funktionalität.
- **Generische Splitter (z. B. für andere Adaptertypen)**: Funktionsprinzip gleich, aber Adaptertyp angepasst.

## Fazit

Der `A2X_SPLIT_2` ist ein einfacher, aber nützlicher Baustein zur Signalverteilung in 4diac-Anwendungen. Seine generische Natur ermöglicht eine flexible Nutzung ohne zusätzliche Konfiguration. Er eignet sich besonders für Szenarien, in denen ein A2X-Signal an mehrere Empfänger weitergegeben werden muss, ohne dass die Signalintegrität beeinträchtigt wird.
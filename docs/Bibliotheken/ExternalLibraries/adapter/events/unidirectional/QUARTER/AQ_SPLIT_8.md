# AQ_SPLIT_8


![AQ_SPLIT_8](./AQ_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AQ_SPLIT_8** ist ein Fan-Out-Baustein, der einen einzigen AQ-Adapter-Eingang auf acht identische AQ-Adapter-Ausgänge verteilt. Er dient der Signalvervielfachung in Analogausgangs-Pfaden und ermöglicht so die parallele Ansteuerung mehrerer gleichartiger Aktoren oder Subsysteme. Die Implementierung basiert auf dem generischen Mechanismus `GEN_AQ_SPLIT` und ist für unidirektionale AQ-Schnittstellen ausgelegt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – der Baustein arbeitet rein adapterbasiert ohne Ereignissteuerung.

### **Ereignis-Ausgänge**
Keine – der Baustein besitzt keine Ereignisausgänge.

### **Daten-Eingänge**
Keine – die gesamte Signalübertragung erfolgt über AQ-Adapter.

### **Daten-Ausgänge**
Keine – siehe Daten-Eingänge.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **IN** | `adapter::types::unidirectional::AQ` | Socket (Eingang) | Empfängt das zu verteilende AQ-Signal. |
| **OUT1** – **OUT8** | `adapter::types::unidirectional::AQ` | Plug (Ausgang) | Identische Ausgänge, die das Signal von `IN` weiterleiten. |

## Funktionsweise
Der Baustein leitet das am Socket `IN` anliegende AQ-Signal durch interne Verdrahtung an alle acht Plug-Ausgänge `OUT1` bis `OUT8` weiter. Dabei erfolgt keine Signalverarbeitung oder -änderung – es handelt sich um eine reine 1:8-Verteilung (Fan-Out). Die Adapter sind unidirektional, d. h. Daten und Ereignisse fließen nur vom Eingang zu den Ausgängen.

## Technische Besonderheiten
- **Keine getaktete Logik**: Der Baustein benötigt keine Ereignis-E/As, da die Weiterleitung direkt über die Adapter-Interface-Ebene erfolgt.
- **Generischer Typ**: Der Baustein ist als generische Instanz (`GEN_AQ_SPLIT`) deklariert – der konkrete Adaptertyp kann je nach Systemumgebung angepasst werden.
- **Erweiterbarkeit**: Die 8 Ausgänge sind fest verdrahtet; eine dynamische Anzahl oder Konfiguration ist nicht vorgesehen.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten (ECC). Die Funktionalität ist rein statisch: Sobald der `IN`-Adapter aktiv ist, geben alle Ausgänge das identische Signal aus. Es gibt keine Betriebsarten, Fehlerzustände oder Lifecycle-Events.

## Anwendungsszenarien
- **Parallelverkabelung**: Ein analoges Ausgangssignal gleichzeitig an mehrere Stellglieder oder Messstellen verteilen.
- **Test- und Simulationsumgebungen**: Ein Signalgenerator speist über `IN` und über `OUT1`–`OUT8` werden mehrere simulierte Komponenten versorgt.
- **Redundante Ansteuerung**: Falls mehrere Subsysteme denselben Sollwert erhalten sollen, ohne dass ein Bus oder eine Softwareverzweigung nötig ist.

## Vergleich mit ähnlichen Bausteinen
- **AQ_SPLIT_4**: Bietet nur 4 Ausgänge – geeignet bei geringerer Verteilungsanforderung.
- **AQ_SELECT**: Ein Multiplexer, der aus mehreren Eingängen einen auswählt – eher Gegenteil der Split-Funktion.
- **DQ_SPLIT_8**: Analoger Baustein für digitale Signale (DQ-Typ) – strukturell identisch, aber für andere Signalart.

## Fazit
Der **AQ_SPLIT_8** ist ein einfacher, zuverlässiger Fan-Out-Baustein für die 1:8-Verteilung von Analogausgangssignalen über Adapter-Schnittstellen. Er verzichtet auf Ereignislogik und Zustandsautomaten und eignet sich daher besonders für klar definierte, statische Signalverteilungen in Automatisierungssystemen. Die generische Basis erleichtert die Wiederverwendung in unterschiedlichen Projekten.
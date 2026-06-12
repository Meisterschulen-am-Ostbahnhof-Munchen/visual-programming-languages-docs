# ADI_SPLIT_2


![ADI_SPLIT_2](./ADI_SPLIT_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ADI_SPLIT_2` dient dazu, einen eingehenden ADI‑Adapter (Socket) auf zwei identische ADI‑Ausgangsadapter (Plugs) zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine einfache Signalbündelung in Adapter-basierten Architekturen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine – dieser Funktionsblock besitzt keine Ereignis-Eingänge.

### **Ereignis-Ausgänge**

Keine – dieser Funktionsblock besitzt keine Ereignis-Ausgänge.

### **Daten-Eingänge**

Keine – dieser Funktionsblock besitzt keine separaten Daten-Eingänge. Alle Daten werden über den ADI-Adapter transportiert.

### **Daten-Ausgänge**

Keine – dieser Funktionsblock besitzt keine separaten Daten-Ausgänge. Alle Daten werden über die ADI-Adapter ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::ADI` | `IN` | Socket | Eingehender ADI-Adapter, der auf die beiden Ausgänge verteilt wird. |
| `adapter::types::unidirectional::ADI` | `OUT1` | Plug | Erster Ausgangs-Adapter (Duplikat des Eingangs). |
| `adapter::types::unidirectional::ADI` | `OUT2` | Plug | Zweiter Ausgangs-Adapter (Duplikat des Eingangs). |

## Funktionsweise

Der Baustein leitet den über den Socket `IN` empfangenen ADI‑Adapter ohne Änderungen an beide Plugs `OUT1` und `OUT2` weiter. Dadurch stehen die vom Eingangsadapter bereitgestellten Daten und Ereignisse gleichzeitig an beiden Ausgängen zur Verfügung. Es findet keine Verarbeitung, Verzögerung oder Umformung der Daten statt.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_ADI_SPLIT`) deklariert und kann in unterschiedlichen ADI‑Umgebungen wiederverwendet werden.  
- **Kein Zustandsautomat:** Aufgrund der reinen Signalweiterleitung besitzt der FB keinen eigenen Zustandsautomaten (ECC).  
- **Adapter‑basiert:** Der gesamte Datenaustausch erfolgt ausschließlich über Adapter, nicht über einzelne Daten- oder Ereignis-Ports.

## Zustandsübersicht

Dieser Funktionsblock besitzt keinen internen Zustandsautomaten. Die Weiterleitung erfolgt statisch und ohne zeitliche Abhängigkeiten.

## Anwendungsszenarien

- **Signalvervielfältigung:** Wenn ein von einem Sensor oder einer Steuerung gelieferter ADI‑Adapter an mehrere nachfolgende Funktionseinheiten (z. B. zur Anzeige, Protokollierung oder parallelen Verarbeitung) verteilt werden soll.  
- **Architekturentkopplung:** In Systemen, in denen ein Ausgangssignal mehrfach benötigt wird, ohne dass der Quellbaustein die Anzahl der Senken kennen muss.  
- **Prototypen und Testaufbauten:** Schnelle Erweiterung einer bestehenden Adapter‑Verschaltung um einen zweiten Abzweig.

## Vergleich mit ähnlichen Bausteinen

- **Ereignis‑/Daten‑Splitter:** Konventionelle Splitter-FBs (z. B. `SPLIT` für `BOOL`) arbeiten auf einzelnen Daten‑ und Ereignis‑Kanälen. `ADI_SPLIT_2` hingegen kopiert einen gesamten Adapter inklusive aller enthaltenen Daten und Ereignisse.  
- **Mux/Demux‑Bausteine:** Multiplexer und Demultiplexer führen eine Zusammenführung oder Verteilung mit Auswahl durch; `ADI_SPLIT_2` verteilt starr und ohne Selektion.

## Fazit

`ADI_SPLIT_2` ist ein einfacher, aber nützlicher Funktionsblock zur Verteilung eines ADI‑Adapters auf zwei identische Ausgänge. Er erleichtert das Design von Adapter-basierten Steuerungen und vermeidet redundante Quellbausteine. Seine generische Natur und die fehlende interne Logik machen ihn zu einer flexiblen Komponente in IEC‑61499‑Applikationen.
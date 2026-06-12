# ADI_FB_CTU


![ADI_FB_CTU](./ADI_FB_CTU.svg)

* * * * * * * * * *

## Einleitung
Der ADI_FB_CTU ist ein Aufwärtszähler (Up-Counter) für Ganzzahlen vom Typ DINT, dessen Ein- und Ausgänge über standardisierte Adapter (AX und ADI) bereitgestellt werden. Er kapselt den Standard-Funktionsblock `FB_CTU_DINT` und ermöglicht dessen Integration in modulare Adapter-basierte Systeme. Der Baustein eignet sich für allgemeine Zählaufgaben in der Automatisierungstechnik.

## Schnittstellenstruktur
Der Funktionsblock besitzt keine direkten Ereignis- oder Datenschnittstellen, sondern ausschließlich Adapter für die Anbindung. Die nachfolgende Tabelle erläutert die verfügbaren Adapter, deren Typ und Bedeutung.

| Richtung | Name | Adapter-Typ | Beschreibung |
|----------|------|-------------|--------------|
| **Eingang (Socket)** | `CU` | `AX` | Zählimpuls-Eingang (Ereignis + Daten) |
| **Eingang (Socket)** | `R`  | `AX` | Rücksetz-Eingang (Ereignis + Daten) |
| **Eingang (Socket)** | `PV` | `ADI` | Vorgabewert (Preset Value) für den Vergleich |
| **Ausgang (Plug)**  | `Q`  | `AX` | Ausgangssignal – aktiv, wenn Zählerstand ≥ PV |
| **Ausgang (Plug)**  | `CV` | `ADI` | Aktueller Zählerstand |

Die Adapter `AX` (Ereignis-Adapter) und `ADI` (Daten-Adapter) sind unidirektional. Über die Adapter werden sowohl die Ereignisse als auch die zugehörigen Datenwerte übertragen.

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Die Ereignisse werden über die Adapter `CU` und `R` (vom Typ `AX`) zugeführt.

### **Ereignis-Ausgänge**
Ein direkter Ereignis-Ausgang `CNF` signalisiert die Bestätigung einer Verarbeitung. Zusätzlich wird über den Adapter `Q` (Typ `AX`) ein Ausgangsereignis bei jeder Aktualisierung ausgegeben.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der Vorgabewert wird über den Adapter `PV` (Typ `ADI`) bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der aktuelle Zählerstand wird über den Adapter `CV` (Typ `ADI`) ausgegeben.

### **Adapter**
Der Funktionsblock verwendet drei Sockets (Eingangsadapter) und zwei Plugs (Ausgangsadapter):

- **`CU` (Socket, `AX`)**: Zählimpuls – bei jedem Ereignis wird der interne Zähler inkrementiert.
- **`R`  (Socket, `AX`)**: Reset – setzt den Zähler auf Null zurück.
- **`PV` (Socket, `ADI`)**: Preset Value – legt den Schwellwert fest, ab dem der Ausgang `Q` aktiv wird.
- **`Q`  (Plug, `AX`)**: Ausgang – wird aktiv, sobald der Zählerstand den Wert von `PV` erreicht oder überschreitet.
- **`CV` (Plug, `ADI`)**: Aktueller Zählerstand – kann von nachgeschalteten Bausteinen gelesen werden.

## Funktionsweise
Der ADI_FB_CTU realisiert einen einfachen Aufwärtszähler mit Vorgabewert-Vergleich.  

- Bei jedem Ereignis am Eingang `CU` wird der interne Zähler um 1 erhöht.  
- Ein Ereignis am Eingang `R` setzt den Zähler auf 0 zurück.  
- Der Vorgabewert `PV` wird beim Eintreffen eines Ereignisses am Eingang `PV` aktualisiert.  

Nach jeder Verarbeitung (unabhängig davon, ob `CU`, `R` oder `PV` ausgelöst hat) wird das Bestätigungsereignis `CNF` ausgegeben. Gleichzeitig wird auch der Ausgangsadapter `Q` mit einem Ereignis bedient und der aktuelle Zählerstand über den Adapter `CV` bereitgestellt.  

> **Wichtig:** Der Baustein feuert das Ausgangsereignis `Q.E1` bei **jeder** Aktualisierung – also auch bei Reset oder Vorgabewert-Änderung – nicht nur bei einer Änderung des Zählerstands. Soll das Ausgangssignal nur bei einer tatsächlichen Änderung des Vergleichsergebnisses ausgelöst werden, empfehlen die Entwickler die Verwendung eines AX_D_FF als nachgeschalteten Filter.

Intern wird ein Standard-Funktionsblock `FB_CTU_DINT` verwendet, dessen Ein- und Ausgänge über die Adapter verdrahtet sind. Der Zählwert ist vom Typ `DINT` (32-Bit-Ganzzahl).

## Technische Besonderheiten
- **Adapter-basierte Schnittstelle** – ermöglicht eine lose Kopplung und einfache Integration in Adapter-basierte Architekturen (z. B. gemäß IEC 61499).  
- **Unidirektionale Adapter** – die Adapter `AX` und `ADI` übertragen jeweils nur in eine Richtung.  
- **Bestätigungsereignis `CNF`** – jedes Ereignis an einem Eingang löst eine sofortige Bestätigung aus.  
- **Keine Flankenerkennung** – der Baustein reagiert auf jedes Ereignis, nicht auf steigende oder fallende Flanken eines digitalen Signals.  
- **Hinweis im Quelltext** – die häufige Ausgabe des `Q.E1`-Ereignisses kann bei zeitkritischen Anwendungen zu unnötigen Lasten führen; ggf. ist eine Filterung erforderlich.

## Zustandsübersicht
Der Funktionsblock besitzt einen einzigen internen Zustand: den aktuellen Zählerstand (Initialwert = 0). Abhängig von den eingehenden Ereignissen ergeben sich folgende Zustandsübergänge:

| Ereignis | Bedingung | Neuer Zustand (Zähler) | Ausgabe |
|----------|-----------|------------------------|---------|
| `CU`     | –         | Zähler + 1             | `CNF`, `Q.E1`, `CV` |
| `R`      | –         | 0                      | `CNF`, `Q.E1`, `CV` |
| `PV`     | –         | unverändert            | `CNF`, `Q.E1`, `CV` (PV-Wert wird intern gespeichert) |

Der Ausgang `Q` (über den Adapter) wird gesetzt, sobald `Zähler ≥ PV` ist. Der aktuelle Wert von `Q` wird bei jeder Ausgabe mitgeliefert.

## Anwendungsszenarien
- **Ereigniszählung** – Zählen von Impulsen, z. B. Teiledurchlauf, Maschinenzyklen.  
- **Füllstandüberwachung** – Erfassen der Anzahl von Behältern oder Chargen.  
- **Produktionssteuerung** – Auslösen einer Aktion, wenn eine bestimmte Stückzahl erreicht ist.  
- **Zeitmessung** – in Kombination mit einem Impulsgeber kann die Anzahl der Impulse als Zeitmaß genutzt werden.  
- **Adapter-basierte Automatisierungssysteme** – überall dort, wo eine einheitliche Adapter-Schnittstelle gefordert ist.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaften |
|----------|---------------|
| `CTU` (Standard, ohne Adapter) | Gleiche Zählfunktion, aber mit direkten Ereignis- und Dateneingängen/-ausgängen. Einfacher in klassischen IEC‑61499-Netzwerken nutzbar. |
| `ADI_FB_CTUD` | Auf-/Abwärtszähler, ebenfalls Adapter-basiert. Bietet zusätzlich einen Abwärtszähleingang. |
| `FB_CTU_DINT` (intern) | Dieselbe Zähllogik, jedoch ohne Adapterkapselung. Die Adapterversion bietet eine einheitliche, modulare Schnittstelle. |
| `CTU` mit AX-Filter | Wenn eine Flankenauswertung erforderlich ist, kann durch Vorschalten eines AX_D_FF eine reine Änderungserkennung realisiert werden. |

Der ADI_FB_CTU ist als „Wrapper“ für den Standardzähler konzipiert und erleichtert die Wiederverwendung in Adapter-basierten Frameworks.

## Fazit
Der ADI_FB_CTU ist ein flexibler, adapterbasierter Aufwärtszähler für DINT-Werte. Er kapselt die bewährte Zähllogik des `FB_CTU_DINT` und stellt sie über standardisierte Adapter (AX und ADI) bereit. Die Besonderheit, dass Ausgangsereignisse bei jeder Aktualisierung generiert werden, sollte bei der Systemauslegung berücksichtigt werden. Der Baustein eignet sich hervorragend für modulare, erweiterbare Automatisierungslösungen, in denen eine einheitliche Adapter-Schnittstelle gefordert wird.
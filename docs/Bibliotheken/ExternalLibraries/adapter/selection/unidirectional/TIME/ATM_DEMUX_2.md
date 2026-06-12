# ATM_DEMUX_2


![ATM_DEMUX_2](./ATM_DEMUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ATM_DEMUX_2` realisiert einen generischen Demultiplexer für ATM‑Signale. Er verteilt ein an seinem Eingang anliegendes ATM‑Signal wahlweise an einen von zwei Ausgängen. Die Auswahl des Zielausgangs erfolgt über einen ganzzahligen Index, der beim Aufruf übergeben wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K, löst die Demultiplex‑Operation aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung, dass die Index‑Setzung und Weiterleitung abgeschlossen ist. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index, welcher Ausgang (1 oder 2) mit dem Eingangssignal verbunden werden soll. |

### **Daten-Ausgänge**

Keine eigenständigen Datenausgänge; die Signale werden über die Adapter‑Ausgänge bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | OUT1 | `adapter::types::unidirectional::ATM` | Erster ATM‑Ausgangskanal. |
| Plug (Ausgang) | OUT2 | `adapter::types::unidirectional::ATM` | Zweiter ATM‑Ausgangskanal. |
| Socket (Eingang) | IN | `adapter::types::unidirectional::ATM` | ATM‑Eingangssignal, das demultiplext wird. |

## Funktionsweise

Der Baustein arbeitet als **1‑zu‑2‑Demultiplexer** für ATM‑Signale. Bei einem Ereignis am **REQ**‑Eingang wird der am Daten‑Eingang **K** (Datentyp `UINT`) übergebene Index ausgewertet. Mögliche Werte von `K` sind:

- `1` → Das am Socket **IN** anliegende Signal wird an den Plug **OUT1** weitergeleitet.
- `2` → Das Signal wird an den Plug **OUT2** weitergeleitet.

Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben. Das zugrunde liegende ATM‑Protokoll wird durch die Adapter‑Typdefinition `adapter::types::unidirectional::ATM` bereitgestellt.

## Technische Besonderheiten

- **Generischer Aufbau**: Der Baustein ist als generischer Funktionsbaustein (`GenericClassName` = `'GEN_ATM_DEMUX'`) deklariert. Dadurch kann er in verschiedenen Ausprägungen (z. B. als `ATM_DEMUX_N` mit mehr als zwei Ausgängen) durch Vererbung oder Parametrisierung abgeleitet werden.
- **Adapter‑basierte Kommunikation**: Die Ein‑ und Ausgänge sind als Adapter (Plug/Socket) definiert. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen desselben Protokolls, ohne auf direkte DataConnections angewiesen zu sein.
- **Minimale Zustandslogik**: Der Baustein besitzt kein explizites Zustandsdiagramm (ECC); die Logik beschränkt sich auf die unmittelbare Umsetzung der Index‑Weiche.

## Zustandsübersicht

Der Baustein implementiert eine triviale endliche Zustandsmaschine, die in der Service‑Sequenz abgebildet wird:

1. **Warten** auf REQ‑Ereignis.
2. Bei REQ wird der Index K ausgewertet und die entsprechende Verbindung hergestellt.
3. Nach der Umschaltung wird CNF ausgegeben.
4. Rückkehr in den Wartezustand.

## Anwendungsszenarien

- **Routing von ATM‑Strömen**: Verteilung eines eingehenden ATM‑Signals auf zwei verschiedene Verarbeitungspfade (z. B. Überwachung und Datenanalyse).
- **Test- und Simulationsumgebungen**: Gezielte Zuschaltung von Prüfsignalen auf einen von zwei Ausgängen.
- **Redundanzschaltungen**: Umschalten zwischen einem primären und einem sekundären Pfad in Abhängigkeit eines Steuerindex.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| `ATM_DEMUX_2` | Spezifisch für 2‑Ausgangs‑Demultiplex, generisch erweiterbar. |
| `ATM_SWITCH_2` | Realisiert eine 2‑zu‑1‑Multiplex‑Funktion (Auswahl eines von zwei Eingängen). |
| `DEMUX` (allgemein) | Oft als reiner Daten‑Demultiplexer ohne Adapter‑Protokoll, ereignisgesteuert. |

Der `ATM_DEMUX_2` hebt sich durch die Integration des ATM‑Adapter‑Protokolls und die generische Architektur hervor.

## Fazit

Der Funktionsbaustein **ATM_DEMUX_2** bietet eine kompakte, wiederverwendbare Lösung zur Demultiplexierung von ATM‑Signalen in der Automatisierungstechnik. Durch den generischen Aufbau und die Adapter‑Schnittstellen ist er leicht an unterschiedliche Kanalanzahlen anpassbar und eignet sich für modulare Steuerungssysteme nach IEC 61499.
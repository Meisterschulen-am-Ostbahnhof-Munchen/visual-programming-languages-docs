# SPLIT_AL_INTO_AD


![SPLIT_AL_INTO_AD](./SPLIT_AL_INTO_AD.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `SPLIT_AL_INTO_AD` dient dazu, einen eingehenden **AL (LWORD)**-Adapter in zwei separate **AD (DWORD)**-Adapter aufzuteilen. Er realisiert damit die notwendige Schnittstellenwandlung für Anwendungen, bei denen ein großes Datenwort (LWORD) in zwei kleinere DWORDs zerlegt und über unidirektionale Adapter bereitgestellt werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **nicht direkt vorhanden**  
  Ereignisse werden über den SOCKET-Adapter `IN` (Signale `IN.E1`) empfangen. Intern löst dies die Verarbeitung aus.

### **Ereignis-Ausgänge**
- **nicht direkt vorhanden**  
  Die Ausgabeereignisse erfolgen über die PLUG-Adapter `DWORD_00.E1` und `DWORD_01.E1`, sobald ein neuer Wert bereitsteht.

### **Daten-Eingänge**
- **IN.D1** – Eingangsdaten (`LWORD`) aus dem SOCKET-Adapter `IN`.

### **Daten-Ausgänge**
- **DWORD_00.D1** – Erstes aufgeteiltes DWORD (Low-Teil) am PLUG-Adapter `DWORD_00`.
- **DWORD_01.D1** – Zweites aufgeteiltes DWORD (High-Teil) am PLUG-Adapter `DWORD_01`.

### **Adapter**
| Typ   | Name       | Richtung | Kommentar                          |
|-------|------------|----------|------------------------------------|
| SOCKET | `IN`       | Eingang  | AL (LWORD) – Quelladapter          |
| PLUG  | `DWORD_00` | Ausgang  | AD (DWORD) – erster Zieladapter    |
| PLUG  | `DWORD_01` | Ausgang  | AD (DWORD) – zweiter Zieladapter   |

## Funktionsweise

Der Baustein arbeitet rein ereignisgesteuert. Sobald am SOCKET `IN` ein Ereignis eintrifft (`IN.E1`), wird das zugehörige Datenwort (`IN.D1`, Typ `LWORD`) intern an den Unterbaustein `SPLIT_LWORD_INTO_DWORDS` weitergeleitet. Dieser zerlegt das 64‑Bit‑Wort in zwei 32‑Bit‑DWORDs.

Die beiden Ergebnisse werden parallel an die Eingänge der Flip‑Flop‑Bausteine `E_D_FF_ANY_00` und `E_D_FF_ANY_01` übergeben. Gleichzeitig löst der Splitter‑Baustein ein gemeinsames Bestätigungsereignis (`CNF`) aus, das beide Flip‑Flops taktet. Dadurch werden die neuen DWORD‑Werte übernommen und als gültige Ausgangsdaten an den jeweiligen PLUG‑Adapter (`DWORD_00.D1` und `DWORD_01.D1`) ausgegeben. Gleichzeitig wird ein Ereignis an den entsprechenden Ausgangsadapter gesendet (`DWORD_00.E1` bzw. `DWORD_01.E1`).

Die Flip‑Flops stellen sicher, dass die Ausgangsdaten bis zum nächsten gültigen Eingabeereignis stabil bleiben und nur bei einer neuen Verarbeitung aktualisiert werden.

## Technische Besonderheiten

- **Vollständige Adapter‑Kapselung** – Der Baustein hat keine direkten Events oder Datenports, sondern kommuniziert ausschließlich über standardisierte unidirektionale Adapter (AL/AD).  
- **Interne Nutzung von `SPLIT_LWORD_INTO_DWORDS`** – Dieser separate, typisierte Splitter‑Baustein übernimmt die reine Datenaufteilung; die Flip‑Flops entkoppeln Daten‑ und Ereignisweitergabe.  
- **Null‑Latenz bei gleichzeitigen Ereignissen** – Da beide Flip‑Flops durch dasselbe `CNF` getaktet werden, werden beide Ausgänge stets synchron aktualisiert.  
- **Kein eigenes Zustandsverhalten** – Der Baustein ist rein kombinatorisch mit ereignisgesteuerter Speicherung; es existiert keine interne Zustandsmaschine.

## Zustandsübersicht

Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Sein Verhalten ist rein daten- und ereignisgesteuert:

- **Idle** – Kein Eingabeereignis; Ausgangsdaten bleiben unverändert.  
- **Processing** – Nach Eintreffen von `IN.E1` werden die Daten aufgeteilt und an die Ausgänge übergeben.  
- **Stable** – Die Flip‑Flops halten die Werte bis zum nächsten Ereignis.

## Anwendungsszenarien

- **Industrielle Automatisierung** – Wenn ein Sensor/Aktor ein LWORD‑Datenwort (z. B. 64‑Bit‑Zähler oder kombinierte Status‑/Steuerwörter) über einen AL‑Adapter liefert, die nachfolgenden Module aber mit zwei getrennten DWORD‑Adaptern arbeiten.  
- **Protokoll‑Umsetzung** – Zerlegung großer Datenpakete in handhabbare Teilwörter für Adapter‑basierte Kommunikationsprotokolle.  
- **Datenvalidierung und -weiterleitung** – Aufteilen eines LWORD in zwei DWORDs, um unterschiedliche Verarbeitungspfade (z. B. Visualisierung und Steuerung) parallel zu bedienen.

## Vergleich mit ähnlichen Bausteinen

- **`SPLIT_LWORD_INTO_DWORDS`** – reiner Datensplitter ohne Adapter‑Anbindung und ohne Ereignis‑Synchronisation. `SPLIT_AL_INTO_AD` erweitert diesen um die erforderlichen Adapter‑Schnittstellen und Flip‑Flops zur korrekten Ereignisbehandlung.  
- **Manuelle Aufteilung** – Alternativ könnte man die Aufteilung direkt in der Logik des übergeordneten Systems programmieren; der Baustein verringert jedoch den Aufwand und verbessert die Wiederverwendbarkeit.

## Fazit

`SPLIT_AL_INTO_AD` ist ein spezialisierter, aber eleganter Adapter‑Baustein, der die nahtlose Verbindung zwischen einer LWORD‑Quelle und zwei DWORD‑Senken ermöglicht. Durch die saubere Trennung von Datenaufteilung und Ereignissynchronisation eignet er sich besonders für modulare, adapterbasierte Steuerungsarchitekturen.
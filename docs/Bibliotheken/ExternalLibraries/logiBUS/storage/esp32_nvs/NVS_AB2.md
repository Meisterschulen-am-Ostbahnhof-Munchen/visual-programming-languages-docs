# NVS_AB2


![NVS_AB2](./NVS_AB2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **NVS_AB2** ermöglicht das Laden und Speichern von `REAL`-Daten in einem nichtflüchtigen Speicher (Non‑Volatile Storage, NVS) unter Verwendung eines Zeichenketten-Schlüssels. Er kapselt den NVS-Zugriff in einer komfortablen, asynchronen Schnittstelle und kommuniziert mit der Umgebung über einen bidirektionalen **AB2**‑Adapter. Dadurch eignet sich der Baustein besonders für Szenarien, in denen Konfigurationswerte oder Zustandsdaten dauerhaft auf einem ESP32 gespeichert werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INIT`   | EInit | Initialisiert den Baustein. Die Eingangsdaten (`QI`, `KEY`, `DEFAULT_VALUE`) werden beim Eintritt dieses Ereignisses übernommen. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| `INITO`  | EInit | Bestätigung der abgeschlossenen Initialisierung und der ersten Leseoperation. |

### **Daten-Eingänge**

| Name           | Typ    | Beschreibung |
|----------------|--------|--------------|
| `QI`           | BOOL   | Qualifizierer für das Initialisierungsereignis (z. B. Freigabe der Verarbeitung). |
| `KEY`          | STRING | Name des Schlüssels, unter dem der Wert im NVS abgelegt ist. |
| `DEFAULT_VALUE`| REAL   | Wert, der zurückgegeben wird, falls im NVS noch kein Wert für den angegebenen Schlüssel existiert. |

### **Daten-Ausgänge**

| Name     | Typ    | Beschreibung |
|----------|--------|--------------|
| `QO`     | BOOL   | Qualifizierer für das Ausgangsereignis – signalisiert Erfolg (`TRUE`) oder Fehler (`FALSE`). |
| `STATUS` | STRING | Detailstatusmeldung (z. B. Fehlertext oder Bestätigung). |

### **Adapter**

| Name  | Typ (AB2‑Adapter) | Beschreibung |
|-------|-------------------|--------------|
| `VAL` | `adapter::types::bidirectional::AB2` | Bidirektionale Schnittstelle für den Datenwert. Lesen und Schreiben erfolgen über die Adapterkanäle (Events: `EI1`, `EO1`; Daten: `DI1`, `DO1`). |

## Funktionsweise
Beim Eintreffen des **INIT**‑Ereignisses wird der interne NVS‑Baustein initialisiert. Unmittelbar nach erfolgreicher Initialisierung wird automatisch eine **Leseoperation** (`GET`) gestartet, die den zum Schlüssel `KEY` gehörenden Wert aus dem NVS ausliest. Falls kein Wert vorhanden ist, wird `DEFAULT_VALUE` verwendet. Der gelesene Wert wird über den Adapter (`VAL.DI1`) ausgegeben und das Ereignis `INITO` signalisiert den Abschluss.

Nach der Initialisierung kann der Baustein über den Adapter asynchrone Lese‑ und Schreibanforderungen bearbeiten:
- **Lesen**: Ein empfangenes Ereignis am Adapter‑Port `VAL.EO1` löst eine erneute Leseoperation (`GET`) im NVS aus. Der gelesene Wert wird wieder über `VAL.DI1` bereitgestellt, und die Bestätigung (`VAL.EI1`) wird gesendet.
- **Schreiben**: Über den Adapter wird der zu speichernde Wert auf `VAL.DO1` bereitgestellt. Ein Ereignis an `VAL.EO1` triggert die **Schreiboperation** (`SET`) im NVS. Nach erfolgreichem Speichern wird über `VAL.EI1` quittiert.

Die Ausgänge `QO` und `STATUS` werden bei jedem der Ausgangsereignisse (`INITO`, sowie den internen Adapterbestätigungen) auf den aktuellen Status des NVS‑Bausteins gesetzt.

## Technische Besonderheiten
- **NVS-Zugriff auf dem ESP32**: Der Baustein nutzt den unter `logiBUS::storage::esp32_nvs::NVS` definierten Funktionsblock, der die Flash‑Speicherverwaltung des ESP32 kapselt.
- **Bidirektionale Adapter‑Schnittstelle**: Durch den AB2‑Adapter kann der Baustein sowohl Lese‑ als auch Schreibanforderungen aus der Umgebung verarbeiten, ohne dass separate Auslöseereignisse am FB selbst nötig sind.
- **Automatischer Erstlesezugriff**: Nach der Initialisierung wird sofort der gespeicherte Wert gelesen, sodass nach `INITO` der aktuelle Datenwert über den Adapter verfügbar ist.
- **Fehlerbehandlung**: Der Status (`STATUS`) und der Qualifizierer (`QO`) geben Aufschluss über Erfolg oder Misserfolg jeder NVS‑Operation.

## Zustandsübersicht
Der Funktionsblock besitzt keine expliziten Zustandsautomaten, da er als Composite‑Baustein das Verhalten des internen NVS‑FBs nutzt. Im Wesentlichen lassen sich folgende Phasen unterscheiden:
1. **Initialisierung** – ausgelöst durch `INIT`
2. **Bereit** – nach erfolgreicher Initialisierung wartet der Baustein auf Adapter‑Ereignisse
3. **Lese‑/Schreiboperation** – kurzzeitiger Zugriff auf den NVS während der Verarbeitung eines Adapter‑Ereignisses

## Anwendungsszenarien
- **Konfigurationsspeicherung** für Geräteparameter (z. B. Sollwerte, Kalibrierdaten) auf ESP32‑basierten Steuerungen.
- **Persistente Zustandssicherung**, z. B. letzter Betriebsmodus oder Zählerstände über einen Neustart hinweg.
- **Datenaustausch über AB2‑Protokoll** mit anderen Bausteinen, die das AB2‑Adapter‑Interface unterstützen – einfache Integration in bestehende Automatisierungslösungen.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einfacheren Lese‑/Schreib‑Bausteinen (z. B. direkte NVS‑FBs ohne Adapter) bietet **NVS_AB2**:
- **Asynchrone, ereignisgesteuerte Kommunikation** über den AB2‑Adapter – entkoppelt den Datenzugriff vom Hauptsteuerungsfluss.
- **Automatische Initialisierung und Erstlese** reduziert den Programmieraufwand.
- **Einheitliche Fehlersignalisierung** über `QO` und `STATUS`.

Bausteine ohne Adapter erfordern hingegen separate Event‑Eingänge für Lesen und Schreiben und bieten keine standardisierte bidirektionale Schnittstelle.

## Fazit
**NVS_AB2** ist ein praxisorientierter Funktionsblock für den zuverlässigen, asynchronen Zugriff auf den nichtflüchtigen Speicher eines ESP32. Durch die Kapselung der NVS‑Logik in einem Composite‑Baustein und die bereitgestellte AB2‑Adapter‑Schnittstelle lässt er sich flexibel in Automatisierungsprojekte einbinden, die persistente Datenhaltung erfordern. Die Kombination aus automatischer Erstinitialisierung, Lese‑/Schreibunterstützung und klarer Statusrückmeldung macht ihn zu einer effizienten Lösung für Embedded‑Steuerungen.
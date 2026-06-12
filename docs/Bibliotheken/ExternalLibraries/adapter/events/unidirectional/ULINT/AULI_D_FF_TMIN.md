# AULI_D_FF_TMIN


![AULI_D_FF_TMIN](./AULI_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_D_FF_TMIN** realisiert ein Daten-Latch (D-Flipflop) mit einer einstellbaren Mindestverzögerungszeit zwischen aufeinanderfolgenden Ereignisausgaben. Er dient als Speicherglied für asynchrone Ereignis-/Datenschnittstellen und stellt sicher, dass nach einer Datenübernahme ein definiertes Zeitintervall vergeht, bevor ein weiteres Ereignis ausgelöst wird. Der Baustein arbeitet ausschließlich über Adapter-Schnittstellen vom Typ `AULI` (unidirektional) und ist dadurch besonders für modulare und verteilte Steuerungsarchitekturen geeignet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                                      |
|-------|--------|-----------------------------------------------|
| INIT  | EInit  | Initialisierungsanforderung; wird mit `Tmin` synchronisiert |

### **Ereignis-Ausgänge**

| Name  | Typ    | Kommentar                                      |
|-------|--------|-----------------------------------------------|
| INITO | EInit  | Bestätigung der Initialisierung               |

### **Daten-Eingänge**

| Name  | Typ   | Kommentar                                              |
|-------|-------|--------------------------------------------------------|
| Tmin  | TIME  | Mindestzeit zwischen zwei Ereignisausgaben (EO) am Ausgangsadapter |

### **Daten-Ausgänge**

Keine

### **Adapter**

| Name | Rolle     | Typ      | Kommentar                                  |
|------|-----------|----------|--------------------------------------------|
| I    | Socket    | AULI     | Eingang: zu latchierender Wert (Ereignis E1, Daten D1) |
| Q    | Plug      | AULI     | Ausgang: latchender Wert (Ereignis E1, Daten D1) |

## Funktionsweise

Der Baustein kapselt einen internen `E_D_FF_ANY_TMIN`-Funktionsblock aus der IEC‑61499‑Bibliothek. Er arbeitet als flankengesteuertes D‑Flipflop mit folgenden Abläufen:

1. **Initialisierung** – Ein Ereignis am Eingang `INIT` setzt den internen Zustand zurück und übernimmt den Parameter `Tmin`. Der Ausgang `INITO` quittiert die Initialisierung.
2. **Ereignis‑gesteuerte Datenübernahme** –  
   - Ein Ereignis am Adapter‑Eingang `I.E1` (als Taktsignal) übernimmt den aktuellen Datenwert `I.D1` in das interne Flipflop.  
   - Gleichzeitig wird die Mindestzeit `Tmin` gestartet.  
   - Nach Ablauf von `Tmin` wird ein Ereignis am Adapter‑Ausgang `Q.E1` ausgelöst und der übernommene Datenwert `Q.D1` ausgegeben.
3. **Sperrzeit** – Während `Tmin` noch aktiv ist, wird ein erneutes Eingangsereignis ignoriert oder gepuffert (abhängig von der internen Implementierung). Erst nach Ablauf der Zeit kann der nächste Wert übernommen werden.

## Technische Besonderheiten

- **Unidirektionale Adapter** – Der Baustein verwendet ausschließlich den standardisierten Adaptertyp `AULI` für Ereignisse und Daten, was eine einfache Kopplung mit anderen AULI‑kompatiblen Bausteinen ermöglicht.
- **Mindestzeit (`Tmin`)** – Erzwingt eine minimale Pause zwischen zwei aufeinanderfolgenden Ausgangsereignissen. Dies verhindert Datenverluste oder Überlastungen in nachgeschalteten Komponenten mit begrenzter Verarbeitungsgeschwindigkeit.
- **Keine eigenen Daten‑Ausgänge** – Die Ausgabedaten werden ausschließlich über den Plugin‑Adapter `Q` bereitgestellt, was die Modularität erhöht.

## Zustandsübersicht

Der interne FB `E_D_FF_ANY_TMIN` kann vereinfacht durch drei Zustände beschrieben werden:

- **IDLE** – Warten auf ein Taktereignis am Eingang `I.E1`.
- **LATCHED** – Daten wurden übernommen und `Tmin`‑Timer läuft. Keine neue Übernahme möglich.
- **OUTPUT** – `Tmin` abgelaufen; Ausgangsereignis wird ausgelöst und zurück in den IDLE‑Zustand gewechselt.

Die Initialisierung (`INIT`) setzt den Baustein in den IDLE‑Zustand zurück.

## Anwendungsszenarien

- **Datensynchronisation** in zeitkritischen Regelkreisen, bei denen ein Sensorwert nur in einem Mindestabstand abgetastet werden darf.
- **Pufferung** von asynchronen Ereignissen, um eine Lastspitze im Datenstrom zu glätten.
- **Kaskadierung** von Flipflops mit unterschiedlichen Mindestzeiten, um eine zeitlich gestaffelte Signalverarbeitung zu realisieren.
- **Schnittstelle zwischen schneller und langsamer Komponente** (z. B. zwischen einer schnellen Logik und einem langsamen Aktor).

## Vergleich mit ähnlichen Bausteinen

- **E_D_FF** – Einfaches D‑Flipflop ohne Zeitsteuerung; übernimmt Daten bei jeder Taktflanke sofort. Der `AULI_D_FF_TMIN` erweitert dies um eine einstellbare Mindestzeit.
- **E_D_FF_TMIN** – Gleicher interner Kern, jedoch mit direkten Ereignis‑/Datenschnittstellen anstelle von Adaptern. Die Adapter‑Version `AULI_D_FF_TMIN` ist für Systeme entworfen, die auf standardisierte, wiederverwendbare Schnittstellen setzen.
- **E_D_FF_ANY_TMIN** (direkt genutzt) – Bietet dieselbe Funktionalität, ist aber für beliebige Datentypen ausgelegt. `AULI_D_FF_TMIN` ist speziell auf den AULI‑Adapter zugeschnitten.

## Fazit

Der `AULI_D_FF_TMIN` ist ein spezialisierter D‑Flipflop‑Baustein für Ereignis‑/Daten‑Adapter‑Schnittstellen, der durch die integrierte Mindestzeit `Tmin` eine zuverlässige und vorhersagbare Datenübernahme in zeitkritischen Umgebungen gewährleistet. Seine modulare Bauweise und die Einhaltung des IEC‑61499‑Anhangs A machen ihn zu einer robusten Komponente für industrielle Steuerungsanwendungen.
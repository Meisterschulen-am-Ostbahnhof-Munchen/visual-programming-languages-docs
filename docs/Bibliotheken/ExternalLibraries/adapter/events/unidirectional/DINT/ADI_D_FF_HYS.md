# ADI_D_FF_HYS


![ADI_D_FF_HYS](./ADI_D_FF_HYS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ADI_D_FF_HYS** realisiert ein datengetaktetes (D‑) Flipflop mit einer einstellbaren Hysterese. Er empfängt Werte über einen unidirektionalen Adapter-Eingang `I` und gibt den mit Hysterese übernommenen Zustand über den Adapter-Ausgang `Q` aus. Die Hysterese-Bandbreite wird beim Initialisierungsereignis `INIT` gesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ  | Beschreibung                     |
|----------|------|----------------------------------|
| `INIT`   | EInit | Setzt die Hysterese-Bandbreite (in Verbindung mit `HYSTERESIS`). |

### **Ereignis-Ausgänge**

| Ereignis | Typ  | Beschreibung                     |
|----------|------|----------------------------------|
| `INITO`  | EInit | Bestätigt die Ausführung von `INIT`. |

### **Daten-Eingänge**

| Variable      | Typ | Beschreibung                     |
|---------------|-----|----------------------------------|
| `HYSTERESIS`  | DINT | Hysterese-Bandbreite (ganzzahliger Wert). |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge; der latched Wert wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Schnittstelle | Typ | Richtung | Beschreibung                     |
|---------------|-----|----------|----------------------------------|
| `I`           | `adapter::types::unidirectional::ADI` | Socket | Eingangswert (bestehend aus Event `E1` und Data `D1`). |
| `Q`           | `adapter::types::unidirectional::ADI` | Plug   | Latched Ausgabewert (bestehend aus Event `E1` und Data `D1`). |

**Hinweis:** Der Adapter `ADI` (unidirectional) stellt standardmäßig einen Event- (E1) und einen Datenkanal (D1) zur Verfügung.

## Funktionsweise

1. **Initialisierung**  
   Durch ein Ereignis an `INIT` wird der Wert an `HYSTERESIS` übernommen und die interne Hysterese-Bandbreite für das Flipflop gesetzt. Das Initialisierungsereignis wird direkt an `INITO` weitergegeben.

2. **Datenübernahme**  
   Der Eingangsadapter `I` liefert mit jedem Event an `I.E1` den aktuellen Datenwert `I.D1`.  
   Der interne Funktionsblock `E_D_FF_ANY_HYS` übernimmt diesen Wert gemäß der konfigurierten Hysterese:  
   - Liegt der Eingangswert **über** dem oberen Schwellwert (gespeicherter Wert + Hysterese), wird der Ausgang auf `1` gesetzt.  
   - Liegt der Eingangswert **unter** dem unteren Schwellwert (gespeicherter Wert - Hysterese), wird der Ausgang auf `0` gesetzt.  
   - Bleibt der Wert innerhalb des Hysteresebandes, ändert sich der Ausgang nicht.

3. **Ausgabe**  
   Der intern latched Wert wird an den Datenausgang `Q.D1` weitergegeben. Gleichzeitig wird ein Event an `Q.E1` ausgelöst, um nachgeschalteten Logikbausteinen die Datenverarbeitung zu signalisieren.

## Technische Besonderheiten

- **Parametrisierbare Hysterese:** Die Hysterese-Bandbreite kann zur Laufzeit über `INIT` und `HYSTERESIS` angepasst werden (ganzzahliger Wert, Datentyp `DINT`).  
- **Adapterbasierte Kommunikation:** Der Baustein verwendet vollständig unidirektionale Adapter, die eine saubere Trennung von Signalfluss und Ereignissteuerung ermöglichen. Dadurch eignet er sich besonders für modulare und dezentrale Signalverarbeitung.  
- **Interne Realisierung:** Die Hysterese-Logik wird durch den standardisierten FB `E_D_FF_ANY_HYS` aus der Bibliothek `logiBUS::signalprocessing::hysteresis` abgebildet.  
- **Keine Verzögerung durch INIT:** Die Initialisierung (`INIT → INITO`) wird im gleichen Zyklus durchgeschleift; die Hysterese steht ab dem Folgezyklus zur Verfügung.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten, sondern basiert auf dem internen Zustand des D‑Flipflops `E_D_FF_ANY_HYS`. Dieser speichert:

- Den aktuellen Ausgangswert (latched).  
- Den zuletzt übernommenen Eingangswert (für die Hysteresebetrachtung).  

Eine Änderung des Ausgangs erfolgt nur, wenn der neue Eingangswert das Hystereseband verlässt.  

## Anwendungsszenarien

- **Entprellung von Sensorschaltern:** Ein- und Ausschaltschwellen mit Hysterese verhindern Flankenrauschen.  
- **Schwellwertüberwachung mit Rückfallverzögerung:** Temperatur-, Druck- oder Füllstandsregelung mit definierten Ein- und Ausschaltpunkten.  
- **Digitalisierung analoger Signale:** Umwandlung eines kontinuierlichen Wertebereichs in einen stabilen Binärwert (Schmitt-Trigger-Verhalten).  
- **Steuerung von Aktoren mit Hysterese:** Vermeidung von schnellem Ein-/Ausschalten, z. B. bei Thermostaten oder Pumpen.

## Vergleich mit ähnlichen Bausteinen

| Baustein             | Eigenschaften                                      |
|----------------------|----------------------------------------------------|
| **E_D_FF**           | Standard-D‑Flipflop ohne Hysterese (direkte Übernahme). |
| **E_D_FF_ANY_HYS**   | Identische Funktion, jedoch mit direkten Datenports statt Adaptern. |
| **Schmitt-Trigger**  | Ähnliches Verhalten, jedoch keine Parametrierbarkeit der Hysterese zur Laufzeit. |

Der **ADI_D_FF_HYS** bietet durch die Adapterschnittstelle eine besonders flexible Einbindung in heterogene Systeme, während die Hysterese zur Laufzeit konfiguriert werden kann.

## Fazit

Der **ADI_D_FF_HYS** ist ein robustes, parametrierbares D‑Flipflop mit Hysterese, das sich ideal für die Signalverarbeitung mit stabilen Schaltschwellen eignet. Die Verwendung unidirektionaler Adapter erleichtert die Integration in prozessnahe Steuerungsanwendungen und ermöglicht eine klare Trennung von Datentransport und Ereignissteuerung.
# ALI_D_FF_HYS


![ALI_D_FF_HYS](./ALI_D_FF_HYS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_D_FF_HYS** realisiert ein Datenlatch (D-Flipflop) mit einer Hysteresefunktion. Er dient der stabilen und entprellten Übertragung eines binären Signals: Ein eingehendes Datensignal wird bei einer steigenden Taktflanke übernommen und ausgegeben, wobei eine konfigurierbare Hysterese verhindert, dass kleine Signaländerungen (Rauschen) zu unerwünschten Ausgangsänderungen führen. Der Baustein ist speziell für die Verwendung der unidirektionalen **ALI**-Adapterstruktur in IEC 61499-Umgebungen ausgelegt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis  | Typ    | Kommentar                                 |
|-----------|--------|-------------------------------------------|
| `INIT`    | EInit  | Setzt den Hysteresewert für die Schaltschwelle. |

### **Ereignis-Ausgänge**

| Ereignis  | Typ    | Kommentar                                 |
|-----------|--------|-------------------------------------------|
| `INITO`   | EInit  | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Variable      | Typ  | Kommentar                                     |
|---------------|------|-----------------------------------------------|
| `HYSTERESIS`  | LINT | Hysterese-Bandbreite (z. B. als Ganzzahl)     |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgabe erfolgt über den Adapter `Q`.

### **Adapter**

| Richtung | Name | Typ                                        | Kommentar                    |
|----------|------|--------------------------------------------|------------------------------|
| Socket   | `I`  | `adapter::types::unidirectional::ALI`      | Eingangswert (Daten + Takt) |
| Plug     | `Q`  | `adapter::types::unidirectional::ALI`      | Ausgangswert (gelatchter Wert) |

Der Adapter `I` liefert zwei Signale:
- **`I.E1`** – Taktsignal (Ereignis)  
- **`I.D1`** – Dateneingang (z. B. BOOL oder numerisch)

Der Adapter `Q` stellt den gelatchten Wert als **`Q.D1`** zur Verfügung.

## Funktionsweise
Der Baustein arbeitet intern mit einem weiteren FB **E_D_FF_ANY_HYS** (aus der Bibliothek `logiBUS::signalprocessing::hysteresis`), welcher die Kernlogik umsetzt. Die Funktionsweise im Überblick:

1. **Initialisierung**  
   Beim Eintreffen des Ereignisses `INIT` wird der Wert von `HYSTERESIS` an den inneren Baustein übergeben und das Ereignis unverzögert als `INITO` bestätigt.

2. **Datenverarbeitung**  
   Die Ereignis- und Datenverbindungen sind direkt zwischen den Adaptern und dem inneren Baustein geschaltet:
   - `I.E1` → **CLK** (Taktsignal)
   - `I.D1` → **D** (Eingangsdaten)
   - **Q** → `Q.D1` (gelatchtes Ausgangssignal)

3. **Hystereseverhalten**  
   Bei jedem Takt (`CLK`) wird der aktuelle Datenwert `D` ausgewertet. Liegt `D` innerhalb des Hysteresebandes um den aktuellen Ausgangswert `Q`, so ändert sich der Ausgang nicht. Überschreitet `D` die obere bzw. untere Schwelle, wird der neue Wert übernommen. Dies unterdrückt Störungen und sorgt für einen sauberen, entprellten Signalverlauf.

## Technische Besonderheiten
- **Reine Adapterkommunikation**: Der FB verwendet ausschließlich unidirektionale Adapter (`ALI`) für die Ereignis- und Datenübergabe. Dadurch ist er in modularen, adapterbasierten Architekturen einfach einsetzbar.
- **Indirekte Hystereseimplementierung**: Die Hysterese wird nicht direkt im FB-Body, sondern durch den internen Baustein `E_D_FF_ANY_HYS` realisiert. Dies ermöglicht eine flexible Wiederverwendung der Logik.
- **Sofortige INIT-Bestätigung**: Das `INIT`-Ereignis wird durch eine direkte Verbindung (`INIT → INITO`) unmittelbar quittiert, ohne auf die Hystereselogik zu warten.
- **Typ des Hystereseparameters**: `HYSTERESIS` ist als `LINT` definiert, erlaubt also große ganzzahlige Werte.

## Zustandsübersicht
Der Baustein besitzt selbst keine sichtbaren Zustände, da alle Zustandslogik im internen FB gekapselt ist. Verhalten des D-Flipflops mit Hysterese:

- **Ruhezustand**: Ausgangswerte bleiben stabil, solange kein Takt anliegt.
- **Taktflanke (steigend)**:  
  - Wenn D > Q + HYSTERESIS → Q = D (Setzen)  
  - Wenn D < Q - HYSTERESIS → Q = D (Rücksetzen)  
  - Sonst → Q unverändert (Hysterese-Bereich)

## Anwendungsszenarien
Typische Einsatzfelder dieses Bausteins sind:

- **Entprellung von Schaltersignalen** in der Automatisierungstechnik (z. B. Endschalter, Näherungssensoren).
- **Signalaufbereitung in rauer Umgebung** (Agrartechnik, Maschinenbau) – die Hysterese verhindert Oszillationen durch Vibrationen oder Rauschen.
- **Grundbaustein für komplexere Logik** mit Adapter-basierter Datenweitergabe, z. B. als Eingangsstufe eines Zustandsautomaten.

## Vergleich mit ähnlichen Bausteinen

| Baustein               | Merkmal                                              |
|------------------------|------------------------------------------------------|
| **ALI_D_FF** (ohne Hyst.) | Einfaches D-FF ohne Rauschunterdrückung           |
| **ALI_D_FF_HYS** (dieser) | D-FF mit parametrierbarer Hysterese zur Störungsfilterung |
| Schmitt-Trigger-FB     | Ähnliche Funktion, jedoch oft mit festen Schwellen   |
| **E_D_FF_ANY_HYS**     | Interne Logik, allgemeiner Typ (kein Adapter-Format) |

Der Vorteil von **ALI_D_FF_HYS** liegt in der direkten Adapteranbindung, die eine nahtlose Integration in bestehende IEC 61499-Adapter-Netzwerke ermöglicht.

## Fazit
Der Funktionsblock **ALI_D_FF_HYS** bietet eine bewährte Kombination aus D-Flipflop und einstellbarer Hysterese, verpackt in einem standardkonformen IEC 61499-Adapter-Interface. Er eignet sich besonders für Anwendungen, bei denen Signale unter realen Bedingungen (Rauschen, Prellen) zuverlässig verarbeitet werden müssen. Durch die klare Trennung von Initialisierung und Datenverarbeitung sowie die Nutzung eines bewährten Unterbausteins ist er robust, wartbar und flexibel einsetzbar.
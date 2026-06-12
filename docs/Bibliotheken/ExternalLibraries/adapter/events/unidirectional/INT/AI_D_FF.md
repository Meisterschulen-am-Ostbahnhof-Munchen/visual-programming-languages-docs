# AI_D_FF


![AI_D_FF](./AI_D_FF.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AI_D_FF** realisiert ein data latch (D-Flipflop) zur temporären Speicherung eines Datenwerts. Er dient als Adapter-gekapselte Implementierung eines flankengesteuerten D-Flipflops nach IEC 61499, das bei einem Ereignis am Eingang den anliegenden Datenwert übernimmt und am Ausgang bereitstellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge.

### **Adapter**
| Bezeichnung | Richtung | Typ | Beschreibung |
|-------------|----------|-----|--------------|
| **I** | Socket | `adapter::types::unidirectional::AI` | Liefert das Eingangsereignis (E1) und den zu latchenden Datenwert (D1). |
| **Q** | Plug | `adapter::types::unidirectional::AI` | Gibt nach der Übernahme das Ergebnisereignis (E1) und den gespeicherten Datenwert (D1) aus. |

Der Adapter `AI` ist unidirektional, d.h. die Daten- und Ereignisflüsse verlaufen nur in eine Richtung. Socket **I** dient als Eingang, Plug **Q** als Ausgang.

## Funktionsweise
Interne Komponente ist ein `E_D_FF_ANY`-Funktionsblock (IEC 61499 D-Flipflop). Die Verdrahtung verbindet:
- `I.E1` → `E_D_FF_ANY.CLK` (Taktflanke)
- `I.D1` → `E_D_FF_ANY.D` (Dateneingang)
- `E_D_FF_ANY.EO` → `Q.E1` (Ausgangsereignis)
- `E_D_FF_ANY.Q` → `Q.D1` (latchender Datenwert)

**Ablauf:**  
Ein Ereignis an `I.E1` löst eine steigende Flanke am Takteingang des internen Flipflops aus. Der aktuelle Wert von `I.D1` wird dabei übernommen und steht nach Ende der Verarbeitung an `Q.D1` zur Verfügung. Gleichzeitig wird ein Ereignis an `Q.E1` ausgegeben, das die Gültigkeit des neuen Datenwerts signalisiert.

## Technische Besonderheiten
- **Adapter-Kapselung:** Der FB besitzt keine direkten Ein-/Ausgänge, sondern ausschließlich Adapter-Schnittstellen. Dies erleichtert die Wiederverwendung in modularen Architekturen, bei denen mehrere Signale gebündelt transportiert werden.
- **Unidirektionaler Datenfluss:** Die Adapter sind als reine Quellen (Plug) oder Senken (Socket) ausgelegt, was die Signalrichtung eindeutig festlegt.
- **Flankengesteuert:** Die Übernahme erfolgt nur bei einem Ereignis (steigende Flanke), nicht bei Pegeländerungen. Somit eignet sich der Baustein für getaktete Systeme.

## Zustandsübersicht
Der interne Zustand des Flipflops wird durch den gespeicherten Wert `Q` bestimmt. Es existieren zwei stabile Zustände:

| Takt (CLK) | D (Eingang) | Q (Ausgang) vorher | Q (Ausgang) nachher |
|------------|-------------|---------------------|----------------------|
| Kein Ereignis | - | Q_alt | Q_alt |
| Ereignis (steigende Flanke) | 0 | X | 0 |
| Ereignis (steigende Flanke) | 1 | X | 1 |

Bei jedem Ereignis an `I.E1` wird der aktuelle D-Wert unabhängig vom vorherigen Q-Wert übernommen.

## Anwendungsszenarien
- **Abtastung analoger Werte:** Ein Sensor (z.B. Temperatur, Druck) liefert über den Adapter `I` periodisch einen Messwert. Der FB speichert diesen bei einem Trigger-Ereignis und gibt ihn an die nachfolgende Logik weiter.
- **Zwischenspeicher in Datenpfaden:** In Fließband- oder Pipeline-Strukturen kann `AI_D_FF` als Datenhalte-Glied eingesetzt werden, um Werte für einen Taktzyklus zu puffern.
- **Entprellung / Flankenverarbeitung:** Kombiniert mit einem Taktgeber kann der Baustein verwendet werden, um eingehende Signale nur zu bestimmten Zeitpunkten zu übernehmen.

## Vergleich mit ähnlichen Bausteinen
- **E_D_FF** (ohne Adapter): Bietet direkte Ereignis- und Dateneingänge/-ausgänge, ist aber weniger abstrahiert. `AI_D_FF` hingegen kapselt die Signale in Adaptern, was die Komposition in höheren Hierarchien vereinfacht.
- **SR-Flipflop (S/R dominant):** Speichert Zustand über Set/Reset, während `AI_D_FF` nur bei Taktflanken übernimmt und keine Reset-Funktion besitzt.
- **Latch (pegelgesteuert):** Anders als ein Latch reagiert `AI_D_FF` nur auf Flanken, wodurch es besser für synchronisierte Systeme geeignet ist.

## Fazit
Der **AI_D_FF** ist ein kompakter, adapterbasierter D-Flipflop-Baustein, der einen Datenwert flankengesteuert speichert und ausgibt. Durch die Verwendung von unidirektionalen Adaptern fügt er sich nahtlos in moderne, modulare Automatisierungskonzepte ein und ermöglicht eine saubere Trennung von Daten- und Ereignissignalen. Seine Anwendung eignet sich vor allem für getaktete Abtast- und Zwischenspeicheraufgaben in IEC-61499-Systemen.
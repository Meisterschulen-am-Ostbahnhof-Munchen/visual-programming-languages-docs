# ALR_D_FF_HYS_TMIN


![ALR_D_FF_HYS_TMIN](./ALR_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALR_D_FF_HYS_TMIN** realisiert ein taktgesteuertes D‑Latch (Flipflop) mit einer einstellbaren Hysterese für die Datenübernahme und einer minimalen Zeitverzögerung zwischen aufeinanderfolgenden Ausgangsereignissen. Er verarbeitet einen analogen oder booleschen Wert über einen Adapter-Eingang und gibt den zwischengespeicherten Wert über einen Adapter-Ausgang aus. Die Hysterese verhindert ein ungewolltes Umschalten bei schwankenden Eingangswerten, während die Mindestzeit (Tmin) die Ereignisfrequenz am Ausgang begrenzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar                        |
|----------|-------|----------------------------------|
| INIT     | EInit | Initialisierungsanforderung (setzt Hysterese und Tmin) |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar                         |
|----------|-------|-----------------------------------|
| INITO    | EInit | Initialisierungsbestätigung       |

### **Daten-Eingänge**

| Name       | Typ   | Kommentar                                       |
|------------|-------|-------------------------------------------------|
| HYSTERESIS | LREAL | Hysterese-Band für die Datenübernahme           |
| Tmin       | TIME  | Mindestzeit zwischen zwei Ausgangsereignissen   |

### **Daten-Ausgänge**

Der FB besitzt keine eigenen Daten-Ausgänge. Der latched Wert wird über den Adapter-Ausgang `Q` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ (unidirektional) | Kommentar                          |
|----------|------|----------------------|------------------------------------|
| Socket   | I    | ALR                  | Eingangswert, der gelatcht werden soll |
| Plug     | Q    | ALR                  | Ausgangswert (latched)             |

## Funktionsweise

Der FB ist als zusammengesetzter Baustein realisiert, der intern einen FB vom Typ `E_D_FF_ANY_HYS_TMIN` (aus der Bibliothek `logiBUS::signalprocessing::hysteresis`) verwendet. Die Funktionsweise im Einzelnen:

1. **Initialisierung (INIT)**: Beim Ereignis `INIT` werden die Parameter `HYSTERESIS` und `Tmin` an den internen FB übergeben. Der interne FB wird initialisiert und bestätigt mit `INITO`.
2. **Datenübernahme**: Ein Ereignis am Adapter-Eingang `I.E1` triggert den Takt (`CLK`) des internen Flipflops. Gleichzeitig wird der Datenwert `I.D1` als neuer Eingang `D` übernommen.
3. **Hysterese**: Die Übernahme des Wertes erfolgt nur, wenn die Abweichung zum aktuell gelatchten Wert größer oder gleich der eingestellten Hysterese ist. Dies verhindert ständiges Umschalten bei kleinen Schwankungen.
4. **Mindestzeit (Tmin)**: Nach jedem ausgegebenen Ereignis (`EO`) wird eine Verzögerung von `Tmin` eingehalten, bevor ein weiteres Ausgangsereignis erzeugt werden kann. Ereignisse, die innerhalb dieser Sperrfrist eintreffen, werden ignoriert.
5. **Ausgabe**: Der gelatchte Wert wird über den Adapter-Ausgang `Q.D1` bereitgestellt, und ein Ereignis (`Q.E1`) signalisiert die Aktualisierung.

## Technische Besonderheiten

- **Hysterese**: Der Baustein arbeitet mit einem einstellbaren Hysterese-Band. Die tatsächliche Umsetzung (ob symmetrisch oder mit Schwellwerten) hängt vom internen FB ab. Üblich ist eine Schmitt-Trigger-Charakteristik.
- **Zeitgesteuerte Ausgabe**: `Tmin` begrenzt die maximale Ausgabefrequenz. Dies ist nützlich, um nachgeschaltete Komponenten zu entlasten oder eine minimale Signalverweildauer zu garantieren.
- **Adapter-Schnittstelle**: Die Verwendung von Adaptern (`ALR`) ermöglicht eine lose Kopplung zwischen Datenwert und Ereignis – ein Ereignis transportiert implizit den zugehörigen Datenwert.
- **Wiederverwendbarkeit**: Der FB ist aus einem standardisierten Hysterese-Flipflop aufgebaut und kann leicht an andere Datenformate angepasst werden.

## Zustandsübersicht

Da der FB aus mehreren internen Zuständen besteht (z. B. Warten auf Takt, Hysterese-Prüfung, Warten auf Tmin), wird hier eine vereinfachte Zustandsbeschreibung gegeben:

1. **Initialisiert** (nach INIT und INITO)
2. **Bereit** – wartet auf ein Ereignis am Eingang `I.E1`
3. **Hysterese-Prüfung** – vergleicht neuen Wert mit gelatchtem Wert
   - Bei Überschreitung: Übernahme des neuen Wertes, Übergang zu **Warten auf Tmin**
   - Sonst: zurück zu **Bereit** ohne Ausgabe
4. **Warten auf Tmin** – nach Ablauf der Mindestzeit wird das Ausgangsereignis `Q.E1` erzeugt und der gelatchte Wert auf `Q.D1` ausgegeben; danach zurück zu **Bereit**

## Anwendungsszenarien

- **Analoge Schaltschwellen**: Überwachung von Sensoren (z. B. Temperatur, Druck) mit einstellbarer Hysterese und minimaler Schaltpause, um Prellen oder Rauschen zu unterdrücken.
- **Digitale Signalaufbereitung**: Verarbeitung von Rechtecksignalen mit Rauschen, wobei die Hysterese Flanken stabilisiert und Tmin eine definierte Impulsdauer erzwingt.
- **Schrittmotorensteuerung**: Latch von Positionswerten mit Hysterese gegen mechanische Schwingungen, begleitet von zeitlicher Entprellung der Ausgabebefehle.
- **Sicherheitskritische Systeme**: Mindestzeit zwischen Ausgabeänderungen verhindert zu schnelle Zustandswechsel und schützt nachfolgende Aktoren.

## Vergleich mit ähnlichen Bausteinen

| Baustein                          | Eigenschaften                                                       | Unterschied zu ALR_D_FF_HYS_TMIN                          |
|-----------------------------------|---------------------------------------------------------------------|------------------------------------------------------------|
| Einfaches D‑Flipflop (D_FF)       | Keine Hysterese, keine Zeitsteuerung                                | Fehlende Signalstabilisierung und Frequenzbegrenzung       |
| Schmitt-Trigger (z. B. S_TRIG)    | Nur Hysterese, keine Zeitsteuerung, oft nur binär                   | Unterscheidet sich bei analogen Werten und erzwungenen Pausen |
| Flankengesteuertes Latch mit Totzeit | Zeitsteuerung (Totzeit) vorhanden, aber meist ohne Hysterese        | Kombination beider Effekte (Hysterese + Tmin)               |
| Filterbaustein (z. B. FILTER)     | Rauschunterdrückung z. B. als Tiefpass, keine diskrete Zustandsänderung | Explizites Latch mit Ereignisausgabe und einstellbarer Hysterese |

Der vorliegende Baustein vereint die Vorteile einer Hysterese mit einer minimalen Ereignisabstandsfunktion und ist damit besonders für raue industrielle Umgebungen geeignet.

## Fazit

Der **ALR_D_FF_HYS_TMIN** ist ein robuster, konfigurierbarer Funktionsblock für die zuverlässige Signalverarbeitung mit Hysterese und zeitlicher Entprellung. Er eignet sich für alle Anwendungen, bei denen ein weicher Schwellwert und eine Begrenzung der Ausgabe-Ereignisfrequenz erforderlich sind. Die Adapter-basierte Schnittstelle erleichtert die Integration in komplexe Steuerungsarchitekturen.
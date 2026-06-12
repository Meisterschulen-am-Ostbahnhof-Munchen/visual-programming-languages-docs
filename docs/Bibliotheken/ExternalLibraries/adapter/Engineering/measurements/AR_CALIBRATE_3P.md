# AR_CALIBRATE_3P


![AR_CALIBRATE_3P](./AR_CALIBRATE_3P.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_CALIBRATE_3P** ermöglicht eine 3‑Punkt‑Kalibrierung eines analogen Eingangssignals unter Verwendung von Adaptern. Er ist speziell für Joysticks ausgelegt, die einen Mittenversatz (Center‑Drift) aufweisen, und korrigiert diesen durch Linearisierung zwischen drei Referenzpunkten: Minimum, Mittelwert und Maximum. Die Kalibrierungspunkte werden gespeichert und können bei Bedarf neu eingestellt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| SET | Event | Setzt die Referenzwerte (MIN_REF, MID_REF, MAX_REF) für die Kalibrierungskennlinie. Löst keine Berechnung aus, sondern legt nur die Zielausgabewerte fest. |

### **Ereignis-Ausgänge**
Keine expliziten Ereignisausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über den Adapter **Y**.

### **Daten-Eingänge**
| Name | Datentyp | Vorgabewert | Kommentar |
|------|----------|-------------|-----------|
| MIN_REF | REAL | 0.0 | Zielwert für den kleinsten Eingangswert (Min). |
| MID_REF | REAL | 50.0 | Zielwert für den Mittelwert (Mid). |
| MAX_REF | REAL | 100.0 | Zielwert für den größten Eingangswert (Max). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – alle Ausgaben werden über die **Plugs** (Ausgangsadapter) bereitgestellt.

### **Adapter**
| Richtung | Name | Adaptertyp | Kommentar |
|----------|------|------------|-----------|
| **Plug** (Ausgang) | Y | `adapter::types::unidirectional::AR` | Kalibrierter Ausgabewert (Analogwert plus Ereignis). |
| **Plug** (Ausgang) | X_MIN | `adapter::types::bidirectional::AR2` | Gespeicherter Minimalwert (vom Rohwert). |
| **Plug** (Ausgang) | X_MID | `adapter::types::bidirectional::AR2` | Gespeicherter Mittelwert (vom Rohwert). |
| **Plug** (Ausgang) | X_MAX | `adapter::types::bidirectional::AR2` | Gespeicherter Maximalwert (vom Rohwert). |
| **Socket** (Eingang) | X | `adapter::types::unidirectional::AR` | Rohwert vom Sensor (Analogwert plus Ereignis). |
| **Socket** (Eingang) | C_MIN | `adapter::types::unidirectional::AX` | Ereignis zum Kalibrieren des Minimalpunkts (liest den aktuellen Rohwert). |
| **Socket** (Eingang) | C_MID | `adapter::types::unidirectional::AX` | Ereignis zum Kalibrieren des Mittelpunkts. |
| **Socket** (Eingang) | C_MAX | `adapter::types::unidirectional::AX` | Ereignis zum Kalibrieren des Maximalpunkts. |

## Funktionsweise
Die Kalibrierung basiert auf einer stückweisen linearen Interpolation zwischen drei gespeicherten Rohwerten (`X_MIN`, `X_MID`, `X_MAX`) und den zugehörigen Referenzwerten (`MIN_REF`, `MID_REF`, `MAX_REF`).

1. **Kalibrierung der Punkte:**  
   Ein Ereignis an einem der Kalibrierungseingänge (`C_MIN.E1`, `C_MID.E1`, `C_MAX.E1`) speichert den gerade anliegenden Rohwert (`X.D1`) in den entsprechenden gespeicherten Wert (`X_MIN.DO1`, `X_MID.DO1`, `X_MAX.DO1`). Voraussetzung ist, dass das mitgelieferte Data‑Signal (`C_MIN.D1` etc.) wahr ist.

2. **Berechnung des kalibrierten Werts:**  
   Sobald ein Ereignis vom Rohwert‑Adapter (`X.E1`) eintrifft, wird der Funktionsblock aktiv und führt den Algorithmus **REQ** aus. Dabei wird der Rohwert `X.D1` linear abgebildet:
   - Liegt der Rohwert unterhalb des gespeicherten Mittelwerts `X_MID.DI1`, wird der untere Zweig der Kennlinie verwendet:  
     `Y.D1 = MIN_REF + (X.D1 – X_MIN.DI1) * (MID_REF – MIN_REF) / (X_MID.DI1 – X_MIN.DI1)`  
     Falls die Intervalle ungültig sind (Division durch Null oder negative Spannweite), wird auf `MIN_REF` zurückgegriffen.
   - Liegt der Rohwert oberhalb oder gleich `X_MID.DI1`, wird der obere Zweig berechnet:  
     `Y.D1 = MID_REF + (X.D1 – X_MID.DI1) * (MAX_REF – MID_REF) / (X_MAX.DI1 – X_MID.DI1)`  
     Auch hier wird bei ungültigen Intervallen `MID_REF` ausgegeben.

3. **Begrenzung (Clipping):**  
   Der berechnete Ausgabewert wird auf das Intervall `[MIN_REF, MAX_REF]` begrenzt, um physikalisch sinnvolle Ergebnisse sicherzustellen.

4. **Ausgabe:**  
   Der kalibrierte Wert wird über den Adapter `Y` (Ereignis `Y.E1` und Data `Y.D1`) ausgegeben.

## Technische Besonderheiten
- **Bidirektionale Adapter für Kalibrierungspunkte:** Die gespeicherten Rohwerte (`X_MIN`, `X_MID`, `X_MAX`) sind bidirektionale Adapter vom Typ `AR2`. Sie können sowohl beschrieben (während der Kalibrierung) als auch gelesen (während der Berechnung) werden. Dadurch bleiben die Kalibrierungspunkte dauerhaft erhalten, solange die Verbindung zur übergeordneten Ressource besteht.
- **Ereignisgesteuerte Kalibrierung:** Die Kalibrierung der drei Punkte erfolgt nicht automatisch, sondern wird durch spezifische Ereignisse (`C_MIN`, `C_MID`, `C_MAX`) ausgelöst. Dies erlaubt eine zeitlich getrennte Aufnahme der Referenzpunkte.
- **Schutz vor ungültigen Intervallen:** Die Algorithmen prüfen, ob die Spannweiten der gespeicherten Rohwerte positiv sind. Falls nicht (z. B. bei noch nicht kalibriertem Zustand), werden sichere Standardwerte ausgegeben.
- **Keine Selbstkalibrierung:** Der FB speichert keine Historie – das System muss die Kalibrierungspunkte explizit setzen.

## Zustandsübersicht
| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Warte – kein Ereignis anliegend. Transitionen: Bei `SET` → IDLE (nur Referenzwerte setzen); bei `X_MIN.EI1`, `X_MID.EI1`, `X_MAX.EI1` → IDLE (keine Aktion); bei `C_MIN.E1[C_MIN.D1]` → CAL_MIN; bei `C_MID.E1[C_MID.D1]` → CAL_MID; bei `C_MAX.E1[C_MAX.D1]` → CAL_MAX; bei `X.E1` → REQ. |
| **REQ** | Berechnung des kalibrierten Ausgangswerts. Nach Ausführung sofort zurück zu IDLE. |
| **CAL_MIN** | Speichert den aktuellen Rohwert als Minimum (`X_MIN.DO1 := X.D1`). Geht automatisch nach IDLE. |
| **CAL_MID** | Speichert den aktuellen Rohwert als Mittelwert. Geht automatisch nach IDLE. |
| **CAL_MAX** | Speichert den aktuellen Rohwert als Maximum. Geht automatisch nach IDLE. |

**Übergangsbedingungen:**
- `X.E1` → Start der Berechnung
- `C_MIN.E1[C_MIN.D1]` → Kalibrierung des Minimalpunkts (nur wenn das Data‑Signal wahr ist)
- `C_MID.E1[C_MID.D1]` → Kalibrierung des Mittelpunkts
- `C_MAX.E1[C_MAX.D1]` → Kalibrierung des Maximalpunkts
- `SET`, `X_MIN.EI1`, `X_MID.EI1`, `X_MAX.EI1` → Keine Zustandsänderung (bleibt in IDLE)

## Anwendungsszenarien
- **Joystick‑Kalibrierung:** Ein Joystick mit analogem Ausgang (z. B. 0‑10 V) weist bauteilbedingte Abweichungen in der Mitte und an den Endanschlägen auf. Der Bediener fährt den Joystick an die drei Positionen (Min, Mitte, Max) und löst über Taster die Kalibrierungsereignisse aus. Danach liefert `Y` einen linearisierten, auf die gewünschten Zielwerte normierten Wert.
- **Analoges Potentiometer:** Ein Schleifpotentiometer mit Abnutzungserscheinungen kann durch 3‑Punkt‑Kalibrierung korrigiert werden.
- **Sensoren mit Offset und Skalierungsfehler:** Z. B. ein Drucksensor mit nichtlinearem Verhalten zwischen 0 %, 50 % und 100 % des Bereichs.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaft |
|----------|-------------|
| **AR_SCALE** | Einfache lineare Skalierung (2‑Punkt) – ohne Korrektur von Nichtlinearitäten in der Mitte. |
| **AR_CALIBRATE_2P** | Zwei‑Punkt‑Kalibrierung (Min, Max) – kann Mittenversatz nicht adressieren. |
| **AR_CALIBRATE_3P** (dieser Baustein) | Drei‑Punkt‑Kalibrierung mit separater Kalibrierung der Mitte – ideal für Joysticks mit Center‑Drift. |
| **Tabellenbasierte Korrektur** | Aufwändiger, erfordert viele Stützstellen; AR_CALIBRATE_3P ist einfacher und schneller. |

Der entscheidende Vorteil liegt in der expliziten Behandlung des Mittelpunkts, die bei vielen einfachen Skalierungen vernachlässigt wird.

## Fazit
`AR_CALIBRATE_3P` ist ein praktischer Funktionsblock für die präzise Korrektur von analogen Sensoren mit drei markanten Referenzpunkten. Durch die adapterbasierte Schnittstelle fügt er sich nahtlos in IEC‑61499‑Systeme ein und ermöglicht eine flexible und wiederverwendbare Kalibrierungslösung, insbesondere für Joysticks und ähnliche Eingabegeräte.
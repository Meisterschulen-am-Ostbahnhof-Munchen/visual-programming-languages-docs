# ASR_AX_SR_SYM


![ASR_AX_SR_SYM](./ASR_AX_SR_SYM.svg)

* * * * * * * * * *

## Einleitung  
Der Funktionsblock **ASR_AX_SR_SYM** realisiert ein ereignisgesteuertes, bistabiles Flipflop (SR-Flipflop) mit symmetrischem Startverhalten. Er ist als Basic-FB gemäß IEC 61499-1 (Annex A) implementiert und arbeitet ausschließlich über Adapter-Schnittstellen – ohne direkte Ereignis- oder Dateneingänge. Der Baustein eignet sich für Anwendungen, bei denen der initiale Zustand durch das erste eintreffende Ereignis bestimmt wird und keinem der beiden Eingänge eine Vorrangstellung eingeräumt ist.

## Schnittstellenstruktur

### Ereignis-Eingänge  
Der FB besitzt keine direkten Ereigniseingänge. Alle Ereignisse werden über den **Socket-Adapter `S_R`** (Typ `adapter::types::unidirectional::ASR`) empfangen. Dieser Adapter stellt die folgenden Ereignis-Eingänge bereit:  
- `S_R.SET` – Setz-Ereignis  
- `S_R.RESET` – Rücksetz-Ereignis

### Ereignis-Ausgänge  
Der FB besitzt keine direkten Ereignisausgänge. Ausgehende Ereignisse werden über den **Plug-Adapter `Q`** (Typ `adapter::types::unidirectional::AX`) gesendet. Dieser Adapter bietet den Ereignis-Ausgang:  
- `Q.E1` – Ausgangsereignis, ausgelöst bei Zustandsänderung

### Daten-Eingänge  
Keine direkten Dateneingänge.

### Daten-Ausgänge  
Der Ausgangswert wird über den Plug-Adapter `Q` bereitgestellt:  
- `Q.D1` (BOOL) – aktueller Zustand des Flipflops (`TRUE` = gesetzt, `FALSE` = rückgesetzt)

### Adapter  

| Bezeichnung | Typ                                    | Richtung | Beschreibung                       |
|-------------|----------------------------------------|----------|------------------------------------|
| `S_R`       | `adapter::types::unidirectional::ASR`  | Socket   | Set-/Reset-Ereignisse (Eingang)    |
| `Q`         | `adapter::types::unidirectional::AX`   | Plug     | Zustandsausgabe (Ereignis + Daten) |

## Funktionsweise  
Der Baustein startet nach der Initialisierung im Zustand **START**. In diesem Zustand wartet er auf das erste eintreffende Ereignis an `S_R.SET` oder `S_R.RESET`. Je nachdem, welches Ereignis zuerst eintrifft, wechselt er in den Zustand **SET** oder **RESET**:

- **SET-Zustand**:  
  Der Datenausgang `Q.D1` wird auf `TRUE` gesetzt, das Ereignis `Q.E1` wird ausgelöst.  
  Bei einem späteren `S_R.RESET` erfolgt der Übergang in den Zustand RESET.

- **RESET-Zustand**:  
  Der Datenausgang `Q.D1` wird auf `FALSE` gesetzt, das Ereignis `Q.E1` wird ausgelöst.  
  Bei einem späteren `S_R.SET` erfolgt der Übergang in den Zustand SET.

Der Baustein bleibt nach dem ersten Übergang in einem der beiden stabilen Zustände, bis das jeweils komplementäre Ereignis eintrifft. Es gibt keine Vorrangstellung von SET oder RESET – das erste Ereignis beim Start bestimmt den Anfangszustand.

## Technische Besonderheiten  
- **Symmetrisches Startverhalten**: Im Gegensatz zu üblichen SR-Flipflops hat keiner der Eingänge Priorität. Der Anfangszustand wird durch das zeitlich erste Ereignis bestimmt.  
- **Reine Adapter-Schnittstelle**: Sowohl Ereignisse als auch Daten werden über IEC 61499-Adapter ausgetauscht, nicht über direkte Ein-/Ausgangsports. Dies vereinfacht die Wiederverwendung in komplexen, adapterbasierten Systemen.  
- **Keine expliziten Ereignis-E/A**: Der FB verzichtet auf eigene EVENT-Eingänge/-Ausgänge und nutzt stattdessen die integrierten Ereignisports der Adapter.  
- **Compact-ST-Implementierung**: Die beiden Algorithmen `SET` und `RESET` setzen lediglich den Datenausgang und lösen das Ausgangsereignis aus.

## Zustandsübersicht  

*(Hinweis: Ein grafisches Zustandsdiagramm kann aus dem ECC‑XML extrahiert werden, ist hier jedoch nicht als Bild eingebettet.)*

| Zustand | Beschreibung                      | Aktion                | Ausgang                                         |
|---------|-----------------------------------|-----------------------|-------------------------------------------------|
| START   | Initialer Wartezustand            | –                     | keine Ausgabe                                   |
| SET     | Gespeicherter Zustand „gesetzt“   | `Q.D1 := TRUE`        | Auslösen von `Q.E1`                             |
| RESET   | Gespeicherter Zustand „rückgesetzt“| `Q.D1 := FALSE`       | Auslösen von `Q.E1`                             |

**Übergänge:**  
- START → SET : wenn `S_R.SET` eintrifft  
- START → RESET : wenn `S_R.RESET` eintrifft  
- SET → RESET : wenn `S_R.RESET` eintrifft (nach erstem Set)  
- RESET → SET : wenn `S_R.SET` eintrifft (nach erstem Reset)

## Anwendungsszenarien  
- **Binäre Zustandspeicher**: Speichern eines Ein-/Aus-Zustands, der durch zwei separate Ereignisse gesteuert wird (z. B. „Start“ und „Stopp“).  
- **Ansteuerung von Aktoren mit Setz- und Rücksetzeingang**: Verwendung in Steuerungen, bei denen ein Ausgang symmetrisch gesetzt und rückgesetzt werden soll, ohne Priorisierung.  
- **Initialisierung durch das erste Ereignis**: Systeme, bei denen der Startzustand nicht vordefiniert ist, sondern durch den ersten Befehl (Setzen oder Rücksetzen) bestimmt wird.

## Vergleich mit ähnlichen Bausteinen  
- **Standard‑SR‑Flipflop (z. B. `SR` klassisch)**: Häufig ist ein Eingang dominant (z. B. Reset hat Vorrang). Der `ASR_AX_SR_SYM` behandelt beide Eingänge gleichberechtigt – beim Start entscheidet das zeitlich erste Ereignis.  
- **RS‑Flipflop mit priorisiertem Set**: Andere Implementierungen setzen den Set‑Eingang stärker.  

Der vorliegende Baustein zeichnet sich durch seine symmetrische Behandlung beider Ereignisse und die ausschließliche Adapter-Schnittstelle aus, was ihn flexibel in adapterbasierten Bibliotheken macht.

## Fazit  
Der Funktionsblock `ASR_AX_SR_SYM` bietet ein zuverlässiges, ereignisgesteuertes SR-Flipflop mit symmetrischem Startverhalten. Durch seine Adapter-Schnittstellen fügt er sich nahtlos in IEC-61499-Systeme ein und eignet sich besonders für Anwendungen, die eine gleichberechtigte Setz‑/Rücksetzsteuerung ohne Vorrang erfordern. Die einfache Zustandslogik und die geringe Anzahl an Algorithmen machen ihn effizient und leicht verständlich.
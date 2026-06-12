# AX_T_FF_SR_SYM_STORE


![AX_T_FF_SR_SYM_STORE](./AX_T_FF_SR_SYM_STORE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_T_FF_SR_SYM_STORE` realisiert ein ereignisgesteuertes, bistabiles Kippglied (Flipflop) mit Setz- (S), Rücksetz- (R) und Toggle-Funktion (CLK). Seine Besonderheit ist das symmetrische Startverhalten: Über einen speziellen Adapter (`Q_INIT`) kann der Anfangszustand beim Systemstart definiert und gespeichert werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar                                   |
|------|-------|---------------------------------------------|
| S    | Event | Setzt den Ausgang `Q` auf TRUE              |
| R    | Event | Setzt den Ausgang `Q` auf FALSE             |
| CLK  | Event | Toggelt den Ausgang `Q` (TRUE ↔ FALSE)      |

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Ausgangsdaten werden ausschließlich über die Adapter-Schnittstellen bereitgestellt.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Initialwert und Zustand werden über Adapter eingelesen bzw. ausgegeben.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der aktuelle Zustand wird über die Adapter verfügbar gemacht.

### **Adapter**
| Name    | Typ                              | Kommentar                                   |
|---------|----------------------------------|---------------------------------------------|
| Q       | adapter::types::unidirectional::AX | Liefert den aktuellen Zustand des Flipflops (einadriger boolescher Wert) |
| Q_INIT  | adapter::types::bidirectional::AX2 | Bidirektionale Schnittstelle für den Startwert von `Q` bei INIT (beinhaltet drei Ein-/Ausgänge: z.B. DI1/DO1, EI1/EO1) |

## Funktionsweise
Der Baustein arbeitet als ein SR-Flipflop (Set-Reset) mit zusätzlicher Toggle-Funktion. Der Ablauf gliedert sich in Initialisierung und Betrieb:

1. **Initialisierung (START → Init)**  
   Nach dem Systemstart befindet sich der FB im Zustand START. Sobald am Adapter `Q_INIT` das Ereignis `EI1` eintrifft, wechselt er in den Zustand Init. Dort wird der über `Q_INIT.DI1` bereitgestellte Initialwert ausgelesen.  
   - Ist der Initialwert FALSE, wird anschließend der Zustand RESET eingenommen.  
   - Ist der Initialwert TRUE, wird der Zustand SET eingenommen.  
   In beiden Fällen wird der entsprechende Ausgang `Q.D1` und der Ausgang `Q_INIT.DO1` auf den Initialwert gesetzt.

2. **Betrieb (SET ↔ RESET)**  
   Ausgehend von SET oder RESET wird bei jedem Ereignis an den Eingängen S, R oder CLK umgeschaltet:  
   - **S** → wechselt in SET (setzt Q = TRUE)  
   - **R** → wechselt in RESET (setzt Q = FALSE)  
   - **CLK** → toggelt den Zustand (von SET nach RESET oder umgekehrt)  
   Bei jeder Zustandsänderung werden die Ausgangsdaten über die Adapter aktualisiert und das Ereignis `Q.E1` sowie `Q_INIT.EO1` ausgegeben.

## Technische Besonderheiten
- **Adapter-basierte Ein-/Ausgabe**  
  Statt klassischer DataInputs/DataOutputs verwendet der Baustein Adapter-Schnittstellen. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen oder Systemkomponenten, die ebenfalls das Adapterprotokoll unterstützen.

- **Symmetrisches Startverhalten**  
  Über den bidirektionalen Adapter `Q_INIT` kann der Anfangszustand sowohl extern vorgegeben als auch nach der Initialisierung ausgelesen werden. Dadurch wird ein deterministisches Wiederanlaufverhalten sichergestellt – besonders wichtig bei sicherheitskritischen oder zustandsbehafteten Anwendungen.

- **Toggle-Funktion (CLK)**  
  Neben den klassischen Setz- und Rücksetzereignissen erlaubt der Takt-Eingang CLK das einfache Umschalten des Ausgangs, ohne dass hierfür ein separates Set/Reset-Signal benötigt wird.

- **Keine Daten-Ein-/Ausgänge**  
  Diese funktionale Reduktion vereinfacht die Schnittstelle und vermeidet Verwechslungen mit den Adaptern.

## Zustandsübersicht
| Zustand | Beschreibung                             | Ausgabe bei Ereignis                          |
|---------|------------------------------------------|-----------------------------------------------|
| START   | Initialer Wartezustand                   | Wartet auf Initialisierungsereignis über Q_INIT.EI1 |
| Init    | Initialisierung                          | Liest Q_INIT.DI1, setzt Q und Q_INIT.DO1 entsprechend |
| SET     | Ausgang Q = TRUE                         | Verarbeitet S, R, CLK (siehe Übergänge)       |
| RESET   | Ausgang Q = FALSE                        | Verarbeitet S, R, CLK (siehe Übergänge)       |

**Zustandsübergänge (vereinfacht)**
- START → Init (Ereignis Q_INIT.EI1)
- Init → SET (falls Q_INIT.DI1 = TRUE)
- Init → RESET (falls Q_INIT.DI1 = FALSE)
- SET → RESET (bei Ereignis R oder CLK)
- RESET → SET (bei Ereignis S oder CLK)

## Anwendungsszenarien
- **Speicherung von Maschinenzuständen**  
  In Fertigungsanlagen kann dieser Baustein den aktuellen Betriebsmodus (z.B. „Ein“ oder „Aus“) speichern und beim Neustart wiederherstellen.

- **Initialisierung von Steuerungssequenzen**  
  Szenarien, bei denen ein definierter Startwert erforderlich ist (z.B. Ventilstellung zu Beginn einer Charge), profitieren vom symmetrischen INIT-Verhalten.

- **Ereignisgesteuerte Toggle-Funktionen**  
  Zum Beispiel das Umschalten einer Signalleuchte bei jedem Tastendruck, ohne dass separate Ein- und Aus-Befehle nötig sind.

## Vergleich mit ähnlichen Bausteinen
- **Standard E_SR (E_R-SET)**  
  Einfaches Set-Reset-Flipflop ohne Toggle und ohne symmetrische Startinitialisierung. Der Anfangszustand ist meist undefiniert oder muss extern gesetzt werden.

- **E_RS**  
  Bietet Priorisierung von Reset, aber ebenfalls keine Toggle- oder INIT-Funktion.

- **Toggle-Bausteine (z.B. E_Toggle)**  
  Reine Toggle-FBs besitzen meist nur einen Takt-Eingang und keinen bidirektionalen Adapter für die Initialisierung. Der AX_T_FF_SR_SYM_STORE vereint alle drei Funktionen in einem Baustein.

- **Adapter-basierte FBs**  
  Wenige FBs in der 4diac-Bibliothek verwenden Adapter für die Zustandsausgabe. Dieses Design ermöglicht eine saubere Trennung von Ereignis- und Datenpfaden und erleichtert die Wiederverwendung in komplexen Systemen.

## Fazit
Der `AX_T_FF_SR_SYM_STORE` ist ein leistungsfähiger und flexibler Funktionsblock für zustandsbehaftete Steuerungsaufgaben. Seine Kombination aus Set, Reset und Toggle, gepaart mit dem symmetrischen Startverhalten über Adapter, macht ihn ideal für Anwendungen, die ein definiertes Wiederanlaufverhalten erfordern. Durch die Verwendung von Adaptern fügt er sich nahtlos in modulare und verteilte Automatisierungssysteme ein.
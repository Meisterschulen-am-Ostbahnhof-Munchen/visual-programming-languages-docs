# AIS_D_FF_TMIN


![AIS_D_FF_TMIN](./AIS_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AIS_D_FF_TMIN** realisiert ein datenabhängiges Flip-Flop (D‑Flip-Flop) mit einer minimalen Zwischenzeit (*minimum inter‑disposal time*) zwischen zwei aufeinanderfolgenden Ausgabeereignissen (EO). Er dient dazu, einen eingehenden Datenwert über einen AIS‑Adapter zu latchen und nur dann auszugeben, wenn die durch den Parameter `Tmin` festgelegte Mindestzeit seit dem letzten EO verstrichen ist. Dadurch werden zu schnelle Signalwechsel unterdrückt und eine definierte Signalverzögerung sichergestellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ  | Kommentar |
|----------|------|-----------|
| `INIT`   | EInit | Initialisierungsanforderung (mit `Tmin`) |

### **Ereignis-Ausgänge**
| Ereignis | Typ  | Kommentar |
|----------|------|-----------|
| `INITO`  | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**
| Variable | Typ  | Kommentar |
|----------|------|-----------|
| `Tmin`   | TIME | Mindestzeitabstand zwischen zwei EO‑Ereignissen |

### **Daten-Ausgänge**
Der FB besitzt keine eigenen Datenausgänge. Die Ausgabe erfolgt ausschließlich über den Adapter‑Plug (siehe unten).

### **Adapter**
| Richtung | Bezeichnung | Adaptertyp | Kommentar |
|----------|-------------|------------|-----------|
| **Plug** (Ausgang) | `Q` | `adapter::types::unidirectional::AIS` | Gelatchter Ausgabewert |
| **Socket** (Eingang) | `I` | `adapter::types::unidirectional::AIS` | Zu latchnder Eingabewert |

Der Adapter `AIS` ist unidirektional und liefert über die Ereignis‑/Datenschnittstellen `E1`/`D1` die eigentlichen Signale.

## Funktionsweise
Der Baustein besteht intern aus einem geschachtelten FB `E_D_FF_ANY_TMIN` (aus der IEC‑61499‑Bibliothek).  
Die Verarbeitung läuft wie folgt ab:

1. **Initialisierung**: Beim Ereignis `INIT` wird der Parameter `Tmin` an den internen FB weitergeleitet und dieser initialisiert. Anschließend wird `INITO` ausgelöst.
2. **Latch‑Vorgang**: Ein am **Socket `I`** eintreffendes Ereignis `E1` (verbunden mit dem internen `CLK`) übernimmt den gleichzeitig anliegenden Datenwert `D1` (verbunden mit `D`) in das Flip‑Flop.
3. **Minimale Verzögerung**: Der interne FB prüft, ob seit dem letzten Ausgangsereignis (`EO`) mindestens die Zeit `Tmin` vergangen ist.
   - Ist die Bedingung erfüllt, wird das gelatchte Datum über den **Plug `Q`** ausgegeben (Ereignis `E1` und Datenwert `D1`).
   - Andernfalls wird der Wert zurückgehalten, bis die geforderte Wartezeit abgelaufen ist.

Somit wird sichergestellt, dass Ausgabeereignisse nicht schneller als durch `Tmin` vorgegeben erfolgen.

## Technische Besonderheiten
- **Adaptor‑basierte Ein‑/Ausgabe**: Die Signale werden nicht als separate Ein‑/Ausgangsvariablen, sondern über standardisierte unidirektionale AIS‑Adapter geführt. Dies ermöglicht eine flexible Verschaltung mit anderen Bausteinen oder Subsystemen.
- **Einhaltung einer minimalen Zwischenzeit**: Die Verzögerung verhindert „Rauschen“ oder zu schnelle Signalwechsel, die in zeitkritischen Systemen zu Fehlfunktionen führen können.
- **Interner IEC‑61499‑Standard‑FB**: Die Implementierung nutzt den bibliothekseigenen `E_D_FF_ANY_TMIN`, was eine hohe Zuverlässigkeit und Wiederverwendbarkeit gewährleistet.

## Zustandsübersicht
Der FB selbst besitzt keine explizit modellierten Zustände in der XML‑Definition. Das Verhalten wird vollständig durch den internen FB `E_D_FF_ANY_TMIN` bestimmt. Dieser durchläuft typischerweise folgende Phasen (vereinfacht):

- **Idle**: Warten auf ein Taktereignis am Eingang `I.E1`.
- **Sampling**: Beim Taktereignis wird der aktuelle Datenwert `I.D1` übernommen.
- **Verzögerung**: Nach der Übernahme wird die seit dem letzten `EO` verstrichene Zeit mit `Tmin` verglichen. Bei Unterschreitung wird in einen Wartezustand gewechselt.
- **Ausgabe**: Nach Ablauf der Mindestzeit wird das gelatchte Datum über `Q.E1` und `Q.D1` ausgegeben.

## Anwendungsszenarien
- **Signalglättung**: Unterdrückung von Prellern oder kurzen Impulsen an digitalen Eingängen.
- **Zyklussteuerung**: Sicherstellung, dass ein Ausgangssignal nur in einem definierten Mindestabakt (z. B. alle 100 ms) aktualisiert wird.
- **Schnittstellen‑Pufferung**: Puffern von Werten zwischen unterschiedlich schnellen Systemkomponenten, wobei eine minimale Aktualisierungsrate eingehalten werden muss.
- **Automatisierungstechnik**: Steuerung von Aktoren, die mechanische Totzeiten oder Mindestschaltintervalle erfordern.

## Vergleich mit ähnlichen Bausteinen
- **Einfaches D‑Flip‑Flop (ohne Zeitsteuerung)**: Ein Standard‑D‑Flip‑Flop gibt den gelatchten Wert sofort mit dem nächsten Taktereignis aus – ohne Verzögerungsbegrenzung. `AIS_D_FF_TMIN` fügt die zusätzliche Zeitbedingung hinzu.
- **Monostabile Kippstufe**: Ein monostabiler Baustein erzeugt einen Impuls fester Dauer; der hier beschriebene FB hält dagegen keine Impulsdauer, sondern einen Mindestabstand zwischen Ausgaben ein.
- **IEC‑61499 `E_D_FF_ANY`**: Ist die Basis ohne Zeitbeschränkung. `E_D_FF_ANY_TMIN` erweitert diese Variante um den `Tmin`‑Parameter.

## Fazit
Der `AIS_D_FF_TMIN` bietet eine robuste Möglichkeit, digitale Signale mit einer einstellbaren minimalen Ausgabezeitverzögerung zu latchen. Durch die Verwendung von AIS‑Adaptern und internen IEC‑61499‑Standard‑Bausteinen ist er sowohl flexibel einsetzbar als auch zuverlässig. Er eignet sich besonders für Automatisierungsaufgaben, bei denen schnelle Signalwechsel unterdrückt oder definierte Mindestpausen zwischen Ausgabeereignissen eingehalten werden müssen.
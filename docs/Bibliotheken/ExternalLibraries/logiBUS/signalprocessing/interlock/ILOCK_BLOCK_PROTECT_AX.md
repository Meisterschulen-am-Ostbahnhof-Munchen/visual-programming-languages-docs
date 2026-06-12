# ILOCK_BLOCK_PROTECT_AX


![ILOCK_BLOCK_PROTECT_AX](./ILOCK_BLOCK_PROTECT_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ILOCK_BLOCK_PROTECT_AX` realisiert eine priorisierte Verriegelung (Interlock) für zwei gegenläufige Richtungen (UP/DOWN) unter Berücksichtigung einer konfigurierbaren Schutz-Totzeit. Der Baustein ist als Adapter-Version ausgeführt, d. h. die Ein- und Ausgänge werden über IEC 61499-Adapter bereitgestellt. Ziel ist die sichere Steuerung von Aktoren, bei denen nur eine Richtung gleichzeitig aktiv sein darf, beispielsweise bei Hebe- oder Schwenkbewegungen. Der erste aktivierte Eingang erhält den Vorrang; ein Wechsel der Richtung erfolgt erst nach Ablauf der Schutzzeit und einer erneuten Bewertung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Mitgeführte Daten | Beschreibung |
| :--- | :--- | :--- | :--- |
| `UPDATE` | Event | `DT_PROTECT` | Ereignis zum dynamischen Aktualisieren der Schutzzeit `DT_PROTECT`. |

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenständigen Ereignis-Ausgänge. Ereignisse werden über die als *Plugs* ausgeführten Adapter `UP_OUT`, `DOWN_OUT` und `timeOut` bereitgestellt.

| Adapter-Ausgang | Ereignis | Beschreibung |
| :--- | :--- | :--- |
| `UP_OUT` | `E1` | Wird ausgelöst, wenn der UP-Zustand aktiv ist oder der UP_STOP-Zustand erreicht wird. |
| `DOWN_OUT` | `E1` | Wird ausgelöst, wenn der DOWN-Zustand aktiv ist oder der DOWN_STOP-Zustand erreicht wird. |
| `timeOut` | `TimeOut` | Wird ausgelöst, wenn die eingestellte Schutzzeit abgelaufen ist (vom Adapter selbst generiert). |

### **Daten-Eingänge**

| Name | Typ | Initialwert | Beschreibung |
| :--- | :--- | :--- | :--- |
| `DT_PROTECT` | TIME | `T#50ms` | Schutzzeit, die nach einer Deaktivierung eines Eingangs verstreicht, bevor eine erneute Bewertung der Eingänge erfolgt. |

### **Daten-Ausgänge**

Der FB besitzt keine eigenständigen Daten-Ausgänge. Ausgangsdaten werden über die Adapter `UP_OUT`, `DOWN_OUT` und `timeOut` bereitgestellt.

| Adapter-Ausgang | Daten | Beschreibung |
| :--- | :--- | :--- |
| `UP_OUT` | `D1` (BOOL) | Signalisiert den aktiven UP-Zustand (`TRUE`) oder inaktiven UP-Zustand (`FALSE`). |
| `DOWN_OUT` | `D1` (BOOL) | Signalisiert den aktiven DOWN-Zustand (`TRUE`) oder inaktiven DOWN-Zustand (`FALSE`). |
| `timeOut` | `DT` (TIME) | Wird vom Algorithmus auf den Wert von `DT_PROTECT` gesetzt und bestimmt die Timer-Dauer. |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| `adapter::types::unidirectional::AX` | `UP_IN` | Socket | Eingang für die UP-Richtung. Das Event `E1` (steigende Flanke) aktiviert die Verarbeitung; `D1` (BOOL) gibt den gewünschten Zustand vor. |
| `adapter::types::unidirectional::AX` | `DOWN_IN` | Socket | Eingang für die DOWN-Richtung. Analog zu `UP_IN`. |
| `adapter::types::unidirectional::AX` | `UP_OUT` | Plug | Ausgang für die UP-Richtung. Stellt Ereignis und Daten für die angeschlossene Logik bereit. |
| `adapter::types::unidirectional::AX` | `DOWN_OUT` | Plug | Ausgang für die DOWN-Richtung. Stellt Ereignis und Daten bereit. |
| `iec61499::events::ATimeOut` | `timeOut` | Plug | Adapter für einen Timer. Der FB setzt die Zeitdauer (`DT`) und startet den Timer über das Ereignis `START`. Das Ereignis `TimeOut` signalisiert den Ablauf. |

## Funktionsweise

Der Baustein arbeitet als zustandsgesteuerte Verriegelung mit zwei Prioritätseingängen. Die grundsätzliche Funktionsweise:

1. **Initialzustand** (`STOP`): Keine Richtung ist aktiv. Ein eingehendes Ereignis an `UP_IN.E1` oder `DOWN_IN.E1` wird nur dann verarbeitet, wenn das zugehörige Datensignal `D1` den Wert `TRUE` hat. Der erste Eingang, der diese Bedingung erfüllt, wechselt in den entsprechenden Zustand (`UP` oder `DOWN`). Sind beide gleichzeitig `TRUE`, wird keiner akzeptiert – der Baustein bleibt im `STOP`.

2. **Aktiver Zustand** (`UP` oder `DOWN`): Der Ausgangsadapter (`UP_OUT` oder `DOWN_OUT`) signalisiert die aktive Richtung über `D1 = TRUE` und löst das Ereignis `E1` aus. Die Schutzzeit wird im Timer gespeichert, jedoch aktiv noch nicht gestartet.

3. **Deaktivierung und Schutzzeit**: Wenn der aktive Eingang sein Datensignal auf `FALSE` (oder das Ereignis ohne `TRUE`) zurücksetzt, wechselt der FB in den entsprechenden Stop-Zustand (`UP_STOP` oder `DOWN_STOP`). Dabei wird der Ausgang auf `FALSE` gesetzt und der Timer über das Ereignis `timeOut.START` gestartet. Nach Ablauf der eingestellten Schutzzeit (`timeOut.TimeOut`) wechselt der FB in den Evaluierungszustand (`EVAL`).

4. **Evaluierung** (`EVAL`): Im Evaluierungszustand werden die aktuellen Datensignale beider Eingänge ausgewertet:
   - Nur `UP_IN.D1 = TRUE` → Wechsel zu `UP`
   - Nur `DOWN_IN.D1 = TRUE` → Wechsel zu `DOWN`
   - Keines oder beide `TRUE` → Wechsel zurück zu `STOP`

5. **Dynamische Aktualisierung**: Das Ereignis `UPDATE` erlaubt es, während des Betriebs die Schutzzeit `DT_PROTECT` zu ändern. Die aktualisierte Zeit wird bei nächster Verwendung des Timers wirksam (der Timer wird nur in den Stop-Zuständen gestartet). Das Ereignis kann in jedem Zustand empfangen werden, ohne den aktuellen Steuerungszustand zu verlassen.

## Technische Besonderheiten

- **Adapter-Schnittstelle**: Der gesamte Datenaustausch erfolgt über Adapter. Dadurch wird eine saubere Trennung zwischen Steuerungslogik und Peripherie erreicht, die Wiederverwendbarkeit erhöht und die Kapselung verbessert.
- **Dynamische Schutzzeit**: Über das `UPDATE`-Ereignis kann die Totzeit zur Laufzeit verändert werden, ohne den Baustein neu zu starten. Dies ist besonders in Applikationen mit variablen Schaltzeiten (z. B. temperaturabhängige Verzögerungen) nützlich.
- **Totzeit-Prinzip**: Der FB geht nach Deaktivierung eines Eingangs nicht sofort in den anderen Zustand, sondern erzwingt eine minimale Verzögerung (`DT_PROTECT`). Dies verhindert Prellen oder ungewollte schnelle Umschaltungen.
- **Priorisierung nach erstem Aktiv**: Die Logik reagiert nur auf das erste `TRUE`-Signal eines Eingangsereignisses. Gleichzeitige Aktivierung beider Eingänge führt zu keiner Richtungsänderung.
- **Selbsthaltung ohne externes Ereignis**: Solange ein aktiver Eingang sein `D1` auf `TRUE` hält, bleibt der zugehörige Ausgangszustand erhalten, auch ohne weitere Ereignisse.

## Zustandsübersicht

| Zustand | Beschreibung | Aktivitäten |
| :--- | :--- | :--- |
| `STOP` | Initial- und Ruhezustand. Keine Richtung aktiv. | – |
| `UP` | UP-Richtung aktiv. | Algorithmus `UP`: setzt `UP_OUT.D1 = TRUE`, `DOWN_OUT.D1 = FALSE`, überträgt `DT_PROTECT` an `timeOut.DT` und sendet `UP_OUT.E1`. |
| `DOWN` | DOWN-Richtung aktiv. | Algorithmus `DOWN`: setzt `DOWN_OUT.D1 = TRUE`, `UP_OUT.D1 = FALSE`, überträgt `DT_PROTECT` an `timeOut.DT` und sendet `DOWN_OUT.E1`. |
| `UP_STOP` | Wartezeit nach Deaktivierung von UP. | Algorithmus `STOP`: setzt beide Ausgänge auf `FALSE`, überträgt `DT_PROTECT` an `timeOut.DT` und startet den Timer mit `timeOut.START`. |
| `DOWN_STOP` | Wartezeit nach Deaktivierung von DOWN. | Algorithmus `STOP` (analog zu `UP_STOP`). |
| `EVAL` | Evaluierung nach Ablauf der Schutzzeit. | Kein Algorithmus; die Transitionen entscheiden über den nächsten Zustand basierend auf den aktuellen Eingangsdaten. |

**Transitionen (vereinfacht):**

- `STOP → UP` wenn `UP_IN.E1` und `UP_IN.D1 = TRUE`
- `STOP → DOWN` wenn `DOWN_IN.E1` und `DOWN_IN.D1 = TRUE`
- `UP → UP_STOP` wenn `UP_IN.E1` und `UP_IN.D1 = FALSE`
- `DOWN → DOWN_STOP` wenn `DOWN_IN.E1` und `DOWN_IN.D1 = FALSE`
- `UP_STOP → EVAL` wenn `timeOut.TimeOut`
- `DOWN_STOP → EVAL` wenn `timeOut.TimeOut`
- `EVAL → UP` wenn `UP_IN.D1 = TRUE` und `DOWN_IN.D1 = FALSE`
- `EVAL → DOWN` wenn `DOWN_IN.D1 = TRUE` und `UP_IN.D1 = FALSE`
- `EVAL → STOP` wenn beide `FALSE` oder beide `TRUE`
- In jedem Zustand kann das Ereignis `UPDATE` zum selben Zustand zurückführen (dient nur der Aktualisierung von `DT_PROTECT`).

## Anwendungsszenarien

- **Hebebühnensteuerung**: Verriegelung von Heben und Senken; nach Loslassen des Hebebefehls wird eine Totzeit von z. B. 100 ms eingehalten, bevor ein Senken möglich ist.
- **Ventilsteuerung**: Umschaltung zwischen zwei Medien (z. B. Heizen/Kühlen) mit einer Schutzzeit, um Druckstöße zu vermeiden.
- **Roboterachsen**: Vermeidung von Kollisionen durch gleichzeitige Ansteuerung gegenläufiger Bewegungen.
- **Türsteuerung**: Öffnen/Schließen mit Verzögerung beim Richtungswechsel zum Schutz von Endanschlägen.

## Vergleich mit ähnlichen Bausteinen

| Baustein / Eigenschaft | `ILOCK_BLOCK_PROTECT_AX` | Einfacher Interlock (ohne Totzeit) | Interlock mit fester Totzeit |
| :--- | :--- | :--- | :--- |
| Totzeit | Dynamisch konfigurierbar über `UPDATE` | Keine | Fest (meist im Baustein verdrahtet) |
| Schnittstelle | Adapter (AX), lose Kopplung | Meist direkte Ein-/Ausgänge | Direkte Ein-/Ausgänge |
| Priorität | Erster aktiver Eingang | Oft festgelegte Priorität | Unterscheidet sich |
| Evaluierung nach Totzeit | Ja, mit klarer Zustandsmaschine | Nein | Teilweise |
| Flexibilität | Hoch (Laufzeitänderung) | Gering | Mittel |

Der `ILOCK_BLOCK_PROTECT_AX` bietet eine besonders flexible Lösung durch die Adapter-Schnittstelle und die dynamisch änderbare Totzeit. Er ist ideal für modulare, wiederverwendbare Steuerungsprojekte nach IEC 61499.

## Fazit

Der Funktionsblock `ILOCK_BLOCK_PROTECT_AX` ist ein robuster, zustandsgesteuerter Verriegelungsbaustein für zwei gegenläufige Richtungen. Die Kombination aus Priorisierung des ersten aktiven Eingangs, einer konfigurierbaren Schutz-Totzeit und der vollständigen Adapter-Schnittstelle macht ihn zu einer hervorragenden Wahl für sichere und flexible Steuerungsaufgaben in der Automatisierungstechnik. Die dynamische Anpassung der Totzeit über das `UPDATE`-Ereignis erhöht die Anpassungsfähigkeit an wechselnde Prozessbedingungen. Durch die klare Zustandsmaschine und die Berücksichtigung der IEC 61499-Standards ist der Baustein sowohl in einfachen als auch in komplexen verteilten Systemen einsetzbar.
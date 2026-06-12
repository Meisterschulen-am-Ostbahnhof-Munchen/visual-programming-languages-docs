# ILOCK_SWITCH_PROTECT_AX


![ILOCK_SWITCH_PROTECT_AX](./ILOCK_SWITCH_PROTECT_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ILOCK_SWITCH_PROTECT_AX` dient zur verriegelten Umschaltung zwischen zwei Eingangskanälen (UP/DOWN) mit einer einstellbaren Schutz-Totzeit. Er priorisiert den zuletzt aktiven Eingang und verhindert durch die Totzeit ein unkontrolliertes Hin- und Herschalten (Prellen) bei gleichzeitigen oder schnell wechselnden Anforderungen. Die Schnittstelle erfolgt über standardisierte unidirektionale Adapter (Typ `AX`) sowie einen Timer-Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `UPDATE` | Parametrierungsereignis; übernimmt den aktuellen Wert von `DT_PROTECT` in den Timer. |

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge. Die Ausgabe erfolgt implizit über die Adapter:

- `UP_OUT.E1` – Ereignisausgang des Up-Adapters
- `DOWN_OUT.E1` – Ereignisausgang des Down-Adapters
- `timeOut.TimeOut` – Ereignis des Timer-Adapters (interne Verwendung)

### **Daten-Eingänge**

| Name | Typ | Initialwert | Beschreibung |
|------|-----|-------------|--------------|
| `DT_PROTECT` | `TIME` | `T#50ms` | Schutz-Totzeit, die nach einem Zustandswechsel aktiviert wird. |

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Die Zustandsausgabe erfolgt über die Adapter:

- `UP_OUT.D1` – Boolescher Wert für den Up-Ausgang (`TRUE` wenn aktiv)
- `DOWN_OUT.D1` – Boolescher Wert für den Down-Ausgang (`TRUE` wenn aktiv)

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket | `UP_IN` | `adapter::types::unidirectional::AX` | Eingang für die Anforderung „Aufwärts/Vorwärts“. Enthält Ereignis `E1` und Bool-Daten `D1`. |
| Socket | `DOWN_IN` | `adapter::types::unidirectional::AX` | Eingang für die Anforderung „Abwärts/Rückwärts“. |
| Plug | `UP_OUT` | `adapter::types::unidirectional::AX` | Ausgang für die Richtung Aufwärts. |
| Plug | `DOWN_OUT` | `adapter::types::unidirectional::AX` | Ausgang für die Richtung Abwärts. |
| Plug | `timeOut` | `iec61499::events::ATimeOut` | Timer-Adapter zur Realisierung der Totzeit. Steuert das Ereignis `TimeOut` nach Ablauf von `DT_PROTECT`. |

## Funktionsweise

Der Baustein realisiert eine **verriegelte Zwei-Kanal-Schaltung mit Totzeit**:

- Die beiden Eingänge `UP_IN` und `DOWN_IN` können nie gleichzeitig aktiv ausgegeben werden.
- Sobald ein Eingang aktiv wird (d.h. sein Ereignis `E1` tritt ein und das zugehörige Datum `D1` ist `TRUE`), schaltet der Baustein nach einer kurzen Totzeit in den entsprechenden Zustand (`UP` oder `DOWN`).
- Erfolgt ein Richtungswechsel, wird zuerst der **Schutzzustand `PROTECT`** eingenommen, in dem alle Ausgänge auf `FALSE` gesetzt und der Timer mit `DT_PROTECT` gestartet wird. Nach Ablauf der Totzeit wird in den Zustand `EVAL` gewechselt, der anhand der aktuellen Eingangssignale entscheidet, welcher Endzustand eingenommen wird.
- Durch die Totzeit wird ein Übersprechen oder Prellen der Signale unterbunden, z. B. bei mechanischen Schaltern oder sich überlappenden Anforderungen.

## Technische Besonderheiten

- **Adapter-basierte Schnittstelle**: Der FB kommuniziert ausschließlich über standardisierte Adapter (`AX` für boolesche Steuerung, `ATimeOut` für Timer). Dies ermöglicht eine einfache Wiederverwendung in verschiedenen Container-Bausteinen.
- **Integrierte Schutzlogik**: Im Zustand `PROTECT` werden alle Ausgänge deaktiviert, bevor eine neue Richtung aktiviert wird – dies schützt angeschlossene Hardware (z. B. Motoren, Ventile) vor Kurzschluss oder gegenseitigem Blockieren.
- **Parameteraktualisierung**: Das Ereignis `UPDATE` erlaubt eine dynamische Anpassung der Totzeit zur Laufzeit, ohne den Baustein resetten zu müssen.
- **Totzeit bei jedem Zustandswechsel**: Jeder Übergang (Stop→Up, Down→Up usw.) durchläuft immer die Schutzphase, unabhängig von der vorherigen Richtung.

## Zustandsübersicht

| Zustand | Beschreibung |
|---------|--------------|
| `STOP` | Ruhezustand. Keine Ausgabe aktiv. Wartet auf Aktivierung eines Eingangs. |
| `UP` | Ausgang `UP_OUT.D1 = TRUE`, `DOWN_OUT.D1 = FALSE`. Wird aktiv, wenn `UP_IN.D1` anliegt und `DOWN_IN.D1` inaktiv ist. |
| `DOWN` | Ausgang `DOWN_OUT.D1 = TRUE`, `UP_OUT.D1 = FALSE`. Wird aktiv, wenn `DOWN_IN.D1` anliegt und `UP_IN.D1` inaktiv ist. |
| `PROTECT` | Schutzphase. Beide Ausgänge werden sofort auf `FALSE` gesetzt, der Timer wird gestartet. Nach Ablauf von `DT_PROTECT` wird in `EVAL` gewechselt. |
| `EVAL` | Auswertungszustand. Basierend auf den aktuellen Eingangsdaten wird entschieden, welcher Endzustand (STOP, UP, DOWN) oder erneut PROTECT (bei gleichzeitigen Anforderungen) eingenommen wird. |

Die in der ECC definierten Transitionen sind:

- STOP → UP (bei UP_IN.E1 und UP_IN.D1)
- STOP → DOWN (bei DOWN_IN.E1 und DOWN_IN.D1)
- UP → PROTECT (bei UP_IN.E1 und NOT UP_IN.D1 ODER DOWN_IN.E1 und DOWN_IN.D1)
- DOWN → PROTECT (analog)
- PROTECT → EVAL (nach timeOut.TimeOut)
- EVAL → UP (bei UP_IN.D1 AND NOT DOWN_IN.D1)
- EVAL → DOWN (bei DOWN_IN.D1 AND NOT UP_IN.D1)
- EVAL → STOP (bei NOT UP_IN.D1 AND NOT DOWN_IN.D1)
- EVAL → PROTECT (bei UP_IN.D1 AND DOWN_IN.D1)
- In jedem Zustand kann ein UPDATE-Ereignis den Zustand neu bewerten und die Totzeit aktualisieren.

## Anwendungsszenarien

- **Verriegelung von Antrieben**: Beispielsweise bei einem Hubtisch oder einem Förderband, das nur in eine Richtung gleichzeitig aktiv sein darf.
- **Schutz vor Kurzschluss** in H-Brücken-Schaltungen: Bevor die Polarität eines Motors umgeschaltet wird, werden beide Ausgänge kurzzeitig deaktiviert.
- **Schaltende Sicherheitslogik** in der Landtechnik oder Automatisierung, wo mechanische Endschalter oder Näherungssensoren eine zeitliche Entprellung benötigen.
- **Schnittstelle zwischen zwei Steuerungssystemen**: Wenn beide Systeme eine gemeinsame Achse ansteuern, verhindert der Baustein Kollisionen durch die Priorisierung des zuletzt aktiven Eingangs.

## Vergleich mit ähnlichen Bausteinen

- **Einfaches RS-Flipflop**: Bietet keine Totzeit und schaltet sofort – kann bei sich überlappenden Signalen oszillieren.
- **SWITCH (ohne Schutz)**: Standard-Umschalter schaltet ebenfalls ohne Verzögerung und ohne Entprellung.
- **SR-Latch mit Timer**: Ähnliche Funktion, jedoch meist als Composite-Baustein realisiert. `ILOCK_SWITCH_PROTECT_AX` kapselt die gesamte Logik inklusive Timer und Auswertung in einem Basic Function Block.
- **Interlock-Bausteine in IEC 61499**: Viele Bibliotheken bieten Interlock-FBs, jedoch oft ohne Adapter-Schnittstelle oder mit festen Verzögerungen. Dieser Baustein ist speziell für den Einsatz mit unidirektionalen `AX`-Adaptern ausgelegt.

## Fazit

`ILOCK_SWITCH_PROTECT_AX` ist ein robuster und flexibler Baustein zur verriegelten Umschaltung mit einstellbarer Schutz-Totzeit. Die Adapter-basierte Schnittstelle ermöglicht eine saubere Integration in modulare 4diac-Architekturen. Die klare Zustandsmaschine gewährleistet deterministisches Verhalten und bietet Schutz vor Fehlschaltungen in zeitkritischen Anwendungen. Ideal für Anwendungen in der Agrartechnik, Automatisierung und Antriebstechnik, bei denen ein sicherer Richtungswechsel erforderlich ist.
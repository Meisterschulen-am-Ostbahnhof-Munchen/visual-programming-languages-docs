# AULI_D_FF_HYS_TMIN


![AULI_D_FF_HYS_TMIN](./AULI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_D_FF_HYS_TMIN** realisiert ein taktflankengesteuertes D‑Flipflop (Data Latch) mit Hysterese und einer Mindestverweilzeit zwischen aufeinanderfolgenden Ereignissen. Er wird typischerweise eingesetzt, um verrauschte oder schwankende Eingangssignale zu glätten und ein ungewolltes schnelles Umschalten zu unterdrücken. Der Baustein kommuniziert über standardisierte unidirektionale Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `INIT` | `EInit` | Initialisierungsanforderung. Setzt die Parameter Hysterese und Mindestzeit. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `INITO` | `EInit` | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `HYSTERESIS` | `ULINT` | Hystereseband als Ganzzahl ohne Vorzeichen. Der Ausgang ändert seinen Wert erst, wenn der Eingang das Band überschreitet. |
| `Tmin` | `TIME` | Mindestzeit zwischen zwei ausgelösten Ereignissen am Ausgang. Verhindert zu schnelles Schalten. |

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Die latched Information wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Adapter | Richtung | Typ | Kommentar |
|---------|----------|-----|-----------|
| `I` (Socket) | **Eingang** | `adapter::types::unidirectional::AULI` | Aufnehmender Adapter, der das zu latchdende Signal liefert. Enthält die Ereignis- und Datensignale `E1` und `D1`. |
| `Q` (Plug) | **Ausgang** | `adapter::types::unidirectional::AULI` | Ausgebender Adapter, der den aktuell gehaltenen Wert bereitstellt. Signal `E1` zeigt eine Wertänderung an, `D1` enthält den Wert. |

## Funktionsweise

Der Baustein verwendet intern den FB `E_D_FF_ANY_HYS_TMIN`, der die eigentliche Logik implementiert. Die Arbeitsweise ist:

1. **Initialisierung:** Ein Ereignis `INIT` übernimmt die Parameter `HYSTERESIS` und `Tmin` in den internen Baustein.
2. **Taktflankensteuerung:** Das Ereignis `I.E1` (Takteingang) bewirkt, dass der aktuelle Datenwert `I.D1` übernommen wird – sofern die Hysterese- und Timing-Bedingungen erfüllt sind.
3. **Hysterese:** Der neue Ausgangswert wird nur dann übernommen, wenn die Differenz zwischen dem aktuellen Eingang `D1` und dem letzten gültigen Ausgang den Betrag der Hysterese überschreitet.
4. **Mindestzeit:** Nach jeder Übernahme (Ausgabe eines Ereignisses auf `Q.E1`) wird für die Dauer `Tmin` keine weitere Übernahme zugelassen.
5. **Ausgabe:** Bei einer gültigen Flanke wird der neue Wert über `Q.D1` ausgegeben und ein Ereignis auf `Q.E1` erzeugt.

## Technische Besonderheiten

- **Hysterese:** Unterdrückt Rauschen oder kleine Schwankungen am Eingang, indem ein Totband definiert wird. Der Ausgang ändert sich nur bei signifikanten Abweichungen.
- **Mindestverweilzeit (`Tmin`):** Erzwingt eine Pause zwischen aufeinanderfolgenden Ausgangsereignissen. Dadurch werden mechanische oder systembedingte Mindestumschaltzeiten eingehalten.
- **Adapter‑Schnittstelle:** Die Verwendung eines unidirektionalen Adaptertyps ermöglicht eine lose Kopplung und Wiederverwendbarkeit in verschiedenen Umgebungen.
- **Interner FB:** Die eigentliche Logik ist in einen getypten FB ausgelagert, was die Testbarkeit und Wartbarkeit verbessert.

## Zustandsübersicht

Der Baustein besitzt keine expliziten eigenen Zustände, sondern delegiert an den internen FB. Die wesentlichen Verhaltensweisen lassen sich jedoch wie folgt beschreiben:

| Phase | Beschreibung |
|-------|--------------|
| **Initial** | Nach dem Einschalten werden `HYSTERESIS` und `Tmin` noch nicht angewendet. Ein `INIT`‑Ereignis muss die Parameter setzen. |
| **Bereit** | Nach erfolgreicher Initialisierung wartet der FB auf Taktereignisse am Eingang `I.E1`. |
| **Sperre (Tmin aktiv)** | Nach einem Ausgangsereignis wird für die Dauer `Tmin` jede weitere Übernahme blockiert. |
| **Übernahme (bei gültiger Flanke)** | Wenn die Hysterese überschritten ist und keine Sperre vorliegt, wird der aktuelle Eingangswert übernommen und ausgegeben. |

## Anwendungsszenarien

- **Entprellung von Sensorsignalen:** Ein Taster oder Näherungsschalter liefert ein schwankendes Signal. Mit Hysterese und Mindestzeit wird eine saubere Schaltflanke erzeugt.
- **Datenlogik mit Signalaufbereitung:** In der Automatisierungstechnik, wo ein digitaler Eingangswert übernommen, aber durch Rauschen oder Prellen verfälscht werden kann.
- **Zeitgesteuerte Stellglieder:** Wenn ein Aktuator eine minimale Umschaltzeit benötigt (z.B. Ventile), verhindert `Tmin` eine zu schnelle Ansteuerung.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| **Einfaches D‑FF** | Keine Hysterese, keine Verzögerung – übernimmt jede Taktflanke sofort. |
| **D‑FF mit Hysterese** | Enthält nur das Hystereseband, keine zeitliche Begrenzung zwischen Ausgaben. |
| **D‑FF mit Tmin** | Nur Mindestzeit ohne Hysterese – kann bei Rauschen trotzdem schnell schalten. |
| **AULI_D_FF_HYS_TMIN** | Kombiniert Hysterese und Mindestverweilzeit – robuster gegenüber Rauschen und schützt nachgeschaltete Komponenten vor zu schnellem Schalten. |

## Fazit

Der **AULI_D_FF_HYS_TMIN** bietet eine zuverlässige Kombination aus Hysterese und Zeitbegrenzung für taktgesteuerte Signalübernahmen. Er eignet sich besonders für industrielle Steuerungen, bei denen Störungen unterdrückt und Aktuatoren geschont werden müssen. Die modulare Adapter‑Schnittstelle erleichtert die Integration in bestehende IEC 61499‑Anwendungen.
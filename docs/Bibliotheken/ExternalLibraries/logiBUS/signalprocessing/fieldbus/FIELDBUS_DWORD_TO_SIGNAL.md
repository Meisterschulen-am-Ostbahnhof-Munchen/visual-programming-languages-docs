# FIELDBUS_DWORD_TO_SIGNAL


![FIELDBUS_DWORD_TO_SIGNAL](./FIELDBUS_DWORD_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FIELDBUS_DWORD_TO_SIGNAL` dient der Spiegelung und Validierung eines DWORD-Eingangssignals. Ist der Eingangswert gültig, wird er unverändert an den Ausgang weitergegeben und das `VALID`-Signal gesetzt. Andernfalls liefert der Baustein einen Nullwert und signalisiert die Ungültigkeit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| REQ      | Normaler Ausführungsanstoß; verarbeitet den aktuellen Wert von `IN`. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| CNF      | Bestätigung der Ausführung; wird nach der Berechnung gesendet. |

### **Daten-Eingänge**

| Variable | Typ    | Initialwert         | Kommentar        |
|----------|--------|---------------------|------------------|
| IN       | DWORD  | `NOT_AVAILABLE_DWM` | Eingangssignal   |

### **Daten-Ausgänge**

| Variable | Typ    | Initialwert   | Kommentar                          |
|----------|--------|---------------|------------------------------------|
| OUT      | DWORD  | `16#00000000` | Gefilterter Ausgangswert           |
| VALID    | BOOL   | `FALSE`       | `TRUE`, wenn das Signal gültig ist |

### **Adapter**
Keine.

## Funktionsweise

Der Baustein wird durch ein Ereignis an `REQ` aktiviert. Im zugehörigen Algorithmus wird der Eingangswert `IN` (als vorzeichenloser Integer) mit einem vordefinierten Grenzwert `VALID_SIGNAL_DW` verglichen:

- Ist `DWORD_TO_UDINT(IN) <= DWORD_TO_UDINT(VALID_SIGNAL_DW)`, so gilt das Signal als **gültig**:
  - `OUT` erhält den Wert von `IN`.
  - `VALID` wird auf `TRUE` gesetzt.
- Andernfalls (Signal ungültig):
  - `OUT` wird auf `DWORD#0` gesetzt.
  - `VALID` wird auf `FALSE` gesetzt.

Nach Abschluss der Berechnung wird das Ausgangsereignis `CNF` gesendet.

## Technische Besonderheiten

- Der Grenzwert `VALID_SIGNAL_DW` stammt aus dem importierten Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. Er definiert den maximalen zulässigen Wert für ein gültiges Signal.
- Der Initialwert des Eingangs `IN` ist `NOT_AVAILABLE_DWM` (ebenfalls importiert), sodass der Baustein bei Start bereits einen ungültigen Zustand annimmt.
- Die Umwandlung von DWORD nach UDINT ermöglicht einen einfachen numerischen Vergleich (≤), ohne Vorzeichenprobleme.
- Der Baustein ist als **SimpleFB** mit einem einzigen ECA-Zustand `REQ` realisiert.

## Zustandsübersicht

| Zustand | Aktion               | Ausgangsereignis |
|---------|----------------------|------------------|
| REQ     | Ausführen `REQ`-Algorithmus | CNF |

Es gibt nur einen Zustand; nach dessen Abarbeitung kehrt der Baustein in den IDLE-Zustand zurück (implizit).

## Anwendungsszenarien

- **Feldbus-Signalverarbeitung**: Ein DWORD-Wert von einem Feldbus (z. B. CANopen, Profibus) wird auf Gültigkeit geprüft, bevor er in der Steuerung verwendet wird.
- **Datenvalidierung**: Der Baustein kann als Filter eingesetzt werden, um ungültige oder fehlerhafte Telegramme zu erkennen und durch einen definierten Nullwert zu ersetzen.
- **Sicherheitskritische Systeme**: Durch die klare Trennung gültiger/ungültiger Signale lässt sich die Signalqualität überwachen und weiterverarbeiten.

## Vergleich mit ähnlichen Bausteinen

- Ein einfacher **MOVE**-Baustein würde den Wert ungeprüft durchreichen; `FIELDBUS_DWORD_TO_SIGNAL` fügt die Validierungslogik hinzu.
- Bausteine wie `FIELDBUS_SIGNAL_TO_DWORD` (sofern vorhanden) führen die entgegengesetzte Wandlung durch – hier wird ein DWORD-Signal in ein validiertes Signal mit Gültigkeitsflag umgesetzt.
- Der Baustein ist spezialisiert auf DWORD-Werte; für andere Datentypen (z. B. WORD, SINT) wären entsprechende Varianten denkbar.

## Fazit

`FIELDBUS_DWORD_TO_SIGNAL` ist ein kompakter, aber essenzieller Funktionsblock für die robuste Feldbus-Anbindung. Er kombiniert Signalweitergabe mit einer einfachen Gültigkeitsprüfung und stellt die Validität als separates Bool-Signal bereit. Dadurch können nachgeschaltete Bausteine schnell auf gültige Daten reagieren oder Fehlerbehandlungen einleiten. Der Einsatz der importierten Konstanten gewährleistet eine konsistente Definition der Gültigkeitsschwelle über mehrere Bausteine hinweg.
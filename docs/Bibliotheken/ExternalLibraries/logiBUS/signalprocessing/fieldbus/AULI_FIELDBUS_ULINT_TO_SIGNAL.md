# AULI_FIELDBUS_ULINT_TO_SIGNAL


![AULI_FIELDBUS_ULINT_TO_SIGNAL](./AULI_FIELDBUS_ULINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_FIELDBUS_ULINT_TO_SIGNAL** dient als zusammengesetzter Baustein zur Verarbeitung eines ULINT-Wertes aus einem Feldbus. Er spiegelt den eingehenden Wert auf den Ausgang, sofern das Signal als gültig („Valid“) erkannt wird, und gibt zusätzlich ein synchronisiertes Gültigkeitssignal aus. Der Baustein kombiniert einen internen Feldbus-Konverter mit einem D-Flipflop, um eine getaktete, zuverlässige Signalweitergabe zu gewährleisten.

## Schnittstellenstruktur
Der Baustein besitzt keine klassischen Ereignis- oder Datenports auf oberster Ebene, sondern kommuniziert ausschließlich über **Adapter**. Diese sind als **Sockets** (Eingänge) und **Plugs** (Ausgänge) realisiert.

### **Ereignis-Eingänge**

| Port | Bezeichnung | Beschreibung |
|------|-------------|--------------|
| `IN.E1` | Ereignis-Eingang (über Socket IN) | Löst die Verarbeitung eines neuen ULINT-Wertes aus. |

### **Ereignis-Ausgänge**

| Port | Bezeichnung | Beschreibung |
|------|-------------|--------------|
| `OUT.E1` | Ereignis-Ausgang (über Plug OUT) | Signalisiert die Fertigstellung der Ausgabe des gespiegelten Wertes. |
| `VALID.E1` | Ereignis-Ausgang (über Plug VALID) | Zeigt an, dass das Gültigkeitssignal aktualisiert wurde. |

### **Daten-Eingänge**

| Port | Bezeichnung | Datentyp | Beschreibung |
|------|-------------|----------|--------------|
| `IN.D1` | Daten-Eingang (über Socket IN) | ULINT | Der zu verarbeitende Feldbus-Wert. |

### **Daten-Ausgänge**

| Port | Bezeichnung | Datentyp | Beschreibung |
|------|-------------|----------|--------------|
| `OUT.D1` | Daten-Ausgang (über Plug OUT) | ULINT | Der gespiegelte Eingangswert (wenn gültig). |
| `VALID.D1` | Daten-Ausgang (über Plug VALID) | BOOL | Gültigkeitssignal (TRUE = Wert ist gültig). |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN` | Socket (Eingang) | `adapter::types::unidirectional::AULI` | Nimmt den ULINT-Wert und das zugehörige Ereignis entgegen. |
| `OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AULI` | Gibt den verarbeiteten ULINT-Wert und ein Ereignis aus. |
| `VALID` | Plug (Ausgang) | `adapter::types::unidirectional::AX` | Stellt das Gültigkeitssignal (BOOL) und ein Ereignis bereit. |

## Funktionsweise
Der Baustein arbeitet intern mit zwei Subbausteinen:

1. **FIELDBUS_ULINT_TO_SIGNAL** – Ein Feldbus-Konverter, der einen ULINT-Wert in ein Signal umwandelt und parallel ein Gültigkeitssignal (BOOL) erzeugt.
2. **E_D_FF** – Ein flankengesteuertes D-Flipflop, das das Gültigkeitssignal synchron zum Ereignis des Konverters übernimmt.

**Ablauf:**
1. Ein Ereignis am Eingang `IN.E1` startet die Verarbeitung.
2. Der Eingangswert `IN.D1` wird an den internen Konverter übergeben.
3. Der Konverter berechnet den Ausgangswert `OUT` und das `VALID`-Signal.
4. Das Ergebnis `OUT` wird sofort auf den Ausgangsadapter `OUT.E1` / `OUT.D1` gespiegelt.
5. Gleichzeitig wird das `VALID`-Signal an das Flipflop weitergeleitet und durch das Ereignis `CNF` getaktet.
6. Der Flipflop-Ausgang `Q` wird auf den Adapter `VALID.D1` ausgegeben und ein Ereignis `VALID.E1` erzeugt.

Dadurch wird sichergestellt, dass der Ausgangswert und das Gültigkeitssignal stets konsistent und synchron zueinander aktualisiert werden.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Der Baustein verwendet standardisierte unidirektionale Adapter (`AULI`, `AX`), was eine lose Kopplung und Wiederverwendbarkeit ermöglicht.
- **Synchronisation durch Flipflop**: Das Gültigkeitssignal wird flankengesteuert übernommen, um Takt- und Glitch-Probleme zu vermeiden.
- **Komposit-Struktur**: Die innere Logik ist als Netzwerk aus zwei Standardbausteinen realisiert, was die Wartbarkeit und Transparenz erhöht.
- **Keine direkten Ereignis-/Datenports**: Die gesamte Kommunikation erfolgt über Adapter, was die Integration in Adapter-basierte Architekturen erleichtert.

## Zustandsübersicht
Der Baustein selbst ist zustandslos (rein kombinatorisch mit getakteter Übernahme). Das interne Flipflop `E_D_FF` besitzt zwei Zustände:
- **Q = FALSE**: Kein gültiges Signal (initial oder nach einem ungültigen Wert).
- **Q = TRUE**: Gültiges Signal liegt an.

Ein Zustandsdiagramm für den gesamten FB ist nicht erforderlich, da das Verhalten vollständig durch die Ereignis- und Datenflüsse beschrieben wird.

## Anwendungsszenarien
- **Feldbus-Signalaufbereitung**: Ein ULINT-Wert (z. B. Zählerstand, Positionswert) wird von einem Feldbus übernommen, auf Gültigkeit geprüft und an eine Steuerung oder Visualisierung weitergegeben.
- **Qualitätskennzeichnung**: Zusammen mit dem Datenwert wird ein Bool-Signal bereitgestellt, das die Gültigkeit anzeigt (z. B. „Daten gültig“/„Daten fehlerhaft“).
- **Sicherheitsgerichtete Übertragung**: Durch die getaktete Übernahme des Gültigkeitssignals können Fehler in der Datenleitung erkannt und signalisiert werden.

## Vergleich mit ähnlichen Bausteinen
- **Einfacher Durchschleif-Baustein**: Ein einfacher `MOVE`- oder `REPEAT`-Baustein leitet den Wert ungeprüft weiter. `AULI_FIELDBUS_ULINT_TO_SIGNAL` fügt eine explizite Gültigkeitsprüfung und -signalisation hinzu.
- **FIELDBUS_ULINT_TO_SIGNAL (einzeln)**: Dieser Kernbaustein liefert bereits das Gültigkeitssignal, jedoch ohne flankengesteuerte Synchronisation. Der vorliegende Kompositbaustein ergänzt die Signalqualität durch das Flipflop.
- **Adapter-basierte Bausteine**: Speziell für den Einsatz in 4diac-Umgebungen, die auf Adapter-Kommunikation setzen; andere Bausteine mit direkten Ports sind weniger flexibel.

## Fazit
`AULI_FIELDBUS_ULINT_TO_SIGNAL` ist ein robuster, adapterbasierter Funktionsblock zur sicheren Weitergabe eines ULINT-Feldbussignals mit Gültigkeitsanzeige. Die Kombination aus Konverter und Flipflop gewährleistet eine synchronisierte und zuverlässige Signalausgabe. Durch seine klare Schnittstellenstruktur eignet er sich besonders für modulare Automatisierungslösungen, die auf lose gekoppelte Adapter setzen.
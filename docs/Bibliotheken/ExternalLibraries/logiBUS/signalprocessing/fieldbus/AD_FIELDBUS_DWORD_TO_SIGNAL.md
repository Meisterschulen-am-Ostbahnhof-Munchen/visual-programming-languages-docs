# AD_FIELDBUS_DWORD_TO_SIGNAL


![AD_FIELDBUS_DWORD_TO_SIGNAL](./AD_FIELDBUS_DWORD_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AD_FIELDBUS_DWORD_TO_SIGNAL` dient dazu, ein eingehendes Datenwort (DWORD) an den Ausgang weiterzuleiten – jedoch nur, wenn das Signal als gültig (VALID) eingestuft wird. Er kombiniert einen spezialisierten Feldbus-Baustein mit einem flankengetriggerten D-Flip-Flop, um eine zuverlässige, datengetriebene Validierung und Weitergabe zu realisieren.

## Schnittstellenstruktur

Der FB besitzt ausschließlich Adapter-Schnittstellen, keine separaten Ereignis- oder Datenports auf oberster Ebene. Die folgenden Adapter definieren die Ein- und Ausgänge:

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AD` | Socket (Eingang) | Eingangsdatenwort und zugehöriges Ereignis |
| `OUT` | `adapter::types::unidirectional::AD` | Plug (Ausgang) | Gefiltertes Ausgangsdatenwort (DWORD) |
| `VALID` | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Gültigkeitssignal (BOOL) des aktuellen Datenworts |

### **Ereignis-Eingänge** (über Adapter `IN`)

| Port | Beschreibung |
|------|--------------|
| `E1` | Ereignis zum Start der Verarbeitung eines neuen Datenworts |

### **Ereignis-Ausgänge** (über Adapter `OUT` und `VALID`)

| Adapter | Port | Beschreibung |
|---------|------|--------------|
| `OUT` | `E1` | Signalisiert, dass das gefilterte Datenwort am Ausgang anliegt |
| `VALID` | `E1` | Signalisiert, dass der Gültigkeitsstatus (TRUE/FALSE) aktualisiert wurde |

### **Daten-Eingänge** (über Adapter `IN`)

| Port | Typ (angenommen) | Beschreibung |
|------|------------------|--------------|
| `D1` | `DWORD` | Das zu verarbeitende Datenwort |

### **Daten-Ausgänge** (über Adapter `OUT` und `VALID`)

| Adapter | Port | Typ (angenommen) | Beschreibung |
|---------|------|------------------|--------------|
| `OUT` | `D1` | `DWORD` | Das gefilterte – ggf. identische – Datenwort |
| `VALID` | `D1` | `BOOL` | `TRUE`, wenn das anliegende Datenwort als gültig bewertet wird, sonst `FALSE` |

### **Adapter**

Die Adapter sind vom Typ `unidirectional`, d.h. sie übertragen jeweils ein Ereignis und ein Datum in eine Richtung. Der FB verwendet zwei verschiedene Adaptertypen:
- **AD**: Überträgt ein Ereignis und ein Datenwort (DWORD)
- **AX**: Überträgt ein Ereignis und ein boolsches Signal

## Funktionsweise

Das Zusammenspiel der internen Bausteine lässt sich in folgenden Schritten beschreiben:

1. Ein Ereignis an `IN.E1` triggert den internen FB `FIELDBUS_DWORD_TO_SIGNAL` über dessen `REQ`-Eingang.
2. Der interne FB verarbeitet das eingehende Datenwort (`IN.D1`) und gibt zwei Ergebnisse aus:
   - Das (ggf. identische) Datenwort an `OUT`
   - Ein boolsches Signal `VALID`, das angibt, ob das Datenwort gültig ist.
3. Nach Abschluss der Verarbeitung signalisiert der interne FB mit `CNF`:
   - Das Ereignis wird an `OUT.E1` weitergeleitet → der Ausgangsadapter gibt das neue Datenwort frei.
   - Gleichzeitig taktet das Ereignis den flankengetriggerten D-Flip-Flop `E_D_FF` über dessen `CLK`.
4. Der Flip-Flop übernimmt den aktuellen Gültigkeitsstatus (`VALID`-Signal) von `FIELDBUS_DWORD_TO_SIGNAL` an seinem `D`-Eingang und gibt ihn an seinem `Q`-Ausgang aus.
5. Der `EO`-Ausgang des Flip-Flops erzeugt ein Ereignis, das an `VALID.E1` gesendet wird – der Validitätsstatus wird somit zeitlich konsistent zum Datenwort aktualisiert.

Im Klartext: Der Baustein *spiegelt* das Eingangs-DWORD an den Ausgang, sofern der interne Validierungsmechanismus des Feldbus-Bausteins es als gültig einstuft. Die Gültigkeit wird durch einen Flip-Flop stabilisiert und als separates Signal ausgegeben.

## Technische Besonderheiten

- **Composite-Baustein**: Der FB ist als Netzwerk aus zwei untergeordneten Bausteinen realisiert (`FIELDBUS_DWORD_TO_SIGNAL` und `E_D_FF`).
- **Lizenz**: Der Baustein unterliegt der Eclipse Public License 2.0 (EPL-2.0).
- **Paketstruktur**: Eingebunden in den Namespace `logiBUS::signalprocessing::fieldbus`.
- **Flankengesteuerter Gültigkeitsspeicher**: Der Einsatz eines D-Flip-Flops sorgt dafür, dass das `VALID`-Signal erst mit der nächsten Taktflanke (dem `CNF`-Ereignis) aktualisiert wird – dies verhindert asynchrone Zustandswechsel.
- **Keine eigenen Ereignis-/Datenports**: Die gesamte Kommunikation erfolgt ausschließlich über standardisierte Adapter.

## Zustandsübersicht

Der FB besitzt keine explizite Zustandsmaschine, sondern arbeitet rein datenflusgesteuert. Der innere Flip-Flop `E_D_FF` kennt zwei interne Zustände:

| Zustand | Beschreibung |
|---------|--------------|
| `Q = FALSE` | Das aktuell ausgesendete `VALID`-Signal ist `FALSE` (Datenwort wird als ungültig betrachtet) |
| `Q = TRUE`  | Das aktuell ausgesendete `VALID`-Signal ist `TRUE` (Datenwort gilt als gültig) |

Der Zustand wechselt nur bei einer steigenden Flanke an `CLK` (entspricht dem `CNF`-Ereignis des internen Feldbus-Bausteins).

## Anwendungsszenarien

- **Feldbus-Datenfilterung**: Einsatz in SPS-Steuerungen, bei denen nur gültige Telegramme eines Bussystems (z. B. CANopen, PROFIBUS) an die Anwendungslogik weitergegeben werden sollen.
- **Qualitätskennzeichnung**: Ein Sensor liefert einen Messwert und ein Validierungsbit – der Baustein trennt beide Informationen sauber und hält sie synchron.
- **Sichere Datenweitergabe**: In sicherheitskritischen Umgebungen kann der FB verwendet werden, um nur geprüfte Datenwörter in nachfolgende Berechnungen zu schleusen.

## Vergleich mit ähnlichen Bausteinen

- **Einfache Buffer (z. B. `MOVE`)**: Diese geben Daten ohne Bewertung weiter. `AD_FIELDBUS_DWORD_TO_SIGNAL` fügt eine Validierungslogik hinzu und separiert das Gültigkeitssignal.
- **Typische Qualitäts-Bausteine (z. B. `QHandler`)**: Diese verarbeiten oft mehrere Qualitätsbits; dieser FB konzentriert sich auf ein einzelnes boolsches `VALID`-Signal und arbeitet mit DWORD-Daten.
- **Adapterbasierte Bausteine**: Durch die reinen Adapterschnittstellen wird eine lose Kopplung und Wiederverwendbarkeit in verschiedenen Laufzeitumgebungen gefördert.

## Fazit

`AD_FIELDBUS_DWORD_TO_SIGNAL` bietet eine kompakte und standardisierte Lösung, um Feldbus-Datenwörter nur bei festgestellter Gültigkeit an die Anwendung weiterzuleiten. Die Kombination aus einem spezifischen Feldbus-Baustein und einem Flip-Flop gewährleistet eine zeitlich korrekte und stabile Ausgabe des Validierungsstatus. Aufgrund seiner Adapter-basierten Schnittstelle lässt sich der FB flexibel in bestehende IEC 61499-Systeme integrieren.
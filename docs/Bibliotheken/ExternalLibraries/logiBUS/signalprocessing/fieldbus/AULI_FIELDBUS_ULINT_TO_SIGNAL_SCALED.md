# AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED


![AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED](./AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED** dient der skalierenden Spiegelung eines vorzeichenlosen Ganzzahlwertes (ULINT) in einen skalierten Signalwert (LREAL) unter Berücksichtigung einer Gültigkeitsinformation. Er ist als Composite-Baustein realisiert und kombiniert die eigentliche Skalierungslogik mit einer synchronisierten Valid-Ausgabe. Der Baustein ist für den Einsatz in Feldbus-Umgebungen konzipiert, wo Rohdaten (z. B. Sensorwerte) mit einem linearen Faktor und Offset umgerechnet werden müssen und die Gültigkeit des Signals zuverlässig weitergereicht werden soll.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar            |
|------|-------|----------------------|
| INIT | EInit | Init Request         |

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar             |
|-------|-------|-----------------------|
| INITO | EInit | Init Confirmation     |

### **Daten-Eingänge**
| Name   | Typ   | Initialwert | Kommentar                       |
|--------|-------|-------------|-----------------------------------|
| SCALE  | LREAL | 1.0         | Skalierungsfaktor               |
| OFFSET | DINT  | 0           | Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**
*Keine expliziten Datenausgänge an der FB-Schnittstelle vorhanden – die Ausgabe erfolgt über die Adapter.*

### **Adapter**
#### **Socket (Eingang)**
| Name | Typ                                              | Kommentar |
|------|--------------------------------------------------|-----------|
| IN   | adapter::types::unidirectional::AULI             | Input     |

#### **Plug (Ausgang)**
| Name  | Typ                                              | Kommentar           |
|-------|--------------------------------------------------|---------------------|
| OUT   | adapter::types::unidirectional::ALR              | Output Filtered     |
| VALID | adapter::types::unidirectional::AX               | TRUE if Signal is VALID |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert. Nach einem INIT-Ereignis (am Eingang `INIT`) wird der interne Skalierungsbaustein initialisiert und quittiert mit `INITO`. Die eigentliche Verarbeitung erfolgt bei jedem Ereignis, das über den Adapter `IN.E1` ankommt:

1. **Datenübernahme:** Der von `IN.D1` bereitgestellte ULINT-Wert wird an den internen Funktionsblock `FIELDBUS_ULINT_TO_SIGNAL_SCALED` weitergeleitet.
2. **Skalierung:** Der interne Block wendet den Skalierungsfaktor `SCALE` (LREAL) und den Offset `OFFSET` (DINT) auf den Rohwert an und erzeugt einen skalierten LREAL-Wert sowie ein Gültigkeitssignal (`VALID`).
3. **Synchronisation:** Das Gültigkeitssignal wird über ein flankengetriggertes D-Flipflop (`E_D_FF`) synchronisiert. Die Taktflanke wird durch das `CNF`-Ereignis des internen Blocks bereitgestellt.
4. **Ausgabe:** Der skalierte Wert wird über `OUT.D1` und das zugehörige Ereignis `OUT.E1` an den Adapter `OUT` gesendet. Das synchronisierte Gültigkeitssignal wird über `VALID.D1` und das Ereignis `VALID.E1` an den Adapter `VALID` ausgegeben.

Der interne Skalierungsbaustein ist derselbe Typ wie der äußere, was bedeutet, dass die Skalierungslogik rekursiv aufgebaut sein könnte, jedoch im vorliegenden Entwurf die innere Instanz die eigentliche Rechenlogik enthält. Die äußere Hülle fügt die Synchronisation der Gültigkeitsinformation hinzu und stellt die Adapter-Schnittstellen bereit.

## Technische Besonderheiten
- **Adaptierte Ein‑/Ausgänge:** Der Baustein verwendet ausschließlich Adapter für die Datenübertragung. Dies ermöglicht eine lose Kopplung in Feldbus‑ und Komponentennetzwerken.
- **Synchronisation der Gültigkeit:** Die Valid-Information wird über ein D‑Flipflop getaktet, sodass sie zeitlich mit dem ausgegebenen Signalwert übereinstimmt.
- **Skalierungsparameter:** `SCALE` und `OFFSET` sind als Eingangsvariablen direkt zugänglich und können zur Laufzeit geändert werden. Initialwerte erlauben einen sofortigen Betrieb ohne Konfiguration.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine. Sein Verhalten wird durch die Ereignissteuerung bestimmt:
- **Initialisiert:** Nach erfolgreichem `INIT` ist der interne Skalierungsblock bereit.
- **Bereit:** Auf ein Ereignis auf `IN.E1` wird die Datenverarbeitung ausgelöst. Nach Abschluss werden `OUT.E1` und `VALID.E1` ausgelöst.
- **Fehlerfall:** Ein fehlerhafter Skalierungsvorgang (z. B. Überlauf) wird durch den internen Block behandelt; das Gültigkeitssignal würde in diesem Fall `FALSE` werden.

## Anwendungsszenarien
- **Feldbus‑Sensorauswertung:** Ein Sensor liefert einen ULINT-Rohwert über einen Bus (z. B. CANopen, PROFIBUS). Der Baustein skaliert den Wert in eine physikalische Einheit (z. B. Temperatur, Druck) und gibt ihn als LREAL an die Steuerung weiter, zusammen mit einem Gültigkeitsflag.
- **Signalaufbereitung in landwirtschaftlichen Maschinen** (wie im Copyright‑Hinweis angedeutet): Umwandlung von Drehzahl‑, Füllstands‑ oder Geschwindigkeitsdaten in normierte Signale für eine übergeordnete Steuerung.
- **Qualitätsgesicherte Datenweitergabe:** Wenn die Gültigkeit eines Signals (z. B. Sensorfehler, Kommunikationsabbruch) explizit mitgeführt werden muss, sorgt die synchronisierte Valid‑Ausgabe für konsistente Signale.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_ULINT_TO_SIGNAL** (ohne Scaled): Ein direkter Durchgang ohne Skalierung – hier ist die Skalierung integriert.
- **Standard‑Skalierungsbausteine** (z. B. aus IEC‑61131‑3): Diese arbeiten oft mit einfachen Ein‑/Ausgängen und ohne Adapter oder Gültigkeitssynchronisation.
- **FB mit integrierter Validierung:** Viele Feldbus‑FB geben nur einen Datenwert aus. Dieser Baustein hebt sich durch die separate, getaktete Gültigkeitsausgabe ab.

## Fazit
Der **AULI_FIELDBUS_ULINT_TO_SIGNAL_SCALED** ist ein spezialisierter Composite‑FB für die skalierte Umwandlung von ULINT‑Feldbusdaten in LREAL‑Signale mit synchronisierter Gültigkeitsinformation. Durch die Verwendung von Adaptern und die klare Trennung von Skalierung und Synchronisation eignet er sich besonders für modulare, sicherheitskritische Anwendungen in der Automatisierungs‑ und Agrartechnik. Die Parametrierung über `SCALE` und `OFFSET` macht ihn flexibel einsetzbar.
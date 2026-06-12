# AUS_FIELDBUS_USINT_TO_SIGNAL


![AUS_FIELDBUS_USINT_TO_SIGNAL](./AUS_FIELDBUS_USINT_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUS_FIELDBUS_USINT_TO_SIGNAL` dient der Weitergabe eines USINT-Signals von einem Feldbus-Adapter unter Berücksichtigung einer Gültigkeitsprüfung. Er spiegelt den Eingangswert auf den Ausgang, sofern das Signal als gültig erkannt wird. Ein zusätzlicher Adapter gibt den Gültigkeitsstatus aus. Die interne Logik verwendet einen dedizierten Fieldbus-Umwandlungsbaustein und ein flankengesteuertes D-Flip-Flop zur Synchronisation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Bezeichnung | Beschreibung |
|-------------|--------------|
| `IN.E1` | Über den Adapter `IN` (Socket) eingehendes Ereignis, das die Verarbeitung anstößt. |

### **Ereignis-Ausgänge**
| Bezeichnung | Beschreibung |
|-------------|--------------|
| `OUT.E1` | Über den Adapter `OUT` (Plug) ausgegebenes Ereignis nach erfolgreicher Spiegelung des gültigen Signals. |
| `VALID.E1` | Über den Adapter `VALID` (Plug) ausgegebenes Ereignis nach Aktualisierung des Gültigkeitsstatus. |

### **Daten-Eingänge**
| Bezeichnung | Typ | Beschreibung |
|-------------|-----|--------------|
| `IN.D1` | USINT (implizit) | Eingangsdatenwert, der auf Gültigkeit geprüft und gespiegelt wird. |

### **Daten-Ausgänge**
| Bezeichnung | Typ | Beschreibung |
|-------------|-----|--------------|
| `OUT.D1` | (analog zu IN) | Ausgangsdatenwert, der bei gültigem Signal den Eingangswert widerspiegelt. |
| `VALID.D1` | BOOL | Gültigkeitsflag: `TRUE` wenn das Eingangssignal als gültig erkannt wurde, sonst `FALSE`. |

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AUS` | Socket | Empfängt das Rohsignal (Ereignis + Daten) vom Feldbus. |
| `OUT` | `adapter::types::unidirectional::AUS` | Plug | Gibt das validierte Signal an nachgelagerte Komponenten weiter. |
| `VALID` | `adapter::types::unidirectional::AX` | Plug | Stellt den Gültigkeitsstatus (Ereignis + BOOL) zur Verfügung. |

## Funktionsweise
Der FB reagiert auf ein eingehendes Ereignis `IN.E1`. Dieses triggert den internen Baustein `FIELDBUS_USINT_TO_SIGNAL`, der den Datenwert `IN.D1` verarbeitet und zwei Ergebnisse liefert:
- Einen Ausgangswert (`OUT`)
- Ein Gültigkeitssignal (`VALID`)

Der Ausgangswert wird direkt auf `OUT.D1` durchgeschaltet und über `OUT.E1` quittiert. Gleichzeitig wird das Gültigkeitssignal dem Daten-Eingang `D` des D-Flip-Flops `E_D_FF` zugeführt. Das Flip-Flop wird durch dasselbe Ereignis (über `CFN`) getaktet, sodass der Gültigkeitsstatus stabil auf `Q` gehalten und auf `VALID.D1` ausgegeben wird. Erst nach dem Taktimpuls wird `VALID.E1` ausgelöst.

Zusammengefasst: Der Ausgang `OUT` spiegelt den Eingang `IN`, sofern das Signal im Feldbus-Baustein als gültig erkannt wird. Der Gültigkeitsstatus wird flankengetriggert gespeichert.

## Technische Besonderheiten
- **Adapterbasierte Kommunikation:** Alle Ein- und Ausgänge sind über standardisierte unidirektionale Adapter (`AUS`, `AX`) realisiert, die eine klare Trennung zwischen Ereignis- und Datenpfaden ermöglichen.
- **Flankengesteuerte Gültigkeitsspeicherung:** Ein D-Flip-Flop sorgt dafür, dass der Gültigkeitszustand nur bei einem Ereignis (steigende Flanke) übernommen wird – dies verhindert Glitches und asynchrone Zustandswechsel.
- **Wiederverwendete interne FB:** Der Baustein `FIELDBUS_USINT_TO_SIGNAL` übernimmt die eigentliche Feldbus-spezifische Konvertierung und Gültigkeitsprüfung; der äußere FB dient als reine Hüll- und Synchronisationslogik.

## Zustandsübersicht
Der interne Zustand wird durch das D-Flip-Flop `E_D_FF` definiert. Es besitzt zwei Zustände:

| Zustand | Beschreibung |
|---------|--------------|
| `Q = FALSE` (Initial) | Ausgang `VALID.D1` zeigt „ungültig“ an. Nach jedem Ereignis wird der aktuelle `VALID`-Wert (`D`) übernommen. |
| `Q = TRUE` | Ausgang `VALID.D1` zeigt „gültig“ an. Der Zustand bleibt bis zum nächsten Ereignis stabil. |

Zustandsübergänge erfolgen ausschließlich bei jeder steigenden Flanke des Taktsignals (Ereignis `CNF` des Fieldbus-Bausteins).

## Anwendungsszenarien
- **Feldbus-Signalaufbereitung:** Ein Sensor sendet USINT-Werte über einen Feldbus; der FB filtert ungültige Werte heraus und gibt nur valide Daten sowie einen klaren Gültigkeitszustand weiter.
- **Sicherheitsgerichtete Datenweitergabe:** In Steuerungen, die auf gültige Signale angewiesen sind (z. B. in der Agrartechnik), kann dieser FB als einfache Validierungsstufe eingesetzt werden.
- **Schnittstellenanpassung:** Der Baustein verbindet einen feldbusspezifischen Adapter (z. B. CANopen, PROFIBUS) mit einem einheitlichen Logik-Adapter, der nur bei gültigen Daten Ereignisse auslöst.

## Vergleich mit ähnlichen Bausteinen
- **Einfache Mirror-FBs** (z. B. `MOVE` oder `AUS_MIRROR`): Diese geben das Signal ohne Gültigkeitsprüfung weiter. Der vorliegende FB bietet zusätzlich eine Validierungslogik und einen separaten Gültigkeitsausgang.
- **Fieldbus-Konverter ohne Speicher:** Manche Bausteine geben das Gültigkeitssignal direkt und ungetaktet aus. Der Einsatz eines Flip-Flops hier vermeidet metastabile Zustände und sorgt für deterministische Ausgaben.

## Fazit
Der `AUS_FIELDBUS_USINT_TO_SIGNAL` ist ein nützlicher Funktionsblock für die saubere, validierte Weiterleitung von USINT-Signalen aus Feldbussystemen. Durch die Kombination aus einem spezialisierten Fieldbus-Baustein und einem flankengesteuerten Flip-Flop wird eine zuverlässige Trennung von gültigen und ungültigen Daten erreicht. Die adapterbasierte Schnittstelle erleichtert die Integration in modulare Steuerungsarchitekturen.
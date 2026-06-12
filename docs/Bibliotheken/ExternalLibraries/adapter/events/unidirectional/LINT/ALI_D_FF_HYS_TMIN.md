# ALI_D_FF_HYS_TMIN


![ALI_D_FF_HYS_TMIN](./ALI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ALI_D_FF_HYS_TMIN** realisiert ein datengesteuertes D-Flip-Flop mit einer einstellbaren Hysteresebreite (Schwellwertband) und einer minimalen Wartezeit zwischen zwei aufeinanderfolgenden Ausgangsereignissen. Er dient zur Entprellung und Stabilisierung von Signalsprüngen in der industriellen Automatisierungstechnik, insbesondere wenn ein Signal erst dann als gültig übernommen werden soll, wenn es einen definierten Toleranzbereich verlassen hat und eine Mindestzeit seit der letzten gültigen Flanke vergangen ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name  | Typ   | Kommentar |
|-------|-------|-----------|
| INIT  | EInit | Initialisierungsanforderung – setzt die Hysteresebreite und die Mindestzeit fest. |

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar |
|-------|-------|-----------|
| INITO | EInit | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**
| Name       | Typ  | Kommentar |
|------------|------|-----------|
| HYSTERESIS | LINT | Hystereseband als ganzzahliger Wert (LINT). |
| Tmin       | TIME | Minimale Zeit zwischen zwei Ausgangsereignissen (Inter‑Disposal Time). |

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden.*  
Der Baustein gibt seinen Zustand über den Adapter **Q** aus (siehe Adapter).

### **Adapter**
| Typ    | Name | Richtung | Kommentar |
|--------|------|----------|-----------|
| `adapter::types::unidirectional::ALI` | I    | Socket   | Eingangsadapter – liefert das zu übernehmende Signal (Ereignis und Datenwert). |
| `adapter::types::unidirectional::ALI` | Q    | Plug     | Ausgangsadapter – gibt den zuletzt gültigen Datenwert sowie ein Ereignis aus. |

Der Adaptertyp `ALI` umfasst ein Ereignis (E1) und einen Datenwert (D1) und dient der unidirektionalen Kommunikation zwischen Funktionsblöcken.

## Funktionsweise
Der Baustein **ALI_D_FF_HYS_TMIN** ist als Komposition realisiert und nutzt intern den FB `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`. Seine Arbeitsweise lässt sich wie folgt beschreiben:

1. **Initialisierung** – Über das Ereignis **INIT** werden die Parameter **HYSTERESIS** und **Tmin** gesetzt. Nach erfolgreicher Initialisierung wird **INITO** ausgelöst.

2. **Signalübernahme** – Jedes Ereignis am Socket **I** (Ereignis **I.E1**) wird als Taktflanke interpretiert. Der zugehörige Datenwert **I.D1** wird nur dann in den internen Speicher übernommen, wenn er sich außerhalb des Hysteresebandes um den aktuell gespeicherten Wert befindet (d. h. die Änderung überschreitet die Hysterese).

3. **Mindestzeitsteuerung** – Nach der Übernahme eines gültigen Wertes wird die Ausgabe über den Plug **Q** (Ereignis **Q.E1** und Wert **Q.D1**) erst dann freigegeben, wenn seit dem letzten Ausgangsereignis mindestens **Tmin** verstrichen ist. Dadurch werden unerwünschte schnelle Signalwechsel unterdrückt.

4. **Ausgabe** – Sobald die Mindestzeit eingehalten wurde, erfolgt die Ausgabe des neuen Wertes über den Ausgangsadapter **Q**. Der Baustein wartet anschließend auf das nächste Eingangsereignis.

## Technische Besonderheiten
- **Hysterese-Datenbreite** – Die Hysterese wird als LINT (64‑Bit‑Ganzzahl) definiert; dies ermöglicht die Verarbeitung sehr großer Wertebereiche.
- **Zeitparameter** – Die minimale Inter‑Disposal‑Zeit **Tmin** wird als IEC‑61499‑`TIME` angegeben (z. B. `T#10ms`).
- **Adapterbasierte Kopplung** – Die Verwendung der Adapter `ALI` erlaubt eine lose Kopplung zwischen signalerzeugenden und signalverarbeitenden Bausteinen. Der Socket **I** empfängt die Daten, der Plug **Q** stellt sie bereit.
- **Typ der Abhängigkeit** – Der Baustein basiert auf dem internen FB `E_D_FF_ANY_HYS_TMIN`, der die eigentliche Hysterese‑ und Zeitlogik implementiert. Der äußere Baustein kapselt lediglich die Adapter‑Schnittstelle.

## Zustandsübersicht
Der Baustein durchläuft folgende Zustände:

1. **INIT** – Warten auf Initialisierungsparameter.
2. **IDLE** – Bereit; wartet auf ein Ereignis am Socket **I**.
3. **SAMPLE** – Ein Ereignis ist eingetroffen; der Datenwert wird auf Überschreitung der Hysterese geprüft.
   - *Hysterese verletzt:* Der Wert wird ignoriert, zurück zu **IDLE**.
   - *Hysterese erfüllt:* Wechsel in Zustand **WAIT_TMIN**.
4. **WAIT_TMIN** – Der neue Wert ist gespeichert, die Freigabe wird um **Tmin** verzögert.
   - Nach Ablauf der Zeit erfolgt die Ausgabe über **Q** und Rücksprung nach **IDLE**.

Eine formale Zustandsmaschine ist nicht über die XML‑Schnittstelle sichtbar, ergibt sich aber aus dem Verhalten des internen Flip‑Flops.

## Anwendungsszenarien
- **Sensorwertglättung** – Ein digitaler Sensor (z. B. Drehgeber) liefert Werte, die aufgrund von Vibrationen oder Rauschen kurzzeitig schwanken. Die Hysterese verhindert, dass kleine Schwankungen als gültige Änderung gewertet werden.
- **Entprellung von Tastern** – Bei mechanischen Kontakten wird durch **Tmin** sichergestellt, dass Prellvorgänge innerhalb einer bestimmten Zeit nicht zu mehrfachen Ausgangsereignissen führen.
- **Messwertübernahme mit Totzeit** – In Dosier‑ oder Positioniersystemen muss die Mindestzeit zwischen zwei gültigen Messwerten eingehalten werden, um die Systemdynamik nicht zu überlasten.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Hysterese | Mindestzeit | Adapterschnittstelle |
|----------|-----------|-------------|----------------------|
| `E_D_FF` (einfach) | Nein | Nein | Nein (direkte I/O) |
| `E_D_FF_HYS` | Ja | Nein | Nein |
| `ALI_D_FF_HYS_TMIN` | Ja | Ja | Ja (Adapternutzung) |

Der hier beschriebene Baustein vereint die Vorteile von Hysterese und zeitlichem Mindestabstand und ist durch seine Adapter‑Schnittstelle besonders gut für eine modulare, ereignisgesteuerte Architektur nach IEC 61499 geeignet.

## Fazit
Der Baustein **ALI_D_FF_HYS_TMIN** stellt eine robuste Lösung zur stabilen Übernahme von Signalen in rauer Umgebung dar. Durch die Kombination von Hysterese und minimaler Ausgabezeit werden sowohl Amplitudenschwankungen als auch zeitliche Preller effektiv unterdrückt. Die adapterbasierte Ein‑ und Ausgabe macht ihn flexibel einsetzbar in komplexen Automatisierungsnetzwerken.
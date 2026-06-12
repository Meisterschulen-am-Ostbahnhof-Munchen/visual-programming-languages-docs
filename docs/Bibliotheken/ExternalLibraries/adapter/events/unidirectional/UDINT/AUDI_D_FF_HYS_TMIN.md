# AUDI_D_FF_HYS_TMIN

Kein Bild vorhanden


![AUDI_D_FF_HYS_TMIN](./AUDI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_D_FF_HYS_TMIN** realisiert ein taktflankengesteuertes Daten-Latch (D-Flipflop) mit einer Hysterese-Funktion und einer Mindestverweilzeit zwischen den Ausgangsereignissen (EO). Er dient der stabilen und entstörten Übernahme eines Datenwertes bei gleichzeitiger Unterdrückung von Rauschen und unerwünscht schnellen Schaltvorgängen. Der FB kapselt die Logik eines internen Bausteins `E_D_FF_ANY_HYS_TMIN` und stellt die Ein‑/Ausgänge über standardisierte Adapter bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ   | Kommentar                                    |
|----------|-------|----------------------------------------------|
| INIT     | EInit | Initialisierungsanfrage, setzt Hysterese und Mindestzeit |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Kommentar                                    |
|----------|-------|----------------------------------------------|
| INITO    | EInit | Initialisierungsbestätigung                  |

### **Daten-Eingänge**
| Variable     | Typ   | Kommentar                                                 |
|--------------|-------|-----------------------------------------------------------|
| HYSTERESIS   | UDINT | Hysterese-Band (Breite der Totzone zur Störunterdrückung) |
| Tmin         | TIME  | Mindestzeit zwischen zwei aufeinanderfolgenden Ausgangsereignissen |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgangsdaten werden über den Adapter **Q** bereitgestellt.

### **Adapter**
| Bezeichnung | Typ                                | Richtung | Kommentar                  |
|-------------|------------------------------------|----------|----------------------------|
| I           | `adapter::types::unidirectional::AUDI` | Eingang  | Zu übernehmender Datenwert |
| Q           | `adapter::types::unidirectional::AUDI` | Ausgang  | Latched Wert               |

## Funktionsweise
1. **Initialisierung** – Über den Ereigniseingang `INIT` werden die Parameter `HYSTERESIS` und `Tmin` gesetzt. Nach erfolgreicher Initialisierung wird `INITO` ausgegeben.
2. **Datenlatch** – Jedes Ereignis am Adaptereingang `I.E1` wird als Takt (CLK) interpretiert. Der aktuelle Datenwert von `I.D1` wird übernommen.
3. **Hysterese** – Eine Änderung des Ausgangswertes erfolgt nur, wenn die Differenz zwischen neuem und altem Wert das Hysterese-Band (`HYSTERESIS`) überschreitet. Dadurch werden kleine Schwankungen (z. B. Rauschen) unterdrückt.
4. **Mindestzeit** – Nach einem Ausgangsereignis (`Q.E1`) wird für die Dauer `Tmin` kein weiteres Ausgangsereignis erzeugt, auch wenn am Eingang neue Takte anliegen. Dies verhindert eine zu hohe Rate der Ausgangsereignisse.

Der FB verwendet intern den Baustein `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN`, der die beschriebene Logik implementiert.

## Technische Besonderheiten
- **Adapterbasierte Ein-/Ausgabe** – Der FB kommuniziert über standardisierte unidirektionale Adapter vom Typ `AUDI`. Dies ermöglicht eine typsichere und modulare Anbindung an andere Bausteine.
- **Parametrierbare Hysterese** – Die Hysterese-Breite kann zur Laufzeit über `HYSTERESIS` angepasst werden.
- **Mindestzeit zwischen Ereignissen** – Die minimale Zeit `Tmin` zwischen zwei Ausgangsereignissen schützt nachgeschaltete Komponenten vor Überlastung und definiert eine maximale Aktualisierungsrate.
- **Initialisierungszwang** – Vor dem ersten Betrieb muss der FB über `INIT` konfiguriert werden, andernfalls sind die internen Parameter undefiniert.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten im XML. Das Verhalten wird vollständig durch den inneren Baustein `E_D_FF_ANY_HYS_TMIN` bestimmt. Folgende Zustände lassen sich logisch ableiten:

- **Initial** – Nach Reset, wartet auf `INIT`.
- **Bereit** – Nach `INIT` und `INITO`, bereit zur Datenübernahme.
- **Warten auf Takt** – Erwartet ein Ereignis an `I.E1`.
- **Verarbeitung** – Daten werden ausgewertet, Hysterese geprüft.
- **Ausgabe gesperrt** – Nach einem Ausgangsereignis läuft die `Tmin`-Zeit, während der keine weiteren Ausgaben erfolgen.

## Anwendungsszenarien
- **Sensorwert-Verdrahtung** – Stabilisierung analoger oder digitaler Sensorsignale mit Hysterese (z. B. Füllstand, Temperatur, Druck) und Begrenzung der Aktualisierungsrate.
- **Taktflankengesteuerte Datenübernahme** – Zuverlässiges Einlesen von Werten aus rauschender Umgebung, wenn eine Mindestzeit zwischen zwei Wertänderungen erforderlich ist.
- **Steuerung von Aktoren** – Schutz von Aktoren vor zu schnellem Schalten durch Begrenzung der Ausgangsereignisfrequenz.

## Vergleich mit ähnlichen Bausteinen
- **Standard D-Flipflop (z. B. `E_D_FF`)** – Keine Hysterese und keine Zeitbegrenzung; reagiert auf jede Taktflanke ohne Filterung.
- **D-Flipflop mit Hysterese (z. B. `AUDI_D_FF_HYS`)** – Enthält Hysterese, aber keine Mindestzeit zwischen Ausgangsereignissen.
- **AUDI_D_FF_HYS_TMIN** – Kombiniert beide Eigenschaften: Hysterese zur Rauschunterdrückung und `Tmin` zur Begrenzung der Ereignisrate.

## Fazit
Der FB `AUDI_D_FF_HYS_TMIN` bietet eine robuste, parametrierbare Lösung für die taktgesteuerte Datenübernahme in industriellen Automatisierungsumgebungen. Durch die Kombination von Hysterese und minimaler Inter-Ereignis-Zeit eignet er sich besonders für Anwendungen mit gestörten Signalen oder begrenzter Ausgangsbandbreite. Die Adapter-basierte Schnittstelle erleichtert die Integration in vorhandene Systeme und fördert die Wiederverwendbarkeit.
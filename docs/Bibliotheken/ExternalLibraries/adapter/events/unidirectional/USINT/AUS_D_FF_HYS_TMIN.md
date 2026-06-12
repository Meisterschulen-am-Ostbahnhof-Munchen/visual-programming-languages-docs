# AUS_D_FF_HYS_TMIN


![AUS_D_FF_HYS_TMIN](./AUS_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUS_D_FF_HYS_TMIN** realisiert ein datengetriggertes Flip-Flop (D‑Flip‑Flop) mit einer Hysterese und einer minimalen Zwischenereigniszeit. Er ist als Sub‑Applikation (FB‑Netzwerk) aufgebaut, die die eigentliche Logik an den inneren Baustein `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS_TMIN` delegiert. Der Baustein dient dazu, einen analogen oder diskreten Wert mit vorgegebenem Hystereseband zu latchen und gleichzeitig die Rate der Ereignisse (über den Adapter‑Eingang) auf einen konfigurierbaren Mindestabstand zu begrenzen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ   | Mit Variablen         | Beschreibung                                      |
|----------|-------|-----------------------|---------------------------------------------------|
| `INIT`   | EInit | `HYSTERESIS`, `Tmin`  | Initialisierungsanforderung; setzt Hysterese und Mindestzeit. |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Mit Variablen | Beschreibung                                  |
|----------|-------|---------------|-----------------------------------------------|
| `INITO`  | EInit | –             | Bestätigung der abgeschlossenen Initialisierung. |

### **Daten-Eingänge**
| Name         | Typ      | Beschreibung                                                     |
|--------------|----------|------------------------------------------------------------------|
| `HYSTERESIS` | ANY_NUM  | Hystereseband – Schwellwertdifferenz, die über‑/unterschritten werden muss, damit ein neuer Wert gelatcht wird. |
| `Tmin`       | TIME     | Minimale Zeitspanne zwischen zwei eingehenden Ereignissen (Inter‑arrival‑Time). |

### **Daten-Ausgänge**
– Keine direkten Datenausgänge vorhanden. Der gelatchte Wert wird über den Adapter‑Plug `Q` ausgegeben.

### **Adapter**
| Adapter | Richtung    | Typ                                 | Beschreibung                                                              |
|---------|-------------|--------------------------------------|---------------------------------------------------------------------------|
| `I`     | Socket (In) | `adapter::types::unidirectional::AUS`| Empfängt das zu latchende Ereignis und den dazugehörigen Datenwert.      |
| `Q`     | Plug (Out)  | `adapter::types::unidirectional::AUS`| Gibt das verarbeitete Ereignis und den gelatchten Datenwert nach außen.   |

## Funktionsweise

Der Baustein arbeitet als reine Kapselung eines internen Flip‑Flops. Nach dem Start muss zuerst `INIT` mit den Parametern `HYSTERESIS` und `Tmin` aufgerufen werden. Danach können über den Adapter‑Socket `I` Ereignisse (via `I.E1`) und zugehörige Datenwerte (via `I.D1`) anliegen.

- Jedes Ereignis am Eingang `I.E1` wird an den internen FB `E_D_FF_ANY_HYS_TMIN` weitergeleitet.
- Die Daten `I.D1` werden mit dem Hystereseband verglichen: Nur wenn der neue Wert außerhalb des durch die Hysterese definierten Totbands um den zuletzt gelatchten Wert liegt, wird das Flip‑Flop aktualisiert.
- Zusätzlich wird die Zeit seit dem letzten gültigen Ereignis überwacht (`Tmin`). Liegt ein Ereignis zu früh (kürzer als `Tmin`) nach dem vorherigen, wird es ignoriert.
- Ein gültiges, gelatchtes Ereignis wird über den Adapter‑Plug `Q` als `Q.E1` und der zugehörige Datenwert als `Q.D1` ausgegeben.

Der interne FB übernimmt die gesamte Logik; der äußere Baustein dient als Schnittstellen‑Wrapper, der die Ereignisse und Daten entsprechend verbindet.

## Technische Besonderheiten

- **Adapter‑Schnittstelle:** Die Kommunikation erfolgt über die unidirektionalen Adapter `adapter::types::unidirectional::AUS`. Dies ermöglicht eine klare Trennung von Ereignis‑ und Datenfluss und eine einfache Wiederverwendung in verschiedenen Kontexten.
- **Hysterese:** Verhindert ständiges Umkippen bei verrauschten Signalen. Der gelatchte Wert ändert sich erst, wenn der Eingang das Hystereseband verlässt.
- **Minimale Zwischenereigniszeit (`Tmin`):** Entprellt die Ereignisse und verhindert Bursts. Nur Ereignisse, die mindestens `Tmin` auseinanderliegen, werden akzeptiert.
- **Kompakte Kapselung:** Der FB enthält kein eigenes Verhalten, sondern bildet eine logische Einheit aus Initialisierung, Ereignisverarbeitung und Ausgabe – ideal für modulare Steuerungsarchitekturen.

## Zustandsübersicht

Da der Baustein kein eigenes Zustandsdiagramm besitzt (die Logik liegt im internen FB), ergibt sich das Zustandsverhalten aus dem Zusammenspiel von Ereignissteuerung und den Parametern:

1. **Initialisierung (`INIT` – `INITO`)**: Nach dem Start wird der interne FB konfiguriert. Erst danach können Ereignisse verarbeitet werden.
2. **Warten auf Eingangsereignis**: Der FB ist passiv, bis ein Ereignis über `I.E1` eintrifft.
3. **Ereignisprüfung** (intern):
   - Zeitprüfung: Ist der Abstand zum letzten Ereignis ≥ `Tmin`?
   - Hystereseprüfung: Überschreitet der neue Wert den alten Wert um mehr als `HYSTERESIS`?
4. **Ausgabe**: Bei bestandener Prüfung wird `Q.E1` ausgelöst und der neue Datenwert an `Q.D1` übergeben.
5. **Rückkehr in Wartezustand**.

## Anwendungsszenarien

- **Sensorauswertung mit Rauschen:** Ein Analogwert (z. B. Temperatur, Druck) soll nur dann einen Schaltvorgang auslösen, wenn er eine signifikante Änderung (Hysterese) zeigt und nicht zu schnell hintereinander kommt (Entprellung).
- **Frequenzbegrenzung:** In Kommunikationsprotokollen, bei denen ein Ereignis nicht häufiger als eine bestimmte Rate verarbeitet werden darf.
- **Sicherheitskritische Anwendungen:** Verhindern von Fehlauslösungen durch kurzzeitige Störimpulse (Mindestzeit zwischen zwei Flanken).

## Vergleich mit ähnlichen Bausteinen

| Baustein                     | Eigenschaften                                                                 |
|------------------------------|-------------------------------------------------------------------------------|
| Standard‑D‑Flip‑Flop         | Latcht bei jeder steigenden Flanke ohne Hysterese oder Zeitbegrenzung.        |
| `E_D_FF_HYS` (ohne Tmin)     | Nur Hysterese, keine zeitliche Entprellung.                                   |
| `E_D_FF_TMIN` (ohne Hys)     | Nur Mindestzeit, keine Hysterese.                                             |
| **`AUS_D_FF_HYS_TMIN`**      | Kombiniert Hysterese **und** Mindestzeit – robuster gegen Rauschen und Bursts.|

Der vorliegende Baustein eignet sich daher besonders dann, wenn beide Effekte (Signaltoleranz und zeitliche Begrenzung) gleichzeitig erforderlich sind.

## Fazit

`AUS_D_FF_HYS_TMIN` ist ein spezialisierter D‑Flip‑Flop‑Wrapper, der durch die Kombination von Hysterese und minimaler Ereignisabstandszeit eine zuverlässige, entprellte Datenlatch‑Funktion bietet. Die Kapselung als Sub‑Applikation mit Adapter‑Schnittstellen macht ihn einfach in größere Steuerungsnetzwerke integrierbar. Die Initialisierung über `INIT` sorgt für eine definierte Startkonfiguration. Für Anwendungen, die eine robuste Schwellwerterkennung mit Rauschunterdrückung und Frequenzbegrenzung benötigen, ist dieser Baustein eine ideale Lösung.
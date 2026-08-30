# E_D_FF_ANY_HYS_TMIN


![E_D_FF_ANY_HYS_TMIN](./E_D_FF_ANY_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `E_D_FF_ANY_HYS_TMIN` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für IEC 61499-basierte Systeme. Er realisiert ein flankengetriggertes D-Flipflop (Data Latch) mit einer integrierten Schwellwert-Hysterese und einer zeitlichen Mindestabstandsbegrenzung (`Tmin`) für ausgehende Ereignisse.

Der Baustein dient dazu, kontinuierliche oder hochfrequente Änderungen eines numerischen Eingangssignals zu filtern. Ein neues Ereignis am Ausgang wird nur dann erzeugt, wenn die Signaländerung die definierte Hysterese überschreitet und gleichzeitig ein definierter Mindestzeitraum seit dem letzten Ausgangsereignis vergangen ist. Dies verhindert effektiv ein sogenanntes "Event Flooding" (Ereignis-Überlastung) in verteilten Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- | :--- |
| **INIT** | EInit | Initialisiert den Baustein und setzt die Mindestzeitbegrenzung. | `Tmin` |
| **CLK** | Event | Taktsignal (Clock). Bei Eintreffen dieses Ereignisses wird der Wert am Eingang `D` ausgewertet. | `D`, `HYSTERESIS` |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- | :--- |
| **INITO** | EInit | Bestätigung der erfolgreichen Initialisierung. | Keine |
| **EO** | Event | Wird ausgelöst, wenn ein CLK-Ereignis eine gültige Änderung des Ausgangswerts `Q` bewirkt hat und die Mindestzeit `Tmin` abgelaufen ist. | `Q` |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
| :--- | :--- | :--- |
| **D** | ANY_NUM | Der zu speichernde Eingangswert (Data). |
| **HYSTERESIS** | ANY_NUM | Das Hystereseband. Bestimmt, wie stark sich `D` vom aktuellen Ausgangswert `Q` unterscheiden muss, um eine Änderung zu bewirken. |
| **Tmin** | TIME | Die minimale Zeitspanne, die zwischen zwei aufeinanderfolgenden `EO`-Ereignissen vergehen muss. |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
| :--- | :--- | :--- |
| **Q** | ANY_NUM | Der gespeicherte und gefilterte Ausgangswert (Latched Value). |

### **Adapter**

Dieser Funktionsbaustein verwendet keine Adapter.

## Funktionsweise

Der Baustein kombiniert intern zwei spezialisierte Funktionsbausteine:
1. Einen Hysterese-Speicherbaustein (`E_D_FF_ANY_HYS`)
2. Einen zeitlichen Ereignisbegrenzer (`E_TMIN`)

Sobald ein Ereignis am Eingang `CLK` eintrifft, liest der interne Baustein `E_D_FF_ANY_HYS` den aktuellen Wert von `D` ein.
- Liegt die Differenz zwischen dem neuen Wert `D` und dem aktuell gespeicherten Wert `Q` außerhalb des durch `HYSTERESIS` definierten Bereichs, wird `Q` mit dem neuen Wert aktualisiert und ein internes Ereignis an den Begrenzer `E_TMIN` weitergeleitet.
- Liegt die Änderung innerhalb des Hysteresebands, bleibt der Wert unverändert und es wird kein Ereignis weitergeleitet.

Der Baustein `E_TMIN` überwacht die Weiterleitung dieses Ereignisses an den Ausgang `EO`. Er stellt sicher, dass zwischen zwei `EO`-Ereignissen mindestens die Zeitspanne `Tmin` verstreicht. Schneller aufeinanderfolgende Ereignisse werden entsprechend verzögert oder gefiltert, um die nachfolgende Logik vor zu hoher Ereignislast zu schützen.

## Technische Besonderheiten

- **Generische Datentypen (`ANY_NUM`):** Durch die Verwendung des generischen Datentyps `ANY_NUM` für `D`, `HYSTERESIS` und `Q` ist der Baustein hochgradig wiederverwendbar und kann für verschiedene numerische Typen (z. B. `INT`, `REAL`, `LREAL`) eingesetzt werden.
- **Kombinierte Filterung:** Der Baustein vereint Amplitudenfilterung (Hysterese) und Zeitfilterung (Tmin) in einer einzigen Komponente.

## Zustandsübersicht

1. **Uninitialisiert:** Der Baustein wartet auf das Ereignis `INIT`.
2. **Initialisiert / Bereit:** Der Baustein hat `Tmin` konfiguriert und wartet auf Ereignisse am Eingang `CLK`.
3. **Wertänderung blockiert (Hysterese):** Ein `CLK`-Ereignis trifft ein, aber die Änderung von `D` ist zu gering. `Q` bleibt gleich, kein `EO`.
4. **Wertänderung aktiv (Zeitverzögerung/Filterung):** Ein `CLK`-Ereignis trifft ein und die Änderung ist groß genug. Wenn `Tmin` abgelaufen ist, wird `Q` aktualisiert und `EO` sofort ausgegeben. Falls `Tmin` noch aktiv ist, greift die Schutzfunktion des Zeitglieds.

## Anwendungsszenarien

- **Analoge Sensorwertverarbeitung:** Dämpfung und Rauschunterdrückung bei verrauschten analogen Messwerten (z. B. Temperatur, Druck oder Füllstand).
- **Netzwerkschonende Datenübertragung:** Reduzierung von Publish-Ereignissen in IoT- oder SCADA-Systemen (z. B. MQTT). Daten werden nur gesendet, wenn sich ein Wert signifikant geändert hat, jedoch maximal alle "X" Sekunden.
- **Ressourceneffizienz in SPS-Steuerungen:** Entlastung der CPU von zyklischen Berechnungen, die durch hochfrequente Signaländerungen getriggert würden.

## Vergleich mit ähnlichen Bausteinen

- **`E_D_FF`:** Speichert Werte direkt bei jedem Takt ohne Hysterese und Zeitbegrenzung. Führt bei unruhigen Signalen zu extrem hoher Ereignisdichte.
- **`E_D_FF_ANY_HYS`:** Besitzt zwar die Hysteresefunktion, bietet jedoch keinen Schutz vor schnellen, kontinuierlichen Signaländerungen (z. B. bei schnellen Rampen), die dennoch zu viele Ereignisse erzeugen würden. `E_D_FF_ANY_HYS_TMIN` löst dieses Problem durch die integrierte `Tmin`-Komponente.

## Fazit

Der `E_D_FF_ANY_HYS_TMIN` ist ein äußerst nützlicher Baustein zur Signalaufbereitung im industriellen Umfeld. Er verbindet eine wertbasierte Filterung mit einer zeitbasierten Ratenbegrenzung. Dadurch eignet er sich ideal für stabile Steuerungsarchitekturen, bei denen Sensorwerte präzise erfasst, aber nachfolgende Systeme vor Überlastung geschützt werden müssen.

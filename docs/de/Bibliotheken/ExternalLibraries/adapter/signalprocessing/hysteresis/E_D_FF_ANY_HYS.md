# E_D_FF_ANY_HYS


![E_D_FF_ANY_HYS](./E_D_FF_ANY_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `E_D_FF_ANY_HYS` ist ein flankengetriggertes D-Flip-Flop (Data Latch) für numerische Datentypen mit integrierter Hysterese. Er dient dazu, einen Eingangswert zu speichern (zu "latchen") und am Ausgang bereitzustellen. Eine Aktualisierung des Ausgangs und das Auslösen des Ausgangsereignisses erfolgen bei einem Taktsignal jedoch nur dann, wenn die Änderung des Eingangswerts im Vergleich zum aktuellen Ausgangswert die definierte Hysterese-Schwelle erreicht oder überschreitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **CLK**: Takt-Eingang (Clock). Bei Eintreffen dieses Ereignisses wird geprüft, ob sich der Eingangswert `D` im Vergleich zum aktuellen Ausgangswert `Q` um mindestens den Wert von `HYSTERESIS` geändert hat.

### **Ereignis-Ausgänge**

*   **EO**: Ereignis-Ausgang (Event Out). Wird ausgelöst, wenn ein Takt-Ereignis (`CLK`) zu einer tatsächlichen Wertänderung und Aktualisierung des Ausgangs `Q` geführt hat.

### **Daten-Eingänge**

*   **D** (`ANY_NUM`): Der aktuelle, einzulesende Datenwert.
*   **HYSTERESIS** (`ANY_NUM`): Das Hysterese-Band. Gibt die Mindestdifferenz an, die zwischen `D` und `Q` liegen muss, damit der Ausgang aktualisiert wird.

### **Daten-Ausgänge**

*   **Q** (`ANY_NUM`): Der gespeicherte (gelatchte) Wert.

### **Adapter**

*   *Keine Adapter vorhanden.*

## Funktionsweise

Der Funktionsbaustein arbeitet intern mit einer Execution Control Chart (ECC) und einem einfachen Zuweisungs-Algorithmus:

1.  **Initialisierung**: Beim ersten Start befindet sich der Baustein im Zustand `START`. Ein erstes `CLK`-Ereignis führt direkt in den Zustand `SET`. Dabei wird der Algorithmus `LATCH` ausgeführt, welcher den aktuellen Wert von `D` auf den Ausgang `Q` schreibt. Gleichzeitig wird das Ausgangsereignis `EO` gesendet.
2.  **Hysterese-Prüfung bei Folge-Ereignissen**: Befindet sich der Baustein im Zustand `SET`, führt jedes weitere `CLK`-Ereignis nur dann zu einer erneuten Ausführung von `SET` (und damit zur Aktualisierung von `Q` und dem Feuern von `EO`), wenn folgende Bedingung erfüllt ist:
    $$\lvert D - Q \rvert \ge \text{HYSTERESIS}$$
    In der ECC-Bedingung wird dies mathematisch über die Formel `GE(SUB(MAX(D, Q), MIN(D, Q)), HYSTERESIS)` realisiert. Dies entspricht der absoluten Differenz zwischen dem Eingangswert `D` und dem aktuell gespeicherten Wert `Q`.
3.  Ist die Differenz kleiner als der Wert von `HYSTERESIS`, wird das Ereignis ignoriert, der Ausgang `Q` bleibt unverändert und es wird kein `EO`-Ereignis ausgelöst.

## Technische Besonderheiten

*   **Generischer Datentyp**: Durch die Verwendung des Datentyps `ANY_NUM` für die Ein- und Ausgänge ist der Baustein hochgradig wiederverwendbar und kann mit verschiedenen numerischen Datentypen (z. B. `INT`, `REAL`, `LREAL`) verschaltet werden.
*   **Effiziente Differenzberechnung**: Die Differenzermittlung über `SUB(MAX(D, Q), MIN(D, Q))` stellt sicher, dass immer ein positiver Absolutwert für den Vergleich mit der Hysterese herangezogen wird, unabhängig davon, ob der neue Wert größer oder kleiner als der alte Wert ist.

## Zustandsübersicht

```
  [ START ] --( CLK )--> [ SET (Algorithmus: LATCH, Ausgang: EO) ]
                            |
                            +--( CLK [Differenz >= HYSTERESIS] )--> (erneuter Aufruf von SET)
```

*   **START**: Wartezustand vor dem ersten Takt.
*   **SET**: Zustand, in dem der Eingangswert übernommen und ausgegeben wird. Wird bei jedem gültigen Takt (unter Berücksichtigung der Hysterese) zyklisch wieder aufgerufen.

## Anwendungsszenarien

*   **Rauschfilterung für analoge Sensorwerte**: Reduzierung von Event-Fluten in verteilten Systemen. Wenn ein Sensor (z. B. Temperatursensor) kontinuierlich leicht schwankende Werte liefert, verhindert die Hysterese, dass bei minimalen Änderungen ständig neue Steuerungsereignisse im System verteilt werden.
*   **Grenzwertüberwachung mit Totband**: Vermeidung von prellenden Signalen bei der Übertragung von Prozesswerten an Visualisierungen (HMI) oder Datenbanken.

## Vergleich mit ähnlichen Bausteinen

*   **E_D_FF**: Das Standard-D-Flip-Flop reagiert meist auf boolescher Ebene oder speichert Werte bei jedem Takt bedingungslos ab. `E_D_FF_ANY_HYS` filtert die Werte zusätzlich durch die Hysterese-Bedingung.
*   **Hysterese-Bausteine (z.B. mit booleschem Ausgang)**: Typische Hysterese-Bausteine vergleichen einen Wert mit festen Schwellenwerten und liefern ein `BOOL`-Signal (z. B. Schwellwertschalter). `E_D_FF_ANY_HYS` hingegen gibt den numerischen Wert selbst weiter, sobald dieser sich signifikant geändert hat.

## Fazit

Der `E_D_FF_ANY_HYS` ist ein extrem nützlicher Baustein zur daten- und ereignisgesteuerten Signalverarbeitung. Er verbindet die Speicherfunktion eines D-Flip-Flops mit einer intelligenten Rausch- und Änderungsfilterung für numerische Signale und trägt so maßgeblich zur Optimierung der Performance und Reduzierung der Event-Last in IEC 61499 Anwendungen bei.
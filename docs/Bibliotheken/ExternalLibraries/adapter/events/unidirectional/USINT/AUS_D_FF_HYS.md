# AUS_D_FF_HYS


![AUS_D_FF_HYS](./AUS_D_FF_HYS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AUS_D_FF_HYS` realisiert ein Data-Latch (D-Flipflop) mit einer Hysterese (Schwellwertband). Er dient dazu, einen eingehenden Datenwert flankengesteuert zu übernehmen und am Ausgang bereitzustellen, wobei durch die Hysterese ein stabiles Schaltverhalten bei rauschenden oder schwankenden Eingangssignalen erreicht wird. Der Baustein verwendet generische Adapter (`AUS`), die eine unidirektionale Datenübertragung mit Ereignissteuerung ermöglichen, und ist damit für beliebige Datentypen einsetzbar.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Comment                        | Mit Parameter |
|----------|-------|--------------------------------|---------------|
| `INIT`   | EInit | Set Hysteresis                 | `HYSTERESIS`  |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Comment            |
|----------|-------|--------------------|
| `INITO`  | EInit | Init Confirmation  |

### **Daten-Eingänge**

| Name         | Typ   | Comment          |
|--------------|-------|------------------|
| `HYSTERESIS` | USINT | Hysteresis band  |

### **Daten-Ausgänge**

Der FB hat keine direkten Datenausgänge. Der latched Wert wird über den Adapterausgang `Q` bereitgestellt.

### **Adapter**

| Name | Typ                                          | Richtung | Comment        |
|------|----------------------------------------------|----------|----------------|
| `I`  | `adapter::types::unidirectional::AUS`        | Socket   | Value to latch |
| `Q`  | `adapter::types::unidirectional::AUS`        | Plug     | Latched value  |

Die Adapter sind unidirektional und enthalten jeweils ein Ereignis (`E1`) und einen Datenwert (`D1`). Über `I` wird der Eingangswert und dessen Übernahmeereignis empfangen, über `Q` wird der ausgegebene Wert und ein Bestätigungsereignis gesendet.

## Funktionsweise

Der FB kapselt einen internen Baustein `E_D_FF_ANY_HYS`, der das eigentliche D-Flipflop mit Hysterese implementiert.

- **Initialisierung:** Mit dem Ereignis `INIT` wird der Hysterese-Wert (`HYSTERESIS`) an den internen Baustein übergeben. Das Ereignis `INITO` quittiert die Initialisierung.
- **Datenübernahme:** Ein Ereignis auf `I.E1` veranlasst den internen Baustein, den aktuellen Datenwert von `I.D1` zu übernehmen und den gelatchten Wert an `Q.D1` weiterzugeben. Gleichzeitig wird `Q.E1` ausgelöst.
- **Hysteresefunktion:** Der Ausgang des Flipflops ändert seinen Zustand nur dann, wenn der Eingangswert eine obere oder untere Schwelle überschreitet, die durch den Hysterese-Wert definiert ist. Dadurch wird ein Prellen oder Rauschen des Eingangssignals unterdrückt (Schmitt-Trigger-Verhalten).

Die genaue Schaltschwelle hängt vom verwendeten Datentyp des Adapters ab (der Adapter `AUS` unterstützt beliebige Typen). Der Hysterese-Wert (`USINT`) wird intern auf den entsprechenden Zahlenbereich skaliert oder interpretiert.

## Technische Besonderheiten

- **Generischer Adapter:** Die Verwendung des unidirektionalen Adapters `AUS` erlaubt den Einsatz mit unterschiedlichsten Datentypen (z. B. `INT`, `REAL`, `BOOL`), ohne dass der FB selbst typisiert werden muss. Die Typanpassung erfolgt durch den internen Baustein.
- **Hysterese als USINT:** Die Hysterese wird als vorzeichenloser 8‑Bit‑Wert angegeben. Die konkrete Interpretation (z. B. als absolute Differenz oder prozentualer Anteil) ist implementierungsabhängig und liegt im internen Baustein.
- **Ereignis-Passthrough:** Das INIT-Ereignis wird direkt an das INITO-Ereignis durchgeschleift. Dies ermöglicht eine einfache Initialisierungskette im Netzwerk.
- **Keine Zustandsmaschine sichtbar:** Der FB besitzt kein eigenes ECC (Execution Control Chart); die Logik wird vollständig durch den internen FB realisiert.

## Zustandsübersicht

Da der FB keine explizite Zustandsmaschine offenlegt, ergibt sich das Verhalten aus dem internen D-Flipflop mit Hysterese. Dieses besitzt zwei stabile Ausgangszustände:

- **Zustand 0:** Ausgangswert entspricht dem logischen „Low“-Niveau (bzw. dem unteren Grenzwert des Datenbereichs).
- **Zustand 1:** Ausgangswert entspricht dem logischen „High“-Niveau (bzw. dem oberen Grenzwert).

Zustandsübergänge erfolgen nur bei Überschreiten der jeweiligen Hystereseschwellen:

| Übergang | Bedingung (Eingangswert)                     |
|----------|----------------------------------------------|
| 0 → 1    | Eingang überschreitet obere Schwelle         |
| 1 → 0    | Eingang unterschreitet untere Schwelle        |

Die Schwellen sind um den Hysterese-Wert gegenüber einem Mittelwert oder Referenzwert versetzt (typischerweise obere Schwelle = Referenz + Hysterese/2, untere Schwelle = Referenz - Hysterese/2).

## Anwendungsszenarien

- **Entprellung von Sensoren:** Ein digitaler oder analoger Sensor liefert schwankende Werte (z. B. durch mechanisches Prellen). Der FB glättet das Signal und gibt einen stabilen Ausgang.
- **Schwellwertschalter mit Rücksetzverzögerung:** Überwachung eines Prozesswertes, der bei Überschreiten eines oberen Grenzwertes ein Signal auslöst und erst beim Unterschreiten eines tieferen Grenzwertes wieder zurückgesetzt wird.
- **Signalaufbereitung in der Gebäudeautomatisierung:** Unterdrückung kurzer Störimpulse bei Temperatur-, Helligkeits- oder Füllstandssensoren.
- **Hysterese in Lagereglern:** Verhindern schnelles Ein- und Ausschalten von Aktoren nahe einer Sollwertgrenze.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften | Unterschied zu `AUS_D_FF_HYS` |
|----------|---------------|-------------------------------|
| Standard-D-Flipflop (`E_D_FF`) | Übernimmt Daten bei Taktflanke, keine Hysterese | Keine Rauschunterdrückung; Zustandswechsel bei jeder Flanke. |
| Schmitt-Trigger (`E_D_FF_ANY_HYS`) | Flipflop mit Hysterese, aber meist datentypspezifisch | `AUS_D_FF_HYS` kapselt den generischen Adapter und bietet eine einheitliche Schnittstelle für beliebige Typen. |
| SR-Flipflop (`E_SR_FF`) | Set-/Reset-Funktion ohne Takt | Keine flankengesteuerte Datenübernahme; Hysterese nicht direkt integriert. |

## Fazit

`AUS_D_FF_HYS` ist ein vielseitiger Funktionsblock für Anwendungen, die eine robuste, flankengesteuerte Datenübernahme mit Hysterese erfordern. Der Einsatz generischer Adapter macht ihn unabhängig vom konkreten Datentyp und erleichtert die Wiederverwendung in unterschiedlichen Kontexten. Besonders in der Automatisierungstechnik, Signalverarbeitung und Sensorauswertung bietet er durch die Unterdrückung von Rauschen und Prellen eine zuverlässige Signalaufbereitung. Die Initialisierung über `INIT` und die direkte Durchleitung des Ereignisses vereinfachen die Einbindung in bestehende Steuerungsnetzwerke.
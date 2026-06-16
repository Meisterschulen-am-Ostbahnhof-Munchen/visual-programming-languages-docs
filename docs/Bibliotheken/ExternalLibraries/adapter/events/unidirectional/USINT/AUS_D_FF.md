# AUS_D_FF


![AUS_D_FF](./AUS_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUS_D_FF** realisiert ein Data Latch (D‑Flip‑Flop) für den Datentyp `AUS`. Er speichert bei einem eingehenden Ereignis den anliegenden Datenwert und gibt diesen gespeicherten Wert über einen Adapter‑Ausgang aus. Die Kommunikation erfolgt ausschließlich über unidirektionale Adapter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Die ereignisgesteuerte Datenübernahme erfolgt über den Adapter‑Eingang **I** (siehe Abschnitt Adapter).

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Die Ausgabe des gespeicherten Wertes wird über den Adapter‑Ausgang **Q** signalisiert (siehe Abschnitt Adapter).

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Die zu speichernden Daten werden über den Adapter‑Eingang **I** bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der gespeicherte Wert wird über den Adapter‑Ausgang **Q** ausgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **I** | Socket | `adapter::types::unidirectional::AUS` | Liefert das zu latchende Signal (Ereignis E1 und Daten D1). |
| **Q** | Plug | `adapter::types::unidirectional::AUS` | Gibt den gelatchten Wert aus (Ereignis E1 und Daten D1). |

Der intern verwendete Baustein `E_D_FF_ANY` erwartet an seinem **CLK**‑Eingang ein Ereignis (übernommen von **I.E1**) und an **D** den Datenwert (von **I.D1**). Das ausgegebene Ereignis **EO** wird an **Q.E1** weitergeleitet, der gespeicherte Datenwert **Q** an **Q.D1**.

## Funktionsweise
Sobald am Adapter‑Eingang **I** ein Ereignis eintrifft (Pin **E1**), wird der gleichzeitig anliegende Datenwert (Pin **D1**) in den internen Speicher übernommen. Nach erfolgreicher Übernahme wird ein Ereignis am Adapter‑Ausgang **Q** (Pin **E1**) ausgelöst und der gespeicherte Wert steht an **Q.D1** zur Verfügung. Der gespeicherte Wert bleibt solange erhalten, bis ein neues Ereignis an **I.E1** einen neuen Wert übernimmt.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle:** Der Baustein verwendet ausschließlich unidirektionale Adapter, was eine lose Kopplung und flexible Verschaltung ermöglicht.
- **Keine eigenen Ereignis-/Daten-Pins:** Die gesamte Ein‑ und Ausgabe erfolgt über die Adapter **I** und **Q**.
- **Interner Standard‑Flip‑Flop:** Die eigentliche Latch‑Funktionalität wird vom IEC‑61499‑Baustein `E_D_FF_ANY` bereitgestellt, der spezifiziert ist, auf ein beliebiges Datentyp‑Template zu arbeiten.

## Zustandsübersicht
Der Baustein besitzt einen impliziten internen Zustand – den gespeicherten Datenwert (`Q`‑Ausgang). Dieser ändert sich nur bei einem Ereignis an **I.E1**. Es gibt keine explizite Zustandsmaschine im FBNetz; der Zustand wird durch den internen `E_D_FF_ANY` verwaltet.

## Anwendungsszenarien
- **Zwischenspeicherung:** Ein Signal (Wert + Ereignis) soll für eine spätere Verarbeitung zwischengespeichert werden, z. B. in einem Steuerungsablauf, bei dem ein Sensorwert erst bei einem bestimmten Takt übernommen werden soll.
- **Datensynchronisation:** Ein asynchron ankommender Datenwert wird synchron zu einem Ereignis gelatcht und dann im weiteren Programmfluss verwendet.
- **Zustandshaltung:** Der Baustein merkt sich den letzten gültigen Wert, bis ein neuer Wert explizit übernommen wird.

## Vergleich mit ähnlichen Bausteinen
- **SR‑Flip‑Flop:** Setzt oder rückgesetzt den Ausgang über separate Set‑/Reset‑Eingänge; speichert nur boolesche oder binäre Zustände. `AUS_D_FF` hingegen speichert allgemeine Datenwerte vom Typ `AUS`.
- **Toggle‑Flip‑Flop (T‑FF):** Wechselt den Ausgang bei jedem Takt. `AUS_D_FF` übernimmt den aktuellen Datenwert und gibt ihn unverändert aus.
- **MUX‑basiertes Latch:** Ein Multiplexer könnte ebenfalls einen Wert speichern, benötigt aber zusätzliche Rücksetzlogik. `AUS_D_FF` kapselt diese Logik bereits.

## Fazit
Der **AUS_D_FF** ist ein einfach zu verwendender Latch‑Baustein, der über Adapter ein Datenwert‑Ereignis‑Paar übernimmt und gespeichert weitergibt. Aufgrund der Adapter‑Schnittstelle und der Nutzung eines standardisierten internen Flip‑Flops eignet er sich für modulare und wiederverwendbare Steuerungsentwürfe in der IEC‑61499‑Umgebung.
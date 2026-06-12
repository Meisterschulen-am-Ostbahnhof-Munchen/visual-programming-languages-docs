# ALR_D_FF_HYS


![ALR_D_FF_HYS](./ALR_D_FF_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALR_D_FF_HYS** realisiert ein Data‑Latch (D‑Flip‑Flop) mit einer einstellbaren Hysterese. Er empfängt einen Datenwert über einen Adapter‑Socket und gibt den gelatchten Wert über einen Adapter‑Plug aus. Die Hysterese wird beim Initialisierungsereignis gesetzt und dient der Unterdrückung von Rauschen oder kleinen Schwankungen im Eingangssignal.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Event | Typ | Beschreibung |
|-------|-----|--------------|
| INIT  | EInit | Setzt die Hysterese (mit dem Datenwert `HYSTERESIS`) und startet die Initialisierung. |

### **Ereignis-Ausgänge**

| Event  | Typ | Beschreibung |
|--------|-----|--------------|
| INITO  | EInit | Bestätigt die erfolgreiche Initialisierung. |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| HYSTERESIS | LREAL | Größe des Hysterese‑Bandes (wird beim `INIT`‑Event übernommen). |

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten‑Ausgänge. Der gelatchte Wert wird ausschließlich über den Adapter‑Plug `Q` ausgegeben.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| I (Socket) | `adapter::types::unidirectional::ALR` | Eingang | Empfängt den zu latchnden Wert über das Ereignis `I.E1` und den zugehörigen Datenwert `I.D1`. |
| Q (Plug)   | `adapter::types::unidirectional::ALR` | Ausgang | Gibt den gelatchten Wert über das Ereignis `Q.E1` und den Datenwert `Q.D1` aus. |

Der verwendete Adapter **ALR** ist ein unidirektionaler Daten‑Adapter mit einem Ereignis (`E1`) und einem Datenwert (`D1`).

## Funktionsweise

Der FB arbeitet intern mit dem Baustein `E_D_FF_ANY_HYS`, der die eigentliche Latch‑ und Hysterese‑Logik implementiert. Die Abläufe sind:

1. **Initialisierung**: Beim Eintreffen von `INIT` wird der Wert von `HYSTERESIS` an den internen Baustein weitergeleitet und das Ausgangsereignis `INITO` sofort bestätigt.
2. **Latch‑Vorgang**: Bei jeder positiven Flanke des Ereignisses `I.E1` (vom Socket) wird der aktuelle Datenwert `I.D1` übernommen. Der gelatchte Wert wird jedoch erst ausgegeben, wenn er das durch die Hysterese bestimmte Band verlässt. Dadurch werden kleine Änderungen um den aktuellen Latch‑Wert unterdrückt.
3. **Ausgabe**: Sobald der gelatchte Wert das Hysterese‑Band verlässt, erzeugt der interne Baustein ein Ereignis auf `EO`, welches als `Q.E1` nach außen gegeben wird, und der neue Wert steht auf `Q.D1` zur Verfügung.

## Technische Besonderheiten

- Die Hysterese wird ausschließlich beim `INIT`‑Ereignis gesetzt und bleibt während des Betriebs konstant.
- Der FB verwendet keinen eigenen Zustandsautomat, sondern delegiert die gesamte Logik an den internen Baustein `E_D_FF_ANY_HYS`.
- Der initiale Zustand des Latch ist nicht definiert; eine Initialisierung mit `INIT` ist zwingend erforderlich, bevor gültige Latch‑Vorgänge stattfinden können.

## Zustandsübersicht

Da der FB das Verhalten über einen internen Baustein realisiert, ergibt sich kein eigenständiges Zustandsdiagramm. Der interne Baustein `E_D_FF_ANY_HYS` arbeitet typischerweise mit folgenden Zuständen:

- **Initial** – Warten auf die Hysterese‑Einstellung.
- **Normal** – Latch‑Betrieb mit Prüfung des Hysterese‑Bandes (verzögerte Aktualisierung des Ausgangs).
- **Ausgabe** – Senden des neuen gelatchten Wertes über den Ausgangs‑Adapter.

## Anwendungsszenarien

- **Signalaufbereitung**: Latch von Messwerten mit Rauschunterdrückung in der Automatisierungstechnik.
- **Entprellung**: Verarbeitung von Schaltsignalen, bei denen kurze Impulse oder Prellen unterdrückt werden sollen.
- **Schwellwertüberwachung**: Erfassung analoger Werte, die nur ober‑ oder unterhalb eines Hysterese‑Bandes einen neuen gültigen Zustand annehmen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| Einfaches D‑Flip‑Flop (z. B. `E_D_FF`) | Latch ohne Hysterese – jede Änderung am Eingang wird sofort übernommen. |
| D‑Flip‑Flop mit Totband (`E_D_FF_TOTBAND`) | Hat ein Totband, das Änderungen blockiert, solange der Wert innerhalb des Bandes bleibt. |
| **ALR_D_FF_HYS** | Hysterese wird nur in einer Richtung wirksam (Schwellwertverhalten), typisch zur Vermeidung von Flattern. |

## Fazit

Der ALR_D_FF_HYS ist ein spezialisierter Funktionsblock für Anwendungen, bei denen ein Datenwert gelatcht und gleichzeitig eine Hysterese zur Störunterdrückung angewendet werden soll. Die Kapselung der Logik in einen internen Baustein hält die Schnittstelle einfach und ermöglicht eine flexible Nutzung über die Adapter‑Schnittstelle.
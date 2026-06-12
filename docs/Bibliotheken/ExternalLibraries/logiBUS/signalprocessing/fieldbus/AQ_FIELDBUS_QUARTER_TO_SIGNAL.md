# AQ_FIELDBUS_QUARTER_TO_SIGNAL


![AQ_FIELDBUS_QUARTER_TO_SIGNAL](./AQ_FIELDBUS_QUARTER_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AQ_FIELDBUS_QUARTER_TO_SIGNAL** dient dazu, ein über einen Feldbusadapter eingehendes Signal (vom Typ `AQ`) auf einen Ausgangsadapter zu spiegeln – jedoch nur, wenn das Signal als gültig (valid) gekennzeichnet ist. Er kombiniert einen feldbusspezifischen Verarbeitungsbaustein mit einem flankengesteuerten D-Flipflop, um den Gültigkeitsstatus zu puffern und als separates Ausgangssignal bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge auf oberster Ebene. Stattdessen werden Ereignisse über den **Socket-Adapter `IN`** (Typ `AQ`) bereitgestellt. Der Ereignisausgang `IN.E1` startet die Verarbeitung des eingehenden Signals.

### **Ereignis-Ausgänge**

Auch Ereignis-Ausgänge werden ausschließlich über die **Plug-Adapter `OUT`** und `VALID` geführt:

- **`OUT.E1`**: Wird nach erfolgreicher Spiegelung des Signals ausgelöst. (Ergebnis liegt am Datenausgang `OUT.D1` an.)
- **`VALID.E1`**: Wird ausgelöst, sobald der Gültigkeitsstatus des Signals aktualisiert wurde (steigende Flanke des internen D-Flipflops).

### **Daten-Eingänge**

Daten werden ebenfalls über den **Socket-Adapter `IN`** übernommen:

- **`IN.D1`**: Empfängt das analoge oder digitale Eingangssignal (Typ des Adapters `AQ`).

### **Daten-Ausgänge**

- **`OUT.D1`**: Gibt das gespiegelte Eingangssignal aus – aber nur, wenn es als gültig erkannt wurde. (Bei ungültigem Signal kann ein definierter Wert oder letzter gültiger Wert ausgegeben werden; dies hängt von der internen Implementierung von `FIELDBUS_QUARTER_TO_SIGNAL` ab.)
- **`VALID.D1`**: Gibt den aktuellen Gültigkeitsstatus aus (`TRUE` = gültig, `FALSE` = ungültig). Dieser Wert ist das Ausgangssignal `Q` des D-Flipflops.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AQ` | **Socket** (Eingang) | Feldbussignal (Ereignis und Daten) |
| `OUT` | `adapter::types::unidirectional::AQ` | **Plug** (Ausgang) | Gefiltertes / gespiegeltes Ausgangssignal |
| `VALID` | `adapter::types::unidirectional::AX` | **Plug** (Ausgang) | Gültigkeitsstatus des Signals |

Hinweis: Die Adaptertypen `AQ` und `AX` sind eindirektionale Protokolle, die üblicherweise ein Ereignis‑ und ein Datenfeld kombinieren.

## Funktionsweise

Der Baustein arbeitet wie folgt:

1. Ein eingehendes Ereignis auf `IN.E1` triggert den internen Funktionsbaustein **`FIELDBUS_QUARTER_TO_SIGNAL`** (Aufruf über `REQ`).
2. Dieser interne Baustein verarbeitet den Datenwert (`IN.D1`) und erzeugt zwei Ausgaben:
   - **`OUT`** – das aufbereitete Signal (z. B. gespiegelt, normiert, gefiltert).
   - **`VALID`** – ein Boolescher Wert (`TRUE`, wenn das Signal gültig ist).
3. Das verarbeitete Signal wird direkt an den Ausgangsadapter `OUT` weitergeleitet (über `OUT.D1`) und gleichzeitig das Ereignis `OUT.E1` ausgelöst.
4. Der Gültigkeitsstatus (`VALID`) wird dem D‑Eingang eines flankengesteuerten D‑Flipflops (`E_D_FF`) zugeführt. Die Taktflanke wird durch dasselbe Ereignis (`CNF`) erzeugt, das auch `OUT.E1` triggert. Somit wird der Gültigkeitsstatus bei jedem Zyklus in das Flipflop übernommen.
5. Der Flipflop-Ausgang `Q` wird über den Adapter `VALID.D1` ausgegeben. Das dazugehörige Ereignis `VALID.E1` wird durch den Flipflop-Ausgang `EO` ausgelöst.

Der Baustein stellt sicher, dass das Ausgangssignal stets mit dem aktuell verarbeiteten Gültigkeitsstatus synchronisiert ist.

## Technische Besonderheiten

- Der Baustein ist als **Komposition** zweier interner Funktionsbausteine realisiert: `FIELDBUS_QUARTER_TO_SIGNAL` und `E_D_FF`. Dies bietet eine hohe Wiederverwendbarkeit und klare Trennung von Verarbeitungslogik und Zustandsspeicherung.
- Die Verwendung eines **D‑Flipflops** puffert den Gültigkeitsstatus zwischen den Ereigniszyklen. Dadurch bleibt der Status auch dann erhalten, wenn das Eingangssignal zwischenzeitlich ausfällt.
- Die Adapter‑Schnittstellen folgen dem **unidirektionalen** Muster, das für Feldbusprotokolle typisch ist. Ein Ereignis transportiert sowohl einen Datenwert als auch eine Ausführungsflanke.
- Die interne Verarbeitung (`FIELDBUS_QUARTER_TO_SIGNAL`) kann je nach Anwendung angepasst werden (z. B. Skalierung, Formatierung oder Plausibilitätsprüfung), ohne die äußere Schnittstelle zu ändern.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen sichtbaren Zustandsautomaten. Der innere Zustand wird maßgeblich durch das **D‑Flipflop** bestimmt:

- **Zustand 0**: Flipflop‑Ausgang `Q = FALSE` → Signal gilt als **ungültig**.
- **Zustand 1**: Flipflop‑Ausgang `Q = TRUE` → Signal gilt als **gültig**.

Der Zustandswechsel erfolgt taktflankengesteuert bei jedem Verarbeitungszyklus (Ereignis auf `IN.E1`). Der aktuelle Zustand ist über den Adapter `VALID.D1` ablesbar.

## Anwendungsszenarien

- **Feldbusanbindung in der Landtechnik**: Übernahme eines analogen Sensorsignals (z. B. Drehmoment, Druck) von einem Feldbus, das nur bei gültiger Kommunikation weitergegeben wird.
- **Signalqualitätsfilterung**: Einbindung in eine Kette von Verarbeitungsbausteinen, bei der nur als gültig markierte Werte in die Regelung oder Visualisierung einfließen.
- **Redundanzprüfung**: Kombination mit einem zweiten Signalweg, wobei der Gültigkeitsstatus als Umschaltkriterium dient.

## Vergleich mit ähnlichen Bausteinen

- **`AQ_FIELDBUS_SIGNAL_TO_QUARTER`** (hypothetisch): Würde den umgekehrten Weg – Umwandlung eines allgemeinen Signals in ein Feldbusformat – abbilden.
- **`AQ_BUFFER`**: Ein reiner Puffer ohne Gültigkeitsprüfung; der vorliegende Baustein erweitert diese Funktion um eine Validierung und Zustandsspeicherung.
- **`AQ_SELECT`**: Wählt zwischen zwei Eingängen aus; im vorliegenden Baustein wird stattdessen die Gültigkeit eines einzelnen Signals bewertet.

## Fazit

**AQ_FIELDBUS_QUARTER_TO_SIGNAL** ist ein kompakter, adapterbasierter Funktionsbaustein zur zuverlässigen Spiegelung von Feldbussignalen unter Berücksichtigung der Signalvalidität. Durch die Kombination von Verarbeitungslogik und ﬂankengesteuertem Zustandsspeicher eignet er sich besonders für sicherheitskritische oder qualitätsüberwachte Anwendungen im industriellen Umfeld. Die klare Trennung der internen Komponenten erleichtert Wartung und Anpassung.
# AULI_D_FF_HYS


![AULI_D_FF_HYS](./AULI_D_FF_HYS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AULI_D_FF_HYS` realisiert ein Data-Latch (D-Flipflop) mit einstellbarer Hysterese. Er kapselt die Logik eines solchen Flipflops in einer adapterbasierten Schnittstelle und erlaubt die Weitergabe von Daten und Ereignissen über unidirektionale Adapter vom Typ `AULI`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- `INIT` (EInit): Setzt den Hysteresewert und initialisiert den Baustein.

### **Ereignis-Ausgänge**
- `INITO` (EInit): Bestätigt den erfolgreichen Initialisierungsvorgang (durchgeschleiftes INIT).

### **Daten-Eingänge**
- `HYSTERESIS` (ULINT): Legt die Hysteresebreite fest. Der Wert wird beim INIT-Ereignis übernommen.

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden; die Ausgabedaten werden über den Adapter `Q` bereitgestellt.

### **Adapter**
- **Socket `I`** (Typ `adapter::types::unidirectional::AULI`): Empfängt den zu latchnden Wert und das zugehörige Taktsignal.
- **Plug `Q`** (Typ `adapter::types::unidirectional::AULI`): Gibt den gelatchten Wert und das Ausgangsereignis weiter.

## Funktionsweise
Der Baustein verwendet intern den Sub-Baustein `E_D_FF_ANY_HYS`. Über den Socket `I` wird das Taktsignal (`I.E1`) an den CLK-Eingang und der Datenwert (`I.D1`) an den D-Eingang des Sub-Bausteins geführt. Der Daten-Eingang `HYSTERESIS` wird direkt mit dem gleichnamigen Eingang des Sub-Bausteins verbunden. Der Ausgang `Q` des Sub-Bausteins wird auf den Datenausgang des Plugs `Q` (`Q.D1`) übertragen, und das Ereignis `EO` des Sub-Bausteins wird auf das Ausgangsereignis des Plugs `Q` (`Q.E1`) gelegt.

Das INIT-Ereignis wird unverändert als INITO durchgeschleift. Die eigentliche Initialisierung der Hysterese erfolgt durch den Sub-Baustein beim Empfang von INIT, wobei der aktuelle Wert von `HYSTERESIS` übernommen wird.

Die Hysterese verhindert ein sofortiges Umschalten des Ausgangs bei kleinen Schwankungen des Eingangssignals. Erst wenn der Eingangswert den gelatchten Wert um mehr als das Hystereseband über- oder unterschreitet, wird ein neuer Wert übernommen.

## Technische Besonderheiten
- Der Baustein ist als reines Zusammenspiel von Adaptern und einem Sub-Baustein definiert (keine eigene ECC- oder SIFB-Logik).
- Die Verwendung des Adapter-Typs `AULI` (unidirektional) erlaubt eine klare Trennung von Daten und Ereignissen in einer standardisierten Schnittstelle.
- Die Hysterese wird nur beim INIT-Ereignis gesetzt, danach bleibt der Wert für die Dauer des Betriebs konstant.
- Der Baustein ist unter der Eclipse Public License 2.0 verfügbar und in der IEC 61499-Annex-A-Standardstruktur definiert.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Die gesamte Zustandslogik ist im Sub-Baustein `E_D_FF_ANY_HYS` implementiert, der vermutlich zwei Zustände (latch setzen, Hysterese prüfen) realisiert.

## Anwendungsszenarien
- **Entprellung von Sensoren oder Schaltern**: Ein rauschbehaftetes digitales Signal wird nur dann als stabiler Wert übernommen, wenn es das Hystereseband überschreitet.
- **Signalglättung**: Kleine Fluktuationen eines gemessenen Werts werden unterdrückt, während signifikante Änderungen sofort durchgereicht werden.
- **Datensicherung in asynchronen Systemen**: Der Baustein dient als zuverlässiger Puffer zwischen einer Signalquelle und einer nachfolgenden Verarbeitungseinheit.

## Vergleich mit ähnlichen Bausteinen
- Ein einfaches D-Flipflop (z.B. `E_D_FF`) übernimmt den Eingangswert bei jeder steigenden Flanke ohne Hysterese. `AULI_D_FF_HYS` erweitert dies um eine konfigurierbare Schaltschwelle.
- Im Vergleich zu einem Schmitt-Trigger-Baustein liegt der Fokus hier auf dem Latch-Verhalten mit zusätzlicher Hysterese, nicht auf der Pegelumsetzung.

## Fazit
Der `AULI_D_FF_HYS` ist ein kompakter, adapterbasierter Funktionsbaustein für die zuverlässige Signalaufbereitung mit Hysterese. Durch die Delegation der Logik an einen spezialisierten Sub-Baustein bleibt das Design wartbar und erweiterbar. Er eignet sich besonders für Anwendungen, bei denen Rauschen oder unstete Eingangssignale gefiltert werden müssen, ohne auf ein einfaches Flipflop verzichten zu können.
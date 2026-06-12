# AL_TO_AX


![AL_TO_AX](./AL_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AL_TO_AX` ist ein Composite-Baustein, der eine unidirektionale Adapterkonvertierung von einem `AL`-Adapter (Datentyp `LWORD`) zu einem `AX`-Adapter (Datentyp `BOOL`) durchführt. Er ermöglicht die einfache Umwandlung eines LWORD-Signals in ein boolesches Signal, das dann typischerweise an nachfolgende BOOL-basierte Adapter oder Funktionsblöcke weitergegeben wird. Der Baustein prüft, ob der eingehende LWORD-Wert ungleich Null ist, und liefert als Ergebnis `TRUE`, wenn dies zutrifft.

## Schnittstellenstruktur
Der Funktionsblock besitzt keine eigenen Ereignis- oder Datenein-/ausgänge, sondern verwendet ausschließlich Adapter-Schnittstellen:

*   **Socket (Eingang):** `AL_IN` – Empfängt einen `AL`-Adapter (enthält ein LWORD und ein Ereignis).
*   **Plug (Ausgang):** `AX_OUT` – Stellt einen `AX`-Adapter (enthält ein BOOL und ein Ereignis) bereit.

Die internen Verbindungen werden über die Adapter-Elemente abgewickelt:

### **Ereignis-Eingänge**
(über den AL_IN-Adapter)
*   **`AL_IN.E1`** – Ereigniseingang; löst die Konvertierung aus.

### **Ereignis-Ausgänge**
(über den AX_OUT-Adapter)
*   **`AX_OUT.E1`** – Ereignisausgang; signalisiert den Abschluss der Konvertierung.

### **Daten-Eingänge**
(über den AL_IN-Adapter)
*   **`AL_IN.D1`** (`LWORD`) – Der umzuwandelnde LWORD-Wert.

### **Daten-Ausgänge**
(über den AX_OUT-Adapter)
*   **`AX_OUT.D1`** (`BOOL`) – Das Ergebnis der Umwandlung: `TRUE`, wenn `AL_IN.D1 ≠ 0`; andernfalls `FALSE`.

### **Adapter**
- **AL_IN** – Socket für den `adapter::types::unidirectional::AL`-Adapter (LWORD-basiert)
- **AX_OUT** – Plug für den `adapter::types::unidirectional::AX`-Adapter (BOOL-basiert)

## Funktionsweise
Der Baustein arbeitet intern mit dem Funktionsblock `F_NE` („ungleich“) aus der IEC 61131-Bibliothek. Dieser vergleicht den eingehenden LWORD-Wert (`AL_IN.D1`) mit dem Konstantwert `LWORD#0`. Wenn die Werte ungleich sind, liefert `F_NE.OUT` den Wert `TRUE`, sonst `FALSE`.

Die ereignisgesteuerte Abfolge ist:
1. Ein Ereignis an `AL_IN.E1` triggert den Eingang `F_NE.REQ`.
2. `F_NE` führt den Vergleich durch und legt das Ergebnis an `F_NE.OUT` an.
3. Nach Abschluss sendet `F_NE` ein Ereignis an `F_NE.CNF`, das mit `AX_OUT.E1` verbunden ist.
4. Gleichzeitig wird das Ergebnis `F_NE.OUT` auf `AX_OUT.D1` übertragen.

Somit wird bei jedem Ereignis am Eingang eine aktualisierte boolesche Ausgabe am Ausgang bereitgestellt.

## Technische Besonderheiten
- **Typkonvertierung:** Der Baustein wandelt einen LWORD-Wert nicht bitweise, sondern als Ganzzahl in einen BOOL-Wert um. Jeder von Null verschiedene LWORD ergibt `TRUE`.
- **Adapterbasiert:** Durch die Verwendung der standardisierten unidirektionalen Adapter (`AL` und `AX`) ist der Baustein in beliebigen 4diac-Netzwerken einsetzbar, die diese Adaptertypen unterstützen.
- **Latenz:** Die Verarbeitung erfolgt synchron zum Eingangsereignis. Die Ausgabe wird im selben Ausführungszyklus aktualisiert.
- **Keine Zustandsspeicherung:** Der Baustein ist rein kombinatorisch; er speichert keine Werte zwischen zwei Aufrufen.

## Zustandsübersicht
Der `AL_TO_AX`-Baustein besitzt keinen eigenen Zustandsautomaten. Sein Verhalten ist rein datenflussgesteuert durch das eingehende Ereignis. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien
- **Schwellwertdetektion:** Umwandlung eines LWORD-Sensorsignals (z. B. Zählerstand, Bitmaske) in ein boolesches Signal, das anzeigt, ob ein Wert ungleich Null anliegt.
- **Kopplung von LWORD- und BOOL-Adaptern:** In heterogenen Systemen, in denen ein Funktionsblock einen LWORD-basierten Adapter bereitstellt, der nächste Block jedoch einen BOOL-Adapter erwartet.
- **Fehlererkennung:** Ein LWORD-Fehlerregister (z. B. 0 = kein Fehler, ≠0 = Fehler) wird in ein einfaches BOOL-Signal „Fehler vorhanden“ übersetzt.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Konvertierer (z. B. `LWORD_TO_BOOL`):** Diese wandeln meist nur das niederwertigste Bit oder definieren ein festes Bit. Der `AL_TO_AX`-Baustein nutzt hingegen den Vergleich mit Null, sodass jedes beliebige gesetzte Bit oder ein von Null verschiedener Wert als `TRUE` interpretiert wird.
- **Adapter-Konverter:** Es gibt generische Adapterumsetzer, die mit verschiedenen Datentypen umgehen (z. B. `ANY_TO_BOOL`). Der spezialisierte `AL_TO_AX`-Baustein ist auf die genannte Adapterkombination zugeschnitten und erfordert keine externe Parametrierung.

## Fazit
Der `AL_TO_AX`-Funktionsblock bietet eine einfache und zuverlässige Möglichkeit, einen unidirektionalen LWORD-basierten Adapter in einen BOOL-basierten Adapter zu konvertieren. Durch die Verwendung des Vergleichs mit Null ist die Interpretation eindeutig. Die Integration in bestehende 4diac-Netzwerke gestaltet sich dank der standardisierten Adapter-Schnittstellen unkompliziert. Der Baustein eignet sich besonders für schnelle, ereignisgesteuerte Umwandlungen ohne zusätzlichen Speicherbedarf und ist eine praktische Ergänzung für die Adapterkonvertierung in der industriellen Automatisierung.
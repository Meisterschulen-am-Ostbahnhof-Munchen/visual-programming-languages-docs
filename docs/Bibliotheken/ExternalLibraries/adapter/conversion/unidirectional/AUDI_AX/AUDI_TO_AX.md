# AUDI_TO_AX


![AUDI_TO_AX](./AUDI_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUDI_TO_AX` ist ein Composite-FB, der einen **AUDI**-Adapter (UDINT-Daten) in einen **AX**-Adapter (BOOL-Daten) umwandelt. Er dient als unidirektionaler Konverter für Anwendungen, bei denen ein ganzzahliger Wert (z.B. aus einem Zähler) auf ein binäres Signal abgebildet werden soll – konkret wird geprüft, ob der Eingangswert ungleich Null ist. Der FB ist als reine Netzwerkverbindung aus IEC‑61131-konformen Bausteinen realisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine eigenen Ereignis-Eingänge. Das Ereignis zum Starten der Verarbeitung wird über den Socket-Adapter `AUDI_IN` bereitgestellt (siehe Abschnitt Adapter).

### **Ereignis-Ausgänge**
Der FB besitzt keine eigenen Ereignis-Ausgänge. Das Ergebnisereignis wird über den Plug-Adapter `AX_OUT` nach außen gegeben (siehe Abschnitt Adapter).

### **Daten-Eingänge**
Der FB besitzt keine eigenen Daten-Eingänge. Der zu verarbeitende UDINT-Wert wird über den Socket-Adapter `AUDI_IN` bereitgestellt (siehe Abschnitt Adapter).

### **Daten-Ausgänge**
Der FB besitzt keine eigenen Daten-Ausgänge. Das Ergebnis (BOOL) wird über den Plug-Adapter `AX_OUT` nach außen gegeben (siehe Abschnitt Adapter).

### **Adapter**
| Name | Typ | Typ des Adapters | Richtung | Kommentar |
|------|-----|------------------|----------|-----------|
| `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Socket | Eingang | Stellt den UDINT-Wert (D1) und das zugehörige Ereignis (E1) bereit |
| `AX_OUT` | `adapter::types::unidirectional::AX` | Plug | Ausgang | Liefert den BOOL-Wert (D1) und das Bestätigungsereignis (E1) |

## Funktionsweise
Der interne Ablauf ist in drei Schritte gegliedert:

1. **Ereignisempfang:** Das Ereignis `E1` des Socket-Adapters `AUDI_IN` triggert die Verarbeitung.
2. **Vergleich:** Der eingegangene UDINT-Wert (`AUDI_IN.D1`) wird im Baustein `F_NE` (IEC 61131‑3: *ungleich*) mit dem konstanten Wert `UDINT#0` verglichen.
3. **Ergebnisausgabe:** Das Ergebnis des Vergleichs (`F_NE.OUT`) – ein BOOL – wird auf den Ausgangsdaten-Port `AX_OUT.D1` gelegt. Gleichzeitig wird das Ereignis `F_NE.CNF` an den Ereigniseingang `AX_OUT.E1` weitergeleitet, sodass der Ausgangsadapter das Ergebnis signalisiert.

**Zusammenhang:**
- Ist der Eingangswert ungleich 0 → Ausgabe `TRUE`
- Ist der Eingangswert gleich 0 → Ausgabe `FALSE`

## Technische Besonderheiten
- **Verwendete Bibliothek:** Der Kern besteht aus dem IEC‑61131-Baustein `F_NE` (Ungleich-Vergleich). Dieser wird aus der Bibliothek `iec61131::comparison::F_NE` importiert.
- **Kein eigener ECC:** Als Composite-FB besitzt `AUDI_TO_AX` keinen eigenen Ablaufzustand – die gesamte Logik ist rein datenflussgesteuert.
- **Unidirektionale Adapter:** Sowohl der Eingangs- als auch der Ausgangsadapter sind als *unidirectional* ausgelegt, d.h. sie unterstützen nur einen festgelegten Daten- und Ereignisfluss von der Quelle zum Senke.
- **Parametrierung:** Der Vergleichswert ist fest auf `UDINT#0` gesetzt und nicht nach außen parametrierbar.

## Zustandsübersicht
Der FB besitzt keinen eigenen Zustandsautomaten. Das Verhalten wird vollständig durch die eingehenden Ereignisse bestimmt: Jedes Ereignis am Socket `AUDI_IN.E1` führt zu einem Durchlauf der internen Logik und einer Ausgabe am Plug `AX_OUT`.

## Anwendungsszenarien
- **Binäre Schwellwertausgabe:** Ein Zählerwert (z.B. Anzahl erfasster Teile) soll als Schaltsignal (`TRUE` wenn vorhanden, `FALSE` wenn Null) an eine nachgeschaltete Steuerung weitergegeben werden.
- **Adapter-Konvertierung in heterogenen Systemen:** Wenn ein Sensor oder Subsystem einen UDINT-Wert über einen AUDI-Adapter liefert, das Zielsystem aber einen BOOL-Wert über einen AX-Adapter erwartet.
- **Vereinfachung von Netzwerken:** Der FB kapselt die Logik „Ungleich Null“ und reduziert dadurch die Komplexität in übergeordneten Funktionsplänen.

## Vergleich mit ähnlichen Bausteinen
- **`AUDI_TO_BOOL` (hypothetisch):** Würde dieselbe Funktionalität bieten, aber ohne Adapter-Konzept – eventuell mit direkten Daten-Eingängen/-Ausgängen.
- **Direkter Vergleich `F_NE`:** Einzelner Baustein, der den Vergleich durchführt, jedoch ohne Adapter-Anpassung.
Der Vorteil von `AUDI_TO_AX` liegt in der nahtlosen Integration in eine Adapter-basierte Architektur, wie sie in der 4diac-IDE üblich ist. Er vermeidet zusätzliche Konvertierungsschritte zwischen unterschiedlichen Schnittstellentypen.

## Fazit
Der Funktionsblock `AUDI_TO_AX` ist ein spezialisierter, aber sehr nützlicher Konverter für die unidirektionale Übertragung eines UDINT-Wertes auf ein BOOL-Signal. Durch die klare Kapselung der Vergleichslogik und die Verwendung von Standard-Adaptern vereinfacht er die Signalkette in IEC‑61499-basierten Automatisierungssystemen. Er ist robust, einfach zu verstehen und benötigt keine aufwändige Konfiguration – ideal für häufige Aufgaben wie die binäre Auswertung von Zählerständen.
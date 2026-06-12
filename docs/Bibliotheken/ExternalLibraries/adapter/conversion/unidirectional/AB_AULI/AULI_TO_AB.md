# AULI_TO_AB


![AULI_TO_AB](./AULI_TO_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AULI_TO_AB` ist ein Composite-Baustein, der einen AULI-Adapter (ULINT-Datentyp) in einen AB-Adapter (BYTE-Datentyp) umwandelt. Er ermöglicht die nahtlose Verbindung von Komponenten, die unterschiedliche Adapter-Schnittstellen verwenden, indem die eingehenden Daten konvertiert und als kompatibler Ausgang bereitgestellt werden.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ereignis- oder Dateneingänge/-ausgänge. Die gesamte Ein- und Ausgabe erfolgt über Adapter.

### **Ereignis-Eingänge**

Keine (Ereignisse werden über den AULI-Adapter empfangen).

### **Ereignis-Ausgänge**

Keine (Ereignisse werden über den AB-Adapter gesendet).

### **Daten-Eingänge**

Keine (Daten werden über den AULI-Adapter empfangen).

### **Daten-Ausgänge**

Keine (Daten werden über den AB-Adapter gesendet).

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `AULI_IN` | `adapter::types::unidirectional::AULI` | Socket (Eingangs-Adapter) | ULINT-Adapter, der die zu konvertierenden Werte und das Auslöse-Ereignis liefert |
| `AB_OUT` | `adapter::types::unidirectional::AB` | Plug (Ausgangs-Adapter) | BYTE-Adapter, der die konvertierten Werte und das Bestätigungs-Ereignis bereitstellt |

## Funktionsweise

Der Baustein nutzt intern den IEC‑61131‑Baustein `F_ULINT_TO_BYTE` für die Konvertierung von ULINT nach BYTE. Die Abläufe sind:

1. **Eingang**: Am Socket `AULI_IN` wird ein Ereignis (E1) empfangen, das die Konvertierung anstößt. Gleichzeitig liegt der Datenwert (D1) als ULINT an.
2. **Verarbeitung**: Das Ereignis und die Daten werden an den internen Baustein `F_ULINT_TO_BYTE` weitergeleitet (Ereignis `REQ`, Daten `IN`). Dieser führt die Typumwandlung durch.
3. **Ausgang**: Nach erfolgreicher Konvertierung signalisiert der interne Baustein ein Ereignis (`CNF`) und liefert das Ergebnis (`OUT`) als BYTE. Beide werden auf den Plug `AB_OUT` übertragen (Ereignis E1, Daten D1).

Der gesamte Ablauf erfolgt synchron innerhalb eines Ausführungszyklus des Composite-Bausteins.

## Technische Besonderheiten

- **Composite-Baustein**: Die Logik wird vollständig durch das interne Netzwerk aus vordefinierten Bausteinen realisiert – es existiert kein eigenes ECC (Execution Control Chart).
- **Lizenz und Copyright**: Der Baustein ist unter der Eclipse Public License 2.0 (EPL-2.0) lizenziert und unterliegt dem Urheberrecht eines Drittanbieters.
- **Abhängigkeiten**: Er setzt den IEC‑61131-Baustein `F_ULINT_TO_BYTE` aus der Bibliothek `iec61131::conversion` voraus.
- **Paketstruktur**: Der Baustein gehört zum Paket `adapter::conversion::unidirectional`.

## Zustandsübersicht

Da der Baustein kein eigenes ECC besitzt, existieren keine expliziten Zustände. Der interne Ablauf ist strikt durch die Ereigniskette `AULI_IN.E1 → Convert.REQ → Convert.CNF → AB_OUT.E1` festgelegt.

## Anwendungsszenarien

- Einbindung eines ULINT‑liefernden Sensors (z. B. hochauflösender Entfernungsmesser) in ein Steuerungssystem, das auf BYTE‑Adapter‑Schnittstellen basiert.
- Nachrüstung bestehender Anlagen, bei denen Komponenten mit unterschiedlichen Adaptertypen (ULINT vs. BYTE) zusammengeführt werden müssen.
- Prototypenentwicklung, bei der vorübergehend ULINT‑Werte über einen BYTE‑Kanal verarbeitet werden (z. B. Simulation oder Test).

## Vergleich mit ähnlichen Bausteinen

Es existieren analoge Konvertierungsbausteine für andere Datentypen (z. B. `AULI_TO_xx` oder `xx_TO_AB`). Der `AULI_TO_AB` ist speziell für die Umwandlung von ULINT in BYTE optimiert und nutzt die zugehörigen Adapter-Typen. Im Gegensatz zu generischen Funktionsbausteinen vermeidet er die manuelle Verkabelung von Einzel-Ereignissen und -Daten und bietet eine gekapselte, adapterbasierte Schnittstelle.

## Fazit

Der `AULI_TO_AB` ist ein kompakter, zuverlässiger Composite-Baustein zur Konvertierung zwischen zwei gängigen Adapter-Typen in der 4diac-IDE. Er reduziert den Verkabelungsaufwand und vereinfacht die Integration heterogener Komponenten. Durch die Verwendung des standardisierten IEC‑61131‑Konvertierungsbausteins bleibt die Umwandlung typsicher und effizient.
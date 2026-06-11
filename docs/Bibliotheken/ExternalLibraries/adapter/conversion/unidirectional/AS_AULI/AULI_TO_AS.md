# AULI_TO_AS


![AULI_TO_AS](./AULI_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_AS** ist ein Composite-Baustein zur Konvertierung eines unidirektionalen **AULI**-Adapters (ULINT) in einen unidirektionalen **AS**-Adapter (SINT). Er kapselt die Typumwandlung von vorzeichenlosen 64‑Bit‑Ganzzahlen in vorzeichenbehaftete 8‑Bit‑Ganzzahlen und stellt eine nahtlose Verbindung zwischen Komponenten mit unterschiedlichen Datentypanforderungen im 4diac‑Framework bereit.

## Schnittstellenstruktur
Der Baustein besitzt keine separaten Ereignis‑ oder Datenports auf der obersten Ebene. Die gesamte Kommunikation erfolgt ausschließlich über zwei Adapter.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `AULI_IN` | Socket (Eingang) | `adapter::types::unidirectional::AULI` | Bietet ein Ereignis `E1` und einen Datenwert `D1` vom Typ `ULINT`. |
| `AS_OUT`  | Plug (Ausgang)  | `adapter::types::unidirectional::AS`   | Liefert ein Ereignis `E1` und einen Datenwert `D1` vom Typ `SINT`. |

### **Ereignis-Eingänge (über Adapter)**
- `AULI_IN.E1` – Startet die Konvertierung des anliegenden ULINT-Wertes.

### **Ereignis-Ausgänge (über Adapter)**
- `AS_OUT.E1` – Bestätigt die Fertigstellung der Konvertierung und zeigt an, dass der neue SINT-Wert gültig ist.

### **Daten-Eingänge (über Adapter)**
- `AULI_IN.D1` – ULINT-Wert, der umgewandelt werden soll (Wertebereich 0 … 2²⁴⁻¹).

### **Daten-Ausgänge (über Adapter)**
- `AS_OUT.D1` – Ergebnis der Konvertierung als SINT‑Wert (Wertebereich −128 … 127).

## Funktionsweise
Der Baustein verwendet intern die IEC‑61131‑Konvertierungsfunktion `F_ULINT_TO_SINT`. Wird am Eingangsadapter das Ereignis `E1` empfangen, wird der aktuelle Wert von `AULI_IN.D1` ausgelesen und der Konvertierung unterzogen. Das Ergebnis wird an `AS_OUT.D1` übergeben und gleichzeitig das Ereignis `AS_OUT.E1` ausgelöst.

Die Verarbeitung ist rein ereignisgesteuert und erfolgt ohne Zwischenspeicherung interner Zustände.

## Technische Besonderheiten
- **Wertebereichsverlust:** Da `ULINT` einen sehr großen Wertevorrat (0 … 2⁶⁴−1) abdeckt, während `SINT` nur −128 … 127 darstellen kann, führt die Konvertierung bei Werte außerhalb des SINT‑Bereichs zu einem Überlauf bzw. zur Sättigung (gemäß IEC‑61131‑Definition). Dies sollte bei der Anwendung bedacht werden.
- **Unidirektionale Adapter:** Der Baustein ist für Datenfluss in einer Richtung ausgelegt – vom Eingangs‑ zum Ausgangsadapter. Er kann nicht für bidirektionale Kommunikation verwendet werden.
- **Lizenz:** Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten und keine internen Zustandsregister. Er verhält sich wie eine rein kombinatorische Funktion, die durch ein Ereignis getriggert wird. Es gibt keinen dauerhaften Speicher von Werten oder Verarbeitungszuständen.

## Anwendungsszenarien
- **Sensor‑Integration:** Ein Sensor liefert Daten im ULINT‑Format, ein nachgeschaltetes Modul erwartet jedoch SINT‑Werte (z. B. für eine einfache Anzeige oder Schwellwertlogik).
- **Protokollanpassung:** Inheterogene Automatisierungssysteme, bei denen Adapter unterschiedliche Datentypen verwenden, können mit diesem Baustein typkompatibel verbunden werden.
- **Datenreduktion:** Gezielte Umwandlung großer Zahlenbereiche in kleinere Formate zur Einsparung von Speicherplatz oder Busbandbreite (unter Inkaufnahme von Genauigkeit).

## Vergleich mit ähnlichen Bausteinen
- **`AULI_TO_INT`** – Konvertiert nach `INT` (16‑Bit, −32768 … 32767), größerer Wertebereich als SINT, aber dennoch verlustbehaftet bei großen Zahlen.
- **`AULI_TO_DINT`** – Konvertiert nach `DINT` (32‑Bit, −2³¹ … 2³¹−1), deckt einen deutlich größeren Teil des ULINT‑Bereichs ab und ist für viele Anwendungen die bessere Wahl.
- **`ULINT_TO_SINT` (direkt)** – Ein einfacher Funktionsbaustein ohne Adapter‑Kapselung; `AULI_TO_AS` bietet denselben Dienst in einer adapterbasierten Umgebung.

## Fazit
Der **AULI_TO_AS** ist ein schlanker, zweckgebundener Konverter für unidirektionale Adapter. Er ermöglicht die einfache Integration von Komponenten, die auf dem SINT‑Datentyp basieren, in ein ULINT‑dominiertes System. Aufgrund der großen Differenz der Wertebereiche muss der Anwender jedoch mögliche Überlauf‑ oder Sättigungseffekte berücksichtigen und gegebenenfalls auf breitere Datentypen ausweichen.
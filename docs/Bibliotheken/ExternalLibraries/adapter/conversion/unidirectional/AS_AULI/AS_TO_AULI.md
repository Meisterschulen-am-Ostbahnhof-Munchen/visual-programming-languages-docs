# AS_TO_AULI

---

## Einleitung

![AS_TO_AULI](./AS_TO_AULI.svg)

Der zusammengesetzte Funktionsbaustein `AS_TO_AULI` dient der Umwandlung eines **AS (SINT)-Adapters** in einen **AULI (ULINT)-Adapter**. Er verwendet intern den IEC 61131-Umwandlungsbaustein `F_SINT_TO_ULINT`, um die eigentliche Typkonvertierung von SINT auf ULINT durchzuführen. Der Baustein ist als Teil einer unidirektionalen Adapter-Bibliothek für die Kommunikation zwischen unterschiedlichen Datentypen konzipiert.

---

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt **keine direkten Ereignis-Eingänge**. Der Empfang von Ereignissen erfolgt über den **Socket-Adapter `AS_IN`**:
- **`AS_IN.E1`** – Ereignis-Eingang über den AS-Adapter, der die Datenumwandlung anstößt.

### **Ereignis-Ausgänge**
Der Baustein besitzt **keine direkten Ereignis-Ausgänge**. Die Ausgabe von Ereignissen erfolgt über den **Plug-Adapter `AULI_OUT`**:
- **`AULI_OUT.E1`** – Ereignis-Ausgang über den AULI-Adapter, der nach abgeschlossener Konvertierung aktiviert wird.

### **Daten-Eingänge**
Der Baustein besitzt **keine direkten Daten-Eingänge**. Die Dateneingabe erfolgt über den **Socket-Adapter `AS_IN`**:
- **`AS_IN.D1`** – Daten-Eingang vom Typ **SINT**, der den umzuwandelnden Wert bereitstellt.

### **Daten-Ausgänge**
Der Baustein besitzt **keine direkten Daten-Ausgänge**. Die Datenausgabe erfolgt über den **Plug-Adapter `AULI_OUT`**:
- **`AULI_OUT.D1`** – Daten-Ausgang vom Typ **ULINT**, der den konvertierten Wert liefert.

### **Adapter**
| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `AS_IN` | `adapter::types::unidirectional::AS` (Socket) | Eingang | Empfängt SINT-Werte und Auslöseereignis `E1`. |
| `AULI_OUT` | `adapter::types::unidirectional::AULI` (Plug) | Ausgang | Sendet ULINT-Werte und Bestätigungsereignis `E1`. |

---

## Funktionsweise
1. Der Baustein erwartet ein Ereignis am Socket-Adapter `AS_IN.E1`. Gleichzeitig muss der Datenwert `AS_IN.D1` (Typ SINT) anliegen.
2. Das Ereignis wird an den internen Funktionsbaustein `F_SINT_TO_ULINT` (weitergeleitet als `REQ`).
3. Der interne Baustein führt die Konvertierung **SINT → ULINT** durch.
4. Nach erfolgreicher Umwandlung sendet `F_SINT_TO_ULINT` ein Bestätigungsereignis (`CNF`) an den Plug-Adapter `AULI_OUT.E1`.
5. Der konvertierte Wert (Typ ULINT) wird über `AULI_OUT.D1` ausgegeben.

Die Konvertierung erfolgt nach den Regeln der IEC 61131-3: Der SINT-Wert (8‑Bit vorzeichenbehaftet) wird in einen vorzeichenlosen 64‑Bit-Wert (ULINT) umgerechnet. Negative SINT-Werte führen dabei zu einer negativen ULINT-Repräsentation (Zweierkomplement-Umwandlung auf 64 Bit).

---

## Technische Besonderheiten
- **Standardkonformität**: Der Baustein ist gemäß IEC 61499-2 spezifiziert.
- **Lizenz**: Eclipse Public License 2.0 (EPL-2.0).
- **Abhängigkeit**: Importiert den IEC 61131-Baustein `F_SINT_TO_ULINT` aus dem Paket `iec61131::conversion`.
- **Typsicherheit**: Die Adapter `AS` und `AULI` gewährleisten typsichere Verbindungen; eine direkte Verkabelung von SINT auf ULINT ohne Konvertierung ist nicht möglich.
- **Unidirektionaler Datenfluss**: Der Baustein arbeitet rein unidirektional – er empfängt Daten und Ereignisse und gibt konvertierte Daten und Bestätigungen aus.

---

## Zustandsübersicht
Der Baustein besitzt **keine eigene Zustandsmaschine**. Er fungiert als reine Verschaltung des inneren `F_SINT_TO_ULINT`-Bausteins. Das Verhalten ist strikt ereignisgesteuert:
- **Warten** (Initialzustand) → Ereignis an `AS_IN.E1` → Übergang zu **Konvertierung**.
- **Konvertierung** → interner Baustein arbeitet asynchron → nach Beendigung → Ereignis an `AULI_OUT.E1` → Rückkehr zu **Warten**.

Eine Fehlerbehandlung ist nicht explizit modelliert; der innere Baustein gibt bei ungültigen Eingaben (z. B. außerhalb des Wertebereichs) ein definiertes Ergebnis (z. B. 0) aus.

---

## Anwendungsszenarien
- **Einbindung in Adapterketten**: Wenn ein vorangeschalteter Funktionsbaustein einen SINT-Wert liefert, nachfolgende Komponenten jedoch nur ULINT verarbeiten, kann `AS_TO_AULI` als Zwischenadapter verwendet werden.
- **Sensor-Anbindung**: Sensoren mit 8‑Bit‑Ausgabe (z. B. Drehgeber, einfache Schalter) können an einen 64‑Bit‑Bus angebunden werden.
- **Legacy-Systeme**: Altanlagen mit SINT‑Schnittstellen werden durch diesen Adapter kompatibel zu modernen ULINT‑basierten Steuerungen.

---

## Vergleich mit ähnlichen Bausteinen
| Baustein | Zieltyp | Quelltyp | Besonderheit |
|----------|---------|----------|--------------|
| `AS_TO_AULI` | ULINT | SINT | Konvertierung SINT → ULINT |
| `AS_TO_AUDI` | UDINT | SINT | Konvertierung SINT → UDINT (32 Bit) |
| `AS_TO_AWORD` | WORD | SINT | Konvertierung SINT → WORD (16 Bit) |
| `AULI_TO_AS` | SINT | ULINT | Rückkonvertierung ULINT → SINT (mit Überlaufbegrenzung) |

Der vorliegende Baustein deckt die Konvertierung von einem 8‑Bit‑Vorzeichen‑Typ auf einen 64‑Bit‑vorzeichenlosen Typ ab und eignet sich besonders für Anwendungen, die einen großen Wertebereich bei der Ausgabe benötigen.

---

## Fazit
`AS_TO_AULI` ist ein einfacher, aber wichtiger zusammengesetzter Baustein zur Typanpassung zwischen SINT- und ULINT-Adaptern. Er kapselt die IEC 61131-Konvertierung und ermöglicht eine typsichere, ereignisgesteuerte Integration in Automatisierungssysteme. Durch seine klare Schnittstellenstruktur und die Verwendung von Standardbibliotheken ist er wartbar, wiederverwendbar und leicht in bestehende 4diac‑IDE‑Projekte einbindbar.
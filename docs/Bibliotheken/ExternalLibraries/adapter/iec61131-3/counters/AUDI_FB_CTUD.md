# AUDI_FB_CTUD


![AUDI_FB_CTUD](./AUDI_FB_CTUD.svg)

* * * * * * * * * *
## Einleitung

Der **AUDI_FB_CTUD** ist ein Aufwärts-/Abwärtszähler (Up-Down Counter) mit einem Wertebereich für vorzeichenlose 32‑Bit‑Ganzzahlen (UDINT). Er ist als reine Adapter‑Version realisiert, d. h. alle Ein‑ und Ausgänge werden über Adapter‑Schnittstellen bereitgestellt. Der Baustein kapselt den standardisierten IEC‑61131‑Funktionsblock `FB_CTUD_UDINT` und erweitert dessen Funktionalität um eine adapterbasierte Anbindung. Bei jedem auslösenden Ereignis (CU, CD, R, LD oder PV) werden alle Ausgangsadapter zyklisch aktualisiert. Wenn eine änderungsgesteuerte (flankensensitive) Auslösung benötigt wird, ist die Verwendung eines `AX_D_FF` als Filterbaustein empfohlen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt auf oberster Ebene keine diskreten Ereignis-Eingänge. Alle Ereignisse werden über die eingehenden Adapter-Schnittstellen (Sockets) vom Typ `AX` übertragen.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | `Event` | Ausführungsbestätigung – wird bei jeder Bearbeitung eines eingehenden Ereignisses ausgegeben. |

Zusätzlich werden Ereignisse über die ausgehenden Adapter (Plugs) gesendet.

### **Daten-Eingänge**

Auf oberster Ebene existieren keine direkten Daten-Eingänge. Alle Datenwerte werden über die Sockets `CU.D1`, `CD.D1`, `R.D1`, `LD.D1` und `PV.D1` bereitgestellt.

### **Daten-Ausgänge**

Auf oberster Ebene existieren keine direkten Daten-Ausgänge. Die Ergebnisdaten werden über die Plugs `QU.D1`, `QD.D1` und `CV.D1` ausgegeben.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| **Socket (Eingang)** | `CU` | `adapter::types::unidirectional::AX` | Count up – Ereignis und Daten (BOOL) zum Hochzählen |
| **Socket (Eingang)** | `CD` | `adapter::types::unidirectional::AX` | Count down – Ereignis und Daten (BOOL) zum Herunterzählen |
| **Socket (Eingang)** | `R`  | `adapter::types::unidirectional::AX` | Reset – Ereignis und Daten (BOOL) zum Rücksetzen des Zählers |
| **Socket (Eingang)** | `LD` | `adapter::types::unidirectional::AX` | Load – Ereignis und Daten (BOOL) zum Laden des Preset-Wertes |
| **Socket (Eingang)** | `PV` | `adapter::types::unidirectional::AUDI` | Preset value – Ereignis und Daten (UDINT) für den Vorgabewert |
| **Plug (Ausgang)** | `QU` | `adapter::types::unidirectional::AX` | Output Up – Ereignis und Daten (BOOL), aktiv wenn der aktuelle Zählwert den Wert 0 erreicht |
| **Plug (Ausgang)** | `QD` | `adapter::types::unidirectional::AX` | Output Down – Ereignis und Daten (BOOL), aktiv wenn der aktuelle Zählwert den Wert >= PV erreicht |
| **Plug (Ausgang)** | `CV` | `adapter::types::unidirectional::AUDI` | Count value – Ereignis und Daten (UDINT) mit dem aktuellen Zählwert |

## Funktionsweise

Der `AUDI_FB_CTUD` nutzt intern den Baustein `FB_CTUD_UDINT` aus der IEC‑61131‑Bibliothek. Alle über die Sockets eingehenden Ereignisse (von `CU`, `CD`, `R`, `LD` und `PV`) werden auf den `REQ`‑Eingang des internen Bausteins geführt. Die zugehörigen Daten werden auf die entsprechenden Eingänge (`CU`, `CD`, `R`, `LD`, `PV`) geleitet. Der interne Baustein verarbeitet die Anforderung und aktualisiert seine Ausgänge. Nach erfolgreicher Bearbeitung wird das Ereignis `CNF` ausgelöst und gleichzeitig werden die Ausgabeadapter `QU`, `QD` und `CV` mit ihren neuen Daten und Ereignissen versorgt.

**Wichtig:** Der Baustein feuert die Ausgangsereignisse (`QU.E1`, `QD.E1`, `CV.E1`) bei **jeder** Verarbeitung eines eingehenden Ereignisses. Eine filternde Flankenauswertung findet nicht statt.

## Technische Besonderheiten

- **Reine Adapter‑Schnittstelle:** Der Baustein besitzt keine klassischen Ein‑/Ausgänge, sondern ausschließlich Adapter (Sockets und Plugs). Dies ermöglicht eine flexible Kopplung in adapterbasierten Automatisierungsarchitekturen.
- **Verwendung unidirektionaler Adapter:** Die Adapter `AX` und `AUDI` sind als unidirektional definiert. Damit wird eine klare Richtung der Daten- und Ereignisflüsse erzwungen.
- **Kapselung des IEC‑61131‑Standards:** Die Zähllogik entspricht dem genormten `CTUD`‑Funktionsblock, was die Übertragbarkeit und Wartbarkeit erhöht.
- **Bereich:** Der Zählwert ist als `UDINT` (vorzeichenlos, 0…2³²−1) implementiert.

## Zustandsübersicht

Der interne `FB_CTUD_UDINT` durchläuft folgende Zustände, abhängig von den eingehenden Befehlen:

| Bedingung | Aktion |
|-----------|--------|
| `CU` = TRUE (steigende Flanke) und `CD` = FALSE | Zähler erhöht sich um 1 |
| `CD` = TRUE (steigende Flanke) und `CU` = FALSE | Zähler verringert sich um 1 |
| `R` = TRUE (steigende Flanke) | Zähler wird auf 0 zurückgesetzt |
| `LD` = TRUE (steigende Flanke) | Zähler wird auf den Wert von `PV` gesetzt |
| Gleichzeitige `CU`- und `CD`-Flanken | Zählerstand bleibt unverändert (Priorität: keine) |
| `QU` = TRUE | Aktueller Wert = 0 |
| `QD` = TRUE | Aktueller Wert ≥ `PV` |

## Anwendungsszenarien

- **Stückzähler in Produktionsanlagen:** Erfassung von Produkten an einer Förderstrecke, wobei `CU` und `CD` für korrekte Zählung bei Vor- und Rücklauf genutzt werden.
- **Lagerbestandsverwaltung:** Zählen von Ein‑ und Auslagerungen, mit Reset bei Inventur und Load für Sollvorgaben.
- **Ereigniszähler in der Gebäudeautomation:** Erfassen von Personenströmen (z. B. in Aufzügen) mit zusätzlicher Rücksetzfunktion.
- **Adapter‑basierte Systeme:** Integration in verteilte Steuerungslandschaften, die auf dem Adapter‑Konzept der 4diac‑IDE aufbauen (z. B. AUTOSAR‑ähnliche Kommunikation).

## Vergleich mit ähnlichen Bausteinen

| Merkmal | `AUDI_FB_CTUD` | Standard `CTUD` (IEC 61131) |
|---------|----------------|----------------------------|
| **Schnittstelle** | Reine Adapter (Sockets/Plugs) | Direkte Ereignis- und Datenein‑/ausgänge |
| **Datenformat** | UDINT (über AUDI‑Adapter) | UDINT (direkt) |
| **Ereignisverhalten** | Jedes eingehende Event feuert alle Ausgänge | Ereignis wird nur bei relevanten Änderungen ausgegeben |
| **Flexibilität** | Höher durch adapterbasierte Verkabelung | Geringer, aber einfacher in klassischen SPS‑Umgebungen |
| **Empfohlener Filter** | Zusätzlicher `AX_D_FF` für flankengesteuerte Ausgabe | Kein Filter nötig, da flankenempfindlich |

## Fazit

Der `AUDI_FB_CTUD` ist ein leistungsfähiger Aufwärts-/Abwärtszähler, der durch seine adapterbasierte Schnittstelle besonders für moderne, modulare Automatisierungslösungen geeignet ist. Er kombiniert die bewährte IEC‑61131‑Zähllogik mit der Flexibilität der 4diac‑Adaptertechnologie. Anwender sollten jedoch beachten, dass die Ausgangsereignisse bei jeder Verarbeitung und nicht nur bei Änderungen ausgelöst werden – gegebenenfalls ist ein nachgeschalteter Flankenfilter erforderlich. Mit seiner klaren Struktur und den standardisierten Datentypen stellt er eine robuste Komponente für Zählaufgaben in industriellen Steuerungssystemen dar.
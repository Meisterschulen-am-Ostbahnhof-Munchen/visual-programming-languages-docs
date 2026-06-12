# ALI_TO_AUI


![ALI_TO_AUI](./ALI_TO_AUI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **ALI_TO_AUI** ist ein zusammengesetzter Baustein (Composite FB) zur Umwandlung eines ALI-Adapters (LINT-Datentyp) in einen AUI-Adapter (UINT-Datentyp). Er erlaubt die nahtlose Integration von Komponenten mit unterschiedlichen Adapterdefinitionen in einer 4diac-Umgebung. Der Baustein basiert auf dem internen Konvertierungsbaustein `F_LINT_TO_UINT` aus der IEC‑61131-Bibliothek.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Nicht vorhanden – die Ereignissteuerung erfolgt über die Adapter.

### **Ereignis-Ausgänge**
Nicht vorhanden – die Ereignissteuerung erfolgt über die Adapter.

### **Daten-Eingänge**
Nicht vorhanden – die Datenübergabe erfolgt über die Adapter.

### **Daten-Ausgänge**
Nicht vorhanden – die Datenübergabe erfolgt über die Adapter.

### **Adapter**
| Typ | Name | Kommentar |
|------|------|-----------|
| Socket | `ALI_IN` | Eingangsadapter vom Typ `adapter::types::unidirectional::ALI` – liefert LINT-Wert und assoziiertes Ereignis. |
| Plug | `AUI_OUT` | Ausgangsadapter vom Typ `adapter::types::unidirectional::AUI` – stellt den umgewandelten UINT-Wert und zugehöriges Ereignis bereit. |

## Funktionsweise
Der Baustein verbindet intern den Socket `ALI_IN` mit dem Eingang des Konvertierungsbausteins `F_LINT_TO_UINT`.  
- Über den Ereignisausgang `E1` von `ALI_IN` wird der `REQ`-Eingang des Konverters angesteuert.  
- Der Datenwert `D1` von `ALI_IN` (LINT) wird auf den `IN`-Eingang des Konverters gelegt.  
- Nach erfolgreicher Konvertierung signalisiert der Konverter mit `CNF` das Ereignis an den Plug `AUI_OUT`, und der umgewandelte Wert (UINT) wird auf dessen `D1`-Ausgang geschrieben.

Der gesamte Ablauf ist ereignisgesteuert: Ein eingehendes Ereignis am ALI‑Adapter löst die Umwandlung aus und erzeugt ein entsprechendes Ausgangsereignis am AUI‑Adapter.

## Technische Besonderheiten
- **Datentypkonvertierung:** Der interne Baustein wandelt einen 64‑Bit signed Integer (LINT) in einen 16‑Bit unsigned Integer (UINT) um. Da der Wertebereich von UINT (0…65535) deutlich kleiner ist als der von LINT, kommt es bei Werten außerhalb dieses Bereichs zu einem Überlauf/Verlust.
- **Abhängigkeit:** Der Baustein benötigt die Bibliothek `iec61131::conversion` (insbesondere den Baustein `F_LINT_TO_UINT`).
- **Adapterreine Schnittstelle:** Der gesamte Datenaustausch erfolgt ausschließlich über Adapter, was eine modulare und wiederverwendbare Einbindung in größere Netzwerke ermöglicht.

## Zustandsübersicht
Der Baustein selbst besitzt keinen eigenen Zustandsautomaten. Die Zustandslogik wird vollständig durch den internen Baustein `F_LINT_TO_UINT` abgebildet. Dieser verfügt typischerweise über die Zustände **IDLE** (wartet auf REQ) und **BUSY** (führt Konvertierung durch). Nach Abschluss wird das Ergebnis bereitgestellt und der CNF-Ereignisausgang aktiviert.

## Anwendungsszenarien
- **Adapterbrücke:** Ein Sensor, der Daten im ALI-Format (LINT) bereitstellt, soll an einen Aktor angeschlossen werden, der einen AUI-Eingang (UINT) erwartet.
- **Systemintegration:** In heterogenen Automatisierungssystemen, in denen unterschiedliche Adapterdefinitionen verwendet werden, dient der Baustein als einfacher Konverter ohne manuelle Programmierung.
- **Prototypenbau:** Schnelles Ersetzen von Adaptern während der Entwicklungsphase, ohne die grundlegende Datenflusslogik ändern zu müssen.

## Vergleich mit ähnlichen Bausteinen
Es existieren analoge Konverterbausteine wie `ALI_TO_UDI` (LINT → UDINT) oder `DINT_TO_UINT`. Der vorliegende Baustein spezialisiert sich auf die Kombination der unidirektionalen Adapter ALI und AUI. Im Gegensatz zu einer direkten Verbindung der Adapter über Datentypkonvertierung in der Netzwerkschicht bietet dieser Composite FB eine kompakte, wiederverwendbare Lösung mit klar definierten Ereignissignalen.

## Fazit
Der ALI_TO_AUI-Baustein ist eine praktische und leicht verständliche Komponente zur Umwandlung zwischen ALI- und AUI-Adaptern. Seine Composite-Struktur kapselt die notwendige Datenkonvertierung und Ereignisweitergabe, sodass er sich nahtlos in bestehende 4diac‑Projekte einfügt. Die einfache Handhabung und die klare Trennung der Schnittstellen machen ihn zu einem nützlichen Werkzeug bei der Adapter‑Integration.
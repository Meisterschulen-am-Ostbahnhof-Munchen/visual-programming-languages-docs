# AB_TO_AUI


![AB_TO_AUI](./AB_TO_AUI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AB_TO_AUI** dient als Adapter-Konverter zwischen einem AB-Adapter (BYTE-basiert) und einem AUI-Adapter (UINT-basiert). Er realisiert eine unidirektionale Konvertierung von BYTE- auf UINT-Datentyp. Der Baustein ist als Composite-FB ausgeführt und nutzt intern die IEC 61131-3 Konvertierungsfunktion `F_BYTE_TO_UINT`. Er ist speziell für die Anbindung von Sensoren oder Aktoren vorgesehen, die ihre Daten im BYTE-Format liefern, jedoch in einer UINT-basierten Umgebung verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge auf der obersten Ebene. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Ereignis-Ausgänge auf der obersten Ebene. Die Ereignisweitergabe erfolgt über die angeschlossenen Adapter.

### **Daten-Eingänge**
Der FB besitzt keine direkten Daten-Eingänge auf der obersten Ebene. Die Datenaufnahme erfolgt über den angeschlossenen AB-Adapter.

### **Daten-Ausgänge**
Der FB besitzt keine direkten Daten-Ausgänge auf der obersten Ebene. Die Datenabgabe erfolgt über den angeschlossenen AUI-Adapter.

### **Adapter**

| Richtung | Name  | Typ des Adapters              | Beschreibung                                    |
|----------|-------|-------------------------------|-------------------------------------------------|
| Socket   | AB_IN | `adapter::types::unidirectional::AB`  | Eingangsadapter für BYTE-Daten (Quelladapter)  |
| Plug     | AUI_OUT| `adapter::types::unidirectional::AUI` | Ausgangsadapter für UINT-Daten (Zieladapter)    |

**Hinweis:** Die Adapter vom Typ `AB` und `AUI` besitzen jeweils einen Ereignis-Eingang (`E1`), einen Ereignis-Ausgang (`E1`), einen Daten-Eingang (`D1` vom Typ BYTE bzw. UINT) sowie einen Daten-Ausgang (`D1` vom Typ BYTE bzw. UINT). Die genauen Details sind den entsprechenden Adapterdefinitionen zu entnehmen.

## Funktionsweise

Der Baustein arbeitet als reiner Konverter: Sobald am Socket `AB_IN` ein Ereignis anliegt (typischerweise über den Ereignis-Eingang des Adapters), wird dieses an den internen FB `F_BYTE_TO_UINT` weitergeleitet. Gleichzeitig wird der vom Adapter bereitgestellte BYTE-Wert (über den Daten-Eingang `D1` des AB-Adapters) an den Konvertierungs-FB übergeben. Der Konvertierungs-FB wandelt den BYTE-Wert in einen gleichwertigen UINT-Wert um. Nach erfolgreicher Konvertierung wird ein Ereignis über den Ereignis-Ausgang des internen FB ausgelöst, das an den Plug `AUI_OUT` weitergegeben wird. Der konvertierte UINT-Wert wird über den Daten-Ausgang des Konvertierungs-FB an den Daten-Eingang des AUI-Adapters übertragen.

Die folgende Abbildung zeigt die interne Verkabelung:

- Ereignisverbindung: `AB_IN.E1` → `Convert.REQ` → `Convert.CNF` → `AUI_OUT.E1`
- Datenverbindung: `AB_IN.D1` → `Convert.IN` → `Convert.OUT` → `AUI_OUT.D1`

Der gesamte Vorgang erfolgt streng sequenziell und ereignisgesteuert.

## Technische Besonderheiten

- **Unidirektionaler Betrieb:** Der FB unterstützt nur die Datenflussrichtung von AB (BYTE) zu AUI (UINT). Eine Rückwandlung ist mit diesem Baustein nicht möglich.
- **Verwendung der IEC 61131-3 Konvertierung:** Die Konvertierung erfolgt über den standardisierten FB `F_BYTE_TO_UINT` aus der IEC 61131-Bibliothek. Dies gewährleistet eine zuverlässige und portable Wandlung.
- **Adapter-basierte Schnittstelle:** Der FB ist bewusst als Adapter-Konverter ausgelegt und nicht als eigenständiger FB mit direkten Ein-/Ausgängen. Dies ermöglicht eine einfache Integration in bestehende Adapter-basierte Kommunikationsstrukturen.
- **Keine Zustandsspeicherung:** Der FB ist stateless, d.h. er speichert keine Zwischenwerte. Jeder Konvertierungsvorgang ist unabhängig von vorhergehenden.

## Zustandsübersicht

Der FB besitzt keine eigenen Zustandsautomaten. Das Verhalten wird durch den internen FB `F_BYTE_TO_UINT` (ein einfacher Funktionsbaustein ohne Zustände) und die Ereignisverkettung bestimmt. Der FB ist daher zu jedem Zeitpunkt bereit, eine Konvertierung durchzuführen, sobald ein Ereignis am Eingangsadapter eintrifft.

## Anwendungsszenarien

- **Sensoranbindung:** Ein Sensor liefert Messwerte im BYTE-Format (z.B. über einen AB-Adapter), während das Steuerungssystem ausschließlich UINT-Werte verarbeitet. Der AB_TO_AUI-FB wandelt die Werte entsprechend um.
- **Protokollanpassung:** In heterogenen Feldbussystemen kann der FB als einfacher Datentypkonverter zwischen unterschiedlichen Adaptertypen eingesetzt werden.
- **Test und Simulation:** Während der Entwicklung können mit diesem FB BYTE-Daten aus einer Testumgebung in UINT-Daten für die Zielapplikation umgewandelt werden.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Adapter-Konverter wie z.B. `AB_TO_UDINT`, `BYTE_TO_WORD` oder direkte Konverter wie `F_BYTE_TO_SINT`. Der `AB_TO_AUI` fokussiert speziell auf die Adapter-Konvertierung unter Beibehaltung der Adapter-Struktur. Im Gegensatz zu reinen Funktionsbausteinen behält er die Adapter-Schnittstellen bei und ermöglicht so eine einfache Kapselung in Adapter-basierten Architekturen. Andere Bausteine wie `F_BYTE_TO_UINT` arbeiten auf Signalebene und benötigen separate Schnittstellen.

## Fazit

Der `AB_TO_AUI` ist ein kompakter und spezialisierter Composite-FB zur unidirektionalen Konvertierung von BYTE- auf UINT-Daten unter Verwendung standardisierter Adapter-Schnittstellen. Er erlaubt eine saubere Integration in adapterbasierte Systeme und reduziert den Aufwand für manuelle Datenkonvertierung. Durch den Einsatz des IEC 61131-3 Konvertierungsbausteins ist die Funktionalität zuverlässig und portabel. Der Baustein eignet sich besonders für Anwendungen, die auf eine lose Kopplung zwischen Datenquellen und -senken angewiesen sind.
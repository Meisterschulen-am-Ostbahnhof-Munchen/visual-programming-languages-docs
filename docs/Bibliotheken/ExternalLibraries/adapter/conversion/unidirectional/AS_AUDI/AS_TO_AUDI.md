# AS_TO_AUDI


![AS_TO_AUDI](./AS_TO_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AS_TO_AUDI ist ein Composite-Baustein, der eine Konvertierung von einem SINT-Adapter (AS) zu einem UDINT-Adapter (AUDI) durchführt. Er dient als Brücke zwischen zwei unterschiedlichen Adaptertypen und ermöglicht die nahtlose Integration von Komponenten, die unterschiedliche Datentypen verwenden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Nicht vorhanden. Die Ereignissteuerung erfolgt über den Adapter-Socket **AS_IN**.

### **Ereignis-Ausgänge**
Nicht vorhanden. Die Ereignisausgabe erfolgt über den Adapter-Plug **AUDI_OUT**.

### **Daten-Eingänge**
Nicht vorhanden. Die Datenaufnahme erfolgt über den Adapter-Socket **AS_IN**.

### **Daten-Ausgänge**
Nicht vorhanden. Die Datenausgabe erfolgt über den Adapter-Plug **AUDI_OUT**.

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **AS_IN** | `adapter::types::unidirectional::AS` | Socket (Eingang) | SINT-Adapter, der einen Eingangswert (SINT) und ein zugehöriges Ereignis bereitstellt. |
| **AUDI_OUT** | `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | UDINT-Adapter, der den konvertierten Wert (UDINT) und ein Ereignis ausgibt. |

Die Adapter enthalten jeweils ein Daten- und ein Ereigniselement:
- **AS_IN**: Daten `D1` (SINT), Ereignis `E1`.
- **AUDI_OUT**: Daten `D1` (UDINT), Ereignis `E1`.

## Funktionsweise
Der Baustein verwendet intern die IEC 61131-Funktion `F_SINT_TO_UDINT`, um den eingehenden SINT-Wert in einen UDINT-Wert umzuwandeln. Die Ablaufsteuerung erfolgt ereignisgesteuert:

1. Ein Ereignis am Element `E1` des Sockets **AS_IN** (z. B. von einem vorgelagerten Baustein) wird zum Eingang `REQ` des internen Konvertierungsbausteins `Convert` weitergeleitet.
2. Der Konvertierungsbaustein liest den aktuellen Wert von `AS_IN.D1` und wandelt ihn in einen UDINT-Wert um.
3. Nach erfolgreicher Konvertierung wird das Ausgangsereignis `CNF` des Konverters ausgelöst, welches wiederum das Ereignis am Element `E1` des Plugs **AUDI_OUT** aktiviert.
4. Gleichzeitig wird der konvertierte Wert über `Convert.OUT` auf `AUDI_OUT.D1` geschrieben.

Damit wird sichergestellt, dass der konvertierte UDINT-Wert erst dann am Ausgang anliegt, wenn das zugehörige Ereignis signalisiert wird.

## Technische Besonderheiten
- **Composite-Pattern**: Der Baustein ist als Composite (zusammengesetzter Funktionsblock) realisiert, der einen einzelnen Konvertierungsbaustein kapselt. Dadurch entsteht eine wiederverwendbare und gekapselte Einheit.
- **Verwendung von IEC 61131-Bausteinen**: Die Konvertierung nutzt die standardisierte Funktion `F_SINT_TO_UDINT`, was Portabilität und Nachvollziehbarkeit fördert.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional (keine Rückmeldung). Dies vereinfacht die Datenflussrichtung.

## Zustandsübersicht
Der Composite-Baustein besitzt keine eigene Zustandsmaschine (ECC). Die gesamte Ablaufsteuerung wird durch die Ereignisverkettung des internen Netzwerks definiert. Somit gibt es keine definierten Zustände oder Zustandsübergänge.

## Anwendungsszenarien
- **Systemintegration**: Wenn ein Subsystem Daten im SINT-Format über einen Adapter bereitstellt, aber ein nachfolgendes Subsystem UDINT-Daten über einen Adapter erwartet.
- **Protokollanpassung**: In heterogenen Automatisierungssystemen, in denen unterschiedliche Datentypen über Adapter ausgetauscht werden, kann dieser Baustein als universeller Konverter dienen.
- **Vereinfachung der Netzwerkstruktur**: Anstatt die Konvertierung direkt in den Applikationsbausteinen vorzunehmen, wird sie in einem eigenen Composite gekapselt, was die Wartbarkeit erhöht.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Bausteine existieren für andere Datentyp-Konvertierungen, z. B. `AS_TO_ABOOL` (SINT nach BOOL) oder `AUINT_TO_AUDI` (UINT nach UDINT). Der vorliegende Baustein unterscheidet sich durch die spezifische Kombination aus SINT-Eingang und UDINT-Ausgang. Er ergänzt die Bibliothek um eine weitere Konvertierungsmöglichkeit und folgt dem gleichen Entwurfsmuster (Composite mit einem internen IEC-61131-Konverter).

## Fazit
Der Funktionsblock `AS_TO_AUDI` bietet eine elegante Lösung zur Umwandlung von SINT-Adapterdaten in UDINT-Adapterdaten. Durch die Kapselung in einem Composite-Baustein wird die Wiederverwendbarkeit und Übersichtlichkeit des Gesamtsystems verbessert. Die Verwendung standardisierter Konvertierungsfunktionen stellt sicher, dass die Konvertierung korrekt und effizient erfolgt.
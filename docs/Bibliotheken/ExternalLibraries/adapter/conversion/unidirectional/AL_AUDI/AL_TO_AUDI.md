# AL_TO_AUDI


![AL_TO_AUDI](./AL_TO_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AL_TO_AUDI** ist ein Composite-Baustein, der einen LWORD-Adaptereingang (Typ `AL`) in einen UDINT-Adapterausgang (Typ `AUDI`) umwandelt. Er kapselt die IEC-61131-3-Konvertierungsfunktion `F_LWORD_TO_UDINT` und stellt eine saubere, adapterbasierte Schnittstelle für unidirektionale Datenflüsse bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt vollständig über den integrierten Socket-Adapter `AL_IN`.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Ereignis-Ausgänge. Ereignisse werden über den integrierten Plug-Adapter `AUDI_OUT` an die nachfolgende Logik weitergegeben.

### **Daten-Eingänge**
Der FB besitzt keine direkten Daten-Eingänge. Die zu konvertierenden LWORD-Daten werden über den Socket-Adapter `AL_IN` empfangen.

### **Daten-Ausgänge**
Der FB besitzt keine direkten Daten-Ausgänge. Die konvertierten UDINT-Daten werden über den Plug-Adapter `AUDI_OUT` ausgegeben.

### **Adapter**
| Adaptertyp | Name      | Beschreibung                                          |
|------------|-----------|-------------------------------------------------------|
| Socket     | `AL_IN`   | LWORD-Adaptereingang (Typ: `adapter::types::unidirectional::AL`) |
| Plug       | `AUDI_OUT`| UDINT-Adapterausgang (Typ: `adapter::types::unidirectional::AUDI`) |

## Funktionsweise
1. Ein eingehendes Ereignis am Socket `AL_IN` (über dessen Ereignisausgang `E1`) triggert die Konvertierungsinstanz `Convert` (Typ `F_LWORD_TO_UDINT`).
2. Gleichzeitig wird der LWORD-Datenwert von `AL_IN.D1` an den Eingang `IN` von `Convert` übergeben.
3. Die Konvertierungsfunktion wandelt den LWORD-Wert in einen UDINT-Wert um.
4. Nach erfolgreicher Konvertierung signalisiert `Convert` dies über seinen Ereignisausgang `CNF`, wodurch der Plug `AUDI_OUT` ein Ereignis an seinem Ereigniseingang `E1` erhält.
5. Der umgewandelte UDINT-Wert wird vom Ausgang `OUT` von `Convert` an den Dateneingang `D1` von `AUDI_OUT` weitergeleitet und steht damit am Ausgangsadapter zur Verfügung.

## Technische Besonderheiten
- **Composite-Architektur**: Der Baustein besteht ausschließlich aus der internen Verwendung des Funktionsblocks `F_LWORD_TO_UDINT` und den Adaptern. Es ist keine eigene Zustandslogik oder zusätzliche Steuerung vorhanden.
- **Unidirektionale Adapter**: Sowohl `AL_IN` als auch `AUDI_OUT` sind unidirektionale Adapter (Richtung von Eingang zu Ausgang).
- **IEC-61131-3-Konformität**: Die Konvertierung nutzt eine standardisierte IEC-61131-3-Funktion, was die Wiederverwendbarkeit und Austauschbarkeit erhöht.

## Zustandsübersicht
Der FB besitzt keine eigenen Zustände. Das Verhalten ist rein kombinatorisch und wird vollständig durch die interne Konvertierungsfunktion bestimmt – die Konvertierung erfolgt pro Ereignis ohne interne Speicherung.

## Anwendungsszenarien
- **Systemintegration**: Verbindung von Komponenten, die unterschiedliche Datentypen für Adressen, Zähler oder Konfigurationswerte verwenden (z. B. LWORD für breite Adressen, UDINT für eingebettete Systeme).
- **Adapter-Architekturen**: Einsatz in modularen Automatisierungslösungen, bei denen über Adapter standardisierte Schnittstellen bereitgestellt werden sollen.
- **Datenaufbereitung**: Konvertierung von LWORD-Signalen aus Sensoren oder Bussystemen in UDINT für die Weiterverarbeitung in Steuerungen.

## Vergleich mit ähnlichen Bausteinen
- **Einfache Typkonverter** (z. B. `F_LWORD_TO_UDINT`): Diese arbeiten direkt mit Ein-/Ausgangsvariablen, während `AL_TO_AUDI` die Konvertierung in eine Adapter-Schnittstelle kapselt und so eine höhere Abstraktionsebene bietet.
- **Andere Adapter-Konverter** (z. B. `UDINT_TO_DINT`): Ähnliche Konzepte, aber für andere Datentypen und Richtungen. `AL_TO_AUDI` ist spezifisch für die unidirektionale Wandlung von LWORD nach UDINT.

## Fazit
Der Funktionsblock `AL_TO_AUDI` ist ein kompakter und wiederverwendbarer Baustein zur Konvertierung von LWORD- auf UDINT-Daten über standardisierte Adapter. Er vereinfacht die Integration von Komponenten mit unterschiedlichen Datentypen und fördert eine modulare, adapterbasierte Architektur in der Automatisierungstechnik.
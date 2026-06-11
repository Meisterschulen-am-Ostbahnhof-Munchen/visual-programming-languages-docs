# AS_TO_AUS


![AS_TO_AUS](./AS_TO_AUS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_TO_AUS** ist ein Composite-Baustein, der einen AS-Adapter (Typ `adapter::types::unidirectional::AS`) mit einem AUS-Adapter (Typ `adapter::types::unidirectional::AUS`) verbindet und die darin enthaltenen Datenwerte von `SINT` (signed 8-Bit) nach `USINT` (unsigned 8-Bit) umwandelt. Die Konvertierung erfolgt durch den eingebetteten Standard-Baustein `F_SINT_TO_USINT` aus der IEC-61131-Bibliothek. Der FB ermöglicht eine einfache, adapterbasierte Datentypanpassung in industriellen Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt ausschließlich über den Adapter `AS_IN` (Socket).

### **Ereignis-Ausgänge**

Keine direkten Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt ausschließlich über den Adapter `AUS_OUT` (Plug).

### **Daten-Eingänge**

Keine direkten Daten-Eingänge. Die Datenaufnahme erfolgt ausschließlich über den Adapter `AS_IN`.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt ausschließlich über den Adapter `AUS_OUT`.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `AS_IN` | `adapter::types::unidirectional::AS` | Socket (Eingang) | Nimmt einen SINT-Wert sowie ein Ereignis (E1) auf. |
| `AUS_OUT` | `adapter::types::unidirectional::AUS` | Plug (Ausgang) | Gibt den konvertierten USINT-Wert sowie ein Ereignis (E1) aus. |

## Funktionsweise

Der FB arbeitet als reiner Datenfluss-Konverter:

1. Ein externes Ereignis am Socket `AS_IN.E1` löst die Konvertierung aus.
2. Gleichzeitig wird der zugehörige Datenwert `AS_IN.D1` (SINT) an den Eingang `IN` des internen Bausteins `F_SINT_TO_USINT` übergeben.
3. Der Konvertierungsbaustein wandelt den SINT-Wert in den entsprechenden USINT-Wert um und legt ihn an seinem Ausgang `OUT` an.
4. Das Abschlussereignis (`CNF`) des Konverters triggert das Ereignis `AUS_OUT.E1` und übergibt den konvertierten Wert an `AUS_OUT.D1`.
5. Der AUS-Adapter stellt das Ergebnis der aufrufenden Umgebung zur Verfügung.

## Technische Besonderheiten

- **Composite-Baustein**: Der FB enthält keine eigene Zustandslogik, sondern kombiniert den vorhandenen Standard-Konverter mit den vorgegebenen Adapter-Schnittstellen.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt – die Daten und Ereignisse fließen nur in eine Richtung.
- **Typkonvertierung**: Die Wandlung von SINT nach USINT ist verlustfrei, da der Wertebereich von USINT (0…255) den positiven Teil von SINT (−128…127) vollständig abdeckt. Negative SINT-Werte werden jedoch wie folgt interpretiert: z. B. −1 wird zu 255 (Zweierkomplement). Dieses Verhalten entspricht der IEC-61131-Funktion `SINT_TO_USINT`.

## Zustandsübersicht

Der FB besitzt keinen internen Zustandsautomaten (ECC). Die gesamte Ablaufsteuerung wird durch die Ereignisverkettung im Netzwerk realisiert.

## Anwendungsszenarien

- **Sensorintegration**: Ein Sensor liefert einen SINT-Wert (z. B. Temperatur als signed Wert), aber das nachfolgende Modul erwartet USINT (z. B. für Anzeigen oder Logik mit unsigned Typen).
- **Systemkopplung**: Zwischen verschiedenen Steuerungskomponenten, die über Adapter kommunizieren, muss eine signierte in eine unsigned Darstellung umgewandelt werden.
- **Protokollanpassung**: In Feldbus- oder OPC-UA-Anbindungen, bei denen die Datenformate vorgegeben sind.

## Vergleich mit ähnlichen Bausteinen

- **F_SINT_TO_USINT**: Dieser Standardbaustein führt die reine Typkonvertierung ohne Adapter durch. Der vorliegende FB kapselt ihn in einer Adapter-Schnittstelle, sodass er direkt in adapterbasierte Architekturen eingebunden werden kann.
- **Weitere Konverter** (z. B. `F_INT_TO_DINT`): Diese arbeiten analog, jedoch für andere Datentypen. Der Vorteil von `AS_TO_AUS` liegt in der spezifischen Adapter-Anpassung für die Typen AS und AUS.

## Fazit

Der Funktionsblock `AS_TO_AUS` ist ein praktischer Helfer zur Typumwandlung in adapterbasierten 4diac-Anwendungen. Er vereinfacht die Integration von Komponenten, die unterschiedliche vorzeichenbehaftete und vorzeichenlose 8-Bit-Datentypen verwenden, und ermöglicht eine saubere Trennung der Adapter-Schnittstellen. Durch die Verwendung des etablierten IEC-Konverters ist die Funktionalität zuverlässig und standardkonform.
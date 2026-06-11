# ALI_TO_AUDI


![ALI_TO_AUDI](./ALI_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ALI_TO_AUDI** ist ein Composite Baustein, der einen ALI-Adapter (LINT) in einen AUDI-Adapter (UDINT) umwandelt. Er dient als unidirektionaler Konverter zwischen zwei unterschiedlichen Datentyp-Adaptern für die IEC 61499-Profilschnittstelle. Die Konvertierung erfolgt über einen internen Baustein *F_LINT_TO_UDINT* aus der IEC 61131-Bibliothek.

## Schnittstellenstruktur

Der FB besitzt keine direkten Ereignis- oder Datenein-/ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen.

### **Ereignis-Eingänge**

Keine eigenen Ereignis-Eingänge vorhanden. Das Ereignis wird über den ALI-Adapter empfangen.

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge vorhanden. Das Ergebnisereignis wird über den AUDI-Adapter gesendet.

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge vorhanden. Der Eingabedatenwert wird über den ALI-Adapter bereitgestellt.

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge vorhanden. Der konvertierte Datenwert wird über den AUDI-Adapter ausgegeben.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| ALI_IN | `adapter::types::unidirectional::ALI` | Socket (Eingang) | Liefert den LINT-Wert (64-Bit signed) und das zugehörige Ereignis. |
| AUDI_OUT | `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | Stellt den konvertierten UDINT-Wert (32-Bit unsigned) und das Bestätigungsereignis bereit. |

## Funktionsweise

Sobald der ALI_IN-Adapter ein Ereignis (E1) empfängt, wird der daran gebundene LINT-Datenwert (D1) ausgelesen. Dieser Datenwert wird an den internen FB *F_LINT_TO_UDINT* übergeben, der ihn in einen UDINT-Wert umwandelt. Nach erfolgreicher Konvertierung sendet der interne FB ein Bestätigungsereignis (CNF), das über den AUDI_OUT-Adapter (E1) weitergegeben wird. Gleichzeitig wird der konvertierte UDINT-Wert (OUT) an den AUDI_OUT-Adapter (D1) übergeben.

Die Konvertierung von LINT (64-Bit signed) nach UDINT (32-Bit unsigned) erfolgt ohne Vorzeichen und kann bei Werten außerhalb des UDINT-Bereichs (0 … 4.294.967.295) zu Überläufen oder Informationsverlust führen.

## Technische Besonderheiten

- **Composite Funktionsblock**: Der FB besteht aus einem internen Netzwerk mit einem einzigen Konvertierungsbaustein.
- **Unidirektionaler Adapter-zu-Adapter-Konverter**: Die Daten fließen nur von ALI_IN nach AUDI_OUT.
- **Keine Zustandslogik**: Der FB besitzt keinen internen Zustandsautomaten; die Konvertierung erfolgt bei jedem Ereignis deterministisch.

## Zustandsübersicht

Der FB hat keinen eigenen Zustandsautomaten. Der Zustand wird allein durch den internen Baustein *F_LINT_TO_UDINT* bestimmt, der bei jedem REQ-Ereignis eine einmalige Konvertierung durchführt und sofort das Ergebnis liefert.

## Anwendungsszenarien

- **Systemintegration**: Wenn ein Systemteil (z. B. Sensor, Antrieb) einen ALI-Adapter (LINT) bereitstellt, ein anderer Teil jedoch einen AUDI-Adapter (UDINT) erwartet.
- **Protokollanpassung**: In heterogenen Steuerungsumgebungen, in denen unterschiedliche IEC 61499-Adaterprofile für Ganzzahlen verwendet werden.
- **Migration**: Austausch von 64-Bit LINT-Werten gegen 32-Bit UDINT-Werte, sofern die Wertebereichsgrenzen eingehalten werden.

## Vergleich mit ähnlichen Bausteinen

- **F_LINT_TO_UDINT (direkt)**: Dieser Baustein führt die reine Datenkonvertierung ohne Adapter durch. *ALI_TO_AUDI* kapselt diese Funktion in einer adapterbasierten Schnittstelle.
- **ALI_TO_xxx/Konverter**: Andere Adapter-Konverter (z. B. ALI_TO_BOOL, ALI_TO_REAL) verwenden analoge Mechanismen, unterscheiden sich jedoch in Zieltyp und Wertebereich.

## Fazit

Der *ALI_TO_AUDI* Funktionsblock ist ein schlanker Composite-Baustein zur einfachen Adapterkonvertierung von LINT nach UDINT. Er nutzt einen vorhandenen IEC 61131-Baustein und ergänzt ihn um eine standardisierte IEC 61499-Adapter-Schnittstelle. Dadurch wird die Integration in bestehende Systeme erleichtert, ohne dass die zugrundeliegende Konvertierungslogik neu implementiert werden muss.
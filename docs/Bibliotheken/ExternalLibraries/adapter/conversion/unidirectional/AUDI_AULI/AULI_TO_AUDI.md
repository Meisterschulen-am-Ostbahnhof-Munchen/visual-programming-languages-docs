# AULI_TO_AUDI


![AULI_TO_AUDI](./AULI_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_TO_AUDI** ist ein Composite-Baustein, der die Konvertierung eines AULI-Adapters (Daten vom Typ ULINT) zu einem AUDI-Adapter (Daten vom Typ UDINT) realisiert. Er dient als unidirektionale Brücke zwischen zwei unterschiedlichen Adaptertypen und ermöglicht die nahtlose Integration von Komponenten, die auf verschiedenen Integer-Breiten basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine separaten Ereignis-Eingänge. Das erforderliche Ereignis wird über den Socket-Adapter empfangen:
- **E1** (im Socket `AULI_IN`): Startet die Konvertierung eines ULINT-Wertes.

### **Ereignis-Ausgänge**
Es sind keine direkten Ereignis-Ausgänge vorhanden. Das Ereignis wird über den Plug-Adapter ausgegeben:
- **E1** (im Plug `AUDI_OUT`): Signalisiert den Abschluss der Konvertierung und die Bereitstellung des UDINT-Wertes.

### **Daten-Eingänge**
Daten werden ausschließlich über den Socket-Adapter bereitgestellt:
- **D1** (im Socket `AULI_IN`): ULINT-Eingabewert (64-Bit unsigned integer).

### **Daten-Ausgänge**
Daten werden über den Plug-Adapter ausgegeben:
- **D1** (im Plug `AUDI_OUT`): UDINT-Ausgabewert (32-Bit unsigned integer).

### **Adapter**
- **Socket AULI_IN**  
  Typ: `adapter::types::unidirectional::AULI`  
  Empfängt den zu konvertierenden ULINT-Wert und das zugehörige Ereignis.
- **Plug AUDI_OUT**  
  Typ: `adapter::types::unidirectional::AUDI`  
  Stellt den konvertierten UDINT-Wert und das Abschluss-Ereignis bereit.

## Funktionsweise

Der FB enthält ein internes Netzwerk mit einem einzigen Konvertierungsbaustein `F_ULINT_TO_UDINT` (aus der IEC 61131-Bibliothek).

1. Ein eingehendes Ereignis **E1** vom Socket `AULI_IN` triggert den Konvertierungsbaustein über dessen `REQ`-Event.
2. Gleichzeitig wird der ULINT-Wert von `AULI_IN.D1` an den Eingang `IN` des Konverters weitergeleitet.
3. Der Konverter wandelt den 64-Bit-Wert in einen 32-Bit-Wert um und legt das Ergebnis an seinem Ausgang `OUT` an.
4. Nach erfolgreicher Konvertierung sendet der Konverter ein Bestätigungsereignis (`CNF`), das als **E1** an den Plug `AUDI_OUT` weitergegeben wird.
5. Der umgewandelte UDINT-Wert wird an `AUDI_OUT.D1` ausgegeben.

## Technische Besonderheiten

- **Composite-FB**: Der Baustein selbst besitzt keine eigene Logik, sondern nutzt einen standardisierten IEC 61131-Konverter.
- **Adapter-Konvertierung**: Ermöglicht die Verbindung von Komponenten, die auf unterschiedlichen Adapterdefinitionen basieren, ohne dass der Anwender die Konvertierung manuell vornehmen muss.
- **Unidirektionale Datenfluss**: Die Konvertierung erfolgt nur in eine Richtung (ULINT → UDINT); eine Rückkonvertierung ist nicht integriert.
- **Keine Datenbereichsüberprüfung**: Da UDINT nur 32 Bit umfasst, gehen bei ULINT-Werten > 2³²‑1 die höherwertigen Bits verloren.

## Zustandsübersicht

Der Composite-FB besitzt keine eigene Zustandsmaschine. Das Verhalten wird vollständig durch den internen Konvertierungsbaustein `F_ULINT_TO_UDINT` bestimmt, der typischerweise einen einfachen Warte‑/Verarbeitungszustand implementiert. Nach dem Start (`REQ`) führt er die Konvertierung aus und quittiert diese mit `CNF`.

## Anwendungsszenarien

- **Adapter-Brücken**: Wenn ein System einen AULI-Adapter (z. B. für große Zähler oder Zeitstempel) bereitstellt, eine nachgelagerte Komponente jedoch einen AUDI-Adapter erwartet (z. B. für kleinere Steuerwerte).
- **Protokoll- oder Schnittstellenanpassung**: In heterogenen Automatisierungsnetzwerken, in denen unterschiedliche Integer-Größen verwendet werden.
- **Datenreduktion**: Wenn nur die unteren 32 Bit einer 64-Bit-Größe relevant sind (z. B. bei bestimmten Sensorwerten).

## Vergleich mit ähnlichen Bausteinen

- **Direkte Typumwandlungen** (z. B. `F_ULINT_TO_UDINT`): Diese arbeiten auf reinem Datenebene ohne Adapter. AULI_TO_AUDI kapselt die Umwandlung in eine adapterbasierte Schnittstelle, was den Austausch zwischen verschiedenen Adaptertypen erleichtert.
- **Bidirektionale Konverter**: Es existieren auch Bausteine für die Umkehrung (UDINT → ULINT). Der vorliegende FB ist auf eine Richtung spezialisiert.
- **Composite-Adapter**: Andere Composite-FBs können mehrere Konvertierungen oder zusätzliche Logik (z. B. Bereichsprüfung) enthalten – hier liegt der Fokus auf Einfachheit und Wiederverwendbarkeit.

## Fazit

Der AULI_TO_AUDI ist ein kompakter, spezialisierter Composite-Baustein, der die Umwandlung eines AULI- (ULINT) in einen AUDI-Adapter (UDINT) sauber kapselt. Dank der Integration des standardisierten Konverters ist er zuverlässig und einfach in bestehende 4diac‑Projekte einbindbar. Er eignet sich ideal für Szenarien, in denen unterschiedliche Adapterdefinitionen aufeinandertreffen, und trägt zur Modularität und Wiederverwendbarkeit von Funktionsbausteinen bei.
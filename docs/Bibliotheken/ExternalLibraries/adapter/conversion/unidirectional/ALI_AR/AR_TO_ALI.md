# AR_TO_ALI


![AR_TO_ALI](./AR_TO_ALI.svg)

* * * * * * * * * *

## Einleitung

Der Composite Funktionsblock `AR_TO_ALI` dient der Umwandlung eines REAL-Adapters (`AR-IN`) in einen LINT-Adapters (`ALI-OUT`). Er ermöglicht die nahtlose Integration von Gleitkommawerten aus dem Adapter `AR` in Applikationen, die ganzzahlige 64‑Bit‑Werte über den Adapter `ALI` erwarten. Die Konvertierung erfolgt über einen internen Baustein `F_REAL_TO_LINT` nach IEC 61131.

## Schnittstellenstruktur

Der FB besitzt keine eigenständigen Ereignis‑ oder Dateneingänge/-ausgänge auf Blockebene. Die gesamte Signalübertragung erfolgt über Adapter‑Sockets bzw.‑Plugs.

### **Ereignis-Eingänge**

Keine eigenständigen Ereignis-Eingänge. Das Ereignis wird über den Socket `AR_IN` (Schnittstelle `E1`) empfangen.

### **Ereignis-Ausgänge**

Keine eigenständigen Ereignis-Ausgänge. Das Ereignis wird über den Plug `ALI_OUT` (Schnittstelle `E1`) gesendet.

### **Daten-Eingänge**

Keine eigenständigen Daten-Eingänge. Die Daten werden über den Socket `AR_IN` (Schnittstelle `D1`) empfangen.

### **Daten-Ausgänge**

Keine eigenständigen Daten-Ausgänge. Die Daten werden über den Plug `ALI_OUT` (Schnittstelle `D1`) gesendet.

### **Adapter**

| Richtung | Bezeichnung | Typ | Kompatibler Adaptertyp | Beschreibung |
|----------|-------------|-----|------------------------|--------------|
| Socket   | `AR_IN`    | `adapter::types::unidirectional::AR` | AR‑Adapter (REAL) | Aufnehmender Adapter für den REAL‑Wert. |
| Plug     | `ALI_OUT`  | `adapter::types::unidirectional::ALI` | ALI‑Adapter (LINT) | Bereitstellender Adapter für den konvertierten LINT‑Wert. |

## Funktionsweise

Im inneren Netzwerk wird der FB `iec61131::conversion::F_REAL_TO_LINT` instanziiert. Sobald am Socket `AR_IN` ein Ereignis anliegt (über die Schnittstelle `E1`), wird der interne Konvertierungsbaustein mit der dafür vorgesehenen Ereignisverbindung `AR_IN.E1 -> Convert.REQ` angestoßen. Gleichzeitig wird der Datenwert `AR_IN.D1` an den Eingang `Convert.IN` übergeben. Nach erfolgter Umrechnung (REAL → LINT) bestätigt der Konverter mit dem Ereignis `Convert.CNF`. Dieses Ereignis wird an den Plug `ALI_OUT.E1` weitergeleitet, und der konvertierte Wert `Convert.OUT` wird auf `ALI_OUT.D1` ausgegeben.

## Technische Besonderheiten

- **Reine Adapter‑Kopplung**: Der FB verwendet keine direkten Ereignis‑ oder Dateneingänge, sondern kommuniziert ausschließlich über die standardisierten unidirektionalen Adapter `AR` und `ALI`. Dadurch lässt er sich leicht in bestehende Adapter‑Strukturen einfügen.
- **IEC 61131‑Konformität**: Der eingesetzte Konvertierungsbaustein `F_REAL_TO_LINT` entspricht der IEC‑Norm und stellt eine standardisierte, deterministische Umwandlung sicher.
- **Laufzeitverhalten**: Die Konvertierung erfolgt ereignisgesteuert und ohne zusätzliche Verzögerung; die Ausgangsgröße liegt im selben Ausführungszyklus an, in dem das Eingangsereignis empfangen wird.

## Zustandsübersicht

Der Composite FB selbst besitzt keinen eigenen Zustandsautomaten. Sein Verhalten wird vollständig durch die interne Verschaltung bestimmt. Es existieren folgende logische Zustände:

- **Idle**: Kein Ereignis am Eingang. Der Ausgang `ALI_OUT` bleibt unverändert.
- **Converting**: Ein Ereignis am Socket `AR_IN` wird empfangen. Der interne Konverter wird aktiviert, und die Konvertierung läuft.
- **Completed**: Die Konvertierung ist abgeschlossen; das Ausgangsereignis wird gesendet und der neue Datenwert liegt am Plug an.

## Anwendungsszenarien

- **Sensor‑Aktor‑Kopplung**: Ein REAL‑Adapter (z. B. von einem analogen Sensor) muss an ein Steuermodul angebunden werden, das ausschließlich LINT‑Werte über den ALI‑Adapter verarbeitet.
- **Protokoll‑Wandlung**: In heterogenen Automatisierungsnetzwerken, in denen Datenformate konvertiert werden müssen, um unterschiedliche Adaptertypen miteinander zu verbinden.
- **Test‑ und Simulationsumgebungen**: Ersetzen eines ALI‑Adapters durch einen simulierten REAL‑Adapter und Rückkonvertierung für Testzwecke.

## Vergleich mit ähnlichen Bausteinen

| FB | Konvertierung | Schnittstelle | Anmerkung |
|----|---------------|---------------|-----------|
| `AR_TO_ALI`  | REAL → LINT | AR / ALI‑Adapter | Speziell für Adapter‑kopplung |
| `F_REAL_TO_LINT` | REAL → LINT | Eigenständige E/A (REQ/CNF, IN/OUT) | Direkter Konverter ohne Adapter |
| `AR_TO_ALI` umschließt `F_REAL_TO_LINT` und fügt die Adapter‑Anschlüsse hinzu. Der Vorteil liegt in der einfachen adapternetzwerktauglichen Anbindung. Ein direkter Konverter ohne Adapter wäre in Adapter‑Strukturen nicht einsetzbar. |

## Fazit

`AR_TO_ALI` ist ein kompakter, zweckgebundener Composite‑FB, der die Konvertierung von REAL‑ nach LINT‑Werten über die standardisierten unidirektionalen Adapter `AR` und `ALI` ermöglicht. Durch die saubere Kapselung und die Verwendung eines IEC‑konformen Kernbausteins wird eine zuverlässige und wiederverwendbare Lösung für die industrielle Automatisierung bereitgestellt. Der FB eignet sich besonders für Szenarien, in denen eine saubere Trennung zwischen Datenformat und Adapter‑Schnittstelle erforderlich ist.
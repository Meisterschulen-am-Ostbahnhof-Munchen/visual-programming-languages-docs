# ALR_TO_AUS


![ALR_TO_AUS](./ALR_TO_AUS.svg)

* * * * * * * * * *
## Einleitung
Der Composite-Funktionsblock **ALR_TO_AUS** dient als universeller Konverter zwischen zwei unidirektionalen Adapterprotokollen. Er wandelt einen LREAL-Wert (64‑Bit Gleitkomma) in einen USINT-Wert (8‑Bit vorzeichenlose Ganzzahl) um. Der Block wurde für den Einsatz in IEC 61499‑basierten Automatisierungssystemen entwickelt und nutzt intern den Standard-Funktionsblock `F_LREAL_TO_USINT` aus der Bibliothek `iec61131::conversion`.

## Schnittstellenstruktur
Da es sich um einen Composite-Baustein handelt, werden alle Ein- und Ausgänge über Adapter realisiert.

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge auf der obersten Ebene.  
  Der über den **Socket ALR_IN** angebundene Adapter besitzt jedoch den Ereignis-Eingang **E1**, der die Konvertierung auslöst.

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge auf der obersten Ebene.  
  Der über den **Plug AUS_OUT** angebundene Adapter stellt den Ereignis-Ausgang **E1** bereit, der den Abschluss der Konvertierung signalisiert.

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge auf der obersten Ebene.  
  Der Adapter **ALR_IN** führt den Daten-Eingang **D1** (Typ: LREAL), der den zu konvertierenden Gleitkommawert bereitstellt.

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge auf der obersten Ebene.  
  Der Adapter **AUS_OUT** führt den Daten-Ausgang **D1** (Typ: USINT), der das konvertierte Ganzzahlergebnis ausgibt.

### **Adapter**

| Name      | Typ                                          | Richtung | Kommentar                       |
|-----------|----------------------------------------------|----------|---------------------------------|
| `ALR_IN`  | `adapter::types::unidirectional::ALR`        | Socket   | Unidirektionaler LREAL-Eingang  |
| `AUS_OUT` | `adapter::types::unidirectional::AUS`        | Plug     | Unidirektionaler USINT-Ausgang  |

## Funktionsweise
Der Funktionsblock arbeitet ereignisgesteuert:
1. Ein eingehendes Ereignis am Adapter-Eingang `ALR_IN.E1` wird intern mit dem **REQ**-Eingang des Konvertierungsbausteins `F_LREAL_TO_USINT` verbunden.
2. Gleichzeitig wird der Datenwert `ALR_IN.D1` an den Daten-Eingang `IN` des Konvertierungsbausteins übergeben.
3. Der Konverter führt die Umwandlung von LREAL nach USINT durch. Hierbei wird der Gleitkommawert gemäß IEC 61131‑3 auf den nächstliegenden ganzzahligen USINT-Wert (0–255) gerundet oder abgeschnitten.
4. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` des Konverters erzeugt, das direkt an den Adapter-Ausgang `AUS_OUT.E1` weitergeleitet wird.
5. Das Ergebnis `OUT` des Konverters wird an den Daten-Ausgang `AUS_OUT.D1` übergeben.

Dadurch wird eine synchrone, datengekoppelte Umsetzung ohne zusätzliche Verzögerung durchgeführt.

## Technische Besonderheiten
- **Composite‑Aufbau**: Der Block kapselt die Konvertierungslogik in einer wiederverwendbaren Einheit und nutzt die standardisierten Adaptertypen `ALR` und `AUS`. Dadurch kann er nahtlos in bestehende unidirektionale Kommunikationsprotokolle eingebunden werden.
- **Standardkonforme Umwandlung**: Die eigentliche Konvertierung erfolgt durch den IEC 61131‑Baustein `F_LREAL_TO_USINT`, der ein definiertes Verhalten (z.B. Runden oder Kappen) gemäß der Norm garantiert.
- **EPL‑2.0 Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 veröffentlicht, was eine uneingeschränkte Nutzung in proprietären und Open‑Source‑Projekten ermöglicht.
- **Keine Zustandsmaschine**: Als Composite besitzt der Block keinen eigenen Zustandsautomaten; die interne Steuerung wird vollständig durch den verwendeten Konverterbaustein übernommen.

## Zustandsübersicht
Der Baustein selbst besitzt keine explizite Zustandsmaschine. Der eingebettete Funktionsblock `F_LREAL_TO_USINT` realisiert typischerweise die Zustände **IDLE** und **BUSY** sowie **ERROR** bei dieser Umwandlung. Bei ungültigen Eingaben (z.B. Überlauf des USINT-Bereichs) kann der Konverter einen Fehler auslösen, der jedoch in dieser Version nicht gesondert an die Adapterausgänge weitergegeben wird.

## Anwendungsszenarien
- **Sensorik / Aktorik‑Anbindung**: Wenn ein Gleitkomma-Sensorwert (z.B. Druck, Temperatur) in ein 8‑Bit‑Signal für einen einfachen Aktor (z.B. Schalterstellung, Helligkeit) umgesetzt werden muss.
- **Protokollanpassung**: In Systemen, die zwischen verschiedenen Adaptertypen für die Datenübertragung vermitteln, wie z.B. in Feldbus-Kopplern oder Gateway-Funktionen.
- **Test und Simulation**: Zur einfachen Umwandlung von LREAL‑Testdaten in USINT‑Formate, um die Funktionsweise nachgeschalteter Bausteine zu prüfen.

## Vergleich mit ähnlichen Bausteinen
- **LREAL_TO_INT / LREAL_TO_DWORD**: Diese Bausteine liefern andere Ausgabetypen (INT, DWORD) und sind daher für Zielplattformen mit breiteren oder vorzeichenbehafteten Ganzzahlen geeignet.
- **REAL_TO_USINT**: Für 32‑Bit Gleitkommazahlen (REAL) steht eine entsprechende Variante zur Verfügung. Der vorliegende Baustein nutzt jedoch den präziseren LREAL-Typ.
- **Skalierung mit arithmetischen Bausteinen**: Eine manuelle Umrechnung mittels `MUL` und `ADD` wäre möglich, aber weniger standardisiert und fehleranfällig. Der `ALR_TO_AUS`-Block bietet eine geprüfte, normenkonforme Lösung.

## Fazit
Der Funktionsblock **ALR_TO_AUS** ist ein spezialisierter, aber unverzichtbarer Helfer für die Umwandlung von LREAL- in USINT-Daten in IEC 61499‑Applikationen. Sein Composite-Design erlaubt eine saubere Trennung der Konvertierungslogik und eine einfache Integration über standardisierte Adapter. Er eignet sich besonders für Szenarien, in denen präzise Gleitkommawerte auf einen engen Ganzzahlbereich abgebildet werden müssen.
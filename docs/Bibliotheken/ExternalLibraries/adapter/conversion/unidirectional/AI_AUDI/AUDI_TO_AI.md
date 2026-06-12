# AUDI_TO_AI


![AUDI_TO_AI](./AUDI_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Der Composite-Funktionsblock `AUDI_TO_AI` dient der Umwandlung eines unidirektionalen AUDI-Adapters (Datentyp `UDINT`) in einen unidirektionalen AI-Adapter (Datentyp `INT`). Er kapselt die Konvertierungslogik und ermöglicht eine einfache Integration in Adapter-basierte Kommunikationsstrukturen gemäß IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Socket `AUDI_IN` vom Typ `adapter::types::unidirectional::AUDI`. Dieser Adapter stellt einen Ereignis-Eingang `E1` bereit, der die Konvertierung anstößt.

### **Ereignis-Ausgänge**
Der FB besitzt keine direkten Ereignis-Ausgänge. Die Ereignisausgabe erfolgt über den Plug `AI_OUT` vom Typ `adapter::types::unidirectional::AI`. Dieser Adapter stellt einen Ereignis-Ausgang `E1` bereit, der den Abschluss der Konvertierung signalisiert.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der Socket `AUDI_IN` liefert über seinen Daten-Eingang `D1` den umzuwandelnden `UDINT`-Wert.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der Plug `AI_OUT` gibt über seinen Daten-Ausgang `D1` den konvertierten `INT`-Wert aus.

### **Adapter**
- **Socket `AUDI_IN`**: Typ `adapter::types::unidirectional::AUDI` – empfängt einen unidirektionalen Datenwert vom Typ `UDINT` sowie ein dazugehöriges Ereignis.
- **Plug `AI_OUT`**: Typ `adapter::types::unidirectional::AI` – sendet einen unidirektionalen Datenwert vom Typ `INT` sowie ein dazugehöriges Ereignis.

## Funktionsweise
Der FB ist als Composite-Baustein realisiert. Intern wird der Socket `AUDI_IN` mit dem Standard-Konvertierungsbaustein `iec61131::conversion::F_UDINT_TO_INT` verbunden, dessen Ausgang wiederum mit dem Plug `AI_OUT` verknüpft ist.  
Wird über den Adapter-Eingang `AUDI_IN.E1` ein Ereignis empfangen, wird der zugehörige Datenwert `AUDI_IN.D1` an den Konvertierungsbaustein übergeben. Nach erfolgreicher Umwandlung von `UDINT` nach `INT` wird das Ereignis `Convert.CNF` erzeugt und über `AI_OUT.E1` ausgegeben. Gleichzeitig steht der konvertierte Wert an `AI_OUT.D1` zur Verfügung.

## Technische Besonderheiten
- Nutzt einen standardisierten IEC 61131-Konvertierungsbaustein, der plattformunabhängig implementiert werden kann.
- Die Umwandlung von `UDINT` (32 Bit ohne Vorzeichen) nach `INT` (16 Bit mit Vorzeichen) ist potenziell verlustbehaftet. Bei Wertebereichsüberschreitung kann je nach Implementierung des Konvertierungsbausteins ein Überlauf oder eine Begrenzung auftreten.
- Die Verwendung unidirektionaler Adapter stellt einen klaren Datenfluss sicher und erleichtert die Integration in modulare Systeme.
- Der FB besitzt keine eigene Zustandsmaschine; die gesamte Logik wird ereignisgesteuert durch die interne Verdrahtung ausgeführt.

## Zustandsübersicht
Der Baustein verfügt über keinen internen Zustandsautomaten. Die Funktionalität ergibt sich ausschließlich aus der kausalen Verkettung von Ereignis- und Datenverbindungen. Es existiert lediglich ein aktiver Zustand, in dem eine eintreffende Ereignis-Daten-Kombination verarbeitet und die Ausgabe erzeugt wird.

## Anwendungsszenarien
- Anbindung eines Sensors, der Messwerte als `UDINT` liefert, an ein Steuerungssystem, das `INT`-Werte erwartet (z. B. SPS mit 16-Bit-Analogeingängen).
- Integration in PROFINET- oder EtherCAT-Anwendungen, bei denen Adapter zur Typanpassung zwischen unterschiedlichen Datenformaten benötigt werden.
- Wiederverwendbare Kapselung der Konvertierung in einer Adapter-basierten Bibliothek für industrielle Automatisierungslösungen.

## Vergleich mit ähnlichen Bausteinen
- Ein direkter Konvertierungsbaustein wie `F_UDINT_TO_INT` erfordert separate Ereignis- und Datenverbindungen und ist nicht für den direkten Einsatz in Adapter-Schnittstellen ausgelegt.
- `AUDI_TO_AI` kapselt die gesamte Adapterkonvertierung und vereinfacht so die Wiederverwendung in Architekturen, die auf unidirektionalen Adaptern basieren.
- Analoge Bausteine für andere Datentypen (z. B. `REAL_TO_INT` oder `DINT_TO_INT`) folgen demselben Entwurfsmuster und können nach dem gleichen Schema realisiert werden.

## Fazit
Der Composite-Baustein `AUDI_TO_AI` bietet eine saubere und wiederverwendbare Lösung zur verlustbehafteten Umwandlung von `UDINT`- in `INT`-Werte unter Verwendung unidirektionaler Adapter. Er vereinfacht die Integration in IEC 61499-Systeme, die auf Adapterkommunikation setzen, und kapselt die Konvertierungslogik in einem einzigen, klar definierten Funktionsblock.
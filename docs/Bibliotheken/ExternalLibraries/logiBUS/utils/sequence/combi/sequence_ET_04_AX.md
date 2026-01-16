# sequence_ET_04_AX

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_04_AX` ist eine Variante des `sequence_ET_04`, der zusätzlich Adapter (`AX`) für die Ausgänge verwendet. Er steuert eine Sequenz mit 4 Ausgabezuständen, wobei Übergänge ereignis- oder zeitgesteuert sein können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **START_S1**: Startet die Sequenz bei State_01.
*   **S1_S2**: Manueller Übergang State_01 -> State_02.
*   **S2_S3**: Manueller Übergang State_02 -> State_03.
*   **S3_S4**: Manueller Übergang State_03 -> State_04.
*   **S4_START**: Manueller Übergang State_04 -> START.
*   **RESET**: Setzt die Sequenz zurück.

### **Ereignis-Ausgänge**
*   **CNF**: Bestätigung der Ausführung mit aktueller Zustandsnummer.

### **Daten-Eingänge**
*   **DT_S1_S2**: Zeit für Übergang State_01 -> State_02.
*   **DT_S2_S3**: Zeit für Übergang State_02 -> State_03.
*   **DT_S3_S4**: Zeit für Übergang State_03 -> State_04.
*   **DT_S4_START**: Zeit für Übergang State_04 -> START.

### **Daten-Ausgänge**
*   **STATE_NR** (SINT): Aktuelle Zustandsnummer.

### **Adapter**
*   **DO_S1** (adapter::types::unidirectional::AX): Ausgangsadapter für State_01.
*   **DO_S2** (adapter::types::unidirectional::AX): Ausgangsadapter für State_02.
*   **DO_S3** (adapter::types::unidirectional::AX): Ausgangsadapter für State_03.
*   **DO_S4** (adapter::types::unidirectional::AX): Ausgangsadapter für State_04.
*   **timeOut** (iec61499::events::ATimeOut): Timer-Adapter.

## Funktionsweise
Die Funktionsweise entspricht im Wesentlichen dem `sequence_ET_04`, jedoch werden die Ausgänge `DO_S1` bis `DO_S4` nicht als einfache BOOL-Variablen, sondern über Adapter gesetzt. Dies ermöglicht eine flexiblere Anbindung in komplexeren Systemen.

## Technische Besonderheiten
*   Verwendung von `adapter::types::unidirectional::AX` für die Ausgänge.

## Zustandsübersicht
Siehe `sequence_ET_04`.

## Anwendungsszenarien
Ähnlich wie `sequence_ET_04`, aber bevorzugt, wenn Adapterverbindungen genutzt werden sollen.

## Vergleich mit ähnlichen Bausteinen
*   **sequence_ET_04**: Die Standardvariante mit einfachen BOOL-Ausgängen.

## Fazit
`sequence_ET_04_AX` bietet die Funktionalität des `sequence_ET_04` mit modernerer Adapter-Schnittstelle.

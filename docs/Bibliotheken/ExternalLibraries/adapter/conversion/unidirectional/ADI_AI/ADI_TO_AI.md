# ADI_TO_AI


![ADI_TO_AI](./ADI_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **ADI_TO_AI** ist ein Composite FB, der einen DINT-Adapter (ADI) in einen INT-Adapter (AI) umwandelt. Er dient als unidirektionale Konvertierungsschnittstelle zwischen zwei Adapter-Typen und nutzt intern den Baustein `F_DINT_TO_INT` zur Typumwandlung der Datenwerte.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine separaten Ereignis-Eingänge. Die ereignisgesteuerte Verarbeitung erfolgt über den **Socket ADI_IN**:
- **ADI_IN.E1** – Ereignis zur Anforderung der Konvertierung (wird intern an den `Convert.REQ` weitergeleitet).

### **Ereignis-Ausgänge**
Der FB besitzt keine separaten Ereignis-Ausgänge. Die Ergebnis-Rückmeldung erfolgt über den **Plug AI_OUT**:
- **AI_OUT.E1** – Ereignis, das nach erfolgreicher Konvertierung ausgelöst wird (entspricht `Convert.CNF`).

### **Daten-Eingänge**
Der FB besitzt keine separaten Daten-Eingänge. Die Eingangsdaten werden über den **Socket ADI_IN** bereitgestellt:
- **ADI_IN.D1** – DINT-Wert (32-Bit-Ganzzahl), der in einen INT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
Der FB besitzt keine separaten Daten-Ausgänge. Die Ergebnisdaten werden über den **Plug AI_OUT** ausgegeben:
- **AI_OUT.D1** – INT-Wert (16-Bit-Ganzzahl), das Ergebnis der Konvertierung.

### **Adapter**
- **Socket**: `ADI_IN` (Typ `adapter::types::unidirectional::ADI`) – DINT-Adapter-Eingang.
- **Plug**: `AI_OUT` (Typ `adapter::types::unidirectional::AI`) – INT-Adapter-Ausgang.

## Funktionsweise
Der Baustein verbindet die Adapter-Schnittstellen direkt mit einer internen Instanz des Konvertierungsbausteins `F_DINT_TO_INT`:
1. Ein Ereignis an `ADI_IN.E1` triggert den `Convert.REQ`.
2. Der Wert von `ADI_IN.D1` wird an `Convert.IN` übergeben.
3. Die Konvertierung `DINT → INT` wird durchgeführt.
4. Nach Abschluss signalisiert `Convert.CNF` das Ereignis an `AI_OUT.E1` und der konvertierte Wert von `Convert.OUT` wird an `AI_OUT.D1` weitergeleitet.

## Technische Besonderheiten
- **Keine eigene Zustandsmaschine**: Der FB ist ein reines Composite (Netzwerk) ohne ECC. Das Verhalten wird ausschließlich durch die interne Verbindung und den verwendeten Konvertierungsbaustein bestimmt.
- **Typkonvertierung**: Die Umwandlung von DINT nach INT erfolgt gemäß IEC 61131-3 (Überlauf bei Wertebereichsüberschreitung wird nicht abgefangen; INT-Bereich: -32768 … 32767).
- **Paket**: Der FB ist im Paket `adapter::conversion::unidirectional` organisiert.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine. Das Verhalten ist rein datenflussgesteuert: Auf jedes eingehende Ereignis erfolgt genau eine Konvertierung und eine Ausgabe.

## Anwendungsszenarien
- **Integration von DINT-basierten Komponenten** in eine Umgebung, die ausschließlich INT-Adapter unterstützt (z. B. ältere Steuerungen oder standardisierte Schnittstellen).
- **Typanpassung** in heterogenen Automatisierungssystemen, bei denen unterschiedliche Datenbreiten verwendet werden.

## Vergleich mit ähnlichen Bausteinen
- **AI_TO_ADI**: Die umgekehrte Konvertierung (INT → DINT). Während `ADI_TO_AI` den Wertebereich verkleinert (potenzieller Datenverlust), erweitert `AI_TO_ADI` den Wertebereich ohne Informationsverlust.
- **Direkte Adapter-Kopplung**: Ohne Konvertierung müssten die Adapter-Typen exakt übereinstimmen. `ADI_TO_AI` ermöglicht die Kommunikation zwischen inkompatiblen Typen.

## Fazit
Der Baustein `ADI_TO_AI` ist ein einfacher, aber nützlicher Konverter, der die Lücke zwischen DINT- und INT-Adapter-Schnittstellen schließt. Durch seine Composite-Struktur ist er leicht verständlich und wartbar. Die Verwendung des standardisierten `F_DINT_TO_INT` stellt die korrekte Umwandlung sicher.
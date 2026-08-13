# ADI_ADD_4


![ADI_ADD_4](./ADI_ADD_4.svg)

*(Bild des Funktionsblocks nicht verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ADI_ADD_4` dient zur Durchführung einer arithmetischen Addition von bis zu vier Werten. Es handelt sich hierbei um einen generischen Funktionsbaustein (Generic FB), der auf dem unidirektionalen Adaptertyp `ADI` basiert. Er ermöglicht eine übersichtliche und modularisierte Addition innerhalb von IEC 61499 Anwendungen in der 4diac-IDE.

## Schnittstellenstruktur

Da der Baustein vollständig auf Adaptern basiert, verfügt er über keine klassischen, separaten Ereignis- oder Datenkanäle auf der Hauptebene des Typs.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird über die angebundenen Adapter realisiert.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung wird über den Ausgangs-Adapter realisiert.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

*   **Sockets (Eingangs-Adapter / Buchsen):**
    *   `IN1` (Typ: `adapter::types::unidirectional::ADI`): Eingang für den ersten Summanden.
    *   `IN2` (Typ: `adapter::types::unidirectional::ADI`): Eingang für den zweiten Summanden.
    *   `IN3` (Typ: `adapter::types::unidirectional::ADI`): Eingang für den dritten Summanden.
    *   `IN4` (Typ: `adapter::types::unidirectional::ADI`): Eingang für den vierten Summanden.
*   **Plugs (Ausgangs-Adapter / Stecker):**
    *   `OUT` (Typ: `adapter::types::unidirectional::ADI`): Ausgang für das berechnete Gesamtergebnis der Addition.

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1` bis `IN4`) neue Datenwerte oder entsprechende Trigger-Ereignisse anliegen, führt der Funktionsbaustein die Addition der Werte durch. Das Ergebnis wird berechnet nach der Formel:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Das berechnete Resultat sowie das zugehörige Trigger-Ereignis werden direkt über den Ausgangs-Adapter `OUT` bereitgestellt.

## Technische Besonderheiten

*   **Generischer Baustein:** Durch die Zuordnung des Attributs `GenericClassName` mit dem Wert `'GEN_ADI_ADD'` ist der Baustein flexibel aufgebaut. Er kann je nach Implementierung des zugrundeliegenden `ADI`-Adapters für verschiedene numerische Datentypen verwendet werden.
*   **Adapterbasiertes Design:** Die Kapselung von Daten und Events in Adaptern (hier vom Typ `ADI`) minimiert den Verdrahtungsaufwand im Funktionsplan der 4diac-IDE drastisch und sorgt für ein sauberes, strukturiertes Anwendungsdesign.
*   **Unidirektionale Kopplung:** Die Verwendung von unidirektionalen Adaptern stellt sicher, dass der Datenfluss strikt sequenziell von den Eingängen zum Ausgang verläuft.

## Zustandsübersicht

Da es sich um einen adapterbasierten Baustein zur reinen arithmetischen Datenverarbeitung handelt, besitzt der `ADI_ADD_4` keine komplexe interne Zustandsmaschine (ECC). Seine Ausführung verhält sich rein reaktiv:
*   **Trigger an einem der Eingänge (`IN1` - `IN4`):** Berechnung der Summe aller vier Eingänge und unmittelbare Weiterleitung des Ergebnisses an `OUT`.

## Anwendungsszenarien

*   **Sensordaten-Aggregation:** Zusammenführen von bis zu vier analogen Messwerten (z. B. vier einzelnen Durchflussmessern oder Temperatursensoren) zu einem Gesamtwert.
*   **Sollwertberechnung mit Offsets:** Addition eines Hauptsollwerts mit bis zu drei verschiedenen Korrekturfaktoren oder Offsets in Regelungsprozessen.
*   **Strukturierte Signalverarbeitung:** Einsatz in Systemen, bei denen die Signalverarbeitungskette durchgehend auf dem `ADI`-Adapterstandard basiert, um unnötiges Entpacken und Verpacken von Signalen zu vermeiden.

## Vergleich mit ähnlichen Bausteinen

*   **Standard-Addierer (z. B. `F_ADD`):** Ein klassischer IEC 61131-3 Addier-Baustein benötigt separate Datenleitungen und Event-Verbindungen. `ADI_ADD_4` bündelt diese in Adaptern, was die visuelle Komplexität im Editor reduziert.
*   **Zweifach-Addierer (`ADI_ADD_2`):** Zur Addition von vier Werten müssten drei zweifache Addierer kaskadiert werden. Der `ADI_ADD_4` spart hierbei signifikant Platz und Ausführungszeit, indem er die Berechnung in einem einzigen Schritt bündelt.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `ADI_ADD_4` ist ein performanter und effizienter Funktionsbaustein zur Addition von vier numerischen Signalen. Durch die konsequente Nutzung von Adaptern reduziert er die Anzahl der physischen Verbindungen im Steuerungsprogramm und trägt maßgeblich zu einer übersichtlichen und wartungsfreundlichen Softwarearchitektur bei.
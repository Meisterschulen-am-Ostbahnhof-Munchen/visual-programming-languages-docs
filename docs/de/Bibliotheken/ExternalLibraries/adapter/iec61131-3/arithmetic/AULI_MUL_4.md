# AULI_MUL_4


![AULI_MUL_4](./AULI_MUL_4.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_MUL_4` ist ein generischer arithmetischer Baustein für die 4diac-ide. Er dient zur Multiplikation von vier Eingangswerten. Der Baustein nutzt ein adapterbasiertes Schnittstellenkonzept, um die Anzahl der einzelnen Event- und Datenverbindungen im Applikationsdiagramm zu minimieren und eine saubere Kapselung zu gewährleisten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübertragung erfolgt gekapselt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenübertragung erfolgt gekapselt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AULI`): Erster Multiplikand.
-   **IN2** (Typ: `adapter::types::unidirectional::AULI`): Zweiter Multiplikand.
-   **IN3** (Typ: `adapter::types::unidirectional::AULI`): Dritter Multiplikand.
-   **IN4** (Typ: `adapter::types::unidirectional::AULI`): Vierter Multiplikand.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AULI`): Ergebnis der Multiplikation.

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1` bis `IN4`) neue Werte signalisiert werden, führt der Baustein die Multiplikation der vier Werte durch.

Die mathematische Formel lautet:
$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3} \times \text{IN4}$$

Das Ergebnis sowie das zugehörige Verarbeitungsereignis werden anschließend über den Ausgangs-Adapter `OUT` ausgegeben. Da es sich um unidirektionale Adapter des Typs `AULI` handelt, fließen Daten und Trigger-Signale gerichtet von den Sockets zum Plug.

## Technische Besonderheiten

-   **Generischer Baustein:** Der Baustein ist als generischer Typ deklariert (`GenericClassName = 'GEN_AULI_MUL'`). Dies ermöglicht eine flexible Anpassung an unterschiedliche numerische Datentypen, die vom zugrundeliegenden `AULI`-Adaptertyp unterstützt werden.
-   **Kapselung durch Adapter:** Durch die Verwendung von Adaptern anstelle von Standard-Event-/Daten-Pins wird das Systemdesign stark vereinfacht ("Spaghetti-Verdrahtung" im Control-Flow wird vermieden).

## Zustandsübersicht

Der Funktionsbaustein verhält sich im Wesentlichen zustandslos (*stateless*). Die Berechnung erfolgt rein reaktiv auf Basis der an den Eingangs-Adaptern anliegenden Werte und Events. Es werden keine internen historischen Zustände gespeichert.

## Anwendungsszenarien

-   **Sensorwert-Skalierung:** Berechnung von korrigierten Messwerten, bei denen ein Rohwert mit mehreren Kalibrierungs-, Korrektur- oder Umrechnungsfaktoren multipliziert werden muss.
-   **Volumen- und Massenberechnung:** Physikalische Berechnungen in der Prozesstechnik, die das Produkt mehrerer Variablen erfordern (z. B. $V = l \times b \times h$ unter Berücksichtigung eines zusätzlichen Dichtefaktors).
-   **Strukturierte Signalverarbeitung:** Einsatz in komplexeren Steuerungsanwendungen, bei denen Daten modular über Adapterstrukturen verteilt werden.

## Vergleich mit ähnlichen Bausteinen

-   **Standard-MUL-Baustein (IEC 61131-3 / IEC 61499):** Standard-Multiplizierer besitzen meist dedizierte Pins wie `REQ`, `CNF` sowie klassische Daten-Eingänge (z. B. `IN1`, `IN2`). `AULI_MUL_4` vereinfacht das Schnittstellendesign durch die Nutzung von Adaptern erheblich.
-   **Kaskadierte 2-fach Multiplizierer:** Um vier Werte mit Standardbausteinen zu multiplizieren, müssten drei herkömmliche `MUL`-Bausteine kaskadiert werden. `AULI_MUL_4` bündelt diese Logik in einem einzigen Baustein, was Ressourcen spart und die Übersichtlichkeit erhöht.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AULI_MUL_4` ist ein praktischer und moderner Funktionsbaustein zur Multiplikation von vier numerischen Werten unter Verwendung des IEC 61499 Adapterkonzepts. Er eignet sich hervorragend für sauber strukturierte, lesbare und wartungsfreundliche Steuerungsapplikationen in der 4diac-ide.

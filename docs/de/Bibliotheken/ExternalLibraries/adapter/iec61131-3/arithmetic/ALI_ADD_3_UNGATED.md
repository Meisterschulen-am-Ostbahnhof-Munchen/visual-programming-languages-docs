# ALI_ADD_3_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ALI_ADD_3`](ALI_ADD_3.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![ALI_ADD_3_UNGATED](./ALI_ADD_3_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALI_ADD_3_UNGATED` ist ein generischer, arithmetischer Baustein zur Addition von drei Werten. Er basiert auf dem Standard IEC 61131-3 für arithmetische Funktionen. Anstelle von klassischen, separaten Daten- und Ereignisanschlüssen nutzt dieser Baustein unidirektionale Adapter des Typs `ALI`, um eine strukturierte und übersichtliche Signalübertragung in 4diac-ide zu ermöglichen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Steuerung und Triggerung erfolgt implizit über die angeschlossenen Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

Der Baustein kommuniziert ausschließlich über Adapter-Schnittstellen:

-   **Sockets (Eingangs-Schnittstellen):**
    -   `IN1` (Typ: `adapter::types::unidirectional::ALI`): Schnittstelle für den ersten Summanden (Eingangswert 1).
    -   `IN2` (Typ: `adapter::types::unidirectional::ALI`): Schnittstelle für den zweiten Summanden (Eingangswert 2).
    -   `IN3` (Typ: `adapter::types::unidirectional::ALI`): Schnittstelle für den dritten Summanden (Eingangswert 3).
-   **Plugs (Ausgangs-Schnittstellen):**
    -   `OUT` (Typ: `adapter::types::unidirectional::ALI`): Schnittstelle zur Ausgabe des berechneten Ergebnisses.

## Funktionsweise

Der Baustein `ALI_ADD_3_UNGATED` führt eine standardmäßige arithmetische Addition durch. Sobald an den Eingangs-Adaptern (`IN1`, `IN2`, `IN3`) neue Werte signalisiert werden, berechnet der Baustein die Summe nach folgender Formel:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Das Ergebnis sowie das zugehörige Aktualisierungsereignis werden anschließend über den Ausgangs-Adapter `OUT` an die nachfolgenden Bausteine weitergegeben.

## Technische Besonderheiten

-   **Generische Implementierung:** Der Baustein ist als generischer Typ (`GEN_ALI_ADD`) deklariert. Dies ermöglicht eine flexible Anpassung an verschiedene Datentypen, die vom `ALI`-Adapter unterstützt werden.
-   **Verwendung von Adaptern:** Durch die Kapselung von Daten und Events in unidirektionalen Adaptern (`ALI`) wird die Anzahl der notwendigen Verbindungslinien im Application-Editor von 4diac-ide drastisch reduziert, was zu einer besseren Übersichtlichkeit führt.

## Zustandsübersicht

Der Funktionsbaustein arbeitet rein zustandslos (stateless). Es gibt keine interne Zustandsmaschine (ECC). Die Berechnung erfolgt rein daten- bzw. ereignisgesteuert: Ein eintreffendes Ereignis an einem der Eingangs-Adapter triggert direkt die Addition und die Aktualisierung des Ausgangs-Adapters.

## Anwendungsszenarien

-   **Messwert-Summierung:** Zusammenfassung von drei analogen Einzelmesswerten (z. B. Leistungsaufnahme von drei Phasen, Durchflussmengen aus drei Rohren) zu einem Gesamtwert.
-   **Mittelwertvorbereitung:** Aufsummierung von drei Werten zur anschließenden Division durch 3 in einem nachfolgenden Baustein.
-   **Strukturierte Signalverarbeitung:** Einsatz in komplexen Projekten, bei denen analoge Signale standardisiert und übersichtlich über Adapter-Kanäle geführt werden sollen.

## Vergleich mit ähnlichen Bausteinen

-   **Standard-ADD (IEC 61131-3):** Ein Standard-ADD-Baustein verwendet klassische Daten- und Ereignis-Verbindungen. `ALI_ADD_3_UNGATED` hingegen kapselt diese Schnittstellen in Adaptern, was die visuelle Komplexität im Systementwurf verringert.
-   **Kaskadierte 2-fach-Addierer:** Um drei Werte mit herkömmlichen 2-fach-Addierern zu addieren, müssten zwei Bausteine in Reihe geschaltet werden. `ALI_ADD_3_UNGATED` spart hierbei einen Baustein sowie die dazwischenliegende Instanziierung und Verdrahtung ein.

- **[`ALI_ADD_3`](ALI_ADD_3.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

`ALI_ADD_3_UNGATED` ist ein kompakter und effizienter Hilfsbaustein für 4diac-ide. Durch die konsequente Nutzung von unidirektionalen Adaptern trägt er maßgeblich zur Erstellung von sauberem, modularisiertem und leicht lesbarem Steuerungscode bei der Verarbeitung von analogen Signalen bei.

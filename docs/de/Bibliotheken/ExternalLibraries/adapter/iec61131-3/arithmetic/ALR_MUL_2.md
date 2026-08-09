# ALR_MUL_2


![ALR_MUL_2](./ALR_MUL_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ALR_MUL_2` ist ein generischer, arithmetischer Baustein, der für die Multiplikation zweier Werte konzipiert ist. Er basiert auf der IEC 61499-Architektur und nutzt Adapter-Schnittstellen zur Kapselung und Übertragung von Daten und Ereignissen. Dadurch ermöglicht er eine saubere Strukturierung und verringert den Verdrahtungsaufwand in 4diac-IDE-Anwendungen, da Daten und zugehörige Kontrollflüsse in gemeinsamen Verbindungen (Adaptern) gebündelt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung des Kontrollflusses erfolgt implizit über die verwendeten Adapter.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt implizit über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge. Die Eingangsdaten werden über die Adapter-Schnittstellen bereitgestellt.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge. Das Berechnungsergebnis wird über den Ausgangs-Adapter bereitgestellt.*

### **Adapter**

Der Baustein kommuniziert ausschließlich über Adapter-Verbindungen des Typs `ALR` (unidirektional):

*   **IN1 (Socket / Buchse)**:
    *   **Typ**: `adapter::types::unidirectional::ALR`
    *   **Beschreibung**: Erster Eingang (Multiplikand 1) für die Multiplikation.
*   **IN2 (Socket / Buchse)**:
    *   **Typ**: `adapter::types::unidirectional::ALR`
    *   **Beschreibung**: Zweiter Eingang (Multiplikand 2) für die Multiplikation.
*   **OUT (Plug / Stecker)**:
    *   **Typ**: `adapter::types::unidirectional::ALR`
    *   **Beschreibung**: Ausgang für das berechnete Multiplikationsergebnis.

---

## Funktionsweise

Der Baustein `ALR_MUL_2` führt eine mathematische Multiplikation nach folgendem Prinzip aus:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

Sobald an den Eingangs-Adaptern `IN1` und/oder `IN2` ein neues Ereignis signalisiert wird, das auf die Aktualisierung der Daten hinweist, nimmt der Baustein die entsprechenden Werte entgegen, multipliziert sie und gibt das Ergebnis sowie ein entsprechendes Aktualisierungsereignis über den Ausgangs-Adapter `OUT` weiter. 

Da es sich um einen generischen Baustein (`GEN_ALR_MUL`) handelt, passt sich die zugrundeliegende Berechnung an den im Adapter definierten Datentyp an.

---

## Technische Besonderheiten

*   **Generische Implementierung**: Der Baustein ist als `GEN_ALR_MUL` klassifiziert. Dies erlaubt eine flexible Nutzung mit verschiedenen numerischen Datentypen, die durch das Adapterprofil `ALR` definiert sind.
*   **Kapselung durch Adapter**: Durch die Verwendung von unidirektionalen Adaptern wird der Kontrollfluss (Events) direkt mit dem Datenfluss (Values) verknüpft. Dies verhindert Synchronisationsfehler zwischen Daten und Ereignissen.
*   **Compiler-Paket**: Der Baustein ist im Paket `adapter::iec61131::arithmetic` deklariert und nutzt die Kernbibliothek `eclipse4diac::core::GenericClassName`.

---

## Zustandsübersicht

Der Baustein verhält sich wie ein klassischer, zustandsloser (bzw. rein funktionaler) Baustein. Es gibt keine internen Zustände, die über einen Berechnungszyklus hinaus gespeichert werden:

1.  **Wartezustand**: Baustein wartet auf ein Ereignis an `IN1` oder `IN2`.
2.  **Berechnung**: Bei Eintreffen eines Ereignisses werden die Werte aus den Adaptern gelesen und multipliziert.
3.  **Ausgabe**: Das Ergebnis wird an `OUT` angelegt und das Ausgangsereignis getriggert. Der Baustein kehrt sofort in den Wartezustand zurück.

---

## Anwendungsszenarien

*   **Signalverarbeitung in verteilten Systemen**: Wenn Sensorwerte bereits als Adapterstrukturen vorliegen und skaliert oder miteinander verrechnet werden müssen (z. B. Berechnung von Leistung aus Strom und Spannung).
*   **Modularer Steuerungsentwurf**: Reduzierung von Linienkreuzungen im Funktionsplan von 4diac-Anwendungen durch den Einsatz von Adaptern anstelle von getrennten Event- und Datenleitungen.
*   **Kaskadierte Berechnungen**: Einfache Verkettung mehrerer mathematischer Operationen ohne zusätzlichen Overhead für die Event-Verdrahtung.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard `MUL` Baustein (IEC 61131-3)**: Der klassische `MUL`-Baustein nutzt separate Event-Eingänge (z.B. `REQ`) und Daten-Eingänge (z.B. `IN1`, `IN2` als REAL/INT). `ALR_MUL_2` vereinfacht dies, indem er diese Kanäle in Adaptern bündelt.
*   **ALR_ADD_2 / ALR_SUB_2**: Diese Bausteine arbeiten nach demselben Adapter-Prinzip, führen jedoch Additionen oder Subtraktionen anstelle einer Multiplikation aus.

---

## Fazit

`ALR_MUL_2` ist ein spezialisierter, hocheffizienter Funktionsbaustein für moderne IEC 61499-Architekturen. Durch die konsequente Nutzung von Adaptern fördert er ein sauberes, objektorientiertes Softwaredesign in der industriellen Automatisierung und eignet sich hervorragend für komplexe, verteilte Steuerungsaufgaben.
# AULI_ADD_3


![AULI_ADD_3](./AULI_ADD_3.svg)

*(Bild des Funktionsbausteins temporär nicht verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_ADD_3` ist ein generischer Arithmetik-Baustein für IEC 61499-Systeme, der speziell für die Addition von drei Eingangswerten entwickelt wurde. Im Gegensatz zu klassischen mathematischen Funktionsbausteinen nutzt dieser Baustein Adapterverbindungen des Typs `AULI` (unidirektional), um Daten und zugehörige Kontrollsignale gebündelt zu übertragen. Dies reduziert den Verdrahtungsaufwand innerhalb der Entwicklungsumgebung (4diac IDE) erheblich.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge definiert.* Die ereignisbasierte Steuerung wird implizit über die angeschlossenen Adapter (`Sockets`) abgewickelt.

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge definiert.* Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter (`Plug`).

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.* Der Datentransfer erfolgt über die Adapter-Schnittstellen.

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.* Das Berechnungsergebnis wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

Die Sockets dienen als Empfänger für die zu addierenden Werte.
*   **IN1** (Typ: `adapter::types::unidirectional::AULI`): Erster Summand der arithmetischen Addition.
*   **IN2** (Typ: `adapter::types::unidirectional::AULI`): Zweiter Summand der arithmetischen Addition.
*   **IN3** (Typ: `adapter::types::unidirectional::AULI`): Dritter Summand der arithmetischen Addition.

#### **Plugs (Ausgangs-Adapter)**

Der Plug dient als Sender für das berechnete Ergebnis.
*   **OUT** (Typ: `adapter::types::unidirectional::AULI`): Ausgang für das Ergebnis der Addition ($IN1 + IN2 + IN3$).

---

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1`, `IN2`, `IN3`) neue Daten signalisiert werden, führt der Baustein die mathematische Addition aus. 

Die zugrunde liegende Berechnungsformel lautet:
$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Das berechnete Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben und steht nachfolgenden Bausteinen zur Verfügung. Da es sich um unidirektionale Adapter handelt, fließt der Datenstrom ausschließlich von den Sockets zum Plug.

---

## Technische Besonderheiten

*   **Generischer Baustein:** Der Baustein ist in der 4diac-IDE als generischer Typ deklariert (`GenericClassName = 'GEN_AULI_ADD'`). Dies ermöglicht eine flexible Verarbeitung verschiedener Datentypen (z. B. INT, REAL, LREAL), die durch die Definition des `AULI`-Adapters gestützt werden.
*   **Adapter-Kapselung:** Durch die Verwendung von Adaptern anstelle von Standard-Daten- und Eventkanälen wird das Systemdesign modularer und übersichtlicher. 
*   **Ressourceneffizienz:** Die Berechnung erfolgt direkt auf Basis der Adapterereignisse, was eine performante Ausführung gewährleistet.

---

## Zustandsübersicht

Der Funktionsbaustein arbeitet als zustandsloser (bzw. rein ereignisgesteuerter) arithmetischer Baustein:
1.  **Bereitschaft (Idle):** Baustein wartet auf Wertänderungen oder Trigger-Signale an den Eingangs-Adaptern `IN1`, `IN2` oder `IN3`.
2.  **Berechnung (Evaluation):** Nach dem Eintreffen eines Signals werden die Werte ausgelesen und summiert.
3.  **Aktualisierung (Output):** Die Summe wird an `OUT` übergeben und das zugehörige Event im Adapter getriggert. Der Baustein kehrt sofort in den Zustand *Bereitschaft* zurück.

---

## Anwendungsszenarien

*   **Messwert-Summierung:** Zusammenfassung von drei analogen Messwerten (z. B. drei Teilstromstärken zur Ermittlung des Gesamtstroms) in der Prozessautomatisierung.
*   **Sollwert-Generierung:** Addition von Basis-Sollwerten mit zwei verschiedenen Korrektur- oder Offset-Werten.
*   **Strukturierte Datenverarbeitung:** Einsatz in komplexen IEC 61499 Steuerungsanwendungen, bei denen ein konsistenter Einsatz von Adaptern zur Erhöhung der Übersichtlichkeit gefordert ist.

---

## Vergleich mit ähnlichen Bausteinen

*   **Standard-ADD (IEC 61131-3):** Der klassische `ADD`-Baustein benötigt explizite `REQ`- und `CNF`-Event-Leitungen sowie einzelne Datenleitungen. `AULI_ADD_3` ersetzt diese durch nur vier Adapter-Verbindungen, was das visuelle Programmierbild aufräumt.
*   **Kaskadierte Addierer (z. B. 2x `AULI_ADD_2`):** Um drei Werte mit klassischen Zwei-Wege-Addierern zu addieren, müssten zwei Bausteine in Reihe geschaltet werden. `AULI_ADD_3` spart hierbei einen kompletten Funktionsblock sowie die dazugehörige Zwischenverdrahtung ein.

---

## Fazit

Der `AULI_ADD_3` ist ein praktischer und moderner Funktionsbaustein für die strukturierte Programmierung in 4diac. Durch die konsequente Nutzung des unidirektionalen `AULI`-Adapters eignet er sich ideal für saubere, übersichtliche und wartbare Architekturen in verteilten Steuerungssystemen nach dem IEC 61499-Standard.
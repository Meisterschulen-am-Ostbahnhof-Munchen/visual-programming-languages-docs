# AULI_SUB_2


![AULI_SUB_2](./AULI_SUB_2.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AULI_SUB_2` ist ein generischer Funktionsbaustein (Generic FB), der für die Durchführung einer arithmetischen Subtraktion (`OUT = IN1 - IN2`) entwickelt wurde. Anstatt klassischer Daten- und Ereignispins nutzt dieser Baustein Adapter-Schnittstellen des Typs `unidirectional::AULI`. Dies ermöglicht eine strukturierte und modularisierte Signalübertragung in IEC 61499 Applikationen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AULI`):
    -   Beschreibung: Der erste Eingang (Minuend) für die Subtraktion.
-   **IN2** (Typ: `adapter::types::unidirectional::AULI`):
    -   Beschreibung: Der zweite Eingang (Subtrahend) für die Subtraktion.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AULI`):
    -   Beschreibung: Der Ausgang (Differenz) der arithmetischen Subtraktion.

---

## Funktionsweise

Sobald über die Eingangs-Adapter `IN1` und `IN2` Werte und die dazugehörigen Ereignisse eintreffen, führt der Baustein die mathematische Operation `OUT = IN1 - IN2` aus.
Da es sich um einen generischen Baustein (`GEN_AULI_SUB`) handelt, kann sich die konkrete Datentyp-Verarbeitung nach den im Adapter definierten Datentypen richten (z. B. Ganzzahlen oder Gleitkommazahlen). Das Ergebnis wird zusammen mit dem entsprechenden Trigger-Ereignis über den Ausgangs-Adapter `OUT` weitergeleitet.

---

## Technische Besonderheiten

-   **Generischer Baustein:** Durch das Attribut `GenericClassName` mit dem Wert `'GEN_AULI_SUB'` ist der Baustein flexibel für verschiedene Datentypen einsetzbar, sofern die verwendeten Adapter dies unterstützen.
-   **Unidirektionale Adapter:** Die Verwendung des Typs `AULI` sorgt für eine klare Trennung der Signalflussrichtungen (unidirektional) und reduziert den Verdrahtungsaufwand im 4diac-Editor drastisch.

---

## Zustandsübersicht

Der Baustein verhält sich rein kombinatorisch bzw. ereignisgesteuert:

1.  **Warten auf Input:** Der Baustein verbleibt im Ruhezustand, bis ein Ereignis an einem der Eingangs-Adapter (`IN1` oder `IN2`) signalisiert wird.
2.  **Berechnung:** Bei Signaländerung/Ereignis wird die Subtraktion durchgeführt.
3.  **Ausgabe:** Das Ergebnis wird unmittelbar an den Plug `OUT` übergeben und das Ausgangsereignis ausgelöst.

---

## Anwendungsszenarien

-   **Soll-Ist-Wert-Vergleich:** Berechnung von Regeldifferenzen in der Prozesstechnik (z. B. `Regeldifferenz = Sollwert - Istwert`).
-   **Offset-Kompensation:** Abzug von Nullpunktfehlern oder Offsets bei analogen Sensorwerten.
-   **Kaskadierte Berechnungen:** Mathematische Berechnungen in modularen Anlagensteuerungen, bei denen Messwerte strukturiert über Adapter transportiert werden.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Subtraktionsbaustein (z. B. `SUB` aus der IEC 61131-3 Standardbibliothek) bietet `AULI_SUB_2` folgende Vorteile:

-   **Reduzierte Komplexität:** Statt einzelner Leitungen für Event (REQ/CNF) und Daten (IN1, IN2, OUT) bündeln die `AULI`-Adapter alle relevanten Informationen in einer einzigen Verbindung.
-   **Modularität:** Das Design eignet sich hervorragend für serviceorientierte Architekturen in verteilten Systemen.

---

- **[`AULI_SUB_2_UNGATED`](AULI_SUB_2_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AULI_SUB_2` ist ein robuster und wiederverwendbarer Funktionsbaustein zur Subtraktion. Durch den konsequenten Einsatz von Adaptern fördert er ein sauberes, übersichtliches und wartungsfreundliches Applikationsdesign in der 4diac-IDE.

# AX_SEL_TIME


![AX_SEL_TIME](./AX_SEL_TIME.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_TIME` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für IEC 61499-basierte Systeme. Er dient als binärer Selektor für Daten des Typs `TIME`. Mit Hilfe eines unidirektionalen Adapters (`G`) kann dynamisch zwischen zwei verschiedenen Zeit-Eingangswerten (`IN0` und `IN1`) gewählt werden, um den ausgewählten Wert an den Ausgang (`OUT`) durchzuschalten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Setzt den Zeitwert am Eingang `IN0` (assoziiert mit der Datenvariable `IN0`).
*   **EI1**: Setzt den Zeitwert am Eingang `IN1` (assoziiert mit der Datenvariable `IN1`).

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Confirmation), das signalisiert, dass der ausgewählte Ausgangswert aktualisiert wurde (assoziiert mit der Datenvariable `OUT`).

### **Daten-Eingänge**

*   **IN0** (`TIME`): Erster auswählbarer Zeitwert.
*   **IN1** (`TIME`): Zweiter auswählbarer Zeitwert.

### **Daten-Ausgänge**

*   **OUT** (`TIME`): Der aktuell ausgewählte Zeitwert.

### **Adapter**

*   **G** (`adapter::types::unidirectional::AX`): Unidirektionaler Adapter, der als Selektor fungiert. Er liefert sowohl das Ereignis zur Umschaltung als auch den Selektionswert (Zustand).

## Funktionsweise

Der Baustein kapselt ein internes Netzwerk zur ereignisgesteuerten Auswahl von Zeitwerten. Die Auswahl wird über den Adapter `G` gesteuert:
*   Liefert der Adapter `G` das Auswahlsignal für den ersten Pfad (entspricht logisch `FALSE` / `0`), wird der Wert von `IN0` auf den Ausgang `OUT` geschaltet.
*   Liefert der Adapter `G` das Auswahlsignal für den zweiten Pfad (entspricht logisch `TRUE` / `1`), wird der Wert von `IN1` auf den Ausgang `OUT` geschaltet.

Intern werden die Eingänge über D-Flipflops gepuffert und mittels des Standard-Auswahlbausteins `F_SEL` verarbeitet. Ein nachgeschaltetes `E_D_FF_ANY` sorgt für die ereignisbasierte Weiterleitung bei Wertänderungen.

## Technische Besonderheiten

*   **Ereignisfilterung am Ausgang:** Ein Ausgangsereignis (`CNF`) wird maßgeblich durch das interne `E_D_FF_ANY_OUT` kontrolliert. Dies bedeutet, dass ein Ausgangsereignis im Regelfall nur dann generiert wird, wenn sich der Zustand des Selektors `G` oder der Wert des aktuell ausgewählten Eingangs tatsächlich ändert, was zu einer Änderung des Ausgangswerts `OUT` führt.
*   **Adapter-Kopplung:** Durch die Verwendung des `AX`-Adapters wird die Ansteuerungslogik des Selektors modularisiert und vereinfacht die Verdrahtung im übergeordneten System-Netzwerk erheblich.

## Zustandsübersicht

Da es sich um einen Composite-Funktionsbaustein handelt, besitzt der Baustein keine eigene ECC (Execution Control Chart). Das Verhalten wird vollständig durch das interne Netzwerk bestimmt:

1.  **Änderung von `IN0` / `IN1`**: Ein Ereignis auf `EI0` oder `EI1` aktualisiert den jeweiligen internen Speicher. Wenn der geänderte Eingang gerade aktiv selektiert ist, wird der neue Wert an `OUT` angelegt und löst ein `CNF`-Ereignis aus.
2.  **Umschaltung via `G`**: Ein Ereignis über den Adapter `G` triggert die Neuberechnung der Selektion. Ändert sich dadurch der Wert am Ausgang `OUT`, wird das Ereignis `CNF` ausgegeben.

## Anwendungsszenarien

*   **Rezeptur- und Prozesssteuerung:** Umschaltung zwischen verschiedenen Prozess- oder Verzögerungszeiten (z. B. unterschiedliche Spül- oder Heizzeiten) basierend auf Betriebsmodi.
*   **Tag-/Nachtumschaltung:** Auswahl zwischen zwei vordefinierten Zeitintervallen für Steuerungsaufgaben in der Gebäudeautomatisierung oder Agrartechnik.
*   **Wartungs- und Diagnosemodi:** Temporäre Verkürzung von Überwachungszeiten (Sollwert-Schnittstellen) während des Servicebetriebs.

## Vergleich mit ähnlichen Bausteinen

*   **Vergleich mit `F_SEL` (IEC 61131-3):** Der klassische `F_SEL`-Baustein arbeitet rein datenflussorientiert. `AX_SEL_TIME` erweitert diese Funktionalität um eine vollständige Ereignissteuerung (IEC 61499) und integriert einen Adapteranschluss für eine sauberere Softwarearchitektur.
*   **Vergleich mit generischen Selektoren:** Im Gegensatz zu generischen Auswahlbausteinen bietet `AX_SEL_TIME` durch die feste Typisierung auf den Datentyp `TIME` eine erhöhte Typsicherheit zur Entwicklungszeit.

## Fazit

`AX_SEL_TIME` ist ein robuster und wiederverwendbarer Baustein zur ereignisgesteuerten Auswahl von Zeitwerten. Die Kombination aus einfacher Binärselektion und moderner Adapter-Anbindung macht ihn zu einer idealen Komponente für flexible Steuerungsanwendungen in verteilten Systemen.
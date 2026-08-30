# AUS_AX_SEL_AUS


![AUS_AX_SEL_AUS](./AUS_AX_SEL_AUS.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AUS_AX_SEL_AUS** ist ein binärer Selektor (Multiplexer) für IEC 61499-Systeme. Er dient dazu, basierend auf dem Zustand eines Auswahlsignals (Selector `G`), zwischen zwei Eingangsadaptern (`IN0` und `IN1`) zu wählen und den ausgewählten Wert an den Ausgangsadapter (`OUT`) weiterzuleiten.

Der Baustein nutzt unidirektionale Adapterstrukturen, was eine saubere Kapselung von Daten- und Ereignisströmen ermöglicht und das visuelle Routing innerhalb der Entwicklungsumgebung vereinfacht.

## Schnittstellenstruktur

Da dieser Funktionsbaustein als Composite-Netzwerk realisiert ist und vollständig auf Adaptern basiert, besitzt er keine direkten, klassischen Ereignis- oder Datenkanäle auf seiner Hauptebene. Die gesamte Kommunikation ist in den Adaptern gebündelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen empfangen).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen gesendet).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **G** (Typ: `adapter::types::unidirectional::AX`):
    -   **Beschreibung:** Auswahlsignal (Selector).
    -   **Inhalt:** Enthält das Auswahlerleignis `E1` und das dazugehörige Datensignal `D1` (üblicherweise boolesch interpretiert), das bestimmt, welcher Eingang durchgeschaltet wird.
-   **IN0** (Typ: `adapter::types::unidirectional::AUS`):
    -   **Beschreibung:** Erster auswählbarer Eingang. Wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Zustand `FALSE` (bzw. `0`) aufweist.
    -   **Inhalt:** Ereignis `E1` und Datensignal `D1` (Daten-Typ: `USINT`).
-   **IN1** (Typ: `adapter::types::unidirectional::AUS`):
    -   **Beschreibung:** Zweiter auswählbarer Eingang. Wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Zustand `TRUE` (bzw. `1`) aufweist.
    -   **Inhalt:** Ereignis `E1` und Datensignal `D1` (Daten-Typ: `USINT`).

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AUS`):
    -   **Beschreibung:** Der ausgewählte Ausgang. Erhält die Daten und Ereignisse des jeweils durchgeschalteten Eingangs.
    -   **Inhalt:** Ereignis `E1` und Datensignal `D1` (Daten-Typ: `USINT`).

## Funktionsweise

Der Baustein kapsele ein internes Netzwerk, welches die Adapter-Signale extrahiert, verarbeitet und über standardisierte IEC 61131-3- und IEC 61499-Bausteine routet:

1.  **Datenerfassung:** Sobald an einem der Eingangs-Adapter (`G`, `IN0` oder `IN1`) ein Ereignis (`E1`) eintrifft, wird der entsprechende Datenwert (`D1`) mithilfe von Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert.
2.  **Wertübergabe:** Die Werte der Eingänge `IN0` und `IN1` werden über Kopiervorgänge (`F_MOVE` mit dem Datentyp `USINT`) an den zentralen Selektionsbaustein weitergegeben.
3.  **Selektion:** Der interne Baustein `F_SEL` (standardmäßiger IEC 61131-3 Selektor) entscheidet anhand des Zustands von `G.D1`:
    -   Ist `G.D1` = `0` (bzw. `FALSE`), wird der Wert von `IN0` auf den Ausgang gelegt.
    -   Ist `G.D1` = `1` (bzw. `TRUE`), wird der Wert von `IN1` auf den Ausgang gelegt.
4.  **Ausgabe:** Das Ergebnis wird über ein weiteres Flip-Flop (`E_D_FF_ANY_OUT`) an den Ausgangs-Adapter `OUT` übergeben und triggert dort das Ereignis `OUT.E1` zeitgleich mit der Bereitstellung der Daten auf `OUT.D1`.

## Technische Besonderheiten

-   **Ereignisgesteuert:** Der Ausgang wird bei jeder Änderung an den Eingängen oder des Selektors sofort aktualisiert und mit einem neuen Ereignis versehen.
-   **Datentyp-Spezifisch:** Intern ist die Verarbeitung der Datenkanäle auf den Typ `USINT` ausgelegt (festgelegt über die Attribute der internen `F_MOVE`-Instanzen).
-   **Adapter-Kapselung:** Erleichtert das saubere Design von Applikationsdiagrammen, da komplexe Daten- und Event-Paare als eine einzige Verbindung (Bus) dargestellt werden.

## Zustandsübersicht

Da es sich um einen Composite-Funktionsbaustein ohne eigene Execution Control Chart (ECC) handelt, wird das Verhalten rein durch den Signalfluss bestimmt:

| Zustand Selektor (`G.D1`) | Trigger-Ereignis | Aktivität am Ausgang (`OUT`) |
| :--- | :--- | :--- |
| `0` / `FALSE` | Beliebig (`G.E1`, `IN0.E1`, `IN1.E1`) | Gibt den Wert von `IN0.D1` aus; triggert `OUT.E1`. |
| `1` / `TRUE` | Beliebig (`G.E1`, `IN0.E1`, `IN1.E1`) | Gibt den Wert von `IN1.D1` aus; triggert `OUT.E1`. |

## Anwendungsszenarien

-   **Sollwert-Umschaltung:** Dynamisches Umschalten einer Zielgröße (z. B. einer Drehzahl oder Stufe vom Typ `USINT`) zwischen einem Automatikbetrieb (`IN1`) und einem Handbetrieb (`IN0`).
-   **Rezepturwahl:** Auswahl zwischen zwei fest vorgegebenen Betriebsmodi oder Parametersätzen in einer Maschine über eine übergeordnete Steuerung.
-   **Fehlersicherungen:** Schnelles Umschalten auf einen Ersatzwert (`IN0`), falls ein Hauptsignalweg gestört ist.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet `AUS_AX_SEL_AUS` den entscheidenden Vorteil, direkt mit den herstellerspezifischen oder standardisierten unidirektionalen Adaptern (`AUS` und `AX`) arbeiten zu können. Während bei `F_SEL` Ereignis- und Datenleitungen in IEC 61499 mühsam einzeln verdrahtet werden müssen, geschieht dies hier vollautomatisch im Inneren des Blocks.

## Fazit

Der Baustein **AUS_AX_SEL_AUS** stellt eine wichtige Brücke für moderne, adapterbasierte IEC 61499-Architekturen dar. Er vereint die bewährte Selektionslogik der IEC 61131-3 mit den Vorteilen der ereignisgesteuerten Adapterkopplung und trägt so signifikant zur Übersichtlichkeit und Wartbarkeit von Steuerungssoftware bei.

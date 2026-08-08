# AX_SEL_UINT


![AX_SEL_UINT](./AX_SEL_UINT.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AX_SEL_UINT` ist ein Standard-Auswahlbaustein (Binary Selection) für vorzeichenlose 16-Bit-Ganzzahlen (`UINT`). Er ermöglicht die Auswahl zwischen zwei Dateneingängen (`IN0` und `IN1`) und leitet den ausgewählten Wert an den Ausgang `OUT` weiter. Die Steuerung, welcher Eingang aktiv geschaltet wird, erfolgt über einen spezialisierten, unidirektionalen Adapter (`G`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Löst die Übernahme und Verarbeitung des Dateneingangs `IN0` aus.
*   **EI1**: Löst die Übernahme und Verarbeitung des Dateneingangs `IN1` aus.

### **Ereignis-Ausgänge**

*   **CNF**: Bestätigungsereignis (Confirmation). Signalisiert dem System, dass ein neuer Wert am Ausgang `OUT` zur Verfügung steht.

### **Daten-Eingänge**

*   **IN0** (UINT): Erster auswählbarer Eingangswert.
*   **IN1** (UINT): Zweiter auswählbarer Eingangswert.

### **Daten-Ausgänge**

*   **OUT** (UINT): Der aktuell ausgewählte und weitergeleitete Datenwert.

### **Adapter**

*   **G** (Typ: `adapter::types::unidirectional::AX`): Socket-Adapter, der als Selektor fungiert. Über diesen Adapter wird das Auswahlsignal (Ereignis und Datenwert) eingespeist.

* * * * * * * * * *

## Funktionsweise

Der Baustein `AX_SEL_UINT` basiert intern auf einem FB-Netzwerk, das die eingehenden Signale synchronisiert und filtert:

1.  **Datenerfassung**: Bei einem Ereignis an `EI0` oder `EI1` wird der jeweilige Wert (`IN0` bzw. `IN1`) über ein ereignisgesteuertes Flip-Flop (`E_D_FF_ANY`) gepuffert und an den eigentlichen Auswahl-FB (`F_SEL`) übergeben.
2.  **Auswahllogik (Selektor)**: Der Adapter `G` liefert das Steuersignal. Eine Änderung an diesem Adapter triggert das interne Flip-Flop `E_D_FF_G`. Der Zustand dieses Signals bestimmt den aktiven Pfad im standardisierten Auswahlbaustein `F_SEL` (IEC 61131-3 `SEL`):
    *   Ist der Zustand des Selektors **0 (FALSE)**, wird der Wert von `IN0` durchgeschaltet.
    *   Ist der Zustand des Selektors **1 (TRUE)**, wird der Wert von `IN1` durchgeschaltet.
3.  **Ausgabe-Filterung**: Der ausgewählte Wert wird an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben. Ein Ausgangsereignis an `CNF` wird nur dann erzeugt, wenn sich der Wert am Ausgang tatsächlich ändert oder ein entsprechendes Triggerereignis durch die Umschaltung des Selektors `G` erfolgt.

* * * * * * * * * *

## Technische Besonderheiten

*   **Ereignis-Filterung bei Wertänderung**: Durch die Verschaltung mit `E_D_FF_ANY` am Ausgang wird sichergestellt, dass nachfolgende Programmteile nicht unnötig mit identischen Werten getriggert werden. Ein `CNF`-Event wird vorrangig bei einer tatsächlichen Änderung des ausgewählten Ausgangswertes generiert.
*   **Adapter-Anbindung**: Die Auslagerung des Selektors in einen eigenständigen Adapter `G` (Typ `AX`) erlaubt eine saubere, modularisierte Kopplung im 4diac-Netzwerk und reduziert den Verdrahtungsaufwand auf der übergeordneten Anwendungsebene.

* * * * * * * * * *

## Zustandsübersicht

Da es sich um einen Composite-Funktionsblock handelt, wird das Verhalten direkt durch das interne Daten- und Ereignisfluss-Netzwerk bestimmt:

| Zustand Selektor (Adapter G) | Triggerndes Eingangsereignis | Aktiver Datenpfad | Ausgang (OUT) | Ausgangsereignis (CNF) |
| :--- | :--- | :--- | :--- | :--- |
| **FALSE (0)** | `EI0` oder Änderung an `G` | `IN0` wird durchgeschaltet | Wert von `IN0` | Aktiviert bei Wertänderung |
| **TRUE (1)** | `EI1` oder Änderung an `G` | `IN1` wird durchgeschaltet | Wert von `IN1` | Aktiviert bei Wertänderung |

* * * * * * * * * *

## Anwendungsszenarien

*   **Sollwertumschaltung**: Umschalten einer Anlage zwischen einem manuell vorgegebenen Sicherheits-Sollwert (`IN0`) und einem automatisch berechneten Prozess-Sollwert (`IN1`) über ein zentrales Steuersignal am Adapter `G`.
*   **Sensor-Redundanz**: Dynamisches Umschalten zwischen zwei redundanten `UINT`-Messwerten basierend auf einem übergeordneten Diagnose-Status, der über den Adapter übermittelt wird.
*   **Rezeptursteuerung**: Auswahl unterschiedlicher Konfigurations- oder Betriebsparameter während des laufenden Betriebs.

* * * * * * * * * *

## Vergleich mit ähnlichen Bausteinen

*   **Standard-`F_SEL`**: Der elementare IEC 61131-3 `F_SEL`-Baustein besitzt keinen Adapter-Anschluss und bietet keine integrierte Ereignis- und Wertfilterung. `AX_SEL_UINT` erweitert diese Funktionalität um flankengetriggerte Event-Flip-Flops für eine ressourcenschonende Ausführung.
*   **`MUX` (Multiplexer)**: Ein klassischer Multiplexer erlaubt die Auswahl aus mehr als zwei Kanälen, benötigt dafür jedoch eine Ganzzahl als Selektor und ist in der Regel nicht so stark auf ereignisdiskrete Steuerungsnetzwerke optimiert wie dieser selektive Baustein.

* * * * * * * * * *

## Fazit

Der `AX_SEL_UINT` ist ein hochoptimierter Hilfsbaustein für 4diac-Anwendungen, der die klassische binäre Auswahlfunktion mit modernen, ereignisgesteuerten Prinzipien verbindet. Durch den Einsatz des `AX`-Adapters wird die Übersichtlichkeit im Anwendungsdiagramm signifikant erhöht, während die interne Filterstruktur für ein stabiles und deterministisches Verhalten sorgt.
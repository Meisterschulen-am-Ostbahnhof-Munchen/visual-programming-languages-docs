# AULI_ADD_4


![AULI_ADD_4](./AULI_ADD_4.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AULI_ADD_4` ist ein generischer Funktionsbaustein (FB), der für die mathematische Addition von vier Werten konzipiert ist. Die Besonderheit dieses Bausteins liegt in der Verwendung von Adaptern des Typs `AULI` (unidirektional). Durch die Kapselung der Daten- und Ereignisübertragung in Adaptern ermöglicht der Baustein eine übersichtliche und modulare Verdrahtung innerhalb von IEC 61499-Anwendungen in der 4diac IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt implizit über die angeschlossenen Adapter-Sockets.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignissteuerung erfolgt implizit über den angeschlossenen Adapter-Plug.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AULI`): Erster Summand für die Additionsoperation.
-   **IN2** (Typ: `adapter::types::unidirectional::AULI`): Zweiter Summand für die Additionsoperation.
-   **IN3** (Typ: `adapter::types::unidirectional::AULI`): Dritter Summand für die Additionsoperation.
-   **IN4** (Typ: `adapter::types::unidirectional::AULI`): Vierter Summand für die Additionsoperation.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AULI`): Enthält das Ergebnis der Addition (`IN1 + IN2 + IN3 + IN4`) sowie das dazugehörige Ausgabe-Ereignis.

## Funktionsweise

Sobald an einem oder mehreren der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Wert-Ereignis signalisiert wird, liest der Funktionsbaustein die aktuellen Werte aus allen vier Adaptern aus. Diese Werte werden mathematisch addiert:

$$\text{Ergebnis} = \text{Wert}_{IN1} + \text{Wert}_{IN2} + \text{Wert}_{IN3} + \text{Wert}_{IN4}$$

Das berechnete Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben und gleichzeitig wird das zugehörige Ereignis am Ausgangs-Plug getriggert, um nachfolgende Bausteine über die Aktualisierung des Werts zu informieren.

## Technische Besonderheiten

-   **Generischer Baustein:** Der FB basiert auf der generischen Klasse `GEN_AULI_ADD`. Das bedeutet, dass er flexibel auf verschiedene Datentypen innerhalb der `AULI`-Adapterstruktur reagieren kann.
-   **Unidirektionale Adapter:** Es werden unidirektionale Adapter (`unidirectional::AULI`) verwendet. Dies vereinfacht den Datenfluss, da die Informationen und Ereignisse ausschließlich in eine Richtung (von den Eingängen zum Ausgang) fließen.
-   **Reduzierter Verdrahtungsaufwand:** Durch die Verwendung von Adaptern müssen Ereignis- und Datenleitungen nicht einzeln gezogen werden. Ein einziger Adapter-Kanal bündelt alle relevanten Signale.

## Zustandsübersicht

Der Funktionsbaustein verhält sich ereignisgesteuert und zustandslos (bzw. besitzt keinen internen Speicher für historische Werte):

1.  **Wartezustand:** Der FB wartet auf ein Ereignis an einem der Eingänge (`IN1` bis `IN4`).
2.  **Berechnung:** Bei Eintreffen eines Ereignisses werden die Daten aller vier Eingänge summiert.
3.  **Ausgabe:** Der berechnete Wert wird an `OUT` angelegt und das Ausgabeereignis ausgelöst. Der FB kehrt sofort in den Wartezustand zurück.

## Anwendungsszenarien

-   **Messwert-Summierung:** Zusammenfassung von vier einzelnen Sensorwerten (z. B. Energiemessungen von vier Verbrauchern, Durchflussmengen von vier Rohren) zu einem Gesamtwert.
-   **Mittelwertvorbereitung:** Vorsummierung von vier Datenpunkten vor einer anschließenden Division zur Mittelwertbildung.
-   **Modulare Steuerungsarchitekturen:** Einsatz in komplexen Systemen, in denen Signale bereits standardisiert als `AULI`-Adapter vorliegen.

## Vergleich mit ähnlichen Bausteinen

-   **Standard-ADD-Bausteine (z. B. `ADD` aus der IEC 61131-3):** Diese nutzen direkte Daten- und Ereignisports (wie `REQ`, `CNF`, `IN1`, `IN2`). `AULI_ADD_4` hingegen kapselt diese Schnittstellen vollständig in Adaptern, was zu einem aufgeräumteren Control-Flow-Diagramm führt.
-   **AULI_ADD_2:** Ein ähnlicher Baustein, der jedoch nur zwei Eingänge besitzt. `AULI_ADD_4` spart bei der Addition von vier Werten die Kaskadierung mehrerer einzelner Additions-Bausteine ein.

- **[`AULI_ADD_4_UNGATED`](AULI_ADD_4_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AULI_ADD_4`-Funktionsbaustein ist ein hocheffizienter, übersichtlicher und moderner Baustein für arithmetische Operationen in IEC 61499. Durch die konsequente Nutzung der `AULI`-Adapterstruktur sorgt er für eine signifikante Reduzierung von Verbindungslinien im Applikationseditor der 4diac IDE und eignet sich hervorragend für modulare Automatisierungslösungen.

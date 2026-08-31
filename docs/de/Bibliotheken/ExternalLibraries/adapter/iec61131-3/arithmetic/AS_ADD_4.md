# AS_ADD_4


![AS_ADD_4](./AS_ADD_4.svg)

*(Bild des Funktionsbausteins nicht vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AS_ADD_4` ist ein generischer Funktionsbaustein (FB), der für die Durchführung einer arithmetischen Addition von vier Eingangswerten entwickelt wurde. Die Besonderheit dieses Bausteins liegt in der Verwendung von unidirektionalen Adaptern (`AS`) für die Ein- und Ausgänge, was eine strukturierte und saubere Kapselung von Daten und zugehörigen Ereignissen in IEC 61499-Anwendungen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Es sind keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt implizit über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**

*Es sind keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt implizit über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AS`): Erster Eingangswert (Summand 1) für die Addition.
-   **IN2** (Typ: `adapter::types::unidirectional::AS`): Zweiter Eingangswert (Summand 2) für die Addition.
-   **IN3** (Typ: `adapter::types::unidirectional::AS`): Dritter Eingangswert (Summand 3) für die Addition.
-   **IN4** (Typ: `adapter::types::unidirectional::AS`): Vierter Eingangswert (Summand 4) für die Addition.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AS`): Ausgangsadapter zur Ausgabe des berechneten Additionsergebnisses.

---

## Funktionsweise

Der Baustein führt eine mathematische Addition der über die vier Eingangs-Adapter (`IN1` bis `IN4`) empfangenen Werte aus. Die mathematische Formel lautet:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Die Berechnung wird typischerweise getriggert, sobald an einem oder mehreren der Eingangs-Adapter ein entsprechendes Aktualisierungsereignis eintrifft. Nach erfolgreicher Berechnung wird das Ergebnis zusammen mit einem Trigger-Ereignis über den Ausgangs-Adapter `OUT` weitergeleitet.

---

## Technische Besonderheiten

-   **Generischer Charakter:** Der Baustein ist als generischer Baustein (`GEN_AS_ADD`) deklariert. Dies ermöglicht eine flexible Handhabung unterschiedlicher Datentypen (z. B. `INT`, `REAL`, `DINT`), je nachdem, wie die zugrundeliegenden Adaptertypen definiert sind.
-   **Adapter-Kopplung:** Durch die Nutzung von unidirektionalen Adaptern wird das Risiko von fehlerhafter Pin-Verdrahtung in der 4diac-IDE reduziert, da Daten und Ereignisse in einer einzigen Verbindunglinie gebündelt übertragen werden.

---

## Zustandsübersicht

Da es sich um einen algorithmischen Baustein zur Berechnung handelt, arbeitet der FB zustandslos bzw. ereignisgesteuert:

1.  **Warten:** Der Baustein wartet auf ein Aktualisierungsereignis an den Eingangs-Adaptern `IN1` bis `IN4`.
2.  **Berechnung:** Bei Eintreffen eines Ereignisses werden die aktuellen Werte der Eingänge addiert.
3.  **Ausgabe:** Der neue Summenwert wird auf den Adapter `OUT` geschrieben, und das zugehörige Ausgangsereignis wird ausgelöst.

---

## Anwendungsszenarien

-   **Messwert-Summierung:** Zusammenfassung von vier analogen Sensorwerten (z. B. Durchflussmengen oder Leistungen) zu einem Gesamtwert.
-   **Sollwert-Generierung:** Addition von Basis-Sollwerten mit verschiedenen Korrektur- oder Offset-Werten in einer Kaskadenregelung.
-   **Strukturierte Signalverarbeitung:** Einsatz in komplexen Steuerungsarchitekturen, bei denen eine strikte Trennung von Logik und Datenfluss durch Adapter-Strukturen gefordert ist.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen, standardmäßigen `ADD`-Baustein (nach IEC 61131-3):

-   **Vorteil:** Weniger Verdrahtungsaufwand in der grafischen Oberfläche, da keine separaten Event- und Datenlinien gezogen werden müssen.
-   **Nachteil:** Erfordert die Definition und Verwendung des spezifischen Adaptertyps `adapter::types::unidirectional::AS`. Ein direkter Anschluss von Standard-Datentypen (wie einfachen `REAL`- oder `INT`-Variablen) ohne Adapter ist nicht möglich.

---

- **[`AS_ADD_4_UNGATED`](AS_ADD_4_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AS_ADD_4` ist ein spezialisierter, hocheffizienter Funktionsbaustein für die moderne, adapterbasierte Programmierung in 4diac-IDE. Er eignet sich hervorragend für Anwendungen, die ein hohes Maß an Modularität und Übersichtlichkeit im Signalfluss erfordern und vier Summanden sauber und performant addieren müssen.

# AUS_MUL_4_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUS_MUL_4`](AUS_MUL_4.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![AUS_MUL_4_UNGATED](./AUS_MUL_4_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUS_MUL_4_UNGATED` ist ein generischer Baustein (Generic FB) zur Durchführung einer arithmetischen Multiplikation (`MUL`) mit bis zu vier Eingangswerten. Er basiert auf der IEC 61499-Architektur und nutzt unidirektionale Adapter, um Daten und die dazugehörigen Steuerungsereignisse sauber gekapselt zu übertragen.

Durch seinen generischen Charakter (`GEN_AUS_MUL`) ist der Baustein flexibel einsetzbar und kann auf verschiedene numerische Datentypen angewendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignissteuerung wird vollständig über den Ausgangs-Adapter abgewickelt.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenübergabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::AUS`): Erster Eingangswert (Multiplikand 1) für die Multiplikation.
-   **IN2** (Typ: `adapter::types::unidirectional::AUS`): Zweiter Eingangswert (Multiplikand 2) für die Multiplikation.
-   **IN3** (Typ: `adapter::types::unidirectional::AUS`): Dritter Eingangswert (Multiplikand 3) für die Multiplikation.
-   **IN4** (Typ: `adapter::types::unidirectional::AUS`): Vierter Eingangswert (Multiplikand 4) für die Multiplikation.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::AUS`): Das berechnete Produkt (Ergebnis der Multiplikation).

---

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1` bis `IN4`) neue Datenwerte und die entsprechenden Triggereignisse anliegen, führt der Baustein die Multiplikation durch.

Die mathematische Berechnung folgt der Formel:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3} \times \text{IN4}$$

Das berechnete Ergebnis wird zusammen mit einem entsprechenden Ausgabe-Ereignis über den Ausgangs-Adapter `OUT` bereitgestellt. Da es sich um einen generischen Funktionsbaustein handelt, passt sich der tatsächliche Datentyp (z. B. `INT`, `REAL`, `LREAL`) der Instanziierung in der 4diac-IDE an.

---

## Technische Besonderheiten

-   **Generischer Baustein:** Durch die Definition als `GEN_AUS_MUL` ist der Baustein nicht auf einen festen Datentyp fixiert, was die Wiederverwendbarkeit in verschiedenen Projekten drastisch erhöht.
-   **Adapterbasierte Kommunikation:** Die Verwendung von unidirektionalen `AUS`-Adaptern sorgt für ein übersichtliches Anwendungsdiagramm, da Daten- und Eventleitungen in einer einzigen Verbindung gebündelt werden. Dies reduziert Verdrahtungsfehler in der Entwicklungsumgebung.

---

## Zustandsübersicht

Der Funktionsbaustein verhält sich wie ein klassischer, zustandsloser mathematischer Operator (kombinatorische Logik). Er speichert keine internen Zustände zwischen den Berechnungszyklen. Jede Aktualisierung der Eingangswerte über die Adapter führt zu einer Neuberechnung und Aktualisierung des Ausgangs.

---

## Anwendungsszenarien

-   **Skalierung und Kalibrierung:** Berechnung von komplexeren physikalischen Werten, bei denen mehrere Faktoren (z. B. Sensorwert × Kalibrierungsfaktor × Temperaturkompensation × Einheitenumrechnung) multipliziert werden müssen.
-   **Leistungsberechnung:** Kombination von mehreren Messgrößen in der Prozesstechnik.
-   **Mehrstufige Verstärkungsregelungen:** Kaskadierung von Verstärkungsfaktoren in Steuerungsalgorithmen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu Standard-Multiplikationsbausteinen (wie dem klassischen `MUL` der IEC 61131-3), die mit einzelnen Pins für Events und Daten arbeiten, bietet der `AUS_MUL_4_UNGATED` folgende Vorteile:

-   **Weniger Verbindungen:** Vier separate Eingänge und ein Ausgang würden im klassischen Modell mindestens 10 Verbindungen (5 Events, 5 Datenleitungen) erfordern. Durch die Adapter-Technologie wird dies auf 5 Adapter-Verbindungen reduziert.
-   **Kompaktheit:** Das Kaskadieren von mehreren 2-fach Multiplizierern entfällt, da direkt vier Operanden in einem einzigen Baustein verarbeitet werden können.

---

- **[`AUS_MUL_4`](AUS_MUL_4.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AUS_MUL_4_UNGATED` ist ein hocheffizienter und moderner Funktionsbaustein für die 4diac-IDE. Er kombiniert die mathematische Grundfunktion der Multiplikation mit den modernen Strukturierungsvorteilen von IEC 61499-Adaptern, was zu saubereren, wartungsfreundlicheren und übersichtlicheren Steuerungsanwendungen führt.

# ADI_MUL_4_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ADI_MUL_4`](ADI_MUL_4.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![ADI_MUL_4_UNGATED](./ADI_MUL_4_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ADI_MUL_4_UNGATED` ist ein generischer, adapterbasierter Baustein für die IEC 61499, der zur Durchführung von arithmetischen Multiplikationen dient. Er berechnet das Produkt aus vier Eingangsgrößen, die über unidirektionale ADI-Adapter (`adapter::types::unidirectional::ADI`) bereitgestellt werden, und gibt das Ergebnis über einen entsprechenden Ausgangs-Adapter aus. Durch die Kapselung von Signalen in Adaptern sorgt dieser Baustein für ein übersichtlicheres Anwendungsdiagramm in der 4diac-IDE.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung ist in den verwendeten Adaptern gekapselt.*

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung ist in den verwendeten Adaptern gekapselt.*

### **Daten-Eingänge**

*Dieser Baustein besitzt keine direkten Daten-Eingänge. Die Datenübergabe erfolgt über die Sockets.*

### **Daten-Ausgänge**

*Dieser Baustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den Plug.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

-   **IN1** (Typ: `adapter::types::unidirectional::ADI`): Erster Faktor für die Multiplikation.
-   **IN2** (Typ: `adapter::types::unidirectional::ADI`): Zweiter Faktor für die Multiplikation.
-   **IN3** (Typ: `adapter::types::unidirectional::ADI`): Dritter Faktor für die Multiplikation.
-   **IN4** (Typ: `adapter::types::unidirectional::ADI`): Vierter Faktor für die Multiplikation.

#### **Plugs (Ausgangs-Adapter)**

-   **OUT** (Typ: `adapter::types::unidirectional::ADI`): Ergebnis der Multiplikation ($OUT = IN1 \times IN2 \times IN3 \times IN4$).

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1` bis `IN4`) neue Werte und die dazugehörigen Ereignisse eintreffen, führt der Baustein die Multiplikation der vier Werte aus:

$$\text{OUT} = \text{IN1} \cdot \text{IN2} \cdot \text{IN3} \cdot \text{IN4}$$

Das berechnete Ergebnis wird zusammen mit dem entsprechenden Trigger-Ereignis über den Ausgangs-Adapter `OUT` an die nachfolgenden Bausteine weitergeleitet. Da es sich um einen generischen Funktionsbaustein (`GEN_ADI_MUL`) handelt, passt sich das Berechnungsverhalten dem im Adapter definierten Datentyp an.

## Technische Besonderheiten

-   **Generischer Typ (`GEN_ADI_MUL`):** Der Baustein ist intern als generischer Baustein deklariert. Dies ermöglicht eine flexible Handhabung verschiedener Datentypen (z.B. `INT`, `REAL`, `LREAL`), je nach Spezifikation der verbundenen ADI-Adapter.
-   **Kapselung durch Adapter:** Da sowohl Daten als auch Ereignisse über unidirektionale Adapter (`ADI`) geführt werden, verringert sich die Anzahl der sichtbaren Verbindungslinien in der 4diac-IDE drastisch. Dies erhöht die Übersichtlichkeit komplexer Steuerungsanwendungen.

## Zustandsübersicht

Der Funktionsbaustein `ADI_MUL_4_UNGATED` ist ein **zustandsloser (stateless)** Rechenbaustein. Er besitzt keine interne State Machine (ECC). Jede Aktivierung durch ein Ereignis an den Eingangs-Adaptern führt direkt zur Neuberechnung des Ausgangs auf Basis der aktuell anliegenden Eingangswerte.

## Anwendungsszenarien

-   **Physikalische Berechnungen:** Berechnung von Volumina ($V = l \times b \times h$) mit einem zusätzlichen Skalierungs- oder Korrekturfaktor.
-   **Messwertskalierung:** Mehrstufige Gewichtung oder Skalierung von analogen Sensorwerten über mehrere Faktoren hinweg.
-   **Leistungsberechnungen:** Multiplikation von verschiedenen elektrischen oder mechanischen Kenngrößen zur Ermittlung von Gesamtleistungen oder Wirkungsgraden in der Prozessautomatisierung.

## Vergleich mit ähnlichen Bausteinen

-   **Standard `MUL`-Baustein (IEC 61131-3):** Klassische Multiplizierer nutzen direkte Daten- und Ereignispins. `ADI_MUL_4_UNGATED` hingegen nutzt Adapter, was das Routing vereinfacht, jedoch eine entsprechende Adapter-Infrastruktur im Projekt voraussetzt.
-   **ADI_MUL_2 / ADI_MUL_3:** Ähnliche Bausteine mit weniger Eingängen. `ADI_MUL_4_UNGATED` eignet sich speziell dann, wenn exakt vier Faktoren miteinander multipliziert werden müssen, ohne mehrere 2-fach-Multiplizierer kaskadieren zu müssen.

- **[`ADI_MUL_4`](ADI_MUL_4.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `ADI_MUL_4_UNGATED` ist ein hocheffizienter Hilfsbaustein für die mathematische Signalverarbeitung in IEC 61499-Systemen. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein sauberes, modulares Software-Design und reduziert die Komplexität der grafischen Verdrahtung innerhalb der 4diac-IDE.

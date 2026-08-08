# AUI_ADD_4

```text
        +-----------------------------------+
        |             AUI_ADD_4             |
        +-----------------------------------+
==#==>  | [Socket] IN1          [Plug] OUT  | ==#==>
==#==>  | [Socket] IN2                      |
==#==>  | [Socket] IN3                      |
==#==>  | [Socket] IN4                      |
        +-----------------------------------+
```


![AUI_ADD_4](./AUI_ADD_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_ADD_4` ist ein generischer Arithmetik-Baustein für die Entwicklungsumgebung 4diac-IDE. Er dient zur Addition von bis zu vier numerischen Eingangswerten, die über standardisierte, unidirektionale Adapter vom Typ `AUI` (Analog Universal Interface) bereitgestellt werden. Das berechnete Summengebnis wird über einen entsprechenden Ausgangs-Adapter ausgegeben. 

Durch die Verwendung von Adaptern wird die Anzahl der sichtbaren Verbindungen im Steuerungsdiagramm minimiert, was zu einer übersichtlicheren und modulareren Applikationsarchitektur führt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt implizit über die integrierten Ereigniskanäle der Eingangs-Adapter (`IN1` bis `IN4`).

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Aktualisierungsereignissen erfolgt implizit über den Ausgangs-Adapter (`OUT`).

### **Daten-Eingänge**
Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe ist vollständig in den Eingangs-Adaptern gekapselt.

### **Daten-Ausgänge**
Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe ist im Ausgangs-Adapter gekapselt.

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**
* **IN1** (Typ: `adapter::types::unidirectional::AUI`): 
  Erster Summand der Additionsoperation.
* **IN2** (Typ: `adapter::types::unidirectional::AUI`): 
  Zweiter Summand der Additionsoperation.
* **IN3** (Typ: `adapter::types::unidirectional::AUI`): 
  Dritter Summand der Additionsoperation.
* **IN4** (Typ: `adapter::types::unidirectional::AUI`): 
  Vierter Summand der Additionsoperation.

#### **Plugs (Ausgangs-Schnittstellen)**
* **OUT** (Typ: `adapter::types::unidirectional::AUI`): 
  Ausgangs-Adapter, der das mathematische Ergebnis der Addition bereitstellt.

## Funktionsweise

Der Funktionsbaustein arbeitet nach den Prinzipien der IEC 61499 für daten- und ereignisgesteuerte Ausführung:

1. **Triggerung:** Sobald an einem der Eingangs-Adapter (`IN1` bis `IN4`) ein neues Datenereignis signalisiert wird, wird der interne Berechnungsalgorithmus aufgerufen.
2. **Berechnung:** Der Baustein liest die numerischen Werte aus allen vier angeschlossenen Adaptern aus und addiert diese nach folgender mathematischer Formel:
   $$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$
3. **Ausgabe:** Der berechnete Summenwert wird in den Ausgangs-Adapter `OUT` geschrieben, und es wird ein Aktualisierungsereignis über diesen Adapter getriggert, um nachfolgende Bausteine über den neuen Wert zu informieren.

## Technische Besonderheiten

* **Generischer Typ (`GEN_AUI_ADD`):** Dank der generischen Definition ist der Baustein flexibel einsetzbar. Die genaue Datentyp-Auflösung (z. B. `INT`, `REAL`, `LREAL`) erfolgt dynamisch zur Laufzeit oder während der Instanziierung in der 4diac-IDE, passend zur Konfiguration des `AUI`-Adapters.
* **Kapselung durch Adapter:** Durch die Verwendung von Adaptern anstelle von einzelnen Event-/Data-Pins wird die visuelle Komplexität im Funktionsplan drastisch reduziert ("Clean Design").
* **Unidirektionaler Datenfluss:** Die Nutzung von unidirektionalen Adaptern stellt sicher, dass Daten und Ereignisse streng gerichtet von den Eingängen zum Ausgang fließen, was unbeabsichtigte Rückkopplungsschleifen verhindert.

## Zustandsübersicht

Der Baustein besitzt eine einfache, ereignisgesteuerte Ausführungslogik (Execution Control Chart - ECC):

```text
  +--------------+          Trigger (Event an IN1..IN4)          +-------------------+
  |              | --------------------------------------------> |                   |
  |    IDLE      |                                               |   BERECHNUNG &    |
  |  (Wartend)   | <-------------------------------------------- |   AKTUALISIERUNG  |
  +--------------+             Berechnung abgeschlossen          +-------------------+
```

1. **IDLE (Standardzustand):** Der Baustein wartet passiv auf eingehende Datenänderungen an den Sockets.
2. **BERECHNUNG:** Ein Event an einem der Eingänge stößt die Summation an. Das Ergebnis wird berechnet, an `OUT` übergeben und ein Ausgangs-Event erzeugt. Anschließend kehrt der Baustein sofort in den Zustand `IDLE` zurück.

## Anwendungsszenarien

* **Sensordaten-Fusion:** Aufsummierung von bis zu vier analogen Messwerten (z. B. Erfassung des Gesamtvolumenstroms aus vier einzelnen Teilströmen).
* **Leistungsberechnung:** Addition der Wirkleistungen von vier separaten Verbrauchern zur Ermittlung der Gesamtleistung in einem Energiemonitorsystem.
* **Sollwert-Generierung:** Zusammenführung eines Basis-Sollwerts mit bis zu drei Korrektur- oder Offsetwerten in Regelungssystemen.

## Vergleich mit ähnlichen Bausteinen

* **Vergleich mit Standard-`ADD` (IEC 61131-3):** Klassische `ADD`-Bausteine arbeiten mit expliziten Daten- und Event-Pins. `AUI_ADD_4` bündelt diese Signale in Adaptern, was die Verkabelung vereinfacht und standardisiert.
* **Vergleich mit `AUI_ADD_2`:** Für die Addition von drei oder vier Werten müssten bei einem 2-fach-Addierer mehrere Bausteine kaskadiert werden. `AUI_ADD_4` spart hierdurch Systemressourcen, verringert die Latenzzeit und sorgt für ein saubereres Applikationslayout.

## Fazit

Der `AUI_ADD_4` ist ein praktischer Hilfsbaustein für fortgeschrittene Steuerungsprojekte in der 4diac-IDE. Er kombiniert die mathematische Grundfunktion der Addition mit den strukturellen Vorteilen moderner Adapter-Verbindungen und eignet sich ideal für saubere, übersichtliche Signalverarbeitungsketten.
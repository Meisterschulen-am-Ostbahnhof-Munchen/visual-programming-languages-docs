# AUI_DIV_2

```
      +-----------------------------------+
      |             AUI_DIV_2             |
      +-----------------------------------+
=====>| [AUI] IN1                 OUT [AUI]|=====>
=====>| [AUI] IN2                         |
      +-----------------------------------+
```


![AUI_DIV_2](./AUI_DIV_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_DIV_2` ist ein generischer Funktionsbaustein zur Durchführung einer arithmetischen Division zweier Eingangswerte. Der Baustein nutzt ein adapterbasiertes Konzept, bei dem die Daten- und Ereignisströme in unidirektionalen Adaptern gebündelt werden. Dies ermöglicht eine saubere, modularisierte und übersichtliche Modellierung innerhalb von IEC 61499 Anwendungen in 4diac.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Es sind keine direkten Ereignis-Eingänge definiert. Die Ereignissteuerung erfolgt implizit über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**
*Es sind keine direkten Ereignis-Ausgänge definiert. Die Ereignissteuerung erfolgt implizit über die Adapter-Schnittstellen.*

### **Daten-Eingänge**
*Es sind keine direkten Daten-Eingänge definiert. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**
*Es sind keine direkten Daten-Ausgänge definiert. Die Datenübergabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**
* **IN1** (Typ: `adapter::types::unidirectional::AUI`): 
  Der erste Eingang-Adapter. Er liefert den Dividenden (Zähler) für die Divisionsoperation sowie die zugehörigen Triggereignisse.
* **IN2** (Typ: `adapter::types::unidirectional::AUI`): 
  Der zweite Eingang-Adapter. Er liefert den Divisor (Nenner) für die Divisionsoperation sowie die zugehörigen Triggereignisse.

#### **Plugs (Ausgangs-Schnittstellen)**
* **OUT** (Typ: `adapter::types::unidirectional::AUI`): 
  Der Ausgangs-Adapter. Er gibt das Ergebnis der Division (Quotient) und das entsprechende Berechnungsereignis aus.

## Funktionsweise

Der Baustein führt die mathematische Operation `OUT = IN1 / IN2` aus. 

Sobald an den Eingangs-Adaptern (`IN1` oder `IN2`) ein entsprechendes Trigger-Ereignis registriert wird, liest der Baustein die aktuellen Werte aus den Adaptern aus, berechnet den Quotienten und gibt diesen zusammen mit einem Ausgangsereignis über den Adapter `OUT` weiter. 

Da es sich um einen generischen Funktionsbaustein (`GEN_AUI_DIV`) handelt, kann sich der Baustein je nach Implementierung und Systemkonfiguration an unterschiedliche numerische Datentypen (z. B. INT, REAL, LREAL) anpassen, sofern die zugrundeliegenden Adapter denselben Datentyp unterstützen.

## Technische Besonderheiten

* **Generischer Typ:** Durch das Attribut `GenericClassName` mit dem Wert `'GEN_AUI_DIV'` ist der Baustein flexibel einsetzbar und nicht auf einen festen Datentyp fixiert.
* **Schnittstellen-Kapselung:** Die Verwendung von unidirektionalen Adaptern (`AUI`) reduziert den Verdrahtungsaufwand in der 4diac-IDE erheblich, da Event- und Datenleitungen in einer einzigen Verbindung gebündelt werden.
* **Division durch Null:** Bei der Verwendung dieses Bausteins muss anwendungstechnisch sichergestellt werden, dass der Wert von `IN2` ungleich Null ist, um Laufzeitfehler oder unendliche Werte (NaN/Inf) im Steuerungssystem zu vermeiden.

## Zustandsübersicht

1. **Wartestatus (IDLE):** Der Baustein wartet auf eingehende Ereignisse über die Adapter `IN1` oder `IN2`.
2. **Berechnung (EVALUATE):** Nach dem Empfang eines Ereignisses werden die Daten der Adapter ausgelesen und die Division durchgeführt.
3. **Ausgabe (DISPATCH):** Das Ergebnis und das verknüpfte Ereignis werden über den Adapter `OUT` bereitgestellt.

## Anwendungsszenarien

* **Skalierung von Sensorwerten:** Division von Rohwerten durch Skalierungsfaktoren in modular aufgebauten Steuerungsarchitekturen.
* **Berechnung von Mittelwerten:** Einsatz in mathematischen Berechnungsnetzwerken, bei denen Datenströme strukturiert über Adapter übertragen werden.
* **Signalverarbeitung:** Reduzierung von Signalstärken oder Frequenzteilungen in verteilten Systemen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen Standard-DIV-Baustein (z. B. aus der Standardbibliothek der IEC 61131-3), welcher mit einzelnen Pins für `REQ`, `CNF`, `IN1`, `IN2` und `OUT` arbeitet, bietet der `AUI_DIV_2` eine signifikant sauberere visuelle Darstellung im Funktionsplan. Durch die Kapselung in Adaptern wird die Fehleranfälligkeit bei der manuellen Verdrahtung von Event-zu-Daten-Zuordnungen minimiert.

## Fazit

Der `AUI_DIV_2` ist ein moderner, modularer und wiederverwendbarer Funktionsbaustein zur Division. Durch die konsequente Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für komplexe, verteilte Steuerungsanwendungen in 4diac, bei denen Übersichtlichkeit und einfache Wartbarkeit des Codes im Vordergrund stehen.
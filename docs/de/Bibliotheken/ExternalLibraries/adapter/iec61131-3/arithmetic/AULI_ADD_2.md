# AULI_ADD_2

```text
       +-------------------------------+
       |          AULI_ADD_2           |
       |                               |
 IN1 ==| (Socket)               (Plug) |== OUT
       |                               |
 IN2 ==| (Socket)                      |
       +-------------------------------+
```


![AULI_ADD_2](./AULI_ADD_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AULI_ADD_2` ist ein generischer Arithmetikbaustein für die IEC 61499-Umgebung (4diac-ide). Er dient zur Durchführung einer mathematischen Addition zweier Eingangswerte, die über standardisierte, unidirektionale Adapter übertragen werden. Das berechnete Ergebnis wird an einen entsprechenden Ausgangs-Adapter übergeben.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen, diskreten Ereignis- oder Dateneingänge auf der obersten Ebene. Die gesamte Kommunikation und Werteübertragungen werden über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.* (Die Ereignissteuerung ist in den Adaptern gekapselt).

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignissteuerung ist in den Adaptern gekapselt).

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

* **IN1** (Typ: `adapter::types::unidirectional::AULI`):
  Der erste Summand für die Additionsoperation.
* **IN2** (Typ: `adapter::types::unidirectional::AULI`):
  Der zweite Summand für die Additionsoperation.

#### **Plugs (Ausgangs-Adapter)**

* **OUT** (Typ: `adapter::types::unidirectional::AULI`):
  Das Ergebnis der Addition ($OUT = IN1 + IN2$).

## Funktionsweise

Der Funktionsbaustein `AULI_ADD_2` führt eine klassische Addition aus. Sobald sich Werte an den Eingangs-Adaptern `IN1` oder `IN2` ändern bzw. ein entsprechendes Aktualisierungsereignis über die Adapter getriggert wird, berechnet der Baustein die Summe der übertragenen Werte:

$$\text{Ergebnis} = \text{Wert}(IN1) + \text{Wert}(IN2)$$

Dieses Ergebnis sowie das dazugehörige Aktualisierungsereignis werden anschließend über den Ausgangs-Plug `OUT` an nachfolgende Bausteine weitergeleitet.

## Technische Besonderheiten

* **Generischer Charakter:** Der Baustein ist über das Attribut `GenericClassName` als `GEN_AULI_ADD` deklariert. Dies ermöglicht eine flexible Typisierung je nach konkreter Implementierung der verwendeten `AULI`-Adapterdaten.
* **Adapter-Kapselung:** Durch die Verwendung von Adaptern des Typs `unidirectional::AULI` wird die Komplexität der Steuerungsschaltpläne reduziert, da Daten und zugehörige Trigger-Ereignisse in einer einzigen Verbindung gebündelt sind.

## Zustandsübersicht

Da es sich bei diesem Baustein um einen rein funktionalen/mathematischen Koppler handelt, besitzt er im Regelfall keine komplexe interne Zustandsmaschine (ECC). Seine Ausführung ist rein daten- bzw. ereignisgetrieben basierend auf den eingehenden Adapter-Signalen:

1. **Wartezustand (Idle):** Baustein wartet auf Signalaktualisierungen an `IN1` oder `IN2`.
2. **Berechnung (Evaluate):** Bei Event-Eingang an einem der Sockets werden die Datenwerte addiert.
3. **Ausgabe (Propagate):** Der addierte Wert wird über den Plug `OUT` ausgegeben und das zugehörige Event getriggert.

## Anwendungsszenarien

* **Messwert-Aggregation:** Addition von zwei analogen Prozesswerten (z. B. zwei parallele Durchflusssensoren zur Ermittlung des Gesamtdurchflusses).
* **Sollwert-Offset:** Beaufschlagung eines Hauptsollwerts (über `IN1`) mit einem Korrekturwert oder Offset (über `IN2`).
* **Signalbündelung:** Strukturierte mathematische Signalverarbeitung in komplexen Anlagensteuerungen unter Verwendung von standardisierten Adapter-Schnittstellen zur Reduzierung des Verdrahtungsaufwands.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Additionsbaustein (wie dem IEC 61131-3 konformen `ADD`-Baustein), welcher mit diskreten Pins für `REQ`, `CNF`, `IN1`, `IN2` und `OUT` arbeitet, entfällt beim `AULI_ADD_2` die explizite Verdrahtung von Kontrollflüssen (Events) und Datenleitungen. Dies erhöht die Übersichtlichkeit in der 4diac-Entwicklungsumgebung signifikant, da pro Signalquelle nur noch eine einzige Adapterlinie gezogen werden muss.

## Fazit

Der `AULI_ADD_2` ist ein hocheffizienter, modularer Hilfsbaustein für die analoge Signalverarbeitung. Durch die konsequente Nutzung von unidirektionalen Adaptern erleichtert er den Entwurf sauber strukturierter und wartungsfreundlicher Steuerungsanwendungen nach dem IEC 61499 Standard.
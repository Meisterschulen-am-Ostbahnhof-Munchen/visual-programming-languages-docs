# AUS_ADD_4

```
        +-----------------------------------------+
        |                AUS_ADD_4                |
  IN1 ==# (Socket)                          (Plug) #== OUT
  IN2 ==# (Socket)                                |
  IN3 ==# (Socket)                                |
  IN4 ==# (Socket)                                |
        +-----------------------------------------+
```


![AUS_ADD_4](./AUS_ADD_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUS_ADD_4` dient der arithmetischen Addition von vier Eingangswerten. Es handelt sich hierbei um einen generischen Funktionsbaustein (Generic FB), der speziell für die Verwendung mit unidirektionalen Adaptern entwickelt wurde. Durch die Kapselung der Signale in Adaptern ermöglicht der Baustein eine saubere und übersichtliche Strukturierung von Datenflüssen innerhalb von IEC 61499 Applikationen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten, klassischen Ereignis-Eingänge. Die Event-Steuerung wird implizit über die Adapter-Schnittstellen abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, klassischen Ereignis-Ausgänge. Die Event-Weiterleitung erfolgt über die Adapter-Schnittstellen.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübertragung erfolgt ausschließlich über die zugeordneten Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

* **IN1** (Typ: `adapter::types::unidirectional::AUS`): Erster Summand der Addition.
* **IN2** (Typ: `adapter::types::unidirectional::AUS`): Zweiter Summand der Addition.
* **IN3** (Typ: `adapter::types::unidirectional::AUS`): Dritter Summand der Addition.
* **IN4** (Typ: `adapter::types::unidirectional::AUS`): Vierter Summand der Addition.

#### **Plugs (Ausgangs-Adapter)**

* **OUT** (Typ: `adapter::types::unidirectional::AUS`): Schnittstelle zur Ausgabe des berechneten Additionsergebnisses.

## Funktionsweise

Der Baustein `AUS_ADD_4` empfängt über seine vier Eingangs-Adapter (`IN1` bis `IN4`) kontinuierlich oder ereignisgesteuert numerische Werte. Sobald an den Sockets Daten anliegen oder ein Update-Event eintrifft, führt der Baustein die arithmetische Addition der vier Werte aus:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

Das Ergebnis dieser Berechnung wird unmittelbar an den Ausgangs-Plug `OUT` übergeben und für nachfolgende Programmteile bereitgestellt. Da es sich um unidirektionale Verbindungen handelt, fließen die Daten strikt gerichtet von den Eingängen zum Ausgang.

## Technische Besonderheiten

* **Generischer Baustein:** Durch die Zuordnung zur generischen Klasse `GEN_AUS_ADD` ist der Baustein hochgradig wiederverwendbar und passt sich flexibel an die zugrundeliegenden Datentypen der Adapter an.
* **Reduzierte Routing-Komplexität:** Durch die Verwendung von Adaptern statt einzelner Event- und Datenleitungen wird die Anzahl der Verbindungslinien in der 4diac-IDE drastisch reduziert, was die Lesbarkeit von großen Applikationsdiagrammen signifikant erhöht.
* **Compiler-Zugehörigkeit:** Der Baustein ist im Package `adapter::iec61131::arithmetic` organisiert.

## Zustandsübersicht

Der Baustein verhält sich wie ein kombinatorisches Glied (bzw. ein zustandsloser Funktionsblock). Er speichert keine historischen Werte zwischen den Berechnungszyklen. Jede Aktualisierung an einem der Eingangs-Adapter stößt die Berechnung direkt an und aktualisiert den Ausgang.

## Anwendungsszenarien

* **Signal-Summierung:** Zusammenführung und Addition von vier analogen Sensorwerten (z. B. Ermittlung des Gesamtvolumenstroms aus vier einzelnen Durchflussmessern oder der Gesamtleistung von vier elektrischen Verbrauchern).
* **Mittelwertvorbereitung:** Aufsummierung von vier Messstellen als vorbereitender Schritt für eine anschließende Division zur Mittelwertberechnung.
* **Kombinatorische Steuerungslogik:** Aggregation von gewichteten Steuersignalen in komplexeren verteilten Systemen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Addierer (z. B. dem klassischen `ADD`-Baustein aus der IEC 61131-3-Bibliothek), der direkt mit elementaren Datentypen (wie `REAL` oder `INT`) arbeitet, setzt `AUS_ADD_4` vollständig auf Adapter-Kopplung. Dies spart Zeit bei der Instanziierung und Verdrahtung, setzt jedoch voraus, dass die Quell- und Zielsignale im Adaptertyp `AUS` gekapselt vorliegen.

## Fazit

Der `AUS_ADD_4` ist ein spezialisierter und effizienter Hilfsbaustein für die strukturierte Applikationsentwicklung in 4diac. Er eignet sich hervorragend für sauber strukturierte Steuerungsanwendungen, bei denen die Signalverarbeitung konsistent über Adapter-Pipelines abgebildet werden soll.
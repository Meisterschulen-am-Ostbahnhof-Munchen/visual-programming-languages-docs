# AUS_MUL_3


![AUS_MUL_3](./AUS_MUL_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein (FB) `AUS_MUL_3` dient der arithmetischen Multiplikation von drei Eingangswerten. Es handelt sich hierbei um einen generischen Funktionsbaustein (`Generic FB`), der auf der Verwendung von unidirektionalen Adaptern des Typs `AUS` basiert. Der Baustein berechnet das Produkt aus drei Eingangsgrößen und stellt das Ergebnis an einem Ausgangs-Adapter zur Verfügung.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig auf Adaptern basiert, verfügt er über keine direkten, klassischen Ereignis- oder Datenschnittstellen auf der Bausteinebene. Die gesamte Kommunikation und Synchronisation erfolgt über die deklarierten Adapter.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.* (Die Ereignissteuerung wird über die Adapter-Sockets abgewickelt).

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.* (Die Ereignissteuerung wird über den Adapter-Plug abgewickelt).

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

- **IN1** (Typ: `adapter::types::unidirectional::AUS`): Der erste Multiplikand für die arithmetische Operation.
- **IN2** (Typ: `adapter::types::unidirectional::AUS`): Der zweite Multiplikand für die arithmetische Operation.
- **IN3** (Typ: `adapter::types::unidirectional::AUS`): Der dritte Multiplikand für die arithmetische Operation.

#### **Plugs (Ausgangs-Adapter)**

- **OUT** (Typ: `adapter::types::unidirectional::AUS`): Das berechnete Ergebnis der Multiplikation ($OUT = IN1 \times IN2 \times IN3$).

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1`, `IN2`, `IN3`) neue Werte anliegen und ein entsprechendes Trigger-Ereignis über die Adapter übertragen wird, führt der Baustein die Multiplikation aus.

Die mathematische Formel lautet:
$$\text{Ergebnis} = \text{Wert von IN1} \times \text{Wert von IN2} \times \text{Wert von IN3}$$

Das berechnete Ergebnis wird zusammen mit einem entsprechenden Bestätigungsereignis über den Ausgangs-Plug `OUT` an die nachfolgenden Programmteile weitergeleitet.

## Technische Besonderheiten

- **Generischer Baustein:** Durch das Attribut `GenericClassName` mit dem Wert `'GEN_AUS_MUL'` ist der Baustein flexibel einsetzbar. Je nach konkreter Implementierung des Adaptertyps `AUS` kann sich der Baustein auf verschiedene Datentypen (z. B. `INT`, `REAL`, `LREAL`) anpassen.
- **Kapselung durch Adapter:** Die Verwendung von unidirektionalen Adaptern (`unidirectional::AUS`) reduziert das Routing von einzelnen Event- und Datenleitungen in der 4diac-IDE drastisch. Dies sorgt für ein saubereres und übersichtlicheres Applikationsdesign.

## Zustandsübersicht

Der Baustein verhält sich rein zustandslos (bzw. reagiert ereignisgesteuert auf die eingehenden Adapter-Signale):

1. **Wartezustand:** Der Baustein wartet auf ein Aktualisierungsereignis an den Sockets `IN1`, `IN2` oder `IN3`.
2. **Berechnung:** Bei Eintreffen eines Ereignisses werden die Datenwerte der drei Eingangs-Adapter gelesen und miteinander multipliziert.
3. **Ausgabe:** Das Ergebnis wird an den Plug `OUT` geschrieben und das dazugehörige Sende-Ereignis des Plugs ausgelöst.

## Anwendungsszenarien

- **Skalierung und Gewichtung:** Multiplikation eines Sensorwertes mit zwei aufeinanderfolgenden Skalierungsfaktoren (z. B. physikalische Umrechnung und Kalibrierungsfaktor).
- **Volumenberechnung:** Berechnung eines dreidimensionalen Rauminhalts oder Durchflusses, bei dem drei Parameter (z. B. Länge × Breite × Höhe oder drei verschiedene Raten) direkt miteinander multipliziert werden müssen.
- **Strukturierte Signalverarbeitung:** Einsatz in komplexeren Regelkreisen, die eine saubere Signalarchitektur mittels Adaptern verlangen.

## Vergleich mit ähnlichen Bausteinen

- **Standard-MUL-Baustein (IEC 61131-3):** Der klassische `MUL`-Baustein nutzt direkte Daten- und Ereignis-Pins. `AUS_MUL_3` hingegen bündelt diese Signale in Adaptern, was die Verdrahtung in großen Projekten vereinfacht.
- **AUS_MUL_2 (Zwei-Eingangs-Variante):** Während eine hypothetische Variante mit zwei Eingängen nur zwei Faktoren multiplizieren kann, spart `AUS_MUL_3` bei der Multiplikation von drei Werten einen zusätzlichen Kaskadierungs-Baustein ein.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUS_MUL_3` ist ein hocheffizienter, generischer Funktionsbaustein zur Multiplikation von drei Werten. Durch die konsequente Nutzung von unidirektionalen Adaptern eignet er sich hervorragend für moderne, adapterbasierte Softwarearchitekturen in der 4diac-Umgebung, da er die visuelle Komplexität von Steuerungsdiagrammen minimiert.

# AUI_SUB_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUI_SUB_2`](AUI_SUB_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.




![AUI_SUB_2_UNGATED](./AUI_SUB_2_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUI_SUB_2_UNGATED` dient zur Durchführung einer arithmetischen Subtraktion innerhalb einer IEC 61499-Anwendung. Es handelt sich hierbei um einen generischen Funktionsbaustein (Generic FB), der speziell für die Interaktion mit Adapter-Schnittstellen entwickelt wurde. Er ermöglicht es, Subtraktionsoperationen modular und strukturiert über standardisierte Adapterverbindungen abzubilden, anstatt diskrete Einzeldrähte für Daten und Ereignisse zu verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird intern über die angebundenen Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Ausgangs-Adapter bereitgestellt.*

### **Adapter**

#### **Sockets (Steckdosen / Eingänge)**

- **IN1** (Typ: `adapter::types::unidirectional::AUI`):
  Erster Eingangsadapter für die Subtraktion. Dieser repräsentiert den Minuenden (Wert, von dem subtrahiert wird).
- **IN2** (Typ: `adapter::types::unidirectional::AUI`):
  Zweiter Eingangsadapter für die Subtraktion. Dieser repräsentiert den Subtrahenden (Wert, der subtrahiert wird).

#### **Plugs (Stecker / Ausgänge)**

- **OUT** (Typ: `adapter::types::unidirectional::AUI`):
  Ausgangsadapter, der das Ergebnis der Subtraktion (die Differenz) zur weiteren Verwendung bereitstellt.

---

## Funktionsweise

Der Baustein führt die grundlegende mathematische Operation der Subtraktion auf den über die Adapter eingehenden Werten aus:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Sobald an den Eingangs-Adaptern `IN1` oder `IN2` eine Wertänderung signalisiert wird (getriggert durch die ereignisgesteuerte Natur des zugrundeliegenden `AUI`-Adapters), berechnet der Baustein die Differenz und gibt das Ergebnis sowie ein entsprechendes Aktualisierungsereignis über den Ausgangs-Adapter `OUT` aus.

---

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein basiert auf der generischen Klasse `GEN_AUI_SUB`. Dies erlaubt eine flexible Handhabung unterschiedlicher Datentypen, sofern diese vom zugrundeliegenden Adaptertyp `AUI` (Analog User Interface / Unidirectional) unterstützt werden.
- **Kapselung:** Durch die Verwendung von unidirektionalen Adaptern werden Signalflüsse und die dazugehörigen Trigger-Events sauber gebündelt. Dies vereinfacht das Applikationsdesign in der 4diac IDE signifikant und reduziert die Anzahl der sichtbaren Verbindungslinien.

---

## Zustandsübersicht

Der Baustein selbst verwaltet keinen komplexen internen Zustand (zustandslos im Sinne einer State Machine). Seine Ausführung verhält sich rein reaktiv:

1. **Warten:** Der Baustein wartet auf ein Aktualisierungsereignis an `IN1` oder `IN2`.
2. **Berechnung:** Nach dem Eintreffen eines Ereignisses werden die Datenwerte ausgelesen und die Subtraktion durchgeführt.
3. **Ausgabe:** Der neue Differenzwert wird an `OUT` angelegt und das Ausgangsereignis des Adapters getriggert.

---

## Anwendungsszenarien

- **Differenzdruck- / Differenztemperaturmessung:** Berechnung der Abweichung zwischen zwei analogen Sensoren, deren Werte bereits als strukturierte Adapter-Signale vorliegen.
- **Soll-Ist-Wert-Vergleich:** Subtraktion eines Istwerts von einem Sollwert zur Ermittlung der Regeldifferenz in Regelungskreisen.
- **Nullpunktkompensation (Offset-Berechnung):** Abzug eines statischen oder dynamischen Offset-Wertes (über `IN2`) von einem Rohsignal (über `IN1`).

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-Subtraktionsblock (wie dem klassischen `SUB`-Baustein aus der IEC 61131-3 Bibliothek) benötigt der `AUI_SUB_2_UNGATED` keine explizite Verdrahtung von separaten Event- und Data-Ports (z.B. `REQ` und `IN1`, `IN2`). Die gesamte Logik der Wertübertragung und -aktualisierung ist im `AUI`-Adapter gekapselt. Dies macht den `AUI_SUB_2_UNGATED` wartungsfreundlicher und robuster gegenüber Verdrahtungsfehlern in komplexen Systemarchitekturen.

---

- **[`AUI_SUB_2`](AUI_SUB_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AUI_SUB_2_UNGATED` ist ein hocheffizienter, übersichtlicher und moderner Funktionsbaustein zur Durchführung von Subtraktionen. Durch die konsequente Nutzung von Adaptern fügt er sich nahtlos in serviceorientierte und modularisierte Steuerungskonzepte ein und trägt zu einem sauberen Software-Design in der 4diac IDE bei.

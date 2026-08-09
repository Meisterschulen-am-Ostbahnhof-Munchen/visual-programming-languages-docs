# AIS_AX_SEL_AIS


![AIS_AX_SEL_AIS](./AIS_AX_SEL_AIS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AIS_AX_SEL_AIS** ist ein binärer Auswahlbaustein (Selection) für die IEC 61499 Architektur in 4diac-IDE. Er dient dazu, basierend auf dem Zustand eines Selektionssignals (Gate) dynamisch zwischen zwei unidirektionalen analogen Eingangssignalen auszuwählen und das gewählte Signal an den Ausgang weiterzuleiten. 

Der Baustein nutzt intern die klassische Auswahl-Logik des standardisierten `SEL`-Bausteins (bekannt aus der IEC 61131-3), ist jedoch vollständig für die ereignisgesteuerte Ausführung der IEC 61499 optimiert und kapselt die Daten- und Ereignisströme mithilfe von standardisierten Adaptern.

## Schnittstellenstruktur

Der Funktionsbaustein verwendet ein adapterbasiertes Schnittstellendesign. Er besitzt keine direkt herausgeführten ereignis- oder datenbasierten Ein- und Ausgänge auf der Hauptebene, sondern wickelt die gesamte Kommunikation über Plugs (Stecker) und Sockets (Buchsen) ab.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignisverarbeitung erfolgt gekapselt über die Adapter-Schnittstellen.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

* **G** (Typ: `adapter::types::unidirectional::AX`): 
  Der Selector-Eingang (Gate). Bestimmt, welcher der beiden Eingänge (`IN0` oder `IN1`) an den Ausgang durchgeschaltet wird.
* **IN0** (Typ: `adapter::types::unidirectional::AIS`): 
  Der erste auswählbare Eingangskanal. Dieser Kanal wird aktiv geschaltet, wenn der Selektor `G` den Zustand `FALSE` (0) aufweist.
* **IN1** (Typ: `adapter::types::unidirectional::AIS`): 
  Der zweite auswählbare Eingangskanal. Dieser Kanal wird aktiv geschaltet, wenn der Selektor `G` den Zustand `TRUE` (1) aufweist.

#### **Plugs (Ausgangs-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AIS`): 
  Der ausgewählte Ausgangskanal. Er liefert den Wert des jeweils aktiven Eingangskanals sowie das zugehörige Aktualisierungsereignis.

---

## Funktionsweise

Im Inneren des FBs arbeitet ein Netzwerk aus Standard-Funktionsbausteinen, welches die Adapter-Ereignisse synchronisiert und die logische Auswahl trifft:

1. **Ereignissynchronisation & Signalspeicherung:**
   Die an den Adaptern `IN0`, `IN1` und `G` ankommenden Daten werden bei jedem Eintreffen eines entsprechenden Adapter-Ereignisses (`E1`) in Daten-Flipflops (`E_D_FF_ANY` bzw. `E_D_FF`) zwischengespeichert. Dadurch wird sichergestellt, dass die Datenwerte für die Weiterverarbeitung stabil zur Verfügung stehen.
2. **Datenbereitstellung:**
   Die Bausteine `F_MOVE_IN0` und `F_MOVE_IN1` kopieren die zwischengespeicherten Daten (interpretiert als Datentyp `STRING`) und leiten sie an den eigentlichen Auswahlkern weiter.
3. **Auswahlprozess (F_SEL):**
   Der Kern-Baustein `F_SEL` (Typ `iec61131::selection::F_SEL`) wertet den Zustand des Selektors `G` aus:
   * Ist `G` = `FALSE`, wird der Wert von `IN0` gewählt.
   * Ist `G` = `TRUE`, wird der Wert von `IN1` gewählt.
4. **Ausgabeübertragung:**
   Das Auswahlergebnis wird über den Baustein `F_MOVE_OUT` an das Ausgangs-Flipflop `E_D_FF_ANY_OUT` übertragen. Dieses triggert das Ereignis `E1` am Ausgangs-Adapter `OUT` und legt den selektierten Datenwert an den Ausgang `D1` an.

---

## Technische Besonderheiten

* **Adapter-Kapselung:** Durch die Verwendung von unidirektionalen Adaptern (`AIS` und `AX`) wird das Applikationsdiagramm in der 4diac-IDE übersichtlich gehalten, da Daten- und Ereignisleitungen in einer einzigen Verbindung gebündelt sind.
* **Asynchrone Ereignisbehandlung:** Jede Änderung an einem der Eingänge (`IN0`, `IN1`) oder am Selektor (`G`) stößt den Auswahlprozess automatisch neu an und aktualisiert den Ausgang wert- und ereignisgetreu.
* **Datentyp-Spezifizierung:** Die internen Datenkopierer (`F_MOVE`) sind fest auf den Datentyp `STRING` parametriert, was darauf hindeutet, dass die zu schaltenden Signale im `AIS`-Adapter als Zeichenketten übertragen werden.

---

## Zustandsübersicht

| Zustand des Selektors (`G`) | Letztes Ereignis an... | Aktiver Ausgang (`OUT.D1`) | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`FALSE`** | `IN0.E1` oder `G.E1` | Wert von `IN0.D1` | Der Eingang 0 ist aktiv geschaltet. Änderungen an `IN1` haben keinen Einfluss auf den Ausgang. |
| **`TRUE`** | `IN1.E1` oder `G.E1` | Wert von `IN1.D1` | Der Eingang 1 ist aktiv geschaltet. Änderungen an `IN0` haben keinen Einfluss auf den Ausgang. |

---

## Anwendungsszenarien

* **Sensorredundanz / Failsafe-Systeme:** Umschalten zwischen einem Hauptsensor und einem Ersatzsensor bei Signalverlust oder Fehlfunktion.
* **Betriebsmodus-Auswahl:** Dynamische Weiterleitung unterschiedlicher Parametersätze (z.B. Automatik- vs. Handbetrieb-Sollwerte) an ein Stellglied.
* **Signalrouting in landwirtschaftlichen Maschinen (ISOBUS-Kontext):** Kanalsteuerung für analoge Prozesswerte oder Zustandsmeldungen in komplexen Steuerungsnetzwerken.

---

## Vergleich mit ähnlichen Bausteinen

* **Klassischer `SEL` (IEC 61131-3):** Der klassische `SEL`-Baustein besitzt keine Ereignissteuerung und ist rein datenflussorientiert. `AIS_AX_SEL_AIS` erweitert dieses Prinzip um eine ereignisbasierte Steuerung für verteilte Systeme.
* **Standard-Auswahlbausteine ohne Adapter:** Typische IEC 61499 Auswahlbausteine arbeiten oft mit vielen einzelnen Event- und Daten-Pins. Dieser Baustein bietet durch die Adapter-Schnittstellen eine deutlich höhere Wartbarkeit und Modularität im Systemdesign.

---

## Fazit

Der **AIS_AX_SEL_AIS** ist eine spezialisierte und performante Lösung für die Signalumschaltung in der 4diac-IDE. Durch die strikte Verwendung von Adaptern und die zuverlässige interne Ereignisverarbeitung eignet er sich ideal für saubere, modulare Softwarearchitekturen im Bereich der industriellen Automatisierung und Agrartechnik.
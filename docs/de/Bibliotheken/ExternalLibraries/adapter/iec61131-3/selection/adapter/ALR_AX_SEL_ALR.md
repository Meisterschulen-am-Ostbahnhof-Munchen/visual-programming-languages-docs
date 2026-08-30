# ALR_AX_SEL_ALR


![ALR_AX_SEL_ALR](./ALR_AX_SEL_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_AX_SEL_ALR` dient zur binären Auswahl (Selektion) zwischen zwei analogen Eingangssignalen, die über Adapter des Typs `ALR` bereitgestellt werden. Gesteuert wird diese Auswahl durch einen Selektor-Adapter des Typs `AX`. Das ausgewählte Signal wird an einen Ausgangs-Adapter des Typs `ALR` weitergegeben.

Der Baustein basiert intern auf der IEC 61131-3 Auswahlfunktion `F_SEL` und ist für ereignisgesteuerte IEC 61499-Architekturen optimiert.

## Schnittstellenstruktur

Da dieser Baustein als Adapter-Koppler aufgebaut ist, besitzt er keine klassischen, direkten Ereignis- oder Daten-Schnittstellen auf der obersten Ebene. Die gesamte Kommunikation wird über Sockets (Eingangs-Adapter) und Plugs (Ausgangs-Adapter) abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

- **Sockets (Eingangs-Schnittstellen):**
  - `IN0` (Typ: `adapter::types::unidirectional::ALR`): Erster auswählbarer Eingangskanal (wird auf den Ausgang geschaltet, wenn der Selektor `G` den Wert `FALSE` aufweist).
  - `IN1` (Typ: `adapter::types::unidirectional::ALR`): Zweiter auswählbarer Eingangskanal (wird auf den Ausgang geschaltet, wenn der Selektor `G` den Wert `TRUE` aufweist).
  - `G` (Typ: `adapter::types::unidirectional::AX`): Selektor-Eingang zur Steuerung der Kanalauswahl.
- **Plugs (Ausgangs-Schnittstellen):**
  - `OUT` (Typ: `adapter::types::unidirectional::ALR`): Ausgang, der das ausgewählte Signal führt.

## Funktionsweise

Der Baustein realisiert eine softwaregesteuerte 1-aus-2-Auswahl auf Basis von Adaptern:

1. **Ereignispufferung:** Eintreffende Ereignisse und Daten an den Sockets `IN0`, `IN1` und `G` werden über interne Ereignis-D-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert, um eine konsistente Datenübergabe zu gewährleisten.
2. **Wertübertragung:** Die Datenwerte werden über interne Zuweisungsglieder (`F_MOVE`) für den Datentyp `LREAL` aufbereitet.
3. **Auswahllogik (`F_SEL`):** Die Auswahl erfolgt über den Standard-Selektionsbaustein:
   - Ist das Signal an `G.D1` gleich `FALSE`, wird der Wert von `IN0.D1` an den Ausgang weitergegeben.
   - Ist das Signal an `G.D1` gleich `TRUE`, wird der Wert von `IN1.D1` an den Ausgang weitergegeben.
4. **Ausgabe-Triggerung:** Jede Änderung an einem der Eingänge oder am Selektor führt zu einer Aktualisierung des Ausgangs-Adapters `OUT`, signalisiert durch das Ereignis `OUT.E1` und den neuen Datenwert `OUT.D1`.

## Technische Besonderheiten

- **Präzise Datenverarbeitung (LREAL):** Die internen Datenpfade sind für den Datentyp `LREAL` ausgelegt, was eine verlustfreie Übertragung hochgenauer analoger Messwerte ermöglicht.
- **Kapselung durch Adapter:** Durch die Verwendung von standardisierten Adaptern (`ALR`, `AX`) entfällt die komplexe Einzelverdrahtung von Daten- und Ereignis-Pins im Applikationseditor.
- **Ereignisgesteuert:** Der Ausgang reagiert dynamisch und verzögerungsfrei auf Wertänderungen und Trigger an den Eingängen.

## Zustandsübersicht

Das Verhalten des Bausteins wird durch den Daten- und Ereignisfluss im internen Netzwerk bestimmt:

| Zustand Selektor `G.D1` | Durchgeschalteter Kanal | Ausgangswert `OUT.D1` | Ausgangsereignis `OUT.E1` |
| :--- | :--- | :--- | :--- |
| `FALSE` | Kanal 0 (`IN0`) | Wert von `IN0.D1` | Triggert bei Ereignissen auf `IN0.E1` oder Änderung von `G` |
| `TRUE` | Kanal 1 (`IN1`) | Wert von `IN1.D1` | Triggert bei Ereignissen auf `IN1.E1` oder Änderung von `G` |

## Anwendungsszenarien

- **Sensor-Redundanz / Failover:** Umschaltung zwischen einem Hauptsensor (`IN0`) und einem Backup-Sensor (`IN1`) bei Ausfall oder Signalstörung, gesteuert durch ein Diagnosesignal an `G`.
- **Sollwertumschaltung:** Wechsel zwischen einem Automatik-Sollwert und einem manuellen Vorgabewert in verfahrenstechnischen Regelkreisen.
- **Rezeptur- und Parametersatz-Auswahl:** Dynamische Zuweisung unterschiedlicher analoger Prozessparameter basierend auf dem aktuellen Anlagenzustand.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen IEC 61131-3 `SEL`-Baustein kapselt `ALR_AX_SEL_ALR` die Signalwege komplett in Adapterstrukturen. Dies reduziert die visuelle Komplexität in 4diac-Applikationsdiagrammen erheblich, da statt mehrerer einzelner Verbindungen nur noch strukturierte Adapterlinien gezogen werden müssen.

## Fazit

Der `ALR_AX_SEL_ALR` ist ein robuster und wiederverwendbarer Baustein für die strukturierte Signalumschaltung in der IEC 61499. Durch die konsequente Nutzung von Adaptern und die Unterstützung von hochauflösenden `LREAL`-Daten eignet er sich ideal für moderne Steuerungs- und Regelungskonzepte in der industriellen Automatisierung.

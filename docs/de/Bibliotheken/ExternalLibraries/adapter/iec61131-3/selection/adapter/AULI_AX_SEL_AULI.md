# AULI_AX_SEL_AULI


![AULI_AX_SEL_AULI](./AULI_AX_SEL_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AULI_AX_SEL_AULI` dient als binärer Selektor (Multiplexer) im 4diac-Framework. Er ermöglicht es, basierend auf einem Steuersignal eines Selektor-Adapters (`G`), zwischen zwei Eingangssignalen von Adapter-Eingängen (`IN0` und `IN1`) auszuwählen und das ausgewählte Signal an einen Ausgangs-Adapter (`OUT`) weiterzuleiten.

Die Besonderheit dieses Bausteins liegt in der konsequenten Verwendung von unidirektionalen Adaptern zur Kapselung von Ereignissen und Daten, was zu einer aufgeräumten und modularen Struktur im übergeordneten Anwendungsnetzwerk führt.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig auf Adaptern basiert, besitzt er keine direkten, klassischen Ereignis- oder Datenkanäle auf seiner äußeren Grenze. Die gesamte Kommunikation ist in den Adaptern gekapselt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt implizit über die Eingangsadapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt implizit über den Ausgangsadapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangsadapter)**

- **G** (Typ: `adapter::types::unidirectional::AX`):
  Der Selektor-Kanal. Das hier anliegende Signal steuert, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird.
- **IN0** (Typ: `adapter::types::unidirectional::AULI`):
  Der erste auswählbare Eingangskanal. Dieser Wert wird an den Ausgang weitergegeben, wenn der Selektor `G` den Zustand `FALSE` (0) aufweist.
- **IN1** (Typ: `adapter::types::unidirectional::AULI`):
  Der zweite auswählbare Eingangskanal. Dieser Wert wird an den Ausgang weitergegeben, wenn der Selektor `G` den Zustand `TRUE` (1) aufweist.

#### **Plugs (Ausgangsadapter)**

- **OUT** (Typ: `adapter::types::unidirectional::AULI`):
  Der ausgewählte Ausgangskanal, welcher das Signal des ausgewählten Eingangs (`IN0` oder `IN1`) führt.

## Funktionsweise

Intern basiert der Baustein auf einem Netzwerk aus Standard-Funktionsbausteinen der IEC 61131 und IEC 61499:

1. **Ereigniserfassung:** Sobald an einem der Eingänge (`IN0.E1`, `IN1.E1`) oder am Selektor (`G.E1`) ein Ereignis eintrifft, wird dieses über flankengetriggerte Ereignis-Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) abgefangen und der jeweils aktuelle Datenwert (`D1`) zwischengespeichert.
2. **Datenkonvertierung & Transport:** Die Datenwerte der Eingänge werden über Konvertierungsbausteine (`F_MOVE` mit dem Datentyp `ULINT`) an den zentralen Auswahlbaustein übergeben.
3. **Auswahllogik (Multiplexing):** Der Baustein `F_SEL` (Standard Selection) wertet den Zustand des Selektors aus:
   - Ist der Wert von `G` gleich `FALSE`, wird der Wert von `IN0` gewählt.
   - Ist der Wert von `G` gleich `TRUE`, wird der Wert von `IN1` gewählt.
4. **Ausgabe:** Nach erfolgreicher Selektion wird das Ergebnis über einen weiteren Konvertierungsblock (`F_MOVE_OUT`) an das Ausgangs-Flip-Flop (`E_D_FF_ANY_OUT`) gesendet. Dieses triggert das Ausgangsereignis `OUT.E1` und legt den ausgewählten Wert an `OUT.D1` an.

## Technische Besonderheiten

- **Datentyp-Spezifität:** Intern arbeitet die Selektion auf dem Datentyp `ULINT` (Unsigned Long Integer / 64-Bit). Dies macht den Baustein besonders geeignet für die Verarbeitung von hochauflösenden Zählerwerten, Zeitstempeln oder großen ID-Nummern.
- **Adapter-Kapselung:** Durch die Verwendung von Adaptern (`AULI` und `AX`) werden Signal- und Eventleitungen gebündelt. Dies verhindert "Spaghetti-Code" im Systementwurf.
- **Event-Driven:** Der Baustein arbeitet rein ereignisgesteuert. Es erfolgt keine zyklische Berechnung, was Ressourcen schont.

## Zustandsübersicht

Der Baustein besitzt keine eigene explizite Zustandskette (Execution Control Chart, ECC), da er als reines Netzwerk (FBNetwork) realisiert ist. Sein Verhalten ist rein daten- und ereignisflussgesteuert:

| Trigger-Ereignis | Zustand Selektor (`G.D1`) | Resultierendes Verhalten | Ausgangsereignis |
| :--- | :--- | :--- | :--- |
| Event an `G.E1`, `IN0.E1` oder `IN1.E1` | `FALSE` | Wert von `IN0.D1` wird nach `OUT.D1` kopiert | `OUT.E1` |
| Event an `G.E1`, `IN0.E1` oder `IN1.E1` | `TRUE` | Wert von `IN1.D1` wird nach `OUT.D1` kopiert | `OUT.E1` |

## Anwendungsszenarien

- **Sensor-Redundanz:** Umschalten zwischen einem Hauptsensor (`IN0`) und einem Backup-Sensor (`IN1`) basierend auf einem Statussignal (`G`).
- **Sollwert-Umschaltung:** Wechseln zwischen einem automatischen Sollwert (z.B. aus einer Rezeptursteuerung) und einem manuell vorgegebenen Benutzer-Sollwert.
- **Betriebsarten-Umschaltung:** Routing von unterschiedlichen Datenströmen je nach aktivem Anlagenstatus (z. B. Normalbetrieb vs. Wartungsmodus).

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum klassischen Standard-Auswahlbaustein `F_SEL` bietet `AULI_AX_SEL_AULI` folgende Vorteile:

- **Kein manuelles Verdrahten von Events:** Bei `F_SEL` müssen Daten- und Eventleitungen manuell synchronisiert werden. Hier geschieht dies automatisch im Inneren des Bausteins durch die Verwendung der Adapter.
- **Erhöhte Typsicherheit & Übersichtlichkeit:** Verbindungsfehler im übergeordneten Steuerungsdiagramm werden minimiert, da Adapter nur mit passenden Gegenstücken verbunden werden können.

## Fazit

Der `AULI_AX_SEL_AULI` ist ein robuster, wiederverwendbarer und ereignisgesteuerter Selektorbaustein für 64-Bit-Ganzzahlwerte. Er eignet sich hervorragend für moderne, komponentenbasierte Softwarearchitekturen in der IEC 61499, bei denen Übersichtlichkeit und standardisierte Schnittstellen im Vordergrund stehen.

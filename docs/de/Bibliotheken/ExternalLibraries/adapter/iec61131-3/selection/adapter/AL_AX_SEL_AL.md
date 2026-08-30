# AL_AX_SEL_AL


![AL_AX_SEL_AL](./AL_AX_SEL_AL.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AL_AX_SEL_AL` ist ein ereignisgesteuerter Selektor (Binäre Auswahl) für IEC 61499-Systeme in der 4diac-IDE. Er dient als Multiplexer, der basierend auf dem Zustand eines Auswahlsignals (Selector) Daten von einem von zwei Eingangs-Adaptern an einen Ausgangs-Adapter weiterleitet. Der Baustein nutzt konsequent die Vorteile von Adaptern, um Daten- und Ereignisströme sauber zu kapseln und die Komplexität der Verkabelung im Anwendungsdiagramm zu minimieren.

## Schnittstellenstruktur

Da dieser Funktionsbaustein intern als Netzwerk aufgebaut ist und vollständig auf Adapter-Schnittstellen basiert, besitzt er keine direkt herausgeführten klassischen Ein- oder Ausgangsvariablen.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt implizit über die angeschlossenen Adapter.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisweiterleitung erfolgt implizit über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Plugs (Stecker)**

- **`OUT`** (Typ: `adapter::types::unidirectional::AL`):
  Der ausgewählte Ausgang. Über diesen Adapter werden die selektierten Daten (`D1`) und das dazugehörige Aktualisierungsereignis (`E1`) ausgegeben.

#### **Sockets (Buchsen)**

- **`G`** (Typ: `adapter::types::unidirectional::AX`):
  Der Selektor-Eingang (Gate/Selector). Steuert, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang durchgeschaltet wird.
- **`IN0`** (Typ: `adapter::types::unidirectional::AL`):
  Der erste auswählbare Eingangskanal. Dieser ist aktiv und wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Zustand `FALSE` (bzw. logisch 0) aufweist.
- **`IN1`** (Typ: `adapter::types::unidirectional::AL`):
  Der zweite auswählbare Eingangskanal. Dieser ist aktiv und wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Zustand `TRUE` (bzw. logisch 1) aufweist.

---

## Funktionsweise

Der Baustein realisiert eine klassische Multiplexer-Logik (Äquivalent zu `SEL` in IEC 61131-3) im IEC 61499-Kontext:

1. **Ereignisverarbeitung & Pufferung:**
   Trifft ein Ereignis auf einem der Eingangs-Adapter (`IN0`, `IN1`) oder dem Selektor-Adapter (`G`) ein, fangen interne D-Flipflops (`E_D_FF` bzw. `E_D_FF_ANY`) die Datenwerte ab und speichern diese zwischen.
2. **Daten-Typkonvertierung:**
   Die gepufferten Datenwerte werden über interne Transfer-Bausteine (`F_MOVE` mit dem Datentyp `LWORD`) an den zentralen Auswahlbaustein weitergeleitet.
3. **Auswahllogik (`F_SEL`):**
   Das Kernstück des Netzwerks wertet den Zustand des Selektors `G` aus:
   - Ist `G` gleich `FALSE`, wird das Signal von `IN0` an den Ausgang weitergegeben.
   - Ist `G` gleich `TRUE`, wird das Signal von `IN1` an den Ausgang weitergegeben.
4. **Ausgabe:**
   Nach erfolgreicher Auswahl wird das Ergebnis über ein weiteres Flipflop an den Plug `OUT` übertragen und dort zeitgleich mit einem Ereignis (`OUT.E1`) zur Verfügung gestellt.

---

## Technische Besonderheiten

- **Typoffenheit durch LWORD-Abstraktion:** Die interne Verwendung von `LWORD` (64-Bit) für die Kopieroperationen (`F_MOVE`) ermöglicht eine hohe Flexibilität bei den transportierten Daten, da verschiedene Bit- und Ganzzahlmuster ohne Informationsverlust übertragen werden können.
- **Vollständige Ereignissteuerung:** Jede Änderung an einem der Eingänge oder dem Selektor triggert eine sofortige Neuberechnung. Es wird sichergestellt, dass am Ausgang stets konsistente und aktuelle Daten anliegen.

---

## Zustandsübersicht

| Selektor-Zustand (`G.D1`) | Ausgangswert (`OUT.D1`) | Trigger-Ereignis |
| :--- | :--- | :--- |
| `FALSE` (0) | Wert von `IN0.D1` | Ereignis auf `IN0` oder `G` |
| `TRUE` (1) | Wert von `IN1.D1` | Ereignis auf `IN1` oder `G` |

---

## Anwendungsszenarien

- **Sollwert-Umschaltung:** Wechseln zwischen einem Standard-Sollwert (`IN0`) und einem alternativen Sollwert (`IN1`) basierend auf einem externen Steuersignal.
- **Hand-/Automatikbetrieb:** Umschalten eines Stellsignals für ein Ventil oder einen Motor zwischen einem manuell vorgegebenen Wert (z. B. aus einer Visualisierung) und dem berechneten Wert eines Automatik-Reglers.
- **Sensor-Redundanz:** Dynamisches Umschalten auf einen Ersatzsensor (`IN1`), falls der Hauptsensor (`IN0`) über eine Diagnosefunktion als fehlerhaft markiert wird (Umschaltung gesteuert durch Fehlerbit auf `G`).

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`SEL`-Funktionsbaustein aus der IEC 61131-3 Bibliothek bietet `AL_AX_SEL_AL` folgende Vorteile:

- **Weniger Verdrahtungsaufwand:** Durch die Kapselung in Adaptern müssen Ereignis- und Datenleitungen nicht einzeln gezogen werden. Ein einziger Verbindungspfad pro Kanal genügt.
- **Ereignis-Kopplung:** Der Baustein reagiert inhärent auf die in den Adaptern integrierten Event-Trigger, was eine manuelle ereignisseitige Verknüpfung im FBD (Function Block Diagram) überflüssig macht.

---

## Fazit

Der `AL_AX_SEL_AL`-Baustein ist eine effiziente und saubere Lösung für Umschaltaufgaben in komplexen 4diac-Anwendungen. Durch die konsequente Nutzung von unidirektionalen Adaptern fördert er ein modulares Softwaredesign und sorgt für übersichtliche Steuerungstopologien bei gleichzeitig robuster, ereignisgesteuerter Signalverarbeitung.

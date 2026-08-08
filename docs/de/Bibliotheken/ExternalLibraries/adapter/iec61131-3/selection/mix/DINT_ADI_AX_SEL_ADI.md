# DINT_ADI_AX_SEL_ADI


![DINT_ADI_AX_SEL_ADI](./DINT_ADI_AX_SEL_ADI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `DINT_ADI_AX_SEL_ADI` dient als binärer Selektor (Multiplexer) für `DINT` (Double Integer) Datenstrukturen innerhalb eines IEC 61499 Netzwerks. Er ermöglicht die dynamische Auswahl zwischen einem lokalen Daten-Eingang (`IN0`) und einem über einen Adapter eingespeisten Signal (`IN1`) basierend auf dem Zustand eines Selektor-Adapters (`G`). Das ausgewählte Signal wird an einen Ausgangs-Adapter (`OUT`) weitergeleitet. 

Dieser Baustein eignet sich besonders für modulare Steuerungsarchitekturen, bei denen Signale flexibel und ereignisgesteuert über standardisierte Adapterschnittstellen geroutet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **EI0** | Event | Signalisiert die Aktualisierung des lokalen Dateneingangs `IN0`. |

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge auf der Hauptschnittstelle. Ereignisse werden ausschließlich gekoppelt über den Ausgangs-Adapter (`OUT.E1`) ausgegeben.*

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | DINT | Auswählbarer lokaler Daten-Eingang (Double Integer). |

### **Daten-Ausgänge**

*Dieser Baustein besitzt keine direkten Daten-Ausgänge auf der Hauptschnittstelle. Die Datenweitergabe erfolgt ausschließlich über den Ausgangs-Adapter (`OUT.D1`).*

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug | `adapter::types::unidirectional::ADI` | Der ausgewählte Ausgang (enthält Daten `D1` und das dazugehörige Ereignis `E1`). |
| **IN1** | Socket | `adapter::types::unidirectional::ADI` | Auswählbarer Adapter-Eingang (liefert Daten `D1` und Ereignis `E1`). |
| **G** | Socket | `adapter::types::unidirectional::AX` | Selektor-Adapter zur Steuerung der Auswahl (liefert Auswahlsignal `D1` und Ereignis `E1`). |

## Funktionsweise

Das interne Netzwerk des Bausteins kombiniert klassische IEC 61131-3 Selektionslogik (`F_SEL`) mit der ereignisgesteuerten Verarbeitung von IEC 61499.

1. **Datenspeicherung und Synchronisation:**
   * Trifft ein Ereignis an einem der Eingänge (`EI0`, `IN1.E1` oder `G.E1`) ein, wird der dazugehörige Wert (`IN0`, `IN1.D1` oder `G.D1`) über interne D-Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) zwischengespeichert.
   * Ein interner Daten-Move (`F_MOVE_IN0` / `F_MOVE_IN1`) stellt sicher, dass die Werte konsistent an den eigentlichen Selektor übergeben werden.

2. **Auswahllogik:**
   * Der interne Baustein `F_SEL` wertet das Signal des Selektors `G.D1` aus:
     * Ist `G.D1` **FALSE (0)**, wird der Wert von `IN0` gewählt.
     * Ist `G.D1` **TRUE (1)**, wird der Wert von `IN1.D1` gewählt.

3. **Ausgabe:**
   * Der selektierte Wert wird an den Ausgangs-Adapter `OUT` übergeben.
   * Gleichzeitig wird das Ereignis `OUT.E1` ausgelöst, um nachfolgende Programmteile über die Datenänderung zu informieren.

## Technische Besonderheiten

* **Hybride Schnittstelle:** Der Baustein schlägt eine Brücke zwischen der klassischen direkten Datenverdrahtung (`IN0` als direkter `DINT`-Eingang) und der modernen adapterbasierten Kommunikation (`IN1` und `OUT`).
* **Datenkonsistenz:** Durch die Verwendung von internen Flanken- und Speicherbausteinen (`E_D_FF_ANY`, `F_MOVE`) ist sichergestellt, dass auch bei asynchron eintreffenden Ereignissen keine Daten verloren gehen oder inkonsistente Zwischenzustände weitergeleitet werden.

## Zustandsübersicht

| Selektor-Zustand (`G.D1`) | Aktiver Kanal | Ausgangswert (`OUT.D1`) | Auslösendes Ereignis am Ausgang (`OUT.E1`) |
| :---: | :---: | :---: | :---: |
| **FALSE** | `IN0` | Wert von `IN0` | Bei jedem Ereignis auf `EI0` oder `G.E1` |
| **TRUE** | `IN1` | Wert von `IN1.D1` | Bei jedem Ereignis auf `IN1.E1` oder `G.E1` |

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Wechsel zwischen einem manuell vorgegebenen Standardwert (über den lokalen Eingang `IN0`) und einem automatisiert berechneten Wert, der über ein Adapternetzwerk (`IN1`) geliefert wird.
* **Signal-Bypass:** Implementierung von Test- oder Überbrückungsfunktionen, bei denen im Normalbetrieb der Adapterpfad genutzt wird, im Fehlerfall jedoch auf einen sicheren Ersatzwert auf `IN0` zurückgegriffen werden kann.
* **Modulare Maschinensteuerung:** Kopplung von Teilsystemen, bei denen die Steuerungsschnittstellen über standardisierte `ADI`- und `AX`-Adapter gekoppelt sind.

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL`:** Der Standard-Auswahlbaustein arbeitet rein datenorientiert und besitzt keine integrierte Ereignissteuerung oder Adapter-Kompatibilität. `DINT_ADI_AX_SEL_ADI` kapselt diese Logik und stellt sie direkt für moderne, adapterbasierte Applikationen zur Verfügung.
* **Reine Adapter-Multiplexer:** Im Gegensatz zu Multiplexern, die ausschließlich Adapter schalten, erlaubt dieser Baustein das direkte Einspeisen eines lokalen `DINT`-Wertes ohne den Overhead eines zusätzlichen Eingangs-Adapters.

## Fazit

Der `DINT_ADI_AX_SEL_ADI` ist ein robuster und vielseitig einsetzbarer Hilfsbaustein. Er vereinfacht das Signalrouting in komplexen IEC 61499 Systemen erheblich, indem er die ereignisgesteuerte Selektion direkt auf Adapterebene abbildet und gleichzeitig eine hohe Datenintegrität garantiert.
# AD_AX_SEL_AD


![AD_AX_SEL_AD](./AD_AX_SEL_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AD_AX_SEL_AD` dient der binären Auswahl (Selektion) zwischen zwei Eingangssignalen, die über Adapterstrukturen bereitgestellt werden. Basierend auf dem Zustand eines Selektions-Signals (G) wird entweder der Wert des Eingangs `IN0` oder des Eingangs `IN1` an den Ausgang `OUT` weitergeleitet. Der Baustein ist intern als Composite-Funktionsbaustein realisiert und nutzt standardisierte IEC 61499- und IEC 61131-Mechanismen, um eine ereignisgesteuerte, typsichere Signalweiterleitung zu gewährleisten.

## Schnittstellenstruktur
Die Schnittstellen dieses Funktionsbausteins sind vollständig über Adapter realisiert, was eine modulare und übersichtliche Verdrahtung im Anwendungsnetzwerk ermöglicht.

### **Ereignis-Eingänge**
*Dieser Baustein besitzt keine direkten Ereignis-Eingänge am Gehäuse. Die Ereignissteuerung erfolgt implizit über die Adapter.*

### **Ereignis-Ausgänge**
*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge am Gehäuse. Die Ereignisweiterleitung erfolgt implizit über die Adapter.*

### **Daten-Eingänge**
*Dieser Baustein besitzt keine direkten Daten-Eingänge am Gehäuse.*

### **Daten-Ausgänge**
*Dieser Baustein besitzt keine direkten Daten-Ausgänge am Gehäuse.*

### **Adapter**
* **Sockets (Eingangs-Adapter):**
  * `IN0` (Typ: `adapter::types::unidirectional::AD`): Erster auswählbarer Eingangskanal (wird gewählt, wenn `G` den Zustand `FALSE` hat).
  * `IN1` (Typ: `adapter::types::unidirectional::AD`): Zweiter auswählbarer Eingangskanal (wird gewählt, wenn `G` den Zustand `TRUE` hat).
  * `G` (Typ: `adapter::types::unidirectional::AX`): Selektor-Signal zur Steuerung der Auswahl.
* **Plugs (Ausgangs-Adapter):**
  * `OUT` (Typ: `adapter::types::unidirectional::AD`): Der ausgewählte Ausgangskanal, der den Wert des selektierten Eingangs führt.

## Funktionsweise
Der Baustein kapselt ein internes Netzwerk aus Steuer- und Konvertierungsbausteinen:
1. **Signalpufferung und Erfassung:** Sobald sich an den Adaptern `IN0`, `IN1` oder `G` Daten ändern, triggert das entsprechende Adapter-Ereignis `E1` die internen Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`).
2. **Datenweiterleitung:** Die Datenwerte (`D1`) der Eingänge `IN0` und `IN1` werden über interne Datenkonverter (`F_MOVE` vom Typ `DWORD`) eingelesen und dem Auswahlbaustein `F_SEL` zur Verfügung gestellt.
3. **Auswahllogik (`F_SEL`):** 
   * Liegt am Selektor `G` das Signal `FALSE` an, schaltet der Baustein das Signal von `IN0` auf den Ausgang.
   * Liegt am Selektor `G` das Signal `TRUE` an, schaltet der Baustein das Signal von `IN1` auf den Ausgang.
4. **Ausgangssynchronisation:** Der ausgewählte Wert wird über einen weiteren `F_MOVE`-Baustein an ein Ausgangs-Flip-Flop (`E_D_FF_ANY_OUT`) übergeben. Dieses generiert das Ausgangsereignis `E1` am Ausgangsadapter `OUT` und legt den selektierten Wert an `D1` an.

## Technische Besonderheiten
* **Adapter-Kapselung:** Durch die Verwendung von unidirektionalen Adaptern (`AD` und `AX`) wird das Signalrouting vereinfacht und lose Daten- und Ereignisleitungen vermieden.
* **Typunabhängigkeit über DWORD:** Die internen Datenpfade verwenden den Datentyp `DWORD` zur Repräsentation der Adapterdaten, was eine flexible Übertragung unterschiedlicher Datenformate ermöglicht.
* **Echtzeitnahe Reaktion:** Jede Flanke oder Wertänderung an den Eingangs- oder Selektor-Adaptern führt unverzüglich zu einer Aktualisierung des Ausgangs.

## Zustandsübersicht
Der Baustein besitzt als Composite-FB kein eigenes Execution Control Chart (ECC). Das Verhalten ist rein daten- und ereignisgesteuert durch das interne Zusammenspiel der Standard-FBs:
* **Ereignis auf `IN0` oder `IN1`:** Aktualisiert den jeweiligen internen Wertpuffer. Falls der betroffene Eingang gerade aktiv geschaltet ist, wird der neue Wert sofort an `OUT` ausgegeben.
* **Ereignis auf `G`:** Wechselt den aktiven Kanal und gibt den Wert des neu gewählten Kanals an `OUT` aus.

## Anwendungsszenarien
* **Sensorredundanz:** Umschalten zwischen einem primären Sensor (`IN0`) und einem redundanten Backup-Sensor (`IN1`) bei Signalverlust oder Fehlfunktion.
* **Sollwert-Umschaltung:** Wechseln zwischen Handbetrieb-Sollwert und Automatik-Sollwert in industriellen Prozessen.
* **Signal-Multiplexing:** Strukturierte Weiterleitung von Steuerungsdaten in modular aufgebauten Gesamtanlagen.

## Vergleich mit ähnlichen Bausteinen
* **Standard `F_SEL`:** Der klassische `F_SEL`-Baustein nach IEC 61131-3 arbeitet direkt auf elementaren Datentypen und erfordert eine manuelle Verdrahtung von Trigger-Ereignissen. `AD_AX_SEL_AD` kapselt diese Logik und stellt sie direkt für adapterbasierte Architekturen bereit.
* **Multiplexer (MUX):** Ein klassischer MUX erlaubt die Auswahl aus mehr als zwei Kanälen mittels eines Integer-Werts. `AD_AX_SEL_AD` ist für einfache binäre Entscheidungen (Entweder-Oder) optimiert und spart dadurch Verarbeitungsressourcen.

## Fazit
Der `AD_AX_SEL_AD` ist ein robuster und effizienter Hilfsbaustein zur ereignisgesteuerten Signalumschaltung. Durch die konsequente Nutzung von Adaptern fügt er sich ideal in moderne, serviceorientierte Steuerungsarchitekturen innerhalb von 4diac ein.
# AX_SEL_DWORD


![AX_SEL_DWORD](./AX_SEL_DWORD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_DWORD` ist ein Standard-Auswahlbaustein (Binary Selection) für den Datentyp `DWORD` (Double Word). Er basiert auf der Norm IEC 61131-3 und ermöglicht es, abhängig vom Zustand eines Selektions-Adapters (`G`), zwischen zwei DWORD-Eingangswerten (`IN0` und `IN1`) zu wählen und den ausgewählten Wert am Ausgang `OUT` bereitzustellen. 

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Löst die Aktualisierung und Übernahme des Daten-Eingangs `IN0` aus.
* **EI1**: Löst die Aktualisierung und Übernahme des Daten-Eingangs `IN1` aus.

### **Ereignis-Ausgänge**

* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert dem nachfolgenden System, dass ein neuer ausgewählter Wert an `OUT` anliegt.

### **Daten-Eingänge**

* **IN0** (`DWORD`): Der erste auswählbare Eingangswert. Wird an den Ausgang durchgereicht, wenn das Auswahlsignal des Adapters `G` logisch `0` (FALSCH) ist.
* **IN1** (`DWORD`): Der zweite auswählbare Eingangswert. Wird an den Ausgang durchgereicht, wenn das Auswahlsignal des Adapters `G` logisch `1` (WAHR) ist.

### **Daten-Ausgänge**

* **OUT** (`DWORD`): Der aktuell ausgewählte DWORD-Wert.

### **Adapter**

* **G** (`adapter::types::unidirectional::AX`): Ein unidirektionaler Adapter, welcher als Selektor fungiert. Über diesen Adapter wird gesteuert, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang geschaltet wird.

## Funktionsweise

Der Funktionsbaustein blockiert oder leitet Daten basierend auf dem Zustand des Adapters `G` weiter:
1. Trifft ein Ereignis am Adapter `G` ein, wird dessen Zustand gelesen.
2. Der interne Standard-Selektionsbaustein `F_SEL` entscheidet:
   * Ist das Signal von `G` deaktiviert (FALSCH), wird der Wert von `IN0` gewählt.
   * Ist das Signal von `G` aktiviert (WAHR), wird der Wert von `IN1` gewählt.
3. Der ausgewählte Wert wird an den Ausgang `OUT` übergeben.
4. Ein Ausgangsereignis (`CNF`) wird an das System gesendet.

## Technische Besonderheiten

* **Ereignis-Optimierung**: Der Baustein nutzt intern `E_D_FF_ANY`-Elemente zur Flankenerkennung. Ein Ausgangsereignis an `CNF` wird nur dann generiert, wenn sich der tatsächlich ausgewählte Wert am Ausgang `OUT` ändert. Dies spart Systemressourcen und verhindert unnötige Folge-Berechnungen im FB-Netzwerk.
* **Adaptergesteuert**: Die Selektion erfolgt nicht über einen klassischen booleschen Dateneingang, sondern ist über einen dedizierten Adapter (`G`) gekapselt. Dies ermöglicht eine saubere, modulare Architektur im Steuerungsprogramm.

## Zustandsübersicht

Der Funktionsbaustein besitzt keine eigene komplexe Zustandsmaschine (ECC), da es sich um einen Composite-Funktionsbaustein handelt. Der Signal- und Datenfluss wird direkt durch die internen Verbindungen der standardisierten Unterbausteine (`F_SEL`, `F_MOVE`, `E_D_FF_ANY`) bestimmt.

## Anwendungsszenarien

* **Rezeptur- und Parameterumschaltung**: Dynamisches Umschalten von Konfigurations- oder Parameter-Doppelworten (z. B. Grenzwerte, Bitmasken) zur Laufzeit.
* **Redundante Sensorik / Signalquellen**: Umschalten zwischen einem Primär- und Sekundär-Datenstrom im DWORD-Format bei Ausfall oder Wartung.
* **Modus-Auswahl**: Auswahl unterschiedlicher Status- oder Steuerwörter für nachgelagerte Aggregate.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen IEC 61131-3 `SEL`-Baustein benötigt `AX_SEL_DWORD` keinen permanent anliegenden booleschen Steuereingang. Stattdessen wird die Auswahl ereignisorientiert über den Adapter `G` gesteuert. Zudem sorgt die interne Filterung dafür, dass nachfolgende Programmteile nur bei einer echten Wertänderung am Ausgang getriggert werden.

## Fazit

`AX_SEL_DWORD` bietet eine effiziente und ereignisgesteuerte Möglichkeit, DWORD-Datenströme innerhalb einer 4diac-Applikation sauber zu verwalten. Dank der Kopplung über einen Adapter eignet er sich hervorragend für serviceorientierte und modulare Softwarearchitekturen in der Automatisierungstechnik.
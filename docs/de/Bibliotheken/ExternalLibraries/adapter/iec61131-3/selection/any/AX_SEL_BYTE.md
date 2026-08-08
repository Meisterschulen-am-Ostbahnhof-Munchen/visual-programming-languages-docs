# AX_SEL_BYTE

![AX_SEL_BYTE Funktionsbaustein](AX_SEL_BYTE.png)


![AX_SEL_BYTE](./AX_SEL_BYTE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_BYTE` ist ein standardisierter Selektionsbaustein, der zur binären Auswahl zwischen zwei Eingangswerten vom Datentyp `BYTE` (`IN0` und `IN1`) dient. Die Steuerung der Auswahl erfolgt über einen spezialisierten Adapter-Kanal (`G`). Der Baustein eignet sich besonders für ereignisgesteuerte Anwendungen, bei denen Datenströme oder Zustands-Bytes in Abhängigkeit von einem externen Auswahlsignal flexibel umgeschaltet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
* **EI0**: Aktualisiert und übernimmt den Wert am Daten-Eingang `IN0`.
* **EI1**: Aktualisiert und übernimmt den Wert am Daten-Eingang `IN1`.

### **Ereignis-Ausgänge**
* **CNF**: Bestätigungsereignis (Confirmation). Signalisiert dem nachfolgenden System, dass ein neuer ausgewählter Wert am Ausgang `OUT` bereitsteht.

### **Daten-Eingänge**
* **IN0** (`BYTE`): Erster auswählbarer Eingangswert (wird selektiert, wenn das Auswahlsignal logisch `0` bzw. inaktiv ist).
* **IN1** (`BYTE`): Zweiter auswählbarer Eingangswert (wird selektiert, wenn das Auswahlsignal logisch `1` bzw. aktiv ist).

### **Daten-Ausgänge**
* **OUT** (`BYTE`): Der aktuell ausgewählte Byte-Wert.

### **Adapter**
* **G** (Typ: `adapter::types::unidirectional::AX`): Ein unidirektionaler Adapter, der als Selektor fungiert. Er liefert sowohl das Ereignis (`E1`) zur Triggerung der Auswahl als auch den eigentlichen booleschen Auswahl-Datenwert (`D1`).

## Funktionsweise

Der Baustein verhält sich wie ein ereignisgesteuerter 2-zu-1-Multiplexer für Byte-Daten:

1. **Eingangsverarbeitung**: Sobald eines der Ereignisse `EI0` oder `EI1` eintrifft, wird der zugehörige Datenwert (`IN0` oder `IN1`) intern gepuffert.
2. **Adapter-Umschaltung**: Trifft über den Adapter `G` ein Ereignis `E1` ein, wird der Selektionswert `D1` ausgewertet. 
   - Ist der Selektionswert `FALSE` (0), wird der Wert von `IN0` an den Selektor weitergegeben.
   - Ist der Selektionswert `TRUE` (1), wird der Wert von `IN1` weitergegeben.
3. **Ereignis-Filterung am Ausgang**: Der Baustein gibt nur dann ein Bestätigungsereignis (`CNF`) am Ausgang aus, wenn sich der tatsächlich ausgewählte Wert am Ausgang `OUT` verändert hat. Dies verhindert unnötige Folge-Berechnungen im System, wenn sich Eingangsdaten ohne Relevanz für den Ausgang ändern.

## Technische Besonderheiten

* **Ereignisbasierte Optimierung**: Durch den Einsatz interner Flankenerkennungen (`E_D_FF_ANY`) wird ein `CNF`-Event nur bei einer echten Änderung des Ausgangswerts erzeugt.
* **Adapter-Kopplung**: Die Verwendung des `AX`-Adapters anstelle eines einfachen Bool-Eingangs ermöglicht eine saubere Kapselung der Steuerungslogik und vereinfacht die Verdrahtung in komplexen 4diac-Netzwerken.

## Zustandsübersicht

Da es sich bei `AX_SEL_BYTE` um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, wird das Verhalten durch das interne Zusammenspiel der Komponenten definiert:

* **Zustand "Warten"**: Der Baustein wartet auf Ereignisse an `EI0`, `EI1` oder dem Adapter `G`.
* **Zustand "Eingangs-Update"**: Ein Wert an `IN0` oder `IN1` ändert sich. Der Wert wird intern gespeichert, führt aber erst dann zu einer Ausgabe, wenn er aktiv selektiert ist und sich der Ausgangswert dadurch ändert.
* **Zustand "Umschaltung"**: Der Adapter signalisiert eine Änderung von `G`. Der Baustein schaltet den Pfad um, aktualisiert `OUT` und triggert `CNF`, falls sich der Wert von `OUT` ändert.

## Anwendungsszenarien

* **Betriebsmodus-Umschaltung**: Auswahl zwischen zwei verschiedenen Status- oder Befehls-Bytes für eine Maschine basierend auf dem aktuellen Automatik-/Handbetrieb-Zustand.
* **Signal-Fallback**: Automatisches Umschalten von einem primären Daten-Byte auf einen Standard-Ersatzwert, falls ein Fehler im System detektiert und über den Adapter signalisiert wird.
* **Parametrierung**: Umschalten zwischen zwei Parametersätzen (z. B. vordefinierte Byte-Konfigurationen) im laufenden Betrieb.

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL`**: Der klassische IEC 61131-3 `F_SEL`-Baustein arbeitet rein datenflussorientiert und besitzt keine Ereignissteuerung oder Adapter-Schnittstellen. `AX_SEL_BYTE` erweitert diese Grundfunktion um ereignisgesteuerte Auswertung und ereignisbasierte Ausgangsfilterung.
* **Andere `AX_SEL_x`-Bausteine**: Es existieren analoge Bausteine für andere Datentypen (z. B. für `REAL`, `INT` oder `WORD`). Sie teilen die exakt gleiche Funktionsweise, unterscheiden sich jedoch im verarbeiteten Datentyp der Ein- und Ausgänge.

## Fazit

`AX_SEL_BYTE` ist ein effizienter Hilfsbaustein für die strukturierte, ereignisgesteuerte Programmierung in 4diac. Er verbindet die klassische Auswahllogik der IEC 61131-3 mit den modernen, ressourcenschonenden Paradigmen der IEC 61499.
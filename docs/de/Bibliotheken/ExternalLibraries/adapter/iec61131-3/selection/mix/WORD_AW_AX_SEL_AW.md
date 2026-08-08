# WORD_AW_AX_SEL_AW


![WORD_AW_AX_SEL_AW](./WORD_AW_AX_SEL_AW.svg)

*(Keine Abbildung verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **WORD_AW_AX_SEL_AW** ist ein ereignisgesteuerter, binärer Selektor für Daten des Typs `WORD`. Er realisiert eine Auswahlfunktion (analog zu `SEL` nach IEC 61131-3) unter Verwendung von modernen, unidirektionalen Adapterschnittstellen. Der Baustein ermöglicht es, ereignisbasiert zwischen einem direkt angebundenen `WORD`-Eingang und einem über einen Adapter eingespeisten `WORD`-Eingang zu wählen und das Ergebnis an einen Ausgangs-Adapter weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **EI0** | Event | Aktualisiert und übernimmt den Wert des Dateneingangs `IN0`. |

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge auf Blockebene. Die Ereignisausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | WORD | Direkter, auswählbarer Eingangswert 0. Wird selektiert, wenn der Selektor `G` den Zustand `FALSE` hat. |

### **Daten-Ausgänge**

*Dieser Baustein besitzt keine direkten Daten-Ausgänge auf Blockebene. Die Datenausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug (Stecker) | `adapter::types::unidirectional::AW` | Der ausgewählte Ausgangswert (`WORD`) inklusive des zugehörigen Aktualisierungsereignisses. |
| **IN1** | Socket (Buchse) | `adapter::types::unidirectional::AW` | Auswählbarer Eingangswert 1 (`WORD`) inklusive des zugehörigen Aktualisierungsereignisses. Wird selektiert, wenn der Selektor `G` den Zustand `TRUE` hat. |
| **G** | Socket (Buchse) | `adapter::types::unidirectional::AX` | Selektor-Eingang (Boolean/Bit-Zustand). Steuert, welcher Eingang auf den Ausgang geschaltet wird. |

## Funktionsweise

Der Baustein arbeitet intern mit einer Kombination aus Event-D-Flip-Flops (`E_D_FF` und `E_D_FF_ANY`) sowie Konvertierungs- und Auswahlbausteinen (`F_MOVE`, `F_SEL`). 

1. **Datenspeicherung und Synchronisation:** 
   Sobald an einem der Eingänge (`EI0`, `IN1.E1` oder `G.E1`) ein Ereignis eintrifft, wird der entsprechende Datenwert (`IN0`, `IN1.D1` oder `G.D1`) im jeweils zugeordneten internen Flip-Flop zwischengespeichert. Dies stellt sicher, dass die Daten konsistent vorliegen.
2. **Auswahllogik (Selection):**
   Das interne Auswahlelement `F_SEL` wertet den Zustand des Selektors `G.D1` aus:
   * Ist der Zustand von **`G` = `FALSE`**, wird der Wert von **`IN0`** an den Ausgang durchgeschaltet.
   * Ist der Zustand von **`G` = `TRUE`**, wird der Wert von **`IN1`** an den Ausgang durchgeschaltet.
3. **Ausgabe:**
   Der ausgewählte Wert wird über den internen Baustein `F_MOVE_OUT` an den Ausgangs-Adapter `OUT.D1` übergeben. Gleichzeitig wird das Ausgangsereignis `OUT.E1` ausgelöst, um nachfolgende Programmteile über die Datenänderung zu informieren.

## Technische Besonderheiten

* **Hybride Schnittstellen:** Der Baustein schließt die Lücke zwischen klassischer IEC 61499 Event/Data-Verbindung (`EI0` / `IN0`) und modernen, adapterbasierten Kommunikationsstrukturen.
* **Unidirektionale Adapter:** Es werden schlanke, unidirektionale Adaptertypen verwendet (`AW` für *Adapter Word*, `AX` für *Adapter Binary/Boolean*), was die Kopplung vereinfacht und Ressourcen spart.
* **Flanken- und Ereignisgesteuert:** Jede Änderung an einem der Eingänge triggert sofort eine Neuberechnung und Aktualisierung des Ausgangs.

## Zustandsübersicht

| Zustand Selektor `G.D1` | Trigger-Ereignis | Gewählter Ausgangswert `OUT.D1` | Ausgangs-Event `OUT.E1` |
| :---: | :---: | :---: | :---: |
| `FALSE` | Beliebig (`EI0`, `G.E1`, `IN1.E1`) | **`IN0`** | Aktiviert |
| `TRUE` | Beliebig (`EI0`, `G.E1`, `IN1.E1`) | **`IN1.D1`** | Aktiviert |

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Wechseln zwischen einem lokal vorgegebenen Standard-Sollwert (`IN0`) und einem über ein Netzwerk/Adapter empfangenen Remote-Sollwert (`IN1`).
* **Betriebsartenwahl:** Umschalten von Steuerworten (`WORD`) basierend auf dem aktuellen Anlagenzustand (z. B. Automatikbetrieb vs. Handbetrieb über Selektor `G`).
* **Signal-Fallback:** Schnelle, ereignisgesteuerte Umschaltung auf einen sicheren Ersatzwert bei Ausfall einer Systemkomponente.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3 Bibliothek bietet der `WORD_AW_AX_SEL_AW` eine direkte Integration in die ereignisgesteuerte Welt der IEC 61499. Während der klassische `F_SEL` rein datenflussorientiert arbeitet, fängt dieser Baustein asynchrone Ereignisse über die Adapter ab, speichert die Daten konsistent zwischen und signalisiert Änderungen aktiv an den Folgeprozess.

## Fazit

Der Baustein **WORD_AW_AX_SEL_AW** ist ein nützliches Werkzeug für die strukturierte Signalverarbeitung in komplexen IEC 61499 Steuerungsanwendungen. Durch die Kapselung der Adapter- und Flip-Flop-Logik vereinfacht er das Design von umschaltbaren Signalpfaden im Applikationsdiagramm erheblich und sorgt für sauberen, ereignisgesteuerten Datenfluss.
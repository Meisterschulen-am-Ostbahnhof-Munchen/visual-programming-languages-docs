# STRING_AIS_AX_SEL_AIS




![STRING_AIS_AX_SEL_AIS](./STRING_AIS_AX_SEL_AIS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `STRING_AIS_AX_SEL_AIS` dient als binärer Selektor (Multiplexer) für Zeichenketten (`STRING`). Er ermöglicht es, basierend auf dem Steuersignal eines Gate-Adapters, zwischen einem lokalen String-Eingang und einem über einen Adapter eingespeisten String-Eingang auszuwählen und das Ergebnis an einen Ausgangs-Adapter weiterzuleiten. Der Baustein verbindet die klassische Auswahllogik der IEC 61131-3 mit der ereignisgesteuerten, adapterbasierten Architektur von IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI0**: Triggert die Übernahme und Verarbeitung des lokalen String-Eingangs `IN0`.

### **Ereignis-Ausgänge**

*(Keine direkten Ereignis-Ausgänge auf Blockebene vorhanden. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter `OUT`.)*

### **Daten-Eingänge**

* **IN0** (STRING): Lokaler, auswählbarer String-Wert.

### **Daten-Ausgänge**

*(Keine direkten Daten-Ausgänge auf Blockebene vorhanden. Die Datenübertragung erfolgt gekapselt über den Ausgangs-Adapter `OUT`.)*

### **Adapter**

* **Plugs (Anschlüsse / Ausgänge):**
  * **OUT** (Typ: `adapter::types::unidirectional::AIS`): Der ausgewählte Ausgangs-Adapter. Gibt den selektierten String-Wert (`D1`) aus und signalisiert Aktualisierungen über das Ereignis (`E1`).
* **Sockets (Buchsen / Eingänge):**
  * **IN1** (Typ: `adapter::types::unidirectional::AIS`): Adapterbasierter String-Eingang. Liefert den String-Wert (`D1`) und das Triggerereignis (`E1`).
  * **G** (Typ: `adapter::types::unidirectional::AX`): Der Selektor-Adapter (Gate). Bestimmt über das Datensignal (`D1` / Boolean) und das Steuerereignis (`E1`), welcher Eingang auf den Ausgang geschaltet wird.

## Funktionsweise

Der Baustein basiert intern auf einem strukturierten Netzwerk aus Standard-Funktionsbausteinen. Die Signal- und Datenverarbeitung läuft wie folgt ab:
1. Treffen Ereignisse an `EI0`, `IN1.E1` oder `G.E1` ein, werden die zugehörigen Datenwerte (`IN0`, `IN1.D1` bzw. `G.D1`) über interne Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) gepuffert und synchronisiert.
2. Der interne Selektor `F_SEL` wertet das Steuersignal aus:
   * Ist das Selektorsignal `G.D1` **FALSE** (0), wird der Wert von **IN0** (lokal) ausgewählt.
   * Ist das Selektorsignal `G.D1` **TRUE** (1), wird der Wert von **IN1.D1** (Adapter) ausgewählt.
3. Der ausgewählte String wird über eine interne Move-Operation an den Ausgangs-Adapter `OUT.D1` übergeben, zeitgleich wird das Ausgangsereignis `OUT.E1` gefeuert.

## Technische Besonderheiten

* **Ereignissynchronisation**: Durch den Einsatz von flanken- und ereignisgesteuerten Flip-Flops im internen Netzwerk wird sichergestellt, dass Datenänderungen an den asynchronen Eingängen stets konsistent und ohne Datenverlust ("Race Conditions") verarbeitet werden.
* **Reduzierte Verdrahtung**: Durch die konsequente Nutzung von Adaptern (`AIS` und `AX`) wird die Anzahl der sichtbaren Verbindungslinien im übergeordneten System-Diagramm minimiert, was die Lesbarkeit komplexer Anwendungen stark erhöht.

## Zustandsübersicht

Da es sich um einen Composite-Funktionsbaustein (FBNetwork) handelt, wird das Verhalten durch den internen Daten- und Ereignisfluss bestimmt. Die folgende Tabelle zeigt das Verhalten bei verschiedenen Eingangskombinationen:

| Auslösendes Ereignis | Zustand Selector (`G.D1`) | Weitergeleiteter Wert an `OUT.D1` | Ausgangs-Ereignis |
| :--- | :--- | :--- | :--- |
| `EI0` | `FALSE` | Aktueller Wert von `IN0` | `OUT.E1` |
| `EI0` | `TRUE` | Letzter bekannter Wert von `IN1.D1` | `OUT.E1` |
| `IN1.E1` | `FALSE` | Letzter bekannter Wert von `IN0` | `OUT.E1` |
| `IN1.E1` | `TRUE` | Aktueller Wert von `IN1.D1` | `OUT.E1` |
| `G.E1` | `FALSE` | Aktueller Wert von `IN0` | `OUT.E1` |
| `G.E1` | `TRUE` | Aktueller Wert von `IN1.D1` | `OUT.E1` |

## Anwendungsszenarien

* **Rezeptur- und Parameterumschaltung**: Auswahl zwischen einem lokal im Programm fest definierten Standard-Parametersatz (String über `IN0`) und einem dynamisch über ein Netzwerk oder HMI geladenen Parametersatz (über Adapter `IN1`).
* **HMI-Text-Routing**: Dynamisches Umschalten von Status- und Fehlermeldungen auf einem Display. So kann beispielsweise im Normalbetrieb ein statischer Betriebszustand (`IN0`) angezeigt werden, während bei einer Störung die detaillierte Fehlermeldung eines Subsystems (`IN1`) eingeblendet wird.
* **Weichensteuerung im Materialfluss**: Routing von Barcode- oder RFID-Informationen (als Strings) an unterschiedliche Zielstationen in Abhängigkeit von Sensorschranken (Gate-Signal `G`).

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL` (IEC 61131-3)**: Der Standard-Selektionsbaustein arbeitet rein datenflussorientiert. Er besitzt keine ereignisbasierte Steuerung und unterstützt keine Adapter. `STRING_AIS_AX_SEL_AIS` kapselt diese Basisfunktionalität und erweitert sie um eine vollständige Ereignis- und Adaptersteuerung für IEC 61499.
* **Klassische Multiplexer (ohne Adapter)**: Diese benötigen separate Anschlüsse für Daten und Events jedes Kanals. Der vorliegende Baustein vereinfacht die Integration durch die Bündelung von Signalen in den Adaptern `AIS` und `AX`.

## Fazit

Der `STRING_AIS_AX_SEL_AIS` ist ein nützlicher Hilfsbaustein für die strukturierte Softwareentwicklung in der 4diac-IDE. Er bietet eine saubere, ereignisgesteuerte Möglichkeit, String-Datenströme zu kontrollieren, und sorgt durch die Verwendung von standardisierten Adaptern für ein aufgeräumtes und wartungsfreundliches Applikationsdesign.
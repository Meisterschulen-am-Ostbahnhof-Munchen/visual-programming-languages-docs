# AB_BYTE_AX_SEL_AB


![AB_BYTE_AX_SEL_AB](./AB_BYTE_AX_SEL_AB.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AB_BYTE_AX_SEL_AB` ist ein binärer Selektor (Multiplexer) für Daten des Typs `BYTE` im IEC 61499-Standard. Er ermöglicht die Auswahl zwischen zwei Byte-Eingangssignalen basierend auf einem logischen Auswahlsignal (Selector). Der Baustein nutzt standardisierte, unidirektionale Adapterverbindungen zur Kapselung von Daten und Ereignissen, was zu einem sauberen und modularen Design innerhalb der 4diac-ide beiträgt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| `EI1` | Setzt bzw. aktualisiert den Wert des direkten Dateneingangs `IN1` | `IN1` |

### **Ereignis-Ausgänge**

*Der Baustein besitzt keine direkten Ereignis-Ausgänge auf der Hauptebene. Die Ereignisausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Datenpunkt | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| `IN1` | `BYTE` | Selektierbare Eingangsvariable (Kanal 1) |

### **Daten-Ausgänge**

*Der Baustein besitzt keine direkten Daten-Ausgänge auf der Hauptebene. Die Datenausgabe erfolgt gekapselt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| `OUT` | `adapter::types::unidirectional::AB` | Plug (Stecker) | Der ausgewählte Ausgang (überträgt das selektierte `BYTE` und das zugehörige Ereignis). |
| `IN0` | `adapter::types::unidirectional::AB` | Socket (Buchse) | Selektierbare Eingangsvariable (Kanal 0) via Adapter. |
| `G` | `adapter::types::unidirectional::AX` | Socket (Buchse) | Auswahlsignal (Selector/Gate) via Adapter. |

*Hinweis: `AB` steht für einen Adapter zur Übertragung eines `BYTE`-Wertes, während `AX` für die Übertragung eines booleschen Zustands (`BOOL`/Bit) zuständig ist.*

---

## Funktionsweise

Der Baustein arbeitet intern als ereignisgesteuerter Multiplexer. Die Auswahl des an `OUT` weiterzugebenden Wertes basiert auf dem logischen Zustand des Adapters `G` (Selector):

1. **Pufferung & Synchronisation:**
   * Die Eingangssignale von `IN0` (Adapter), `IN1` (Direkteingang über `EI1`) und dem Selector `G` (Adapter) werden intern mithilfe von D-Flip-Flop-Bausteinen (`E_D_FF_ANY` bzw. `E_D_FF`) bei Eintreffen des jeweiligen Ereignisses zwischengespeichert.
2. **Auswahllogik (F_SEL):**
   * Wenn das Auswahlsignal `G.D1` den Zustand **`FALSE`** (0) hat, wird der Wert von `IN0` (Kanal 0) an den Ausgang weitergeleitet.
   * Wenn das Auswahlsignal `G.D1` den Zustand **`TRUE`** (1) hat, wird der Wert von `IN1` (Kanal 1) an den Ausgang weitergeleitet.
3. **Ausgabe:**
   * Sobald sich ein Eingangswert oder das Auswahlsignal ändert, berechnet der interne Funktionsbaustein `F_SEL` den neuen Ausgangswert. Dieser wird über den Adapter `OUT` ausgegeben und gleichzeitig ein Ausgangsereignis (`OUT.E1`) ausgelöst.

---

## Technische Besonderheiten

* **Adapter-basierte Architektur:** Durch die Verwendung von Plugs und Sockets wird die Anzahl der sichtbaren Verbindungslinien im übergeordneten System drastisch reduziert, was die Übersichtlichkeit komplexer Anwendungen verbessert.
* **Ereignissteuerung:** Die interne Verarbeitung reagiert flexibel auf Ereignisse aus verschiedenen Quellen (sowohl direkte Events wie `EI1` als auch Adapter-Events von `IN0` und `G`).
* **Typkonvertierung und Schutz:** Durch den Einsatz von internen Verschiebe-Bausteinen (`F_MOVE`) wird eine sichere Datenübergabe gewährleistet.

---

## Zustandsübersicht

| Zustand Selector `G` | Aktiver Eingang | Wert an `OUT` | triggered Event an `OUT` |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | `IN0.D1` | Ja (bei Wertänderung oder Trigger von `IN0.E1`/`G.E1`) |
| `TRUE` | `IN1` | `IN1` | Ja (bei Wertänderung oder Trigger von `EI1`/`G.E1`) |

---

## Anwendungsszenarien

* **Umschaltung Betriebsmodus:** Wechseln zwischen einem Standard-Sollwert (z. B. Automatikmodus via `IN0`) und einem manuell vorgegebenen Byte-Wert (z. B. Handbetrieb via `IN1`).
* **Fehlerwert-Aufschaltung:** Im Normalbetrieb wird der Sensorwert eines Byte-Kanals (`IN0`) durchgelassen. Bei Erkennung eines Fehlers schaltet der Selektor `G` auf einen sicheren Ersatzwert (`IN1`) um.
* **Signalrouting in Bussystemen:** Dynamisches Routing von Status- oder Kontroll-Bytes innerhalb verteilter Steuerungsarchitekturen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-3-Element `SEL` bietet dieser Baustein eine direkte Integration in die ereignisorientierte Welt von IEC 61499. Während der klassische `SEL`-Baustein kontinuierlich zyklisch aufgerufen werden muss und diskrete Verdrahtungen erfordert, arbeitet `AB_BYTE_AX_SEL_AB` rein ereignisbasiert und nutzt das vorteilhafte Adapterkonzept zur Kapselung von Signalwegen.

---

## Fazit

Der `AB_BYTE_AX_SEL_AB`-Baustein ist eine robuste, wiederverwendbare und gut strukturierte Lösung zur binären Signalauswahl von Byte-Werten. Durch die konsequente Nutzung von Adaptern fügt er sich perfekt in moderne, serviceorientierte Steuerungsanwendungen ein und trägt zur Übersichtlichkeit von 4diac-Anwendungsprogrammen bei.
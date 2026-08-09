# AX_AX_SEL_AX

<!-- Bild des FB falls vorhanden (Platzhalter) -->

![AX_AX_SEL_AX](./AX_AX_SEL_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_AX_SEL_AX` dient der binären Auswahl (Selektion) zwischen zwei booleschen Signalen, die über standardisierte Adapter übertragen werden. Er stellt eine IEC 61499-konforme Kapselung der klassischen IEC 61131-3 `SEL`-Funktion dar. Durch die Verwendung von Adaptern werden sowohl die Datenwerte als auch die dazugehörigen Ereignisse gebündelt übertragen, was den Verdrahtungsaufwand im Control-Application-Design erheblich reduziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisausgabe wird vollständig über die Adapter abgewickelt.*

### **Daten-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Eingänge.*

### **Daten-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten Daten-Ausgänge.*

### **Adapter**

#### **Sockets (Eingang-Schnittstellen)**

* **IN0** (Typ: `adapter::types::unidirectional::AX`):
  Auswählbarer Eingangsadapter 0. Der hier anliegende Wert wird an den Ausgang durchgereicht, wenn das Auswahlsignal `G` den Zustand `FALSE` aufweist.
* **IN1** (Typ: `adapter::types::unidirectional::AX`):
  Auswählbarer Eingangsadapter 1. Der hier anliegende Wert wird an den Ausgang durchgereicht, wenn das Auswahlsignal `G` den Zustand `TRUE` aufweist.
* **G** (Typ: `adapter::types::unidirectional::AX`):
  Selektor-Adapter. Bestimmt, welcher der beiden Eingänge (`IN0` oder `IN1`) auf den Ausgang geschaltet wird.

#### **Plugs (Ausgang-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AX`):
  Ausgangsadapter, der das ausgewählte Signal (`D1`) und das dazugehörige Bestätigungsereignis (`E1`) ausgibt.

---

## Funktionsweise

Intern basiert der `AX_AX_SEL_AX` auf einem ereignisgesteuerten Netzwerk, welches die Eingangssignale der Sockets verarbeitet und über den Plug ausgibt:

1. **Ereigniserfassung:** Jedes Eintreffen eines Ereignisses (`E1`) an den Adaptern `IN0`, `IN1` oder `G` triggert ein internes flanken-gesteuertes Flip-Flop (`E_D_FF` bzw. `E_D_FF_ANY`).
2. **Datenpufferung & Transport:** Die Datenwerte (`D1`) der Adapter werden über Konvertierungsbausteine des Typs `F_MOVE` (konfiguriert auf den Datentyp `BOOL`) an den zentralen Selektionsbaustein `F_SEL` weitergeleitet.
3. **Auswahllogik:**
   * Ist das Signal am Adapter `G` gleich `FALSE`, schaltet der interne Baustein `F_SEL` den Wert von `IN0` auf den Ausgang.
   * Ist das Signal am Adapter `G` gleich `TRUE`, wird der Wert von `IN1` auf den Ausgang geschaltet.
4. **Ausgabe:** Der ausgewählte Wert wird an das Flip-Flop des Ausgangs-Adapters übergeben, welches das Ereignis `OUT.E1` auslöst und den Datenpunkt `OUT.D1` aktualisiert.

---

## Technische Besonderheiten

* **Typisierung auf BOOL:** Die internen Datenkopierer (`F_MOVE`) sind fest auf den Datentyp `BOOL` parametriert. Daher ist dieser spezifische Baustein für die Auswahl von booleschen Zuständen optimiert.
* **Ereignissynchronisation:** Durch den internen Einsatz von `E_D_FF` und `E_D_FF_ANY` ist sichergestellt, dass Datenänderungen an den Eingängen sofort und ohne Zyklusverzögerung konsistent an den Ausgang übertragen werden.

---

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) handelt, wird das Verhalten direkt durch den Daten- und Ereignisfluss bestimmt:

| Zustand Selektor `G.D1` | Ausgang `OUT.D1` | Verhalten bei Ereignis an den Eingängen |
| :--- | :--- | :--- |
| `FALSE` | Wert von `IN0.D1` | Ereignisse an `IN0.E1` oder `G.E1` triggern eine Aktualisierung von `OUT.E1`. |
| `TRUE` | Wert von `IN1.D1` | Ereignisse an `IN1.E1` oder `G.E1` triggern eine Aktualisierung von `OUT.E1`. |

---

## Anwendungsszenarien

* **Betriebsartenumschaltung:** Umschalten zwischen einem Automatik- und einem Hand-Befehl (z. B. Ventil öffnen/schließen).
* **Signal-Redundanz:** Auswahl zwischen einem primären Steuersignal und einem Backup-Signal im Fehlerfall.
* **Kompakte Applikationserstellung:** Reduzierung von "Spaghetti-Code" und unübersichtlichen Linienverbindungen in 4diac-ide durch Nutzung der Adapter-Technologie.

---

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL`:** Der klassische `F_SEL`-Baustein benötigt separate Event-Verbindungen (`REQ` / `CNF`) und Datenleitungen für jeden Kanal. `AX_AX_SEL_AX` vereinfacht dies durch die Kapselung in drei Eingangs- und einen Ausgangsadapter.
* **Multiplexer (MUX):** Während ein Multiplexer zwischen einer Vielzahl von Kanälen umschalten kann, ist der `AX_AX_SEL_AX` als binärer Selektor auf exakt zwei Kanäle spezialisiert und dadurch ressourcenschonender und einfacher zu beschalten.

---

## Fazit

Der `AX_AX_SEL_AX` ist ein praktischer Hilfsbaustein für die strukturierte Anwendungsentwicklung in der IEC 61499. Er kombiniert die bewährte Selektionslogik der IEC 61131 mit den modernen Vorteilen der adapterbasierten Signalübertragung in der 4diac-ide.
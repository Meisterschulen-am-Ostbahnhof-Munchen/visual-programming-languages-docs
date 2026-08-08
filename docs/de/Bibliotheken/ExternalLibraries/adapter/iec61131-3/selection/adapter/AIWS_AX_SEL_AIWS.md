# AIWS_AX_SEL_AIWS


![AIWS_AX_SEL_AIWS](./AIWS_AX_SEL_AIWS.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AIWS_AX_SEL_AIWS` dient der binären Auswahl (Selektion) zwischen zwei unidirektionalen Adaptersignalen vom Typ `AIWS`. Die Steuerung, welcher der beiden Eingänge auf den Ausgang geschaltet wird, erfolgt über einen Steueradapter vom Typ `AX`. 

Der Baustein kapselt die klassische Selektionslogik (vergleichbar mit dem `SEL`-Standardbaustein aus der IEC 61131-3) in der ereignisgesteuerten Umgebung von IEC 61499. Dies ermöglicht eine saubere, modulare und übersichtliche Signalumschaltung direkt auf Adapterebene, ohne dass Ereignis- und Datenleitungen im übergeordneten System einzeln verdrahtet werden müssen.

## Schnittstellenstruktur

Da es sich um einen adapterbasierten Funktionsbaustein handelt, besitzt der Baustein selbst keine direkten, klassischen Ereignis- oder Daten-Ein- und Ausgänge auf seiner äußeren Hülle. Die gesamte Kommunikation wird über die Adapter-Schnittstellen abgewickelt.

### **Ereignis-Eingänge**
*Keine direkten Ereignis-Eingänge vorhanden (Ereignisse werden über die Adapter-Sockets empfangen).*

### **Ereignis-Ausgänge**
*Keine direkten Ereignis-Ausgänge vorhanden (Ereignisse werden über den Adapter-Plug gesendet).*

### **Daten-Eingänge**
*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**
*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**
* **`G`** (Typ: `adapter::types::unidirectional::AX`): 
  Der Selektor-Adapter. Das darin enthaltene Datensignal bestimmt, welcher Eingang aktiv geschaltet wird.
* **`IN0`** (Typ: `adapter::types::unidirectional::AIWS`): 
  Der erste auswählbare Eingangs-Adapter. Dieser wird an den Ausgang durchgereicht, wenn das Selektorsignal den Zustand `FALSE` (0) aufweist.
* **`IN1`** (Typ: `adapter::types::unidirectional::AIWS`): 
  Der zweite auswählbare Eingangs-Adapter. Dieser wird an den Ausgang durchgereicht, wenn das Selektorsignal den Zustand `TRUE` (1) aufweist.

#### **Plugs (Ausgangs-Adapter)**
* **`OUT`** (Typ: `adapter::types::unidirectional::AIWS`): 
  Der Ausgangs-Adapter. Er gibt die Daten und Ereignisse des jeweils selektierten Eingangs (`IN0` oder `IN1`) aus.

## Funktionsweise

Das interne Netzwerk des Funktionsbausteins realisiert die Signalweiterleitung und Ereignissynchronisation wie folgt:

1. **Ereigniserfassung und Pufferung:** 
   Sobald an einem der Sockets (`G`, `IN0` oder `IN1`) das Ereignis `E1` eintrifft, wird der dazugehörige Datenwert `D1` über ein internes ereignisgesteuertes Flipflop (`E_D_FF` für den Selektor bzw. `E_D_FF_ANY` für die Daten) zwischengespeichert.
2. **Datenkonvertierung / Zuweisung:** 
   Die Daten der Eingänge `IN0` und `IN1` werden über interne Zuweisungsglieder (`F_MOVE`) vom Typ `WSTRING` an den Auswahlbaustein übergeben.
3. **Auswahlprozess (`F_SEL`):** 
   Der interne Baustein `F_SEL` (IEC 61131-3 `SEL`) wertet den Zustand des Selektors aus dem Adapter `G` aus:
   * Ist das Signal aus `G` im Zustand `FALSE`, wird das Signal von `IN0` an den Ausgang weitergeleitet.
   * Ist das Signal aus `G` im Zustand `TRUE`, wird das Signal von `IN1` an den Ausgang weitergeleitet.
4. **Ausgabe:** 
   Das ausgewählte Signal wird über einen weiteren `F_MOVE`-Baustein und ein Ausgangs-Flipflop (`E_D_FF_ANY_OUT`) an den Datenpunkt `D1` des Ausgangs-Plugs `OUT` übergeben. Gleichzeitig wird am Ausgang das Ereignis `E1` ausgelöst, um nachfolgende Bausteine über die Datenaktualisierung zu informieren.

## Technische Besonderheiten
* **Datentyp `WSTRING`:** Die interne Verarbeitung der Adapterdaten erfolgt über `F_MOVE`-Bausteine mit dem Datentyp `WSTRING`. Dies bedeutet, dass die Nutzdaten innerhalb der `AIWS`-Adapter als Zeichenketten (Wide Strings) übertragen und umgeschaltet werden.
* **Ereignisentkopplung:** Durch die Verwendung von Flipflops (`E_D_FF`) wird sichergestellt, dass jede Änderung an den Eingängen oder am Selektor eine sofortige und konsistente Aktualisierung des Ausgangs zur Folge hat.

## Zustandsübersicht

Die logische Zuordnung des Ausgangs verhält sich in Abhängigkeit vom Selektor `G` wie folgt:

| Zustand von `G` (Selektor) | Aktiver Pfad | Datenwert an `OUT.D1` | Ereignis an `OUT.E1` |
| :--- | :--- | :--- | :--- |
| `FALSE` | `IN0` | Wert von `IN0.D1` | Wird bei Ereignissen an `IN0.E1` oder `G.E1` ausgelöst |
| `TRUE` | `IN1` | Wert von `IN1.D1` | Wird bei Ereignissen an `IN1.E1` oder `G.E1` ausgelöst |

## Anwendungsszenarien
* **Umschaltung von Analogwerten mit Status (formatiert als WSTRING):** Redundante Sensorik, bei der im Fehlerfall von Sensor 1 (`IN0`) auf einen Ersatzsensor 2 (`IN1`) umgeschaltet werden soll.
* **Dynamische Text- oder Rezepturauswahl:** Umschaltung von Konfigurations-Strings, Logmeldungen oder Sollwerten, die über Adapterstrukturen an ein HMI oder eine Steuereinheit geleitet werden.
* **Signal-Routing:** Flexibles Routing in modular aufgebauten Industrieanlagen, bei denen Datenströme je nach Betriebsmodus (z. B. Automatik vs. Handbetrieb) umgeleitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
* **Standard `SEL` (IEC 61131-3):** Der klassische `SEL`-Baustein arbeitet auf elementaren Datentypen (z.B. `INT`, `REAL`, `STRING`) und besitzt keine native Ereignissteuerung oder Adapterunterstützung. `AIWS_AX_SEL_AIWS` erweitert dieses Prinzip für die IEC 61499, indem er die Umschaltung direkt für komplexe Adaptertypen bereitstellt.
* **Multiplexer (`MUX`):** Ein klassischer Multiplexer erlaubt die Auswahl aus mehr als zwei Kanälen über einen Integer-Index. Der `AIWS_AX_SEL_AIWS` ist für die schnelle und ressourcenschonende binäre Auswahl (2 Kanäle) optimiert.

## Fazit
Der `AIWS_AX_SEL_AIWS` ist ein hochspezialisierter Hilfsbaustein für IEC 61499-Systeme (wie 4diac-ide), der komplexe Daten- und Ereignisströme zweier Adapter elegant und deterministisch umschaltet. Er trägt maßgeblich zur Reduzierung von "Spaghetti-Code" und unübersichtlicher Verdrahtung in grafischen Programmierumgebungen bei.
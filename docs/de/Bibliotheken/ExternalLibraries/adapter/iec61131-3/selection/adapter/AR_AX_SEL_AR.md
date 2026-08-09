# AR_AX_SEL_AR




![AR_AX_SEL_AR](./AR_AX_SEL_AR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AR_AX_SEL_AR` dient der binären Auswahl (Selektion) zwischen zwei analogen Eingangssignalen, die über Adapter übertragen werden. Basierend auf dem Zustand eines Auswahlsignals (Selector) wird einer der beiden Eingänge auf den Ausgang durchgeschaltet. 

Durch die konsequente Verwendung von Adaptern anstelle von klassischen diskreten Daten- und Ereignispins wird die Komplexität der Verkabelung im übergeordneten IEC 61499 Applikationsdiagramm signifikant reduziert.

## Schnittstellenstruktur

Da dieser Funktionsbaustein vollständig auf adapterbasierte Kommunikation setzt, verfügt er auf oberster Ebene über keine direkten, klassischen Event- oder Daten-Schnittstellen. Die gesamte Kommunikation wird über die deklarierten Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen empfangen).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Ereignisse werden über die Adapter-Schnittstellen gesendet).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangsschnittstellen)**

* **G** (Typ: `adapter::types::unidirectional::AX`):
  Der Auswahladapter (Selector). Das hier anliegende Signal steuert, welcher der beiden Eingänge (`IN0` oder `IN1`) an den Ausgang weitergeleitet wird.
* **IN0** (Typ: `adapter::types::unidirectional::AR`):
  Der erste auswählbare Signal-Eingang. Dieser Wert wird an den Ausgang `OUT` weitergegeben, wenn der Selektor `G` den Zustand `FALSE` (0) aufweist.
* **IN1** (Typ: `adapter::types::unidirectional::AR`):
  Der zweite auswählbare Signal-Eingang. Dieser Wert wird an den Ausgang `OUT` weitergegeben, wenn der Selektor `G` den Zustand `TRUE` (1) aufweist.

#### **Plugs (Ausgangsschnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AR`):
  Der selektierte Ausgangsadapter. Er liefert den Wert des jeweils aktiven Eingangs inklusive des dazugehörigen Aktualisierungsereignisses.

---

## Funktionsweise

Im Inneren des Funktionsbausteins `AR_AX_SEL_AR` befindet sich ein Netzwerk aus Standard-IEC-61131-3- und IEC-61499-Bausteinen, welches die Adapter-Signale verarbeitet:

1. **Ereignis- und Datenerfassung:**
   Sobald ein Ereignis `E1` an einem der Eingangs-Adapter (`IN0`, `IN1` oder `G`) eintrifft, wird dieses durch interne flankengetriggerte Flip-Flops (`E_D_FF` bzw. `E_D_FF_ANY`) abgefangen. Die entsprechenden Datenwerte (`D1`) werden zwischengespeichert.
2. **Datenkonvertierung:**
   Die Werte der analogen Eingänge werden über Konvertierungsbausteine des Typs `F_MOVE` (konfiguriert auf den Datentyp `REAL`) geleitet, um eine konsistente Datenverarbeitung zu gewährleisten.
3. **Auswahllogik (Multiplexing):**
   Der Standard-Auswahlbaustein `F_SEL` übernimmt die eigentliche Selektion:
   * Ist der Wert von `G.D1` gleich `FALSE`, wird das Signal von `IN0` an den Ausgang weitergeleitet.
   * Ist der Wert von `G.D1` gleich `TRUE`, wird das Signal von `IN1` weitergeleitet.
4. **Ausgabe:**
   Das ausgewählte Signal wird über einen weiteren `F_MOVE`-Baustein an das Ausgangs-Flip-Flop `E_D_FF_ANY_OUT` übergeben. Dieses generiert das Ausgangsereignis `E1` am Plug `OUT` und stellt den ausgewählten Wert an `OUT.D1` bereit.

---

## Technische Besonderheiten

* **Unidirektionale Adapterstruktur:** Der Baustein nutzt unidirektionale Adaptertypen (`AR` für analoge Werte, `AX` für binäre Werte), was eine klare und störungsfreie Signalrichtung im System gewährleistet.
* **Typkonsistenz:** Intern arbeitet der Baustein mit dem Datentyp `REAL` für die analogen Signale (konfiguriert über die Attribute der `F_MOVE`-Bausteine).
* **Ereignisgesteuert:** Eine Neuberechnung und Aktualisierung des Ausgangs erfolgt sofort, sobald sich entweder die Selektion `G` ändert oder neue Werte an den Eingängen `IN0` bzw. `IN1` signalisiert werden.

---

## Zustandsübersicht

Das Verhalten lässt sich über folgende einfache Logiktabelle beschreiben:

| Zustand Selektor (`G.D1`) | Wert am Ausgang (`OUT.D1`) | Triggerndes Ereignis |
| :--- | :--- | :--- |
| `FALSE` | Wert von `IN0.D1` | Ereignis an `IN0.E1` oder Änderung an `G.E1` |
| `TRUE` | Wert von `IN1.D1` | Ereignis an `IN1.E1` oder Änderung an `G.E1` |

---

## Anwendungsszenarien

* **Sensorredundanz:** Umschalten zwischen einem primären und einem sekundären analogen Sensor (z. B. Temperatursensor oder Drucksensor) bei Ausfall des Primärsensors.
* **Hand-/Automatik-Umschaltung:** Wahlweise Aufschaltung eines automatischen Regelwerts (z. B. berechnet durch einen PID-Regler) oder eines manuell vorgegebenen Sollwerts auf ein Stellglied.
* **Signalrouting:** Dynamische Pfadauswahl in komplexeren verfahrenstechnischen oder agrartechnischen Steuerungsanwendungen.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-Baustein `F_SEL` bietet `AR_AX_SEL_AR` den Vorteil der vollständigen Kapselung über Adapter. Während beim Standard-`F_SEL` Events und Daten getrennt im Netzwerk verdrahtet und synchronisiert werden müssen, reduziert `AR_AX_SEL_AR` den Verdrahtungsaufwand im übergeordneten System auf nur drei Verbindungen (zwei Eingangs-Adapter, ein Ausgangs-Adapter) plus das Selektionssignal.

---

## Fazit

Der `AR_AX_SEL_AR` ist ein äußerst nützlicher Hilfsbaustein für IEC 61499 Applikationen. Durch die Abstraktion der Daten- und Eventströme in standardisierte Adapterkanäle sorgt er für ein aufgeräumtes Applikationsdesign und vereinfacht die Implementierung von Umschalt- und Redundanzlogiken für analoge Signale.
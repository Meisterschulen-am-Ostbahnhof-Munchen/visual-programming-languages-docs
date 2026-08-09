# AQ_AX_SEL_AQ


![AQ_AX_SEL_AQ](./AQ_AX_SEL_AQ.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AQ_AX_SEL_AQ` dient der binären Auswahl (Selektion) zwischen zwei analogen oder wertbasierten Eingangssignalen, die über Adapter bereitgestellt werden. Die Steuerung, welcher der beiden Eingänge an den Ausgang durchgeschaltet wird, erfolgt über einen Selektor-Adapter. Der Baustein kapselt die klassische Auswahl-Logik und bereitet sie für die ereignisgesteuerte Ausführung in IEC 61499-Umgebungen auf.

## Schnittstellenstruktur

Der Funktionsbaustein kommuniziert ausschließlich über standardisierte Adapter-Schnittstellen. Dies vereinfacht die Modellierung im Applikationsnetzwerk, da zusammengehörige Daten- und Ereignislinien gebündelt übertragen werden.

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignisverarbeitung erfolgt implizit über die Ereignisse der angeschlossenen Eingangs-Adapter (`IN0`, `IN1`, `G`).

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten Ereignis-Ausgänge. Die Weiterleitung von Ereignissen erfolgt über den Ausgangs-Adapter (`OUT`).

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge auf der Bausteinoberfläche vorhanden. Die Datenübergabe erfolgt gekapselt über die Sockets.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenbereitstellung erfolgt gekapselt über den Plug.

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

* **G** (Typ: `adapter::types::unidirectional::AX`):
  * **Beschreibung**: Selektor (Auswahlsignal).
  * **Daten**: `D1` (Zustand des Selektors).
  * **Ereignis**: `E1` (Trigger bei Wertänderung des Selektors).
* **IN0** (Typ: `adapter::types::unidirectional::AQ`):
  * **Beschreibung**: Erster wählbarer Eingangskanal (wird bei `G = FALSE` gewählt).
  * **Daten**: `D1` (Eingangswert).
  * **Ereignis**: `E1` (Trigger bei Wertänderung an IN0).
* **IN1** (Typ: `adapter::types::unidirectional::AQ`):
  * **Beschreibung**: Zweiter wählbarer Eingangskanal (wird bei `G = TRUE` gewählt).
  * **Daten**: `D1` (Eingangswert).
  * **Ereignis**: `E1` (Trigger bei Wertänderung an IN1).

#### **Plugs (Ausgangs-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AQ`):
  * **Beschreibung**: Der ausgewählte Ausgangskanal.
  * **Daten**: `D1` (Ausgangswert des selektierten Eingangs).
  * **Ereignis**: `E1` (Ausgangs-Ereignis zur Signalisierung eines neuen gültigen Wertes).

## Funktionsweise

Der Baustein ist intern als FB-Netzwerk realisiert und arbeitet nach folgendem Ablauf:

1. **Ereigniserfassung**: Sobald ein Ereignis `E1` an einem der Eingänge (`IN0`, `IN1`) oder dem Selektor (`G`) eintrifft, wird dieses über flanken- bzw. wertgesteuerte Hilfsbausteine (`E_D_FF` und `E_D_FF_ANY`) abgefangen und synchronisiert.
2. **Datenpufferung**: Die aktuellen Werte der Adapter-Eingänge werden mittels `F_MOVE`-Funktionsbausteinen im internen Netzwerk zwischengespeichert und typkonform aufbereitet.
3. **Auswahl-Logik (Selection)**: Der interne Kernbaustein `F_SEL` (basierend auf der standardisierten Auswahlfunktion nach IEC 61131-3) wertet den Zustand des Selektors aus:
   * Ist `G.D1` auf `FALSE` gesetzt, wird der Wert von `IN0` durchgeschaltet.
   * Ist `G.D1` auf `TRUE` gesetzt, wird der Wert von `IN1` durchgeschaltet.
4. **Ausgabe**: Der selektierte Wert wird an den Ausgangs-Plug `OUT.D1` übergeben. Gleichzeitig wird das Ausgangsereignis `OUT.E1` gefeuert, um nachfolgende Programmteile im Steuerungsnetzwerk über die Wertänderung zu informieren.

## Technische Besonderheiten

* **Ereignis-Daten-Konsistenz**: Durch die Verwendung von internen D-Flipflops wird sichergestellt, dass die Datenwerte zum exakten Zeitpunkt des Eintreffens des entsprechenden Änderungsereignisses gelesen und verarbeitet werden.
* **Typisierung**: Der Baustein nutzt intern `F_MOVE` mit dem Datentyp `BYTE` zur Kapselung und Zuweisung der Adapterdaten. Das bedeutet, dass die genutzten `AQ`-Schnittstellen binär- bzw. bytekompatible Datenstrukturen übertragen.

## Zustandsübersicht

Da es sich bei `AQ_AX_SEL_AQ` um einen rein daten- und ereignisgesteuerten Kombinationsbaustein ohne eigenen internen Zustandsautomaten (ECC) handelt, lässt sich das Verhalten über folgende logische Tabelle beschreiben:

| Selektor (`G.D1`) | Wert `IN0.D1` | Wert `IN1.D1` | Ausgang (`OUT.D1`) | Verhalten des Ausgangsereignisses (`OUT.E1`) |
| :---: | :---: | :---: | :---: | :--- |
| **FALSE** | `Wert_A` | `Wert_B` | **`Wert_A`** | Wird gefeuert, sobald ein Ereignis an `IN0.E1`, `IN1.E1` oder `G.E1` auftritt. |
| **TRUE** | `Wert_A` | `Wert_B` | **`Wert_B`** | Wird gefeuert, sobald ein Ereignis an `IN0.E1`, `IN1.E1` oder `G.E1` auftritt. |

## Anwendungsszenarien

* **Sensor-Redundanz / Umschaltung**: Automatisches oder manuelles Umschalten zwischen einem Primärsensor (`IN0`) und einem Sekundär-/Backupsensor (`IN1`) im Fehlerfall über das Steuersignal `G`.
* **Hand-/Automatikbetrieb**: Auswahl von Sollwerten für Aktoren. Im Automatikmodus (`G = TRUE`) wird der berechnete Reglerwert (`IN1`) verwendet, im Handbetrieb (`G = FALSE`) ein vordefinierter Festwert oder ein manuell vorgegebener Parameter (`IN0`).
* **Rezepturgesteuerte Parametrierung**: Dynamische Umschaltung von Prozessgrenzwerten während des laufenden Betriebs.

## Vergleich mit ähnlichen Bausteinen

* **Standard `SEL` (IEC 61131-3)**: Der klassische `SEL`-Baustein besitzt keine Ereignissteuerung und reagiert rein zyklisch auf anstehende Daten. `AQ_AX_SEL_AQ` erweitert diese Funktionalität um das ereignisbasierte Paradigma von IEC 61499.
* **Klassische Multiplexer (MUX)**: Während ein Multiplexer meist aus einer Vielzahl von Eingängen wählt, beschränkt sich dieser Baustein gezielt auf eine effiziente 1-aus-2-Auswahl (binäre Selektion), was den Parametrierungs- und Verdrahtungsaufwand minimiert.

## Fazit

Der `AQ_AX_SEL_AQ` ist ein nützlicher Infrastruktur-Baustein für modulare 4diac-Anwendungen. Durch die vollständige Kapselung der Signale in Adapter-Verbindungen trägt er maßgeblich zur Übersichtlichkeit im Application-Window bei und sorgt für eine robuste, ereignisgesteuerte Signalweiterleitung.
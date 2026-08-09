# AW_AX_SEL_AW


![AW_AX_SEL_AW](./AW_AX_SEL_AW.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AW_AX_SEL_AW` dient der binären Auswahl (Selektion) zwischen zwei analogen oder wortbasierten Eingangssignalen über einen binären Selektor. Der Baustein ist speziell für die Verwendung mit adapterbasierten Schnittstellen in 4diac-ide (IEC 61499) konzipiert. Er kapselt die klassische Selektionslogik (`SEL`) und stellt diese über unidirektionale Adapter für `WORD`-Daten (`AW`) und binäre Steuersignale (`AX`) zur Verfügung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Es sind keine direkten Ereignis-Eingänge auf Bausteinebene vorhanden. Die Ereignisverarbeitung erfolgt vollständig gekapselt über die Adapter-Schnittstellen.

### **Ereignis-Ausgänge**

Es sind keine direkten Ereignis-Ausgänge auf Bausteinebene vorhanden. Die Ereignisausgabe erfolgt vollständig gekapselt über die Adapter-Schnittstellen.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge auf Bausteinebene vorhanden.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge auf Bausteinebene vorhanden.

### **Adapter**

#### **Sockets (Eingang-Schnittstellen)**

* **G** (Typ: `adapter::types::unidirectional::AX`): 
  * Selektions-Eingang (Selector). Bestimmt, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird.
* **IN0** (Typ: `adapter::types::unidirectional::AW`): 
  * Erster auswählbarer Eingangskanal (wird selektiert, wenn `G` den Zustand `FALSE` bzw. `0` hat).
* **IN1** (Typ: `adapter::types::unidirectional::AW`): 
  * Zweiter auswählbarer Eingangskanal (wird selektiert, wenn `G` den Zustand `TRUE` bzw. `1` hat).

#### **Plugs (Ausgang-Schnittstellen)**

* **OUT** (Typ: `adapter::types::unidirectional::AW`): 
  * Selektierter Ausgangskanal, der den Wert des ausgewählten Eingangs führt.

## Funktionsweise

Der Baustein basiert intern auf einem Netzwerk aus Standard-Funktionsbausteinen, um die ereignisgesteuerte Selektion zu realisieren:

1. **Signalpufferung:** Die über die Adapter `IN0`, `IN1` und `G` eingehenden Ereignisse (`E1`) und Daten (`D1`) werden über D-Flipflops (`E_D_FF` bzw. `E_D_FF_ANY`) zwischengespeichert. Dies stellt sicher, dass die Daten konsistent zur Verfügung stehen, sobald ein Ereignis eintrifft.
2. **Datenweiterleitung:** Die Daten aus den WORD-Adaptern werden über `F_MOVE`-Bausteine (konfiguriert auf den Datentyp `WORD`) an den zentralen Auswahlbaustein übergeben.
3. **Auswahllogik (F_SEL):** Der Baustein `F_SEL` (Standard-Auswahlfunktion) wertet den Zustand des Selektors `G` aus:
   * Ist `G.Q` = `FALSE`, wird der Wert von `IN0` an den Ausgang weitergegeben.
   * Ist `G.Q` = `TRUE`, wird der Wert von `IN1` an den Ausgang weitergegeben.
4. **Ausgabe-Triggerung:** Jede Änderung an den Eingängen oder dem Selektor triggert über die Event-Verbindungen den Durchlauf. Der selektierte Wert wird über den Ausgangs-Zwischespeicher `E_D_FF_ANY_OUT` an den Ausgangs-Plug `OUT` übergeben und das zugehörige Ausgangsereignis `OUT.E1` ausgelöst.

## Technische Besonderheiten

* **Adapter-Kapselung:** Durch die ausschließliche Verwendung von Adaptern wird der Verkabelungsaufwand im übergeordneten System drastisch reduziert, da Daten- und Eventleitungen in einem einzigen Adapterkanal gebündelt sind.
* **Unidirektionale Datenübertragung:** Die verwendeten Adaptertypen `AW` (Adapter Word) und `AX` (Adapter Bit/Boolean) sind unidirektional aufgebaut, was eine klare Signalflussrichtung definiert.
* **Datentyp:** Die interne Verarbeitung der analogen Werte ist fest auf den Datentyp `WORD` ausgelegt.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite FB) ohne eigene State-Machine (ECC) handelt, wird das Verhalten direkt durch den Daten- und Ereignisfluss der internen Komponenten bestimmt:

* **Ereignis auf G.E1:** Der Selektorwert wird aktualisiert. Die Auswahllogik schaltet entsprechend um und aktualisiert den Ausgang `OUT`.
* **Ereignis auf IN0.E1 / IN1.E1:** Die Eingangsdaten werden aktualisiert. Wenn der geänderte Eingang dem aktuell über `G` selektierten Kanal entspricht, wird der neue Wert sofort an `OUT` weitergeleitet und das Ereignis `OUT.E1` getriggert.

## Anwendungsszenarien

* **Umschaltung von Sollwerten:** Wahlweise Vorgabe eines Sollwerts (z. B. Drehzahl, Druck, Temperatur als `WORD` codiert) aus einem Automatikprogramm (`IN1`) oder einer manuellen Bedienung (`IN0`).
* **Signal-Routing:** Dynamische Umleitung von Datenströmen innerhalb modularer Steuerungsarchitekturen.
* **Redundante Sensorik:** Umschalten zwischen einem Hauptsensor und einem Ersatzsensor bei Signalfehlern.

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL` (IEC 61131-3):** Der Standard-Auswahlbaustein arbeitet mit direkten Elementardatentypen (z.B. WORD, BOOL) und besitzt keine integrierte Event-Steuerung für IEC 61499. `AW_AX_SEL_AW` erweitert diese Funktionalität um die Event-Kopplung und verpackt sie in standardisierte Adapter.
* **Multiplexer (MUX):** Ein Multiplexer erlaubt die Auswahl aus mehr als zwei Kanälen über einen ganzzahligen Index (INT). `AW_AX_SEL_AW` ist hingegen für die schnelle, binäre Auswahl (2 Kanäle via BOOL/AX) optimiert.

## Fazit

Der `AW_AX_SEL_AW` ist ein robuster und wiederverwendbarer Hilfsbaustein für die strukturierte Programmierung in IEC 61499. Er eignet sich hervorragend für Applikationen, die auf eine saubere Schnittstellenarchitektur mittels Adaptern setzen, und vereinfacht die Signalumschaltung im industriellen Umfeld.
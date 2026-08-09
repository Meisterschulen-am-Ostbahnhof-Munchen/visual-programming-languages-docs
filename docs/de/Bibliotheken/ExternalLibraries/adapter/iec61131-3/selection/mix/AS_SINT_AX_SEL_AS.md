# AS_SINT_AX_SEL_AS


![AS_SINT_AX_SEL_AS](./AS_SINT_AX_SEL_AS.svg)

*(Kein Bild vorhanden)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AS_SINT_AX_SEL_AS` dient als binärer Selektor (Auswahlschalter) für Signale des Datentyps `SINT` (Short Integer) unter Verwendung von standardisierten Adaptern. Er ermöglicht es, basierend auf dem Zustand eines Auswahlsignals (`G`), dynamisch zwischen einem über einen Adapter eingespeisten Eingangswert (`IN0`) und einem direkt am Funktionsbaustein anliegenden Datenwert (`IN1`) umzuschalten. Der jeweils ausgewählte Wert wird an einen Ausgangs-Adapter (`OUT`) weitergeleitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI1**: Triggert die Übernahme und Verarbeitung des lokal anliegenden Daten-Eingangs `IN1`.

### **Ereignis-Ausgänge**

* *Keine direkten Ereignis-Ausgänge auf Bausteinebene vorhanden. Die Ereignisausgabe erfolgt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

* **IN1** (SINT): Der direkt am Baustein anliegende, selektierbare Eingangswert.

### **Daten-Ausgänge**

* *Keine direkten Daten-Ausgänge auf Bausteinebene vorhanden. Die Datenausgabe erfolgt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

* **Sockets (Eingangs-Schnittstellen):**
  * **IN0** (Typ: `adapter::types::unidirectional::AS`): Selektierbarer Eingangsadapter, der einen `SINT`-Wert führt.
  * **G** (Typ: `adapter::types::unidirectional::AX`): Selektor-Adapter (Steuersignal für die Auswahl).
* **Plugs (Ausgangs-Schnittstellen):**
  * **OUT** (Typ: `adapter::types::unidirectional::AS`): Adapter zur Ausgabe des selektierten `SINT`-Wertes.

## Funktionsweise

Im Inneren des Funktionsbausteins wird ein Netzwerk aus IEC 61131- und IEC 61499-Standardbausteinen verwendet, um die flankengetriggerte Auswahl zu realisieren:

1. **Ereignis- und Datenpufferung:** 
   Sowohl die Signale der Eingangs-Adapter (`IN0`, `G`) als auch der lokale Eingang (`IN1` gekoppelt an `EI1`) werden über D-Flipflops (`E_D_FF_ANY` bzw. `E_D_FF`) gepuffert. Dies stellt sicher, dass Datenwerte synchron mit ihren jeweiligen Ereignissen erfasst werden.
2. **Datenkonvertierung/Weiterleitung:**
   Die gepufferten Werte für `IN0` und `IN1` werden über `F_MOVE`-Bausteine an den zentralen Auswahlbaustein `F_SEL` übergeben.
3. **Auswahllogik (F_SEL):**
   * Ist das über den Adapter `G` empfangene Auswahlsignal **FALSE** (0), wird der Wert von `IN0` an den Ausgang weitergegeben.
   * Ist das Auswahlsignal **TRUE** (1), wird der Wert von `IN1` weitergegeben.
4. **Ausgabe:**
   Der ausgewählte Wert wird an das Flipflop `E_D_FF_ANY_OUT` übergeben, welches schließlich das Ereignis `E1` und den neuen Datenwert `D1` am Ausgangs-Adapter `OUT` bereitstellt.

## Technische Besonderheiten

* **Adapterbasierte Architektur:** Durch die Verwendung von unidirektionalen Adaptern (`AS` und `AX`) wird die Verkabelung im übergeordneten System stark vereinfacht.
* **Ereignisgesteuert:** Der Baustein reagiert sofort auf Wertänderungen an einem der Eingänge (`IN0`, `IN1` oder `G`) und berechnet den Ausgangswert neu.
* **Sichere Zustandsspeicherung:** Die internen Flipflops gewährleisten, dass auch bei asynchron eintreffenden Ereignissen immer die aktuellsten Daten konsistent verarbeitet werden.

## Zustandsübersicht

Die Selektion verhält sich wie folgt:

| Zustand Selektor `G` | Ausgewählter Eingang | Signal am Ausgang `OUT` |
|:---:|:---:|:---:|
| **FALSE** | `IN0` (über Adapter) | Wert von `IN0` |
| **TRUE** | `IN1` (lokaler Eingang) | Wert von `IN1` |

## Anwendungsszenarien

* **Umschaltung zwischen Automatik- und Handbetrieb:** Einlesen eines Sollwerts über ein Bussystem (`IN0`) im Automatikbetrieb oder über ein lokales HMI (`IN1`) im Handbetrieb, gesteuert durch das Signal `G`.
* **Signal-Bypass/Rückfallebene:** Temporäres Aufschalten eines Festwerts oder sicheren Ersatzwerts (`IN1`) auf einen Signalpfad, falls der Primärsensor (`IN0`) eine Störung meldet.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-Baustein `SEL` arbeitet dieser Funktionsbaustein nicht auf reinen Datenebenen, sondern ist vollständig in die ereignisgesteuerte Architektur von IEC 61499 integriert. Er kapselt die notwendigen Event-to-Data-Konvertierungen und eignet sich im Gegensatz zum einfachen `SEL` direkt für die Kopplung mit Adapterverbindungen.

## Fazit

`AS_SINT_AX_SEL_AS` ist ein robuster und wiederverwendbarer Signal-Umschalter für ereignisgesteuerte Steuerungsanwendungen. Er verbindet die Flexibilität lokaler Variablen mit der strukturellen Eleganz von Adapter-Schnittstellen.
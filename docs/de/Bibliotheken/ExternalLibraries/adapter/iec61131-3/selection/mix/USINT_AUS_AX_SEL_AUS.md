# USINT_AUS_AX_SEL_AUS


![USINT_AUS_AX_SEL_AUS](./USINT_AUS_AX_SEL_AUS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `USINT_AUS_AX_SEL_AUS` dient der binären Auswahl (Selektion) zwischen zwei Eingangssignalen des Datentyps `USINT` (Unsigned Short Integer). Die Steuerung, welcher der beiden Werte an den Ausgang weitergegeben wird, erfolgt über ein Selektionssignal eines Adapters. Der Baustein nutzt intern ereignisgesteuerte Mechanismen, um Ressourcen zu schonen und Daten nur bei tatsächlichen Änderungen zu verarbeiten. Durch die Verwendung von Adaptern wird die Verdrahtung innerhalb der 4diac-IDE erheblich vereinfacht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **EI0** | Event | Aktualisiert den Wert am lokalen Dateneingang `IN0`. |

### **Ereignis-Ausgänge**

*Der Funktionsbaustein besitzt keine direkten Standard-Ereignisausgänge. Die Ereignisweiterleitung erfolgt vollständig über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | USINT | Erster auswählbarer Datenkanal (lokaler Eingang). |

### **Daten-Ausgänge**

*Der Funktionsbaustein besitzt keine direkten Standard-Datenausgänge. Die Datenweiterleitung erfolgt vollständig über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug | `adapter::types::unidirectional::AUS` | Der ausgewählte Ausgangskanal (enthält das Ereignis `E1` und die Daten `D1`). |
| **IN1** | Socket | `adapter::types::unidirectional::AUS` | Zweiter auswählbarer Datenkanal über Adapter (enthält das Ereignis `E1` und die Daten `D1`). |
| **G** | Socket | `adapter::types::unidirectional::AX` | Selektor-Eingang (Steuersignal zur Auswahl zwischen `IN0` und `IN1`). |

---

## Funktionsweise

Der Baustein basiert intern auf einem Netz aus Standard-Funktionsbausteinen, die eine ereignisgesteuerte Auswahl realisieren:

1. **Datenspeicherung und Synchronisation**: 
   * Sobald am Ereignis-Eingang `EI0` ein Signal ankommt, wird der Wert von `IN0` über ein ereignisgesteuertes D-Flip-Flop (`E_D_FF_ANY_IN0`) und einen Kopierbaustein (`F_MOVE_IN0`) zwischengespeichert.
   * Analoge Abläufe finden für den Adapter-Eingang `IN1` (über `E_D_FF_ANY_IN1` / `F_MOVE_IN1` bei Eintreffen von `IN1.E1`) und den Selektor `G` (über `E_D_FF_G` bei Eintreffen von `G.E1`) statt.

2. **Auswahllogik**:
   * Der eigentliche Auswahlprozess wird durch den Standard-Selektionsbaustein `F_SEL` durchgeführt.
   * Liegt am Selektor-Eingang `G` der Zustand `FALSE` (0) an, wird der Wert von `IN0` ausgewählt.
   * Liegt am Selektor-Eingang `G` der Zustand `TRUE` (1) an, wird der Wert von `IN1` ausgewählt.

3. **Ausgabe**:
   * Das Ergebnis der Auswahl wird an den Ausgangs-Adapter `OUT` übergeben. 
   * Jede Änderung des ausgewählten Wertes triggert das Ausgangsereignis `OUT.E1` und stellt den neuen `USINT`-Wert an `OUT.D1` zur Verfügung.

---

## Technische Besonderheiten

* **Mischbetrieb**: Der Baustein erlaubt die saubere Kopplung zwischen einem klassischen Daten-Eingang (`IN0`) und einem adapterbasierten Eingang (`IN1`).
* **Ereignisgesteuertes Design**: Es wird keine kontinuierliche zyklische Berechnung durchgeführt. Die Verarbeitung erfolgt ausschließlich dann, wenn sich Eingangsdaten ändern oder ein Selektionsereignis eintrifft.
* **Kompakte Architektur**: Durch die Kapselung der D-Flip-Flops und der `F_SEL`-Logik im FB-Netzwerk wird die Komplexität vor dem Anwender verborgen.

---

## Zustandsübersicht

| Zustand Selektor (`G`) | Triggerndes Ereignis | Aktiver Kanal | Ausgang (`OUT.D1`) | Ausgangsereignis (`OUT.E1`) |
| :---: | :---: | :---: | :---: | :---: |
| `FALSE` | `EI0` oder `G.E1` | `IN0` | Wert von `IN0` | Ja |
| `TRUE` | `IN1.E1` oder `G.E1` | `IN1` | Wert von `IN1.D1` | Ja |

---

## Anwendungsszenarien

* **Umschaltung Betriebsmodi**: Wechseln eines Parameters (z. B. eine ID oder ein Modus-Wert im Bereich 0–255) zwischen einem festen Standardwert (`IN0`) und einem dynamisch über einen Bus-Adapter empfangenen Wert (`IN1`).
* **Hand-/Automatik-Umschaltung**: Vorgabe von Sollwerten für Aktoren, bei denen im Handbetrieb ein lokaler Wert (`IN0`) und im Automatikbetrieb ein übergeordneter Adapterwert (`IN1`) aktiv geschaltet wird.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem Standard-`F_SEL`-Baustein der IEC 61131-3 bietet dieser Baustein eine direkte Integration von IEC 61499-Adaptern. Während bei einem Standard-`F_SEL` die Ereignisbehandlung und die Adapterkonvertierung manuell extern aufgebaut werden müssten, erledigt `USINT_AUS_AX_SEL_AUS` diese Aufgaben direkt intern. Dies spart Platz im Applikationsdiagramm und minimiert Fehler bei der Event-Verkettung.

---

## Fazit

Der `USINT_AUS_AX_SEL_AUS`-Baustein ist eine effiziente, robuste und installationsfertige Lösung für die Signalumschaltung im `USINT`-Bereich. Durch die konsequente Nutzung von Adaptern fügt er sich ideal in moderne, serviceorientierte und modulare Architekturen innerhalb der 4diac-Umgebung ein.
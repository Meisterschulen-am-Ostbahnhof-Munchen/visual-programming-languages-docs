# AX_SEL_USINT




![AX_SEL_USINT](./AX_SEL_USINT.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AX_SEL_USINT` dient der binären Auswahl (Multiplexing) zwischen zwei Eingangswerten des Datentyps `USINT` (Unsigned Short Integer). Die Steuerung, welcher der beiden Eingänge an den Ausgang durchgeschaltet wird, erfolgt über einen spezialisierten Kopplungs-Adapter (`G`). Der Baustein basiert auf den Auswahl-Konzepten der Normen IEC 61131-3 (SEL-Funktion) und ist für den Einsatz in verteilten Steuerungssystemen nach IEC 61499 optimiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI0** | Aktualisiert und übernimmt den Wert am Eingang `IN0` | `IN0` |
| **EI1** | Aktualisiert und übernimmt den Wert am Eingang `IN1` | `IN1` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **CNF** | Bestätigungsereignis. Signalisiert, dass ein neuer ausgewählter Wert am Ausgang bereitsteht. | `OUT` |

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | USINT | Erster auswählbarer Eingangswert (wird selektiert, wenn der Selektor `FALSE` ist). |
| **IN1** | USINT | Zweiter auswählbarer Eingangswert (wird selektiert, wenn der Selektor `TRUE` ist). |

### **Daten-Ausgänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **OUT** | USINT | Der aktuell selektierte Ausgangswert. |

### **Adapter**

| Steckplatz (Socket) | Adaptertyp | Beschreibung |
| :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Unidirektionaler Adapter, der das Selektionssignal (`G.D1`) und das zugehörige Trigger-Ereignis (`G.E1`) liefert. |

---

## Funktionsweise

Der Baustein `AX_SEL_USINT` kapselt ein internes Netzwerk aus Event- und Auswahlbausteinen:

1. **Datenerfassung:** Die analogen Eingangswerte `IN0` und `IN1` werden bei Eintreffen der jeweiligen Ereignisse `EI0` bzw. `EI1` über flankengetriggerte Flip-Flops (`E_D_FF_ANY`) zwischengespeichert.
2. **Selektion über Adapter:** Das Steuersignal für die Auswahl wird über den Adapter `G` eingespeist. Sobald am Adapter das Ereignis `G.E1` anliegt, übernimmt ein internes D-Flip-Flop den Zustand des Datenkanals `G.D1`.
3. **Auswahlprozess:** Der interne Kernbaustein `F_SEL` schaltet basierend auf dem Zustand des Selektors durch:
   - Ist der Zustand von `G` **FALSE** (0), wird der Wert von `IN0` an den Ausgang `OUT` weitergeleitet.
   - Ist der Zustand von `G` **TRUE** (1), wird der Wert von `IN1` an den Ausgang `OUT` weitergeleitet.
4. **Ereignisgenerierung:** Ein Ausgangsereignis am Ausgang `CNF` wird primär dann erzeugt, wenn sich der Zustand des Selektors `G` ändert oder sich der resultierende Ausgangswert modifiziert.

---

## Technische Besonderheiten

- **Ereignisfilterung:** Durch die interne Verwendung von `E_D_FF_ANY`-Bausteinen am Ausgang wird sichergestellt, dass das Bestätigungsereignis `CNF` effizient gesteuert wird. Ein Ausgangsereignis wird gezielt generiert, wenn sich der Zustand des Selektions-Adapters `G` ändert.
- **Adapter-Kopplung:** Die Auslagerung des Selektionssignals in einen Adapter reduziert den Verdrahtungsaufwand im übergeordneten Funktionsplan (FB-Netzwerk) drastisch und erhöht die Modularität.

---

## Zustandsübersicht

| Zustand Selektor (G.D1) | Aktivierter Eingang | Ausgangswert (OUT) |
| :---: | :---: | :---: |
| **FALSE** | IN0 | Wert von `IN0` |
| **TRUE** | IN1 | Wert von `IN1` |

---

## Anwendungsszenarien

- **Sollwert-Umschaltung:** Dynamisches Wechseln zwischen zwei verschiedenen Zielwerten (z. B. Standby-Wert vs. Betriebswert) in einer Maschinensteuerung.
- **Hand-/Automatik-Umschaltung:** Signalrouting, bei dem im Handbetrieb ein manuell vorgegebener `USINT`-Wert und im Automatikbetrieb ein berechneter Wert einer Steuerung übergeben wird.
- **Rezeptursteuerung:** Auswahl zwischen zwei fest hinterlegten Konfigurationsparametern über ein zentrales Steuersignal.

---

## Vergleich mit ähnlichen Bausteinen

- **Standard-SEL-Baustein (IEC 61131-3):** Der klassische `SEL`-Baustein benötigt diskrete Hardware-Pins für das Selektionssignal und besitzt keine integrierte Ereignissteuerung für verteilte Systeme. `AX_SEL_USINT` löst dies elegant über den Adapter `G` und IEC 61499 Event-Verbindungen.
- **AX_SEL-Varianten für andere Datentypen:** Es existieren analoge Bausteine für Typen wie `INT` oder `REAL`. `AX_SEL_USINT` ist speziell auf den vorzeichenlosen 8-Bit-Datentyp (`USINT`) optimiert, um Speicherplatz und Datentypkonsistenz im Netzwerk zu wahren.

---

## Fazit

Der `AX_SEL_USINT` ist ein zuverlässiger und hochgradig modularer Hilfsbaustein für die Signalflusssteuerung in IEC 61499-Anwendungen. Durch die Nutzung des `AX`-Adapters gliedert er sich nahtlos in moderne, ereignisgesteuerte Steuerungsarchitekturen ein und sorgt für eine saubere Trennung von Steuerungslogik und Datenpfaden.
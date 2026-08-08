# LINT_ALI_AX_SEL_ALI


![LINT_ALI_AX_SEL_ALI](./LINT_ALI_AX_SEL_ALI.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `LINT_ALI_AX_SEL_ALI` dient der binären Auswahl (Selektion) zwischen zwei Eingangswerten des Datentyps `LINT` (64-Bit Ganzzahl) und stellt das Ergebnis an einem Adapter-Ausgang zur Verfügung. 

Die Besonderheit dieses Bausteins liegt in der hybriden Schnittstellenführung: Er ermöglicht die Auswahl zwischen einem direkt anliegenden Datenwert (`IN0`) und einem über einen Adapter eingespeisten Datenwert (`IN1`). Die Steuerung der Auswahl erfolgt ebenfalls über einen Adapter (`G`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI0** | Setzt den Wert von `IN0` und triggert die interne Berechnung. | `IN0` |

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge auf der Hauptschnittstelle. Die Ereignisweiterleitung erfolgt gekoppelt über die Adapter (siehe Abschnitt Adapter).*

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **IN0** | LINT | Erster auswählbarer Eingangswert (wird gewählt, wenn der Selektor `G` den Zustand `FALSE` hat). |

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge auf der Hauptschnittstelle. Die Datenausgabe erfolgt über den Adapter-Plug `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung (Plug/Socket) | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::ALI` | Plug (Stecker) | Der ausgewählte Ausgangswert (Typ `LINT`), verpackt in einer unidirektionalen Adapterschnittstelle. |
| **IN1** | `adapter::types::unidirectional::ALI` | Socket (Buchse) | Zweiter auswählbarer Eingangswert (Typ `LINT`), der über einen Adapter eingespeist wird (wird gewählt, wenn `G` den Zustand `TRUE` hat). |
| **G** | `adapter::types::unidirectional::AX` | Socket (Buchse) | Selektor-Eingang (Boolean), der über einen Adapter empfangen wird. |

---

## Funktionsweise

Der Baustein basiert intern auf dem IEC 61131-3 Standard-Auswahl-Algorithmus (`F_SEL`). Die Steuerung erfolgt flanken- bzw. ereignisgesteuert über D-Flipflops (`E_D_FF` und `E_D_FF_ANY`), um eine konsistente Datenübernahme bei Eintreffen von Ereignissen zu garantieren.

1. **Ereignisverarbeitung**:
   * Ein Ereignis an `EI0` aktualisiert den internen Wert für `IN0`.
   * Ein Ereignis am Adapter `IN1` (`IN1.E1`) aktualisiert den internen Wert für `IN1`.
   * Ein Ereignis am Selektor-Adapter `G` (`G.E1`) aktualisiert das Selektionssignal.
2. **Auswahllogik**:
   * Liegt am Selektor-Adapter `G.D1` der Wert `FALSE` an, wird der Wert von `IN0` an den Ausgang `OUT.D1` weitergegeben.
   * Liegt am Selektor-Adapter `G.D1` der Wert `TRUE` an, wird der Wert von `IN1.D1` an den Ausgang `OUT.D1` weitergegeben.
3. **Ausgabe**:
   * Nach jeder internen Wertänderung oder Auswahlaktualisierung wird das Ausgangsereignis `OUT.E1` des Ausgangs-Adapters getriggert, um nachfolgende Programmteile über die Datenänderung zu informieren.

---

## Technische Besonderheiten

* **Datensicherheit durch Event-Kopplung**: Durch die Zwischenschaltung von `E_D_FF` (D-Flipflop) Bausteinen wird sichergestellt, dass Datenwerte nur dann übernommen werden, wenn das dazugehörige Ereignis eintrifft. Dies verhindert "Glitches" oder das Verarbeiten von unvollständigen Datenpaketen.
* **Reduzierter Verdrahtungsaufwand**: Die Verwendung von Adaptern (`ALI` und `AX`) fasst Daten und Ereignisse in logische Kanäle zusammen. Dies sorgt für eine übersichtlichere Struktur im 4diac-Anwendungsnetzwerk.

---

## Zustandsübersicht

Da es sich um einen zusammengesetzten Funktionsbaustein (Composite/Network FB) handelt, gibt es keine klassische Zustandsmaschine (Execution Control Chart - ECC). Das Verhalten lässt sich jedoch über folgende Funktionstabelle beschreiben:

| Zustand Selektor (`G.D1`) | Eingang `IN0` | Eingang `IN1.D1` | Ausgang (`OUT.D1`) | Getriggertes Ereignis |
| :---: | :---: | :---: | :---: | :---: |
| **FALSE** | `Wert A` | `Wert B` | **Wert A** | `OUT.E1` |
| **TRUE** | `Wert A` | `Wert B` | **Wert B** | `OUT.E1` |

---

## Anwendungsszenarien

* **Sollwert-Umschaltung**: Umschalten zwischen einem lokal fest hinterlegten Standardwert (`IN0` als statischer Parameter im FB) und einem dynamisch über das Netzwerk oder ein HMI kommenden Alternativwert (`IN1` via Adapter).
* **Betriebsartenwahl**: Auswahl unterschiedlicher Zeit- oder Zählvorgaben (repräsentiert als 64-Bit-Ganzzahl `LINT`) je nach Zustand einer übergeordneten Steuerung (z.B. Automatik- vs. Handbetrieb).

---

## Vergleich mit ähnlichen Bausteinen

* **Klassischer `F_SEL`**: Der Standard-Auswahlbaustein besitzt keine Adapter-Unterstützung und erfordert die direkte Verdrahtung aller Daten- und Ereignisleitungen. `LINT_ALI_AX_SEL_ALI` kapselt diese Logik und ist speziell für den Datentyp `LINT` optimiert.
* **Andere Typ-Selektoren**: Es existieren analoge Selektoren für andere Datentypen (z.B. für `REAL` oder `INT`). Dieser Baustein ist exklusiv für 64-Bit-Ganzzahlen (`LINT`) ausgelegt.

---

## Fazit

Der `LINT_ALI_AX_SEL_ALI` ist ein spezialisierter Hilfsbaustein, der in modernen, adapterbasierten 4diac-Anwendungen die Auswahl von 64-Bit-Ganzzahlwerten vereinfacht. Durch die saubere Trennung und Kapselung der Signalwege trägt er maßgeblich zur Übersichtlichkeit und Wartbarkeit von Steuerungssoftware bei.
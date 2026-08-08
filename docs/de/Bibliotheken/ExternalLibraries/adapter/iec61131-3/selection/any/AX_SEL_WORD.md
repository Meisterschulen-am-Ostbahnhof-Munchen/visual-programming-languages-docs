# AX_SEL_WORD




![AX_SEL_WORD](./AX_SEL_WORD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AX_SEL_WORD` dient zur binären Auswahl (Selektion) zwischen zwei Eingangswerten des Datentyps `WORD` (`IN0` und `IN1`). Die Auswahl wird über einen Adapter vom Typ `AX` gesteuert. Der Baustein eignet sich besonders für den Einsatz in ereignisgesteuerten Systemen gemäß IEC 61499, da er eine effiziente Signalweiterleitung mit einer integrierten Ereignisfilterung kombiniert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
* **EI0**: Aktualisiert den Wert des Eingangs `IN0`.
* **EI1**: Aktualisiert den Wert des Eingangs `IN1`.

### **Ereignis-Ausgänge**
* **CNF**: Bestätigungsereignis. Wird ausgelöst, um anzuzeigen, dass ein neuer ausgewählter Wert am Ausgang `OUT` anliegt (Achtung: Wird nur bei einer tatsächlichen Änderung des Ausgangswertes getriggert).

### **Daten-Eingänge**
* **IN0** (`WORD`): Erster auswählbarer Eingangswert (wird gewählt, wenn das Auswahlsignal `FALSE` ist).
* **IN1** (`WORD`): Zweiter auswählbarer Eingangswert (wird gewählt, wenn das Auswahlsignal `TRUE` ist).

### **Daten-Ausgänge**
* **OUT** (`WORD`): Der aktuell ausgewählte Ausgangswert.

### **Adapter**
* **G** (Typ: `adapter::types::unidirectional::AX`, Socket): Adapter-Schnittstelle zur Steuerung der Selektion. Das Datensignal `D1` dieses Adapters dient als Selektor, während das Ereignis `E1` den Auswahlprozess triggert.

---

## Funktionsweise
Intern koppelt `AX_SEL_WORD` die Eingangssignale und den Adapterzustand über ein Netzwerk aus Standard-Hilfsbausteinen (wie `F_SEL`, `F_MOVE` und Flankendetektoren):

1. **Datenübernahme**: Trifft ein Ereignis an `EI0` oder `EI1` ein, werden die entsprechenden Daten (`IN0` bzw. `IN1`) eingelesen.
2. **Adapter-Auswertung**: Ein Ereignis `E1` am Adapter `G` signalisiert eine Änderung des Auswahlsignals. Der Datenwert `D1` des Adapters bestimmt die Auswahl:
   * Ist `G.D1` = `FALSE`, wird `IN0` selektiert.
   * Ist `G.D1` = `TRUE`, wird `IN1` selektiert.
3. **Ausgangssteuerung**: Der ausgewählte Wert wird an `OUT` bereitgestellt. Das Ausgangsereignis `CNF` wird über einen internen Änderungsdetektor (`E_D_FF_ANY`) geführt. Es wird **nur dann** ein `CNF`-Event generiert, wenn sich der Wert von `OUT` im Vergleich zum vorherigen Zustand tatsächlich geändert hat.

---

## Technische Besonderheiten
* **Ressourcenschonende Ereignisfilterung**: Durch die Kopplung des Ausgangs an einen Wertänderungsdetektor (`E_D_FF_ANY`) werden redundante Ereignisse unterdrückt. Dies minimiert die CPU-Last in nachfolgenden Programmteilen.
* **Adapterbasierte Steuerung**: Die Verwendung des `AX`-Adapters erlaubt eine saubere, modularisierte Kopplung der Steuerungslogik ohne lose Event- und Datenleitungen.

---

## Zustandsübersicht

| Selektor (`G.D1`) | Eingang 0 (`IN0`) | Eingang 1 (`IN1`) | Ausgang (`OUT`) |
| :--- | :--- | :--- | :--- |
| **FALSE** | Wert_A | Wert_B | **Wert_A** |
| **TRUE** | Wert_A | Wert_B | **Wert_B** |

---

## Anwendungsszenarien
* **Sollwert-Umschaltung**: Wechseln zwischen zwei verschiedenen Betriebsparametern (z. B. Rezepturwerten oder Hand-/Automatik-Vorgaben) im `WORD`-Format.
* **Signal-Multiplexing**: Weiterleitung von Status- oder Steuerwörtern in Abhängigkeit von einem übergeordneten Prozesszustand.
* **Ereignisoptimierte Datenverarbeitung**: Reduzierung des Datenflusses in Netzwerken, bei denen nur Wertänderungen eine Aktion auslösen sollen.

---

## Vergleich mit ähnlichen Bausteinen
* **Standard `F_SEL` (IEC 61131-3)**: Der Standard-Selektor arbeitet rein datenflussorientiert und besitzt keine integrierte Ereignissteuerung oder Adapter-Anbindung. `AX_SEL_WORD` erweitert diese Funktionalität für die IEC 61499.
* **`AX_SEL`-Bausteine für andere Datentypen** (z. B. `AX_SEL_INT` oder `AX_SEL_REAL`): Besitzen dieselbe interne Logik und Struktur, verarbeiten jedoch die jeweiligen anderen Datentypen an den Ein- und Ausgängen.

---

## Fazit
`AX_SEL_WORD` ist ein hochoptimierter Funktionsbaustein für die ereignisgesteuerte Selektion von `WORD`-Daten. Dank der intelligenten Filterung von Ausgangsereignissen und der modernen Adapter-Anbindung eignet er sich hervorragend für performante und übersichtliche Steuerungsarchitekturen.
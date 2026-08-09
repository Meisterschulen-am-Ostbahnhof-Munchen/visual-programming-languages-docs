# AUI_AX_SEL_AUI


![AUI_AX_SEL_AUI](./AUI_AX_SEL_AUI.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_AX_SEL_AUI` ist ein zusammengesetzter Funktionsbaustein (Composite Function Block) für 4diac-ide. Er dient der binären Auswahl (Selektion) zwischen zwei analogen bzw. numerischen Eingangssignalen, die über Adapter bereitgestellt werden. Basierend auf dem Zustand eines Selektions-Adapters schaltet der Baustein eines der beiden Eingangssignale auf den Ausgang auf.

## Schnittstellenstruktur

Der Funktionsbaustein verfügt über keine klassischen, direkten Ereignis- oder Datenkanäle an seiner Hauptoberfläche. Die gesamte Kommunikation wird über Adapter abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden.*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN0** (Typ: `adapter::types::unidirectional::AUI`): Unidirektionaler Adapter für das erste auswählbare Eingangssignal. Dieses Signal wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Wert `FALSE` aufweist.
*   **IN1** (Typ: `adapter::types::unidirectional::AUI`): Unidirektionaler Adapter für das zweite auswählbare Eingangssignal. Dieses Signal wird an den Ausgang weitergeleitet, wenn der Selektor `G` den Wert `TRUE` aufweist.
*   **G** (Typ: `adapter::types::unidirectional::AX`): Unidirektionaler Selektor-Adapter. Bestimmt, welches der beiden Eingangssignale durchgeschaltet wird.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::AUI`): Unidirektionaler Adapter für das ausgewählte Ausgangssignal.

---

## Funktionsweise

Im Inneren des Bausteins befindet sich ein definiertes Netzwerk aus Standard-Funktionsbausteinen, das die Adapter-Signale verarbeitet:

1.  **Pufferung & Synchronisation:**
    Die über die Adapter `IN0`, `IN1` und `G` eintreffenden Ereignisse (`E1`) und Daten (`D1`) werden mithilfe von Ereignis-Daten-Flipflops (`E_D_FF` und `E_D_FF_ANY`) zwischengespeichert und synchronisiert.
2.  **Datenkonvertierung:**
    Über interne `F_MOVE`-Bausteine (konfiguriert auf den Datentyp `UINT`) werden die gepufferten numerischen Werte der Eingänge an den eigentlichen Auswahl-Baustein weitergeleitet.
3.  **Selektion:**
    Der Standard-Auswahlbaustein `F_SEL` (gemäß IEC 61131-3) führt die eigentliche Auswahl durch:
    *   Ist der Wert am Selektor `G` gleich `FALSE`, wird das Signal von `IN0` gewählt.
    *   Ist der Wert am Selektor `G` gleich `TRUE`, wird das Signal von `IN1` gewählt.
4.  **Ausgabe:**
    Das Ergebnis der Selektion wird über einen weiteren `F_MOVE`- und `E_D_FF_ANY`-Puffer an den Ausgangs-Plug `OUT` übertragen. Gleichzeitig wird das Ausgangsereignis am Plug ausgelöst, um nachfolgende Bausteine über den neuen Wert zu informieren.

---

## Technische Besonderheiten

*   **Reine Adapter-Schnittstelle:** Der Baustein ist speziell für die Verwendung in modernen, adapterbasierten Architekturen konzipiert. Dies sorgt für ein sehr cleanes und übersichtliches Applikationsdiagramm, da lose Daten- und Event-Leitungen in Adaptern gebündelt werden.
*   **Ereignisgesteuert:** Jede Änderung (Senden eines Ereignisses) an den Eingängen `IN0`, `IN1` oder dem Selektor `G` triggert eine sofortige Neuberechnung und führt zu einer Aktualisierung des Ausgangs `OUT`.
*   **Typisierung:** Die internen Konvertierungs- und Weiterleitungsbausteine arbeiten primär mit dem Datentyp `UINT`.

---

## Zustandsübersicht

Da es sich um einen Composite-FB handelt, besitzt der Baustein keine eigene Zustandsmaschine (ECC). Das Verhalten ist rein daten- und ereignisgesteuert:

| Zustand Selektor `G` (Wert von D1) | Ausgang `OUT` (Wert von D1) | Triggerung von `OUT.E1` |
|:---|:---|:---|
| `FALSE` (0) | Entspricht dem Wert von `IN0` | Ja, bei Änderung/Ereignis an `IN0` oder `G` |
| `TRUE` (1) | Entspricht dem Wert von `IN1` | Ja, bei Änderung/Ereignis an `IN1` oder `G` |

---

## Anwendungsszenarien

*   **Sollwert-Umschaltung:** Wechseln zwischen einem manuell vorgegebenen Sollwert (z. B. über ein HMI an `IN0`) und einem Automatik-Sollwert (z. B. aus einer Berechnungslogik an `IN1`).
*   **Sensorredundanz:** Umschalten zwischen zwei analogen Messwertgebern (z. B. Primärsensor an `IN1` und Backup-Sensor an `IN0`) im Fehlerfall über ein Steuersignal an `G`.
*   **Betriebsartenwahl:** Auswahl unterschiedlicher analoger Steuerparameter in Abhängigkeit vom aktuellen Maschinenzustand.

---

## Vergleich mit ähnlichen Bausteinen

Der klassische Standard-Baustein `F_SEL` benötigt direkte Datenleitungen (z. B. `ANY_ELEMENTARY`) und eine manuelle Event-Verkabelung für die Berechnungstriggerung (`REQ`/`CNF`). 

Der Baustein `AUI_AX_SEL_AUI` kapselt diese komplette Logik inklusive der Event-Synchronisation und Pufferung. Er eignet sich daher ideal für modularisierte Software-Architekturen, bei denen Signalgruppen bereits standardmäßig als Adapter vorliegen.

---

## Fazit

`AUI_AX_SEL_AUI` vereinfacht das Signalrouting in 4diac-Anwendungen erheblich. Er kombiniert die bewährte Auswahl-Logik der IEC 61131-3 mit den strukturellen Vorteilen ereignisgesteuerter Adapter in der IEC 61499.
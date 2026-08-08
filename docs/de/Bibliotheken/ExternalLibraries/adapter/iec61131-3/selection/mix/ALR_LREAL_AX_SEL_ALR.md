# ALR_LREAL_AX_SEL_ALR


![ALR_LREAL_AX_SEL_ALR](./ALR_LREAL_AX_SEL_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_LREAL_AX_SEL_ALR` dient der binären Auswahl (Multiplexing) zwischen zwei analogen Eingangssignalen des Datentyps `LREAL`. Der Baustein kombiniert klassische IEC 61499-Ereignisse und -Daten mit modernen, adapterbasierten Schnittstellen. 

Die Steuerung, welcher der beiden Eingänge auf den Ausgang durchgeschaltet wird, erfolgt über ein binäres Auswahlsignal (`G`), welches über einen Adapter eingelesen wird. Das Ausgangssignal wird ebenfalls über einen Adapter ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Zugehörige Daten |
| :--- | :--- | :--- |
| **EI1** | Signalisiert die Aktualisierung des klassischen Dateneingangs `IN1`. | `IN1` |

### **Ereignis-Ausgänge**

*Der Baustein besitzt keine direkten, klassischen Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Daten-Eingänge**

| Datenpunkt | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| **IN1** | LREAL | Zu selektierender Eingangswert 1 (klassische Variable). |

### **Daten-Ausgänge**

*Der Baustein besitzt keine direkten, klassischen Daten-Ausgänge. Die Datenausgabe erfolgt gekoppelt über den Ausgangs-Adapter `OUT`.*

### **Adapter**

| Adaptername | Typ | Richtung | Beschreibung |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::ALR` | Plug (Stecker) | Der ausgewählte Ausgangswert (LREAL) inklusive des dazugehörigen Aktualisierungsereignisses. |
| **IN0** | `adapter::types::unidirectional::ALR` | Socket (Buchse) | Zu selektierender Eingangswert 0 (LREAL-Signal via Adapter). |
| **G** | `adapter::types::unidirectional::AX` | Socket (Buchse) | Selektionseingang (Gate/Selector via Adapter). |

## Funktionsweise

Der Baustein basiert intern auf einem logischen Netzwerk, das Ereignisse und Daten puffert und über den Standard-Auswahlbaustein `F_SEL` verarbeitet:

1. **Pufferung der Eingänge:**
   * Das Auswahlsignal aus dem Adapter `G` (Datenpunkt `D1`, Ereignis `E1`) wird über ein D-Flipflop (`E_D_FF`) stabilisiert.
   * Der Adapter-Eingang `IN0` (Datenpunkt `D1`, Ereignis `E1`) wird über ein universelles D-Flipflop (`E_D_FF_ANY_IN0`) gepuffert und mittels `F_MOVE_IN0` an den Selektor übergeben.
   * Der klassische Dateneingang `IN1` (getriggert durch `EI1`) wird analog über `E_D_FF_ANY_IN1` und `F_MOVE_IN1` verarbeitet.

2. **Auswahllogik (`F_SEL`):**
   * Liegt am Adapter `G` das Signal `FALSE` an, wird der Wert von `IN0` (Adapter) auf den Ausgang durchgeschaltet.
   * Liegt am Adapter `G` das Signal `TRUE` an, wird der Wert von `IN1` (klassischer Eingang) auf den Ausgang durchgeschaltet.

3. **Ausgabesteuerung:**
   * Jede Änderung an den Eingängen oder dem Auswahlsignal triggert eine Neuberechnung. Der selektierte Wert wird über das Ausgangs-Flipflop `E_D_FF_ANY_OUT` an den Ausgangs-Adapter `OUT` (Datenpunkt `D1`, Ereignis `E1`) übergeben.

```
          +-----------------------------------------+
          |           ALR_LREAL_AX_SEL_ALR          |
          |                                         |
 (ALR) ---> [IN0]  ======\                          |
          |               \                         |
 (AX)  ---> [G]    ========+===> [ F_SEL ] ===> [OUT] ---> (ALR)
          |               /                         |
 (LREAL)--> [IN1]  ======/                          |
 (Event)--> [EI1]  -----/                           |
          +-----------------------------------------+
```

## Technische Besonderheiten

* **Adapter-Kopplung:** Der Baustein eignet sich hervorragend zur Brückenbildung zwischen adapterbasierter Kommunikation (z. B. strukturierte Feldbus- oder Sensor-Koppler) und klassischen Funktionsbaustein-Strukturen.
* **Ereignisgesteuert:** Durch die interne Verwendung von Ereignis-Flipflops (`E_D_FF` / `E_D_FF_ANY`) wird sichergestellt, dass der Ausgang nur dann ein Ereignis feuert, wenn sich tatsächlich Daten oder der Zustand des Selektors geändert haben.

## Zustandsübersicht

Die nachfolgende Tabelle zeigt das Verhalten des Ausgangs `OUT` in Abhängigkeit vom Steuersignal `G`:

| Zustand von `G` | Ausgewählter Ausgang (`OUT.D1`) | Triggerndes Ereignis am Ausgang (`OUT.E1`) |
| :--- | :--- | :--- |
| **FALSE** | Wert von `IN0.D1` | Bei Änderung von `IN0.D1`, `IN0.E1` oder Zustandswechsel von `G` |
| **TRUE** | Wert von `IN1` | Bei Änderung von `IN1`, `EI1` oder Zustandswechsel von `G` |

## Anwendungsszenarien

* **Sollwert-Umschaltung:** Umschalten einer analogen Führungsgröße (LREAL) zwischen einem automatischen Sensorwert (über Adapter `IN0`) und einem manuell vorgegebenen Parameter (über klassischen Eingang `IN1`).
* **Hand-/Automatik-Umschaltung:** Einsatz in verfahrenstechnischen Anlagen, bei denen im Fehlerfall oder zu Wartungszwecken über das Signal `G` auf einen statischen Ersatzwert oder manuellen Vorgabewert gewechselt werden muss.
* **Signal-Routing:** Dynamische Umleitung von Datenströmen in komplexen verteilten Steuerungssystemen.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-Auswahlbaustein `F_SEL` aus der IEC 61131-3-Bibliothek, welcher rein datenflussorientiert arbeitet, bietet `ALR_LREAL_AX_SEL_ALR` eine vollständige Integration in die ereignisgesteuerte Architektur von IEC 61499. Er kapselt die notwendige Ereignis- und Konvertierungslogik, sodass keine zusätzlichen Hilfsbausteine zur Signalpufferung im Anwendungsnetzwerk benötigt werden.

## Fazit

Der `ALR_LREAL_AX_SEL_ALR` ist ein spezialisierter und robuster Multiplexer für `LREAL`-Signale. Durch die geschickte Kombination von klassischen Dateneingängen und modernen, unidirektionalen Adaptern ermöglicht er eine saubere und übersichtliche Strukturierung von Steuerungssoftware in 4diac.
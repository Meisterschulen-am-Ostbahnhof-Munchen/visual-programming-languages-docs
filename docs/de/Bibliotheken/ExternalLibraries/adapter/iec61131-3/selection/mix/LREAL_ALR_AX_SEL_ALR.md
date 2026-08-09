# LREAL_ALR_AX_SEL_ALR


![LREAL_ALR_AX_SEL_ALR](./LREAL_ALR_AX_SEL_ALR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `LREAL_ALR_AX_SEL_ALR` ist ein binärer Selektionsbaustein (Auswahlbaustein) für den Datentyp `LREAL`. Er dient dazu, basierend auf dem Zustand eines Selektionssignals (Gate-Signal `G`), einen von zwei hochpräzisen analogen Eingangswerten (`IN0` oder `IN1`) auszuwählen und an den Ausgang (`OUT`) weiterzuleiten. Durch die Verwendung von IEC 61499 Adaptern ermöglicht der Baustein eine saubere, modulare und ereignisgesteuerte Signalverarbeitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **EI0**: Löst die Aktualisierung und Übernahme des direkt anliegenden Daten-Eingangs `IN0` aus.

### **Ereignis-Ausgänge**

*   *(Keine direkten Ereignis-Ausgänge auf der Hauptschnittstelle vorhanden. Die Ereignisweiterleitung erfolgt gekapselt über den Ausgangs-Adapter `OUT`.)*

### **Daten-Eingänge**

*   **IN0** (LREAL): Der erste auszuwählende Eingangswert. Dieser Wert wird zum Ausgang durchgeschaltet, wenn das Selektionssignal `G` den Zustand `FALSE` aufweist.

### **Daten-Ausgänge**

*   *(Keine direkten Daten-Ausgänge auf der Hauptschnittstelle vorhanden. Die Datenbereitstellung erfolgt gekapselt über den Ausgangs-Adapter `OUT`.)*

### **Adapter**

*   **IN1** (Socket, Typ: `adapter::types::unidirectional::ALR`): Ein unidirektionaler Adapter-Eingang für den zweiten auszuwählenden Wert.
*   **G** (Socket, Typ: `adapter::types::unidirectional::AX`): Ein unidirektionaler Adapter-Eingang für das Selektionssignal (Selector).
*   **OUT** (Plug, Typ: `adapter::types::unidirectional::ALR`): Ein unidirektionaler Adapter-Ausgang, der das ausgewählte Signal sowie das zugehörige Aktualisierungsereignis ausgibt.

## Funktionsweise

Der Baustein ist intern als Netzwerk (Sub-FB) realisiert, das eine zuverlässige, ereignisgesteuerte Selektion sicherstellt:
1.  **Signalpufferung**: Die Eingangsdaten von `IN0`, `IN1` und `G` werden bei Eintreffen ihrer jeweiligen Ereignisse (`EI0`, `IN1.E1`, `G.E1`) über D-Flip-Flops (`E_D_FF` / `E_D_FF_ANY`) zwischengespeichert.
2.  **Wertübergabe**: Über nachgeschaltete Move-Bausteine (`F_MOVE`) werden die Daten konsistent an den zentralen Selektionsbaustein (`F_SEL`) übergeben.
3.  **Auswahlprozess**: Der Baustein `F_SEL` führt die eigentliche binäre Auswahl durch:
    *   Ist das Selektionssignal `G.D1` = `FALSE`, wird der Wert von `IN0` gewählt.
    *   Ist das Selektionssignal `G.D1` = `TRUE`, wird der Wert von `IN1.D1` gewählt.
4.  **Ausgangsaktualisierung**: Der selektierte Wert wird an den Ausgangs-Plug `OUT` übergeben. Gleichzeitig wird das Ausgangsereignis `OUT.E1` generiert, um nachfolgende Programmteile über das Vorliegen eines neuen Wertes zu informieren.

## Technische Besonderheiten

*   **Ereignisgesteuerter Datenfluss**: Jede Änderung an einem der Eingänge oder am Auswahlsignal triggert sofort eine Neuberechnung und eine eventuelle Aktualisierung des Ausgangs.
*   **Adapter-Strukturierung**: Durch die Verwendung unidirektionaler Adapter wird die Komplexität der Verkabelung in übergeordneten Systemen erheblich reduziert, da Daten und Ereignisse in einem einzigen Verbindungskanal gebündelt sind.
*   **Datentyp-Präzision**: Durch die durchgängige Verwendung des Typs `LREAL` eignet sich der Baustein für hochpräzise physikalische Größen und Berechnungen.

## Zustandsübersicht

Da es sich um einen reinen datenfluss- und ereignisgesteuerten Sub-FB handelt, besitzt der Baustein keine eigene komplexe Zustandsmaschine (ECC). Das Verhalten lässt sich tabellarisch wie folgt beschreiben:

| Zustand Selector (`G.D1`) | Auslösendes Ereignis | Ausgangswert (`OUT.D1`) | Beschreibung |
| :--- | :--- | :--- | :--- |
| `FALSE` | Beliebiges Eingangsereignis | Wert von `IN0` | `IN0` ist aktiv durchgeschaltet. Änderungen an `IN1` beeinflussen den Ausgang nicht. |
| `TRUE` | Beliebiges Eingangsereignis | Wert von `IN1.D1` | `IN1` ist aktiv durchgeschaltet. Änderungen an `IN0` beeinflussen den Ausgang nicht. |

## Anwendungsszenarien

*   **Sollwert-Umschaltung**: Wechseln zwischen einem lokal vorgegebenen Sollwert (`IN0` via `LREAL`) und einem externen, über ein Bus-System oder ein anderes Softwaremodul bereitgestellten Sollwert (`IN1` via Adapter).
*   **Hand-/Automatikbetrieb**: Umschalten einer Stellgröße zwischen einem manuell eingegebenen Wert und dem berechneten Wert eines Automatikreglers.
*   **Signal-Umschaltung für redundante Sensoren**: Auswählen eines Backup-Sensors bei Ausfall oder zur Kalibrierung des Primärsensors.

## Vergleich mit ähnlichen Bausteinen

*   **Standard-FB `F_SEL`**: Der klassische Selektionsbaustein nach IEC 61131-3 arbeitet rein datenorientiert und besitzt keine integrierte Ereignissteuerung oder Adapter-Schnittstellen. `LREAL_ALR_AX_SEL_ALR` erweitert diese Basisfunktionalität um die ereignisbasierte Ausführung von IEC 61499.
*   **Typ-Varianten**: Für andere Datentypen (z.B. `REAL`, `INT`) existieren analoge Bausteine, die dieselbe interne Logik verwenden, jedoch auf die jeweiligen Datentypen der Adapter angepasst sind.

## Fazit

Der Baustein `LREAL_ALR_AX_SEL_ALR` bietet eine effiziente, sichere und standardisierte Möglichkeit, präzise Fließkommawerte in ereignisgesteuerten Systemen zu selektieren. Durch die Kapselung der D-Flip-Flops zur Signalstabilisierung und die Verwendung moderner Adapterstrukturen trägt er maßgeblich zur Übersichtlichkeit und Determinierung von Steuerungsprogrammen bei.
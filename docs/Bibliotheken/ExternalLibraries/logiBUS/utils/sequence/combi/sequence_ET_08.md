# sequence_ET_08

```{index} single: sequence_ET_08
```

<img width="1352" height="421" alt="image" src="https://github.com/user-attachments/assets/597e2c46-3888-4688-b81b-b23b010b500a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_08` ist ein Sequenzer mit acht Ausgängen. Er ermöglicht die Abarbeitung einer festen Schrittkette, wobei der Übergang von einem Schritt zum nächsten entweder durch ein externes Ereignis oder durch einen einstellbaren Zeitablauf erfolgen kann. Der Baustein ist besonders für Steuerungsaufgaben geeignet, bei denen eine zyklische oder zeitgesteuerte Abfolge von Aktionen benötigt wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   `START_S1`: Springt vom `START`-Zustand in den Zustand `State_01`. Überträgt alle Zeitdaten (`DT_S1_S2` bis `DT_S8_START`).
*   `S1_S2`: Springt von `State_01` zu `State_02`.
*   `S2_S3`: Springt von `State_02` zu `State_03`.
*   `S3_S4`: Springt von `State_03` zu `State_04`.
*   `S4_S5`: Springt von `State_04` zu `State_05`.
*   `S5_S6`: Springt von `State_05` zu `State_06`.
*   `S6_S7`: Springt von `State_06` zu `State_07`.
*   `S7_S8`: Springt von `State_07` zu `State_08`.
*   `S8_START`: Springt von `State_08` zurück in den `START`-Zustand.
*   `RESET`: Setzt den Baustein aus jedem beliebigen Zustand zurück in den `START`-Zustand.

### **Ereignis-Ausgänge**
*   `CNF`: Ausführungsbestätigung. Wird bei jedem Zustandswechsel gesetzt und überträgt die aktuelle Zustandsnummer (`STATE_NR`).
*   `EO_S1` bis `EO_S8`: Zustands-spezifische Ereignisausgänge. Werden beim Eintritt in den entsprechenden Zustand (`State_01` bis `State_08`) ausgelöst und übertragen den jeweiligen booleschen Datenausgang (`DO_S1` bis `DO_S8`).

### **Daten-Eingänge**
*   `DT_S1_S2` bis `DT_S8_START` (Typ `TIME`): Definieren die Zeitdauer für den automatischen Übergang vom aktuellen zum nächsten Zustand. Wenn der Wert auf `NO_TIME` gesetzt ist, ist der zeitgesteuerte Übergang für diesen Schritt deaktiviert und ein Ereignis ist erforderlich.

### **Daten-Ausgänge**
*   `STATE_NR` (Typ `SINT`): Gibt die aktuelle Zustandsnummer aus (`START = 0`, `State_01 = 1`, ..., `State_08 = 8`).
*   `DO_S1` bis `DO_S8` (Typ `BOOL`): Logische Ausgänge, die `TRUE` sind, solange sich der Baustein im entsprechenden Zustand (`State_01` bis `State_08`) befindet.

### **Adapter**
*   `timeOut` (Typ `iec61499::events::ATimeOut`): Ein Zeitgeber-Adapter, der für die Realisierung der zeitgesteuerten Zustandsübergänge verwendet wird.

## Funktionsweise
Der Baustein ist als Basic-FB mit einer Execution Control Chart (ECC) implementiert. Er startet im initialen Zustand `xSTART`. Ein `START_S1`-Ereignis führt in den ersten aktiven Zustand `sState_01`. Jeder aktive Zustand (`sState_01` bis `sState_08`) führt beim Eintritt folgende Aktionen aus:
1.  Stoppt den laufenden Zeitgeber.
2.  Führt den Exit-Algorithmus des vorherigen Zustands aus (schaltet den vorherigen Ausgang aus).
3.  Führt den Confirmation-Algorithmus (`*_C`) aus, der die `STATE_NR` setzt und die Zeit für den nächsten möglichen automatischen Übergang im `timeOut`-Adapter konfiguriert.
4.  Führt den Entry-Algorithmus (`*_E`) aus, der den zugehörigen booleschen Ausgang (`DO_Sx`) aktiviert und das entsprechende Ereignis (`EO_Sx`) auslöst.
5.  Startet den Zeitgeber mit der für diesen Zustand eingestellten Dauer (`DT_*`).

Der Übergang zum nächsten Zustand kann auf zwei Arten erfolgen:
1.  **Ereignisgesteuert:** Durch das entsprechende Sprung-Ereignis (z.B. `S1_S2`).
2.  **Zeitgesteuert:** Durch das `TimeOut`-Ereignis des Adapters, sofern die Zeitdauer (`DT_*`) nicht `NO_TIME` ist.

Das `RESET`-Ereignis führt in einen dedizierten Reset-Zustand (`sRESET`), der alle aktiven Ausgänge ausschaltet, bevor er in den inaktiven `START`-Zustand (`sState_00`) übergeht.

## Technische Besonderheiten
*   **Hybride Transitionen:** Jeder Schritt bietet zwei parallele Übergangsbedingungen (Ereignis ODER Zeit), was maximale Flexibilität bietet.
*   **Sichere Zustandsbehandlung:** Beim Zustandswechsel wird der Zeitgeber immer gestoppt, und die Ausgänge werden durch definierte Exit-Algorithmen sauber deaktiviert.
*   **Konfigurierbare Zeiten:** Die Zeit für jeden Schritt kann individuell eingestellt oder durch `NO_TIME` deaktiviert werden.
*   **Explizite Zustandsrückmeldung:** Der Ausgang `STATE_NR` erlaubt eine einfache externe Überwachung der aktuellen Schrittposition.

## Zustandsübersicht
1.  **xSTART:** Initialer, inaktiver Zustand (beim Start des FBs).
2.  **sState_00:** Inaktiver `START`-Zustand (nach Reset oder Zyklusende). `STATE_NR = 0`.
3.  **sState_01 bis sState_08:** Aktive Zustände der Sequenz. `STATE_NR = 1` bis `8`. Die entsprechenden Ausgänge `DO_S1` bis `DO_S8` sind aktiv.
4.  **sRESET:** Temporärer Zustand, der bei einem `RESET`-Ereignis alle aktiven Ausgänge ausschaltet.

## Anwendungsszenarien
*   Steuerung von zyklischen Prozessen in Verpackungs- oder Fertigungsmaschinen.
*   Schrittkette für einen automatisierten Test- oder Kalibrierablauf.
*   Steuerung einer Belichtungs- oder Spülsequenz in der Halbleiterfertigung.
*   Allgemeine Zustandsautomaten, bei denen Schritte sowohl durch Sensorik (Ereignis) als auch durch feste Zeiten vorangetrieben werden können.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Sequenzern (z.B. `E_SR` oder `E_CTU` in Reihe) bietet `sequence_ET_08` eine vollständig vordefinierte Schrittkette mit integrierter Zeitsteuerung und dedizierten Ausgängen pro Schritt. Im Gegensatz zu einer individuell programmierten SFC (Sequential Function Chart) ist die Logik fest verdrahtet, was die Anwendung einfacher, aber auch weniger flexibel macht. Bausteine wie `E_DELAY` müssten extern hinzugefügt werden, während hier die Zeitfunktionalität integriert ist.

## Fazit
Der `sequence_ET_08` ist ein robuster und einfach zu konfigurierender Sequenzer-Baustein für IEC 61499. Seine Stärke liegt in der kombinierten Ereignis- und Zeitsteuerung sowie der klaren, pro Schritt definierten Schnittstelle. Er eignet sich ideal für standardisierte Steuerungsabläufe mit bis zu acht Schritten, bei denen ein hohes Maß an Vorhersagbarkeit und einfache Parametrierung gewünscht ist. Für Prozesse mit variabler Schrittanzahl oder komplexeren Verzweigungen sind flexiblere Lösungen wie Composite-FBs oder eigene SFCs vorzuziehen.
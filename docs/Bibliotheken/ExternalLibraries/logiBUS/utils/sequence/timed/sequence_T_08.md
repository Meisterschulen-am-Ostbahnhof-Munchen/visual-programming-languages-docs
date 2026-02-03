# sequence_T_08

```{index} single: sequence_T_08
```

<img width="1169" height="403" alt="image" src="https://github.com/user-attachments/assets/fc79f7bd-8f7c-4df6-891f-b05cfce0f952" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_08` ist ein zeitgesteuerter Sequenzer mit acht Ausgängen. Er realisiert eine feste Abfolge von Zuständen, wobei der Übergang zwischen den einzelnen Zuständen durch einstellbare Zeitverzögerungen gesteuert wird. Der Baustein ist für Anwendungen konzipiert, in denen Prozessschritte oder Maschinenzustände nacheinander für eine definierte Dauer aktiviert werden müssen, wie z.B. in Verpackungsmaschinen, Förderstrecken oder Waschanlagen.

![sequence_T_08](sequence_T_08.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   `START_S1`: Startet die Sequenz. Ein Ereignis an diesem Eingang bewirkt den Übergang vom `START`-Zustand in den ersten aktiven Zustand `State_01`. Es werden alle acht Zeitdaten-Eingänge mitgelesen.
*   `RESET`: Setzt die Sequenz sofort zurück. Ein Ereignis an diesem Eingang führt von jedem beliebigen Zustand zum `START`-Zustand und deaktiviert alle Ausgänge.

### **Ereignis-Ausgänge**
*   `CNF`: Bestätigungsereignis (Execution Confirmation). Wird bei jedem Zustandswechsel ausgelöst und liefert die neue Zustandsnummer `STATE_NR`.
*   `EO_S1` bis `EO_S8`: Zustandsereignisse. Jedes dieser Ereignisse wird beim Eintritt in den entsprechenden Zustand (`State_01` bis `State_08`) ausgelöst und liefert den zugehörigen booleschen Datenausgangswert (`DO_S1` bis `DO_S8`).

### **Daten-Eingänge**
*   `DT_S1_S2` bis `DT_S8_START` (Typ `TIME`): Definieren die Verweilzeit für jeden Zustand. Der Wert legt fest, wie lange der FB im jeweiligen Zustand verbleibt, bevor der automatische Übergang zum nächsten Zustand erfolgt. Der Standardwert `NO_TIME` deaktiviert den zeitgesteuerten Übergang, sodass der FB im Zustand verharrt, bis ein `RESET` erfolgt.

### **Daten-Ausgänge**
*   `STATE_NR` (Typ `SINT`): Gibt die aktuelle Zustandsnummer aus. `0` entspricht dem `START`-Zustand, `1` bis `8` entsprechen den aktiven Zuständen `State_01` bis `State_08`.
*   `DO_S1` bis `DO_S8` (Typ `BOOL`): Die physischen Ausgangssignale der Sequenz. Jeder Ausgang wird auf `TRUE` gesetzt, wenn der entsprechende Zustand aktiv ist, andernfalls ist er `FALSE`.

### **Adapter**
*   `timeOut` (Typ `iec61499::events::ATimeOut`): Ein Steckadapter, der die Zeitsteuerung bereitstellt. Der FB nutzt die Schnittstelle, um einen Timer zu starten (`timeOut.START`) und auf dessen Ablauf zu warten (`timeOut.TimeOut`). Die jeweilige Zeitdauer wird über `timeOut.DT` übergeben.

## Funktionsweise
Der FB arbeitet als Basic Function Block (BFB) mit einer definierten Execution Control Chart (ECC). Die Sequenz durchläuft die Zustände `State_01` bis `State_08` in fester Reihenfolge. Jeder aktive Zustand führt drei wesentliche Aktionen aus:
1.  **Exit-Aktion des vorherigen Zustands**: Deaktiviert den zugehörigen Ausgang (Algorithmus `State_XX_X`).
2.  **Confirmation-Aktion**: Setzt die Zustandsnummer `STATE_NR` und übergibt die für diesen Zustand konfigurierte Zeitdauer an den Timer-Adapter (Algorithmus `State_XX_C`). Löst das `CNF`-Ereignis aus.
3.  **Entry-Aktion**: Aktiviert den zugehörigen Ausgang (Algorithmus `State_XX_E`). Löst das entsprechende `EO_Sx`-Ereignis aus. Startet den Timer.

Der Übergang zum nächsten Zustand erfolgt ausschließlich, wenn der Timer abgelaufen ist (`timeOut.TimeOut`). Nach `State_08` springt der FB in den inaktiven `State_00` (auch als `START` dargestellt), wo der Timer gestoppt wird. Von hier aus kann die Sequenz nur durch ein neues `START_S1`-Ereignis neu gestartet werden. Ein `RESET`-Ereignis von jedem Zustand aus führt über einen dedizierten Reset-Zustand (`sRESET`) zurück in `State_00`, wobei dabei alle aktiven Ausgänge deaktiviert werden.

## Technische Besonderheiten
*   **Flexible Zeitsteuerung**: Jeder Zustandsübergang kann individuell und zur Laufzeit über die `DT_`-Eingänge konfiguriert werden. Der Wert `NO_TIME` erlaubt es, die Sequenz an einer bestimmten Stelle anzuhalten.
*   **Sofortiger Reset**: Der `RESET`-Eingang hat jederzeit Priorität und unterbricht die laufende Zeitsteuerung sofort.
*   **Zustandsrückmeldung**: Die aktuelle Position in der Sequenz ist über den `STATE_NR`-Ausgang stets nachvollziehbar.
*   **Ereignisgesteuerte Ausgänge**: Neben den kontinuierlichen Datenausgängen (`DO_Sx`) bietet der FB für jeden Zustand ein separates Ereignis (`EO_Sx`), was die Ansteuerung nachgelagerter, ereignisgesteuerter FB erleichtert.

## Zustandsübersicht
Die ECC umfasst folgende Zustände:
*   **xSTART / sState_00**: Inaktiver Start- und Endzustand. `STATE_NR = 0`, alle Ausgänge sind `FALSE`.
*   **sState_01 bis sState_08**: Die acht aktiven Sequenzzustände. `STATE_NR = 1` bis `8`. Der entsprechende Ausgang `DO_Sx` ist `TRUE`.
*   **sRESET**: Interner Reset-Zustand. Deaktiviert alle Ausgänge und führt zurück zu `sState_00`.

## Anwendungsszenarien
*   **Steuerung von Zyklusabläufen**: In Maschinen, bei denen verschiedene Aktoren (Ventile, Motoren, Heizungen) nacheinander für eine bestimmte Zeit ein- und ausgeschaltet werden müssen.
*   **Batch-Prozesse**: Für die Reihensteuerung von Prozessschritten in der Lebensmittel- oder Chemieindustrie, z.B. Füllen, Erhitzen, Rühren, Abkühlen.
*   **Teststände**: Automatisierte Abfolge von Prüf- und Messschritten an einem Bauteil.
*   **Sicherheitssequenzen**: Geordnetes An- und Abfahren einer Anlage, bei dem Schritte erst nach einer Wartezeit ausgelöst werden dürfen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem einfachen TON (Timer On-Delay) oder TOF (Timer Off-Delay), die nur einen einzigen zeitverzögerten Schaltvorgang steuern, orchestriert `sequence_T_08` eine komplette Kette von zeitgesteuerten Aktionen. Im Vergleich zu einem Zählerbaustein (CTU) bietet er eine vordefinierte, zustandsbasierte Logik mit dedizierten Ausgängen und ist daher einfacher zu konfigurieren und abzusichern. Er ist eine spezialisierte Form einer Schrittkette (Sequential Function Chart - SFC) mit fester Schrittanzahl und reiner Zeitsteuerung.

## Fazit
Der `sequence_T_08` ist ein robuster und einfach zu konfigurierender Funktionsblock für alle Anwendungen, die eine feste, zeitgesteuerte Abfolge von Schritten erfordern. Durch die klare Trennung von Zustandslogik, Zeitparametern und Ausgangssignalen sowie die sofortige Reset-Funktionalität eignet er sich besonders für übersichtliche und wartungsfreundliche Steuerungsprogramme. Die Integration eines Standard-Timer-Adapters macht ihn zudem portabel und wiederverwendbar in verschiedenen 4diac-Projekten.
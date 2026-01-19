# SchieberControl

```{index} single: SchieberControl
```

<img width="1509" height="338" alt="image" src="https://github.com/user-attachments/assets/ed91b9bc-3eed-4d26-8b19-06f71ea1f94d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SchieberControl` ist ein Basis-Funktionsblock (Basic FB) gemäß IEC 61499 zur Steuerung eines Schieber-Antriebs (z. B. pneumatisch). Er realisiert eine vollständige Zustandsmaschine (ECC), die die Bewegung (Öffnen/Schließen), Haltezustände und Fehlerzustände eines Schiebers verwaltet. Der Baustein bietet eine umfassende Schnittstelle zur Parametrierung, zur Bedienung über Taster (Button), Softkeys und Hilfssteuerungen (Auxiliary) sowie zur Ausgabe von Steuersignalen für die Aktorik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`INIT`**: Initialisierungsanforderung. Setzt alle Werte. Ein vollständiges De-Initialisieren wird nicht vollständig unterstützt. Wird mit den Daten `QI`, `DT_Opening`, `DT_Closing` und `START` verknüpft.
*   **`Open`**: Startet den Öffnungsvorgang des Schiebers.
*   **`Close`**: Startet den Schließvorgang des Schiebers.
*   **`RESET`**: Setzt den internen Zustand auf "Unknown" (Unbekannt) zurück.
*   **`INPUT_DATA`**: Überträgt die konfigurierten Eingangsdaten für Taster, Softkeys und Hilfssteuerung. Wird mit den Daten `BT`, `SK` und `AUXC` verknüpft.

### **Ereignis-Ausgänge**
*   **`INITO`**: Initialisierungsbestätigung. Wird mit dem Datenausgang `QO` verknüpft.
*   **`EO`**: Allgemeines Ausgangsereignis, das den aktuellen Systemzustand und die konfigurierten Ausgangswerte liefert. Wird mit `Button`, `Softkey`, `Auxiliary` und `STATE` verknüpft.
*   **`EO_POWERED`**: Steuersignal zum Betätigen des "Öffnen"-Ventils für die Pneumatik. Wird mit `DO_POWERED` verknüpft.
*   **`EO_OPEN`**: Steuersignal zum Betätigen des "Öffnen"-Ventils. Wird mit `DO_OPEN` verknüpft.
*   **`EO_CLOSE`**: Steuersignal zum Betätigen des "Schließen"-Ventils. Wird mit `DO_CLOSE` verknüpft.
*   **`EO1`**: Zusätzliches Ausgangsereignis ohne Daten.

### **Daten-Eingänge**
*   **`QI` (BOOL)**: Qualifizierer für das INIT-Ereignis.
*   **`BT` (SchieberStruct)**: Konfiguration für die Taster-Bedienelemente.
*   **`SK` (SchieberStruct)**: Konfiguration für die Softkey-Bedienelemente.
*   **`AUXC` (SchieberAuxInStruct)**: Konfiguration für die Hilfssteuerung (Bild und Farbe).
*   **`DT_Opening` (TIME)**: Zeitdauer für den Öffnungsvorgang.
*   **`DT_Closing` (TIME)**: Zeitdauer für den Schließvorgang.
*   **`START` (UINT)**: Definiert den gewünschten Startzustand nach der Initialisierung (z. B. `START::STARTClosed`, `START::STARTOpened`, `START::STARTUnknown`).

### **Daten-Ausgänge**
*   **`QO` (BOOL)**: Qualifizierer für das INITO-Ereignis.
*   **`Button` (UINT)**: Aktueller Wert für die Taster-Ausgabe, abhängig vom Zustand.
*   **`Softkey` (UINT)**: Aktueller Wert für die Softkey-Ausgabe, abhängig vom Zustand.
*   **`Auxiliary` (SchieberAuxOutStruct)**: Aktuelle Werte für die Hilfssteuerungs-Ausgabe (Bild und Farbe).
*   **`DO_POWERED` (BOOL)**: Binäres Signal zum Betätigen des "Öffnen"-Ventils für die Pneumatik.
*   **`DO_OPEN` (BOOL)**: Binäres Signal zum Betätigen des "Öffnen"-Ventils.
*   **`DO_CLOSE` (BOOL)**: Binäres Signal zum Betätigen des "Schließen"-Ventils.
*   **`STATE` (STRING)**: Zeichenkette, die den aktuellen internen Zustand des FB beschreibt (z. B. "Closed", "Opening").

### **Adapter**
*   **`timeOut` (ATimeOut)**: Ein Stecker-Adapter vom Typ `ATimeOut`. Wird zur Realisierung der zeitgesteuerten Zustandsübergänge (Öffnen/Schließen) verwendet. Der FB startet (`START`) und stoppt (`STOP`) den Timer und reagiert auf dessen `TimeOut`-Ereignis.

## Funktionsweise
Der `SchieberControl`-FB arbeitet als zustandsgesteuerte Sequenz. Der interne Ablaufsteuerungsgraph (ECC) definiert die Zustände `Closed` (Geschlossen), `Opened` (Geöffnet), `Opening` (Öffnend), `Closing` (Schließend), verschiedene STOP-Zustände und `Unknown` (Unbekannt). Bei jedem Zustandswechsel wird ein entsprechender Algorithmus ausgeführt, der die Datenausgänge (wie `DO_OPEN`, `STATE`, `Button`) setzt und bei Bedarf den Timer-Adapter startet. Die Bewegung zwischen `Closed` und `Opened` erfolgt zeitgesteuert über die Zustände `Opening` und `Closing`. Während einer Bewegung kann durch das gegenteilige Ereignis (`Open` während `Closing` oder `Close` während `Opening`) ein Stopp eingeleitet werden, der in einen entsprechenden STOP-Zustand überführt. Von jedem Zustand aus kann ein `RESET` den FB in den `Unknown`-Zustand versetzen.

## Technische Besonderheiten
*   **Zustandsinitialisierung**: Über den `START`-Eingang kann nach `INIT` der gewünschte Anfangszustand (`Closed`, `Opened` oder `Unknown`) vorgegeben werden. Dies erfordert das nachfolgende Eintreffen des `INPUT_DATA`-Ereignisses.
*   **Adapter-Nutzung**: Die Zeitsteuerung ist vollständig in den Adapter `timeOut` ausgelagert, was eine klare Trennung der Funktionalität und potenzielle Wiederverwendbarkeit ermöglicht.
*   **Datenkonfiguration**: Die Ausgabewerte für Benutzerschnittstellen (`Button`, `Softkey`, `Auxiliary`) werden nicht hartkodiert, sondern über entsprechende Eingangsstrukturen (`BT`, `SK`, `AUXC`) konfiguriert, was eine flexible Anpassung an verschiedene HMI erlaubt.
*   **Power-Signal**: Das Signal `DO_POWERED` wird nur in den Zuständen `Opening` und `Opened` aktiviert, was auf eine spezifische pneumatische Ansteuerlogik hindeutet (z. B. Halten der Druckluft im geöffneten Zustand).

## Zustandsübersicht
Die ECC umfasst folgende Hauptzustände:
1.  **`START`**: Inaktiver Ausgangszustand.
2.  **`Init`/`INIT3`**: Initialisierungssequenz.
3.  **`Closed`**: Endzustand "geschlossen". Aktiviert `DO_CLOSE`.
4.  **`Opened`**: Endzustand "geöffnet". Aktiviert `DO_OPEN` und `DO_POWERED`.
5.  **`Opening`/`Closing`**: Bewegungszustände. Starten den Timer mit `DT_Opening`/`DT_Closing` und aktivieren die entsprechenden Aktorsignale sowie `DO_POWERED` (nur bei `Opening`).
6.  **`Opening_STOP`/`Closing_STOP`**: Stopp-Zustände während einer Bewegung, ausgelöst durch den gegenteiligen Befehl. Deaktivieren `DO_OPEN`/`DO_CLOSE` und stoppen den Timer.
7.  **`Opening_STOP_R`/`Closing_STOP_R`**: Stopp-Zustände während einer Bewegung, ausgelöst durch `RESET`. Führen zum `Unknown`-Zustand.
8.  **`Unknown`**: Fehler- oder unbekannter Zustand. Setzt alle Aktorsignale zurück.

## Anwendungsszenarien
*   **Steuerung pneumatischer Schieber** in Verpackungs-, Förder- oder Sortieranlagen.
*   **Integration in übergeordnete Sequenzer** für Materialfluss-Steuerungen.
*   **Anbindung an Bedienpanels (HMI)**, da strukturierte Daten für Taster, Softkeys und Anzeigen bereitgestellt werden.
*   **Protokollierung und Visualisierung** des Schieberzustands über den `STATE`-String-Ausgang.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren binären Aktor-Bausteinen (z. B. einem einfachen Zylinder-FB) bietet `SchieberControl` eine deutlich höhere Funktionalität:
*   **Vollständige Zustandsmaschine** mit Bewegungs-, End- und Stopp-Zuständen.
*   **Integrierte Zeitsteuerung** für die Bewegung.
*   **Umfangreiche HMI-Schnittstelle** zur Konfiguration von Bedienelementen.
*   **Explizite Behandlung eines "Unbekannt"-Zustands** (`RESET`-Funktionalität).
Er ist spezialisierter und komplexer als ein generischer `E_SR` (Flip-Flop) oder ein einfacher Timer-Baustein, da er diese Funktionalitäten kombiniert und auf die Steuerung eines Schieberantriebs zuschneidet.

## Fazit
Der `SchieberControl` ist ein robust ausgelegter und funktional umfassender Steuerbaustein für Schieber-Antriebe. Seine Stärken liegen in der klaren Zustandslogik, der flexiblen Konfigurierbarkeit der Benutzerschnittstelle und der sauberen Trennung von Steuerlogik und Zeitgeber-Funktionalität durch Adapter. Er eignet sich gut für den Einsatz in mittleren bis komplexen Steuerungsanwendungen, bei denen eine zuverlässige und überwachbare Ansteuerung eines Schiebers erforderlich ist.
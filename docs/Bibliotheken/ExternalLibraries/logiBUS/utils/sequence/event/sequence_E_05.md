# sequence_E_05

<img width="1389" height="390" alt="image" src="https://github.com/user-attachments/assets/6251fda5-cb6c-43dd-b0bf-c6e5e43d5acc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_E_05` ist ein sequenzieller Zustandsautomat, der eine feste Abfolge von fünf Zuständen durchläuft. Der Übergang zwischen den einzelnen Zuständen erfolgt ausschließlich durch externe Ereignisse. Der Baustein ist für Steuerungsaufgaben konzipiert, bei denen eine schrittweise Abarbeitung einer Prozesssequenz erforderlich ist, wie z.B. in Handhabungs- oder Verpackungsanlagen. Jeder aktive Zustand setzt einen eigenen binären Ausgang und bestätigt die Ausführung.

## Schnittstellenstruktur
Der Funktionsblock besitzt eine reine Ereignisschnittstelle. Zustandsübergänge werden durch Eingangsereignisse ausgelöst, und der aktive Zustand wird über Ausgangsereignisse und Datenausgänge signalisiert.

### **Ereignis-Eingänge**
*   `START_S1`: Wechselt vom initialen START-Zustand oder vom Zustand `sState_00` in den ersten Zustand `State_01`.
*   `S1_S2`: Wechselt von `State_01` zu `State_02`.
*   `S2_S3`: Wechselt von `State_02` zu `State_03`.
*   `S3_S4`: Wechselt von `State_03` zu `State_04`.
*   `S4_S5`: Wechselt von `State_04` zu `State_05`.
*   `S5_START`: Wechselt von `State_05` zurück in den inaktiven Zustand `sState_00`.
*   `RESET`: Setzt den Automaten von jedem beliebigen Zustand sofort in den inaktiven Zustand `sState_00` zurück.

### **Ereignis-Ausgänge**
*   `CNF`: Allgemeines Bestätigungsereignis. Wird bei jedem Zustandswechsel ausgelöst und liefert die aktuelle Zustandsnummer `STATE_NR`.
*   `EO_S1`: Wird beim Eintritt in `State_01` ausgelöst und liefert den Wert `DO_S1`.
*   `EO_S2`: Wird beim Eintritt in `State_02` ausgelöst und liefert den Wert `DO_S2`.
*   `EO_S3`: Wird beim Eintritt in `State_03` ausgelöst und liefert den Wert `DO_S3`.
*   `EO_S4`: Wird beim Eintritt in `State_04` ausgelöst und liefert den Wert `DO_S4`.
*   `EO_S5`: Wird beim Eintritt in `State_05` ausgelöst und liefert den Wert `DO_S5`.

### **Daten-Eingänge**
Es sind keine Dateneingänge vorhanden.

### **Daten-Ausgänge**
*   `STATE_NR` (SINT): Numerische Kennung des aktuellen Zustands. START = 0, State_01 = 1, State_02 = 2, ..., State_05 = 5.
*   `DO_S1` (BOOL): Ist `TRUE`, wenn Zustand `State_01` aktiv ist.
*   `DO_S2` (BOOL): Ist `TRUE`, wenn Zustand `State_02` aktiv ist.
*   `DO_S3` (BOOL): Ist `TRUE`, wenn Zustand `State_03` aktiv ist.
*   `DO_S4` (BOOL): Ist `TRUE`, wenn Zustand `State_04` aktiv ist.
*   `DO_S5` (BOOL): Ist `TRUE`, wenn Zustand `State_05` aktiv ist.

### **Adapter**
Es sind keine Adapterschnittstellen vorhanden.

## Funktionsweise
Der FB ist als Basic Function Block (BFB) mit einem Execution Control Chart (ECC) implementiert. Das ECC besteht aus sieben Zuständen: einem initialen `xSTART`, fünf aktiven Zuständen (`sState_01` bis `sState_05`), einem inaktiven Endzustand (`sState_00`) und einem speziellen Reset-Zustand (`sRESET`).

Bei Eintritt in einen aktiven Zustand (z.B. `sState_01`) werden zwei Algorithmen nacheinander ausgeführt:
1.  Ein *Confirmation Step* (z.B. `State_01_C`), der die `STATE_NR` auf die entsprechende Konstante setzt und das `CNF`-Ereignis auslöst.
2.  Ein *Entry Step* (z.B. `State_01_E`), der den zugehörigen binären Ausgang (z.B. `DO_S1`) auf `TRUE` setzt und das entsprechende Ereignis (z.B. `EO_S1`) auslöst.

Beim Verlassen eines aktiven Zustands wird ein *Exit Step* (z.B. `State_01_X`) ausgeführt, der den zugehörigen binären Ausgang auf `FALSE` zurücksetzt. Die Zustandsübergänge werden strikt durch die anliegenden Ereignisseingänge gesteuert. Ein `RESET`-Ereignis führt über den Zwischenzustand `sRESET` dazu, dass alle aktiven Ausgänge (`DO_S1` bis `DO_S5`) deaktiviert werden, bevor der Automat in den inaktiven Zustand `sState_00` wechselt.

## Technische Besonderheiten
*   **Ereignisgesteuerte Transitionen:** Im Gegensatz zu zeit- oder bedingungsgesteuerten Sequenzern erfolgen die Zustandswechsel hier ausschließlich durch externe Ereignisse. Dies ermöglicht eine enge Kopplung an andere Prozessschritte oder Bedieneraktionen.
*   **Explizite Reset-Logik:** Der Reset-Vorgang ist als eigener ECC-Zustand (`sRESET`) modelliert, der sicherstellt, dass beim Zurücksetzen alle fünf Ausgänge (`DO_S1` bis `DO_S5`) ordnungsgemäß deaktiviert werden, unabhängig vom aktuellen Zustand.
*   **Separate Entry/Exit-Aktionen:** Die Logik zum Setzen und Rücksetzen der Ausgänge ist in separate Algorithmen aufgeteilt (E für Entry, X für Exit). Dies fördert eine klare und wartbare Struktur.
*   **Konstanten für Zustandsnummern:** Die Werte für `STATE_NR` werden aus einer importierten Bibliothek (`sequence::State_01`, etc.) bezogen, was die Wiederverwendbarkeit und zentrale Pflege erleichtert.

## Zustandsübersicht
1.  **xSTART:** Initialer Zustand nach dem Start. Wartet auf `START_S1`.
2.  **sState_01:** Erster aktiver Schritt. Setzt `DO_S1=TRUE` und `STATE_NR=1`. Wartet auf `S1_S2` oder `RESET`.
3.  **sState_02:** Zweiter aktiver Schritt. Setzt `DO_S2=TRUE` und `STATE_NR=2`. Wartet auf `S2_S3` oder `RESET`.
4.  **sState_03:** Dritter aktiver Schritt. Setzt `DO_S3=TRUE` und `STATE_NR=3`. Wartet auf `S3_S4` oder `RESET`.
5.  **sState_04:** Vierter aktiver Schritt. Setzt `DO_S4=TRUE` und `STATE_NR=4`. Wartet auf `S4_S5` oder `RESET`.
6.  **sState_05:** Fünfter aktiver Schritt. Setzt `DO_S5=TRUE` und `STATE_NR=5`. Wartet auf `S5_START` oder `RESET`.
7.  **sState_00:** Inaktiver Endzustand. Alle Ausgänge sind `FALSE`, `STATE_NR=0`. Wartet auf `START_S1` für einen neuen Zyklus.
8.  **sRESET:** Temporärer Reset-Zustand. Deaktiviert alle aktiven Ausgänge und wechselt dann zu `sState_00`.

## Anwendungsszenarien
*   **Schrittkette in Handhabungsgeräten:** Steuerung eines Pick-and-Place Roboters (Greifen → Anheben → Bewegen → Absenken → Loslassen), wobei jeder Schritt durch ein Sensorereignis (z.B. "Teil erkannt", "Position erreicht") ausgelöst wird.
*   **Manuelle Bediensequenzen:** Abarbeitung einer vom Bediener vorgegebenen Reihenfolge, z.B. in einer Maschineneinrichtung ("Schritt 1 freigeben" → "Schritt 2 freigeben").
*   **Synchronisation mit übergeordneten Steuerungen:** Die Sequenz dient als Unterprogramm einer Hauptsteuerung, die den Fortschritt über die Ereignisse vorgibt.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einem zyklisch ablaufenden Sequenzer (z.B. `CYCLE_5`), der nach einer festen Zeit automatisch weiter schaltet, verharrt `sequence_E_05` in jedem Zustand, bis das entsprechende Weitereignis eintrifft. Dies macht ihn deterministischer in Bezug auf externe Bedingungen, erfordert aber eine zuverlässige Ereignisgenerierung durch die Peripherie oder übergeordnete Logik. Er ist einfacher und transparenter als ein kompletter Schrittkettenbaustein (SFC) für feste, lineare Abfolgen.

## Fazit
Der `sequence_E_05` ist ein robuster und einfach zu konfigurierender Funktionsblock für ereignisgesteuerte Schrittketten mit fester Länge. Seine klare Trennung von Zustandslogik und Ausgangsaktionen sowie der integrierte Reset-Mechanismus machen ihn zu einer zuverlässigen Komponente für sequentielle Steuerungsaufgaben in 4diac-basierten Automatisierungssystemen. Die fehlende Flexibilität in der Anzahl der Schritte oder der Übergangsbedingungen ist für definierte, lineare Prozesse ein Vorteil in Bezug auf Übersichtlichkeit und Vorhersagbarkeit.

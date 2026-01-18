# E_SREN

```{index} single: E_SREN
```

<img width="1633" height="341" alt="image" src="https://github.com/user-attachments/assets/637ba12a-c1ae-4cc7-a7c5-06b2888347d5" />

* * * * * * * * * *
## Einleitung
Der E_SREN (Event-driven quad-state) ist ein ereignisgesteuerter Funktionsblock, der einen Ausgang mit vier definierten Zuständen steuert. Er reagiert auf verschiedene Eingangsereignisse und setzt seinen Ausgang entsprechend auf einen der vier Zustände: Aktiviert (`SET`), Deaktiviert (`RESET`), Fehler (`ERROR`) oder Keine Aktion (`NONE`). Der Baustein ist besonders für Anwendungen geeignet, in denen ein Signal mehrere Betriebszustände repräsentieren muss, wie z.B. in Überwachungs- oder Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **S (Set):** Setzt den Ausgang `Q` auf `TRUE` und `QB` auf den Zustand `COMMAND_ENABLE`.
*   **R (Reset):** Setzt den Ausgang `Q` auf `FALSE` und `QB` auf den Zustand `COMMAND_DISABLE`.
*   **ERR (Error):** Setzt den Ausgang `Q` auf `FALSE` und `QB` auf den Zustand `STATUS_ERROR`.
*   **NONE:** Setzt den Ausgang `QB` auf den Zustand `COMMAND_NO_ACTION`. Der Ausgang `Q` bleibt unverändert.

### **Ereignis-Ausgänge**
*   **EO (Event Output):** Wird ausgelöst, wenn sich einer der Ausgangswerte (`Q` oder `QB`) geändert hat. Dieses Ereignis wird immer zusammen mit den aktuellen Werten der Datenausgänge `Q` und `QB` gesendet.

### **Daten-Eingänge**
*   Dieser Funktionsblock besitzt keine Daten-Eingänge.

### **Daten-Ausgänge**
*   **Q (BOOL):** Einfacher boolescher Ausgang. Er ist nur `TRUE`, wenn das `S`-Ereignis eintrifft. Er ist `FALSE` bei den Ereignissen `R` und `ERR` und bleibt unverändert bei `NONE`.
*   **QB (BYTE):** Ein Byte-Ausgang, der speziell zur Kodierung von vier Zuständen (2 Bit) dient. Die konkreten Werte (z.B. `COMMAND_ENABLE`) werden aus der importierten Bibliothek `quarter::const::quarter` bezogen.

### **Adapter**
*   Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der E_SREN ist als Basic-FB implementiert und besitzt einen internen Zustandsautomaten (ECC). Der Ausgangszustand ist `START`. Bei Eintreffen eines Eingangsereignisses (`S`, `R`, `ERR`, `NONE`) wechselt der Automat in den entsprechenden Zustand (`SET`, `RESET`, `Error`, `none`). In diesen Zuständen wird der zugehörige Algorithmus ausgeführt, der die Werte für `Q` und `QB` berechnet.

Anschließend prüft eine Bedingung, ob sich der neue Wert von `Q` oder `QB` gegenüber dem zuletzt gespeicherten Wert (`old_Q`, `old_QB`) geändert hat. Falls ja, wechselt der Automat in den Zustand `FireEvent`. Hier wird der Algorithmus `HOLD` ausgeführt, der die aktuellen Ausgangswerte in den internen Variablen speichert, und gleichzeitig das Ausgangsereignis `EO` ausgelöst. Danach kehrt der Automat immer in den `START`-Zustand zurück. Falls sich die Ausgangswerte nicht geändert haben, erfolgt ein direkter Übergang von den Zuständen `SET`, `RESET`, `Error` oder `none` zurück in den `START`-Zustand, ohne dass `EO` ausgelöst wird.

## Technische Besonderheiten
*   **Zustandserkennung:** Der Baustein merkt sich den vorherigen Ausgangszustand in den internen Variablen `old_Q` und `old_QB`. Das Ausgangsereignis `EO` wird nur bei einer tatsächlichen Zustandsänderung generiert, was redundante Ereignisausgaben verhindert.
*   **Bibliotheksabhängigkeit:** Die spezifischen Byte-Werte für den `QB`-Ausgang werden aus der Konstanten-Bibliothek `logiBUS::utils::quarter::const::quarter` importiert. Die korrekte Funktion setzt die Verfügbarkeit dieser Bibliothek voraus.
*   **Vier-Zustands-Logik:** Die Logik des `NONE`-Ereignisses ist speziell: Während `QB` auf `COMMAND_NO_ACTION` gesetzt wird, bleibt der boolesche Ausgang `Q` explizit unverändert.

## Zustandsübersicht
Der ECC (Execution Control Chart) besteht aus sechs Zuständen:
1.  **START:** Initialer und Ruhezustand.
2.  **SET:** Wird bei Ereignis `S` aktiviert. Setzt `Q=TRUE`, `QB=COMMAND_ENABLE`.
3.  **RESET:** Wird bei Ereignis `R` aktiviert. Setzt `Q=FALSE`, `QB=COMMAND_DISABLE`.
4.  **Error:** Wird bei Ereignis `ERR` aktiviert. Setzt `Q=FALSE`, `QB=STATUS_ERROR`.
5.  **none:** Wird bei Ereignis `NONE` aktiviert. Setzt `QB=COMMAND_NO_ACTION`. `Q` bleibt unverändert.
6.  **FireEvent:** Wird nur betreten, wenn sich `Q` oder `QB` geändert haben. Speichert die neuen Werte und löst `EO` aus.

## Anwendungsszenarien
*   **Aktorsteuerung:** Steuerung eines Antriebs mit den Befehlen "Einschalten" (`S`), "Ausschalten" (`R`), "Störung" (`ERR`) und "Manuell/Extern gesteuert" (`NONE`).
*   **Meldesysteme:** Darstellung des Status einer Maschine: "In Betrieb", "Stopp", "Fehler", "Wartung".
*   **Sicherheitsrelevante Steuerungen:** Klare Trennung von normalen Betriebs- (`S`/`R`), Fehler- (`ERR`) und Wartungs-/Override-Zuständen (`NONE`).

## Vergleich mit ähnlichen Bausteinen
*   **E_SR (Bistabile Funktion):** Der klassische Set-Reset-Flipflop kennt nur zwei stabile Zustände (`TRUE`/`FALSE`). Der E_SREN erweitert dieses Konzept um zwei weitere Zustände (`ERROR`, `NO_ACTION`), die über ein dediziertes Byte (`QB`) kodiert werden.
*   **E_D_FF (D-Flipflop):** Übernimmt einen Datenwert bei einem Takt-Ereignis. Der E_SREN ist ereignisgesteuert (vier verschiedene Ereignisse) und hat keinen separaten Dateneingang. Die "Daten" sind in den auslösenden Ereignissen implizit enthalten.

## Fazit
Der E_SREN ist ein spezialisierter, ereignisgesteuerter Funktionsblock für Anwendungen, die mehr als zwei diskrete Zustände benötigen. Durch die Kombination eines einfachen booleschen Signals (`Q`) mit einem mehrwertigen Byte-Signal (`QB`) und der intelligenten, änderungsbasierten Ereignisausgabe (`EO`) bietet er eine effiziente und übersichtliche Lösung für komplexe Zustandssteuerungen. Seine Stärke liegt in der klaren Semantik der vier Eingangsereignisse und der zuverlässigen Vermeidung von redundanten Ausgabeereignissen.

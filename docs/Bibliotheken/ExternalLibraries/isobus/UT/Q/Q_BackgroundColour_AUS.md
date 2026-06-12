# Q_BackgroundColour_AUS


![Q_BackgroundColour_AUS](./Q_BackgroundColour_AUS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **Q_BackgroundColour_AUS** dient zum Ändern der Hintergrundfarbe eines Objekts im ISOBUS Virtual Terminal (VT). Er kapselt die entsprechende Kommando-Schnittstelle gemäß ISO 11783-6 (Part 6 – F.20).  
Der Baustein wird über einen Socket mit der neuen Farbe versorgt und gibt über einen Plug die vorherige Farbe zurück. Die eigentliche Farbänderung wird durch den internen Baustein `Q_BackgroundColour` ausgeführt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Typ   | Kommentar                          | Mit Variablen       |
|--------|-------|------------------------------------|---------------------|
| `INIT` | EInit | Service Initialisierung            | `u16ObjId`          |

### **Ereignis-Ausgänge**

| Name    | Typ   | Kommentar                              | Mit Variablen               |
|---------|-------|----------------------------------------|-----------------------------|
| `INITO` | EInit | Initialisierungsbestätigung            | –                           |
| `CNF`   | Event | Bestätigung des angeforderten Dienstes | `STATUS`, `s16result`       |

### **Daten-Eingänge**

| Name        | Datentyp | Initialwert     | Kommentar                          |
|-------------|----------|-----------------|------------------------------------|
| `u16ObjId`  | UINT     | `ID_NULL`       | Objekt-ID des zu ändernden Objekts |

### **Daten-Ausgänge**

| Name        | Datentyp | Kommentar                                              |
|-------------|----------|--------------------------------------------------------|
| `STATUS`    | STRING   | Dienststatus (z. B. Fehlertext oder „OK“)              |
| `s16result` | INT      | Rückgabewert (siehe Beschreibung – Fehlercodes)        |

### **Adapter**

* **Socket** `u8Colour`  
  Typ: `adapter::types::unidirectional::AUS`  
  Liefert die neue Hintergrundfarbe (gemäß ISO 11783-6, A.3 VT Standard-Farbpalette).  
  Über den Adapter wird sowohl das Ereignis `E1` (zur Auslösung des Farbwechsels) als auch der Datenwert `D1` (Farbwert) bereitgestellt.

* **Plug** `u8OldColour`  
  Typ: `adapter::types::unidirectional::AUS`  
  Gibt die vorherige Hintergrundfarbe zurück, nachdem der Änderungsbefehl ausgeführt wurde.  
  Das Ereignis `E1` signalisiert, dass der Wert gültig ist, der Datenwert `D1` enthält die alte Farbe.

## Funktionsweise

1. **Initialisierung**  
   Ein Ereignis `INIT` startet den Baustein. Die übergebene Objekt-ID (`u16ObjId`) wird an den internen FB `Q_BackgroundColour` weitergeleitet und dort initialisiert. Nach erfolgreicher Initialisierung wird `INITO` ausgegeben.

2. **Farbänderung auslösen**  
   Sobald am Socket `u8Colour` ein Ereignis eintrifft (über den Adapter-Pfad `E1`), wird der interne Baustein mit `REQ` angestoßen. Der Farbwert (`u8Colour.D1`) wird an `Q_BackgroundColour.u8Colour` übergeben.

3. **Rückmeldung**  
   Nach Abschluss des Kommandos sendet der interne Baustein ein `CNF`-Ereignis.  
   * Die Ausgänge `STATUS` und `s16result` werden entsprechend gesetzt und sind am Ereignisausgang `CNF` gültig.  
   * Gleichzeitig wird über den Plug `u8OldColour` der alte Farbwert (Daten `D1`) und ein Bestätigungsereignis (`E1`) ausgegeben.

## Technische Besonderheiten

* Der Baustein implementiert das Kommando „Change Background Colour“ nach ISO 11783-6, Abschnitt F.20.  
* Die Farbwerte entsprechen der VT-Standard-Farbpalette aus Anhang A.3 der Norm.  
* Mögliche Rückgabewerte (`s16result`) sind:
  * `VT_E_NO_ERR (0)` – Erfolg
  * `VT_E_OVERFLOW (-6)` – Pufferüberlauf
  * `VT_E_NOACT (-8)` – Kommando im aktuellen Zustand nicht möglich
  * `VT_E_NO_INSTANCE (-21)` – Kein VT-Client verfügbar
  * `VT_E_ISO_INSTANCE_INVALID (-129)` – Ungültige Verbindungskennung
  * `VT_E_HANDLE_INVALID (-128)` – Ungültiger Handle
  * `VT_E_NOT_ALIVE (-130)` – VT nicht erreichbar
* Der Baustein nutzt einen unidirektionalen Adapter (`AUS`), der Ereignis- und Datenkanal kombiniert – dies reduziert die Anzahl der Schnittstellen.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten auf der obersten Ebene, doch das Zusammenspiel mit `INIT`, `REQ` (via Adapter) und `CNF` ergibt folgende implizite Zustände:

1. **IDLE** – Warten auf `INIT` oder auf ein Ereignis am Socket `u8Colour`.  
2. **INIT** – Nach `INIT` läuft die Initialisierung des internen Bausteins.  
3. **READY** – Nach `INITO` ist der FB bereit, Farbänderungen entgegenzunehmen.  
4. **BUSY** – Während der Ausführung des Farbänderungskommandos (nach `REQ`).  
5. **DONE** – Nach `CNF` kann der nächste Befehl verarbeitet werden.

## Anwendungsszenarien

* **ISOBUS Virtual Terminal**  
  Ändern der Hintergrundfarbe eines grafischen Objekts (z. B. Button, Gruppe, Softkey) auf dem VT-Bildschirm in einer landwirtschaftlichen Steuerung.
* **HMI-Anpassung**  
  Reaktion auf Benutzereingaben oder Systemzustände, um die optische Darstellung dynamisch anzupassen (z. B. Alarmfarben, Markierung aktiver Elemente).
* **Rücklesen der alten Farbe**  
  Der Plug `u8OldColour` ermöglicht es, den vorherigen Farbwert zu speichern oder für eine spätere Wiederherstellung zu nutzen.

## Vergleich mit ähnlichen Bausteinen

* **`Q_BackgroundColour`** (ohne `_AUS`):  
  Bietet die gleiche Kernfunktion, jedoch meist mit einzelnen Ereignis-/Datenanschlüssen statt gekapselter Adapter. Der `_AUS`-Baustein vereinfacht die Verbindung zu anderen Bausteinen, die ebenfalls mit AUS-Adaptern arbeiten.
* **`Q_Colour`** oder **`Q_ForegroundColour`**:  
  Ändern andere Farbeigenschaften (Vordergrund, Vollfarbe) und verwenden ähnliche Rückgabewerte und Statusmechanismen.
* **`Command_ChangeColour`** (allgemeiner):  
  Könnte mehrere Farbparameter gleichzeitig ändern, während `Q_BackgroundColour_AUS` auf Hintergrundfarben spezialisiert ist.

## Fazit

Der Funktionsblock `Q_BackgroundColour_AUS` bietet eine standardkonforme, kompakte Schnittstelle zum Ändern von Hintergrundfarben in einem ISOBUS-VT. Durch den Einsatz des unidirektionalen Adapters wird die Anbindung an andere Komponenten erleichtert und die Übersichtlichkeit erhöht. Die dokumentierten Fehlercodes und die saubere Trennung von Initialisierung und Dienstausführung machen ihn zu einem zuverlässigen Baustein für dynamische HMI-Anpassungen in landwirtschaftlichen Steuerungssystemen.
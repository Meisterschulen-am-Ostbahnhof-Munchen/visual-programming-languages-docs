# StringValue_IWS


![StringValue_IWS](./StringValue_IWS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **StringValue_IWS** ist ein Service-Interface-Funktionsblock (SIFB), der für den Empfang breiter Zeichenketten (*Wide String*, `WSTRING`) als Eingabedaten aus einer ressourcenseitigen Quelle (z. B. Hardware‑Schnittstelle, Bussystem) zuständig ist. Er stellt eine standardisierte Schnittstelle zur Verfügung, um Initialisierung und zyklische/anforderungsgesteuerte Datenabrufe sowie asynchrone Indikationen zu verwalten. Der Baustein ist typischerweise in ISOBUS-basierten Steuerungsumgebungen oder anderen Feldbussystemen anzutreffen, die Unicode‑kodierte Textdaten verarbeiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar | Mitgeführte Daten |
|----------|-----------|-------------------|
| `INIT`   | Service-Initialisierung | `QI`, `PARAMS`, `u16ObjId` |
| `REQ`    | Service-Anforderung     | `QI` |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar | Mitgeführte Daten |
|----------|-----------|-------------------|
| `INITO`  | Bestätigung der Initialisierung | `QO`, `STATUS` |
| `CNF`    | Bestätigung der angeforderten Aktion | `QO`, `STATUS`, `IN` |
| `IND`    | Asynchrone Indikation von der Ressource | `QO`, `STATUS`, `IN` |

### **Daten-Eingänge**

| Name      | Typ      | Initialwert | Kommentar |
|-----------|----------|-------------|-----------|
| `QI`      | `BOOL`   | –           | Ereigniseingangs-Qualifier |
| `PARAMS`  | `STRING` | –           | Dienstparameter (z. B. Port-/Gerätekonfiguration) |
| `u16ObjId`| `UINT`   | `ID_NULL`   | Objekt‑ID zur Identifikation der Datenquelle |

### **Daten-Ausgänge**

| Name     | Typ       | Kommentar |
|----------|-----------|-----------|
| `QO`     | `BOOL`    | Ereignisausgangs-Qualifier |
| `STATUS` | `STRING`  | Status- oder Fehlermeldung |
| `IN`     | `WSTRING` | Empfangene Eingabedaten (breite Zeichenkette) |

### **Adapter**

Keine.

## Funktionsweise

Der `StringValue_IWS` folgt dem typischen Verhalten eines Service-Interface-Funktionsblocks:

1. **Initialisierung (`INIT` → `INITO`)**  
   Durch Auslösen des `INIT`-Ereignisses wird der Dienst gestartet. Der Qualifier `QI` bestimmt, ob die Initialisierung aktiv (`TRUE`) oder deaktivierend (`FALSE`) ist. Mit `PARAMS` werden notwendige Konfigurationsparameter übergeben (z. B. Busadresse, Protokoll‑Optionen). Die Objekt-ID `u16ObjId` legt fest, welche Datenquelle (z. B. ein bestimmtes ISOBUS‑Objekt) angesprochen werden soll. Nach erfolgreicher Initialisierung wird `INITO` ausgegeben; `QO` und `STATUS` geben den Ausgangszustand an.

2. **Anforderung (`REQ` → `CNF`)**  
   Mit dem `REQ`-Ereignis wird eine explizite Datenabfrage ausgelöst. Der Baustein holt (z. B. über einen Treiber) einen neuen Wert vom angeschlossenen Gerät. Die Antwort wird über den Ausgang `IN` (als `WSTRING`) und den Status `STATUS` bereitgestellt. Gleichzeitig wird das `CNF`-Ereignis gesendet.

3. **Asynchrone Indikation (`IND`)**  
   Falls die Ressource unaufgefordert neue Daten liefert (z. B. bei Änderung einer Eingabe), wird das `IND`-Ereignis ausgelöst. `IN` enthält dann die aktuellen Daten, `STATUS` den zugehörigen Zustand. Dieser Ausgang kann parallel zum `CNF`-Ereignis genutzt werden.

Die Ereignisausgänge `QO` liefern immer den aktuellen Qualifier‑Wert (in der Regel Übernahme von `QI` bei erfolgreicher Operation, sonst `FALSE`). Der Status `STATUS` enthält menschenlesbare Fehler‑ oder Erfolgsmeldungen.

## Technische Besonderheiten

- **Breite Zeichenketten (`WSTRING`)**  
  Der Baustein verwendet `WSTRING` (UTF‑16‑kodiert), um internationale Zeichensätze, Sonderzeichen und Emojis korrekt zu übertragen. Dies ist besonders in der ISOBUS‑Landtechnik wichtig, wenn z. B. Bedienterminals Unicode‑Texte anzeigen.

- **Objekt‑ID `u16ObjId`**  
  Der Initialwert `ID_NULL` wird aus der importierten Konstanten `isobus::UT::Q::const::IDs::ID_NULL` übernommen. Eine gültige Objekt‑ID muss vor der `INIT`‑Aktion gesetzt werden, um die korrekte Datenquelle zu adressieren.

- **Service-Interface-Charakter**  
  Der Baustein ist als SIFB realisiert und erwartet eine ressourcenseitige Implementierung (Treiber). Die eigentliche Kommunikation mit der Hardware oder dem Bussystem erfolgt außerhalb des Funktionsblocks und wird über die Ereignis‑/Datenschnittstellen abstrahiert.

- **Verwendung von `eclipse4diac::core::TypeHash`**  
  Das Attribut dient der Laufzeit-Identifikation des Typs und wird für dynamische Funktionsblock‑Instanzen verwendet.

## Zustandsübersicht

Eine explizite Zustandsmaschine ist im XML nicht definiert, jedoch ergibt sich aus der Semantik des SIFB folgender impliziter Ablauf:

1. **IDLE** – Warten auf `INIT` oder erste `REQ`.
2. **INIT** – Initialisierungsphase, nach erfolgreicher Ausführung Wechsel in **READY**.
3. **READY** – Bereit für `REQ` oder `IND`. Bei `REQ` kurzzeitig in **BUSY**, dann zurück zu **READY**.
4. **INDICATION** – Asynchrone Datenindikation, nach Verarbeitung Rückkehr zu **READY**.
5. **ERROR** – Bei Fehlern (z. B. Kommunikationsabbruch) wird `STATUS` gesetzt und der Block verharrt, bis ein erneutes `INIT` (mit `QI=FALSE` ggf. als Reset) erfolgt.

## Anwendungsszenarien

- **ISOBUS‑Terminal (UT) – Eingabe von Unicode-Text**  
  Empfang von Benutzereingaben wie Maschinenbezeichnungen, Adressen oder Diagnosetexten von einem Bedienterminal über den ISOBUS.

- **Universal‑Interface für Zeicheneingabe**  
  Anbindung externer Sensoren oder Eingabegeräte, die Zeichenketten im UTF‑16‑Format liefern (z. B. Barcode‑Scanner, RFID‑Leser mit Textausgabe).

- **Diagnose‑ und Logging‑Schnittstelle**  
  Aufnahme von Statusmeldungen, Warnungen oder Fehlertexten aus einer Steuerungseinheit zur Weiterleitung an ein HMI oder eine Cloud‑Anbindung.

## Vergleich mit ähnlichen Bausteinen

| Funktionsblock | Typ   | Unterschied |
|----------------|-------|-------------|
| `StringValue_IWS` (vorliegend) | `WSTRING` | Empfängt UTF‑16‑kodierte Zeichenketten. |
| `StringValue_IWS` (normale Variante) | `STRING` | Empfängt ASCII‑/UTF‑8‑Strings, geringere Zeichenabdeckung. |
| `AnalogInput_IWS` | `REAL` | Empfängt analoge Messwerte, keine Zeichenketten. |
| `EventInput_IWS` | – | Nur Ereignis‑Schnittstelle, keine Daten. |

Der `StringValue_IWS` ist speziell für die Verarbeitung von Unicode‑Text konzipiert und eignet sich daher für internationale oder zeichensatzlastige Anwendungen.

## Fazit

Der `StringValue_IWS` ist ein essenzieller Baustein für die Integration von Text‑Eingaben in IEC 61499‑basierten Steuerungssystemen, insbesondere im ISOBUS‑Umfeld. Seine Unterstützung von `WSTRING`, die saubere Trennung von Initialisierung, Anforderung und asynchroner Indikation sowie die flexible Objekt‑ID‑Adressierung machen ihn zu einer robusten Lösung für den Empfang breiter Zeichenketten aus verteilten Ressourcen.
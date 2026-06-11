# Q_SetAudioVolume_AUS


![Q_SetAudioVolume_AUS](./Q_SetAudioVolume_AUS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock Q_SetAudioVolume_AUS ist ein zusammengesetzter Baustein (Composite FB), der den Befehl „SetAudioVolume“ gemäß ISO 11783‑6 auf einem Virtual Terminal (VT) ausführt. Er kapselt den Basisbaustein Q_SetAudioVolume und stellt eine adapterbasierte Schnittstelle zur Verfügung, um die Lautstärke zu setzen und den alten Wert zurückzulesen. Der FB initialisiert sich über den Ereigniseingang INIT und bestätigt dies mit INITO. Anschließend kann über den u8Volume-Adapter eine neue Lautstärke übergeben werden, woraufhin der Befehl ausgelöst und das Ergebnis über CNF mit STATUS und s16result ausgegeben wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **INIT** (EInit): Dienstinitialisierung. Löst die Initialisierung des internen Bausteins aus.

### **Ereignis-Ausgänge**
- **INITO** (EInit): Bestätigung der erfolgreichen Initialisierung.
- **CNF** (Event): Bestätigung des angeforderten Dienstes. Wird nach dem Setzen der Lautstärke ausgegeben. Enthält die Ausgabedaten STATUS und s16result.

### **Daten-Eingänge**
Der FB besitzt keine direkten Daten-Eingänge. Die Eingabe der Lautstärke erfolgt über den Adapter u8Volume.

### **Daten-Ausgänge**
- **STATUS** (STRING): Service-Statusmeldung.
- **s16result** (INT): Rückgabewert des Befehls. Mögliche Werte:
  - 0 (VT_E_NO_ERR): Erfolg.
  - -6 (VT_E_OVERFLOW): Pufferüberlauf.
  - -8 (VT_E_NOACT): Befehl im aktuellen Zustand nicht möglich.
  - -21 (VT_E_NO_INSTANCE): Kein VT-Client verfügbar.
  - -129 (VT_E_ISO_INSTANCE_INVALID): Verbindungsinstanz ungültig.
  - -128 (VT_E_HANDLE_INVALID): Handle ungültig.
  - -130 (VT_E_NOT_ALIVE): VT nicht aktiv.

### **Adapter**
- **u8Volume** (Socket): Unidirektionaler Adapter vom Typ AUS. Empfängt die gewünschte Lautstärke als Wert zwischen 0 und 100 %.
- **u8OldVolume** (Plug): Unidirektionaler Adapter vom Typ AUS. Gibt die vor dem Befehl gültige Lautstärke (0–100 %) aus.

## Funktionsweise
Nach dem Start wird der FB über den INIT-Eingang initialisiert. Der interne Baustein Q_SetAudioVolume wird bereitgemacht und INITO signalisiert die Bereitschaft. Sobald ein neuer Lautstärkewert über den u8Volume-Adapter anliegt (Ereignis E1 des Adapters), wird der Befehl zum Ändern der Lautstärke an das VT gesendet. Nach Abschluss des Vorgangs wird CNF ausgelöst, und die Ausgabevariablen STATUS und s16result enthalten das Ergebnis. Parallel wird der vorherige Lautstärkewert über den Adapter u8OldVolume ausgegeben, sodass eine externe Logik den alten Wert auslesen kann.

Die möglichen Fehlercodes entsprechen den ISO 11783‑6‑Definitionen und decken typische VT-Fehlersituationen ab.

## Technische Besonderheiten
- Der FB ist als Composite-Baustein realisiert, der den Basisfunktionsblock Q_SetAudioVolume aus der isobus-Bibliothek verwendet.
- Die Schnittstelle nutzt ausschließlich Adapter für die Datenübergabe, wodurch eine lose Kopplung und flexible Verdrahtung erreicht wird.
- Die Adapter sind vom Typ „unidirectional::AUS“ und ermöglichen eine ereignisgesteuerte Datenweitergabe.
- Der FB ist für den Einsatz in ISOBUS-Systemen nach ISO 11783‑6 ausgelegt.

## Zustandsübersicht
Da es sich um einen zusammengesetzten Baustein mit internem FB handelt, ist keine explizite Zustandsmaschine auf oberster Ebene vorhanden. Der FB durchläuft folgende Phasen:
1. Initialisierung (INIT empfangen → INITO senden)
2. Bereit (wartet auf Lautstärkeänderung über u8Volume-Adapter)
3. Verarbeitung (interner Befehl wird ausgeführt)
4. Ergebnisausgabe (CNF mit STATUS/s16result)

Ein detaillierter Zustandsautomat ist im internen Baustein Q_SetAudioVolume implementiert.

## Anwendungsszenarien
- Landwirtschaftliche Maschinensteuerung: Anpassung der Lautstärke von Sprachausgaben oder Warntönen des Virtual Terminals.
- Integration in ISOBUS-konforme Applikationen, die über das Bedienterminal die Audioeinstellungen verändern.
- Kombination mit anderen VT-Befehlsbausteinen wie Q_SelectAudioOutput, Q_Beep etc.

## Vergleich mit ähnlichen Bausteinen
Der Baustein Q_SetAudioVolume_AUS unterscheidet sich von einem direkten Q_SetAudioVolume durch die Verwendung von Adaptern zur Datenübergabe. Während Q_SetAudioVolume möglicherweise direkte Daten-Eingänge (z. B. u8Volume als VarDeclaration) besitzt, erlaubt die Adaptervariante eine entkoppelte, ereignisgesteuerte Kommunikation. Ähnliche Adapter-Bausteine existieren für andere VT-Befehle, sodass ein einheitliches Entwurfsmuster entsteht.

## Fazit
Q_SetAudioVolume_AUS ist ein spezialisierter Funktionsblock zur Lautstärkeregelung eines ISOBUS-VT. Durch die adapterbasierte Schnittstelle wird eine klare Trennung von Steuerungs- und Datenebene erreicht. Der Baustein liefert vollständige Rückmeldungen über den Erfolg des Befehls und eignet sich für den zuverlässigen Einsatz in landwirtschaftlichen Steuerungen.
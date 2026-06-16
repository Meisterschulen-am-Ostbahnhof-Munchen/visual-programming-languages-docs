# DWORDS_TO_ARR08B


![DWORDS_TO_ARR08B](./DWORDS_TO_ARR08B.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **DWORDS_TO_ARR08B** wandelt zwei 32‑Bit‑DWORD-Werte in ein Array von acht Bytes (BYTE) um. Die Konvertierung erfolgt im Little‑Endian‑Format (Intel‑Standard), d. h. das niederwertigste Byte eines DWORDs wird an die kleinste Indexposition des Ausgangsarrays geschrieben. Der Baustein ist für den Einsatz auf PC‑basierten Steuerungen (z. B. Beckhoff, Wago, B&R, Raspberry Pi) optimiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Konvertierung. Die aktuellen Werte von `IN_00` und `IN_01` werden eingelesen. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Wird gesendet, sobald die Ausgabe `OUT` aktualisiert wurde. |

### **Daten-Eingänge**

| Variable | Typ    | Beschreibung      |
|----------|--------|-------------------|
| `IN_00`  | DWORD  | Erstes 32‑Bit‑Wort (niederwertig). |
| `IN_01`  | DWORD  | Zweites 32‑Bit‑Wort (höherwertig). |

### **Daten-Ausgänge**

| Variable | Typ               | Beschreibung                                          |
|----------|-------------------|-------------------------------------------------------|
| `OUT`    | ARRAY[0..7] OF BYTE| Ausgabearray mit 8 Bytes (Bytes 0–3 aus `IN_00`, Bytes 4–7 aus `IN_01`). |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei einem positiven Flanke am Ereigniseingang `REQ` wird die folgende Logik ausgeführt:
1. Die beiden Eingangs‑DWORDs `IN_00` und `IN_01` werden Byte für Byte ausgelesen.
2. Dabei kommen die systeminternen Byte‑Zugriffe (z. B. `IN_00.%B0` für das niederwertigste Byte) zum Einsatz.
3. Die Bytes werden in **Little‑Endian‑Reihenfolge** in das Ausgangsarray `OUT` kopiert:
   - `OUT[0]` ← niederwertigstes Byte von `IN_00`
   - `OUT[1]` ← zweites Byte von `IN_00`
   - `OUT[2]` ← drittes Byte von `IN_00`
   - `OUT[3]` ← höchstwertiges Byte von `IN_00`
   - `OUT[4]` ← niederwertigstes Byte von `IN_01`
   - `OUT[5]` ← zweites Byte von `IN_01`
   - `OUT[6]` ← drittes Byte von `IN_01`
   - `OUT[7]` ← höchstwertiges Byte von `IN_01`
4. Nach Abschluss der Zuweisungen wird das Ereignis `CNF` gesendet.

## Technische Besonderheiten
- Die Byte‑Reihenfolge folgt dem **Little‑Endian‑Format** (Intel‑Standard), das auf den meisten PC‑basierten Steuerungen (Windows‑basierte Systeme, Raspberry Pi) nativ verwendet wird.
- Der Baustein ist als **strukturierter Text (ST)** implementiert und benötigt keine Zustandsmaschine – die Verarbeitung erfolgt linear bei jedem `REQ`.
- Das im ST‑Code verwendete Paket `logiBUS::utils::conversion::arr::reversing` deutet auf eine wiederverwendbare Bibliothek für Konvertierungen hin.

## Zustandsübersicht
Der Funktionsblock besitzt keine eigene Zustandsmaschine. Er führt bei jedem `REQ`‑Ereignis eine einmalige, deterministische Berechnung durch und signalisiert die Fertigstellung mit `CNF`. Es gibt keine internen Speicherzustände, die über mehrere Aufrufe hinweg erhalten bleiben.

## Anwendungsszenarien
- **Datenprotokoll‑Aufbereitung**: Umwandlung von Steuerungsdaten (z. B. Positionswerte, Timer‑Zähler), die als zwei DWORDs vorliegen, in ein Byte‑Array für die serielle Übertragung (RS‑232, CAN, Ethernet).
- **Kommunikation mit Endian‑empfindlichen Geräten**: Sicherstellung der korrekten Byte‑Reihenfolge beim Austausch mit Sensoren oder Aktoren, die Little‑Endian erwarten.
- **Speicher‑Abbildung / Union‑Ersatz**: In Sprachen ohne Union‑Typen dient der Baustein als portable Methode, um DWORD‑Werte byteweise zu zerlegen.

## Vergleich mit ähnlichen Bausteinen
- **WORD_TO_ARR04B**: Konvertiert ein WORD in ein 4‑Byte‑Array – hier wird der gleiche Ansatz für zwei DWORDs erweitert.
- **DWORDS_TO_ARR08B_BIGENDIAN**: Alternativbaustein für Big‑Endian‑Systeme (Motorola‑Standard) mit umgekehrter Byte‑Reihenfolge.
- **SWAP_BYTES**: Tauscht die Bytes eines DWORDs, liefert aber kein Array. Der vorliegende Baustein erzeugt direkt das komplette 8‑Byte‑Array.

## Fazit
Der Funktionsblock `DWORDS_TO_ARR08B` bietet eine einfache, effiziente Möglichkeit, zwei DWORDs im Little‑Endian‑Format in ein Byte‑Array zusammenzuführen. Seine konsequente Ausrichtung auf PC‑basierte Steuerungen und die klare, wartbare ST‑Implementierung machen ihn zu einem zuverlässigen Werkzeug für die Datenkonvertierung in der Automatisierungstechnik.
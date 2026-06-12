# AX_TO_AS


![AX_TO_AS](./AX_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AX_TO_AS` ist ein Composite-FB, der einen BOOL-Adapter (Typ AX) in einen SINT-Adapter (Typ AS) umwandelt. Er kapselt die Konvertierung eines binären Signals in einen vorzeichenbehafteten 8‑Bit‑Wert und stellt diese über eine standardisierte Adapterschnittstelle bereit.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine separaten Ereignis-Eingänge; die Ereignissteuerung erfolgt über den AX_IN-Adapter (siehe Adapter).

### **Ereignis-Ausgänge**
Keine separaten Ereignis-Ausgänge; die Ereignisausgabe erfolgt über den AS_OUT-Adapter (siehe Adapter).

### **Daten-Eingänge**
Keine separaten Daten-Eingänge; die Datenübergabe erfolgt über den AX_IN-Adapter (siehe Adapter).

### **Daten-Ausgänge**
Keine separaten Daten-Ausgänge; die Datenausgabe erfolgt über den AS_OUT-Adapter (siehe Adapter).

### **Adapter**
- **AX_IN** (Socket):  
  Typ `adapter::types::unidirectional::AX` (BOOL).  
  Stellt das binäre Eingangssignal über den Ereignis-Port `E1` und den Daten-Port `D1` bereit.
- **AS_OUT** (Plug):  
  Typ `adapter::types::unidirectional::AS` (SINT).  
  Gibt das konvertierte SINT-Signal über den Ereignis-Port `E1` und den Daten-Port `D1` aus.

## Funktionsweise
Der FB besitzt ein internes Netzwerk, das aus einer Instanz des Standardbausteins `F_BOOL_TO_SINT` besteht.  
1. Ein eingehendes Ereignis am AX_IN‑Adapter (`E1`) triggert die Konvertierung.
2. Der Datenwert von `AX_IN.D1` (BOOL) wird an den Eingang `IN` des Konvertierungsbausteins übergeben.
3. Der Konvertierungsbaustein wandelt den BOOL-Wert in einen SINT-Wert um (`TRUE` → 1, `FALSE` → 0).
4. Das Ergebnis wird am Ausgang `OUT` bereitgestellt und an den AS_OUT‑Adapter (`D1`) weitergeleitet.
5. Ein Bestätigungsereignis wird über `AS_OUT.E1` ausgegeben.

## Technische Besonderheiten
- **Composite‑Struktur**: Der FB ist als Composition realisiert, wodurch die interne Logik transparent und wiederverwendbar ist.
- **Standard‑Konvertierung**: Verwendet den genormten FB `iec61131::conversion::F_BOOL_TO_SINT` aus der IEC‑61131‑Bibliothek.
- **Adapter‑Schnittstelle**: Die Ein‑ und Ausgabe erfolgt ausschließlich über unidirektionale Adapter (Sockets/Plugs), was eine modulare Verbindung in Adapter‑basierten Architekturen ermöglicht.

## Zustandsübersicht
Der FB besitzt keine explizit modellierten Zustände. Das Verhalten ist rein ereignisgesteuert: Jedes Ereignis am Eingangsadapter löst eine Konvertierung aus, nach deren Abschluss ein Ausgangsereignis gesendet wird.

## Anwendungsszenarien
- **Binäre Sensoranbindung**: Ein binärer Sensor (z. B. Endschalter) wird über einen AX‑Adapter eingelesen und als SINT‑Wert an eine Steuerung weitergegeben.
- **Protokollanpassung**: In Systemen, die SINT‑basierte Adapter erfordern, können vorhandene BOOL‑Adapter ohne zusätzliche Codierung angebunden werden.
- **Testumgebungen**: Einfaches Umschalten zwischen BOOL‑ und SINT‑Signalen zur Überprüfung von Adapter‑Kommunikationswegen.

## Vergleich mit ähnlichen Bausteinen
- **Direkte Konvertierungen (`F_BOOL_TO_SINT`)**: Diese arbeiten auf Datenebene ohne Adapter. Der `AX_TO_AS` kapselt die Konvertierung in eine adapterbasierte Schnittstelle und ist daher leichter in Adapter‑Netzwerke integrierbar.
- **Andere Adapterkonverter (z. B. `AS_TO_AX`)**: Bilden die umgekehrte Richtung ab; `AX_TO_AS` ergänzt diese als Gegenstück.

## Fazit
Der `AX_TO_AS` ist ein einfacher, aber nützlicher Composite‑FB für die Umwandlung von BOOL‑Adapter‑Signalen in SINT‑Adapter‑Signale. Durch die Verwendung eines standardisierten Konvertierungsbausteins und der Adapter‑Technologie lässt er sich flexibel in bestehende 4diac‑Projekte einfügen und trägt zur sauberen Trennung von Signaltypen bei.
# SET_UDINT


![SET_UDINT](./SET_UDINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_UDINT** dient dazu, einen Wert vom Dateneingang `IN` auf die InOut-Variable `OUT` zu schreiben. Der Vorgang wird durch ein Ereignis am Eingang `REQ` ausgelöst und nach erfolgreicher Zuweisung wird der Ausgang `CNF` aktiviert. Der Baustein ist speziell für den UDINT-Datentyp ausgelegt und ermöglicht so eine effiziente und typsichere Datenübergabe an eine gemeinsame Variable.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ` | Event | Normaler Ausführungsauftrag; triggert das Schreiben des Eingangswertes auf die Ausgangsvariable. |

*Mit `REQ` verknüpfte Daten:* `IN`, `OUT`

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `CNF` | Event | Bestätigung der Ausführung; wird ausgegeben, sobald der Wert erfolgreich zugewiesen wurde. |

*Mit `CNF` verknüpfte Daten:* `OUT`

### **Daten-Eingänge**

| Bezeichner | Datentyp | Initialwert | Kommentar |
|------------|----------|-------------|-----------|
| `IN` | UDINT | 0 | Wert, der auf die Zielvariable geschrieben werden soll. |
| `OUT` (InOut) | UDINT | 0 | Zielvariable, die sowohl als Eingang (lesbar) als auch als Ausgang (beschreibbar) fungiert. |

### **Daten-Ausgänge**

| Bezeichner | Datentyp | Kommentar |
|------------|----------|-----------|
| `OUT` (InOut) | UDINT | Dieselbe Variable wie am Eingang; nach der Ausführung enthält sie den Wert von `IN`. |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock arbeitet sehr einfach:
1. Ein Ereignis am Eingang `REQ` startet die Verarbeitung.
2. Der im Algorithmus `REQ` implementierte ST-Code führt die Zuweisung `OUT := IN;` aus.
3. Nach der Zuweisung wird das Ereignis am Ausgang `CNF` gesendet, um den erfolgreichen Abschluss zu signalisieren.

Die InOut-Variable `OUT` ist dabei sowohl lesbar als auch schreibbar. Der zugewiesene Wert bleibt so lange erhalten, bis ein erneuter `REQ` einen neuen Wert zuweist oder die Variable von außen verändert wird.

## Technische Besonderheiten
- **Verwendung einer InOut-Variable**: `OUT` ist als InOut deklariert. Dadurch kann der Baustein direkt auf eine externe Variable zugreifen und sie ändern, ohne dass ein eigener Datenausgang notwendig ist. Der Wert ist nach dem Schreibvorgang sowohl innerhalb als auch außerhalb des Bausteins sichtbar.
- **Einfache Logik**: Kein Zwischenspeicher, keine Verzögerungen – der Vorgang ist atomar und erfolgt in einem einzigen Schritt.
- **Typbindung**: Der Baustein ist ausschließlich für den Typ `UDINT` (unsigned 32‑Bit Integer) definiert, was typsichere Verwendung garantiert.

## Zustandsübersicht
Der Baustein enthält einen einzigen Zustand `REQ` (Ereignisverarbeitung):

| Zustand | Aktion | Ausgangsereignis |
|---------|--------|------------------|
| `REQ` | Führe Algorithmus `REQ` aus (OUT := IN) | CNF |

Nach Ausführung von `CNF` kehrt der Baustein in den Grundzustand zurück und wartet auf das nächste `REQ`-Ereignis.

## Anwendungsszenarien
- **Initialisierung von Variablen**: Setzen eines UDINT-Wertes auf einen vorgegebenen Startwert zur Laufzeit.
- **Steuerung von Parametern**: Überschreiben von Konfigurationswerten in einer laufenden Anwendung (z. B. Sollwerte, Zählerstände).
- **Datenweitergabe zwischen Logikbausteinen**: Nutzung einer gemeinsamen InOut-Variablen, um Daten ohne zusätzliche Zwischenspeicher zu aktualisieren.
- **Ersatz für einfache Move‑Funktionen**: Ähnlich einem MOVE-Baustein, jedoch mit explizitem UDINT-Fokus und InOut-Mechanik.

## Vergleich mit ähnlichen Bausteinen
- **MOVE (Generic)**: Ein allgemeiner MOVE-Baustein kann Werte beliebigen Typs kopieren, erfordert jedoch separate Ein‑/Ausgänge. `SET_UDINT` nutzt dagegen InOut, was die Verkabelung reduziert und den Zugriff auf die ursprüngliche Variable ermöglicht.
- **SET_BOOL, SET_INT, etc.**: Typvarianten desselben Konzepts für unterschiedliche Datentypen. `SET_UDINT` ist speziell auf 32‑Bit‑Ganzzahlen ohne Vorzeichen optimiert.
- **R_TRIG / F_TRIG**: Diese Flankenerkennungen setzen keine Werte, sondern detektieren Änderungen. `SET_UDINT` agiert direkt wertschreibend.

## Fazit
Der Funktionsblock `SET_UDINT` ist ein schlanker, zuverlässiger Baustein zum Beschreiben einer InOut-Variablen mit einem UDINT-Wert. Seine einfache Struktur (ein Ereignis, eine Zuweisung) macht ihn leicht verständlich und debug-freundlich. Die Verwendung einer InOut-Schnittstelle spart Verkabelungsaufwand und ermöglicht direkte Manipulation externer Variablen. Typisch für IEC 61499 ist er ideal in Automatisierungsprojekten einsetzbar, in denen schnelle und typsichere Wertzuweisungen gefordert sind.
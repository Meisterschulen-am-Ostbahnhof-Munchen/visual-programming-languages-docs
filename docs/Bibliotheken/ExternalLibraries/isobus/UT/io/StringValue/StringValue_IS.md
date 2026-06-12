# StringValue_IS


![StringValue_IS](./StringValue_IS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **StringValue_IS** ist ein Eingangs-Service-Interface-Funktionsblock (Input SIFB) für den Empfang von Zeichenketten-Daten (String) aus einer Ressource. Er dient als standardisierte Schnittstelle, um externe String-Informationen in die 4diac-Umgebung zu integrieren. Typische Anwendungen sind die Anbindung an ISOBUS-Systeme, bei denen Zeichenketten wie Benennungen, Statusmeldungen oder Kennungen empfangen werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung | Mitgeführte Daten |
|---------|------|-------------|-------------------|
| `INIT` | EInit | Initialisierung des Service-Interface-Bausteins | `QI`, `PARAMS`, `u16ObjId` |
| `REQ` | Event | Anforderung zur Datenabfrage oder -aktualisierung | `QI` |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung | Mitgeführte Daten |
|---------|------|-------------|-------------------|
| `INITO` | EInit | Bestätigung der erfolgreichen Initialisierung | `QO`, `STATUS` |
| `CNF` | Event | Bestätigung der ausgeführten Anforderung | `QO`, `STATUS`, `IN` |
| `IND` | Event | Asynchrone Indikation – neue Eingangsdaten von der Ressource | `QO`, `STATUS`, `IN` |

### **Daten-Eingänge**

| Name | Typ | Anfangswert | Beschreibung |
|------|-----|-------------|-------------|
| `QI` | BOOL | – | Ereignisqualifizierer: Steuert die Ausführung der zugehörigen Ereignisse |
| `PARAMS` | STRING | – | Service-Parameter (z. B. Konfiguration des Zugriffs auf die Ressource) |
| `u16ObjId` | UINT | `ID_NULL` | Objekt-ID, die den zu lesenden String in der Ressource identifiziert |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `QO` | BOOL | Ereignisqualifizierer: Zeigt an, ob der Ausgang gültige Daten liefert |
| `STATUS` | STRING | Statusmeldung des Service (z. B. Fehlercodes oder Erfolgsmeldung) |
| `IN` | STRING | Empfangene Zeichenkette von der Ressource |

### **Adapter**

Der Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise

Der **StringValue_IS** arbeitet nach dem üblichen Schema eines Service-Interface-Funktionsblocks für den Dateneingang:

1. **Initialisierung (`INIT`)**  
   Durch Anlegen eines `INIT`-Ereignisses wird der Baustein konfiguriert. Die Parameter `QI` (Qualifizierer), `PARAMS` (Service-Parameter) und `u16ObjId` (Objekt-ID) werden übergeben. Nach erfolgreicher Initialisierung bestätigt der Baustein mit dem Ereignis `INITO` und liefert den Status über `QO` und `STATUS`.

2. **Anforderung (`REQ`)**  
   Ein `REQ`-Ereignis löst eine aktive Datenabfrage bei der Ressource aus. Der Qualifizierer `QI` wird ausgewertet. Die Antwort wird mit dem Ereignis `CNF` zurückgegeben. Der empfangene String steht dann am Ausgang `IN` zur Verfügung.

3. **Asynchrone Indikation (`IND`)**  
   Die Ressource kann jederzeit neue Daten senden. Der Baustein signalisiert dies durch das Ereignis `IND`. Gleichzeitig werden die aktuellen Daten am Ausgang `IN` sowie der Status über `QO` und `STATUS` bereitgestellt.

Die Ausgänge `IN`, `QO` und `STATUS` werden bei jedem der Ereignisse `CNF` und `IND` aktualisiert und können sofort von nachfolgenden Bausteinen verwendet werden.

## Technische Besonderheiten

- **Objekt-ID:**  
  Der Eingang `u16ObjId` ist mit dem Initialwert `ID_NULL` vordefiniert. Vor der ersten Nutzung muss eine gültige Objekt-ID gesetzt werden. Die tatsächliche Bedeutung der ID ist abhängig vom zugrundeliegenden Ressourcen-Protokoll (z. B. ISOBUS-Objektnummer).

- **Service-Parameter (`PARAMS`):**  
  Dieser String-Eingang dient der Übergabe konfigurationsspezifischer Parameter (z. B. Busadresse, Kommunikationspfad). Die genaue Syntax ist vom implementierten Treiber abhängig.

- **Typische Ereignissequenz:**  
  `INIT` → `INITO` → (ggf. wiederholte `REQ` ↔ `CNF` oder asynchrone `IND`).

- **Fehlerbehandlung:**  
  Fehler werden über den `STATUS`-Ausgang signalisiert und können zur Fehlerdiagnose herangezogen werden.

## Zustandsübersicht

Der Baustein durchläuft folgende grundlegende Zustände (nicht im XML explizit modelliert, aber typisch für SIFBs):

- **Nicht initialisiert:** Nach dem Start des Systems. Nur `INIT` wird verarbeitet.
- **Initialisiert:** Nach erfolgreichem `INITO`. Der Baustein ist bereit für `REQ` und kann asynchrone `IND` empfangen.
- **Anforderung läuft:** Nach einem `REQ` bis zum Eintreffen von `CNF`. In dieser Zeit werden keine weiteren Anforderungen verarbeitet.
- **Fehlerzustand:** Bei Fehlern in der Kommunikation. Kann durch erneutes `INIT` zurückgesetzt werden.

## Anwendungsszenarien

- **ISOBUS-Steuergeräte:**  
  Empfangen von Zeichenketten wie Gerätenamen, Variablenbezeichnungen oder Statusmeldungen von einem ISOBUS-Server.

- **Benutzerschnittstellen:**  
  Einlesen von Textdaten, die von einem externen HMI oder einem Bedienpanel gesendet werden.

- **Konfigurationsdaten:**  
  Abrufen von String-Parametern aus einem zentralen Konfigurationsservice.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Datentyp | Besonderheit |
|----------|----------|--------------|
| `BOOL_IS` | BOOL | Einfache boolesche Eingänge (z. B. Schalter) |
| `INT_IS` | INT | Ganzzahlige Eingänge (z. B. Zählerstände) |
| `REAL_IS` | REAL | Gleitkomma-Eingänge (z. B. Messwerte) |
| **`StringValue_IS`** | **STRING** | **Zeichenketten – für Namen, Beschreibungen, irregular formatierte Daten** |

Der `StringValue_IS` ergänzt die Familie der Eingangs-SIFBs um den flexiblen Datentyp `STRING`, der sich durch variable Länge und Inhalt auszeichnet.

## Fazit

Der **StringValue_IS** ist ein wesentlicher Baustein für die Integration zeichenkettenbasierter Daten in 4diac. Er bietet eine standardisierte Schnittstelle zur Ressource, ermöglicht sowohl aktive Abfragen als auch asynchrone Indikationen und lässt sich durch die Parameter `PARAMS` und `u16ObjId` flexibel konfigurieren. Seine Verwendung vereinfacht die Anbindung an Protokolle wie ISOBUS und erhöht die Wiederverwendbarkeit von Anwendungslogiken.
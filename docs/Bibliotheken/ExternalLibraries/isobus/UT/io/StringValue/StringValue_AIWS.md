# StringValue_AIWS


![StringValue_AIWS](./StringValue_AIWS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **StringValue_AIWS** ist ein Eingabe-Service-Interface-Baustein für die Verarbeitung von Wide-String-Daten (UTF‑16) in einem ISOBUS-Kontext. Er stellt eine Adapter-basierte Schnittstelle zur Verfügung, über die externe Ressourcen Zeichenketten eingeben können. Der Baustein dient als Wrapper für den internen Baustein *StringValue_IWS* und bietet eine standardisierte Initialisierungs- und Anforderungsschnittstelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Mit-Variablen | Kommentar |
|---|---|---|---|
| `INIT` | EInit | `QI`, `PARAMS`, `u16ObjId` | Initialisierung des Dienstes |
| `REQ`  | Event | `QI` | Dienstanforderung (Abfrage) |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Mit-Variablen | Kommentar |
|---|---|---|---|
| `INITO` | EInit | `QO`, `STATUS` | Bestätigung der Initialisierung |

### **Daten-Eingänge**

| Name | Typ | Initialwert | Kommentar |
|---|---|---|---|
| `QI` | BOOL | – | Ereignis-Qualifier (Freigabe) |
| `PARAMS` | STRING | – | Dienstparameter (z. B. Konfigurationsstring) |
| `u16ObjId` | UINT | `ID_NULL` | Objekt‑ID (z. B. ISOBUS-Objektkennung) |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|---|---|---|
| `QO` | BOOL | Ausgangs-Qualifier (Status der letzten Operation) |
| `STATUS` | STRING | Statusmeldung (z. B. Fehlertext oder Erfolgsmeldung) |

### **Adapter**

| Name | Typ | Kommentar |
|---|---|---|
| `IN` | `adapter::types::unidirectional::AIWS` | Eingabe von Wide-String-Daten aus der Ressource (unidirektional) |

Der Adapter `IN` empfängt die eigentlichen Zeichenketten und stellt sie dem Baustein zur Verfügung. Die Verbindung erfolgt über die Ereignisleitung `E1` und den Datenkanal `D1`.

## Funktionsweise

Der Baustein initialisiert über das Ereignis `INIT` den internen *StringValue_IWS*-Baustein. Dabei werden die Parameter `QI`, `PARAMS` und `u16ObjId` an diesen weitergegeben. Nach erfolgreicher Initialisierung wird das Ereignis `INITO` ausgelöst und die Ausgabevariablen `QO` und `STATUS` gesetzt.

Mit dem Ereignis `REQ` wird eine Anforderung zur Bereitstellung eines neuen Wide-String-Werts gestartet. Die eigentliche Zeichenkette wird asynchron über den Adapter `IN` geliefert: Sobald der interne Baustein eine neue Zeichenkette empfängt, sendet er ein Ereignis (`IND` oder `CNF`) an den Adapterausgang `E1`, und die Daten werden über den Datenkanal `D1` an die angeschlossene Ressource weitergegeben.

Der Baustein kapselt die gesamte Logik zur Initialisierung und Kommunikation mit dem zugrunde liegenden Wide-String-Dienst und stellt eine einheitliche Adapter-Schnittstelle nach außen bereit.

## Technische Besonderheiten

- **Wide-String-Unterstützung**: Der Baustein ist für UTF‑16 (Wide Strings) ausgelegt und eignet sich daher besonders für internationale Zeichensätze (Unicode).
- **Adapterbasierte Kommunikation**: Die Verwendung eines unidirektionalen Adapters (`AIWS`) erlaubt eine saubere Trennung zwischen Dienstlogik und Ressourcenschnittstelle.
- **ISOBUS-Konformität**: Die Objekt‑ID (`u16ObjId`) wird mit dem Initialwert `ID_NULL` belegt, was auf eine ISOBUS-spezifische Vergabe hinweist.
- **Ereignisgesteuerte Verarbeitung**: Sowohl Initialisierung als auch Datenanforderung werden über explizite Ereignisse ausgelöst, sodass der Baustein in zeitkritischen Umgebungen einsetzbar ist.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine, das Verhalten wird durch die Ereignisse gesteuert:

1. **Ruhezustand** – Der Baustein wartet auf `INIT` oder `REQ`.
2. **Initialisierung** – Nach `INIT` werden die Parameter an den internen Baustein übergeben; die Ausgänge `QO` und `STATUS` aktualisiert und `INITO` gesendet.
3. **Anforderungszustand** – Nach `REQ` wird eine Datenanforderung gestartet. Die Antwort erfolgt asynchron über den Adapter `IN` (Ereignis `E1`).
4. **Fehlerbehandlung** – Bei einem Fehler während der Initialisierung wird `QO` auf `FALSE` gesetzt und eine entsprechende `STATUS`-Meldung ausgegeben.

## Anwendungsszenarien

- **Eingabe von Unicode-Text** in landwirtschaftliche Bedienterminals (ISOBUS-UT) – z. B. für Fahrzeugnamen, Feldnamen oder Produktbezeichnungen.
- **Konfigurationsschnittstelle** für ISOBUS-Geräte, die Wide-String-Parameter benötigen.
- **Anbindung externer Eingabegeräte** (Tastaturen, Touchscreens) an ein ISOBUS-Steuergerät über eine standardisierte Adapter-Schnittstelle.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Schnittstelle | Besonderheit |
|---|---|---|
| `StringValue_AIWS` | Adapter (Eingang) | Empfängt Wide-Strings über den Adapter `AIWS` |
| `StringValue_IWS` | Direkte Events/Daten | Interne Logik, keine Adapter-Schnittstelle |
| `StringValue` (Standard) | Events/Daten | Einfacher Wide-String-Eingang (ohne Adapter) |

Der `StringValue_AIWS` hebt sich durch seine Adapter-basierte Schnittstelle hervor, die eine lose Kopplung zwischen Ressource und Dienst ermöglicht. Er eignet sich besonders für modulare Systeme, bei denen die Datenquelle dynamisch wechseln kann.

## Fazit

Der **StringValue_AIWS** ist ein robuster Eingabe-Service-Interface-Baustein für Wide-String-Daten in ISOBUS-Systemen. Durch die Kombination von ereignisgesteuerter Initialisierung, Adapter-Kommunikation und klarer Schnittstellenstruktur bietet er eine zuverlässige Grundlage für die Verarbeitung von Unicode-Texten in industriellen Anwendungen. Die Trennung von Dienstlogik und Ressourcenschnittstelle vereinfacht die Wartbarkeit und Wiederverwendbarkeit des Bausteins.
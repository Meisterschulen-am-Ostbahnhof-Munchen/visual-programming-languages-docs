# ALI_TO_AULI


![ALI_TO_AULI](./ALI_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ALI_TO_AULI` ist ein Composite-Baustein, der eine bidirektionale Adapterkonvertierung zwischen dem LINT-Adapter (ALI) und dem ULINT-Adapter (AULI) realisiert. Er dient als standardisierte Schnittstelle, um einen mit Vorzeichen behafteten 64‑Bit‑Ganzzahlwert (LINT) in einen vorzeichenlosen 64‑Bit‑Ganzzahlwert (ULINT) umzuwandeln. Der Baustein kapselt den IEC‑61131‑3‑Konvertierungsbaustein `F_LINT_TO_ULINT` und vereinfacht die Einbindung in adapterbasierte Architekturen.

## Schnittstellenstruktur
Der Baustein besitzt keine eigenen Ereignis- oder Datenschnittstellen, sondern lediglich zwei Adapteranschlüsse (Socket und Plug). Die innere Logik erfolgt durch den eingebetteten Unterbaustein und die direkte Verbindung der Adaptersignale.

### **Ereignis-Eingänge**
– Keine (Ereignisse werden über den ALI‑Adapter empfangen)

### **Ereignis-Ausgänge**
– Keine (Ereignisse werden über den AULI‑Adapter gesendet)

### **Daten-Eingänge**
– Keine (Daten werden über den ALI‑Adapter empfangen)

### **Daten-Ausgänge**
– Keine (Daten werden über den AULI‑Adapter ausgegeben)

### **Adapter**
| Adaptertyp | Richtung | Name | Kommentar |
|------------|----------|------|-----------|
| `adapter::types::unidirectional::ALI` | Socket (Eingang) | `ALI_IN` | LINT‑Adapter‑Eingang (liefert Ereignis und einen LINT‑Wert) |
| `adapter::types::unidirectional::AULI` | Plug (Ausgang) | `AULI_OUT` | ULINT‑Adapter‑Ausgang (gibt Ereignis und einen ULINT‑Wert weiter) |

## Funktionsweise
Der Baustein arbeitet als reine Durchreiche‑Konvertierung:
1. Ein eingehendes Ereignis am Socket `ALI_IN.E1` triggert den internen Baustein `Convert` (`F_LINT_TO_ULINT`) über dessen Ereigniseingang `REQ`.
2. Gleichzeitig wird der vom Socket bereitgestellte LINT‑Wert (`ALI_IN.D1`) an den Dateneingang `IN` von `Convert` übergeben.
3. Nach erfolgreicher Konvertierung signalisiert `Convert` mit einem Ereignis an seinem Ausgang `CNF`, welches direkt an den Plug `AULI_OUT.E1` weitergeleitet wird.
4. Der konvertierte ULINT‑Wert (`Convert.OUT`) wird parallel an den Dateneingang `D1` des AULI‑Adapters übergeben.

Somit wird eine vollständige, ereignisgesteuerte und datensynchrone Umwandlung ohne zusätzliche Verzögerung oder Logik realisiert.

## Technische Besonderheiten
- **Verwendeter Unterbaustein**: `iec61131::conversion::F_LINT_TO_ULINT` – standardkonforme Typkonvertierung gemäß IEC 61131‑3.
- **Adapter‑Kopplung**: Der Baustein setzt auf das unidirektionale Adapter‑Konzept von 4diac und ermöglicht die lose Kopplung zwischen verschiedenen Datentypschnittstellen.
- **Keine Zustandshaltung**: Als Composite‑Baustein besitzt `ALI_TO_AULI` keinen eigenen internen Zustand; alle Entscheidungen werden durch den Unterbaustein getroffen.
- **Plattformunabhängigkeit**: Der Baustein kann in jeder 4diac‑Umgebung eingesetzt werden, die die IEC‑61131‑Konvertierungsbausteine bereitstellt.

## Zustandsübersicht
Der Baustein selbst führt keinen Zustandsautomaten. Sämtliche Zustandsübergänge werden vom internen `F_LINT_TO_ULINT` gesteuert, der nach einem Ereignis am Eingang `REQ` in den Zustand „konvertiere“ wechselt und nach Abschluss ein Bestätigungsereignis ausgibt. Da diese Zustände nicht nach außen sichtbar sind, wird auf eine detaillierte Darstellung verzichtet.

## Anwendungsszenarien
- **Systemintegration**: Anbindung eines älteren Steuerungssystems, das LINT‑Werte (vorzeichenbehaftet) verwendet, an eine moderne Komponente, die nur ULINT‑Werte (vorzeichenlos) verarbeiten kann.
- **Datenkonvertierung in Adapterketten**: Einbettung zwischen zwei Adaptern, z. B. in einer Datenvorverarbeitungskette, die eine einheitliche ULINT‑Schnittstelle erfordert.
- **Migration**: Ersatz von LINT‑basierten Bausteinen durch ULINT‑Äquivalente, ohne die gesamte Adapterinfrastruktur ändern zu müssen.

## Vergleich mit ähnlichen Bausteinen
In der Bibliothek existieren analoge Konverter für andere Datentypen, z. B. `DINT_TO_UDINT` oder `REAL_TO_LREAL`. `ALI_TO_AULI` unterscheidet sich durch die spezifische Adapter‑Schnittstelle und die Kapselung des Konvertierungsbausteins in einem Composite. Während die reinen IEC‑Bausteine einzelne Daten‑ und Ereignisschnittstellen besitzen, ermöglicht dieser Baustein eine direkte Adapter‑zu‑Adapter‑Konvertierung, was den Entwurf modulärer und austauschbarer Komponenten erleichtert.

## Fazit
Der `ALI_TO_AULI`‑Baustein bietet eine einfache und zuverlässige Möglichkeit, LINT‑Adapter in ULINT‑Adapter umzuwandeln. Er kapselt die Standardkonvertierung sauber in einer adapterbasierten Architektur und trägt so zur Wiederverwendbarkeit und Interoperabilität von 4diac‑Anwendungen bei. Durch die Verwendung des bewährten IEC‑Bausteins ist die Konvertierung korrekt und plattformunabhängig.
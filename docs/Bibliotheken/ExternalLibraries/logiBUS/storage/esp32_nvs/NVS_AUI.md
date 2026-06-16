# NVS_AUI


![NVS_AUI](./NVS_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **NVS_AUI** dient dem Laden und Speichern von UINT-Daten in einem nichtflüchtigen Speicher (NVS) mittels eines Schlüssels (Key). Er kapselt die Zugriffe auf den NVS und stellt eine standardisierte AUI‑Adapter‑Schnittstelle bereit, über die gelesene Werte ausgegeben und zu speichernde Werte entgegengenommen werden. Typische Einsatzorte sind eingebettete Systeme, die Konfigurations- oder Zustandsdaten persistent ablegen müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar | Mitgeführte Daten |
|----------|-----------|-------------------|
| `INIT`   | Service‑Initialisierung | `QI` (BOOL), `KEY` (STRING), `DEFAULT_VALUE` (UDINT) |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar | Mitgeführte Daten |
|----------|-----------|-------------------|
| `INITO`  | Initialisierungsbestätigung | `QO` (BOOL), `STATUS` (STRING) |

### **Daten-Eingänge**

| Name            | Typ    | Kommentar |
|-----------------|--------|-----------|
| `QI`            | BOOL   | Qualifikator für das Eingangsereignis |
| `KEY`           | STRING | Schlüsselname für den NVS‑Zugriff |
| `DEFAULT_VALUE` | UDINT  | Wert, der ausgelesen wird, falls im NVS kein Eintrag vorhanden |

### **Daten-Ausgänge**

| Name     | Typ    | Kommentar |
|----------|--------|-----------|
| `QO`     | BOOL   | Qualifikator für das Ausgangsereignis |
| `STATUS` | STRING | Dienststatus‑Meldung |

### **Adapter**

| Adapter    | Typ / Richtung                         | Kommentar |
|------------|----------------------------------------|-----------|
| `AUI_IN`   | **Socket** (Eingang) – Typ: `adapter::types::unidirectional::AUI` | Liefert den zu speichernden Wert (SET) |
| `AUI_OUT`  | **Plug** (Ausgang) – Typ: `adapter::types::unidirectional::AUI` | Gibt den ausgelesenen Wert aus (GETO) |

## Funktionsweise
1. **Initialisierung**  
   Ein `INIT`‑Ereignis löst die Verbindung zum nichtflüchtigen Speicher aus. Dabei werden der Schlüssel (`KEY`) und der Standardwert (`DEFAULT_VALUE`) übergeben. Nach erfolgreicher Initialisierung wird `INITO` mit dem Ergebnis (`QO` / `STATUS`) quittiert.

2. **Daten lesen**  
   Nach der Initialisierung wird intern automatisch der gespeicherte Wert zum angegebenen Schlüssel gelesen und über den Ausgangsadapter `AUI_OUT` als Ereignis (E1) und Daten (D1) bereitgestellt. Falls kein Eintrag existiert, wird der `DEFAULT_VALUE` ausgegeben.

3. **Daten speichern**  
   Über den Eingangsadapter `AUI_IN` kann ein neuer Wert empfangen werden. Ein eingehendes Ereignis (E1) mit den zugehörigen Daten (D1) wird an den internen NVS‑Funktionsblock weitergeleitet, der den Wert unter dem initialisierten Schlüssel persistent ablegt.

Der gesamte Daten‑ und Ereignisfluss wird durch den eingebetteten Funktionsblock `NVS` (aus der Bibliothek `logiBUS::storage::esp32_nvs`) realisiert.

## Technische Besonderheiten
- **AUI‑Adapter‑Schnittstelle**  
  Die unidirektionalen Adapter `AUI_IN` und `AUI_OUT` ermöglichen eine lose Kopplung zwischen dem NVS‑Baustein und anderen Komponenten, die standardisierte AUI‑Schnittstellen verwenden.
- **Automatischer Lesevorgang nach INIT**  
  Direkt nach der Initialisierung wird der Wert gelesen und über `AUI_OUT` bereitgestellt – ohne ein separates „Get“‑Ereignis.
- **Fehlerbehandlung**  
  Fehler während der Initialisierung oder bei Speicherzugriffen werden über `STATUS` signalisiert.

## Zustandsübersicht
Der FB befindet sich nach dem Hochlaufen im **Ruhezustand**.  
- **Initialisierung** (beim Eintreffen von `INIT`): Herstellen der NVS‑Verbindung, Lesen des vorhandenen Werts.  
- **Bereit** (nach erfolgreichem `INITO`): Warten auf eingehende Daten über `AUI_IN` zum Speichern oder auf externe Anfragen über `AUI_OUT`.  
- **Speichervorgang** (bei Ereignis an `AUI_IN`): Wert wird persistiert; danach Rückkehr in den Bereit‑Zustand.  
- **Fehlerzustand** (bei nicht erfolgreicher Initialisierung): `QO` = FALSE, `STATUS` enthält Fehlertext.

## Anwendungsszenarien
- **Konfigurationsspeicher** in IoT‑Geräten: Ablegen von Netzwerkeinstellungen, Kalibrierdaten oder Benutzereinstellungen.  
- **Zustandsüberwachung**: Speichern des letzten Betriebszustands (z. B. Zählerstände) vor einem Spannungsausfall.  
- **Parameterübergabe** zwischen unterschiedlichen Automatisierungskomponenten, die über AUI‑Adapter kommunizieren.

## Vergleich mit ähnlichen Bausteinen
Gegenüber dem direkten **NVS**‑Funktionsblock bietet `NVS_AUI` eine höhere Abstraktion durch die Adapter‑Schnittstelle. Während der Basis‑Baustein separate Ereignisse für Lesen (`GET`) und Schreiben (`SET`) benötigt, vereinfacht `NVS_AUI` den Datenfluss durch die unidirektionalen Adapter und den automatischen Lesevorgang nach INIT. Andere Speicherbausteine (z. B. `F_MMAP`, `F_FILE`) verwenden meist dateibasierte oder speicherabbildende Verfahren; `NVS_AUI` ist speziell für nichtflüchtige Speicher mit Schlüssel‑Wert‑Paaren optimiert.

## Fazit
`NVS_AUI` ist ein praktischer Funktionsblock zur persistenten Datenhaltung in Automatisierungssystemen. Die Kombination aus NVS‑Speicher und AUI‑Adapter erlaubt eine einfache Einbindung in bestehende IEC 61499‑Applikationen, reduziert den Verdrahtungsaufwand und sorgt für eine klare Trennung zwischen Speicherlogik und Kommunikation.
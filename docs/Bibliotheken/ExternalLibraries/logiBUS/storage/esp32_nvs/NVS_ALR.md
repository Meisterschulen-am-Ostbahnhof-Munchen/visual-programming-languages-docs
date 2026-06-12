# NVS_ALR


![NVS_ALR](./NVS_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **NVS_ALR** dient zum Laden und Speichern von Werten des Typs `LREAL` in einem nichtflüchtigen Speicher (Non-Volatile Storage, NVS) unter Verwendung eines Schlüssels (Key). Er ist speziell für die Anbindung über den unidirektionalen **ALR-Adapter** ausgelegt. Der Baustein kombiniert eine Initialisierungsphase, in der der Speicherinhalt gelesen wird, mit einer späteren Schreib- und Leseoperation über den Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| **INIT**  | Initialisiert den Baustein und führt einen ersten Lesevorgang aus dem NVS durch. | QI, KEY, DEFAULT_VALUE |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| **INITO** | Bestätigung der Initialisierung und Rückmeldung des Ergebnisses. | QO, STATUS |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| QI       | BOOL  | Steuerung für die Initialisierung (TRUE = aktiv). |
| KEY      | STRING| Schlüsselname für den NVS-Zugriff. |
| DEFAULT_VALUE | LREAL | Wert, der gelesen wird, falls im NVS noch kein Eintrag unter dem angegebenen Schlüssel existiert. |

### **Daten-Ausgänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| QO       | BOOL  | Quittung der Initialisierung (TRUE = erfolgreich). |
| STATUS   | STRING| Statusmeldung (z. B. Fehlertext bei misslungenem Zugriff). |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **ALR_IN** | Socket | `adapter::types::unidirectional::ALR` | Empfängt Schreibaufträge (Wert speichern). |
| **ALR_OUT** | Plug   | `adapter::types::unidirectional::ALR` | Sendet gelesene Werte nach einem Lesevorgang. |

## Funktionsweise

1. **Initialisierung**  
   Nach einem Ereignis am **INIT**-Eingang wird der interne Baustein `NVS` mit dem angegebenen Schlüssel (`KEY`), dem Default-Wert (`DEFAULT_VALUE`) und der Aktivierung (`QI`) aufgerufen. Der Initialisierungsvorgang öffnet den NVS-Bereich und liest sofort den vorhandenen Wert aus. Dieser Wert wird über den **ALR_OUT**-Adapter als Ereignis mit dem zugehörigen Datenwert (`D1`) ausgegeben. Gleichzeitig wird der **INITO**-Ereignisausgang mit den Quittungen (`QO`, `STATUS`) ausgelöst.

2. **Schreiben über ALR_IN**  
   Ein Ereignis am **ALR_IN.E1**-Eingang (verbunden mit dem Socket) löst einen **SET**-Vorgang aus. Der mitgelieferte Datenwert (`ALR_IN.D1`) wird in den NVS unter dem zuvor gespeicherten Schlüssel geschrieben. Nach erfolgreichem Schreiben wird das Ereignis an **ALR_OUT.E1** weitergegeben und der geschriebene Wert dort ausgegeben.

3. **Lesen über ALR_IN?**  
   Im vorliegenden Netzwerk wird nach der Initialisierung automatisch ein **GET**-Befehl ausgelöst. Ein expliziter Leseaufruf über den Adapter ist im Entwurf nicht vorgesehen; der Baustein gibt den aktuellen Wert immer nach jeder NVS-Operation (INIT, SET) über **ALR_OUT** aus.

## Technische Besonderheiten

- **Adapterinterface**  
  Die Kommunikation mit der Außenwelt erfolgt ausschließlich über den unidirektionalen ALR-Adapter. Dadurch wird der Baustein besonders geeignet für modulare Architekturen, bei denen Datenflüsse über standardisierte Schnittstellen abgewickelt werden.
- **Interner NVS-Baustein**  
  Im Netzwerk wird der FB `NVS` (aus der Bibliothek `logiBUS::storage::esp32_nvs`) verwendet. Dieser kapselt die eigentliche Lese- und Schreiblogik auf dem ESP32-NVS.
- **Automatischer Lesevorgang**  
  Nach der Initialisierung wird sofort ein GET ausgeführt, sodass der Anwender unmittelbar den aktuellen Wert (Standardwert oder gespeicherten Wert) erhält.
- **Fehlerbehandlung**  
  Die Ausgänge `QO` und `STATUS` erlauben eine einfache Prüfung des Initialisierungserfolgs. Fehler werden als String gemeldet.

## Zustandsübersicht

Der Baustein durchläuft keine explizit modellierten Zustände, sondern ist ereignisgesteuert. Folgendes Verhalten tritt auf:

- **Ruhezustand** – Kein INIT erfolgt. Es werden keine Aktionen ausgeführt.
- **Initialisieren** – INIT empfangen; NVS-Operationen werden gestartet; nach Abschluss wird INITO ausgelöst und ein GET angestoßen.
- **Bereit** – Nach erfolgreicher Initialisierung wartet der Baustein auf Ereignisse über **ALR_IN.E1** (Schreiben) oder interne GETs (werden nur initial automatisch ausgelöst).
- **Schreiben** – Bei ALR_IN.E1 wird der Wert gespeichert und das Ergebnis an ALR_OUT gesendet.

## Anwendungsszenarien

- **ESP32-Konfigurationsparameter**  
  Speicherung von LREAL-Werten wie Kalibrierungsfaktoren, Schwellwerten oder PID-Parametern, die nach einem Neustart erhalten bleiben sollen. Der ALR-Adapter ermöglicht die einfache Integration mit anderen Bausteinen, die denselben Adaptertyp verwenden.
- **Gekapselter Datenzugriff**  
  Wenn ein Baustein LREAL-Werte aus dem NVS lesen und schreiben muss, aber die direkte Verwendung des NVS-Bausteins zu komplex erscheint, bietet NVS_ALR eine abstrahierte Schnittstelle.
- **Modulare Automatisierung**  
  Einsatz in Industrie 4.0-Anwendungen, bei denen Geräte über standardisierte Adapterdienste kommunizieren (z. B. über eine ALR-Konfigurationsschicht).

## Vergleich mit ähnlichen Bausteinen

- **NVS (direkt)**  
  Der Baustein `NVS` bietet mehr Flexibilität (z. B. wahlfreier Zugriff, unterschiedliche Datentypen), erfordert aber eine aufwändigere Verkabelung und explizite GET/SET-Aufrufe. NVS_ALR reduziert die Komplexität auf eine Adapterschnittstelle.
- **BOOL_NVS, INT_NVS (hypothetisch)**  
  Analoge Bausteine für andere Datentypen. NVS_ALR ist speziell auf LREAL zugeschnitten und nutzt den ALR-Adapter, der typischerweise für LREAL-Daten vorgesehen ist.
- **Remanente Variablen**  
  In manchen Systemen können remanente Variablen direkt im FB-Modell verwendet werden. NVS_ALR ist jedoch explizit für den Einsatz mit einem externen Flash-Speicher (NVS) konzipiert und daher portabler.

## Fazit

Der **NVS_ALR**-Funktionsbaustein bietet eine kompakte und benutzerfreundliche Möglichkeit, LREAL-Werte persistent in einem NVS zu speichern und über einen unidirektionalen Adapter auszutauschen. Durch die Kombination von Initialisierung, automatischem Lesen und Adapter-basiertem Schreiben eignet er sich besonders für modulare und wiederverwendbare Steuerungsanwendungen auf ESP32-Basis. Sein Design folgt dem IEC 61499-Standard und ermöglicht eine saubere Trennung von Speicherlogik und Applikation.
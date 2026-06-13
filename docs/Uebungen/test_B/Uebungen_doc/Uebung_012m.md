# Uebung_012m: String Input und Speichern NVS mit Subapp

* * * * * * * * * *

## Einleitung

Diese Übung demonstriert die Verarbeitung eines Zeichenketten-Inputs (String) aus einer isobus-Quelle und das Speichern sowie Auslesen des Wertes in/aus dem nichtflüchtigen Speicher (NVS) eines ESP32. Die gesamte Logik ist in einer gekapselten SubApp organisiert, die die Wiederverwendbarkeit und Modularität fördert. Ziel ist es, eine robuste Speicherung von Konfigurationsdaten oder Benutzereingaben zu realisieren, die auch nach einem Neustart erhalten bleibt.

## Verwendete Funktionsbausteine (FBs)

### Sub-Baustein: Uebung_012m_sub

- **Typ**: `SubAppType` (eigene SubApp)
- **Verwendete interne FBs**:
  - **StringValue_IS**: `isobus::UT::io::StringValue::StringValue_IS`
    - **Parameter**: `QI` = `TRUE`
    - **Ereignisausgang/-eingang**: 
      - Eingang: (kein expliziter Ereigniseingang im XML, wird über `IND` von darüber liegender Logik gesteuert – hier nicht direkt sichtbar)
      - Ausgang: `IND` – signalisiert, dass der Wert von der isobus-Quelle gelesen wurde
    - **Datenausgang/-eingang**:
      - Eingang: `u16ObjId` (über SubApp-Parameter verbunden) – Identifikation des isobus-Objekts
      - Ausgang: `IN` – der gelesene String-Wert
  - **NVS**: `logiBUS::storage::esp32_nvs::NVS`
    - **Parameter**: `QI` = `TRUE`, `DEFAULT_VALUE` = `STRING#''`
    - **Ereigniseingänge/-ausgänge**:
      - Eingänge: `SET` (schreiben), `GET` (lesen), `INIT` (Initialisierung)
      - Ausgänge: `SETO` (Schreiben bestätigt), `GETO` (Lesen bestätigt), `INITO` (Initialisierung abgeschlossen)
    - **Dateneingänge/-ausgänge**:
      - Eingänge: `KEY` (Schlüssel für NVS-Eintrag), `VALUE` (zu speichernder Wert)
      - Ausgänge: `VALUEO` (ausgelesener Wert)
  - **Q_StringValue**: `isobus::UT::Q::Q_StringValue`
    - **Parameter**: keine sichtbaren in der XML
    - **Ereigniseingang/-ausgang**:
      - Eingang: `REQ` – Anforderung zur Ausgabe des Wertes auf den isobus-Bus
      - Ausgang: (nicht im XML gelistet, dient der Bus-Kommunikation)
    - **Dateneingänge/-ausgänge**:
      - Eingang: `u16ObjId` (Objekt-ID für isobus), `pau8String` (Zeiger auf String-Daten)
      - Ausgang: keiner sichtbar (sendet über isobus)

- **Funktionsweise**:
  Die SubApp `Uebung_012m_sub` kapselt den gesamten Ablauf: Einlesen eines Strings über `StringValue_IS`, Speichern im NVS über den FB `NVS`, und optionales Senden des gespeicherten Wertes über den isobus-Bus mit `Q_StringValue`. Die Parameter `KEY` und `u16ObjId` werden von außen übergeben und bestimmen den NVS-Speicherplatz bzw. die isobus-Objekt-ID.

  **Ablauf**:
  1. Nach der Initialisierung (`NVS.INITO`) wird automatisch ein Lesevorgang (`NVS.GET`) ausgelöst. Der ausgelesene Wert liegt dann an `NVS.VALUEO`.
  2. Bei einem Event von außen (nicht gezeigt, aber logisch) wird `StringValue_IS` aktiviert. Dessen Ausgang `IND` triggert `NVS.SET`, wodurch der aktuelle String im NVS gespeichert wird.
  3. Nach erfolgreichem Schreiben (`NVS.SETO`) oder Lesen (`NVS.GETO`) wird ein Event an den Ausgang `IND` der SubApp gesendet.
  4. Gleichzeitig wird bei jedem Lesevorgang (`NVS.GETO`) der ausgelesene Wert über `Q_StringValue.REQ` an den isobus-Bus gesendet, sodass andere Geräte den aktuellen Wert abfragen können.

## Programmablauf und Verbindungen

Die Haupt-SubApp `Uebung_012m` instanziiert `Uebung_012m_sub` und versorgt diese mit zwei Parametern:
- `KEY` = `KEY_I1_STORE` (ein konstanter Schlüssel für den NVS-Eintrag)
- `u16ObjId` = `InputString_S1` (die isobus-Objekt-ID, von der der Eingabestring gelesen wird)

Die Verbindungen innerhalb von `Uebung_012m_sub` sind wie folgt (aus der XML-Datei):

- **Ereignisflüsse**:
  - `StringValue_IS.IND` → `NVS.SET` (nach Einlesen eines neuen Strings wird dieser sofort gespeichert)
  - `NVS.SETO` → SubApp-Eventausgang `IND` (Signal nach erfolgreichem Schreiben)
  - `NVS.GETO` → `Q_StringValue.REQ` sowie → SubApp-Eventausgang `IND` (nach Lesen wird der Wert auf den Bus gegeben und Signal ausgegeben)
  - `NVS.INITO` → `NVS.GET` (direkt nach Initialisierung wird der gespeicherte Wert gelesen)

- **Datenflüsse**:
  - `StringValue_IS.IN` → `NVS.VALUE` (der eingelesene String wird dem NVS zum Speichern übergeben)
  - `NVS.VALUEO` → `Q_StringValue.pau8String` (der ausgelesene String wird zum Senden vorbereitet)
  - `NVS.VALUEO` → SubApp-Datenausgang `VALUEO` (zur Weitergabe an darüberliegende Schichten)
  - `KEY` (extern) → `NVS.KEY`
  - `u16ObjId` (extern) → `StringValue_IS.u16ObjId` und `Q_StringValue.u16ObjId`

**Hinweise**:
- Die Übung setzt voraus, dass die isobus-Bibliothek und der NVS-Treiber für den ESP32 in der Laufzeitumgebung vorhanden sind.
- Der Parameter `DEFAULT_VALUE = STRING#''` definiert einen leeren String als Standard, falls im NVS noch kein Wert hinterlegt ist.
- Die Verbindungen sind als sichtbar markiert (außer einige mit `Visible = false` – diese dienen lediglich der internen Verschaltung und sind in der grafischen Darstellung der IDE standardmäßig ausgeblendet).

## Zusammenfassung

In dieser Übung wird der Umgang mit String-Eingaben, nichtflüchtigem Speicher (NVS) und isobus-Kommunikation in einer gekapselten SubApp trainiert. Die Lernziele umfassen:
- Verständnis für die Initialisierung und Nutzung des NVS-FBs.
- Ereignisgesteuerte Verkettung von Lese-, Schreib- und Kommunikationsvorgängen.
- Parametrisierung von SubApps zur Wiederverwendung.
- Integration von isobus-Objekten zur Datenübertragung.

**Schwierigkeitsgrad**: Mittel  
**Benötigte Vorkenntnisse**: Grundlagen der 4diac-IDE, Ereignis- und Datenverbindungen, einfache FBs.  
**Start der Übung**: Laden Sie die Haupt-SubApp `Uebung_012m` in ein Projekt und verbinden Sie die Eingänge `KEY` und `u16ObjId` mit entsprechenden Konstanten oder Variablen. Die Ausgabe `VALUEO` kann z. B. an eine Anzeige angeschlossen werden.